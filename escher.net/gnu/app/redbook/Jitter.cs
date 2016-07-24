using System;

namespace gnu.app.redbook {


/** 
 * Jitter point arrays for 2, 3, 4, 8, 15, 24 and 66 jitters. Values are
 * floating point in the range -.5 < x < .5, -.5 < y < .5, and have a
 * gaussian distribution around the origin.
 *
 * <p>Use these to do model jittering for scene anti-aliasing and view volume
 * jittering for depth of field effects.
 *
 * <p>Modified from <code>jitter.h</code> in <a href=
 * "http://trant.sgi.com/opengl/examples/redbook/redbook.html">
 * redbook</a> by SGI.
*/
public class Jitter {
  public static readonly float [] [] J2 = new float[] []{
    new float[]{0.246490f, 0.249999f},
    new float[]{-0.246490f, -0.249999f}
  };


  public static readonly float [] [] J3 = new float[][]{
    new float[] {-0.373411f, -0.250550f},
    new float[] {0.256263f, 0.368119f},
    new float[] {0.117148f, -0.117570f}
  };


  public static readonly float [] [] J4 = new float[][]{
    new float[] {-0.208147f, 0.353730f},
    new float[] {0.203849f, -0.353780f},
    new float[] {-0.292626f, -0.149945f},
    new float[] {0.296924f, 0.149994f}
  };


  public static readonly float [] [] J8 = new float[][]{
    new float[] {-0.334818f, 0.435331f},
    new float[] {0.286438f, -0.393495f},
    new float[] {0.459462f, 0.141540f},
    new float[] {-0.414498f, -0.192829f},
    new float[] {-0.183790f, 0.082102f},
    new float[] {-0.079263f, -0.317383f},
    new float[] {0.102254f, 0.299133f},
    new float[] {0.164216f, -0.054399f}
  };


  public static readonly float [] [] J15 = new float[][]{
    new float[] {0.285561f, 0.188437f},
    new float[] {0.360176f, -0.065688f},
    new float[] {-0.111751f, 0.275019f},
    new float[] {-0.055918f, -0.215197f},
    new float[] {-0.080231f, -0.470965f},
    new float[] {0.138721f, 0.409168f},
    new float[] {0.384120f, 0.458500f},
    new float[] {-0.454968f, 0.134088f},
    new float[] {0.179271f, -0.331196f},
    new float[] {-0.307049f, -0.364927f},
    new float[] {0.105354f, -0.010099f},
    new float[] {-0.154180f, 0.021794f},
    new float[] {-0.370135f, -0.116425f},
    new float[] {0.451636f, -0.300013f},
    new float[] {-0.370610f, 0.387504f}
  };


  public static readonly float [] [] J24 = new float[][]{
    new float[] {0.030245f, 0.136384f},
    new float[] {0.018865f, -0.348867f},
    new float[] {-0.350114f, -0.472309f},
    new float[] {0.222181f, 0.149524f},
    new float[] {-0.393670f, -0.266873f},
    new float[] {0.404568f, 0.230436f},
    new float[] {0.098381f, 0.465337f},
    new float[] {0.462671f, 0.442116f},
    new float[] {0.400373f, -0.212720f},
    new float[] {-0.409988f, 0.263345f},
    new float[] {-0.115878f, -0.001981f},
    new float[] {0.348425f, -0.009237f},
    new float[] {-0.464016f, 0.066467f},
    new float[] {-0.138674f, -0.468006f},
    new float[] {0.144932f, -0.022780f},
    new float[] {-0.250195f, 0.150161f},
    new float[] {-0.181400f, -0.264219f},
    new float[] {0.196097f, -0.234139f},
    new float[] {-0.311082f, -0.078815f},
    new float[] {0.268379f, 0.366778f},
    new float[] {-0.040601f, 0.327109f},
    new float[] {-0.234392f, 0.354659f},
    new float[] {-0.003102f, -0.154402f},
    new float[] {0.297997f, -0.417965f}
  };


  public static readonly float [] [] J66 = new float[][]{
    new float[] {0.266377f, -0.218171f},
    new float[] {-0.170919f, -0.429368f},
    new float[] {0.047356f, -0.387135f},
    new float[] {-0.430063f, 0.363413f},
    new float[] {-0.221638f, -0.313768f},
    new float[] {0.124758f, -0.197109f},
    new float[] {-0.400021f, 0.482195f},
    new float[] {0.247882f, 0.152010f},
    new float[] {-0.286709f, -0.470214f},
    new float[] {-0.426790f, 0.004977f},
    new float[] {-0.361249f, -0.104549f},
    new float[] {-0.040643f, 0.123453f},
    new float[] {-0.189296f, 0.438963f},
    new float[] {-0.453521f, -0.299889f},
    new float[] {0.408216f, -0.457699f},
    new float[] {0.328973f, -0.101914f},
    new float[] {-0.055540f, -0.477952f},
    new float[] {0.194421f, 0.453510f},
    new float[] {0.404051f, 0.224974f},
    new float[] {0.310136f, 0.419700f},
    new float[] {-0.021743f, 0.403898f},
    new float[] {-0.466210f, 0.248839f},
    new float[] {0.341369f, 0.081490f},
    new float[] {0.124156f, -0.016859f},
    new float[] {-0.461321f, -0.176661f},
    new float[] {0.013210f, 0.234401f},
    new float[] {0.174258f, -0.311854f},
    new float[] {0.294061f, 0.263364f},
    new float[] {-0.114836f, 0.328189f},
    new float[] {0.041206f, -0.106205f},
    new float[] {0.079227f, 0.345021f},
    new float[] {-0.109319f, -0.242380f},
    new float[] {0.425005f, -0.332397f},
    new float[] {0.009146f, 0.015098f},
    new float[] {-0.339084f, -0.355707f},
    new float[] {-0.224596f, -0.189548f},
    new float[] {0.083475f, 0.117028f},
    new float[] {0.295962f, -0.334699f},
    new float[] {0.452998f, 0.025397f},
    new float[] {0.206511f, -0.104668f},
    new float[] {0.447544f, -0.096004f},
    new float[] {-0.108006f, -0.002471f},
    new float[] {-0.380810f, 0.130036f},
    new float[] {-0.242440f, 0.186934f},
    new float[] {-0.200363f, 0.070863f},
    new float[] {-0.344844f, -0.230814f},
    new float[] {0.408660f, 0.345826f},
    new float[] {-0.233016f, 0.305203f},
    new float[] {0.158475f, -0.430762f},
    new float[] {0.486972f, 0.139163f},
    new float[] {-0.301610f, 0.009319f},
    new float[] {0.282245f, -0.458671f},
    new float[] {0.482046f, 0.443890f},
    new float[] {-0.121527f, 0.210223f},
    new float[] {-0.477606f, -0.424878f},
    new float[] {-0.083941f, -0.121440f},
    new float[] {-0.345773f, 0.253779f},
    new float[] {0.234646f, 0.034549f},
    new float[] {0.394102f, -0.210901f},
    new float[] {-0.312571f, 0.397656f},
    new float[] {0.200906f, 0.333293f},
    new float[] {0.018703f, -0.261792f},
    new float[] {-0.209349f, -0.065383f},
    new float[] {0.076248f, 0.478538f},
    new float[] {-0.073036f, -0.355064f},
    new float[] {0.145087f, 0.221726f}
  };
}
}
