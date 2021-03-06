using System;
using gnu.x11;
using gnu.x11.xevent;

namespace gnu.x11.extension {


/** 
 * Nonrectangular Window Extension. The specification can be found <a href= 
 * "http://escher.sourceforge.net/etc/specification/shape-library.ps.gz"
 * >here</a> (<a href=
 * "http://escher.sourceforge.net/etc/specification/shape-protocol.ps.gz"
 * >protocol</a>).
 */
public class Shape : Extension, EventFactory {
  public static readonly String [] MINOR_OPCODE_STRINGS = {
    "QueryVersion",             // 0
    "Rectangles",               // 1
    "Mask",                     // 2
    "Combine",                  // 3
    "Offset",                   // 4
    "QueryExtents",             // 5
    "SelectInput",              // 6
    "InputSelected",            // 7
    "GetRectangles"             // 8
  };
    

  public const int CLIENT_MAJOR_VERSION = 1;
  public const int CLIENT_MINOR_VERSION = 0;


  public int server_major_version, server_minor_version;


  // shape opcode 0 - query version
  /**
   * @see <a href="XShapeQueryExtension.html">XShapeQueryExtension</a>
   */
  public Shape (Display display) //throws NotFoundException { 
    :base (display, "SHAPE", MINOR_OPCODE_STRINGS, 0, 1) {

    // check version before any other operations
    Request request = new Request (display, major_opcode, 0, 1);
    Data reply = display.read_reply (request);
    server_major_version = reply.read2 (8);
    server_minor_version = reply.read2 (10);
  }


  public const int BOUNDING = 0;
  public const int CLIP = 1;


  public const int SET = 0;
  public const int UNION = 1;
  public const int INTERSECT = 2;
  public const int SUBTRACT = 3;
  public const int INVERT = 4;


  public const int UN_SORTED = 0;
  public const int Y_SORTED = 1;
  public const int YX_SORTED = 2;
  public const int YX_BANDED = 3;


  // shape opcode 1 - rectangles
  /**
   * @param dest_kind valid:
   * {@link #BOUNDING},
   * {@link #CLIP}
   * 
   * @param operation valid:
   * {@link #SET},
   * {@link #UNION},
   * {@link #INTERSECT},
   * {@link #SUBTRACT},
   * {@link #INVERT}
   * 
   * @param ordering valid: 
   * {@link #UN_SORTED},
   * {@link #Y_SORTED},
   * {@link #YX_SORTED},
   * {@link #YX_BANDED}
   * 
   * @see <a href="XShapeCombineRectangles.html">XShapeCombineRectangles</a>
   */
  public void combine_rectangles (Window dest, int dest_kind, int x_offset,
    int y_offset, Rectangle [] rectangles, int operation, int ordering) {

    Request request = new Request (display, major_opcode, 1,
      4+2*rectangles.Length); 
    request.write1 (operation);
    request.write1 (dest_kind);
    request.write1 (ordering);
    request.write1_unused ();
    request.write4 (dest.id);
    request.write2 (x_offset);
    request.write2 (y_offset);

    for (int i=0; i<rectangles.Length; i++) {
      request.write2 (rectangles [i].x);
      request.write2 (rectangles [i].y);
      request.write2 (rectangles [i].width);
      request.write2 (rectangles [i].height);
    }

    display.send_request (request);
  }


  // shape opcode 2 - mask
  /**
   * @param dest_kind valid:
   * {@link #BOUNDING},
   * {@link #CLIP}
   * 
   * @param operation valid:
   * {@link #SET},
   * {@link #UNION},
   * {@link #INTERSECT},
   * {@link #SUBTRACT},
   * {@link #INVERT}
   * 
   * @param src possible: {@link gnu.x11.Pixmap#NONE}
   * @see <a href="XShapeCombineMask.html">XShapeCombineMask</a>
   */
  public void combine_mask (Window dest, int dest_kind, int x_offset, 
    int y_offset, Pixmap src, int operation) { 

    Request request = new Request (display, major_opcode, 2, 5);
    request.write1 (operation);
    request.write1 (dest_kind);
    request.write2_unused ();
    request.write4 (dest.id);
    request.write2 (x_offset);
    request.write2 (y_offset);
    request.write4 (src.id);
    display.send_request (request);
  }


  // shape opcode 3 - combine
  /**
   * @param dest_kind valid:
   * {@link #BOUNDING},
   * {@link #CLIP}
   * 
   * @param src_kind valid: 
   * {@link #BOUNDING},
   * {@link #CLIP}
   * 
   * @param operation valid:
   * {@link #SET},
   * {@link #UNION},
   * {@link #INTERSECT},
   * {@link #SUBTRACT},
   * {@link #INVERT}
   * 
   * @see <a href="XShapeCombineShape.html">XShapeCombineShape</a>
   */
  public void combine_shape (Window dest, int dest_kind, int x_offset,
    int y_offset, Window src, int src_kind, int operation) { 

    Request request = new Request (display, major_opcode, 3, 5);
    request.write1 (operation);
    request.write1 (dest_kind);
    request.write1 (src_kind);
    request.write1_unused ();
    request.write4 (dest.id);
    request.write2 (x_offset);
    request.write2 (y_offset);
    request.write4 (src.id);
    display.send_request (request);
  }


  // shape opcode 4 - offset
  /**
   * @see <a href="XShapeOffsetShape.html">XShapeOffsetShape</a>
   */
  public void offset_shape (Window dest, int dest_kind,
    int x_offset, int y_offset) {

    Request request = new Request (display, major_opcode, 4, 4);
    request.write1 (dest_kind);
    request.write3_unused ();
    request.write4 (dest.id);
    request.write2 (x_offset);
    request.write2 (y_offset);    
    display.send_request (request);
  }


  /** Reply of {@link #extents(Window)} */
  public /*static*/ class ExtentsReply : Data {
    public ExtentsReply (Data data) : base (data) {}
    public bool bounding_shaped () { return read_bool (8); }
    public bool clip_shaped () { return read_bool (9); }
    public int bounding_x () { return read2 (12); }
    public int bounding_y () { return read2 (14); }
    public int bounding_width () { return read2 (16); }
    public int bounding_height () { return read2 (18); }
    public int clip_x () { return read2 (20); }
    public int clip_y () { return read2 (22); }
    public int clip_width () { return read2 (24); }
    public int clip_height () { return read2 (26); }
  
  
    public Rectangle bounding () { 
      return new Rectangle (
        bounding_x (), bounding_y (),
        bounding_width (), bounding_height ());
    }
        
  
    public Rectangle clip () { 
      return new Rectangle (
        clip_x (), clip_y (),
        clip_width (), clip_height ());
    }
        
  
    public override String ToString () {
      String output = "#Extents ";
  
      if (bounding_shaped ()) output += "Bounding: " + bounding ();
      if (clip_shaped ()) output += "Clip: " + clip ();
  
      return output;
    }
  }
  
  
  // shape opcode 5 - query extents
  /**
   * @see <a href="XShapeQueryExtents.html">XShapeQueryExtents</a>
   */
  public ExtentsReply extents (Window dest) {
    Request request = new Request (display, major_opcode, 5, 2);
    request.write4 (dest.id);
    return new ExtentsReply (display.read_reply (request));
  }


  // shape opcode 6 - select input
  /**
   * @see <a href="XShapeSelectInput.html">XShapeSelectInput</a>
   */
  public void select_input (Window dest, bool enable) {
    Request request = new Request (display, major_opcode, 6, 3);
    request.write4 (dest.id);
    request.write1 (enable);
    display.send_request (request);    
  }


  // shape opcode 7 - input selected
  /**
   * @see <a href="XShapeInputSelected.html">XShapeInputSelected</a>
   */
  public bool input_selected (Window dest) {
    Request request = new Request (display, major_opcode, 7, 2);
    request.write4 (dest.id);
    return display.read_reply (request).read_bool (1);
  }

  
  /** Reply of {@link #rectangles()} */
  public /*static*/ class RectanglesReply : Data {
    public RectanglesReply (Data data) : base (data) {}
  
  
    /**
     * @return valid:
     * {@link #UN_SORTED},
     * {@link #Y_SORTED},
     * {@link #YX_SORTED},
     * {@link #YX_BANDED}
     */
    public int ordering () { return read1 (1); }
    public int rectangle_count () { return read4 (8); }
  
  
    /**
     * @return valid: {@link Enum#next()} of type {@link Rectangle}
     */
	private /*static*/ class RectanglesEnum : Enum
 {
	public RectanglesEnum(RectanglesReply owner, int len, int c) : base(owner,len,c) {}
        public override Object next () {
          int x = this.read2 (0);
          int y = this.read2 (2);
          int width = this.read2 (4);
          int height = this.read2 (6);
          Rectangle rectangle = new Rectangle (x, y, width, height);
  
          inc (8);
          return rectangle;
        }
      }

    public Enum rectangles () {
      return new RectanglesEnum (this, 32, rectangle_count ());
    }
  }
  
  
  // shape opcode 8 - get rectangles
  /**
   * @see <a href="XShapeGetRectangles.html">XShapeGetRectangles</a>
   */
  public RectanglesReply rectangles (Window window, int kind) {
    Request request = new Request (display, major_opcode, 8, 3);
    request.write4 (window.id);
    request.write1 (kind);
    return new RectanglesReply (display.read_reply (request));
  }


  /** SHAPE notify event. */
  public /*static*/ class NotifyEvent : Event {
    public new const int code = 0;


    public NotifyEvent (Display display, byte [] data) 
      :base (display, data, 4) {
    }


    public int x () { return read2 (8); }
    public int y () { return read2 (10); }
    public int width () { return read2 (12); }
    public int height () { return read2 (14); }
    public override int time () { return read4 (16); }
    public bool shaped () { return read_bool (20); }


    /**
     * @return valid:
     * {@link #BOUNDING},
     * {@link #CLIP}
     */
    public int kind () { return read1 (1); }


    public Rectangle rectangle () {
      return new Rectangle (x (), y (), width (), height ());
    }
  }


  public Event build (Display display, byte [] data, int code) {
    // only one extension event
    return new NotifyEvent (display, data);
  }


  public override String more_string () {
    return "\n  client-version: " 
      + CLIENT_MAJOR_VERSION + "." + CLIENT_MINOR_VERSION
      + "\n  server-version: "
      + server_major_version + "." + server_minor_version;
  }
}

}
