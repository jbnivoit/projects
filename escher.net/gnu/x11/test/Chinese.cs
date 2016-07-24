using System;

using gnu.x11;

namespace gnu.x11.test {


/**
 * Test text output with Chinese font. 
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Chinese.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Chinese.help">
 * help output</a>
 */
public class Chinese : Graphics {
  public GC gc;


  public Chinese (String [] args)
    : base (args, 100, 50) {

    about ("0.1", "test text output with chinese font",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;

    // check if any big5 font is present
    gnu.x11.Enum fonts = display.fonts ("-*-*-*-*-*-*-*-*-*-*-*-*-big5-*", 1);
    if (fonts.count == 0)
      throw new Exception (
        "No Chinese font defined on this X server");

    GC.Values gv = new GC.Values ();
    gv.set_background (display.default_white);
    gv.set_foreground (display.default_black);
    // just pick any of those matching fonts
    gv.set_font ((gnu.x11.Font) fonts.next ());
    gc = new GC (window, gv);
  }

  
  protected override void paint () {    
    // use `native2ascii' in jdk to get encoding (§A¦n¶Ü)
    window.image_text16 (gc, 20, 30,
      "\u00a7A\u00a6n\u00b6\u00dc");
  }


  public static void Main (String [] args) { 
    new Chinese (args).exec ();
  }
}

}
