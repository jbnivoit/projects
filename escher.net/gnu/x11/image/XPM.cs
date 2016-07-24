using System;
using System.Collections;
using gnu.x11;

namespace gnu.x11.image {


public class XPM : ZPixmap { // TODO
  public XPM (Display display, String [] xpm)
    :base (display) {

    String [] values = xpm [0].Split(new char[] { ' ' });
    width = Int32.Parse (values[0]);
    height = Int32.Parse (values[1]);
    int num_colors = Int32.Parse (values[2]);
    int chars_per_pixel = Int32.Parse (values[3]);

    // TODO how to select best SUITABLE format?
    format = FORMAT;
    pixmap_format = display.default_pixmap_format;
    image_byte_order = display.image_byte_order;
    pixel_byte_count = pixmap_format.bits_per_pixel () / 8;
    init ();

    Hashtable mapping = new Hashtable (2*num_colors);
    Colormap cmap = display.default_colormap;
    
    for (int i=0; i<num_colors; i++) {
      String [] color = xpm [i+1].Split(new char[] {' '});
      String symbol = color[0];
      
      while (color.Length>1
	&& color[1].Equals ("c")) { // can only parse c for now
	
	String color_value = color[2];

	if (color_value[0] == '#') {
	  int pixel = Int32.Parse (
	    color_value.Substring (1, color_value.Length), System.Globalization.NumberStyles.HexNumber);

	  mapping.Add (symbol, new Color (pixel));

	} else			// not starting with #
	  mapping.Add (symbol, cmap.alloc_named_color (color_value));
      }
    }

    // TODO more efficient linear for-loop
    for (int y=0; y<height; y++) {
      String pixels = xpm [1+num_colors+y];

      for (int x=0; x<width; x++) {
	String symbol = pixels.Substring (x*chars_per_pixel,
	  (x+1)*chars_per_pixel);
	Color color = (Color) mapping[symbol];
	set (x, y, color.pixel);
      }
    }
  }
}



}
