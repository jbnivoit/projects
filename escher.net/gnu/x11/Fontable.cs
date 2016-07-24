using System;
namespace gnu.x11 {


/** X fontable. */
public abstract class Fontable : Resource {
  /** Predefined. */
  public Fontable (int id)
    :base (id) {
  }


  /** Create. */
  public Fontable (Display display) 
    :base (display) {
  }


  /** Intern. */
  public Fontable (Display display, int id) 
    :base (display, id) {
  }


  /** Reply of {@link #info()}. */
  public /*static*/ class FontReply : Data {
    public FontReply (Data data) :base (data) { }
  
  
    public const int LEFT_TO_RIGHT = 0;
    public const int RIGHT_TO_LEFT = 1;
  
  
    public int min_char_or_byte2 () { return read2 (40); }
    public int max_char_or_byte2 () { return read2 (42); }
    public int default_char () { return read2 (44); }
    public int direction () { return read1 (48); }
    public int min_byte1 () { return read1 (49); }
    public int max_byte1 () { return read1 (50); }
    public bool all_chars_exist () { return read_bool (51); }
    public int ascent () { return read2 (52); }
    public int descent () { return read2 (54); }
  }
  
  
  // opcode 47 - query font  
  /**
   * @see <a href="XQueryFont.html">XQueryFont</a>
   */
  public FontReply info () {
    Request request = new Request (display, 47, 2);
    request.write4 (id);

    return new FontReply (display.read_reply (request));
  }

  
  /** Reply of {@link #text_extent(String)}. */
  public /*static*/ class TextExtentReply : Data {
    public TextExtentReply (Data data) :base (data) { }
  }
  
  
  // opcode 48 - query text extents  
  /**
   * @see <a href="XQueryTextExtents.html">XQueryTextExtents</a>
   */
  public TextExtentReply text_extent (String s) {
    Request request = new Request (display, 48, s.Length % 2 == 1,
      2+Data.unit (s));

    request.write4 (id);
    request.write1 (s);
    return new TextExtentReply (display.read_reply (request));
  }
}

}
