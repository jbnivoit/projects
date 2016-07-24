using System;
using gnu.x11;

namespace gnu.x11.extension {


/** 
 * XC-MISC Extension. The specification can be found <a href= 
 * "http://escher.sourceforge.net/etc/specification/xcmisc.ps.gz"
 * >here</a>.
 */
public class XCMisc : Extension {
  public static readonly String [] MINOR_OPCODE_STRINGS = {
    "GetVersion",               // 0
    "GetXIDRange",              // 1
    "GetXIDList"                // 2
  };


  public const int CLIENT_MAJOR_VERSION = 1;
  public const int CLIENT_MINOR_VERSION = 1;

  public int server_major_version, server_minor_version;


  // xc-misc opcode 0 - get version
  public XCMisc (gnu.x11.Display display) //throws NotFoundException {
    :base (display, "XC-MISC", MINOR_OPCODE_STRINGS) {

    // check version before any other operations
    Request request = new Request (display, major_opcode, 0, 2);
    request.write2 (CLIENT_MAJOR_VERSION);
    request.write2 (CLIENT_MINOR_VERSION);

    Data reply = display.read_reply (request);
    server_major_version = reply.read2 (8);
    server_minor_version = reply.read2 (10);
  }

  
  /** Reply of {@link XCMisc#xid_range()} */
  public /*static*/ class XIDRangeReply : Data {
    public XIDRangeReply (Data data) : base (data) {}
    public int start_id () { return read4 (8); }
    public int count () { return read4 (12); }
  }
  
  
  // xc-misc opcode 1 - get xid range
  public XIDRangeReply xid_range () {
    Request request = new Request (display, major_opcode, 1, 1);
    return new XIDRangeReply (display.read_reply (request));
  }


  // xc-misc opcode 2 - get xid list
  public Enum xid_list (int count) {
    Request request = new Request (display, major_opcode, 2, 2);
    request.write4 (count);

    Data reply = display.read_reply (request);
    return new Enum (reply, 32, reply.read4 (8));
  }


  public override String more_string () {
    return "\n  client-version: " 
      + CLIENT_MAJOR_VERSION + "." + CLIENT_MINOR_VERSION
      + "\n  server-version: "
      + server_major_version + "." + server_minor_version;
  }
}

}
