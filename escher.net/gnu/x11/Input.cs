using System;
namespace gnu.x11 {


/** X keyboard and pointer. */
public class Input {
  // KEYBUTMASK - keyboard button mask
  public const int SHIFT_MASK = 1<<0;
  public const int LOCK_MASK = 1<<1; // cap lock
  public const int CONTROL_MASK = 1<<2;
  public const int MOD1_MASK = 1<<3; // alt key
  public const int MOD2_MASK = 1<<4; // num lock
  public const int MOD3_MASK = 1<<5; // menu key
  public const int MOD4_MASK = 1<<6; // window key
  public const int MOD5_MASK = 1<<7; // scroll lock
  public const int BUTTON1_MASK = 1<<8;
  public const int BUTTON2_MASK = 1<<9;
  public const int BUTTON3_MASK = 1<<10;
  public const int BUTTON4_MASK = 1<<11;
  public const int BUTTON5_MASK = 1<<12;


  // 104 PC keyboard
  public const int META_MASK = MOD1_MASK;
  public const int ALT_MASK = MOD3_MASK;
  public const int SUPER_MASK = MOD4_MASK;


  public const int BUTTON1 = 1;
  public const int BUTTON2 = 2;
  public const int BUTTON3 = 3;
  public const int BUTTON4 = 4;
  public const int BUTTON5 = 5;


  public static readonly int [] LOCK_COMBINATIONS = {
    0, LOCK_MASK, LOCK_MASK|MOD2_MASK, LOCK_MASK|MOD5_MASK, 
    LOCK_MASK|MOD2_MASK|MOD5_MASK, MOD2_MASK, MOD2_MASK|MOD5_MASK,
    MOD5_MASK
  };


  public Display display;
  public int min_keycode, max_keycode, keysyms_per_keycode;
  public int [] keysyms;
  

  public Input (Display display, int min_keycode, int max_keycode) {
    this.display = display;
    this.min_keycode = min_keycode;
    this.max_keycode = max_keycode;
  }


  // opcode 27 - ungrab pointer
  /**
   * @param time possible: {@link Display#CURRENT_TIME}
   * @see <a href="XUngrabPointer.html">XUngrabPointer</a>
   */
  public void ungrab_pointer (int time) {
    Request request = new Request (display, 27, 2);
    request.write4 (time);
    display.send_request (request);
  }


  // opcode 30 - change active pointer grab
  /**
   * @param cursor possible: {@link Cursor#NONE}
   * @param time possible: {@link Display#CURRENT_TIME}
   * @see <a href="XChangeActivePointerGrab.html">
   *  XChangeActivePointerGrab</a>
   */
  public void change_active_pointer_grab (int event_mask, 
    Cursor cursor, int time) {

    Request request = new Request (display, 30, 4);
    request.write4 (cursor.id);
    request.write4 (time);
    request.write2 (event_mask);
    display.send_request (request);    
  }


  // opcode 32 - ungrab keyboard
  /**
   * @param time possible: {@link Display#CURRENT_TIME}
   * @see <a href="XUngrabKeyboard.html">XUngrabKeyboard</a>
   */
  public void ungrab_keyboard (int time) {
    Request request = new Request (display, 32, 2);
    request.write4 (time);
    display.send_request (request);
  }


  public const int ASYNC_POINTER = 0;
  public const int SYNC_POINTER = 1;
  public const int REPLY_POINTER = 2;
  public const int ASYNC_KEYBOARD = 3;
  public const int SYNC_KEYBOARD = 4;
  public const int REPLY_KEYBOARD = 5;
  public const int ASYNC_BOTH = 6;
  public const int SYNC_BOTH = 7;


  // opcode 35 - allow events
  /**
   * @param mode valid:
   * {@link #ASYNC_POINTER},
   * {@link #SYNC_POINTER},
   * {@link #REPLY_POINTER},
   * {@link #ASYNC_KEYBOARD},
   * {@link #SYNC_KEYBOARD},
   * {@link #REPLY_KEYBOARD},
   * {@link #ASYNC_BOTH},
   * {@link #SYNC_BOTH}
   *
   * @param time possible: {@link Display#CURRENT_TIME}
   * @see <a href="XAllowEvents.html">XAllowEvents</a>
   */
  public void allow_events (int mode, int time) {
    Request request = new Request (display, 35, mode, 2);
    request.write4 (time);
    display.send_request (request);
  }


  /** Reply of {@link #input_focus()} */
  public /*static*/ class InputFocusReply : Data {
    public Display display;

    public InputFocusReply (Display display, Data data)
      : base (data) {
      this.display = display;
    }
  
  
    /**
     * @return possible:
     * {@link Window#NONE},
     * {@link Window#POINTER_ROOT}
     */
    public int focus_id () { return read4 (8); }
  
  
    public Window focus () { 
      return (Window) Window.intern (this.display, focus_id ()); 
    }
  
  
    /** 
     * @return valid:
     * {@link Window#TO_NONE},
     * {@link Window#TO_POINTER_ROOT},
     * {@link Window#TO_PARENT}
     */
    public int revert_to () { return read1 (1); }
  }
  
  
  // opcode 43 - get input focus
  /**
   * @see <a href="XGetInputFocus.html">XGetInputFocus</a>
   */
  public InputFocusReply input_focus () {
    Request request = new Request (display, 43, 1);
    return new InputFocusReply (display, display.read_reply (request));
  }


  // opcode 44 - query keymap
  /**
   * @return valid: {@link Enum#next1()}
   * @see <a href="XQueryKeymap.html">XQueryKeymap</a>
   */
  public Enum keymap () {
    Request request = new Request (display, 44, 1);
    return new Enum (display.read_reply (request), 8, 32);
  }


  // opcode 100 - change keyboard mapping  
  /**
   * @see <a href="XChangeKeyboardMapping.html">XChangeKeyboardMapping</a>
   */
  public void change_keyboard_mapping (int first_keycode, 
    int keysyms_per_keycode, int [] keysyms) {
    
    int keycode_count = keysyms.Length / keysyms_per_keycode;

    Request request = new Request (display, 100, keycode_count, 2+keysyms.Length);
    request.write1 (first_keycode);
    request.write1 (keysyms_per_keycode);
    request.write2_unused ();

    for (int i=0; i<keysyms.Length; i++)
      request.write4 (keysyms [i]);

    display.send_request (request);
  }


  // opcode 101 - get keyboard mapping  
  /**
   * @see <a href="XGetKeyboardMapping.html">XGetKeyboardMapping</a>
   */
  public void keyboard_mapping () {
    int keysym_count = max_keycode - min_keycode + 1;

    Request request = new Request (display, 101, 2);
    request.write1 (min_keycode);
    request.write1 (keysym_count);
    Data reply = display.read_reply (request);

    keysyms_per_keycode = reply.read1 (1);
    keysyms = new int [keysym_count];

    for (int i=0; i<keysym_count; i++)
      keysyms [i] = reply.read4 (32 + 4 * i * keysyms_per_keycode);
  }


  /** Reply of {@link #keyboard_control()} */
  public /*static*/ class KeyboardControlReply : Data {
    public KeyboardControlReply (Data data) : base (data) {}
    public int led_mask () { return read4 (8); }
    public int key_click_percent () { return read1 (12); }
    public int bell_percent () { return read1 (13); }
    public int bell_pitch () { return read2 (14); }
    public int bell_duration () { return read2 (16); }
  
    
    /**
     * @return valid:
     * {@link Input.KeyboardControl#OFF},
     * {@link Input.KeyboardControl#ON}
     */
    public int global_auto_repeat () { return read1 (1); }
  
  
    /**
     * @return valid: {@link Enum#next1()}
     */
    public Enum auto_repeats () {
      return new Enum (this, 20, 32);
    }
  
  
    public override String ToString () {
      return "#KeyboardControlReply"
        + "\n  global-auto-repeat: " 
        + KeyboardControl.GLOBAL_AUTO_REPEAT_STRINGS [global_auto_repeat ()]
        + "\n  led-mask: " + gnu.util.Misc.toBinaryString (led_mask ())
        + "\n  key-click-percent: " + key_click_percent ()
        + "\n  bell-percent: " + bell_percent ()
        + "\n  bell-pitch: " + bell_pitch ()
        + "\n  bell-duration: " + bell_duration ();
    }
  }
  
  
  /** X keyboard control. */
  public /*static*/ class KeyboardControl : ValueList { // TODO
    public KeyboardControl () : base (8) {}
  
  
    public const int OFF = 0;
    public const int ON = 1;
  
  
    public static readonly String [] GLOBAL_AUTO_REPEAT_STRINGS
      = {"off", "on"};
  }


  // opcode 102 - change keyboard control
  /**
   * @see <a href="XChangeKeyboardControl.html">XChangeKeyboardControl</a>
   */
  public void change_keyboard_control (KeyboardControl control) {
    display.send_request (new Request.ValueList (
      display, 102, 2, 0, control));
  }


  // opcode 103 - get keyboard control
  /**
   * @see <a href="XGetKeyboardControl.html">XGetKeyboardControl</a>
   */
  public KeyboardControlReply keyboard_control () {
    Request request = new Request (display, 103, 1);    
    return new KeyboardControlReply (display.read_reply (request));
  }


  // opcode 105 - change pointer control
  /**
   * @see <a href="XChangePointerControl.html">XChangePointerControl</a>
   */
  public void change_pointer_control (bool do_accel, 
    bool do_threshold, int accel_numerator, int accel_denominator,
    int threshold) {

    Request request = new Request (display, 105, 3);
    request.write2 (accel_numerator);
    request.write2 (accel_denominator);
    request.write2 (threshold);
    request.write1 (do_accel);
    request.write1 (do_threshold);
    display.send_request (request);
  }


  /** Reply of {@link #pointer_control()}. */
  public /*static*/ class PointerControlReply : Data {
    public PointerControlReply (Data data) : base (data) {}
    public int acceleration_numerator () { return read2 (8); }
    public int acceleration_denumerator () { return read2 (10); }
    public int threshold () { return read2 (12); }
  
  
    public override String ToString () {
      return "#PointerControlReply"
        + "\n  acceleration: " 
        + acceleration_numerator () + "/" + acceleration_denumerator ()
        + "\n  threshold: " + threshold ();
    }
  }
  
  
  // opcode 106 - get pointer control
  /**
   * @see <a href="XGetPointerControl.html">XGetPointerControl</a>
   */
  public PointerControlReply pointer_control () {
    Request request = new Request (display, 106, 1);    
    return new PointerControlReply (display.read_reply (request));
  }


  public const int SUCCESS = 0;
  public const int BUSY = 1;


  // opcode 116 - set pointer mapping
  /**
   * @return valid:
   * {@link #SUCCESS},
   * {@link #BUSY}
   *
   * @see <a href="XSetPointerMapping.html">XSetPointerMapping</a>
   */
  public int set_pointer_mapping (byte [] map) {
    Request request = new Request (display, 116, map.Length, 2+Data.unit (map));
    request.write1 (map);
    return display.read_reply (request).read1 (1);
  }


  // opcode 117 - get pointer mapping
  /**
   * @see <a href="XGetPointerMapping.html">XGetPointerMapping</a>
   */
  public Data pointer_mapping () {
    Request request = new Request (display, 117, 1);
    return display.read_reply (request);
  }


  public const int FAILED = 2;


  // opcode 118 - set modifier mapping
  /**
   * @return valid:
   * {@link #SUCCESS},
   * {@link #BUSY},
   * {@link #FAILED}
   *
   * @see <a href="XSetModifierMapping.html">XSetModifierMapping</a>
   */
  public int set_modifier_mapping (int keycodes_per_modifier, 
    byte [] keycodes) {

    Request request = new Request (display, 118, keycodes_per_modifier, 
      1+Data.unit (keycodes));
    
    request.write1 (keycodes);
    return display.read_reply (request).read1 (1);
  }


  // opcode 119 - get modifier mapping
  /**
   * @return valid: {@link Enum#next1()}
   * @see <a href="XModifierKeymap.html">XModifierKeymap</a>
   */
  public Enum modifier_mapping () {
    Request request = new Request (display, 119, 1);

    Data reply = display.read_reply (request);
    return new Enum (reply, 32, reply.read1 (1));
  }


  public static readonly String [] KEYBUT_STRINGS = {
    "shift", "lock", "control", "mod1", "mod2", "mod3", "mod4", "mod5",
    "button1", "button2", "button3", "button4", "button5"
  };


  public static void dump_keybut_mask (int m) {
    for (int i=0; i<KEYBUT_STRINGS.Length; i++)
      if (((m & 0x1fff) & 1 << i) != 0)
	Console.Write (KEYBUT_STRINGS [i] + " ");
  }


  /** Convert a keysym of uppercase to lowercase. */
  private int lower (int keysym) {
    if (keysym >= 'A' && keysym <= 'Z')
      return keysym - 'A' + 'a';
    else
      return keysym;
  }
    

  /** Convert a keysym of lowercase to uppercase. */
  private int upper (int keysym) {
    if (keysym >= 'a' && keysym <= 'z')
      return keysym - 'a' + 'A';
    else
      return keysym;
  }


  public int keycode_to_keysym (int keycode, int keystate) {
    if (keycode > max_keycode) 
      throw new Error ("Invalid keycode: " + keycode);

    int keysym = keysyms [keycode - min_keycode];
    bool shift_down_p = (keystate & Input.SHIFT_MASK) != 0;

    /* We cannot guarantee keysyms returned by `keyboard_mapping()' from
     * server is in lowercase or uppercase. XFree86 returns lowercase while
     * Solaris uppercase.
     */    
    if (shift_down_p) 
      return upper (keysym);
    else
      return lower (keysym);
  }


  public int keysym_to_keycode (int keysym) {
    // linear lookup - expensive?
    //for (int i=0; i<keysyms.Length; i++)
    // FIXME, hacked to do it in reverse order for solaris

    for (int i=keysyms.Length-1; i>=0; i--)
      if (keysyms [i] == keysym)
	return i + min_keycode;
    
    throw new Error ("Invalid keysym: " + keysym);	
  }


  /** 
   * Input#ungrab_keyboard(int)
   */
  public void ungrab_keyboard () {
    ungrab_keyboard (Display.CURRENT_TIME);
  }
}

}
