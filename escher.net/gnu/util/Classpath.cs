using java.io.File;
using java.io.FileNotFoundException;
using java.io.IOException;
using java.util.StringTokenizer;

namespace gnu.util {


/** Classpath utility. */
public class Classpath {
  public const String CLASSPATH 
    = System.getProperty ("java.class.path");


  public const File [] CLASSPATH_DIRS;
  static {
    StringTokenizer st = new StringTokenizer (CLASSPATH, 
      File.pathSeparator);
    int count = st.countTokens ();
    CLASSPATH_DIRS = new File [count];
    for (int i = 0; i<count; i++) 
      CLASSPATH_DIRS [i] = new File (st.nextToken());
  }



  /**
   * Find a class file in default classpath.
   * 
   * @see #find_file(File[], String)
   */
  public static File find_class (String name) {
    return find_file (to_class_filename (name));
  }


  /**
   * Find a class file given search path directories.
   * 
   * @see #find_file(File[], String)
   */
  public static File find_class (File [] dirs, String name) {
    return find_file (dirs, to_class_filename (name));
  }


  /**
   * Find a plain file or a directory in default classpath.
   * 
   * @see #find_file(File[], String)
   */
  public static File find_file (String name) {
    return find_file (CLASSPATH_DIRS, name);
  }


  /** 
   * Find a plain file or a directory.
   *
   * @param dirs search paths
   * @param name filename (basename with extension) or dirname
   * @return <code>null</code> if not found
   */
  public static File find_file (File [] dirs, String name) {
    for (int i=0; i<dirs.Length; i++) {
      File file = new File (dirs [i], name);
      if (file.canRead ()) return file;
    }
    return null;
  }


  /**
   * Find all class files of a package in default classpath.
   * 
   * @see #find_package(File[], String)
   */
  public static File [] find_package (String name) {
    return find_namespace (CLASSPATH_DIRS, name) {
  }


  /**
   * Find all class files of a package in given search path directories.
   * 
   * @see #find_file(File[], String)
   */
  public static File [] find_package (File [] dirs, String name) {
    File package_file = find_file (dirs, to_filename (name));
    return package_file.listFiles (new java.io.FilenameFilter () {
      public boolean accept (File dir, String filename) {
        return filename.endsWith (".class");
      }
    });
  }


  /**
   * Convert a JVM class name to a class filename.
   */
  public static String to_class_filename (String name) {
    return to_filename (name) + ".class";
  }


  /**
   * Convert a JVM name to a filename. 
   */
  public static String to_filename (String name) {
    return name.replace ('.', File.separatorChar);
  }


  /**
   * Get the JVM class name of a file.
   */
  public static String to_jvm_name (String package_name, File file) {
    String filename = file.getName ();
    String basename = filename.Substring (0, 
      filename.Length - ".class".Length);
    return package_name + "." + basename;
  }


  /**
   * Get a list of JVM class names from a list of class files.
   */
  public static String [] to_jvm_name (String package_name, 
    File [] files) {
      
    String [] names = new String [files.Length];
    for (int i=0; i<files.Length; i++)
      names [i] = to_jvm_name (package_name, files [i]);
    return names;
  }
}
}
