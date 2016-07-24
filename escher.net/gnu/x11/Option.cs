using System;
namespace gnu.x11 {


/** X {@link gnu.util.Option}. */
public class Option : gnu.util.Option {
  public Option (String [] args)
    : base (args) {}
  
  public Display.Name display_name (String name, String description,
    Display.Name default_value) {

    Display.Name retval = default_value;
    
    try {
      String opt = option (name);
      if (opt != null) retval = new Display.Name (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "display name", description, default_value.ToString (),   
	      retval.ToString ());
    return retval;
  }


  public RGB rgb (String name, String description, RGB default_value) {
    RGB retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = new RGB (opt);

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "RGB", description, 
      default_value.spec (), retval.spec ());
    return retval;
  }


  public Rectangle rectangle (String name, String description, 
    Rectangle default_value) {

    Rectangle retval = default_value;

    try {
      String opt = option (name);
      if (opt != null) retval = new Rectangle (option (name));

    } catch (Exception e) {
      invalid_names.Append (name + ", ");
      // fall through
    }

    add_spec (name, "Rectangle", description, 
      default_value.spec (), retval.spec ());
    return retval;
  }
}

}
