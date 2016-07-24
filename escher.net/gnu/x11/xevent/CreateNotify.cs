using gnu.x11;

namespace gnu.x11.xevent {


/** X create notify event. */
public class CreateNotify : Event {
  public const int CODE = 16;


  public CreateNotify (Display display, byte [] data)
    :base (display, data, 8) {
  }

}
}
