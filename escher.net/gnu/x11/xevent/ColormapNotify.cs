using gnu.x11;

namespace gnu.x11.xevent {


/** X colormap notify event. */
public class ColormapNotify : Event {
  public const int CODE = 32;


  public ColormapNotify (Display display, byte [] data)
    :base (display, data, 8) {
  }

}
}
