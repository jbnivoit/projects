namespace gnu.x11.keysym {


/**
 * Sun-specific keyboard symbols. Imported from
 * <code>/usr/include/X11/Sunkeysym.h</code>.
 */
public class Sun {
  /* Floating Accent. */

  public const int FA_GRAVE = 0x1005ff00;
  public const int FA_CIRCUM = 0x1005ff01;
  public const int FA_TILDE = 0x1005ff02;
  public const int FA_ACUTE = 0x1005ff03;
  public const int FA_DIAERESIS = 0x1005ff04;
  public const int FA_CEDILLA = 0x1005ff05;

  
  /* Miscellaneous Functions. */

  public const int F36 = 0x1005ff10; /* labeled f11 */
  public const int F37 = 0x1005ff11; /* labeled f12 */

  
  /* International & Multi-Key Character Composition. */

  public const int SYS_REQ = 0x1005ff60;
  public const int PRINT_SCREEN = 0x0000ff61; /* same as xk_print */
  public const int COMPOSE = 0x0000ff20; /* same as xk_multi_key */
  public const int ALT_GRAPH = 0x0000ff7e; /* same as xk_mode_switch */


  /* Cursor Control. */ 

  public const int PAGE_UP = 0x0000ff55; /* same as xk_prior */
  public const int PAGE_DOWN = 0x0000ff56; /* same as xk_next */


  /* Open Look Functions. */

  public const int UNDO = 0x0000ff65; /* same as xk_undo */
  public const int AGAIN = 0x0000ff66; /* same as xk_redo */
  public const int FIND = 0x0000ff68; /* same as xk_find */
  public const int STOP = 0x0000ff69; /* same as xk_cancel */
  public const int PROPS = 0x1005ff70;
  public const int FRONT = 0x1005ff71;
  public const int COPY = 0x1005ff72;
  public const int OPEN = 0x1005ff73;
  public const int PASTE = 0x1005ff74;
  public const int CUT = 0x1005ff75;
  public const int POWER_SWITCH = 0x1005ff76;
  public const int AUDIO_LOWER_VOLUME = 0x1005ff77;
  public const int AUDIO_MUTE = 0x1005ff78;
  public const int AUDIO_RAISE_VOLUME = 0x1005ff79;
  public const int VIDEO_DEGAUSS = 0x1005ff7a;
  public const int VIDEO_LOWER_BRIGHTNESS = 0x1005ff7b;
  public const int VIDEO_RAISE_BRIGHTNESS = 0x1005ff7c;
  public const int POWER_SWITCH_SHIFT = 0x1005ff7d;
}

}
