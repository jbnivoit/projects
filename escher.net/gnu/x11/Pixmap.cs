using System;
namespace gnu.x11 {


/** X pixmap. */
public class Pixmap : Drawable {
  /** 
   * Predefined pixmap.
   *
   * @see Window#NONE
   */
  public static readonly Pixmap NONE = new Pixmap (0);
  public static readonly Pixmap COPY_FROM_PARENT = NONE;
  public static readonly Pixmap PARENT_RELATIVE = new Pixmap (1);


  /** Predefined. */
  public Pixmap (int id) : base (id) {
  }


  /** X pixmap format. */
  public /*static*/ class Format : Data {
    public Format (Data data, int offset) : base (data, offset) { }
    public int depth () { return read1 (0); }
    public int bits_per_pixel () { return read1 (1); }
    public int scanline_pad () { return read1 (2); }
  
  
    public override String ToString () {
      return "#Pixmap.Format"
        + "\n  depth: " + depth ()
        + "\n  bits-per-pixel: " + bits_per_pixel ()
        + "\n  scanline-pad: " + scanline_pad ();
    }
  }


  // opcode 53 - create pixmap
  /** 
   * @see <a href="XCreatePixmap.html">XCreatePixmap</a>
   */
  public Pixmap (Drawable drawable, int width, int height, int depth) 
    :base (drawable.display) {
    this.width = width;
    this.height = height;

    Request request = new Request (display, 53, depth, 4);
    request.write4 (id);
    request.write4 (drawable.id);
    request.write2 (width);
    request.write2 (height);
    display.send_request (request);
  }


  /**
   * @see #Pixmap(Drawable, int, int, int)
   */
  public Pixmap (Display display, int width, int height)
    : this (display.default_root, width, height, display.default_depth) {}


  /**
   * @see #Pixmap(Drawable, int, int, int)
   */
  public Pixmap (Drawable drawable, int depth)
    : this (drawable, drawable.width, drawable.height, depth) {}


  /**
   * @see #Pixmap(Drawable, int)
   */
  public Pixmap (Drawable drawable) : this (drawable, drawable.display.default_depth) {}

  // opcode 54 - free pixmap
  /**
   * @see <a href="XFreePixmap.html">XFreePixmap</a>
   */
  public void free () {
    Request request = new Request (display, 54, 2);
    request.write4 (id);
    display.send_request (request);
  }
}

}
