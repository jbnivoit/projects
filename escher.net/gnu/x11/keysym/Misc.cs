namespace gnu.x11.keysym {


/**
 * Miscellaneous keyboard symbols. Imported from <code>XK_MISCELLANY</code>
 * section of <code>/usr/include/X11/keysymdef.h</code>.
 */
public class Misc {
  /* I use the following emacs lisp code together with some other (dirty)
   * keyboard macro hack to convert `/usr/include/X11/*keysym*.h' to java
   * defintions.
   *
   * (defun mixed-case-to-lisp-case (string)
   *   "Convert SomeMixedCaseString to a_more_readable_lisp_case_string.
   * E.g. XK_Armenian_ligature_ew _> xk_armenian_ligature_ew."
   *   (downcase
   *    (char-list-to-string 
   *     (loop
   *       with previous = ? 
   *       for current in (string-to-char-list string)
   *       if (and (lowercasep previous) (uppercasep current))
   *       collect ?_ and collect current
   *       else collect current
   *       do (setq previous current)))))   
   */


  public const int VOID_SYMBOL = 0xffffff;


  /* TTY Functions, cleverly chosen to map to ascii, for convenience of
   * programming, but could have been arbitrary (at the cost of lookup
   * tables in client code).
   */

  public const int BACKSPACE = 0xff08; /* back space, back char */
  public const int TAB = 0xff09;
  public const int LINEFEED = 0xff0a; /* linefeed, LF */
  public const int CLEAR = 0xff0b;
  public const int RETURN = 0xff0d; /* return, enter */
  public const int PAUSE = 0xff13; /* pause, hold */
  public const int SCROLL_LOCK = 0xff14;
  public const int SYS_REQ = 0xff15;
  public const int ESCAPE = 0xff1b;
  public const int DELETE = 0xffff; /* delete, rubout */


  /* International & multi-key character composition. */

  public const int MULTI_KEY = 0xff20; /* multi-key character compose */
  public const int CODEINPUT = 0xff37;
  public const int SINGLE_CANDIDATE = 0xff3c;
  public const int MULTIPLE_CANDIDATE = 0xff3d;
  public const int PREVIOUS_CANDIDATE = 0xff3e;



  /* Japanese keyboard support. 0xff31 thru 0xff3f are under XK_KOREAN. */  
  
  public const int KANJI = 0xff21; /* kanji, kanji convert */
  public const int MUHENKAN = 0xff22; /* cancel conversion */
  public const int HENKAN_MODE = 0xff23; /* start/stop conversion */
  public const int HENKAN = 0xff23; /* alias for henkan_mode */
  public const int ROMAJI = 0xff24; /* to romaji */
  public const int HIRAGANA = 0xff25; /* to hiragana */
  public const int KATAKANA = 0xff26; /* to katakana */
  public const int HIRAGANA_KATAKANA = 0xff27; /* hiragana/katakana toggle */
  public const int ZENKAKU = 0xff28; /* to zenkaku */
  public const int HANKAKU = 0xff29; /* to hankaku */
  public const int ZENKAKU_HANKAKU = 0xff2a; /* zenkaku/hankaku toggle */
  public const int TOUROKU = 0xff2b; /* add to dictionary */
  public const int MASSYO = 0xff2c; /* delete from dictionary */
  public const int KANA_LOCK = 0xff2d; /* kana lock */
  public const int KANA_SHIFT = 0xff2e; /* kana shift */
  public const int EISU_SHIFT = 0xff2f; /* alphanumeric shift */
  public const int EISU_TOGGLE = 0xff30; /* alphanumeric toggle */
  public const int KANJI_BANGOU = 0xff37; /* codeinput */
  public const int ZEN_KOHO = 0xff3d; /* multiple/all candidate(s) */
  public const int MAE_KOHO = 0xff3e; /* previous candidate */


  /** Cursor control & motion. */

  public const int HOME = 0xff50;
  public const int LEFT = 0xff51; /* move left, left arrow */
  public const int UP = 0xff52; /* move up, up arrow */
  public const int RIGHT = 0xff53; /* move right, right arrow */
  public const int DOWN = 0xff54; /* move down, down arrow */
  public const int PRIOR = 0xff55; /* prior, previous */
  public const int PAGE_UP = 0xff55;
  public const int NEXT = 0xff56; /* next */
  public const int PAGE_DOWN = 0xff56;
  public const int END = 0xff57; /* eol */
  public const int BEGIN = 0xff58; /* bol */


  /* Misc Functions. */

  public const int SELECT = 0xff60; /* select, mark */
  public const int PRINT = 0xff61;
  public const int EXECUTE = 0xff62; /* execute, run, do */
  public const int INSERT = 0xff63; /* insert, insert here */
  public const int UNDO = 0xff65; /* undo, oops */
  public const int REDO = 0xff66; /* redo, again */
  public const int MENU = 0xff67;
  public const int FIND = 0xff68; /* find, search */
  public const int CANCEL = 0xff69; /* cancel, stop, abort, exit */
  public const int HELP = 0xff6a; /* help */
  public const int BREAK = 0xff6b;
  public const int MODE_SWITCH = 0xff7e; /* character set switch */
  public const int SCRIPT_SWITCH = 0xff7e; /* alias for mode_switch */
  public const int NUM_LOCK = 0xff7f;


  /* Keypad Functions, keypad numbers cleverly chosen to map to ascii. */

  public const int KP_SPACE = 0xff80; /* space */
  public const int KP_TAB = 0xff89;
  public const int KP_ENTER = 0xff8d; /* enter */
  public const int KP_F1 = 0xff91; /* pf1, kp_a, ... */
  public const int KP_F2 = 0xff92;
  public const int KP_F3 = 0xff93;
  public const int KP_F4 = 0xff94;
  public const int KP_HOME = 0xff95;
  public const int KP_LEFT = 0xff96;
  public const int KP_UP = 0xff97;
  public const int KP_RIGHT = 0xff98;
  public const int KP_DOWN = 0xff99;
  public const int KP_PRIOR = 0xff9a;
  public const int KP_PAGE_UP = 0xff9a;
  public const int KP_NEXT = 0xff9b;
  public const int KP_PAGE_DOWN = 0xff9b;
  public const int KP_END = 0xff9c;
  public const int KP_BEGIN = 0xff9d;
  public const int KP_INSERT = 0xff9e;
  public const int KP_DELETE = 0xff9f;
  public const int KP_EQUAL = 0xffbd; /* Equals */
  public const int KP_MULTIPLY = 0xffaa;
  public const int KP_ADD = 0xffab;
  public const int KP_SEPARATOR = 0xffac; /* separator, often comma */
  public const int KP_SUBTRACT = 0xffad;
  public const int KP_DECIMAL = 0xffae;
  public const int KP_DIVIDE = 0xffaf;

  public const int KP_0 = 0xffb0;
  public const int KP_1 = 0xffb1;
  public const int KP_2 = 0xffb2;
  public const int KP_3 = 0xffb3;
  public const int KP_4 = 0xffb4;
  public const int KP_5 = 0xffb5;
  public const int KP_6 = 0xffb6;
  public const int KP_7 = 0xffb7;
  public const int KP_8 = 0xffb8;
  public const int KP_9 = 0xffb9;



  /* Auxilliary Functions; note the duplicate definitions for left and
   * right function keys; Sun keyboards and a few other manufactures have
   * such function key groups on the left and/or right sides of the
   * keyboard. We've not found a keyboard with more than 35 function keys
   * total.
   */

  public const int F1 = 0xffbe;
  public const int F2 = 0xffbf;
  public const int F3 = 0xffc0;
  public const int F4 = 0xffc1;
  public const int F5 = 0xffc2;
  public const int F6 = 0xffc3;
  public const int F7 = 0xffc4;
  public const int F8 = 0xffc5;
  public const int F9 = 0xffc6;
  public const int F10 = 0xffc7;
  public const int F11 = 0xffc8;
  public const int L1 = 0xffc8;
  public const int F12 = 0xffc9;
  public const int L2 = 0xffc9;
  public const int F13 = 0xffca;
  public const int L3 = 0xffca;
  public const int F14 = 0xffcb;
  public const int L4 = 0xffcb;
  public const int F15 = 0xffcc;
  public const int L5 = 0xffcc;
  public const int F16 = 0xffcd;
  public const int L6 = 0xffcd;
  public const int F17 = 0xffce;
  public const int L7 = 0xffce;
  public const int F18 = 0xffcf;
  public const int L8 = 0xffcf;
  public const int F19 = 0xffd0;
  public const int L9 = 0xffd0;
  public const int F20 = 0xffd1;
  public const int L10 = 0xffd1;
  public const int F21 = 0xffd2;
  public const int R1 = 0xffd2;
  public const int F22 = 0xffd3;
  public const int R2 = 0xffd3;
  public const int F23 = 0xffd4;
  public const int R3 = 0xffd4;
  public const int F24 = 0xffd5;
  public const int R4 = 0xffd5;
  public const int F25 = 0xffd6;
  public const int R5 = 0xffd6;
  public const int F26 = 0xffd7;
  public const int R6 = 0xffd7;
  public const int F27 = 0xffd8;
  public const int R7 = 0xffd8;
  public const int F28 = 0xffd9;
  public const int R8 = 0xffd9;
  public const int F29 = 0xffda;
  public const int R9 = 0xffda;
  public const int F30 = 0xffdb;
  public const int R10 = 0xffdb;
  public const int F31 = 0xffdc;
  public const int R11 = 0xffdc;
  public const int F32 = 0xffdd;
  public const int R12 = 0xffdd;
  public const int F33 = 0xffde;
  public const int R13 = 0xffde;
  public const int F34 = 0xffdf;
  public const int R14 = 0xffdf;
  public const int F35 = 0xffe0;
  public const int R15 = 0xffe0;


  /* Modifiers. */

  public const int SHIFT_L = 0xffe1; /* left shift */
  public const int SHIFT_R = 0xffe2; /* right shift */
  public const int CONTROL_L = 0xffe3; /* left control */
  public const int CONTROL_R = 0xffe4; /* right control */
  public const int CAPS_LOCK = 0xffe5; /* caps lock */
  public const int SHIFT_LOCK = 0xffe6; /* shift lock */

  public const int META_L = 0xffe7; /* left meta */
  public const int META_R = 0xffe8; /* right meta */
  public const int ALT_L = 0xffe9; /* left alt */
  public const int ALT_R = 0xffea; /* right alt */
  public const int SUPER_L = 0xffeb; /* left base */
  public const int SUPER_R = 0xffec; /* right base */
  public const int HYPER_L = 0xffed; /* left hyper */
  public const int HYPER_R = 0xffee; /* right hyper */  
}

}
