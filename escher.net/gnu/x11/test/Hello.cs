using System;

using gnu.x11;
using gnu.x11.xevent;

namespace gnu.x11.test {


/** 
 * Hello World.
 *
 * <p>This program covers the basic elements of a primitive X
 * application. It intensionally does not base on {@link Graphics}.
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Hello.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Hello.help">
 * help output</a>
 * 
 * @see Hello2
 */
public class Hello : gnu.x11.Application {
  public Hello (String [] args)
    : base (args) {

    about ("0.1", "hello world",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/",
      "\nTo quit, press 'q', 'Q', ESCAPE, or any button.");
   
    if (help_option) return;

    Window.Attributes win_attr = new Window.Attributes ();
    win_attr.set_background (display.default_white);
    win_attr.set_border (display.default_black);
    win_attr.set_event_mask (Event.BUTTON_PRESS_MASK
      | Event.EXPOSURE_MASK | Event.KEY_PRESS_MASK);
    Window window = new Window (display.default_root, 10, 10,
      100, 50, 5, win_attr);
    
    window.set_wm (this, "main");
    window.set_wm_delete_window ();
    window.map ();


    while (!exit_now) {
      Event evt = display.next_event ();

      switch (evt.code ()) {
      case gnu.x11.xevent.ButtonPress.CODE:
        exit ();
        break;

      case ClientMessage.CODE:
        if (((ClientMessage) evt).delete_window ()) exit ();
        break;

      case Expose.CODE:
        if (((Expose) evt).count () == 0) 
          window.text (display.default_gc, 20, 30, "Hello World!");
        break;
	
      case KeyPress.CODE: {
        KeyPress e = (KeyPress) evt;
	
        int keycode = e.detail ();
        int keystate = e.state ();
        int keysym = display.input.keycode_to_keysym (keycode, keystate);

        if (keysym == 'q' || keysym == 'Q' 
          || keysym == gnu.x11.keysym.Misc.ESCAPE) exit ();
        break;
      }      
      }
    }

    display.close ();
  }


  public static void Main (String [] args) {
    new Hello (args);
  }
}

}
