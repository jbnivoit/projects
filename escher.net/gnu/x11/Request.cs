using System;
using System.Collections;
using System.IO;

namespace gnu.x11 {


/**
 * Request to X server.
 *
 * <h3>Aggregate Requests</h3>
 * 
 * In C xlib, "similar requests" will be aggregated into one if possible. 
 * For example, setting foreground followed by setting background of a gc
 * can be aggregated into one <code>ChangeGC</code> request (as suggested
 * in Section 1.4.1 "Client Library Implementation" on page 36 of <cite>X
 * Protocol Reference Manual</cite> by Adrian Nye).
 *
 * <p>Details on how C xlib implements this feature is unclear (missing?) 
 * because of arcane C macros. Without a documented reference
 * implementation, an early attempt to implement such a feature into this
 * library was a failure. We did not have a clear mind of the exact
 * conditions of when a request can be aggregated into previous requests in
 * the queue.
 *
 * <p>There are two kinds of requests that can be aggregated:
 * <ul>
 * 
 * <li>value list requests
 * <ul>
 * <li><code>ChangeGC</code>
 * <li><code>ChangeKeyboardControl</code>
 * <li><code>ChangeWindowAttributes</code>
 * <li><code>ConfigureWindow</code>)
 * </ul>
 *
 * <li>poly drawing requests
 * <ul>
 * <li><code>FillPoly</code>
 * <li><code>Poly/Fill Arc</code>
 * <li><code>PolyLine</code>
 * <li><code>PolyPoint</code>
 * <li><code>Poly/Fill Rectangle</code>
 * <li><code>PolySegment</code>
 * </ul>
 * 
 * </ul>
 *
 * Note that <code>PolyText</code> cannot be aggregated easily in general
 * because of the presence of <code>x</code> and <code>y</code> parameter. 
 * Besides of being the same protocol opcode, two requests to be aggregated
 * have to be acting on the same drawable and using the same gc. Special
 * care must be taken for different <code>coordinate_mode</code>. Moreover,
 * the gc must not have been changed since the last poly request. That is,
 * we need to keep track of gc modification requests
 * (<code>ChangeGC</code>, <code>SetDashes</code>, and
 * <code>SetClipRectangles</code>) to mark the respective gc "dirty". 
 * However, there is one more critical condition that makes aggregating
 * poly drawing requests almost worthless: drawing order. For example,
 * given there are <code>PolyRectangleRequest r1</code> and
 * <code>PolyArcRequest r2</code>, even when a <code>PolyRectangleRequest
 * r3</code> comes in and <code>r1</code> and <code>r3</code> are "similar"
 * (same opcode, same "clean" gc, same drawable), they cannot be aggregated
 * because of the drawing order. If aggregated, drawing <code>r2</code>
 * would overwrite <code>r3</code>, producing an unintended result.
 *
 * <p>For value list requests, the conditions are less restrictive. Two
 * requests to be aggregated have to be of the same opcode code and acting
 * on the same object. However, there is also one critical condition: state
 * dependency. For example, two requests for setting a gc cannot be
 * aggregated if there is a drawing request in between. If aggregated, the
 * second background would be used instead of the first one. The same
 * applies to changing window attributes when in between there are other
 * requests that depends on the states of the window.
 *
 * <p>In conclusion, to aggregate poly drawing requests at maximum level,
 * we must identify all drawing requests in core and extension requests to
 * preserve the drawing order. The same applies to value list requests but
 * with more cases to be handled. At a lesser level (current implementation
 * of this library), we can aggregate a new request with only the last one
 * in the queue such that there are no order or dependency conditions. This
 * way convenience methods of
 * 
 * <ul>
 * <li><code>ChangeGC</code>
 * <li><code>ChangeKeyboardControl</code>
 * <li><code>ChangeWindowAttributes</code>
 * <li><code>ConfigureWindow</code>)
 * <li><code>FillPoly</code>
 * <li><code>Poly/Fill Arc</code>
 * <li><code>PolyLine</code>
 * <li><code>PolyPoint</code>
 * <li><code>Poly/Fill Rectangle</code>
 * <li><code>PolySegment</code>
 * </ul>
 * 
 * such as {@link gnu.x11.GC#set_foreground} can be used extensively
 * without generating extra requests. However, it fails to aggregate at
 * maximum level. For example, two requests for setting a gc will never be
 * aggregated (while it is safe to do so) if there is a request for
 * querying font in between.
 *
 *
 * <p>[Sep 07, 00] Finally, in xlib.ps, I have found a note of xlib's
 * implementation of this feature, which is called "batching". A discussion
 * can be found in section C.4 "Graphics Batching" of Appendix C "Writing
 * Extensions to X" of the postscript document, or you can view it from <a
 * href=
 * "http://www.tronche.com/gui/x/xlib/appendix/c/graphics-batching.html">
 * here</a>. Basically xlib implements batching using the same technique
 * described above but with specialized buffers and less OOP.
 *
 */
public class Request : Data {
  public int length;
	public int Length { 
		get { return length; } 
		set { length=value; }
	}


  public Request () {}          // for PolyRequest and ValueListRequest


  public Request (Display display, int opcode, int i, int unit) {
    init (display, opcode, i, unit);
  }


  public Request (Display display, int opcode, bool b, int unit) {
    init (display, opcode, b ? 1 : 0, unit);
  }


  public Request (Display display, int opcode, int unit) {
    init (display, opcode, 0, unit);
  }


  /** Base class for aggregating requests. */
	public abstract class Aggregate : Request {
    public abstract bool aggregate (Request request);
    public abstract override void write (Stream output) ;//throws IOException;
  }
  

  /** Aggregate value list requests. */
  public /*static*/ class ValueList : Aggregate {
    public Display display;
    public int opcode;
	public new int unit;
	public int id;
    public gnu.x11.ValueList vl;
  
  
    public ValueList (Display display, int opcode, int unit, 
      int id, gnu.x11.ValueList vl) {
  
      this.display = display;
      this.opcode = opcode;
      this.unit = unit;
      this.id = id;
      this.vl = vl;
    }
  
  
    public override bool aggregate (Request request) {
      if (!(request is ValueList)) return false;
  
      ValueList vlr = (ValueList) request;
      if (vlr.opcode != opcode || vlr.id != id) return false;
  
      vlr.vl.aggregate (vl);
      return true;
    }
  
    
    public override void write (Stream output) //throws IOException {  
	{
      unit += vl.count ();
      init (display, opcode, 0, unit);
  
  
      if (opcode != 102)          // special case: change keyboard control
        write4 (id);
  
      if (opcode == 12) {         // special case: configure window
        write2 (vl.bitmask);
        write2_unused ();
  
      } else      
        write4 (vl.bitmask);
  
      vl.write (this);
      output.Write (data,0,data.Length);
    }
  }

  
  /** Aggregate poly drawing requests. */
  public abstract class Poly : Aggregate {
    public Drawable drawable;
    public GC gc;
    public ArrayList items_sets = new ArrayList();
    public int items_sets_unit_count;
    public int opcode;
  
   
    public Poly (int opcode, Drawable drawable, GC gc,
      Object [] items, int item_unit_count) {
  
      this.opcode = opcode;
      this.drawable = drawable;
      this.gc = gc;
      items_sets.Add (items);
      items_sets_unit_count = items.Length * item_unit_count;
    }
  
  
    /** Aggregate fill poly requests. */
    public /*static*/ class Fill : Poly {
      int coordinate_mode;
      public int shape;
    
    
      public Fill (Drawable drawable, GC gc, 
        Point [] points, int shape, int coordinate_mode) 
    
        :base (69, drawable, gc, points, 1) {
        this.shape = shape;
        this.coordinate_mode = coordinate_mode;
      }
    
    
      public override bool more_aggregatep (Poly pr) {
        Fill fpr = (Fill) pr;
    
        return coordinate_mode == Drawable.ORIGIN 
          && fpr.coordinate_mode == Drawable.ORIGIN
          && fpr.shape == shape;
      }
    
    
      public override void write (Stream output, Object item)
    	//    throws IOException 
	{
    
        Point point = (Point) item;
        write2 (point.x);
        write2 (point.y);
      }
    
    
      public override void write_head () {
        int unit = 4 + items_sets_unit_count;
        init (drawable.display, opcode, 0, unit);
    
        write4 (drawable.id);
        write4 (gc.id);
        write1 (shape);
        write1 (coordinate_mode);
        write2_unused ();
      }
    }


    /** Aggregate poly arc requests. */
    public /*static*/ class Arc : Poly {
      public Arc (Drawable drawable, GC gc, gnu.x11.Arc [] arcs, 
        bool fill) 
    
        :base (fill ? 71 : 68, drawable, gc, arcs, 3){
      }
    
    
      public override void write (Stream output, Object item) //throws IOException 
	{    
        gnu.x11.Arc arc = (gnu.x11.Arc) item;
        write2 (arc.x);
        write2 (arc.y);
        write2 (arc.width);
        write2 (arc.height);
        write2 (arc.angle1);
        write2 (arc.angle2);
      }
    }



    /** Aggregate poly dot requests. */
    public /*static*/ class Dot : Poly {
      public int coordinate_mode;
    
    
      public Dot (Drawable drawable, GC gc, 
        gnu.x11.Point [] points, int coordinate_mode, bool join) 
    
        :base (join ? 65 : 64, drawable, gc, points, 1){
        this.coordinate_mode = coordinate_mode;
      }
    
    
      public override bool more_aggregatep (Poly pr) {
        return coordinate_mode == Drawable.ORIGIN 
          && ((Dot) pr).coordinate_mode == Drawable.ORIGIN;
      }
    
    
      public override void write (Stream output, Object item)
    	//    throws java.io.IOException 
	{
    
        gnu.x11.Point point = (gnu.x11.Point) item;
        write2 (point.x);
        write2 (point.y);
      }
    
    
      public override void write_head () {
        int unit = 3 + items_sets_unit_count;
        init (drawable.display, opcode, coordinate_mode, unit);
    
        write4 (drawable.id);
        write4 (gc.id);
      }
    }


    /** Aggregate poly rectangle requests. */
    public /*static*/ class Rectangle : Poly {
      public Rectangle (Drawable drawable, GC gc,
        gnu.x11.Rectangle [] rectangles, bool fill)
    	:base (fill ? 70 : 67, drawable, gc, rectangles, 2){
      }
    
    
      public override void write (Stream output, Object item)
    	//    throws java.io.IOException 
	{
    
        gnu.x11.Rectangle rectangle = (gnu.x11.Rectangle) item;
        write2 (rectangle.x);
        write2 (rectangle.y);
        write2 (rectangle.width);
        write2 (rectangle.height);
      }
    }


    /** Aggregate poly segment requests. */
    public /*static*/ class Segment : Poly {
      public Segment (Drawable drawable, GC gc, 
        gnu.x11.Segment [] segments) :
        base (66, drawable, gc, segments, 2) {
      }
    
    
      public override void write (Stream output, Object item) 
    	//    throws IOException 
	{
    
        gnu.x11.Segment segment = (gnu.x11.Segment) item;
        write2 (segment.x1);
        write2 (segment.y1);
        write2 (segment.x2);
        write2 (segment.y2);
      }
    }

    
    public override bool aggregate (Request request) {
      if (!(request is Poly)) return false;
  
      Poly pr = (Poly) request;
  
      if (pr.opcode != opcode || pr.drawable != drawable || pr.gc != gc)
        return false;
  
      if (!more_aggregatep (pr)) return false;
  
      pr.items_sets.Add (items_sets[0]);
      pr.items_sets_unit_count += items_sets_unit_count;
      return true;
    }
  
  
    public virtual bool more_aggregatep (Poly pr) { return true; }
  
    
    public override void write (Stream output) 
	//throws IOException 
	{  
      write_head ();
  
      for (int j=0;j<items_sets.Count; j++) {
        Object [] items = (Object []) items_sets[j];
        for (int i=0; i<items.Length; i++) write (output, items [i]);
      }
  
      output.Write (data,0,data.Length);
    }
  
    
    public abstract void write (Stream output, Object item) 
      //throws IOException
	;
  
  
    public virtual void write_head () {
      int unit = 3 + items_sets_unit_count;
      init (drawable.display, opcode, 0, unit);
  
      write4 (drawable.id);
      write4 (gc.id);
    }
  }


  public void init (Display display, int opcode, 
    int second_field, int unit) {

    // x extensions use extended_maximum_request_length? (glx does not). if
    // not, we should check opcode here
    
    if (display.connected
      && unit > display.extended_maximum_request_length)

      throw new Exception ("Request too long (in byte): "
        + (unit*4) + " > " 
        + (display.extended_maximum_request_length*4));


    // big requests in use
    bool big = display.big_requests_present
      && unit > display.maximum_request_length;   

    if (big) unit++;            // extra storage
    length = unit * 4;
    data = new byte [length];

    write1 (opcode);
    write1 (second_field);

    if (!big)
      write2 (unit);

    else {
      write2 (0);               // extended length flag
      write4 (unit);
    }
  }


  public virtual void write (Stream output) //throws IOException 
	{
    output.Write (data, 0, length);
  }
}

}
