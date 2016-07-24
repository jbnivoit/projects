using System;
using System.Text;
using System.Collections;

namespace gnu.util {


/**
 * Primitive command-line option parsing.
 *
 * <p>Only long option is supported, for clarity and easy parsing. GNU long
 * option requires a equal sign "=" between the option name and option
 * value. No equal sign is required (allowed) here, for clarity and easy
 * parsing, again.
 *
 * <p>Usual approach to option parsing such as that in GNU
 * <code>getopt</code> may not be the best in Java because Java does not
 * support pointer needed for uniform argument type and pass-by-reference. 
 * Instead this library uses "explicit method call per option". By this
 * type checking can be strictly enforced and return value can be directly
 * assigned to the desired variable. No boxing of primitive types or
 * un-boxing of wrapper classes will take place. Moreover, instead of
 * combining arrays of option table, option can be specified in base
 * classes and subclasses easily. One caveat is that option values cannot
 * be used in initializations of class member variables because parsing
 * takes place outside constructors. For instance, {@link
 * gnu.x11.Application} cannot initialize and create a window member
 * variable because parsing is not done yet and <code>Display</code> may
 * not be initialized; a window can be created only after all parsings.
 */
public class Option {
  public String [] args;
  public bool noisy;
  public StringBuilder spec = new StringBuilder ();
  public StringBuilder invalid_names = new StringBuilder ();
  public ArrayList valid_names = new ArrayList ();


  public Option (String [] args) {
    this.args = args;

    noisy = booleann ("noisy-option-parser", 
      "show working of option parsing", false);
  }


  /** 
   * Print "about" and list possible options. This method
   * should be called only once after all options are specified.
   *
   * <p>Note that this package is under GNU Public License, and thus all
   * programs using this package MUST be under GNU Public License.
   */
  public void about (Object obj, String version, String description,
    String author, String url, String usage, String extra) {

    String name = obj.GetType ().ToString();

    Console.WriteLine ("\n" + name + " (" + version + ") - " + description
      + ".\nCopyright (C) " + author
      + ". Under GNU Public License.\n" + url
      + ".\n\nUsage: java " + name + " " + usage
      + "\n\nPossible options:\n"
      + spec + extra);

    spec = null;                // help garbage collection
  }


  public void add_spec (String name, String type, String description,
    String default_value, String return_value) {

    spec.Append ("  --" + name + " [" + type + "] " + description
      + " (" + default_value + ")\n");
    valid_names.Add ("--" + name);

    if (noisy) Console.WriteLine (name + " --> " + return_value);
  }


  public bool booleann (String name, String description, 
    bool default_value) {

    bool retval = default_value;

    try {
      String opt = option (name);
      if (opt != null && opt.Equals ("true")) retval = true;
      if (opt != null && opt.Equals ("false")) retval = false;

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "boolean", description, 
      default_value.ToString(), retval.ToString());
    return retval;
  }
 

  public double doublee (String name, String description,
    double default_value) {

    double retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = Double.Parse (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "double", description, 
      default_value.ToString(), retval.ToString()); 
    return retval;
  }


  public int Enum (String name, String description,
    String [] enum_strings, int default_value) {     
      
    int retval = default_value;

    try {
      String opt = option (name);
      bool successful = false;
      if (opt != null) {
        for (int i=0; i<enum_strings.Length; i++)
          if (opt.Equals (enum_strings [i])) {           
            successful = true;
            retval = i;            
            break;
          }
        if (!successful) throw new Exception ();
      }

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }


    StringBuilder sb = new StringBuilder ("enum: ");
    for (int i=0; i<enum_strings.Length; i++)
      sb.Append (enum_strings [i] + ", ");    
    sb.Remove (sb.Length-2, 2); // delete last ", "

    add_spec (name, sb.ToString (), description, 
      enum_strings [default_value], enum_strings [retval]);
    return retval;
  }    


  public double doublet (String name, String description,
    double default_value) {

    double retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = Double.Parse (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "double", description, 
      default_value.ToString(), retval.ToString()); 
    return retval;
  }


  public double doublet (String name, String description,
    double default_value, double low, double high) {

    double retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = Double.Parse (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    String full_description = description + " from " + low + " to " + high;
    retval = Math.clamp (retval, 0.0f, 1.0f);
    add_spec (name, "double", full_description, 
      default_value.ToString(), retval.ToString()); 
    return retval;
  }


  protected int index (String name) {
    for (int i=0; i<args.Length; i++)
      if (args [i].Equals ("--" + name))
        return i;

    return -1;
  }


  public bool invalid () {
    for (int i=0; i<args.Length; i++) {
      String arg = args [i];

      if (arg.StartsWith ("--")) // option
        if (arg.Length == 2) // end-option-mark
          break;

        else if (!valid_names.Contains (arg))
          invalid_names.Append (arg + ", ");
    }

    int n = invalid_names.Length;
    bool any = n > 2;
    if (any) {
      invalid_names.Remove (n-2, n); // delete last ", "
      Console.WriteLine ("\nInvalid options: " + invalid_names);
      Console.WriteLine ("Try --help for a list of valid options.");
    }

    invalid_names = null;       // help garbage collection
    valid_names = null;         // help garbage collection
    return any;
  }


  public int intt (String name, String description, 
    int default_value) {
 
    int retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = Int32.Parse (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "int", description, 
      default_value.ToString(), retval.ToString()); 
    return retval;
  }


  public int intt (String name, String description, 
    int default_value, int low, int high) {

    int retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = Int32.Parse (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    String full_description = description + " from " + low + " to " + high;
    retval = Math.clamp (retval, low, high);
    add_spec (name, "int", description, 
      default_value.ToString(), retval.ToString()); 
    return retval;
  }


  public long longg (String name, String description,
    long default_value) {

    long retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = Int64.Parse (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "long", description, 
      default_value.ToString(), retval.ToString()); 
    return retval;
  }


  public String option (String name, String ignored, String dummy) {
	return option(name);
	}
  public String option (String name) {
    int idx = index (name);
    if (idx == -1 || idx == args.Length-1) return null;
    return args [idx+1];
  }


  public bool flag (String name, String description) {
    bool retval = index (name) != -1;
    add_spec (name, "flag", description, "absent",
      retval ? "present" : "absent");
    return retval;
  }


  public double scale (String name, String description,
    double default_value) {

    return doublet (name, description, default_value, 0.0f, 1.0f);
  }
  

  public String buildString (String name, String description, 
    String default_value) {

    String retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = opt;

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "String", description, default_value, retval);
    return retval;
  }
}
}
