using gnu.x11;

namespace gnu.x11.xevent {


/** X selection clear event. */
public class SelectionClear : Event {
  public const int CODE = 29;


  public SelectionClear (Display display, byte [] data)
    : base (display, data, 8) {
  }
}
}
