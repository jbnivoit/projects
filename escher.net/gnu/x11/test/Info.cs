using System;

using gnu.util;
using gnu.x11;
using gnu.x11.extension;
using gnu.x11.extension.render;
using gnu.x11.extension.glx;

namespace gnu.x11.test {


/** 
 * List info about X server. 
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Info.output">
 * text output on linux + xfree86 4.0</a>
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Info.output.solaris">
 * text output on solaris + x11</a>
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Info.output.windows">
 * text output on window 98 + winpro</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Chinese.help">
 * help output</a>
 */
public class Info : gnu.x11.Application {
  public Info (String [] args)
    : base (args) {

    bool print_keysyms = option.booleann ("print-keysyms",
      "print all keysyms for debug", false);

    about ("0.1", "list info about X server",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;

    Console.WriteLine ("\n\n---- display\n" + display);

    Console.WriteLine ("\n\n---- extension"
      + display.extensions ().to_string (Enum.NEXT_STRING));    

    extension_details ();

    Console.WriteLine ("\n\n---- keyboard control\n"
      + display.input.keyboard_control ());
    
    Console.WriteLine ("\n\n---- pointer control\n"
      + display.input.pointer_control ());
    
    Console.WriteLine ("\n\n---- screen saver\n"
      + display.screen_saver ());
    
    Console.WriteLine ("\n\n---- font path"
      + display.font_path ().to_string (Enum.NEXT_STRING));

    Console.WriteLine ("\n\n---- first 20 fonts"
      + display.fonts ("*", 20).to_string (Enum.NEXT_STRING));

    Console.WriteLine ("\n\n---- children of root"
      + display.default_root.tree ().children ()
      .to_string (Enum.NEXT4));

    Console.WriteLine ("\n\n---- properties of root"
      + display.default_root.properties ().to_string (Enum.NEXT));

    Console.WriteLine ("\n\n---- screens"
      + Misc.to_string (display.screens));

    Console.WriteLine ("\n\n---- pixmap formats"
      + Misc.to_string (display.pixmap_formats));


    Console.WriteLine ("\n\n---- keyboard symbols");
    Console.WriteLine ("  min-keycode: " + display.input.min_keycode);
    Console.WriteLine ("  max-keycode: " + display.input.max_keycode);
    Console.WriteLine ("  keycode-count: "
      + (display.input.max_keycode - display.input.min_keycode + 1));
    Console.WriteLine ("  keysyms-per-keycode: : " 
      + display.input.keysyms_per_keycode);

    // compare to "xmodmap -pk"
    if (print_keysyms) {
      Console.WriteLine ("  ** keysyms **");
      for (int i=0; i<display.input.keysyms.Length; i++)
        Console.WriteLine (i+display.input.min_keycode + ": " 
          + display.input.keysyms [i]);
    }
  }


  public void extension_details () {
    Console.WriteLine ("\n\n---- extension details");

    try {
      Console.WriteLine (new gnu.x11.extension.
      BigRequests (display) + "\n");
    } catch (NotFoundException e) {
      Console.WriteLine ("big requests not found\n");
    }

    try {
      Console.WriteLine (new gnu.x11.extension.DBE (display) + "\n");
    } catch (NotFoundException e) {
      Console.WriteLine ("dbe not found\n");
    }

    try {
      Console.WriteLine (new gnu.x11.extension.DPMS (display) + "\n");
    } catch (NotFoundException e) {
      Console.WriteLine ("dpms not found\n");
    }

    try {
      Console.WriteLine (new gnu.x11.extension.EVI (display) + "\n");
    } catch (NotFoundException e) {
      Console.WriteLine ("evi not found\n");
    }

    try {
      GLX glx = new GLX (display);
      Console.WriteLine (glx + Misc.to_string (glx.visual_configs (0)));

      GL gl = glx.create_context (display.default_screen.root_visual_id (),
        display.default_screen_no, GL.NONE0);
      gl.make_current (display.default_root);
      Console.WriteLine (gl + "\n");

    } catch (NotFoundException e) {
      Console.WriteLine ("glx not found\n");
    }

    try {
      Render render = new Render (display);
      Console.WriteLine (render 
        + Misc.to_string (render.picture_formats ()));
    } catch (NotFoundException e) {
      Console.WriteLine ("render not found\n");
    }

    try {
      Console.WriteLine (new gnu.x11.extension.Shape (display) + "\n");
    } catch (NotFoundException e) {
      Console.WriteLine ("shape not found\n");
    }

    try {
      Console.WriteLine (new gnu.x11.extension.XCMisc (display) + "\n");
    } catch (NotFoundException e) {
      Console.WriteLine ("xcmic not found\n");
    }

    try {
      Console.WriteLine (new gnu.x11.extension.XTest (display) + "\n");
    } catch (NotFoundException e) {
      Console.WriteLine ("xtest not found\n");
    }
  }


  public static void Main (String [] args) { 
    new Info (args);
  }
}

}
