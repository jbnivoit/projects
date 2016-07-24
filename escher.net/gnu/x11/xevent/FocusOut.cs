using gnu.x11;

namespace gnu.x11.xevent {


/** X focus out event. */
public class FocusOut : Event {
  public const int CODE = 10;


  public FocusOut (Display display, byte [] data)
    : base (display, data, 8) {
  }
}
}
