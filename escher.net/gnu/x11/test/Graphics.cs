using System;

using gnu.x11;
using gnu.x11.xevent;

namespace gnu.x11.test {


/** Base class for testing basic drawing. */
public abstract class Graphics : gnu.x11.Application {  
  public Event evt;
  public bool leave_display_open;
  public Window window;


  public Graphics (String [] args, int width, int height)
    : base (args) {

    Window.Attributes win_attr = new Window.Attributes ();
    win_attr.set_background (display.default_white);
    win_attr.set_border (display.default_black);
    win_attr.set_event_mask (Event.BUTTON_PRESS_MASK
      | Event.EXPOSURE_MASK | Event.KEY_PRESS_MASK);
    window = new Window (display.default_root, 10, 10,
      width, height, 5, win_attr);

    window.set_wm (this, "main");
    window.set_wm_delete_window ();
  }


  protected virtual void paint () {}

  
  protected override void about (String version, String description,
    String author, String url) {
    
    about (version, description, author, url,
      "\nTo quit, press 'q', 'Q', ESCAPE, or any button.");
  }


  protected virtual void exec () {
    if (help_option) return;

    window.map ();
    while (!exit_now) dispatch_event ();
    if (!leave_display_open) display.close ();
  }


  protected virtual void dispatch_event () {
    evt = display.next_event ();

    switch (evt.code ()) {
    case gnu.x11.xevent.ButtonPress.CODE:
      exit ();
      break;

    case ClientMessage.CODE:
      if (((ClientMessage) evt).delete_window ()) exit ();
      break;

    case Expose.CODE:
      if (((Expose) evt).count () == 0) paint ();
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
}

}
