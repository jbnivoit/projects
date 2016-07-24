using gnu.x11;

namespace gnu.x11.xevent {


/** X key press event. */
public class KeyPress : Input {
  public const int CODE = 2;


  // reading
  public KeyPress (Display display, byte [] data)
    :base(display, data) {
  }


  // writing
  public KeyPress (Display display) : base (display, CODE) {}
}
}
