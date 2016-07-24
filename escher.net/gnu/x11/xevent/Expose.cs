using gnu.x11;

namespace gnu.x11.xevent {


/** X expose event. */
public class Expose : Event {
  public const int CODE = 12;


  public Expose (Display display, byte [] data)
    :base (display, data, 4) {
  }


  public int x () { return read2 (8); }
  public int y () { return read2 (10); }
  public int width () { return read2 (12); }
  public int height () { return read2 (14); }
  public int count () { return read2 (16); }
}
}
