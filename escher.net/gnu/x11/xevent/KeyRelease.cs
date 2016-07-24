using gnu.x11;

namespace gnu.x11.xevent {


/** X key release event. */
public class KeyRelease : Input {
  public const int CODE = 3;


  public KeyRelease (Display display, byte [] data)
	:base(display, data) {
  }

}
}
