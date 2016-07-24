using gnu.x11;

namespace gnu.x11.xevent {


/** X visibility notify event. */
public class VisibilityNotify : Event {
  public const int CODE = 15;


  public VisibilityNotify (Display display, byte [] data)
    : base (display, data, 8) {
  }
}
}
