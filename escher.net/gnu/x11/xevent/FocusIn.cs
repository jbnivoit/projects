using gnu.x11;

namespace gnu.x11.xevent {


/** X focus in event. */
public class FocusIn : Event {
  public const int CODE = 9;


  public FocusIn (Display display, byte [] data)
    : base (display, data, 8) {
  }
}
}
