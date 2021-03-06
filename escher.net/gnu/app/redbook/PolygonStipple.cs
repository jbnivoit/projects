using System;

using gnu.x11.extension.glx;

namespace gnu.app.redbook {


/**
 * Do polygon stipple. Modified from <code>polys.c</code>.
 *
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/PolygonStipple.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/PolygonStipple.help">
 * help output</a>
 */
public class PolygonStipple : gnu.x11.extension.glx.Application {
  private static readonly byte [] FLY = new byte[]{
    (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00, 
    (byte) 0x00, (byte) 0x00, (byte) 0x00, (byte) 0x00,
    (byte) 0x03, (byte) 0x80, (byte) 0x01, (byte) 0xc0,
    (byte) 0x06, (byte) 0xc0, (byte) 0x03, (byte) 0x60, 
    (byte) 0x04, (byte) 0x60, (byte) 0x06, (byte) 0x20,
    (byte) 0x04, (byte) 0x30, (byte) 0x0c, (byte) 0x20, 
    (byte) 0x04, (byte) 0x18, (byte) 0x18, (byte) 0x20,
    (byte) 0x04, (byte) 0x0c, (byte) 0x30, (byte) 0x20,
    (byte) 0x04, (byte) 0x06, (byte) 0x60, (byte) 0x20,
    (byte) 0x44, (byte) 0x03, (byte) 0xc0, (byte) 0x22, 
    (byte) 0x44, (byte) 0x01, (byte) 0x80, (byte) 0x22,
    (byte) 0x44, (byte) 0x01, (byte) 0x80, (byte) 0x22, 
    (byte) 0x44, (byte) 0x01, (byte) 0x80, (byte) 0x22,
    (byte) 0x44, (byte) 0x01, (byte) 0x80, (byte) 0x22,
    (byte) 0x44, (byte) 0x01, (byte) 0x80, (byte) 0x22,
    (byte) 0x44, (byte) 0x01, (byte) 0x80, (byte) 0x22, 
    (byte) 0x66, (byte) 0x01, (byte) 0x80, (byte) 0x66,
    (byte) 0x33, (byte) 0x01, (byte) 0x80, (byte) 0xcc, 
    (byte) 0x19, (byte) 0x81, (byte) 0x81, (byte) 0x98,
    (byte) 0x0c, (byte) 0xc1, (byte) 0x83, (byte) 0x30,
    (byte) 0x07, (byte) 0xe1, (byte) 0x87, (byte) 0xe0,
    (byte) 0x03, (byte) 0x3f, (byte) 0xfc, (byte) 0xc0, 
    (byte) 0x03, (byte) 0x31, (byte) 0x8c, (byte) 0xc0,
    (byte) 0x03, (byte) 0x33, (byte) 0xcc, (byte) 0xc0, 
    (byte) 0x06, (byte) 0x64, (byte) 0x26, (byte) 0x60,
    (byte) 0x0c, (byte) 0xcc, (byte) 0x33, (byte) 0x30,
    (byte) 0x18, (byte) 0xcc, (byte) 0x33, (byte) 0x18,
    (byte) 0x10, (byte) 0xc4, (byte) 0x23, (byte) 0x08, 
    (byte) 0x10, (byte) 0x63, (byte) 0xc6, (byte) 0x08,
    (byte) 0x10, (byte) 0x30, (byte) 0x0c, (byte) 0x08, 
    (byte) 0x10, (byte) 0x18, (byte) 0x18, (byte) 0x08,
    (byte) 0x10, (byte) 0x00, (byte) 0x00, (byte) 0x08
  };

  
  private static readonly byte [] HALFTONE = new byte[]{
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55,
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55,
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55,
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55,
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55,
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55, 
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55,
    (byte) 0xaa, (byte) 0xaa, (byte) 0xaa, (byte) 0xaa,
    (byte) 0x55, (byte) 0x55, (byte) 0x55, (byte) 0x55
  };

  
  public PolygonStipple (String [] args)
    : base (args, RESIZE_BIT) {

    about ("0.1", "polygon stipple",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;
    init_window (350, 150);

    gl.shade_model (GL.FLAT);
  }


  protected override void handle_expose () {
    gl.clear (GL.COLOR_BUFFER_BIT);

    gl.rectf (25.0f, 25.0f, 125.0f, 125.0f);
    gl.enable (GL.POLYGON_STIPPLE);
    gl.polygon_stipple (FLY);
    gl.rectf (125.0f, 25.0f, 225.0f, 125.0f);
    gl.polygon_stipple (HALFTONE);
    gl.rectf (225.0f, 25.0f, 325.0f, 125.0f);
    gl.disable (GL.POLYGON_STIPPLE);

    gl.swap_buffers (window);
  }


  protected override void handle_resize (int width, int height) {
    gl.viewport (0, 0, width, height);
    gl.matrix_mode (GL.PROJECTION);
    gl.load_identity ();
    glu.ortho_2d (0.0, width, 0.0, height);
  }


  public static void Main (String [] args) {
    new PolygonStipple (args).exec ();
  }
}
}
