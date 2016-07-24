using gnu.x11;

namespace gnu.x11.xevent {


/** X map notify event. */
public class MapNotify : Event {
  public const int CODE = 19;


  public MapNotify (Display display, byte [] data) 
	: base (display, data, 8) {
  }
}
}
