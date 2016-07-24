using gnu.x11;

namespace gnu.x11.xevent {


/** X selection notify event. */
public class SelectionNotify : Event {
  public const int CODE = 31;


  public SelectionNotify (Display display, byte [] data)
    : 	base (display, data, 8) {
  }
}
}
