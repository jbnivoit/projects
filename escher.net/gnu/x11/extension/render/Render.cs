using System;
using gnu.x11;

namespace gnu.x11.extension.render {


/**
 * X Rendering Extension.
 *
 * <p>This extension is still under active development. Please check its <a
 * href="http://www.xfree86.org/~keithp/render/protocol.html">homepage</a>.
 * The implemented version is XRender 0.0.14.
 */
public class Render : gnu.x11.extension.Extension, gnu.x11.extension.ErrorFactory {

  public static readonly String [] MINOR_OPCODE_STRINGS = {
    "QueryVersion",             // 0
    "QueryPictFormats",         // 1
    "QueryPictIndexValues",     // 2
    "QueryDithers",             // 3
    "CreatePicture",            // 4
    "ChangePicture",            // 5
    "SetPictureClipRectangles", // 6
    "FreePicture",              // 7
    "Composite",                // 8
    "Scale",                    // 9
    "Trapezoids",               // 10
    "Triangles",                // 11
    "TriStrip",                 // 12
    "TriFan",                   // 13
    "ColorTrapezoids",          // 14
    "ColorTriangles",           // 15
    "Transform",                // 16
    "CreateGlyphSet",           // 17
    "ReferenceGlyphSet",        // 18
    "FreeGlyphSet",             // 19
    "AddGlyphs",                // 20
    "AddGlyphsFromPicture",     // 21
    "FreeGlyphs",               // 22
    "CompositeGlyphs8",         // 23
    "CompositeGlyphs16",        // 24
    "CompositeGlyphs32",        // 25
    "FillRectangles"            // 26
  };


  public const int CLIENT_MAJOR_VERSION = 0;
  public const int CLIENT_MINOR_VERSION = 1;


  public int server_major_version, server_minor_version;


  private Picture.Format [] picture_formats_cache;


  // render opcode 0 - query version
  public Render (Display display) 
    //throws gnu.x11.extension.NotFoundException 

    :base (display, "RENDER", MINOR_OPCODE_STRINGS, 5, 0) {

    // check version before any other operations
    Request request = new Request (display, major_opcode, 0, 3);
    request.write4 (CLIENT_MAJOR_VERSION);
    request.write4 (CLIENT_MINOR_VERSION);    

    Data reply = display.read_reply (request);
    server_major_version = reply.read4 (8);
    server_minor_version = reply.read4 (12);    
  }


  // render opcode 1 - query picture formats
  public Picture.Format [] picture_formats () {
    if (picture_formats_cache != null)
      return picture_formats_cache;

    Request request = new Request (display, major_opcode, 1, 1);
    Data reply = display.read_reply (request);
    int count = reply.read4 (8);

    Picture.Format [] pfs = new Picture.Format [count];
    for (int i=0, offset=32; i<count; i++) {
      pfs [i] = new Picture.Format (reply, offset);
      offset += Picture.Format.LENGTH;
    }

    picture_formats_cache = pfs;
    return pfs;
  }


  // render opcode 2 - query picture index values
  public void picture_index_values () {
    Request request = new Request (display, major_opcode, 2, 2);
    display.send_request (request);
  }


  // render opcode 3 - query dithers
  public void dithers (Drawable drawable) {
    Request request = new Request (display, major_opcode, 3, 2);
    request.write4 (drawable.id);
    display.send_request (request);
  }

  
  public const int CLEAR = 0;
  public const int SRC = 1;
  public const int DST = 2;
  public const int OVER = 3;
  public const int OVER_REVERSE = 4;
  public const int IN = 5;
  public const int IN_REVERSE = 6;
  public const int OUT = 7;
  public const int OUT_REVERSE = 8;
  public const int ATOP = 9;
  public const int ATOP_REVERSE = 10;
  public const int XOR = 11;
  public const int ADD = 12;
  public const int SATURATE = 13;
  public const int MAXIMUM = 14;



  // render opcode 8 - composite
  /**
   * @param operation
   * {@link #CLEAR}
   * {@link #SRC}
   * {@link #DST}
   * {@link #OVER}
   * {@link #OVER_REVERSE}
   * {@link #IN}
   * {@link #IN_REVERSE}
   * {@link #OUT}
   * {@link #OUT_REVERSE}
   * {@link #ATOP}
   * {@link #ATOP_REVERSE}
   * {@link #XOR}
   * {@link #ADD}
   * {@link #SATURATE}
   * {@link #MAXIMUM}
   * 
   * @see <a href="XRenderComposite.html">XRenderComposite</a>
   */
  public void composite (int op, Picture src, Picture mask, Picture dst, 
    int src_x, int src_y, int mask_x, int mask_y, int dst_x, int dst_y, 
    int width, int height) {

    Request request = new Request (display, major_opcode, 8, 9);
    request.write1 (op);
    request.write3_unused ();
    request.write4 (src.id);
    request.write4 (mask.id);
    request.write4 (dst.id);
    request.write2 (src_x);
    request.write2 (src_y);
    request.write2 (mask_x);
    request.write2 (mask_y);
    request.write2 (dst_x);
    request.write2 (dst_y);
    request.write2 (width);
    request.write2 (height);
    display.send_request (request);
  }
    

  public const int BAD_PICTURE_FORMAt = 0;
  public const int BAD_PICTURE = 1;
  public const int BAD_PICTURE_OPERATIOR = 2;
  public const int BAD_GLYPH_SET = 3;
  public const int BAD_GLYPH = 4;


  public static readonly String [] ERROR_STRINGS = {
    "BAD_RENDER_PICTURE_FORMAT: parameter not a RENDER picture format",
    "BAD_RENDER_PICTURE: parameter not a RENDER picture",
    "BAD_RENDER_PICTURE_OPERATOR: parameter not a RENDER picture operator",
    "BAD_RENDER_GLYPH_SET: parameter not a RENDER glyph set",
    "BAD_RENDER_GLYPH: parameter not a RENDER glyph",
  };


  public Error build (Display display, Data data, int code,
    int seq_no, int bad, int minor_opcode, int major_opcode) {

    String error_string = ERROR_STRINGS [code - first_error];
    return new Error (display, error_string, code, seq_no, bad, 
      minor_opcode, major_opcode);
  }


  /**
   * @see Picture#Picture(Render, Drawable, Picture.Format, Picture.Attributes)
   */  
  public Picture create_picture (Drawable drawable, Picture.Format format,
    Picture.Attributes attr) {
    
    return new Picture (this, drawable, format, attr);
  }

  
  /**
   * @see <a href="XRenderFindFormat.html">XRenderFindFormat</a>
   */
  public Picture.Format picture_format (Picture.Format template, 
    bool must) {

    Picture.Format [] pfs = picture_formats ();
    for (int i=0; i<pfs.Length; i++)
      if (pfs [i].match (template)) return pfs [i];
      
    if (!must) return null;
    throw new Error ("No matching: " + template);
  }


  public override String more_string () {
    return "\n  client-version: " 
      + CLIENT_MAJOR_VERSION + "." + CLIENT_MINOR_VERSION
      + "\n  server-version: "
      + server_major_version + "." + server_minor_version;
  }
}

}
