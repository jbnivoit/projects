using gnu.x11;

namespace gnu.x11.xevent {


/** X map request event. */
public class MapRequest : Event {
  public const int CODE = 20;


  public MapRequest (Display display, byte [] data)
    : base (display, data, 8) {
  }
}
}
