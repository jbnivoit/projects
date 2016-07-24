namespace gnu.x11 {


/** X value list. */
public class ValueList {
  public const int ALL = 0xffff;


  public int bitmask;
  public int [] data;


  public ValueList (int count) {
    data = new int [count];
  }


  public void clear () { bitmask = 0; }


  public void aggregate (ValueList vl) {
    for (int i=0; i<vl.data.Length && i<32; i++)
      if ((vl.bitmask & 1 << i) != 0)
        set (i, vl.data [i]);   // overwrite
  }


  public int count () {
    int k = 0;

    for (int i=0; i<data.Length && i<32; i++)
      if ((bitmask & 1 << i) != 0) k++;

    return k;
  }


  public void copy (ValueList vl) {
    bitmask = vl.bitmask;
    System.Array.Copy (data, 0, vl.data, 0, data.Length);
  }


  public void set (int index, bool value) {  
    set (index, value ? 1 : 0);
  }


  public void set (int index, int value) {
    bitmask |= 1 << index;
    data [index] = value;
  }


  public void write (Request request) {
    for (int i=0; i<data.Length && i<32; i++)
      if ((bitmask & 1 << i) != 0)
	request.write4 (data [i]);
  }
}

}
