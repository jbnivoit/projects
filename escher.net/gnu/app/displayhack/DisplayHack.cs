using System;
using System.Threading;

using gnu.x11;
using gnu.app.displayhack.eraser;
using gnu.x11.xevent;

namespace gnu.app.displayhack {


/**
 * Base class for display hacks. 
 * 
 * <p>The implementation uses two threads so that one can be painting and
 * one can be waiting for user input. Only with two threads can {@link
 * #sleep(long)} be interrupted (with {@link #restart()} or {@link
 * #exit()}) to give responsive user interface.
 */
public abstract class DisplayHack : gnu.x11.Application
{

  public bool stop_now;
  public static readonly System.Random random = new System.Random ();

  public int eraser_delta, eraser_mode;
  public long delay, eraser_delay;
  public Color [] colors;
  public gnu.x11.GC gc, eraser_gc;
  public gnu.x11.GC.Values gc_values = new gnu.x11.GC.Values ();
  public Window window;
  public Thread thread;


  /** 
   * Clear window before the first iteration. Hacks that play with screen
   * content or those that wish to improve initial perceived drawing speed
   * (such as {@link Deco}) should set this to false.
   */
  public bool clear;


  /** Erase window between iterations. */
  public bool erase_;


  public DisplayHack (String [] args, bool clear, bool erase,
    bool rainbow_color, int default_color_count, int default_delay)
    : base (args) {
	this.thread = new Thread (new ThreadStart(this.run));
    this.clear = clear;
    this.erase_ = erase;

    int color_count = option.intt ("color-count", 
      "total number of random colors", default_color_count);
    delay = option.longg ("delay",
      "delay between screens in ms", default_delay);

    if (erase) {
      eraser_delay = option.longg ("eraser-delay", 
        "delay between iterations of eraser in ms", 10);
      eraser_delta = option.intt ("eraser-delta",
        "granularity of eraser", 5, 1, 10);
      eraser_mode = option.Enum ("eraser-mode",
        "which eraser", Eraser.ALL_STRINGS, 
        Eraser.RANDOM_ERASER_INDEX);
    }

    Rectangle geometry = option.rectangle ("geometry", 
      "initial geometry of main window",
      new Rectangle (10, 10, 600, 480));

    if (help_option) return;

    gc = gnu.x11.GC.build (display);
    if (erase_) eraser_gc = gnu.x11.GC.build (display);


    colors = new Color [color_count];

    if (rainbow_color)
      for (int i=0; i<color_count; i++)   
        colors [i] = display.default_colormap.
          alloc_random_rainbow_color (random);

    else
      for (int i=0; i<color_count; i++)   
        colors [i] = display.default_colormap. alloc_random_color (random);


    Window.Attributes win_attr = new Window.Attributes ();
    win_attr.set_background (display.default_black);
    win_attr.set_event_mask (Event.BUTTON_PRESS_MASK
      | Event.STRUCTURE_NOTIFY_MASK 
      | Event.EXPOSURE_MASK | Event.KEY_PRESS_MASK);
    window = new Window (display.default_root, geometry, 0, win_attr);

    window.set_wm (this, "main");
    window.set_wm_delete_window ();
  }


  public abstract void paint ();


  protected override void about (String version, String description,
    String author, String url) {

    about (version, description, author, url,
      "\nTo quit, press 'q', 'Q', or ESCAPE."
      + "\nTo force next screen, press SPACE or BUTTON1");
  }


  public static bool chance (float probability) {
    return ((float)random.NextDouble()) < probability;
  }


  public void dispatch_event () {
    Event evt = display.next_event ();

    switch (evt.code ()) {
    case ButtonPress.CODE: {
      int button = ((ButtonPress) evt).detail ();
      if (button == gnu.x11.Input.BUTTON1) restart ();
      else if (button == gnu.x11.Input.BUTTON3) exit ();
      break;

    } case ConfigureNotify.CODE:
      window.set_geometry_cache (((ConfigureNotify) evt).rectangle ());
      break;

    case Expose.CODE:
      if (thread.IsAlive) restart ();
      else {
        if (clear) window.clear (false); // before thread starts
        thread.Start ();
      }
      break;
	
    case KeyPress.CODE: {
      KeyPress e = (KeyPress) evt;
	
      int keycode = e.detail ();
      int keystate = e.state ();
      int keysym = display.input.keycode_to_keysym (keycode, keystate);

      if (keysym == ' ') restart ();
      else if (keysym == 'q' || keysym == 'Q' 
        || keysym == gnu.x11.keysym.Misc.ESCAPE) exit ();
      break;

    } case ClientMessage.CODE:
      if (((ClientMessage) evt).delete_window ()) exit ();
      break;
    }
  }


  public void erase () {
    int which = eraser_mode;
    if (eraser_mode == Eraser.RANDOM_ERASER_INDEX)
      which = random.Next (Eraser.ALL.Length);

    Eraser.ALL [which].erase (this);
  }


  /**
   * Main method. Separating this method from constructor allows subclass
   * constructors to be called before dispatching the first
   * <code>Expose</code>. It is responsible for user interaction.
   */
  public void exec () { 
    if (help_option) return;

    window.map ();
    while (!exit_now) dispatch_event ();

    /* Do not close display here. The other thread (painting thread) is
     * reponsible for closing display, because it always outlasts the main
     * thread.
     */
  }


  protected override void exit () {
    base.exit ();
    restart ();
  }


  public Color random_color () {
    return colors [random.Next (colors.Length)];
  }   


  /** {@link java.util.Random#nextInt(int)} accepting zero as argument. */
  public int random_int (int n) {
    if (n == 0) return 0;
    return random.Next (n);
  }


  public int random_sign () {
    return random.Next()%2==0 ? 1 : -1;
  }


  public void restart () {
    stop_now = true;            // stop paint, if painting
    thread.Interrupt ();        // stop sleep, if sleeping
  }


  public void run () {
    while (!exit_now) {
      stop_now = false;
      paint ();
      sleep (delay);

      // erase despite `stop_now'
      if (erase_ && !exit_now) erase ();
    }

    display.close ();
  }


  public bool sleep (long millis) {
    if (millis != 0) display.flush ();
    if (!stop_now) gnu.util.Misc.sleep ((int)millis);
    return stop_now;
  }
}
}
