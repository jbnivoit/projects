using gnu.x11;

namespace gnu.x11.xevent {


/** X property notify event. */
public class PropertyNotify : Event {
  public const int CODE = 28;


  public PropertyNotify (Display display, byte [] data) 
    : base (display, data, 4) {
  }


  public Atom atom (Display display) { 
    return (Atom) Atom.intern (display, read4 (8), true);
  }
}
}
