using System;
using gnu.x11;
using gnu.x11.xevent;

namespace gnu.x11.extension.glx {


/** OpenGL application. */
public abstract class Application : gnu.x11.Application {
  protected const int EVENT_BIT = 1<<Event.LAST_MASK_INDEX+1;
  protected const int DELETE_BIT = 1<<Event.LAST_MASK_INDEX+2;    

  protected const int BUTTON_PRESS_BIT = Event.BUTTON_PRESS_MASK;
  protected const int BUTTON_MOTION_BIT = Event.BUTTON_MOTION_MASK;
  protected const int BUTTON1_MOTION_BIT = Event.BUTTON1_MOTION_MASK;
  protected const int BUTTON2_MOTION_BIT = Event.BUTTON2_MOTION_MASK;
  protected const int BUTTON3_MOTION_BIT = Event.BUTTON3_MOTION_MASK;
  protected const int BUTTON4_MOTION_BIT = Event.BUTTON4_MOTION_MASK;
  protected const int BUTTON5_MOTION_BIT = Event.BUTTON5_MOTION_MASK;
  protected const int KEYBOARD_BIT = Event.KEY_PRESS_MASK;
  protected const int POINTER_MOTION_BIT = Event.POINTER_MOTION_MASK;
  protected const int RESIZE_BIT = Event.STRUCTURE_NOTIFY_MASK;

  private const int ANY_BUTTON_MOTION_BITS = BUTTON_MOTION_BIT 
    | BUTTON1_MOTION_BIT 
    | BUTTON2_MOTION_BIT
    | BUTTON3_MOTION_BIT 
    | BUTTON4_MOTION_BIT 
    | BUTTON5_MOTION_BIT;

  private const int MOTION_BITS = ANY_BUTTON_MOTION_BITS
    | POINTER_MOTION_BIT;


  protected int event_mask;
  protected Event evt;
  protected GL gl;
  protected GLU glu;
  protected GLUT glut;
  protected GLX glx;
  protected bool leave_display_open;
  protected VisualConfig visual_config;
  protected Window window;
  protected bool window_dirty;


  protected Application (String [] args, int event_mask) 
    :base (args) {
    this.event_mask = event_mask;

    if (help_option) return;
    visual_config = new VisualConfig ();

    try {
      glx = new GLX (display);
    } catch (gnu.x11.extension.NotFoundException e) {
      throw new gnu.x11.Error ("Failed to initialize: " + e);
    }
  }


  abstract protected void handle_expose ();
  protected void mark_window_dirty () { window_dirty = true; }


  /**
   * Throw when application declares to override some event (via
   * `event_mask' in constructor) but forgets to override the corresponding
   * evetn handler.
   */
  private void error () {
    throw new gnu.x11.Error ("Un-overridden");
  }


  protected virtual void handle_button (int key, int state, int x, int y) { 
    error (); 
  }


  protected virtual bool handle_delete () { 
    error (); 
    return false; 
  }


  protected virtual bool handle_event (Event evt) { 
    error (); 
    return false; 
  }


  protected virtual void handle_keyboard (int key, int state, int x, int y) { 
    error (); 
  }


  protected virtual void handle_motion (int state, int x, int y) { 
    error (); 
  }


  protected virtual void handle_resize (int width, int height) { 
    error (); 
  }


  protected void init_window (int width, int height) {
    visual_config = glx.visual_config (visual_config);
    int vid = visual_config.visual_id ();
    gl = glx.create_context (vid, display.default_screen_no, GL.NONE0);

    // FIXME share colormap
    Colormap colormap = new Colormap (display.default_root, vid, false);
    
    Window.Attributes attr = new Window.Attributes ();
    attr.set_colormap (colormap);

    // TODO use depth of x visual config instead of
    // `visual_config.buffer_size'?
    int depth = visual_config.buffer_size ();

    int more = Event.EXPOSURE_MASK | Event.KEY_PRESS_MASK; // compulsory

    /* Bugs? Whenever button motion events are selected, it is required to
     * select button press event as well. 
     */
     if ((event_mask & ANY_BUTTON_MOTION_BITS) != 0)
       more |= Event.BUTTON_PRESS_MASK;
     attr.set_event_mask (event_mask | more);

    window = new Window (display.default_root, 10, 10, width, height);
    window.create (5, depth, Window.INPUT_OUTPUT, vid, attr);

    window.set_wm (this, "main");
    window.set_wm_delete_window ();

    gl.make_current (window);
    glu = new GLU (gl);
    glut = new GLUT (glu);
  }


  protected override void about (String version, String description,
    String author, String url, String extra) {

    base.about (version, description, author, url, 
      extra + "\nTo quit, press ESCAPE.\n");
  }


  private void dispatch_button_press () {
    if ((event_mask & BUTTON_PRESS_BIT) == 0) return;
      
    ButtonPress e = (ButtonPress) evt;
    int button = e.detail ();
    int state = e.state ();      
    handle_button (button, state, e.event_x (), e.event_y ());
  }


  private void dispatch_client_message () {
    if (!((ClientMessage) evt).delete_window ()) return;
    if ((event_mask & DELETE_BIT) != 0 && handle_delete ()) return;
    exit ();
  }


  private void dispatch_configure_notify () {
    if ((event_mask & RESIZE_BIT) == 0) return;
    ConfigureNotify e = (ConfigureNotify) evt;
      
    if (window.resized (e.rectangle ()))
      handle_resize (e.width (), e.height ());      
    window.set_geometry_cache (e.rectangle ());
  }


  private void dispatch_event () {
    evt = display.next_event ();
    if ((event_mask & EVENT_BIT) != 0 && handle_event (evt)) return;

    switch (evt.code ()) {
    case ButtonPress.CODE: dispatch_button_press (); break;
    case ClientMessage.CODE: dispatch_client_message (); break;
    case ConfigureNotify.CODE: dispatch_configure_notify (); break;
    case Expose.CODE: dispatch_expose (); break;	
    case KeyPress.CODE: dispatch_key_press (); break;
    case MotionNotify.CODE: dispatch_motion_notify (); break;
    }
  }


  private void dispatch_expose () {
    if (((Expose) evt).count () == 0) handle_expose ();
  }


  private void dispatch_key_press () {
    KeyPress e = (KeyPress) evt;
    int keycode = e.detail ();
    int keystate = e.state ();
    int keysym = display.input.keycode_to_keysym (keycode, keystate);

    if ((event_mask & KEYBOARD_BIT) != 0)
      handle_keyboard (keysym, keystate, e.event_x (), e.event_y ());

    if (keysym == gnu.x11.keysym.Misc.ESCAPE) exit ();
  }


  private void dispatch_motion_notify () {
    if ((event_mask & MOTION_BITS) == 0) return;

    MotionNotify e = (MotionNotify) evt;
    int state = e.state ();      
    handle_motion (state, e.event_x (), e.event_y ());
  }


  protected void exec () {
    if (help_option) return;

    window.map ();
    if ((event_mask & RESIZE_BIT) != 0)
      handle_resize (window.width, window.height);

    while (!exit_now) {
      if (window_dirty) {
        window_dirty = false;
        handle_expose ();
      }
     
      // `exit_now' may have become true during `handle_expose'
      if (!exit_now) dispatch_event ();
    }

    if (!leave_display_open) display.close ();
  }
}

}
