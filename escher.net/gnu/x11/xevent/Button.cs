using gnu.x11;

namespace gnu.x11.xevent {

/** X button event. */
public class Button : Input {
  public Button (Display display, byte [] data)
    :base (display, data) {
  }


  public override int detail () { return read1 (1); }
  public override int child_id () { return read4 (16); }
  public override Window child () { return (Window) Window.intern (display, child_id ()); }
}
}
