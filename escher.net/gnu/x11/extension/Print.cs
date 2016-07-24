using System;
using gnu.x11;

namespace gnu.x11.extension {


/**
 * X Print Service Extension. The specification can be found <a href=
 * "http://escher.sourceforge.net/etc/specification/print-library.ps.gz"
 * >here</a> (<a href=
 * "http://escher.sourceforge.net/etc/specification/print-protocol.ps.gz"
 * >protocol</a>; <a href=
 * "http://escher.sourceforge.net/etc/specification/print-server.ps.gz"
 * >server</a>).
 */
public class Print : gnu.x11.extension.Extension,
  gnu.x11.extension.ErrorFactory,
  gnu.x11.extension.EventFactory {

  public static readonly String [] MINOR_OPCODE_STRINGS = {
    "QueryVersion",             // 0
    "GetPrinterList",           // 1
    "CreateContext",            // 2
    "SetContext",               // 3
    "GetContext",               // 4
    "DestroyContext",           // 5
    "GetContextScreen",         // 6
    "StartJob",                 // 7
    "EndJob",                   // 8
    "StartDoc",                 // 9
    "EndDoc",                   // 10
    "PutDocumentData",          // 11
    "GetDocumentData",          // 12
    "StartPage",                // 13
    "EndPage",                  // 14
    "SelectInput",              // 15
    "InputSelected",            // 16
    "GetAttributes",            // 17
    "SetAttributes",            // 18
    "GetOneAttribute",          // 19
    "RehashPrinterList",        // 20
    "GetPageDimensions",        // 21
    "QueryScreens",             // 22
    "SetImageResolution",       // 23
    "GetImageResolution",       // 24
  };


  public const int CLIENT_MAJOR_VERSION = 1;
  public const int CLIENT_MINOR_VERSION = 0;


  public String locale = "";
  public int server_major_version, server_minor_version;


  public class Context : gnu.x11.Resource {
	Print owner;
    /** Intern. */
    public Context (Print owner, int id) :
      base (owner.display, id) {
		this.owner=owner;
    }
  
    
    // print 2 - create context
    /**
     * @see <a href="XpCreateContext.html">XpCreateContext</a>
     */
    public Context (Print owner, String name) 
      : base (owner.display) {
		this.owner=owner;
  
      int len = 4 + Data.unit (name) + Data.unit (owner.locale);
      Request request = new Request (this.display, owner.major_opcode, 2, len);
      request.write4 (id);
      request.write4 (name.Length);
      request.write4 (owner.locale.Length);
      request.write1 (name);
      request.write1 (owner.locale);
      this.display.send_request (request);
    }
  
  
    // print 3 - set context
    /**
     * @see <a href="XpSetContext.html">XpSetContext</a>
     */
    public void set () {
      Request request = new Request (this.display, this.owner.major_opcode, 3, 2);
      request.write4 (id);
      this.display.send_request (request);
    }
  
  
    // print 5 - destroy context
    /**
     * @see <a href="XpDestroyContext.html">XpDestroyContext</a>
     */
    public void destroy () {
      Request request = new Request (this.display, this.owner.major_opcode, 5, 2);
      request.write4 (id);
      this.display.send_request (request);
    }
  
  
    // print 6 - get screen of context
    /**
     * @see <a href="XpGetScreenOfContext.html">XpGetScreenOfContext</a>
     */
    public Window screen () {
      Request request = new Request (this.display, this.owner.major_opcode, 6, 2);
      // error in spec: missing context field
      request.write4 (id);
  
      Data reply = this.display.read_reply (request);
      int root_id = reply.read4 (8);
      return (Window) Window.intern (this.display, root_id);
    }
  
  
    // print 15 - select input
    /**
     * @see <a href="XpSelectInput.html">XpSelectInput</a>
     */
    public void select_input (int event_mask) {
      Request request = new Request (this.display, this.owner.major_opcode, 15, 3);
      request.write4 (id);
      request.write4 (event_mask);
      this.display.send_request (request);
    }
  
  
    /** Reply of {@link #input_selected(int)}. */
    public class InputSelectedReply : Data {
      public InputSelectedReply (Data data) : base (data) {}
      public int event_mask () { return read4 (8); }
      public int all_events_mask () { return read4 (8); }
    }
  
  
    // print 16 - input selected
    /**
     * @see <a href="XpInputSelected.html">XpInputSelected</a>
     */
    public InputSelectedReply input_selected (int event_mask) {
      Request request = new Request (this.display, this.owner.major_opcode, 16, 2);
      request.write4 (id);
  
      Data reply = this.display.read_reply (request);
      return new InputSelectedReply (reply);
    }
  
  
    public const int JOB_ATTRIBUTE_POOL = 1;
    public const int DOC_ATTRIBUTE_POOL = 2;
    public const int PAGE_ATTRIBUTE_POOL = 3;
    public const int PRINTER_ATTRIBUTE_POOL = 4;
    public const int SERVER_ATTRIBUTE_POOL = 5;
    public const int MEDIUM_ATTRIBUTE_POOL = 6;
    public const int SPOOLER_ATTRIBUTE_POOL = 7;
  
  
    // print 17 - get attributes
    /**
     * @param pool valid:
     * {@link #JOB_ATTRIBUTE_POOL},
     * {@link #DOC_ATTRIBUTE_POOL},
     * {@link #PAGE_ATTRIBUTE_POOL},
     * {@link #PRINTER_ATTRIBUTE_POOL},
     * {@link #SERVER_ATTRIBUTE_POOL},
     * {@link #MEDIUM_ATTRIBUTE_POOL},
     * {@link #SPOOLER_ATTRIBUTE_POOL}
     *
     * @see <a href="XpGetAttributes.html">XpGetAttributes</a>
     */
    public String attributes (int pool) {
      Request request = new Request (this.display, this.owner.major_opcode, 17, 3);
      request.write4 (id);
      request.write1 (pool);
  
      Data reply = this.display.read_reply (request);
      int len = reply.read4 (8);
      return reply.read_string (32, len);
    }   
  
  
    public const int ATTRIBUTE_REPLACE = 1;
    public const int ATTRIBUTE_MERGE = 2;
  
  
    // print 18 - set attributes
    /**
     * @param pool valid:
     * {@link #JOB_ATTRIBUTE_POOL},
     * {@link #DOC_ATTRIBUTE_POOL},
     * {@link #PAGE_ATTRIBUTE_POOL},
     * {@link #PRINTER_ATTRIBUTE_POOL},
     * {@link #SERVER_ATTRIBUTE_POOL}
     *
     * @see <a href="XpSetAttributes.html">XpSetAttributes</a>
     */
    public void set_attributes (int pool, int rule, String attributes) {
      int len = 4 + Data.unit (attributes);
      Request request = new Request (this.display, this.owner.major_opcode, 18, len);
      request.write4 (id);
      request.write4 (attributes.Length);
      request.write1 (pool);
      request.write1 (rule);
      request.write2_unused ();
      request.write1 (attributes);
      this.display.send_request (request);
    }
  
  
    // print 19 - get one attribute
    /**
     * @param pool valid:
     * {@link #JOB_ATTRIBUTE_POOL},
     * {@link #DOC_ATTRIBUTE_POOL},
     * {@link #PAGE_ATTRIBUTE_POOL},
     * {@link #PRINTER_ATTRIBUTE_POOL},
     * {@link #SERVER_ATTRIBUTE_POOL}
     *
     * @param rule valid:
     * {@link #ATTRIBUTE_REPLACE},
     * {@link #ATTRIBUTE_MERGE}
     *
     * @see <a href="XpGetOneAttribute.html">XpGetOneAttribute</a>
     */
    public String one_attribute (int pool, String name) {
      int len = 4 + Data.unit (name);
      Request request = new Request (this.display, this.owner.major_opcode, 19, len);
      request.write4 (id);
      request.write4 (name.Length);
      request.write1 (pool);
      request.write3_unused ();
      request.write1 (name);
  
      Data reply = this.display.read_reply (request);
      len = reply.read4 (8);
      return reply.read_string (32, len);
    }
  
  
    /** Reply of {@link #page_dimensions()}. */  
    public class PageDimensionsReply : Data {
      public PageDimensionsReply (Data data) : base (data) {}
      public int width () { return read2 (8); }
      public int height () { return read2 (10); }
      public int offset_x () { return read2 (12); }
      public int offset_y () { return read2 (14); }
      public int reproducible_x () { return read2 (16); }
      public int reproducible_y () { return read2 (18); }
  
  
      public override String ToString () {
        return "#PageDimensionsReply"
          + "\nwidth: " + width ()
          + "\nheight: " + height ()
          + "\noffset-x: " + offset_x ()
          + "\noffset-x: " + offset_y ()
          + "\nreproducible-x: " + reproducible_x ()
          + "\nreproducible-y: " + reproducible_y ();
      }
    }
  
  
    /** Reply of {@link #page_dimensions()}. */  
    public class SetImageResolutionReply : Data {
      public SetImageResolutionReply (Data data) : base (data) {}
      public bool status () { return read_bool (1); }
      public int previous_resolution () { return read2 (8); }
    }
  
  
    // print 21 - get page dimensions
    /**
     * @see <a href="XpGetPageDimensions.html">XpGetPageDimensions</a>
     */
    public PageDimensionsReply page_dimensions () {
      Request request = new Request (this.display, this.owner.major_opcode, 21, 2);
      request.write4 (id);
  
      Data reply = this.display.read_reply (request);
      return new PageDimensionsReply (reply);
    }
  
  
    // print 23 - set image resolution
    /**
     * @see <a href="XpSetImageResolution.html">XpSetImageResolution</a>
     */
    public SetImageResolutionReply set_image_resolution (int resolution) {
      Request request = new Request (this.display, this.owner.major_opcode, 23, 3);
      request.write4 (id);
      request.write2 (resolution);
      
      Data reply = this.display.read_reply (request);
      return new SetImageResolutionReply (reply);
    }
      
  
    // print 24 - get image resolution
    /**
     * @see <a href="XpGetImageResolution.html">XpGetImageResolution</a>
     */
    public int image_resolution () {
      Request request = new Request (this.display, this.owner.major_opcode, 24, 2);
      request.write4 (id);
      
      Data reply = this.display.read_reply (request);
      return reply.read2 (8);
    }
      
  
    /**
     * All possible attributes.
     *
     * @see #attributes(int)
     */
    public String attributes () {
      return attributes (JOB_ATTRIBUTE_POOL)
        + attributes (DOC_ATTRIBUTE_POOL)
        + attributes (PAGE_ATTRIBUTE_POOL)
        + attributes (PRINTER_ATTRIBUTE_POOL)
        + attributes (SERVER_ATTRIBUTE_POOL);
    }
  
  
    public override String ToString () {
      return "#Context\n" 
        + attributes ();
    }
  }
  
  
    // print opcode 0 - query version
  /**
   * @see <a href="XpQueryVersion.html">XpQueryVersion</a>
   */
  public Print (Display display) 
    //throws gnu.x11.extension.NotFoundException { 

    :base (display, "XpExtension", MINOR_OPCODE_STRINGS, 2, 2) {

    // check version before any other operations
    Request request = new Request (display, major_opcode, 0, 1);
    Data reply = display.read_reply (request);
    server_major_version = reply.read2 (4);
    server_minor_version = reply.read2 (4);    
  }


  /** Reply of {@link #printer_list(String)}. */
  public class Printer : Data {
	private Print owner;
    public Printer (Print owner, Data data, int offset) : base (data, offset) { this.owner=owner; }
    public int name_length () { return read4 (0); }
    public String name () { return read_string (4, name_length ()); }


    public int description_length () { 
      // 4 = length of name length field
      int offset = Data.len (name_length ()) + 4;
      return read4 (offset);
    }


    public String description () {
      // 4 = length of name length field
      // 4 = length of description length field
      int offset = Data.len (name_length ()) + 4 + 4;      
      return read_string (offset, description_length ()); 
    }


    /**
     * @see #create_context(String)
     */
    public Context context () {
      return owner.create_context (name());
    }


    public int length () { 
      // 4 = length of name length field
      // 4 = length of description length field
      return Data.len (name_length ()) 
        + Data.len (description_length ()) + 4 + 4;
    }


    public override String ToString () {
      return "#Printer"
        + "\nprinter-name: " + name ()
        + "\nprinter-description: "  + description ();
    }
  }

  
  // print opcode 1 - get printer list
  /**
   * @return valid: {@link Enum#next()}
   * @see <a href="XpGetPrinterList.html">XpGetPrinterList</a>
   */
	private /*static*/ class PrintersEnum : Enum 
	 {
		private Print owner;
		public PrintersEnum(Print owner, Data reply, int len, int c) :base(reply,len,c) { this.owner=owner; }
      public override Object next () {
        Printer printer = new Printer (owner,null,0);
        inc (printer.length());
        return printer;
      }
    }

  public Enum printer_list (String name) {
    int len = 3 + Data.unit (name) + Data.unit (locale);
    Request request = new Request (display, major_opcode, 1, len);
    request.write4 (name.Length);
    request.write4 (locale.Length);
    request.write1 (name);
    request.write1 (locale);

    Data reply = display.read_reply (request);
    return new PrintersEnum (this, reply, 32, reply.read4 (8));
  }


  // print 4 - get context
  /**
   * @see <a href="XpGetContext.html">XpGetContext</a>
   */
  public Context context () {
    Request request = new Request (display, major_opcode, 4, 1);
    Data reply = display.read_reply (request);
    int id = reply.read4 (8);
    return new Context (this,id);
  }


  public const int SPOOL = 1;
  public const int GET_DATA = 2;


  // print 7 - start job
  /**
   * @param output_mode valid:
   * {@link #SPOOL},
   * {@link #GET_DATA}
   *
   * @see <a href="XpStartJob.html">XpStartJob</a>
   */
  public void start_job (int output_mode) {
    Request request = new Request (display, major_opcode, 7, 2);
    request.write1 (output_mode);
    display.send_request (request);
  }


  // print 8 - end job
  /**
   * @see <a href="XpEndJob.html">XpEndJob</a>
   */
  public void end_job (bool cancel) {
    Request request = new Request (display, major_opcode, 8, 2);
    request.write1 (cancel);
    display.send_request (request);
  }


  // print 9 - start doc
  /**
   * @see <a href="XpStartDoc.html">XpStartDoc</a>
   */
  public void start_doc (int type) {
    Request request = new Request (display, major_opcode, 9, 2);
    request.write1 (type);
    display.send_request (request);
  }


  // print 10 - end doc
  /**
   * @see <a href="XpEndDoc.html">XpEndDoc</a>
   */
  public void end_doc (bool cancel) {
    Request request = new Request (display, major_opcode, 10);
    request.write1 (cancel);
    display.send_request (request);
  }


  // print 13 - start page
  /**
   * @see <a href="XpStartPage.html">XpStartPage</a>
   */
  public void start_page (Window window) {
    Request request = new Request (display, major_opcode, 13, 2);
    request.write4 (window.id);
    display.send_request (request);
  }


  // print 14 - end page
  /**
   * @see <a href="XpEndPage.html">XpEndPage</a>
   */
  public void end_page (bool cancel) {
    Request request = new Request (display, major_opcode, 14, 2);
    request.write1 (cancel);
    display.send_request (request);
  }


  // print opcode 20 - rehash printer list
  /**
   * @see <a href="XpRehashPrinterList.html">XpRehashPrinterList</a>
   */
  public void rehash_printer_list () {
    Request request = new Request (display, major_opcode, 20, 1);
    display.send_request (request);
  }


  // printer opcode 22 - query screens
  /**
   * @return valid:
   * {@link Enum#next()} of type {@link Window},
   * {@link Enum#next4()}
   *
   * @see <a href="XpQueryScreens.html">XpQueryScreens</a>
   */
	private /*static*/ class ScreensEnum : Enum
	 {
		private Display display;
		public ScreensEnum(Display display, Data owner, int len, int c) : base(owner,len,c) { this.display=display; }
      public override Object next () {
        return Window.intern (display, next4 ());
      }
    }

  public Enum screens () {
    // error in spec: request length = 1 vs. 2
    Request request = new Request (display, major_opcode, 22, 1);
    Data reply = display.read_reply (request);
    int count = reply.read4 (8);

    return new ScreensEnum (display, reply, 32, count);
  }
    

  public static readonly String [] ERROR_STRINGS = {
    "BAD_PRINT_CONTEXT: parameter not a PRINT context",
    "BAD_PRINT_SEQUENCE: illegal sequence of PRINT operations",
    "BAD_PRINT_RESOURCE_ID: parameter not a X-resource ID"
  };


  public Error build (Display display, Data data, int code,
    int seq_no, int bad, int minor_opcode, int major_opcode) {

    String error_string = ERROR_STRINGS [code - first_error];
    return new Error (display, error_string, code, seq_no, bad, 
      minor_opcode, major_opcode);
  }


  /** PRINT attribute notify event. */
  public class AttributeNotifyEvent : gnu.x11.xevent.Event {
    public new const int code = 0;
  	  
    public AttributeNotifyEvent (Display display, byte [] data)
      :base (display, data, 0){
    }
  
  
    /**
     * @return valid:
     * {@link Print.Context#JOB_ATTRIBUTE_POOL},
     * {@link Print.Context#DOC_ATTRIBUTE_POOL},
     * {@link Print.Context#PAGE_ATTRIBUTE_POOL},
     * {@link Print.Context#PRINTER_ATTRIBUTE_POOL},
     * {@link Print.Context#SERVER_ATTRIBUTE_POOL},
     * {@link Print.Context#MEDIUM_ATTRIBUTE_POOL},
     * {@link Print.Context#SPOOLER_ATTRIBUTE_POOL}
     */
    public int detail () { return read1 (1); }
    public int context_id () { return read4 (8); }
  }  
  
  
  /** PRINT print notify event. */
  public class PrintNotifyEvent : gnu.x11.xevent.Event {
    public new const int code = 0;
  
  
    public PrintNotifyEvent (Display display, byte [] data)
      : base (display, data, 0) {
    }
  
  
    public const int START_JOB_NOTIFY = 0;
    public const int END_JOB_NOTIFY = 1;
    public const int START_DOC_NOTIFY = 2;
    public const int END_DOC_NOTIFY = 3;
    public const int START_PAGE_NOTIFY = 4;
    public const int END_PAGE_NOTIFY = 5;
  
  
    /**
     * @return valid:
     * {@link #START_JOB_NOTIFY},
     * {@link #END_JOB_NOTIFY},
     * {@link #START_DOC_NOTIFY},
     * {@link #END_DOC_NOTIFY},
     * {@link #START_PAGE_NOTIFY},
     * {@link #END_PAGE_NOTIFY}
     */
    public int detail () { return read1 (1); }
  
  
    public int context_id () { return read4 (8); }
    public bool cancel () { return read_bool (12); }
  }
  
  
  public gnu.x11.xevent.Event build (Display display, 
    byte [] data, int code) {

    //return new PrintNotifyEvent (display, data);
    return null;
  }


  // javadoc bug? should be Context#Context(String)
  /**
   * Create print context.
   *
   * @param name if zero-length, default (first) printer name is used
   *
   * @see Context
   */
  public Context create_context (String name) {
    if (name.Length == 0) {
      Printer printer = (Printer) printer_list ().next ();      
      name = printer.name ();
    }

    return new Context (this, name);    
  }


  /**
   * @see #end_doc(bool)
   */
  public void end_doc () { 
    end_doc (false); 
  }


  /**
   * @see #end_job(bool)
   */
  public void end_job () { 
    end_job (false); 
  }


  /**
   * @see #end_page(bool)
   */
  public void end_page () { 
    end_page (false); 
  }


  public override String more_string () {
    return "\n  client-version: " 
      + CLIENT_MAJOR_VERSION + "." + CLIENT_MINOR_VERSION
      + "\n  server-version: "
      + server_major_version + "." + server_minor_version;
  }


  /**
   * @see #printer_list(String)
   */
  public Enum printer_list () {
    return printer_list ("");
  }
}

}
