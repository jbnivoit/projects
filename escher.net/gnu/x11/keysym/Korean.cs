namespace gnu.x11.keysym {


/**
 * Korean-specific keyboard symbols. Imported from
 * <code>XK_KOREAN</code> section of
 * <code>/usr/include/X11/keysymdef.h</code>. Note that byte 3 = 0x0e.
 */
public class Korean {
  public const int TOGGLE = 0xff31; /* hangul start/stop(toggle) */
  public const int START = 0xff32; /* hangul start */
  public const int END = 0xff33; /* hangul end, english start */
  public const int HANJA = 0xff34; /* start hangul->hanja conversion */
  public const int JAMO = 0xff35; /* hangul jamo mode */
  public const int ROMAJA = 0xff36; /* hangul romaja mode */
  public const int CODEINPUT = 0xff37; /* hangul code input mode */
  public const int JEONJA = 0xff38; /* jeonja mode */
  public const int BANJA = 0xff39; /* banja mode */
  public const int PRE_HANJA = 0xff3a; /* pre hanja conversion */
  public const int POST_HANJA = 0xff3b; /* post hanja conversion */
  public const int SINGLE_CANDIDATE = 0xff3c; /* single candidate */
  public const int MULTIPLE_CANDIDATE = 0xff3d; /* multiple candidate */
  public const int PREVIOUS_CANDIDATE = 0xff3e; /* previous candidate */
  public const int SPECIAL = 0xff3f; /* special symbols */
  public const int SWITCH = 0xff7e; /* alias for mode_switch */


  /* Hangul Consonant Characters. */

  public const int KIYEOG = 0xea1;
  public const int SSANG_KIYEOG = 0xea2;
  public const int KIYEOG_SIOS = 0xea3;
  public const int NIEUN = 0xea4;
  public const int NIEUN_JIEUJ = 0xea5;
  public const int NIEUN_HIEUH = 0xea6;
  public const int DIKEUD = 0xea7;
  public const int SSANG_DIKEUD = 0xea8;
  public const int RIEUL = 0xea9;
  public const int RIEUL_KIYEOG = 0xeaa;
  public const int RIEUL_MIEUM = 0xeab;
  public const int RIEUL_PIEUB = 0xeac;
  public const int RIEUL_SIOS = 0xead;
  public const int RIEUL_TIEUT = 0xeae;
  public const int RIEUL_PHIEUF = 0xeaf;
  public const int RIEUL_HIEUH = 0xeb0;
  public const int MIEUM = 0xeb1;
  public const int PIEUB = 0xeb2;
  public const int SSANG_PIEUB = 0xeb3;
  public const int PIEUB_SIOS = 0xeb4;
  public const int SIOS = 0xeb5;
  public const int SSANG_SIOS = 0xeb6;
  public const int IEUNG = 0xeb7;
  public const int JIEUJ = 0xeb8;
  public const int SSANG_JIEUJ = 0xeb9;
  public const int CIEUC = 0xeba;
  public const int KHIEUQ = 0xebb;
  public const int TIEUT = 0xebc;
  public const int PHIEUF = 0xebd;
  public const int HIEUH = 0xebe;


  /* Hangul Vowel Characters. */

  public const int A = 0xebf;
  public const int AE = 0xec0;
  public const int YA = 0xec1;
  public const int YAE = 0xec2;
  public const int EO = 0xec3;
  public const int E = 0xec4;
  public const int YEO = 0xec5;
  public const int YE = 0xec6;
  public const int O = 0xec7;
  public const int WA = 0xec8;
  public const int WAE = 0xec9;
  public const int OE = 0xeca;
  public const int YO = 0xecb;
  public const int U = 0xecc;
  public const int WEO = 0xecd;
  public const int WE = 0xece;
  public const int WI = 0xecf;
  public const int YU = 0xed0;
  public const int EU = 0xed1;
  public const int YI = 0xed2;
  public const int I = 0xed3;


  /* Hangul syllable-final (JongSeong) Characters. */

  public const int J_KIYEOG = 0xed4;
  public const int J_SSANG_KIYEOG = 0xed5;
  public const int J_KIYEOG_SIOS = 0xed6;
  public const int J_NIEUN = 0xed7;
  public const int J_NIEUN_JIEUJ = 0xed8;
  public const int J_NIEUN_HIEUH = 0xed9;
  public const int J_DIKEUD = 0xeda;
  public const int J_RIEUL = 0xedb;
  public const int J_RIEUL_KIYEOG = 0xedc;
  public const int J_RIEUL_MIEUM = 0xedd;
  public const int J_RIEUL_PIEUB = 0xede;
  public const int J_RIEUL_SIOS = 0xedf;
  public const int J_RIEUL_TIEUT = 0xee0;
  public const int J_RIEUL_PHIEUF = 0xee1;
  public const int J_RIEUL_HIEUH = 0xee2;
  public const int J_MIEUM = 0xee3;
  public const int J_PIEUB = 0xee4;
  public const int J_PIEUB_SIOS = 0xee5;
  public const int J_SIOS = 0xee6;
  public const int J_SSANG_SIOS = 0xee7;
  public const int J_IEUNG = 0xee8;
  public const int J_JIEUJ = 0xee9;
  public const int J_CIEUC = 0xeea;
  public const int J_KHIEUQ = 0xeeb;
  public const int J_TIEUT = 0xeec;
  public const int J_PHIEUF = 0xeed;
  public const int J_HIEUH = 0xeee;

  
  /* Ancient Hangul Consonant Characters. */

  public const int RIEUL_YEORIN_HIEUH = 0xeef;
  public const int SUNKYEONGEUM_MIEUM = 0xef0;
  public const int SUNKYEONGEUM_PIEUB = 0xef1;
  public const int PAN_SIOS = 0xef2;
  public const int KKOGJI_DALRIN_IEUNG = 0xef3;
  public const int SUNKYEONGEUM_PHIEUF = 0xef4;
  public const int YEORIN_HIEUH = 0xef5;


  /* Ancient Hangul Vowel Characters. */

  public const int ARAEA = 0xef6;
  public const int ARAEAE = 0xef7;


  /* Ancient Hangul syllable-final (JongSeong) Characters. */

  public const int J_PAN_SIOS = 0xef8;
  public const int J_KKOGJI_DALRIN_IEUNG = 0xef9;
  public const int J_YEORIN_HIEUH = 0xefa;


  /* Korean currency symbol. */  
  public const int WON = 0xeff;
}

}
