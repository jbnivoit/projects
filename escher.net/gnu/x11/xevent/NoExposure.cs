using gnu.x11;

namespace gnu.x11.xevent {


/** X no exposure event. */
public class NoExposure : Event {
  public const int CODE = 14;


  public NoExposure (Display display, byte [] data)
    : base (display, data, 4) {
  }
}
}
