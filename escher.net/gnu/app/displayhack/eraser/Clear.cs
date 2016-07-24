namespace gnu.app.displayhack.eraser {


/** Simply clear. */
public class Clear : Eraser {
  public Clear () : base ("clear") {}


  public override void erase (gnu.app.displayhack.DisplayHack hack) {
    hack.window.clear (false);
    hack.sleep (hack.delay/2);  // before next screen
  }
}
}
