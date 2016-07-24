using gnu.x11;

namespace gnu.x11.xevent {


/** X input-related event. */
public abstract class Input : Event {
  /** Reading. */
  public Input (Display display, byte [] data) 
    :base (display, data, 4) {
  }


  //-- reading

  public virtual int detail () { return read1 (1); }
  public int root_id () { return read4 (8); }
  public virtual int child_id () { return read4 (16); }
  public int root_x () { return read2 (20); }
  public int root_y () { return read2 (22); }
  public int event_x () { return read2 (24); }
  public int event_y () { return read2 (26); }
  public int state () { return read2 (28); }
  public bool same_screen () { return read_bool (30); }


  public Window root () { 
    return (Window) Window.intern (display, root_id ()); 
  }


  public virtual Window child () { 
    return (Window) Window.intern (display, child_id ()); 
  }


  /** Writing. */
  public Input (Display display, int CODE) :
    base (display, CODE, 12) {
  }


  //-- writing

  public void set_detail (int i) { write1 (1, i); }
  public void set_root (Window w) { set_root_id (w.id); }
  public void set_root_id (int i) { write4 (8, i); }
  public void set_child (Window w) { set_child_id (w.id); }
  public void set_child_id (int i) { write4 (16, i); }
  public void set_root_x (int i) { write2 (20, i); }
  public void set_root_y (int i) { write2 (22, i); }
  public void set_event_x (int i) { write2 (24, i); }
  public void set_event_y (int i) { write2 (26, i); }
  public void set_state (int i) { write2 (28, i); }
  public void set_same_screen (bool b) { write1 (30, b); }
}
}
