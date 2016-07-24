namespace gnu.x11.keysym {


/**
 * Caucasus-specific keyboard symbols. Imported from
 * <code>XK_CAUCASUS</code> section of
 * <code>/usr/include/X11/keysymdef.h</code>. Note that byte 3 = 0x16. 
 */
public class Caucasus {
  /* Azeri (and other Turkic or Caucasian languages of ex-USSR). */

  public const int CCEDILLAABOVEDOT = 0x16a2;
  public const int XABOVEDOT = 0x16a3;
  public const int QABOVEDOT = 0x16a5;
  public const int IBREVE = 0x16a6;
  public const int IE = 0x16a7;
  public const int UO = 0x16a8;
  public const int ZSTROKE = 0x16a9;
  public const int GCARON = 0x16aa;
  public const int OBARRED = 0x16af;

  public const int CCEDILLAABOVEDOT_SMALL = 0x16b2;
  public const int XABOVEDOT_SMALL = 0x16b3;

  public const int OCARON = 0x16b4;

  public const int QABOVEDOT_SMALL = 0x16b5;
  public const int IBREVE_SMALL = 0x16b6;
  public const int IE_SMALL = 0x16b7;
  public const int UO_SMALL = 0x16b8;
  public const int ZSTROKE_SMALL = 0x16b9;
  public const int GCARON_SMALL = 0x16ba;
  public const int OCARON_SMALL = 0x16bd;
  public const int OBARRED_SMALL = 0x16bf;

  public const int SCHWA = 0x16c6;
  public const int SCHWA_SMALL = 0x16f6;


  /* Inupiak (not really Caucasus). */

  public const int LBELOWDOT = 0x16d1;
  public const int LSTROKEBELOWDOT = 0x16d2;
  public const int LBELOWDOT_SMALL = 0x16e1;
  public const int LSTROKEBELOWDOT_SMALL = 0x16e2;


  /* Guarani (not really Caucasus). */

  public const int GTILDE = 0x16d3;
  public const int GTILDE_SMALL = 0x16e3;
}

}
