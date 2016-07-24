using gnu.x11;

namespace gnu.x11.extension {


/**
 * Big Requests Extension. The specification can be found <a href= 
 * "http://escher.sourceforge.net/etc/specification/bigrequest.ps.gz"
 * >here</a>.
 */
public class BigRequests : Extension {
  public BigRequests (gnu.x11.Display display) : base (display, "BIG-REQUESTS", null)
  {
  }


  // bigrequests opcode 0 - big req enable
  /**
   * @see <a href="XExtendedMaxRequestSize.html">
   * XExtendedMaxRequestSize</a>
   */
  public int enable () {
    Request request = new Request (display, major_opcode, 0, 1);
    return display.read_reply (request).read4 (8);
  }
}
}
