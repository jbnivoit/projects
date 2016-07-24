using System;
using System.Text;

using gnu.x11.extension.glx;

namespace gnu.app.redbook {


/**
 * Draw stroke (vector) font. To demonstrate display list. Modified from
 * <code>stroke.c</code>.
 *
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/StrokeFont.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/app/redbook/StrokeFont.help">
 * help output</a>
 */
public class StrokeFont : gnu.x11.extension.glx.Application {
	private static readonly ASCIIEncoding ascii = new ASCIIEncoding();
  private const String LINE1 = "A SPARE SERAPE APPEARS AS";
  private const String LINE2 = "APES PREPARE RARE PEPPERS";

  private const int POINT = 1;
  private const int STROKE = 2;
  private const int END = 3;

  private static readonly int [] [] LETTER_A = new int[][]{
   new int[]{0, 0, POINT}, new int []{0, 9, POINT}, new int []{1, 10, POINT}, 
   new int []{4, 10, POINT}, new int []{5, 9, POINT}, new int []{5, 0, STROKE}, 
   new int []{0, 5, POINT}, new int []{5, 5, END}
  };


  private static readonly int [] [] LETTER_E = new int[][]{
   new int []{5, 0, POINT}, new int []{0, 0, POINT}, new int []{0, 10, POINT}, 
   new int []{5, 10, STROKE}, new int []{0, 5, POINT}, new int []{4, 5, END}
  };


  private static readonly int [] [] LETTER_P = new int[][]{
   new int []{0, 0, POINT}, new int []{0, 10, POINT},  new int []{4, 10, POINT}, 
   new int []{5, 9, POINT}, new int []{5, 6, POINT}, new int []{4, 5, POINT}, 
   new int []{0, 5, END}
  };


  private static readonly int [] [] LETTER_R = new int[][]{
   new int []{0, 0, POINT}, new int []{0, 10, POINT},  new int []{4, 10, POINT}, 
   new int []{5, 9, POINT}, new int []{5, 6, POINT}, new int []{4, 5, POINT}, 
   new int []{0, 5, STROKE}, new int []{3, 5, POINT}, new int []{5, 0, END}
  };


  private static readonly int [] [] LETTER_S = new int[][]{
   new int []{0, 1, POINT}, new int []{1, 0, POINT}, new int []{4, 0, POINT}, 
   new int []{5, 1, POINT}, new int []{5, 4, POINT}, new int []{4, 5, POINT}, 
   new int []{1, 5, POINT}, new int []{0, 6, POINT}, new int []{0, 9, POINT}, 
   new int []{1, 10, POINT}, new int []{4, 10, POINT}, new int []{5, 9, END}
  };
    

  public StrokeFont (String [] args)
    : base (args, RESIZE_BIT) {

    about ("0.1", "stroke font",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;
    init_window (440, 120);

    gl.shade_model (GL.FLAT);
    init_letters ();
  }


  private void draw_letter (int [] [] letter) {
   gl.begin (GL.LINE_STRIP);

   for (int i=0; i<letter.Length; i++) {
     int [] instruction = letter [i];
     int x = instruction [0];
     int y = instruction [1];
     int type = instruction [2];
     gl.vertex2f (x, y);

     switch (type) {
     case POINT:
       break;

     case STROKE: {
       gl.end ();
       gl.begin (GL.LINE_STRIP);
       break;

     } case END: {
       gl.end ();
       gl.translatef (8.0f, 0.0f, 0.0f);
       return;
     }
     }
   }
  }


  protected override void handle_expose () {
    gl.clear (GL.COLOR_BUFFER_BIT);

    // line 1
    gl.push_matrix ();   
    gl.scalef (2.0f, 2.0f, 2.0f);
    gl.translatef (10.0f, 30.0f, 0.0f);
    gl.call_lists (GL.BYTE, ascii.GetBytes (LINE1));
    gl.pop_matrix ();

    // line 2
    gl.push_matrix ();
    gl.scalef (2.0f, 2.0f, 2.0f);
    gl.translatef (10.0f, 13.0f, 0.0f);
    gl.call_lists (GL.BYTE, ascii.GetBytes (LINE2));
    gl.pop_matrix ();

    gl.swap_buffers (window);
  }


  protected override void handle_resize (int width, int height) {
    gl.viewport (0, 0, width, height);
    gl.matrix_mode (GL.PROJECTION);
    gl.load_identity ();
    glu.ortho_2d (0.0, width, 0.0, height);
  }


  private void init_letters () {
    int b = gl.gen_lists (128);
    gl.list_base (b);

    gl.new_list (b+'A', GL.COMPILE); 
    draw_letter (LETTER_A); 
    gl.end_list ();

    gl.new_list (b+'E', GL.COMPILE);
    draw_letter (LETTER_E);
    gl.end_list ();

    gl.new_list (b+'P', GL.COMPILE);
    draw_letter (LETTER_P);
    gl.end_list ();

    gl.new_list (b+'R', GL.COMPILE);
    draw_letter (LETTER_R); 
    gl.end_list ();

    gl.new_list (b+'S', GL.COMPILE); 
    draw_letter (LETTER_S);
    gl.end_list ();

    gl.new_list (b+' ', GL.COMPILE); 
    gl.translatef (8.0f, 0.0f, 0.0f);
    gl.end_list ();
  }


  public static void Main (String [] args) {
    new StrokeFont (args).exec ();
  }
}
}
