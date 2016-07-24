using System;
using gnu.x11;

namespace gnu.x11.xevent {


/** X event. */
public class Event : gnu.x11.Data {
  public const int NO_EVENT_MASK = 0;
  public const int KEY_PRESS_MASK = 1<<0;
  public const int KEY_RELEASE_MASK = 1<<1;
  public const int BUTTON_PRESS_MASK = 1<<2;
  public const int BUTTON_RELEASE_MASK = 1<<3;
  public const int ENTER_WINDOW_MASK = 1<<4;
  public const int LEAVE_WINDOW_MASK = 1<<5;
  public const int POINTER_MOTION_MASK = 1<<6;
  public const int POINTER_MOTION_HINT_MASK = 1<<7;
  public const int BUTTON1_MOTION_MASK = 1<<8;
  public const int BUTTON2_MOTION_MASK = 1<<9;
  public const int BUTTON3_MOTION_MASK = 1<<10;
  public const int BUTTON4_MOTION_MASK = 1<<11;
  public const int BUTTON5_MOTION_MASK = 1<<12;
  public const int BUTTON_MOTION_MASK = 1<<13;
  public const int KEYMAP_STATE_MASK = 1<<14;
  public const int EXPOSURE_MASK = 1<<15;
  public const int VISIBILITY_CHANGE_MASK = 1<<16;
  public const int STRUCTURE_NOTIFY_MASK = 1<<17;
  public const int RESIZE_REDIRECT_MASK = 1<<18;
  public const int SUBSTRUCTURE_NOTIFY_MASK = 1<<19;
  public const int SUBSTRUCTURE_REDIRECT_MASK = 1<<20;
  public const int FOCUS_CHANGE_MASK = 1<<21;
  public const int PROPERTY_CHANGE_MASK = 1<<22;
  public const int COLORMAP_CHANGE_MASK = 1<<23;
  public const int OWNER_GRAB_BUTTON_MASK = 1<<24;
  public const int LAST_MASK_INDEX = 24;


  public Display display;
  public bool synthetic;
  public int window_offset;


  /** Writing. */
  public Event (Display display, int code, int window_offset) {
    this.display = display;
    this.window_offset = window_offset;

    data = new byte [32];
    data [0] = (byte) code;
  }


  /** Reading. */
  public Event (Display display, byte [] data, int window_offset) :base (data) {
    this.display = display;
    this.window_offset = window_offset;

    synthetic = (this.data [0] & 0x80) != 0;
    this.data [0] &= 0x7f;
  }


  public int code () { return read1 (0); }
  public int seq_no () { return read2 (2); }
  public virtual int time () { return read4 (4); }
  public virtual int window_id () { return read4 (window_offset); }
  public virtual void set_window (Window window) { set_window (window.id); }
  public virtual void set_window (int i) { write4 (window_offset, i); }


  public override String ToString () {
    String class_name = "#" + GetType().ToString();
    String synthetic0 = synthetic ? " (synthetic) " : " ";
    return class_name + " " + code () + synthetic0 + window ();
  }


  public Window window () {
    return (Window) Window.intern (display, window_id ());
  }
}
}
