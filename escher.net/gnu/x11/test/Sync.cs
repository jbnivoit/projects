using System;
using System.Threading;

using gnu.x11;
using gnu.x11.xevent;

namespace gnu.x11.test {

/**
 * Test multi-threading and synchronization. 
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Sync.gif">
 * screenshot</a>
 * 
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Sync.output">
 * text output</a>
 *
 * @see <a href="../../../../etc/screenshot/gnu/x11/test/Sync.help">
 * help output</a>
 */
public class Sync : Graphics {
  public static readonly Random random = new Random ();
  public Thread thread;


  public Sync (String [] args)  
    : base (args, 256, 256) {
	thread = new Thread (new ThreadStart(this.run));
    about ("0.1", "test multi-threading and synchronization",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;
    leave_display_open = true;
    
    Console.WriteLine ("stress test with send-mode = round-trip");
    display.connection.send_mode = gnu.x11.Connection.ROUND_TRIP;
  }


  
  protected override void dispatch_event () {
    Console.WriteLine ("blocking-read event");
    evt = display.next_event ();
    Console.WriteLine ("got event " + evt);

    switch (evt.code ()) {
    case gnu.x11.xevent.ButtonPress.CODE:
      exit ();
      break;

    case ClientMessage.CODE:
      if (((ClientMessage) evt).delete_window ()) exit ();
      break;

    case Expose.CODE:
      if (!thread.IsAlive) thread.Start ();
      break;
	
    case KeyPress.CODE: {
      KeyPress e = (KeyPress) evt;
	
      int keycode = e.detail ();
      int keystate = e.state ();
      int keysym = display.input.keycode_to_keysym (keycode, keystate);

      if (keysym == 'q' || keysym == 'Q' 
        || keysym == gnu.x11.keysym.Misc.ESCAPE) exit ();
      break;	

    }
    }
  }


  protected override void exit () {
    base.exit ();
    thread.Interrupt ();
  }    


  public void run () {
    while (!exit_now) {
      // generate round-trip request during `Display#next_event()'
      Console.WriteLine ("try round-trip request");
      display.input.input_focus ();
      Console.WriteLine ("done round-trip request");

      // generate one-way request during `Display#next_event()'
      window.line (display.default_gc, 
        random.Next (window.width), random.Next (window.height),
        random.Next (window.width), random.Next (window.height));
      display.flush ();

      if (!exit_now) gnu.util.Misc.sleep (1000);
    }

    display.close ();
  }


  public static void Main (String [] args) { 
    new Sync (args).exec ();
  }
}

}
