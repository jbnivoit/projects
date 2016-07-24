using System;

using gnu.x11;
using gnu.x11.xevent;

namespace gnu.app {


/**
 * Send string to top-level windows. It sends to all top-level windows
 * matching res_name and res_class given. I use this all the time to send
 * common long strings to netscape.
 *
 * <p>You may find this emacs code helpful.
 * <pre>
 * <code>
 * (defun salt-id ()
 *   (interactive)
 *   (shell-command 
 *   (format "java gnu.app.Salt Navigator Netscape 29340002487578")))
 * </code>
 * </pre>
 * 
 * @see <a href="../../../etc/screenshot/gnu/app/Salt.help">
 * help output</a>
 */
public class Salt : gnu.x11.Application {
  public Salt (String [] args)
    : base (args) {

    String res_name = option.option ("res-name", "resource name of windows", "");
    String res_class = option.option ("res-class","resource class of windows", "");
    String message = option.option ("message", "message to be sent", "");
    
    about ("0.1", "send string to top-level windows",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;

    for (gnu.x11.Enum e=display.default_root.tree ().children (); 
         e.more ();) {

      Window window = (Window) e.next ();
      Window.WMClassHint class_hint = window.wm_class_hint ();
      
      if (class_hint == null) continue;
      if (!class_hint.Equals (res_name, res_class)) continue;
      
      if (window.attributes ().override_redirect ()
        || window.attributes ().map_state () 
        != Window.AttributesReply.VIEWABLE
	|| window.wm_name () == null) continue;


      for (int i=0; i<message.Length; i++)
        send_key (window, message[i]);

      // keep loop to salt all matched apps 
    }
    
    display.close ();
  }


  public void send_key (Window window, int keysym) {
    bool capital = keysym >= 'A' && keysym <= 'Z';
    // keysym of corresponding small letter
    int small_keysym = !capital ? keysym : keysym + ('a' - 'A');

    KeyPress key_event = new KeyPress (display);
    key_event.set_window (window);
    key_event.set_detail (display.input.keysym_to_keycode (small_keysym));
    if (capital) key_event.set_state (gnu.x11.Input.SHIFT_MASK);

    window.send_event (false, Event.NO_EVENT_MASK, key_event);
  }


  public static void Main (String [] args) {
    new Salt (args);
  }
}
}
