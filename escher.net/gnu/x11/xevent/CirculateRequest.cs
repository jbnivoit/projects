using gnu.x11;

namespace gnu.x11.xevent {


/** X circulate request event. */
public class CirculateRequest : Event {
  public const int CODE = 27;


  public CirculateRequest (Display display, byte [] data)
    :base (display, data, 8) {
  }

}
}
