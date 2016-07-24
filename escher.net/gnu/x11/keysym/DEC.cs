namespace gnu.x11.keysym {


/**
 * DEC-specific keyboard symbols. Imported from
 * <code>/usr/include/X11/DECkeysym.h</code>. Note that 29th bit is set.
 */
public class DEC {
  /* Two-key compose sequence initiators, chosen to map to Latin1
   * characters.
   */

  public const int RING_ACCENT = 0x1000feb0;
  public const int CIRCUMFLEX_ACCENT = 0x1000fe5e;
  public const int CEDILLA_ACCENT = 0x1000fe2c;
  public const int ACUTE_ACCENT = 0x1000fe27;
  public const int GRAVE_ACCENT = 0x1000fe60;
  public const int TILDE = 0x1000fe7e;
  public const int DIAERESIS = 0x1000fe22;


  /* Special keysym for LK2** "Remove" key on editing keypad. */

  public const int REMOVE = 0x1000ff00;
}

}
