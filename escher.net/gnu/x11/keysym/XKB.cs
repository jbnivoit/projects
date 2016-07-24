namespace gnu.x11.keysym {


/**
 * ISO 9995-specific keyboard symbols. Imported from
 * <code>XK_XKB_KEYS</code> section of
 * <code>/usr/include/X11/keysymdef.h</code>. 
 * Note that byte 3 = 0xfe.
 */
public class XKB {
  public const int LOCK = 0xfe01;
  public const int LEVEL2_LATCH = 0xfe02;
  public const int LEVEL3_SHIFT = 0xfe03;
  public const int LEVEL3_LATCH = 0xfe04;
  public const int LEVEL3_LOCK = 0xfe05;
  public const int GROUP_SHIFT = 0xff7e; /* alias for mode_switch */
  public const int GROUP_LATCH = 0xfe06;
  public const int GROUP_LOCK = 0xfe07;
  public const int NEXT_GROUP = 0xfe08;
  public const int NEXT_GROUP_LOCK = 0xfe09;
  public const int PREV_GROUP = 0xfe0a;
  public const int PREV_GROUP_LOCK = 0xfe0b;
  public const int FIRST_GROUP = 0xfe0c;
  public const int FIRST_GROUP_LOCK = 0xfe0d;
  public const int LAST_GROUP = 0xfe0e;
  public const int LAST_GROUP_LOCK = 0xfe0f;

  public const int LEFT_TAB = 0xfe20;
  public const int MOVE_LINE_UP = 0xfe21;
  public const int MOVE_LINE_DOWN = 0xfe22;
  public const int PARTIAL_LINE_UP = 0xfe23;
  public const int PARTIAL_LINE_DOWN = 0xfe24;
  public const int PARTIAL_SPACE_LEFT = 0xfe25;
  public const int PARTIAL_SPACE_RIGHT = 0xfe26;
  public const int SET_MARGIN_LEFT = 0xfe27;
  public const int SET_MARGIN_RIGHT = 0xfe28;
  public const int RELEASE_MARGIN_LEFT = 0xfe29;
  public const int RELEASE_MARGIN_RIGHT = 0xfe2a;
  public const int RELEASE_BOTH_MARGINS = 0xfe2b;
  public const int FAST_CURSOR_LEFT = 0xfe2c;
  public const int FAST_CURSOR_RIGHT = 0xfe2d;
  public const int FAST_CURSOR_UP = 0xfe2e;
  public const int FAST_CURSOR_DOWN = 0xfe2f;
  public const int CONTINUOUS_UNDERLINE = 0xfe30;
  public const int DISCONTINUOUS_UNDERLINE = 0xfe31;
  public const int EMPHASIZE = 0xfe32;
  public const int CENTER_OBJECT = 0xfe33;
  public const int ENTER = 0xfe34;

  public const int DEAD_GRAVE = 0xfe50;
  public const int DEAD_ACUTE = 0xfe51;
  public const int DEAD_CIRCUMFLEX = 0xfe52;
  public const int DEAD_TILDE = 0xfe53;
  public const int DEAD_MACRON = 0xfe54;
  public const int DEAD_BREVE = 0xfe55;
  public const int DEAD_ABOVEDOT = 0xfe56;
  public const int DEAD_DIAERESIS = 0xfe57;
  public const int DEAD_ABOVERING = 0xfe58;
  public const int DEAD_DOUBLEACUTE = 0xfe59;
  public const int DEAD_CARON = 0xfe5a;
  public const int DEAD_CEDILLA = 0xfe5b;
  public const int DEAD_OGONEK = 0xfe5c;
  public const int DEAD_IOTA = 0xfe5d;
  public const int DEAD_VOICED_SOUND = 0xfe5e;
  public const int DEAD_SEMIVOICED_SOUND = 0xfe5f;
  public const int DEAD_BELOWDOT = 0xfe60;
  public const int DEAD_HOOK = 0xfe61;
  public const int DEAD_HORN = 0xfe62;

  public const int FIRST_VIRTUAL_SCREEN = 0xfed0;
  public const int PREV_VIRTUAL_SCREEN = 0xfed1;
  public const int NEXT_VIRTUAL_SCREEN = 0xfed2;
  public const int LAST_VIRTUAL_SCREEN = 0xfed4;
  public const int TERMINATE_SERVER = 0xfed5;

  public const int ACCESS_X_ENABLE = 0xfe70;
  public const int ACCESS_X_FEEDBACK_ENABLE = 0xfe71;
  public const int REPEAT_KEYS_ENABLE = 0xfe72;
  public const int SLOW_KEYS_ENABLE = 0xfe73;
  public const int BOUNCE_KEYS_ENABLE = 0xfe74;
  public const int STICKY_KEYS_ENABLE = 0xfe75;
  public const int MOUSE_KEYS_ENABLE = 0xfe76;
  public const int MOUSE_KEYS_ACCEL_ENABLE = 0xfe77;
  public const int OVERLAY1_ENABLE = 0xfe78;
  public const int OVERLAY2_ENABLE = 0xfe79;
  public const int AUDIBLE_BELL_ENABLE = 0xfe7a;

  public const int POINTER_LEFT = 0xfee0;
  public const int POINTER_RIGHT = 0xfee1;
  public const int POINTER_UP = 0xfee2;
  public const int POINTER_DOWN = 0xfee3;
  public const int POINTER_UP_LEFT = 0xfee4;
  public const int POINTER_UP_RIGHT = 0xfee5;
  public const int POINTER_DOWN_LEFT = 0xfee6;
  public const int POINTER_DOWN_RIGHT = 0xfee7;
  public const int POINTER_BUTTON_DFLT = 0xfee8;
  public const int POINTER_BUTTON1 = 0xfee9;
  public const int POINTER_BUTTON2 = 0xfeea;
  public const int POINTER_BUTTON3 = 0xfeeb;
  public const int POINTER_BUTTON4 = 0xfeec;
  public const int POINTER_BUTTON5 = 0xfeed;
  public const int POINTER_DBL_CLICK_DFLT = 0xfeee;
  public const int POINTER_DBL_CLICK1 = 0xfeef;
  public const int POINTER_DBL_CLICK2 = 0xfef0;
  public const int POINTER_DBL_CLICK3 = 0xfef1;
  public const int POINTER_DBL_CLICK4 = 0xfef2;
  public const int POINTER_DBL_CLICK5 = 0xfef3;
  public const int POINTER_DRAG_DFLT = 0xfef4;
  public const int POINTER_DRAG1 = 0xfef5;
  public const int POINTER_DRAG2 = 0xfef6;
  public const int POINTER_DRAG3 = 0xfef7;
  public const int POINTER_DRAG4 = 0xfef8;
  public const int POINTER_DRAG5 = 0xfefd;

  public const int POINTER_ENABLE_KEYS = 0xfef9;
  public const int POINTER_ACCELERATE = 0xfefa;
  public const int POINTER_DFLT_BTN_NEXT = 0xfefb;
  public const int POINTER_DFLT_BTN_PREV = 0xfefc;
}

}
