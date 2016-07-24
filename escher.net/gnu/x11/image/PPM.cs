using System;
using System.IO;

using gnu.x11;

namespace gnu.x11.image {


public class PPM : ZPixmap { // TODO
  public PPM (Display display, StreamReader bin) 
	//throws IOException 
    // WARNING: very naive parsing

    :base (display) {


    // format

    String format = bin.ReadLine ();
    if (!(format.Equals ("P6")))
      throw new Error ("Unsupported format: " + format);


    // dimension

    String dimension = bin.ReadLine ();      
    int index = dimension.IndexOf (' ');
    try {
      width = Int32.Parse (dimension.Substring (0, index));
      height = Int32.Parse (dimension.Substring (
        index+1, dimension.Length));

    } catch (Exception e) {
      throw new Error ("Invalid dimension: " + dimension);
    }

    String color_count = bin.ReadLine ();


    // fill up data
    
    init ();
    Colormap cmap = display.default_colormap;   

    for (int y=0; y<height; y++)
      for (int x=0; x<width; x++) {
        int r = bin.Read ();
        int g = bin.Read ();
        int b = bin.Read ();

        // FIXME cache and index color
        set (x, y, cmap.alloc_color8 (r, g, b));
      }
  }
}

}
