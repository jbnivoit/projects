using gnu.x11;

namespace gnu.x11.xevent {


/** X unmap notify event. */
public class UnmapNotify : Event {
  public const int CODE = 18;


  /** Reading. */
  public UnmapNotify (Display display, byte [] data)
    : base (display, data, 8) {
  }


  //-- reading
  public bool from_configure () { return read_bool (12); }


  /** Writing. */
  public UnmapNotify (Display display) : base (display, CODE, 8) {}

  //-- writing
  public void set_event (Window w) { write4 (4, w.id); }
  public override void set_window (Window w) { write4 (8, w.id); }
  public void set_from_configure (bool b) { write1 (12, b); }
}
}
