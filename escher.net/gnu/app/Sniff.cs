using System;
using System.IO;
using System.Net.Sockets;

using gnu.x11;

namespace gnu.app {


/**
 * A network middle-layer sniffer.
 *
 * <p>Useful for debugging x11 protocol. Highly un-optimizied.
 * 
 * @see <a href="../../../etc/screenshot/gnu/app/Sniff.help">
 * help output</a>
 */
public class Sniff : Application {
  public Sniff (String [] args) 
	// throws java.io.IOException, java.net.UnknownHostException, InterruptedException {
    : base (args) {

    int listen_port = option.intt ("listen-port",
      "port number to listen to", 6001);
    int talk_port = option.intt ("talk-port",
      "port number to talk to", 6000);

    about ("0.1", "network middle-layer sniffer",
      "Stephen Tse <stephent@sfu.ca>",
      "http://escher.sourceforge.net/");

    if (help_option) return;    

    Socket listen_socket = new java.net.ServerSocket (
      listen_port).accept ();
    InputStream listen_is = listen_socket.getInputStream ();
    OutputStream listen_os = listen_socket.getOutputStream ();

    Socket talk_socket = new Socket ("127.0.0.1", talk_port);
    InputStream talk_is = talk_socket.getInputStream ();
    OutputStream talk_os = talk_socket.getOutputStream ();
    
    while (true) {
      bool something = false;

      while (listen_is.available () > 0) {
        something = true;
        int data = listen_is.read ();
        talk_os.write (data);
        Console.WriteLine ("> " + Data.byte_to_string (data));
      }

      while (talk_is.available () > 0) {
        something = true;
        int data = talk_is.read ();
        listen_os.write (data);
        Console.WriteLine ("< " + Data.byte_to_string (data));
      }

      if (!something) gnu.util.Misc.sleep (100);
    }
  }

  
  public static void Main (String [] args) {
    new Sniff (args);
  }
}
}
