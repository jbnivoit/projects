using gnu.x11;

namespace gnu.x11.xevent {


/** X button press event. */
public class ButtonPress : Input {
  public const int CODE = 4;


  public ButtonPress (Display display, byte [] data)
    :base(display, data) {
  }


  public ButtonPress (Display display) : base (display, CODE) {}
}
}
