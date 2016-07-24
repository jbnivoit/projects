using gnu.x11;

namespace gnu.x11.xevent {


/** X circulate notify event. */
public class CirculateNotify : Event {
  public const int CODE = 26;


  public CirculateNotify (Display display, byte [] data) 
    :base (display, data, 8) {
  }

}
}
