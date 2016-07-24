using System;

using gnu.x11;

namespace gnu.app.redbook {


public class Checkerboard {

	private static Object m_lock = new Object();
	private static bool m_initialized = false;
	private static Data m_PIXELS;
	private static Data m_RED_PIXELS;
	private static Data m_RGB_PIXELS;
	private static Data m_SUB_PIXELS;

  public static Data PIXELS { get { init(); return m_PIXELS; } }
  public static Data RED_PIXELS { get { init(); return m_RED_PIXELS; } }
  public static Data RGB_PIXELS { get { init(); return m_RGB_PIXELS; } }
  public static Data SUB_PIXELS { get { init(); return m_SUB_PIXELS; } }

  public const int SIZE = 64;
  public const int SUB_SIZE = 16;


  private static void init() {
	lock(m_lock) {
	if(m_initialized) return;
	m_initialized=true;
    byte [] [] [] pixels;


    pixels = new byte [SIZE][][];

    for (int i=0; i<SIZE; i++)
	{
		pixels[i]= new byte[SIZE][];
      for (int j=0; j<SIZE; j++) {
        bool b1 = (i & 0x8) == 0;
        bool b2 = (j & 0x8) == 0;
        int c = (b1 && !b2) || (!b1 && b2) ? 255 : 0;
		pixels[i][j]=new byte[4];
        pixels [i] [j] [0] = (byte) c;
        pixels [i] [j] [1] = (byte) c;
        pixels [i] [j] [2] = (byte) c;
        pixels [i] [j] [3] = (byte) 255;
      }
    }
    m_PIXELS = new Data (pixels);


    pixels = new byte [SIZE][][];

    for (int i=0; i<SIZE; i++) {
		pixels[i]= new byte[SIZE][];
      for (int j=0; j<SIZE; j++) {
        bool b1 = (i & 0x8) == 0;
        bool b2 = (j & 0x8) == 0;
        int c = (b1 && !b2) || (!b1 && b2) ? 255 : 0;
		pixels[i][j]=new byte[4];
        pixels [i] [j] [0] = (byte) c;
        pixels [i] [j] [1] = (byte) 0;
        pixels [i] [j] [2] = (byte) 0;
        pixels [i] [j] [3] = (byte) 255;
      }
    }
    m_RED_PIXELS = new Data (pixels);


    pixels = new byte [SIZE][][];

    for (int i=0; i<SIZE; i++) {
		pixels[i]= new byte[SIZE][];
      for (int j=0; j<SIZE; j++) {
        bool b1 = (i & 0x8) == 0;
        bool b2 = (j & 0x8) == 0;
        int c = (b1 && !b2) || (!b1 && b2) ? 255 : 0;

		pixels[i][j]=new byte[3];
        pixels [i] [j] [0] = (byte) c;
        pixels [i] [j] [1] = (byte) c;
        pixels [i] [j] [2] = (byte) c;
      }
	}
    m_RGB_PIXELS = new Data (pixels);


    pixels = new byte [SUB_SIZE][][];

    for (int i=0; i<SUB_SIZE; i++) {
		pixels[i]= new byte[SUB_SIZE][];
      for (int j=0; j<SUB_SIZE; j++) {
        bool b1 = (i & 0x4) == 0;
        bool b2 = (j & 0x4) == 0;
        int c = (b1 && !b2) || (!b1 && b2) ? 255 : 0;
		pixels[i][j]=new byte[4];
        pixels [i] [j] [0] = (byte) c;
        pixels [i] [j] [1] = (byte) 0;
        pixels [i] [j] [2] = (byte) 0;
        pixels [i] [j] [3] = (byte) 255;
      }
	}
    m_SUB_PIXELS = new Data (pixels);
  }}
}    
}
