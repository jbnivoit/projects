using gnu.x11;

namespace gnu.x11.xevent {


/** X enter notify event. */
public class EnterNotify : Input {
  public const int CODE = 7;


  public EnterNotify (Display display, byte [] data)
    :base (display, data) {
  }
}
}
