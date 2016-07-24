namespace gnu.util {


/** Common math-related utility. */
public class Math {

  private static double max (double a, double b) {
	if(a>=b) {
		return a;
	} else {
		return b;
	}
  }

  private static double min (double a, double b) {
	if(b>=a) {
		return a;
	} else {
		return b;
	}
  }

  private static float max (float a, float b) {
	if(a>=b) {
		return a;
	} else {
		return b;
	}
  }

  private static float min (float a, float b) {
	if(b>=a) {
		return a;
	} else {
		return b;
	}
  }

  private static int max (int a, int b) {
	if(a>=b) {
		return a;
	} else {
		return b;
	}
  }

  private static int min (int a, int b) {
	if(b>=a) {
		return a;
	} else {
		return b;
	}
  }

  private static long max (long a, long b) {
	if(a>=b) {
		return a;
	} else {
		return b;
	}
  }

  private static long min (long a, long b) {
	if(b>=a) {
		return a;
	} else {
		return b;
	}
  }

  public static double clamp (double i, double low, double high) {
    return max (min (i, high), low);
  }


  public static float clamp (float i, float low, float high) {
    return max (min (i, high), low);
  }


  public static int clamp (int i, int low, int high) {
    return max (min (i, high), low);
  }


  public static long clamp (long i, long low, long high) {
    return max (min (i, high), low);
  }

	public static double toRadians(double degrees) {
		return degrees*System.Math.PI/180.0;
	}

}
}
