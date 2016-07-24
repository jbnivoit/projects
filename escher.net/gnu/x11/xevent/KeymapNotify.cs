using gnu.x11;

namespace gnu.x11.xevent {


/** X keymap notify event. */
public class KeymapNotify : Event {
  public const int CODE = 11;


  public KeymapNotify (Display display, byte [] data)
    :base(display, data, 8) {
  }

}
}
