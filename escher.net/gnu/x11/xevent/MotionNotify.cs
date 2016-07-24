using gnu.x11;

namespace gnu.x11.xevent {


/** X motion notify event. */
public class MotionNotify : Input {
  public const int CODE = 6;


  public MotionNotify (Display display, byte [] data)
    : base (display, data) {
  }

}
}
