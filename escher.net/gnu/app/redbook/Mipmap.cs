using System;

using gnu.x11.extension.glx;
using gnu.x11;

namespace gnu.app.redbook {


/**
 * Texture map with mipmaps. To overtly show the effect of mipmaps, each
 * mipmap reduction level has a solidly colored, contrasting texture image. 
 * Thus, the quadrilateral which is drawn is drawn with several different
 * colors. Modified from <code>mipmap.c</code>.
 *
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/Mipmap.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/Mipmap.help">
 * help output</a>
 */
public class Mipmap : gnu.x11.extension.glx.Application {
  private bool support_bind;
  private int texture;  

  private byte [] [] [] IMAGE32 ;
  private byte [] [] [] IMAGE16 ;
  private byte [] [] [] IMAGE8 ;
  private byte [] [] [] IMAGE4 ;
  private byte [] [] [] IMAGE2 ;
  private byte [] [] [] IMAGE1 ;
  

  public Mipmap (String [] args)
    : base (args, RESIZE_BIT) {

    about ("0.1", "mipmap texture",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;

    visual_config.set_depth_size (1);
    init_window (500, 500);
    support_bind = gl.support (1, 1) && glx.support (1, 3);

    gl.enable (GL.DEPTH_TEST);
    gl.enable (GL.TEXTURE_2D);
    gl.shade_model (GL.FLAT);
    gl.translatef (0.0f, 0.0f, -3.6f);
    gl.pixel_storei (GL.UNPACK_ALIGNMENT, 1);

    init_images ();
    init_texture ();
  }


  protected override void handle_expose () {
    gl.clear (GL.COLOR_BUFFER_BIT | GL.DEPTH_BUFFER_BIT);    
    if (support_bind) gl.bind_texture (GL.TEXTURE_2D, texture);

    gl.begin (GL.QUADS);
    gl.tex_coord2f (0.0f, 0.0f); 
    gl.vertex3f (-2.0f, -1.0f, 0.0f);
    gl.tex_coord2f (0.0f, 8.0f); 
    gl.vertex3f (-2.0f, 1.0f, 0.0f);
    gl.tex_coord2f (8.0f, 8.0f); 
    gl.vertex3f (2000.0f, 1.0f, -6000.0f);
    gl.tex_coord2f (8.0f, 0.0f); 
    gl.vertex3f (2000.0f, -1.0f, -6000.0f);
    gl.end ();

    gl.swap_buffers (window);
  }


  protected override void handle_resize (int width, int height) {
    gl.viewport (0, 0, width, height);
    gl.matrix_mode (GL.PROJECTION);
    gl.load_identity ();
    double wh = (float) width / (float) height;
    glu.perspective (60.0, wh, 1.0, 30000.0);
    gl.matrix_mode (GL.MODELVIEW);
    gl.load_identity ();
  }


  private void init_images () {

	IMAGE32 = new byte [32] [] [];
    for (int i=0; i<32; i++) {
		IMAGE32[i] = new byte[32][];
      for (int j=0; j<32; j++) {
		IMAGE32[i][j]=new byte[4];
        IMAGE32 [i] [j] [0] = (byte) 255;
        IMAGE32 [i] [j] [1] = (byte) 255;
        IMAGE32 [i] [j] [2] = (byte) 0;
        IMAGE32 [i] [j] [3] = (byte) 255;
      }
	}

	IMAGE16 = new byte [16] [] [];
    for (int i=0; i<16; i++) {
		IMAGE16[i] = new byte[16][];
      for (int j=0; j<16; j++) {
		IMAGE16[i][j]=new byte[4];
        IMAGE16 [i] [j] [0] = (byte) 255;
        IMAGE16 [i] [j] [1] = (byte) 0;
        IMAGE16 [i] [j] [2] = (byte) 255;
        IMAGE16 [i] [j] [3] = (byte) 255;
      }
	}

	IMAGE8 = new byte [8] [] [];
  	for (int i=0; i<8; i++) {
		IMAGE8[i] = new byte[8][];
      for (int j=0; j<8; j++) {
		IMAGE8[i][j]=new byte[4];
        IMAGE8 [i] [j] [0] = (byte) 255;
        IMAGE8 [i] [j] [1] = (byte) 0;
        IMAGE8 [i] [j] [2] = (byte) 0;
        IMAGE8 [i] [j] [3] = (byte) 255;
      }
	}

   IMAGE4 = new byte [4] [] [];
    for (int i=0; i<4; i++) {
	IMAGE4[i] = new byte[4][];
      for (int j=0; j<4; j++) {
		IMAGE4[i][j]=new byte[4];
        IMAGE4 [i] [j] [0] = (byte) 0;
        IMAGE4 [i] [j] [1] = (byte) 255;
        IMAGE4 [i] [j] [2] = (byte) 0;
        IMAGE4 [i] [j] [3] = (byte) 255;
      }
	}

   IMAGE2 = new byte [2] [] [];
    for (int i=0; i<2; i++) {
	IMAGE2[i] = new byte[2][];
      for (int j=0; j<2; j++) {
		IMAGE2[i][j]=new byte[4];
        IMAGE2 [i] [j] [0] = (byte) 0;
        IMAGE2 [i] [j] [1] = (byte) 0;
        IMAGE2 [i] [j] [2] = (byte) 255;
        IMAGE2 [i] [j] [3] = (byte) 255;
      }
	}

   	IMAGE1 = new byte [1] [] [];
   	IMAGE1[0] = new byte [1] [];
   	IMAGE1[0][0] = new byte [4];
    IMAGE1 [0] [0] [0] = (byte) 255;
    IMAGE1 [0] [0] [1] = (byte) 255;
    IMAGE1 [0] [0] [2] = (byte) 255;
    IMAGE1 [0] [0] [3] = (byte) 255;
  }


  private void init_texture () {
    if (support_bind) {
      texture = gl.gen_textures (1).next4 ();
      gl.bind_texture (GL.TEXTURE_2D, texture);
    }

    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_WRAP_S, GL.REPEAT);
    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_WRAP_T, GL.REPEAT);
    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_MAG_FILTER, 
      GL.NEAREST);
    gl.tex_parameteri (GL.TEXTURE_2D, GL.TEXTURE_MIN_FILTER, 
      GL.NEAREST_MIPMAP_NEAREST); // vs. `GL.NEAREST'

    gl.tex_envf (GL.TEXTURE_ENV, GL.TEXTURE_ENV_MODE, GL.DECAL);

    gl.tex_image_2d (GL.TEXTURE_2D, 0, GL.RGBA, 32, 32, 0,
      GL.RGBA, GL.UNSIGNED_BYTE, new Data (IMAGE32));
    gl.tex_image_2d (GL.TEXTURE_2D, 1, GL.RGBA, 16, 16, 0,
      GL.RGBA, GL.UNSIGNED_BYTE, new Data (IMAGE16));
    gl.tex_image_2d (GL.TEXTURE_2D, 2, GL.RGBA, 8, 8, 0,
      GL.RGBA, GL.UNSIGNED_BYTE, new Data (IMAGE8));
    gl.tex_image_2d (GL.TEXTURE_2D, 3, GL.RGBA, 4, 4, 0,
      GL.RGBA, GL.UNSIGNED_BYTE, new Data (IMAGE4));
    gl.tex_image_2d (GL.TEXTURE_2D, 4, GL.RGBA, 2, 2, 0,
      GL.RGBA, GL.UNSIGNED_BYTE, new Data (IMAGE2));
    gl.tex_image_2d (GL.TEXTURE_2D, 5, GL.RGBA, 1, 1, 0,
      GL.RGBA, GL.UNSIGNED_BYTE, new Data (IMAGE1));
  }


  public static void Main (String [] args) {
    new Mipmap (args).exec ();
  }
}
}
