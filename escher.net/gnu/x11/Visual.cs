using System;
namespace gnu.x11 {


/** X visual. */
public class Visual : Data {
  public static readonly Visual COPY_FROM_PARENT = new Visual (4);


  public Visual (int length) :base (length) {}
  public Visual (Data data, int offset) : base (data, offset) {}
  public int id () { return read4 (0); }
  public int bits_per_rgb_value () { return read1 (5); }
  public int colormap_entries () { return read2 (6); }
  public int red_mask () { return read4 (8); }
  public int green_mask () { return read4 (12); }
  public int blue_mask () { return read4 (16); }


  public const int STATIC_GRAY = 0;
  public const int GRAY_SCALE = 1;
  public const int STATIC_COLOR = 2;
  public const int PSEUDO_COLOR = 3;
  public const int TRUE_COLOR = 4;
  public const int DIRECT_COLOR = 5;


  public static readonly String [] CLASS_STRINGS = {
    "static-gray", "gray-scale", "static-color", "pseudo-color", 
    "true-color", "direct-color" 
  };


  /**
   * @return valid:
   * {@link #STATIC_GRAY}
   * {@link #STATIC_COLOR}
   * {@link #TRUE_COLOR}
   * {@link #GRAY_SCALE}
   * {@link #PSEUDO_COLOR}
   * {@link #DIRECT_COLOR}
   */
  public int klass () { return read1 (4); }


  public override String ToString () {
    return "#Visual"
      + "\n  id: " + id ()
      + "\n  class: " + CLASS_STRINGS [klass ()]
      + "\n  bits-per-rgb-value: " + bits_per_rgb_value ()
      + "\n  colormap-entries: " + colormap_entries ()
      + "\n  red-mask: 0x" + gnu.util.Misc.toHexString (red_mask ())
      + "\n  green-mask: 0x " + gnu.util.Misc.toHexString (green_mask ())
      + "\n  blue-mask: 0x" + gnu.util.Misc.toHexString (blue_mask ());
  }
}

}
