using gnu.x11;

namespace gnu.x11.extension.glx {


/** GLX pbuffer clobber event. */
public class PbufferClobberEvent : gnu.x11.xevent.Event {
  public new const int code = 0;


  public PbufferClobberEvent (Display display, byte [] data)
    :base (display, data, 0) {
  }


  public int drawable_id () { return read4 (8); }
  public int buffer_mask () { return read4 (12); }
  public int aux_buffer () { return read2 (16); }
  public int x () { return read2 (18); }
  public int y () { return read2 (20); }
  public int width () { return read2 (22); }
  public int height () { return read2 (24); }
  public int count () { return read2 (26); }


  public const int DAMAGED = 0x8017;
  public const int SAVED = 0x8018;


  /** 
   * @return valid:
   * {@link #DAMAGED},
   * {@link #SAVED}
   */
  public int event_type () { return read2 (4); }


  public const int WINDOW = 0x8019;
  public const int PBUFFER = 0x801A;


  /** 
   * @return valid:
   * {@link #WINDOW},
   * {@link #PBUFFER}
   */
  public int drawable_type () { return read2 (6); }
}  

}
