namespace gnu.x11 {


/** X cursor. */
public class Cursor : Resource {
  /** 
   * Predefined cursor.
   *
   * @see Window#NONE
   */
  public static readonly Cursor NONE = new Cursor (0);
  public static readonly Cursor CURRENT = new Cursor (1);


  // cursor shapes
  public const int X_CURSOR = 0;
  public const int ARROW = 2;
  public const int BASED_ARROW_DOWN = 4;
  public const int BASED_ARROW_UP = 6;
  public const int BOAT = 8;
  public const int BOGOSITY = 10;
  public const int BOTTOM_LEFT_CORNER = 12;
  public const int BOTTOM_RIGHT_CORNER = 14;
  public const int BOTTOM_SIDE = 16;
  public const int BOTTOM_TEE = 18;
  public const int BOX_SPIRAL = 20;
  public const int CENTER_PTR = 22;
  public const int CIRCLE = 24;
  public const int CLOCK = 26;
  public const int COFFEE_MUG = 28;
  public const int CROSS = 30;
  public const int CROSS_REVERSE = 32;
  public const int CROSSHAIR = 34;
  public const int DIAMOND_CROSS = 36;
  public const int DOT = 38;
  public const int DOTBOX = 40;
  public const int DOUBLE_ARROW = 42;
  public const int DRAFT_LARGE = 44;
  public const int DRAFT_SMALL = 46;
  public const int DRAPED_BOX = 48;
  public const int EXCHANGE = 50;
  public const int FLEUR = 52;
  public const int GOBBLER = 54;
  public const int GUMBY = 56;
  public const int HAND1 = 58;
  public const int HAND2 = 60;
  public const int HEART = 62;
  public const int ICON = 64;
  public const int IRON_CROSS = 66;
  public const int LEFT_PTR = 68;
  public const int LEFT_SIDE = 70;
  public const int LEFT_TEE = 72;
  public const int LEFTBUTTON = 74;
  public const int LL_ANGLE = 76;
  public const int LR_ANGLE = 78;
  public const int MAN = 80;
  public const int MIDDLEBUTTON = 82;
  public const int MOUSE = 84;
  public const int PENCIL = 86;
  public const int PIRATE = 88;
  public const int PLUS = 90;
  public const int QUESTION_ARROW = 92;
  public const int RIGHT_PTR = 94;
  public const int RIGHT_SIDE = 96;
  public const int RIGHT_TEE = 98;
  public const int RIGHTBUTTON = 100;
  public const int RTL_LOGO = 102;
  public const int SAILBOAT = 104;
  public const int SB_DOWN_ARROW = 106;
  public const int SB_H_DOUBLE_ARROW = 108;
  public const int SB_LEFT_ARROW = 110;
  public const int SB_RIGHT_ARROW = 112;
  public const int SB_UP_ARROW = 114;
  public const int SB_V_DOUBLE_ARROW = 116;
  public const int SHUTTLE = 118;
  public const int SIZING = 120;
  public const int SPIDER = 122;
  public const int SPRAYCAN = 124;
  public const int STAR = 126;
  public const int TARGET = 128;
  public const int TCROSS = 130;
  public const int TOP_LEFT_ARROW = 132;
  public const int TOP_LEFT_CORNER = 134;
  public const int TOP_RIGHT_CORNER = 136;
  public const int TOP_SIDE = 138;
  public const int TOP_TEE = 140;
  public const int TREK = 142;
  public const int UL_ANGLE = 144;
  public const int UMBRELLA = 146;
  public const int UR_ANGLE = 148;
  public const int WATCH = 150;
  public const int XTERM = 152;


  // cursor font
  public static Font FONT = null;
  

  /** Predefined. */
  public Cursor (int id) 
    :base (id) {
  }


  /**
   * @see <a href="XCreateFontCursor.html">XCreateFontCursor</a>
   */  
  public Cursor (Display display, int shape) 
    :base (display) {
    
    // X predefined special font
    if (FONT == null) FONT = new Font (display, "cursor");

    /* From <X11/Cursor.c>: The cursor font contains the shape glyph
     * followed by the mask glyph; so character position 0 contains a
     * shape, 1 the mask for 0, 2 a shape, etc.
     */

    // black and white
    create (FONT, FONT, shape, shape+1, 0, 0, 0, 1, 1, 1);
  }


  /**
   * @see <a href="XCreateGlyphCursor.html">XCreateGlyphCursor</a>
   */
  public Cursor (Font src, Font mask, int source_char,  
    int mask_char, int fg_r, int fg_g, int fg_b, 
    int bg_r, int bg_g, int bg_b) : base (src.display) {
    create (src, mask, source_char, mask_char, fg_r, fg_g, fg_b,
      bg_r, bg_g, bg_b);
  }


  // opcode 93 - create cursor
  /**
   * @param mask possible: {@link Pixmap#NONE}
   * @see <a href="XCreatePixmapCursor.html">XCreatePixmapCursor</a>
   */
  public Cursor (Pixmap src, Pixmap mask, int source_char,  
    int mask_char, int fg_r, int fg_g, int fg_b, 
    int bg_r, int bg_g, int bg_b, int x, int y) :base (src.display) {

    Request request = new Request (display, 93, 8);
    request.write4 (id);
    request.write4 (src.id);
    request.write4 (mask.id);
    request.write2 (fg_r);
    request.write2 (fg_g);
    request.write2 (fg_b);
    request.write2 (bg_r);
    request.write2 (bg_g);
    request.write2 (bg_b);
    request.write2 (x);
    request.write2 (y);
    display.send_request (request);    
  }


  // opcode 94 - create glyph cursor
  public void create (Font src, Font mask, int source_char, 
    int mask_char, int fg_r, int fg_g, int fg_b, 
    int bg_r, int bg_g, int bg_b) {

    Request request = new Request (display, 94, 8);
    request.write4 (id);
    request.write4 (src.id);
    request.write4 (mask.id);
    request.write2 (source_char);
    request.write2 (mask_char);
    request.write2 (fg_r);
    request.write2 (fg_g);
    request.write2 (fg_b);
    request.write2 (bg_r);
    request.write2 (bg_g);
    request.write2 (bg_b);
    display.send_request (request);
  }


  // opcode 95 - free cursor
  /**
   * @see <a href="XFreeCursor.html">XFreeCursor</a>
   */
  public void free () {
    Request request = new Request (display, 95, 2);
    request.write4 (id);
    display.send_request (request);
  }


  // opcode 96 - recolor cursor
  /**
   * @see <a href="XRecolorCursor.html">XRecolorCursor</a>
   */
  public void recolor (RGB foreground, RGB background) {
    Request request = new Request (display, 96, 5);
    request.write2 (id);
    request.write2 (foreground.red);
    request.write2 (foreground.green);
    request.write2 (foreground.blue);
    request.write2 (background.red);
    request.write2 (background.green);
    request.write2 (background.blue);
    display.send_request (request);
  }
}
}

