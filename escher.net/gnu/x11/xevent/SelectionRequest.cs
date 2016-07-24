using gnu.x11;

namespace gnu.x11.xevent {


/** X selection request event. */
public class SelectionRequest : Event {
  public const int CODE = 30;


  public SelectionRequest (Display display, byte [] data)
    : base (display, data, 8) {
  }
}
}
