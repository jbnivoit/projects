using System;
namespace gnu.x11 {


/** Text item for drawing text to X server. */
public class Text {
  public String s;
  public int delta;
  public Font font;
  

  public Text (String s) { this.s = s; }

  public Text (String s, int delta) {
    this.s = s;
    this.delta = delta;
  }


  public Text (String s, int delta, Font font) {
    this.s = s;
    this.delta = delta;
    this.font = font;
  }


  public int Length (int bit) {
    // 2 = length of string field and delta field
    // 5 = font field
    int n = font == null ? 2 : 2+5;

    if (bit == 8 || s[0] > 128) // non-ascii	  
      return n + s.Length;
      
    else
      return n + 2 * s.Length;
  }


  public override String ToString () {
    return "#Text [" + s + " " + delta + " " + font + "]";
  }
}

}
