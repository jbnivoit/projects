using gnu.x11;

namespace gnu.x11.xevent {


/** X button release event. */
public class ButtonRelease : Input {
  public const int CODE = 5;


  public ButtonRelease (Display display, byte [] data) 
    :base (display, data){
  }


  public ButtonRelease (Display display) : base (display, CODE) { }
}
}
