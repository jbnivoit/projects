using gnu.x11;

namespace gnu.x11.xevent {


/** X leave notify event. */
public class LeaveNotify : Input {
  public const int CODE = 8;


  public LeaveNotify (Display display, byte [] data)
    :base(display, data) {
  }
}
}
