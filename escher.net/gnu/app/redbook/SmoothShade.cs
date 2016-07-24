using System;

using gnu.x11.extension.glx;

namespace gnu.app.redbook {


/**
 * Draw a smooth shaded polygon in a 2D projection. Modified from
 * <code>smooth.c</code>.
 *
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/SmoothShade.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/SmoothShade.help">
 * help output</a>
 */
public class SmoothShade : gnu.x11.extension.glx.Application {
  public SmoothShade (String [] args)
    : base (args, RESIZE_BIT) {

    about ("0.1", "smooth shade",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;
    init_window (500, 500);
  }


  protected override void handle_expose () {
    gl.clear (GL.COLOR_BUFFER_BIT);

    gl.begin (GL.TRIANGLES);
    gl.color3f (1.0f, 0.0f, 0.0f);
    gl.vertex2f (5.0f, 5.0f);
    gl.color3f (0.0f, 1.0f, 0.0f);
    gl.vertex2f (25.0f, 5.0f);
    gl.color3f (0.0f, 0.0f, 1.0f);
    gl.vertex2f (5.0f, 25.0f);
    gl.end ();

    gl.swap_buffers (window);
  }


  protected override void handle_resize (int width, int height) {
    gl.viewport (0, 0, width, height);
    gl.matrix_mode (GL.PROJECTION);
    gl.load_identity ();

    double wh = (float) width / (float) height;
    double hw = (float) height / (float) width;
    
    if (width <= height)
      glu.ortho_2d (0.0, 30.0, 0.0, 30.0*hw);
    else
      glu.ortho_2d (0.0, 30.0*wh, 0.0, 30.0);

    gl.matrix_mode (GL.MODELVIEW);
  }


  public static void Main (String [] args) {
    new SmoothShade (args).exec ();
  }
}
}
