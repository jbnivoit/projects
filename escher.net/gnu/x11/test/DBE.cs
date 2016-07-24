using System;

namespace gnu.x11.test {


/**
 * Test Double Buffer Extension. 
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/DBE.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/DBE.output">
 * text output</a>
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/DBE.help">
 * help output</a>
 */
public class DBE : Graphics {
  public gnu.x11.extension.DBE.BackBuffer back_buffer;
  public gnu.x11.extension.DBE dbe;
  public static readonly Random random = new Random ();


  public DBE (String [] args) //throws gnu.x11.extension.NotFoundException {
    : base (args, 256, 256) {
    
    about ("0.1", "test double buffer extension",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;

    dbe = new gnu.x11.extension.DBE (display);

    // server bug
    //Console.WriteLine (dbe.visual_info (gnu.x11.extension.DBE.EMPTY)
    //  .ToString (Enum.NEXT, "\n"));    

    // test allocation and deallocation
    back_buffer = dbe.allocate (window, gnu.x11.extension.DBE.UNDEFINED);
    back_buffer.deallocate ();

    // test extension error
    try {
      back_buffer = dbe.allocate (window, gnu.x11.extension.DBE.UNDEFINED);
      back_buffer.id = 666;
      back_buffer.deallocate ();
      display.check_error ();

    } catch (Error e) {
      Console.WriteLine ("Forced error for testing: " + e);
    }

    // test get back buffer attributes
    back_buffer = dbe.allocate (window, gnu.x11.extension.DBE.UNDEFINED);
    Console.WriteLine ("back buffer attributes: " 
      + back_buffer.attributes ());
  }


  protected override void paint () {   
    for (int i=0; i<10; i++) {
      back_buffer.line (display.default_gc, 
        random.Next (back_buffer.width), 
        random.Next (back_buffer.height),
        random.Next (back_buffer.width), 
        random.Next (back_buffer.height));
    }

    back_buffer.swap (gnu.x11.extension.DBE.UNDEFINED);
  }


  public static void Main (String [] args) { 
    new DBE (args).exec ();
  }
}

}
