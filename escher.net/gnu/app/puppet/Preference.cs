using System;
using System.Collections;

using gnu.x11;

namespace gnu.app.puppet {


/**
 * User settings of {@link Puppet}.
 * 
 * You can find out WM-NAME and WM-CLASS of any window using standard X
 * Window System utilities such as `xwininfo' and `xprop', or you can use
 * `key-dump-info' of Puppet.
 */
public class Preference {
  /* My desktop.
   *
   * licq 0.85
   * pclock -w -B $HOME/lib/ugly-yellow.xpm -H blue
   * wmload -exe puppet
   * xeyes
   * xsetbg $HOME/lib/echer.jpg
   */

  private static readonly String [] [] NO_FOCUS = {
    new String [] {"MainWindow", "licq"},     // valid only for licq 0.85
    new String [] {"pclock", "PClock"},
    new String [] {"wmload", "WMLoad"},
    new String [] {"xeyes", "XEyes"}
  };


  private static readonly String [] [] NO_GEOMETRY_CHANGE = {
    new String [] {"MainWindow", "licq"},
  };


  private static readonly Object [] [] POSITION = {
    new Object [] {"MainWindow", "licq", new Rectangle (0, 0, 135, 1024)},
    new Object [] {"findDialog_popup", "Netscape", new Rectangle (860, 30, 0, 0)},
    new Object [] {"pclock", "PClock", new Rectangle (-64, 0, 0, 0)},
    new Object [] {"wmload", "WMLoad", new Rectangle (140, 2, 0, 0)},
    new Object [] {"gv", "GV", new Rectangle (0, 0, 1400, 1024)},
    new Object [] {"xeyes", "XEyes", new Rectangle (210, 2, 64, 64)}
  };


  private static readonly String [] [] REGISTER = { 
    new String [] {"MainWindow", "licq"},     // 0
    new String [] {"Navigator", "Netscape"},	// 1
    new String [] {"emacs", "Emacs"},		// 2
    new String [] {"rxvt", "XTerm"},		// 3
    null,			// 4
    null,			// 5
    null,			// 6
    null,			// 7
    null,			// 8
    null                        // 9
  };


  private static readonly String [] LAUNCH = {
    "licq",			// 0
    "netscape",			// 1
    "emacs",			// 2
    "rxvt",			// 3
    null,                       // 4
    null,                       // 5
    null,                       // 6
    null,                       // 7
    null,                       // 8
    "xterm"                     // 9
  };


  private static readonly String LAUNCH_ON_ROOT = "xterm.exe";


  private static readonly Point [] WARP = {
    new Point (60, 1015),       // 0 - licq message
    null,                       // 1
    null,                       // 2
    null,                       // 3
    null,                       // 4
    null,                       // 5
    null,                       // 6
    null,                       // 7
    null,                       // 8
    null                        // 9
  };


  private static readonly Rectangle SPACE
    // small margins (5 pixels) on all sides
    = new Rectangle (140, 70, 1135, 950);


  // end of user setting

  
  private static readonly Hashtable hash = new Hashtable (29);  
  public static void staticInit() {
    // no focus
    for (int i=0; i<NO_FOCUS.Length; i++) {
      String key = NO_FOCUS [i] [0] + "\0" + NO_FOCUS [i] [1]
        + ":" + "no-focus";
      hash.Add (key, true);
    }


    // no geometry change
    for (int i=0; i<NO_GEOMETRY_CHANGE.Length; i++) {
      String key = NO_GEOMETRY_CHANGE [i] [0] + "\0" + NO_GEOMETRY_CHANGE [i] [1]
        + ":" + "no-geometry-change";
      hash.Add (key, true);
    }

    
    // position
    for (int i=0; i<POSITION.Length; i++) {
      String key = POSITION [i] [0] + "\0" + POSITION [i] [1]
        + ":" + "position";
      hash.Add (key, POSITION [i] [2]);
    }


    // register
    for (int i=0; i<REGISTER.Length; i++) {
      if (REGISTER [i] == null) continue;

      String key = REGISTER [i] [0] + "\0" + REGISTER [i] [1]
        + ":" + "register";
      hash.Add (key, i);
    }
  }


  public bool no_focus (String id) {
    Object value = hash[id + "no-focus"];
	if(value == null)
		return false;
    return value.Equals(true);
  }


  public bool no_geometry_change (String id) {
    Object value = hash[id + "no-geometry-change"];
	if(value == null)
		return false;
    return value.Equals(true);
  }


  public String launch (int i) { return LAUNCH [i]; }
  public String launch_on_root () { return LAUNCH_ON_ROOT; }


  public Rectangle position (String id) {
    return (Rectangle) hash[id + "position"];
  }


  public int register (String id) {
    Object value = hash[id + "register"];

    if (value is Int32) 
      return ((Int32) value);
    else
      return -1;
  }


  public Rectangle space () { return SPACE; }
  public Point warp_position (int i) { return WARP [i]; }
}
}
