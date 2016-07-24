using System;

using gnu.x11;
using gnu.x11.extension;

namespace gnu.x11.test {


/**
 * Test internal workings of <code>gnu.x11</code>. 
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Internal.output">
 * text output</a>
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Internal.help">
 * help output</a>
 */
public class Internal : gnu.x11.Application {
  public Internal (String [] args)
    : base (args) {

    about ("0.1", "test internal workings of the library",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;

    // xc-misc, overflow it first
    display.resource_index = unchecked((int)0xfffffff0);
    new Cursor (display, 0);
    Console.WriteLine ("xc-misc allocation test passed");


    // keyboard mapping
    int keycode = display.input.keysym_to_keycode (gnu.x11.keysym.Misc.DELETE);
    Console.WriteLine ("keycode for DELETE: " + keycode);
    int keysym = display.input.keycode_to_keysym (keycode, 0);
    Console.WriteLine ("keysym for " + keycode + ": " + keysym);
    if (keysym != gnu.x11.keysym.Misc.DELETE) throw new gnu.x11.Error ("");
    if (display.input.keysyms_per_keycode != 2)
      Console.WriteLine ("WARNING: keysyms-per-keycode > 2: "
        + display.input.keysyms_per_keycode);
  }


  public static void Main (String [] args) { 
    new Internal (args);
  }
}

}
