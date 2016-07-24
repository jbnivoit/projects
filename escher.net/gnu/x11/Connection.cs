using System;
using System.Collections;
using System.IO;
using System.Threading;
using System.Net;
using System.Net.Sockets;

using gnu.x11.xevent;

namespace gnu.x11 {


/**
 * Low-level network input/output with X server.
 *
 * 
 * <h3>Flow Control and Concurrency</h3>
 * 
 * From <cite>X11 protocol specification</cite>:
 * 
 * <p>Whenever the server is writing to a given connection, it is
 * permissible for the server to stop reading from that connection (but if
 * the writing would block, it must continue to service other connections). 
 * The server is not required to buffer more than a single request per
 * connection at one time. For a given connection to the server, a client
 * can block while reading from the connection but should undertake to read
 * (events and errors) when writing would block. Failure on the part of a
 * client to obey this rule could result in a deadlocked connection,
 * although deadlock is probably unlikely unless either the transport layer
 * has very little buffering or the client attempts to send large numbers
 * of requests without ever reading replies or checking for errors and
 * events.
 * 
 * <p>Whether or not a server is implemented with internal concurrency, the
 * overall effect must be as if individual requests are executed to
 * completion in some serial order, and requests from a given connection
 * must be executed in delivery order (that is, the total execution order
 * is a shuffle of the individual streams). The execution of a request
 * includes validating all arguments, collecting all data for any reply,
 * and generating and queueing all required events. However, it does not
 * include the actual transmission of the reply and the events. In
 * addition, the effect of any other cause that can generate multiple
 * events (for example, activation of a grab or pointer motion) must
 * effectively generate and queue all required events indivisibly with
 * respect to all other causes and requests. For a request from a given
 * client, any events destined for that client that are caused by executing
 * the request must be sent to the client before any reply or error is
 * sent.
 */
public class Connection {
  public Display display;


  // connection infomation
  public int display_no;
  public String hostname;
  public Socket socket;


  // incoming

  /* Optimization: use DataInputStream vs. InputStream so that
   * MessageFactory can use DataInputStream.readFully ().
   */
  public BinaryReader din;
  public Object read_lock = new Object ();
  public bool reading_reply;
  public Data saved_reply;
  public ArrayList events = new ArrayList ();


  // outgoing

  /**
   * valid:
   * <code>ASYNCHRONOUS</code> (default),
   * {@link #SYNCHRONOUS},
   * {@link #ROUND_TRIP}
   */
  public int send_mode;

  
  public static readonly String [] SEND_MODE_STRINGS = {
    "async", "sync", "round-trip"
  };


  /**
   * In this mode, protocol requests are sent asynchronously to X server. 
   * This is the default mode for C xlib as well. It means that protocol
   * requests will be queued and aggregated if possible, and then send to X
   * server in a burst only when necessary (reading reply for round-trip
   * request, reading event, or explicit flush). This mode offers the
   * highest performance over slow network connections.
   */
  public const int ASYNCHRONOUS = 0;


  /**
   * In this mode, protocol requests are sent synchronously to X server. It
   * means that protocol requests are sent to the network laywer as soon as
   * the function is called. This mode may aid debugging network or library
   * problems but it hurts the performance.
   */
  public const int SYNCHRONOUS = 1;


  /**
   * In this mode, protocol requests are sent synchronously to X server,
   * and X server is deliberately forced to give a round-trip reply. It
   * means that if the request is a one-way request (XCreateWindow), an
   * additional dummy round-trip request will be sent to X server to force
   * X server to give a reply immediately; and that if the request is
   * already a round-trip request (XGetGeometry), there will be no
   * additional dummy round-trip request. This mode significantly hurts the
   * performance but offers good debugging tracebacks. Because any error
   * will be reported by X server at the point of function call, a correct
   * stack trace will show where the problem is in the code.
   */
  public const int ROUND_TRIP = 2;


  public const int MAX_REUQEST_COUNT = 100;
  public int request_count = 0;
  public Request [] requests = new Request [MAX_REUQEST_COUNT];


  public NetworkStream output;


  /** Request sequence number counter.
   *
   * <p>From Protocol Specification: Every request on a given connection is
   * implicitly assigned a sequence number, starting with one, that is used
   * in replies, errors, and events.
   */
  public int next_seq_no = 1;


  public Connection (Display display, String hostname, int display_no) {
    this.display = display;
    this.hostname = hostname;
    this.display_no = display_no;

    if (hostname.Length == 0) hostname = "127.0.0.1";

    try {
      socket = new Socket (AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

      // Get DNS host information.
      IPHostEntry hostInfo = Dns.Resolve(hostname);
      // Get the DNS IP addresses associated with the host.
      IPAddress[] IPaddresses = hostInfo.AddressList;
      IPEndPoint hostEndPoint = new IPEndPoint(IPaddresses[0], 6000+display_no);
		socket.Connect(hostEndPoint);

      /* Should we use buffered streams? <code>BufferedInputStream</code>:
       * we know the pattern of inflow from the reply length of all X
       * server reply packet; and we use <code>readFully</code> already -
       * is buffer still useful? <code>BufferedOutputStream</code>: we send
       * out in request chunk with <code>out.write</code> - is buffer still
       * useful? We need to take care of flushing if we use
       * <code>BufferedOutputStream</code>.
       *
       * Any data to support any arguments?
       */
      output = new NetworkStream(socket);
      din = new BinaryReader (output);

    } catch (IOException e) {
      throw new Error ("Failed to create socket: " + e);
    }     
  }


  public void check_error () {
    // `XSync' function in `xc/lib/X11/Sync.c' uses the same technique.
    try {
      display.input.input_focus ();

    } catch (Error e) {
      /* When an X error occurs, Java throws an `gnu.x11.Error' exception,
       * the normal execution order is disrupted; the reply of
       * `input_focus()' resides in network buffer while nobody wants it. 
       * In case someone (`gnu.x11.test.Shape') catches the error and
       * continues to work, we should discard the input focus reply (by
       * clearing the socket input stream).
       *
       * TODO Should I be careful not to clear other packets after the
       * reply of input focus? Some event may come after that?
       */
      try {
	//        din.skip (din.Available ());
		while(socket.Poll(0,SelectMode.SelectRead)) {
			din.Read();
		}
      } catch (IOException ie) {
        throw new Error ("Failed to clear socket input stream: " + ie);
      }

      throw e;
    }
  }
      

  /**
   * Flush all queued requests and close network connection.
   *
   * @see <a href="XCloseDisplay.html">XCloseDisplay</a>

   * @see #flush()
   */  
  public void close () {
    try {
      flush ();

      // closing socket also closes its input and output streams
      socket.Close ();

    } catch (IOException e) {
      throw new Error ("Failed to close: " + e);
    }
  }


  public bool enqueue_request (Request request) {
    lock (requests) {
      if (request is Request.Aggregate && request_count > 0) {
        Request.Aggregate ar = (Request.Aggregate) request;
        Request last = requests [request_count-1];

        if (ar.aggregate (last)) return true;
      }

      // cannot aggregate it, append to request buffer
      requests [request_count] = request;
      request_count++;
      return false;
    }
  }


  public void flush () {
    if (request_count == 0) return;
    lock (requests) {
      try {
        for (int i=0; i<request_count; i++) {
          requests [i].write (output);
          requests [i] = null;  // for garbage collection
        }

      } catch (IOException e) {
        throw new Error ("Failed to write: " + e);
      }
      
      request_count = 0;
    }
  }


  /**
   * Pull all events on network.
   *
   * <b>Caution</b>: This pulls all events that X server has already put on
   * network, not necessarily all events that X server schedules for this
   * client. You must use grabbing server technique as follows (used in
   * {@link gnu.app.puppet.Puppet#read_and_dispatch_event()} as well) to
   * pull all events on server.
   *
   * <pre>
   *   display.grab_server ();
   * 
   *   display.check_error ();
   *   ArrayList all_and_everything = pull_all_events ();
   * 
   *   display.grab_server ();
   * </pre>
   *
   * Note <code>display.check_error ()</code> forces a round-trip reply
   * from X server, and X server would flush pending all events before
   * that reply.
   */
  public ArrayList pull_all_events () {
    while (true) {
      Data evt = read_message (false);
      if (evt == null) break;
      events.Add (evt);
    }
    
    lock (events) {
      ArrayList all = events;
      events = new ArrayList ();
      return all;
    }
  }
    

  public Event read_event (bool blocking, bool remove) {
    if (events.Count > 0)
      lock (events) {
        Event evt = (Event) events[0];
        events.Remove (0);
        return evt;
      }

    Data message = null;
    while (message == null) {
      /* ALWAYS yield, despite priorities of threads, to the thread running
       * `read_reply(Request)' to avoid dead-lock.
       *
       * Note that yielding once does not guarantee the thread running
       * `read_reply(Request)' will gain the control even when they have a
       * higher priority than this thread. We must repeatively yield until
       * it does so. The number of yields is unbounded.
       *
       * Reference: http://www.eng.uiowa.edu/~skaliann/books/jthreads/index.htm.
       */
      while (reading_reply) Thread.SpinWait (100);

      lock (read_lock) {
        message = read_message (blocking);
        if (message.read1 (0) == 1) { // reply
          saved_reply = message;
          message = null;
        }
      }
    }

    if (!remove) events.Add (message);
    return (Event) message;
  }


  public Data read_message (bool blocking) {
    try {
      /* Synchronize so that <code>din.available()</code> and
       * <code>din.readFully(byte[], int, int)</code> used in
       * <code>MessageFactory#build_message(Display)</code> behave
       * atomically.
       *
       * Note the output stream is already used to lock for atomic reading
       * in {@link #read_reply(Request)}.
       */
      lock (din) {
        if (!blocking && !output.DataAvailable) return null;

        /* Flushing for reading events. Round-trip requests are flushed in
         * {@link #send(Request, bool)} and hence reading reply does not
         * need flushing here. However, there may be one-way requests
         * (which will generate events) that needed to be flushed before
         * reading events.
         */
        flush ();
        return MessageFactory.build (display);
      }
    } catch (EndOfStreamException e) {
      throw new Error ("Connection closed by X server: " + e);

    } catch (IOException e) {
      throw new Error ("Failed to read: " + e);
    }
  }
   
  
  public Data read_reply (Request request) {
    reading_reply = true;       // outside lock block

    /* Synchronize so that `send(Request, bool)' and
     * `read_message(bool)' behave atomically. That is, a reply is
     * matched with its corresponding request.
     * 
     * Note the input stream `din' is already used to lock for atomic
     * reading in `read_message(bool)'.
     */
    lock (output) {
      int seq_no = send (request, true);

      Data message;
      lock (read_lock) {
        reading_reply = false;
        if (saved_reply != null) {
          message = saved_reply;
          saved_reply = null;
                          
        } else {
          while ((message = read_message (true)) is Event)
            events.Add (message);
        }
      }

      int reply_seq_no = message.read2 (2);
      if (display.connected && reply_seq_no != seq_no)
        throw new Error (
          "X server error: reply out of order: expect "
          + seq_no + " got " + reply_seq_no);
      return message;
    }
  }


  public int send (Request request, bool round_trip) {
    int seq_no = next_seq_no;

    /* Case 1: Do not increment sequence number if we are not connected.
     *
     * Case 2: Do not increment sequence number if we can and have
     * aggregated the new request.
     *
     * @see #next_seq_no
     * @see #enqueue_request
     */
    if (!enqueue_request (request) && display.connected)
      // only the least 16-bit is significant
      next_seq_no = (next_seq_no + 1) & 0xffff;


    /* We flush the request queue only when
     * 
     * 1. {@link #send_mode} is {@link #SYNCHRONOUS} or {@link
     * #ROUND_TRIP}; or
     *
     * 2. when the queue is full, or
     *
     * 3. when it is a round-trip request.
     *
     * Note round-trip requests are flushed here instead of in {@link
     * #read_message(bool)} because some other thread may already be
     * block-reading events with {@link #next_event(bool)} and thus this
     * thread fails to obtain lock on {@link #din}.
     */
    if (send_mode == SYNCHRONOUS || send_mode == ROUND_TRIP
      || request_count >= MAX_REUQEST_COUNT
      || round_trip) flush ();

    if (!round_trip && send_mode == ROUND_TRIP)
      check_error ();

    return seq_no;
  }


  public override String ToString () {
    return "#Connection"
      + "\n  hostname: " + hostname
      + "\n  display-number: " + display_no;
  }
}
}
