using System;

using gnu.app.displayhack;

namespace gnu.app.displayhack.eraser {

/** Base class for erasers. */
public abstract class Eraser {
  public static readonly Eraser [] ALL = {
    new Circle (),
    new Clear (),
    new SlideLines (),
    new ThreeCircles ()
  };


  public static readonly int RANDOM_ERASER_INDEX = ALL.Length;
  public static readonly String [] ALL_STRINGS = new String [] { 
	ALL[0].id, 
	ALL[1].id, 
	ALL[2].id, 
	ALL[3].id, 
	"random"
	};


  public String id;

  
  public Eraser (String id) { this.id = id; }
  public abstract void erase (DisplayHack hack);


  public bool sleep (DisplayHack hack) {
    bool interrupted = hack.sleep (hack.eraser_delay);
    if (interrupted) hack.window.clear (false);
    return interrupted;
  }
}
}
