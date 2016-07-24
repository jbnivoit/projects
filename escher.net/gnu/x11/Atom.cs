using System;
using System.Text;

namespace gnu.x11 {


/** X atom. */
public class Atom {
  // predefined atom ids
  public const int ANY_PROPERTY_TYPE_ID = 0;
  public const int PRIMARY_ID = 1;
  public const int SECONDARY_ID = 2;
  public const int ARC_ID = 3;
  public const int ATOM_ID = 4;
  public const int BITMAP_ID = 5;
  public const int CARDINAL_ID = 6;
  public const int COLORMAP_ID = 7;
  public const int CURSOR_ID = 8;
  public const int CUT_BUFFER0_ID = 9;
  public const int CUT_BUFFER1_ID = 10;
  public const int CUT_BUFFER2_ID = 11;
  public const int CUT_BUFFER3_ID = 12;
  public const int CUT_BUFFER4_ID = 13;
  public const int CUT_BUFFER5_ID = 14;
  public const int CUT_BUFFER6_ID = 15;
  public const int CUT_BUFFER7_ID = 16;
  public const int DRAWABLE_ID = 17;
  public const int FONT_ID = 18;
  public const int INTEGER_ID = 19;
  public const int PIXMAP_ID = 20;
  public const int POINT_ID = 21;
  public const int RECTANGLE_ID = 22;
  public const int RESOURCE_MANAGER_ID = 23;
  public const int RGB_COLOR_MAP_ID = 24;
  public const int RGB_BEST_MAP_ID = 25;
  public const int RGB_BLUE_MAP_ID = 26;
  public const int RGB_DEFAULT_MAP_ID = 27;
  public const int RGB_GRAY_MAP_ID = 28;
  public const int RGB_GREEN_MAP_ID = 29;
  public const int RGB_RED_MAP_ID = 30;
  public const int STRING_ID = 31;
  public const int VISUALID_ID = 32;
  public const int WINDOW_ID = 33;
  public const int WM_COMMAND_ID = 34;
  public const int WM_HINTS_ID = 35;
  public const int WM_CLIENT_MACHINE_ID = 36;
  public const int WM_ICON_NAME_ID = 37;
  public const int WM_ICON_SIZE_ID = 38;
  public const int WM_NAME_ID = 39;
  public const int WM_NORMAL_HINTS_ID = 40;
  public const int WM_SIZE_HINTS_ID = 41;
  public const int WM_ZOOM_HINTS_ID = 42;
  public const int MIN_SPACE_ID = 43;
  public const int NORM_SPACE_ID = 44;
  public const int MAX_SPACE_ID = 45;
  public const int END_SPACE_ID = 46;
  public const int SUPERSCRIPT_X_ID = 47;
  public const int SUPERSCRIPT_Y_ID = 48;
  public const int SUBSCRIPT_X_ID = 49;
  public const int SUBSCRIPT_Y_ID = 50;
  public const int UNDERLINE_POSITION_ID = 51;
  public const int UNDERLINE_THICKNESS_ID = 52;
  public const int STRIKEOUT_ASCENT_ID = 53;
  public const int STRIKEOUT_DESCENT_ID = 54;
  public const int ITALIC_ANGLE_ID = 55;
  public const int X_HEIGHT_ID = 56;
  public const int QUAD_WIDTH_ID = 57;
  public const int WEIGHT_ID = 58;
  public const int POINT_SIZE_ID = 59;
  public const int RESOLUTION_ID = 60;
  public const int COPYRIGHT_ID = 61;
  public const int NOTICE_ID = 62;
  public const int FONT_NAME_ID = 63;
  public const int FAMILY_NAME_ID = 64;
  public const int FULL_NAME_ID = 65;
  public const int CAP_HEIGHT_ID = 66;
  public const int WM_CLASS_ID = 67;
  public const int WM_TRANSIENT_FOR_ID = 68;


  /**
   * Predefined atoms. 
   *
   * @see Window#NONE
   */
  public static readonly Atom NONE
    = new Atom (0, "NONE");
  public static readonly Atom ANY_PROPERTY_TYPE 
    = new Atom (ANY_PROPERTY_TYPE_ID, "ANY_PROPERTY_TYPE");
  public static readonly Atom PRIMARY 
    = new Atom (PRIMARY_ID, "PRIMARY");
  public static readonly Atom SECONDARY 
    = new Atom (SECONDARY_ID, "SECONDARY");
  public static readonly Atom ARC 
    = new Atom (ARC_ID, "ARC");
  public static readonly Atom ATOM 
    = new Atom (ATOM_ID, "ATOM");
  public static readonly Atom BITMAP 
    = new Atom (BITMAP_ID, "BITMAP");
  public static readonly Atom CARDINAL 
    = new Atom (CARDINAL_ID, "CARDINAL");
  public static readonly Atom COLORMAP 
    = new Atom (COLORMAP_ID, "COLORMAP");
  public static readonly Atom CURSOR 
    = new Atom (CURSOR_ID, "CURSOR");
  public static readonly Atom CUT_BUFFER0 
    = new Atom (CUT_BUFFER0_ID, "CUT_BUFFER0");
  public static readonly Atom CUT_BUFFER1 
    = new Atom (CUT_BUFFER1_ID, "CUT_BUFFER1");
  public static readonly Atom CUT_BUFFER2 
    = new Atom (CUT_BUFFER2_ID, "CUT_BUFFER2");
  public static readonly Atom CUT_BUFFER3 
    = new Atom (CUT_BUFFER3_ID, "CUT_BUFFER3");
  public static readonly Atom CUT_BUFFER4 
    = new Atom (CUT_BUFFER4_ID, "CUT_BUFFER4");
  public static readonly Atom CUT_BUFFER5 
    = new Atom (CUT_BUFFER5_ID, "CUT_BUFFER5");
  public static readonly Atom CUT_BUFFER6 
    = new Atom (CUT_BUFFER6_ID, "CUT_BUFFER6");
  public static readonly Atom CUT_BUFFER7 
    = new Atom (CUT_BUFFER7_ID, "CUT_BUFFER7");
  public static readonly Atom DRAWABLE 
    = new Atom (DRAWABLE_ID, "DRAWABLE");
  public static readonly Atom FONT 
    = new Atom (FONT_ID, "FONT");
  public static readonly Atom INTEGER 
    = new Atom (INTEGER_ID, "INTEGER");
  public static readonly Atom PIXMAP 
    = new Atom (PIXMAP_ID, "PIXMAP");
  public static readonly Atom POINT 
    = new Atom (POINT_ID, "POINT");
  public static readonly Atom RECTANGLE 
    = new Atom (RECTANGLE_ID, "RECTANGLE");
  public static readonly Atom RESOURCE_MANAGER 
    = new Atom (RESOURCE_MANAGER_ID, "RESOURCE_MANAGER");
  public static readonly Atom RGB_COLOR_MAP 
    = new Atom (RGB_COLOR_MAP_ID, "RGB_COLOR_MAP");
  public static readonly Atom RGB_BEST_MAP 
    = new Atom (RGB_BEST_MAP_ID, "RGB_BEST_MAP");
  public static readonly Atom RGB_BLUE_MAP 
    = new Atom (RGB_BLUE_MAP_ID, "RGB_BLUE_MAP");
  public static readonly Atom RGB_DEFAULT_MAP 
    = new Atom (RGB_DEFAULT_MAP_ID, "RGB_DEFAULT_MAP");
  public static readonly Atom RGB_GRAY_MAP 
    = new Atom (RGB_GRAY_MAP_ID, "RGB_GRAY_MAP");
  public static readonly Atom RGB_GREEN_MAP 
    = new Atom (RGB_GREEN_MAP_ID, "RGB_GREEN_MAP");
  public static readonly Atom RGB_RED_MAP 
    = new Atom (RGB_RED_MAP_ID, "RGB_RED_MAP");
  public static readonly Atom STRING 
    = new Atom (STRING_ID, "STRING");
  public static readonly Atom VISUALID 
    = new Atom (VISUALID_ID, "VISUALID");
  public static readonly Atom WINDOW 
    = new Atom (WINDOW_ID, "WINDOW");
  public static readonly Atom WM_COMMAND 
    = new Atom (WM_COMMAND_ID, "WM_COMMAND");
  public static readonly Atom WM_HINTS 
    = new Atom (WM_HINTS_ID, "WM_HINTS");
  public static readonly Atom WM_CLIENT_MACHINE 
    = new Atom (WM_CLIENT_MACHINE_ID, "WM_CLIENT_MACHINE");
  public static readonly Atom WM_ICON_NAME 
    = new Atom (WM_ICON_NAME_ID, "WM_ICON_NAME");
  public static readonly Atom WM_ICON_SIZE 
    = new Atom (WM_ICON_SIZE_ID, "WM_ICON_SIZE");
  public static readonly Atom WM_NAME 
    = new Atom (WM_NAME_ID, "WM_NAME");
  public static readonly Atom WM_NORMAL_HINTS 
    = new Atom (WM_NORMAL_HINTS_ID, "WM_NORMAL_HINTS");
  public static readonly Atom WM_SIZE_HINTS 
    = new Atom (WM_SIZE_HINTS_ID, "WM_SIZE_HINTS");
  public static readonly Atom WM_ZOOM_HINTS 
    = new Atom (WM_ZOOM_HINTS_ID, "WM_ZOOM_HINTS");
  public static readonly Atom MIN_SPACE 
    = new Atom (MIN_SPACE_ID, "MIN_SPACE");
  public static readonly Atom NORM_SPACE 
    = new Atom (NORM_SPACE_ID, "NORM_SPACE");
  public static readonly Atom MAX_SPACE 
    = new Atom (MAX_SPACE_ID, "MAX_SPACE");
  public static readonly Atom END_SPACE 
    = new Atom (END_SPACE_ID, "END_SPACE");
  public static readonly Atom SUPERSCRIPT_X 
    = new Atom (SUPERSCRIPT_X_ID, "SUPERSCRIPT_X");
  public static readonly Atom SUPERSCRIPT_Y 
    = new Atom (SUPERSCRIPT_Y_ID, "SUPERSCRIPT_Y");
  public static readonly Atom SUBSCRIPT_X 
    = new Atom (SUBSCRIPT_X_ID, "SUBSCRIPT_X");
  public static readonly Atom SUBSCRIPT_Y 
    = new Atom (SUBSCRIPT_Y_ID, "SUBSCRIPT_Y");
  public static readonly Atom UNDERLINE_POSITION 
    = new Atom (UNDERLINE_POSITION_ID, "UNDERLINE_POSITION");
  public static readonly Atom UNDERLINE_THICKNESS 
    = new Atom (UNDERLINE_THICKNESS_ID, "UNDERLINE_THICKNESS");
  public static readonly Atom STRIKEOUT_ASCENT 
    = new Atom (STRIKEOUT_ASCENT_ID, "STRIKEOUT_ASCENT");
  public static readonly Atom STRIKEOUT_DESCENT 
    = new Atom (STRIKEOUT_DESCENT_ID, "STRIKEOUT_DESCENT");
  public static readonly Atom ITALIC_ANGLE 
    = new Atom (ITALIC_ANGLE_ID, "ITALIC_ANGLE");
  public static readonly Atom X_HEIGHT 
    = new Atom (X_HEIGHT_ID, "X_HEIGHT");
  public static readonly Atom QUAD_WIDTH 
    = new Atom (QUAD_WIDTH_ID, "QUAD_WIDTH");
  public static readonly Atom WEIGHT 
    = new Atom (WEIGHT_ID, "WEIGHT");
  public static readonly Atom POINT_SIZE 
    = new Atom (POINT_SIZE_ID, "POINT_SIZE");
  public static readonly Atom RESOLUTION 
    = new Atom (RESOLUTION_ID, "RESOLUTION");
  public static readonly Atom COPYRIGHT 
    = new Atom (COPYRIGHT_ID, "COPYRIGHT");
  public static readonly Atom NOTICE 
    = new Atom (NOTICE_ID, "NOTICE");
  public static readonly Atom FONT_NAME 
    = new Atom (FONT_NAME_ID, "FONT_NAME");
  public static readonly Atom FAMILY_NAME 
    = new Atom (FAMILY_NAME_ID, "FAMILY_NAME");
  public static readonly Atom FULL_NAME 
    = new Atom (FULL_NAME_ID, "FULL_NAME");
  public static readonly Atom CAP_HEIGHT 
    = new Atom (CAP_HEIGHT_ID, "CAP_HEIGHT");
  public static readonly Atom WM_CLASS 
    = new Atom (WM_CLASS_ID, "WM_CLASS");
  public static readonly Atom WM_TRANSIENT_FOR 
    = new Atom (WM_TRANSIENT_FOR_ID, "WM_TRANSIENT_FOR");


  public Display display;
  public int id;
  public String name;


  /** Predefined. */
  public Atom (int id, String name) {
    this.id = id;
    this.name = name;
  }


  // opcode 16 - intern atom
  /**
   * @see <a href="XInternAtom.html">XInternAtom</a>
   */ 
  public Atom (Display display, String name, bool only_if_exists) {
    this.display = display;
    this.name = name;

    Request request = new Request (display, 16, only_if_exists, 2+Data.unit (name));
    request.write2 (name.Length);
    request.write2_unused ();
    request.write1 (name);
    
    Data reply = display.read_reply (request);
    id = reply.read4 (8);

    display.atom_ids.Add (id, this);
    display.atom_names.Add (name, this);
  }


  // opcode 17 - get atom name
  /**
   * @see <a href="XGetAtomName.html">XGetAtomName</a>
   */
  public Atom (Display display, int id, bool only_if_exists) {
    this.display = display;
    this.id = id;

    Request request = new Request (display, 17, 2);
    request.write4 (id);

    Data reply = display.read_reply (request);
    int len = reply.read2 (8);
        Decoder dec	 = Encoding.ASCII.GetDecoder();
		char [] d = new char[len];
	len = dec.GetChars(reply.data,32,len,d,0);
    name = new String (d, 0, len);

    display.atom_ids.Add (id, this);
    display.atom_names.Add (name, this);
  }


  /**
   * @see #Atom(Display, int, bool)
   */
  public static Object intern (Display display, int id) {
    return intern (display, id, false);
  }


  /**
   * @see #Atom(Display, String, bool)
   */
  public static Object intern (Display display, String name) {
    return intern (display, name, false);
  }


  /**
   * @see #Atom(Display, int, bool)
   */
  public static Object intern (Display display, int id, 
    bool only_if_exists) {    

    Object value = display.atom_ids[id];
    if (value != null && value is Atom) return value;
    return new Atom (display, id, only_if_exists);
  }


  /**
   * @see #Atom(Display, String, bool)
   */
  public static Object intern (Display display, String name, 
    bool only_if_exists) { 

    Object value = display.atom_names[name];
    if (value != null && value is Atom) return value;
    return new Atom (display, name, only_if_exists);
  }


  public override String ToString () {    
    return "#Atom: " + name + " " + id;
  }
}
}
