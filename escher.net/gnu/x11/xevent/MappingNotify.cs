using gnu.x11;

namespace gnu.x11.xevent {


/** X mapping notify event. */
public class MappingNotify : Event {
  public const int CODE = 34;


  public MappingNotify (Display display, byte [] data)
    :base(display, data, 0) {
  }


  public override void set_window (int i) {} // no window
  public override int window_id () { return 0; } // no window
}
}
