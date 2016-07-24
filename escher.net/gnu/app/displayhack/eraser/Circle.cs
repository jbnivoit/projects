using System;

namespace gnu.app.displayhack.eraser {


/**
 * Erase by a circle. 
 *
 * <p>Modified from <code>circle_wipe</code> of <code>erase.c</code> in <a
 * href="http://www.jwz.org/xscreensaver/">xscreensaver</a> by Johannes
 * Keukelaar <johannes@nada.kth.se>.
 */
public class Circle : Eraser {
  public Circle () : base ("circle-wipe") {}


  public override void erase (gnu.app.displayhack.DisplayHack hack) {
    gnu.x11.Window window = hack.window;

    /* Minimum radius = L/sqrt(2) ~= 0.707*L,
     *   where L = max(width, heigth)
     *         sqrt(2) = 1.414213562373095
     *
     * Take radius = L for faster (easier) computation.
     */
    int radius = Math.Max (window.width, window.height);

    int full = 360 * 64;
    int delta = (full/200) * hack.eraser_delta;
    int step_count = (int) Math.Ceiling ( (double)(1 + full/delta));
    int start = DisplayHack.random.Next (full);

    // clockwise or counter-clockwise
    if (DisplayHack.random.Next()%2==0) delta = -delta;


    for (int i=0; i<step_count; i++) {
      window.arc (hack.display.default_gc, 
        window.width/2 - radius, window.height/2 - radius,
        2*radius, 2*radius, (start+i*delta) % full, delta, true);

      if (sleep (hack)) return;
    }
    
    hack.sleep (hack.delay/2);  // before next screen
  }
}
}
