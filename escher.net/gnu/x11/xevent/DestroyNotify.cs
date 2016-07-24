using gnu.x11;

namespace gnu.x11.xevent {


/** X destroy notify event. */
public class DestroyNotify : Event {
  public const int CODE = 17;


  public DestroyNotify (Display display, byte [] data)
    :base (display, data, 8) {
  }

}
}
