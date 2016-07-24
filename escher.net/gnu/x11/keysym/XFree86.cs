namespace gnu.x11.keysym {


/**
 * XFree86-specific keyboard symbols. Imported from
 * <code>/usr/include/X11/XF86keysym.h</code>.
 */
public class XFree86 {
  /* ModeLock. This one is old, and not really used any more since XKB
   * offers this functionality.
   */

  public const int MODE_LOCK = 0x1008ff01; /* mode switch lock */

  
  /* "Internet" keyboards. */

  public const int STANDBY = 0x1008ff10;
  public const int AUDIO_LOWER_VOLUME = 0x1008ff11;
  public const int AUDIO_MUTE = 0x1008ff12;
  public const int AUDIO_RAISE_VOLUME = 0x1008ff13;
  public const int AUDIO_PLAY = 0x1008ff14;
  public const int AUDIO_STOP = 0x1008ff15;
  public const int AUDIO_PREV = 0x1008ff16;
  public const int AUDIO_NEXT = 0x1008ff17;
  public const int HOME_PAGE = 0x1008ff18;
  public const int MAIL = 0x1008ff19;
  public const int START = 0x1008ff1a;
  public const int SEARCH = 0x1008ff1b;
  public const int AUDIO_RECORD = 0x1008ff1c;


  /* PDA's (e.g. Palm, PocketPC or elsewhere). */

  public const int CALCULATOR = 0x1008ff1d;
  public const int MEMO = 0x1008ff1e;
  public const int TO_DO_LIST = 0x1008ff1f;
  public const int CALENDAR = 0x1008ff20;
  public const int POWER_DOWN = 0x1008ff21;
  public const int CONTRASTADJUST = 0x1008ff22;
  public const int ROCKER_UP = 0x1008ff23;
  public const int ROCKER_DOWN = 0x1008ff24;
  public const int ROCKER_ENTER = 0x1008ff25;
  public const int BACK = 0x1008ff26;
  public const int FORWARD = 0x1008ff27;
  public const int STOP = 0x1008ff28;
  public const int REFRESH = 0x1008ff29;
  public const int POWER_OFF = 0x1008ff1a;
  public const int WAKE_UP = 0x1008ff1b;


  /* Note, 0x1008ff02 - 0x1008ff0f are free and should be used for misc new
   * keysyms that don't fit into any of the groups below.
   */

  
  /* Misc. */

  public const int FAVORITES = 0x1008ff30;
  public const int AUDIO_PAUSE = 0x1008ff31;
  public const int AUDIO_MEDIA = 0x1008ff32;
  public const int MY_COMPUTER = 0x1008ff33;
  public const int VENDOR_HOME = 0x1008ff34;
  public const int LIGHT_BULB = 0x1008ff35;
  public const int SHOP = 0x1008ff36;  
}

}
