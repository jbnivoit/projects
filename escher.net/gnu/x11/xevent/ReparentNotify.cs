using gnu.x11;

namespace gnu.x11.xevent {


/** X reparent notify event. */
public class ReparentNotify : Event {
  public const int CODE = 21;


  public ReparentNotify (Display display, byte [] data)
    : base (display, data, 8) {
  }
}
}
