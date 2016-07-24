using System;
using gnu.x11;

namespace gnu.app.puppet {


/** Wrapper of {@link gnu.x11.Window} for {@link Puppet}. */
public class Client : Window {
  // system attributes
  public new Window.AttributesReply attributes;
  public WMClassHint class_hint;
  public String name;
  public WMSizeHints size_hints;


  // internal states
  public bool early_unmapped, early_destroyed;
  public int register = -1;     // invalid register index
  public int saved_width, saved_height;
  public Puppet.InternalState state;


  /** Intern. */
  public Client (Display display, int id)
    : base (display, id) {
  }


  public static Object intern (Window window) {
    return intern (window.display, window.id);
  }


  public new static Object intern (Display display, int id) {
    Object value = display.resources[id];
    if (value != null && value is Client) return value;
    return new Client (display, id);
  }
    
  
  public static readonly String [] STATE_STRINGS = {
    "unmanaged", "normal", "hidden", "no-focus", "early-unmapped",
    "early-destroyed"
  };


  public override String ToString () {
    String name0 = name == null ? "" : "\"" + name + "\" ";
    String hint0 = class_hint == null ? "(" : class_hint.ToString () + " (";
    return "#Client " + name0 + hint0 + STATE_STRINGS [(int)state] + ") "
      + base.ToString ();
  }

    public void update_attributes() {
		this.attributes = base.attributes();
	}

}
}
