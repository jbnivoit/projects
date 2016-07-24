using System;
namespace gnu.x11 {


/** Position and size in geometry. */
public class Rectangle {
  public int x, y, width, height;


  /**
   * Construct from a resource geometry specification string.
   *
   * <ul>supported formats
   * <li>width x height + x + y (e.g. 100x300+50+50 or 100x300-20+20)
   * <li>width x height (e.g. 100x300)
   * <li>+ x + y (+50+50 or -20-20)
   * </ul>
   */
  public Rectangle (String spec) {
    try {
      int i0 = spec.IndexOf ('x');
      int i1 = spec.IndexOf ('+');
      int i2 = spec.IndexOf ('-');
      if (i0 == -1 && i1 == -1 && i2 == -1) throw new Exception ();

      int index;                // beginning of +x+y
      if (i1 == -1) index = i2;
      else if (i2 == -1) index = i1;
      else index = Math.Min (i1, i2);


      if (i0 != -1) {        
        int j = index == -1 ? spec.Length : index;

        width = Int32.Parse (spec.Substring (0, i0));
        height = Int32.Parse (spec.Substring (i0+1, j));
      }


      if (index != -1) {
        String offset = spec.Substring (index+1, spec.Length);
        int j0 = offset.IndexOf ('+');
        int j1 = offset.IndexOf ('-');
        int j = Math.Max (j0, j1); // beginning of +y

        int s0 = spec[index] == '+' ? 1 : -1;
        int s1 = offset[j] == '+' ? 1 : -1;
        
        x = s0 * Int32.Parse (offset.Substring (0, j));
        y = s1 * Int32.Parse (offset.Substring (j+1, offset.Length));
      }

    } catch (Exception e) {
      throw new Exception ("Invalid geometry specification: "
        + "\nSupported examples:"
        + "\n  100x300+50+50 or 100x300-20+20"
        + "\n  100x300"
        + "\n  +50+50 or -20+20");
    }
  }


  public Rectangle (int x, int y, int width, int height) {
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
  }


  public Rectangle within (Rectangle bound) {
    int x0 = Math.Max (x, bound.x);
    int y0 = Math.Max (y, bound.y);
    int width0 = Math.Min (width, bound.width);
    int height0 = Math.Min (height, bound.height);
    return new Rectangle (x0, y0, width0, height0);
  }


  public String spec () {
    return width + "x" + height
      + (x >= 0 ? "+" : "") + x
      + (y >= 0 ? "+" : "") + y;    
  }


  public override String ToString () {
    return "#Rectangle " + spec ();
  }
}

}
