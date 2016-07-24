using System;
using System.IO;

using gnu.x11.xevent;

namespace gnu.x11.test {


/** 
 * Test sending synthetic events.
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/SendEvent.output">
 * text output</a>
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/SendEvent.help">
 * help output</a>
 */
public class SendEvent : Graphics {
  public SendEvent (String [] args)
    : base (args, 100, 50) {

    about ("0.1", "test sending synthetic events",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;
  }


  protected override void exec () {
    if (help_option) return;

    Console.WriteLine ("Sending a synthetic KeyPress...");
    KeyPress key_event = new KeyPress (display);
    key_event.set_window (window);
    key_event.set_detail (display.input.keysym_to_keycode ('t'));
    window.send_event (false, Event.NO_EVENT_MASK, key_event);
    
    Console.WriteLine ("Sending a synthetic ButtonPress to exit...");
    ButtonPress button_event = new ButtonPress (display);
    key_event.set_window (window);
    window.send_event (false, Event.NO_EVENT_MASK, button_event);

    while (!exit_now) {
      dispatch_event ();
      Console.WriteLine ("Received: " + evt);
    }

    display.close ();
  }

    
  public static void Main (String [] args) { 
    new SendEvent (args).exec ();
  }
}

}
