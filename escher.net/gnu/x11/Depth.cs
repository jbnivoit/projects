using System;

namespace gnu.x11 {


/** X depth. */
public class Depth : Data {
  public Depth (Data data, int offset) : base (data, offset) {}
  public int depth () { return read1 (0); }
  public int visual_count () { return read2 (2); }
  public int Length {
	get { return 8 + visual_count ()*24; }
	}


  /**
   * @return valid:
   * {@link Enum#elt(int)} of type {@link Visual},
   * {@link Enum#next()} of type {@link Visual}
   */
	private class DepthEnum : Enum {
		public DepthEnum(Depth owner, int len, int c)
			: base(owner,len,c) {}
	
      public override Object elt (int i) {
        int offset = start_offset + i*24;
        return new Visual (this, offset);
      }


      public override Object next () {
        Visual visual = new Visual (this, 0);
        inc (24);
        return visual;
      }     
    }

  public Enum visuals () {
    return new DepthEnum (this, 8, visual_count ());
	}


  public override String ToString () {
    return "#Depth"
      + "\n  depth: " + depth ()
      + "\n  visual-count: " + visual_count ()
      + visuals ().to_string (Enum.NEXT, "\n#Depth: ");
  }
}
}
