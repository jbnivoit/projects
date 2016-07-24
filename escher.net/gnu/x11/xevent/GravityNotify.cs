using gnu.x11;

namespace gnu.x11.xevent {


/** X gravity notify event. */
public class GravityNotify : Event {
  public const int CODE = 24;


  public GravityNotify (Display display, byte [] data)
	:base(display, data, 8) {
  }
}
}
