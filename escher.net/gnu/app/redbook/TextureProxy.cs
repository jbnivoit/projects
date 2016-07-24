using System;

using gnu.x11.extension.glx;

namespace gnu.app.redbook {


/**
 * Test texture proxy. It prints out some messages about whether certain
 * size textures are supported and then exits. Modified from <code>texprox.c</code>.
 *
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/TextureProxy.output">
 * text output</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/TextureProxy.help">
 * help output</a>
 */
public class TextureProxy : gnu.x11.extension.glx.Application {

  public TextureProxy (String [] args)
    : base (args, RESIZE_BIT) {

    about ("0.1", "texture binding",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;
    init_window (500, 500);

    if (!gl.support (1, 1) || !glx.support (1, 3))
      throw new gnu.x11.Error ("Texture binding unsupported");
    test_texture ();
  }


  protected override void handle_expose () {
    exit ();
  }


  protected override void handle_resize (int width, int height) {
    gl.viewport (0, 0, width, height);
    gl.matrix_mode (GL.PROJECTION);
    gl.load_identity ();
  }


  private static readonly String [] STRINGS = {
    "failed!", "succeeded!"};


  private void test_texture () {
    int proxy_components;

    gl.tex_image_2d (GL.PROXY_TEXTURE_2D, 0, GL.RGBA8, 64, 64, 0, GL.RGBA, 
      GL.UNSIGNED_BYTE, null);
    proxy_components = gl.tex_level_parameteriv (GL.PROXY_TEXTURE_2D,
      0, GL.TEXTURE_INTERNAL_FORMAT).next4 ();
    Console.WriteLine (
      "Proxying 64x64 level 0 RGBA8 texture... "
      + STRINGS [proxy_components == GL.RGBA8 ? 1 : 0]);

    gl.tex_image_2d (GL.PROXY_TEXTURE_2D, 0, GL.RGBA16, 2048, 2048, 0, GL.RGBA, 
      GL.UNSIGNED_BYTE, null);
    proxy_components = gl.tex_level_parameteriv (GL.PROXY_TEXTURE_2D,
      0, GL.TEXTURE_INTERNAL_FORMAT).next4 ();
    Console.WriteLine (
      "Proxying 2048x2048 level 0 RGBA16 texture... "
      + STRINGS [proxy_components == GL.RGBA8 ? 1 : 0]);   
  }


  public static void Main (String [] args) {
    new TextureProxy (args).exec ();
  }
}
}
