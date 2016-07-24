using gnu.x11;

namespace gnu.x11.image {


public class XBM : Bitmap {
  public XBM (Display display, int width, int height, int [] xbm)
    :base (display, width, height) {

    // take <code>int</code> as parameter to avoid casting in java
    for (int i=0; i<data.Length; i++)
      data [i] = (byte) xbm [i];
  }
}

}
