using gnu.x11;

namespace gnu.x11.image {


public class Image {
  public const int LSB_FIRST = 0;
  public const int MSB_FIRST = 1;
  public const int LEAST_SIGNIFICANT = 0;
  public const int MOST_SIGNIFICANT = 1;

  public byte [] data;
  public int width, height, left_pad, format, line_byte_count;
  public Pixmap.Format pixmap_format;


  public Image () {}

  public Image (int width, int height, int format, Pixmap.Format pixmap_format) {
    this.width = width;
    this.height = height;
    this.format = format;
    this.pixmap_format = pixmap_format;
    
    init ();
  }


  public void init () {
    // compute line_byte_count
    int line_bit_count = width * pixmap_format.bits_per_pixel ();
    int rem = line_bit_count % pixmap_format.scanline_pad ();
    int line_pad_count = line_bit_count / pixmap_format.scanline_pad ()
      + (rem == 0 ? 0 : 1);
    line_byte_count = line_pad_count * pixmap_format.scanline_pad () / 8;

    left_pad = format == ZPixmap.FORMAT ? 
      0 : line_byte_count * 8 - line_bit_count;
    
    data = new byte [line_byte_count * height];
  }
}

}
