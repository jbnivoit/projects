using System;

using gnu.x11.extension.glx;
using gnu.util;
using gnu.x11;

namespace gnu.app.redbook {


/**
 * Draw a surface with texture. To demonstrate how to evaluators to
 * generate a curved surface and automatically generated texture
 * coordinates. Modified from <code>texturesuf.c</code>.
 *
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/SurfaceTexture.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/SurfaceTexture.help">
 * help output</a>
 */
public class SurfaceTexture : gnu.x11.extension.glx.Application {
  private const int IMAGE_SIZE = 64;

  private byte [] [] [] IMAGE;

  private static readonly float [] [] TEXTURE_POINTS = new float[][]{ 
    new float[]{0.0f, 0.0f},
    new float[]{0.0f, 1.0f},
    new float[]{1.0f, 0.0f}, 
    new float[]{1.0f, 1.0f}
  };
    
  private static readonly float [] [] [] CONTROL_POINTS = new float[][][]{
    new float[][]{
	 new float[]{-1.5f, -1.5f, 4.0f},
     new float[]{-0.5f, -1.5f, 2.0f},
     new float[]{0.5f, -1.5f, -1.0f},
     new float[]{1.5f, -1.5f, 2.0f}},

    new float[][]{
	 new float[]{-1.5f, -0.5f, 1.0f},
     new float[]{-0.5f, -0.5f, 3.0f},
     new float[]{0.5f, -0.5f, 0.0f},
     new float[]{1.5f, -0.5f, -1.0f}},

    new float[][]{
	 new float[]{-1.5f, 0.5f, 4.0f},
     new float[]{-0.5f, 0.5f, 0.0f},
     new float[]{0.5f, 0.5f, 3.0f},
     new float[]{1.5f, 0.5f, 4.0f}}, 

    new float[][]{
	 new float[]{-1.5f, 1.5f, -2.0f},
     new float[]{-0.5f, 1.5f, -2.0f},
     new float[]{0.5f, 1.5f, 0.0f},
     new float[]{1.5f, 1.5f, -1.0f}}
  };


  public SurfaceTexture (String [] args)
    : base (args, RESIZE_BIT) {

    about ("0.1", "surface texture",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;

    visual_config.set_depth_size (1);
    init_window (500, 500);

    gl.enable (GL.DEPTH_TEST);
    gl.enable (GL.MAP2_VERTEX_3);
    gl.enable (GL.MAP2_TEXTURE_COORD_2);
    gl.enable (GL.TEXTURE_2D);
    gl.shade_model (GL.FLAT);

    gl.map2f (GL.MAP2_VERTEX_3, 0.0f, 1.0f, 3, 4, 
      0.0f, 1.0f, 12, 4, Misc.linearize (CONTROL_POINTS));
    gl.map2f (GL.MAP2_TEXTURE_COORD_2, 0.0f, 1.0f, 2, 2, 
      0.0f, 1.0f, 4, 2, Misc.linearize (TEXTURE_POINTS));
    gl.map_grid2f (20, 0.0f, 1.0f, 20, 0.0f, 1.0f);

    init_images ();
    init_texture ();
  }


  protected override void handle_expose () {
    gl.clear (GL.COLOR_BUFFER_BIT | GL.DEPTH_BUFFER_BIT);
    gl.eval_mesh2 (GL.FILL, 0, 20, 0, 20);
    gl.swap_buffers (window);
  }


  protected override void handle_resize (int width, int height) {
    gl.viewport (0, 0, width, height);
    gl.matrix_mode (GL.PROJECTION);
    gl.load_identity ();

    double wh = (float) width / (float) height;
    double hw = (float) height / (float) width;
    
    if (width <= height)
      gl.ortho (-4.0, 4.0, -4.0*hw, 4.0*hw, -4.0, 4.0);
    else
      gl.ortho (-4.0*wh, 4.0*wh, -4.0, 4.0, -4.0, 4.0);

    gl.matrix_mode (GL.MODELVIEW);
    gl.load_identity ();
    gl.rotatef (85.0f, 1.0f, 1.0f, 1.0f);
  }



  private void init_images () {
	IMAGE = new byte [IMAGE_SIZE] [][];

    for (int i=0; i<IMAGE_SIZE; i++) {
      float ti = (float) (2.0 * System.Math.PI * i / IMAGE_SIZE);
		IMAGE[i] = new byte[IMAGE_SIZE][];
      for (int j=0; j<IMAGE_SIZE; j++) {
        float tj = (float) (2.0 * System.Math.PI * j / IMAGE_SIZE);
        
		IMAGE[i][j] = new byte[3];
        IMAGE [i] [j] [0] = (byte) (127 * (1.0 + System.Math.Sin (ti)));
        IMAGE [i] [j] [1] = (byte) (127 * (1.0 + System.Math.Cos (2 * tj)));
        IMAGE [i] [j] [2] = (byte) (127 * (1.0 + System.Math.Cos (ti + tj)));
      }
    }
  }


  private void init_texture () {
    gl.tex_envf (GL.TEXTURE_ENV, GL.TEXTURE_ENV_MODE, GL.DECAL);

    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_WRAP_S, GL.REPEAT);
    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_WRAP_T, GL.REPEAT);
    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_MAG_FILTER, 
      GL.NEAREST);
    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_MIN_FILTER, 
      GL.NEAREST);

    gl.tex_image_2d (GL.TEXTURE_2D, 0, GL.RGB, IMAGE_SIZE, IMAGE_SIZE, 
      0, GL.RGB, GL.UNSIGNED_BYTE, new gnu.x11.Data (IMAGE));
  }


  public static void Main (String [] args) {
    new SurfaceTexture (args).exec ();
  }
}
}
