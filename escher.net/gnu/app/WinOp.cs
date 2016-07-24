using gnu.x11;

namespace gnu.app {


/**
 * Perform action on window given its ID. This can be useful for debugging
 * window programming.
 * 
 * @see <a href="../../../etc/screenshot/gnu/app/WinOp.help">
 * help output</a>
 */
public class WinOp : gnu.x11.Application {
  public const int LIST_TOP_LEVEL = 0;
  public const int LIST_CHILDREN = 1;
  public const int MAP = 2;
  public const int SET_INPUT_FOCUS = 3;


  public static readonly String [] OPERATION_STRINGS = {
    "list-top-level",
    "list-children",
    "map",
    "set-input-focus"
  };


  Window window;


  public WinOp (String [] args)
    : base (args) {

    int window_id = option.intt ("window-id",
      "window id (0 = default root)", 0);
    int operation = option.enum ("operation",
      "action on window", OPERATION_STRINGS, LIST_TOP_LEVEL);
    
    about ("0.1", "perform action on window given its ID",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;
    
    if (window_id == 0) window_id = display.default_root.id;
    window = (Window) Window.intern (display, window_id);
    
    switch (operation) {
    case LIST_TOP_LEVEL:
      list_top_level ();
      break;

    case LIST_CHILDREN:
      list_children ();
      break;
      
    case MAP:
      window.map ();
      break;

    case SET_INPUT_FOCUS:
      window.set_input_focus ();
      break;
    }

    display.close ();
  }


  public void list_top_level () {
    // query all top-level windows
    for (Enum e=display.default_root.tree ().children (); 
         e.more ();) {

      Window child = (Window) e.next ();

      // selection criteria
      if (child.attributes ().override_redirect ()
        || child.attributes ().map_state ()
        != Window.AttributesReply.VIEWABLE
	|| child.wm_name () == null) continue;

      Console.WriteLine (child.id + " " + child.wm_name ());
    }
  }

  
  public void list_children () {
    Console.WriteLine ("---- children of " + window
      + window.tree ().children ().to_string (Enum.NEXT4));
  }


  public static void Main (String args []) {
    new WinOp (args);
  }
}
}
