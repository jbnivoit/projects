using gnu.x11;

namespace gnu.x11.xevent {


/** X resize request event. */
public class ResizeRequest : Event {
  public const int CODE = 25;


  public ResizeRequest (Display display, byte [] data)
    : base (display, data, 8) {
  }


  //-- reading

  public int width () { return read2 (8); }
  public int height () { return read2 (10); }
}
}
