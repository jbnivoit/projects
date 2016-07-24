using System;
using System.Text;
using System.Threading;
//using java.util.StringTokenizer;

namespace gnu.util {


/**
 * Provide some handy static methods.
 */
public class Misc {
  public const String VERSION = "0.2.0";


  //-- copy array

  public static double [] copy (double [] src, 
    int src_offset, int Length) {

    double [] dst = new double [Length];
    Array.Copy (src, src_offset, dst, 0, Length);
    return dst;
  }

  
  public static double [] copy (double [] src, int src_offset) {
    return copy (src, src_offset, src.Length-src_offset);
  }


  public static float [] copy (float [] src, int src_offset, int Length) {
    float [] dst = new float [Length];
    Array.Copy (src, src_offset, dst, 0, Length);
    return dst;
  }

  
  public static float [] copy (float [] src, int src_offset) {
    return copy (src, src_offset, src.Length-src_offset);
  }


  //-- linearize array

  public static float [] linearize (float [] [] src) {
    int s1 = src [0].Length;
    int s2 = src.Length;   
    float [] dst = new float [s1 * s2];
    
    for (int i=0; i<s2; i++) {
      int offset = i * s1;
      Array.Copy (src [i], 0, dst, offset, s1);
    }
    return dst;
  }


  public static float [] linearize (float [] [] [] src) {
    int s1 = src [0] [0].Length;
    int s2 = src [0].Length;
    int s3 = src.Length;    
    float [] dst = new float [s1 * s2 * s3];
    
    for (int i=0; i<s3; i++)
      for (int j=0; j<s2; j++) {
        int offset = s1 * (j + s2 * i);
        Array.Copy (src [i] [j], 0, dst, offset, s1);
      }
    return dst;
  }

  public static float [] linearize (float [,,] src) {
    int s1 = src.GetLength(0);
    int s2 = src.GetLength(1);
    int s3 = src.GetLength(2);
    float [] dst = new float [s1 * s2 * s3];
    
    for (int i=0; i<s3; i++)
      for (int j=0; j<s2; j++) {
        int offset = s1 * (j + s2 * i);
        //Array.Copy (src [i] [j], 0, dst, offset, s1);
		for(int k=0; k<s1; k++) {
			dst[offset+k] = src[i,j,k];
		}
      }
    return dst;
  }


  //-- string

  public static bool empty (String s) {
    return s == null || trim (s).Length == 0;
  }
  

  /**
   * @see #tokenize(String, String)
   */
  public static String [] tokenize (String s) {
    return tokenize (s, " \t\n\r\f");
  }

  
  /** Tokenize a string given a delimiter and from-index. */
  public static String [] tokenize (String s, String delim) {    
	return s.Split(delim.ToCharArray());
  }


  public static String to_string (double [] d, String prefix) {
    StringBuilder sb = new StringBuilder ();
    for (int i=0; i<d.Length; i++) {
      sb.Append (prefix);
      sb.Append (i + ": ");
      sb.Append (d [i]);
    }
    return sb.ToString ();
  }


  public static String to_string (int [] j, String prefix) {
    StringBuilder sb = new StringBuilder ();
    for (int i=0; i<j.Length; i++) {
      sb.Append (prefix);
      sb.Append (i + ": ");
      sb.Append (j [i]);
    }
    return sb.ToString ();
  }


  /**
   * @see #to_string(Object[], String)
   */
  public static String to_string (Object [] objects) {
    return to_string (objects, "\n");
  }


  public static String to_string (Object [] objects, String prefix) {
    StringBuilder sb = new StringBuilder ();
    for (int i=0; i<objects.Length; i++) {
      sb.Append (prefix);
      sb.Append (i + ": ");
      sb.Append (objects [i]);
    }
    return sb.ToString ();
  }


  public static String trim (String s) {
/*
    if (s == null || s.Length == 0) return s;

    int from = 0;
    while (from < s.Length)
      if (Char.IsWhiteSpace (s.Chars[from])) from++;
      else break;
    if (from == s.Length) return "";

    int to = s.Length - 1;
    while (to > 0)
      if (Char.IsWhiteSpace (s.Chars[to])) to--;
      else break;

    return s.Substring (from, to+1);
*/
	return s.Trim(new char[]{' ','\t','\n'});
  }


  //-- system functions

  public static void sleep (int millis) {
      Thread.Sleep (millis);
  }  


    private static readonly char[] digits = new char []{
	'0' , '1' , '2' , '3' , '4' , '5' ,
	'6' , '7' , '8' , '9' , 'a' , 'b' ,
	'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
	'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
	'o' , 'p' , 'q' , 'r' , 's' , 't' ,
	'u' , 'v' , 'w' , 'x' , 'y' , 'z'
    };

    public static String toHexString(int i) {
	return toUnsignedString(i, 4);
    }

    public static String toBinaryString(int i) {
	return toUnsignedString(i, 1);
    }
    private static String toUnsignedString(int i, int shift) {
	char[] buf = new char[32];
	int charPos = 32;
	int radix = 1 << shift;
	int mask = radix - 1;
	do {
	    buf[--charPos] = digits[i & mask];
	    i >>= shift; // FIXME should be unsigned shift here.
	} while (i != 0);

	return new String(buf, charPos, (32 - charPos));
    }

}
 
}
