using gnu.x11;

namespace gnu.x11.xevent {


/** X graphics expose event. */
public class GraphicsExpose : Event {
  public const int CODE = 13;


  public GraphicsExpose (Display display, byte [] data)
    :base(display, data, 8) {
  }
}
}
