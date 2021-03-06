using System;
using gnu.util;

namespace gnu.app {


/** Application with command-line parsing. */
public class Application {
  protected bool help_option, exit_now;
  protected Option option;



  protected Application (String [] args) : this (args, new Option (args))
  {
  }


  /** 
   * Allow subclass to override {@link #option}. 
   * @see gnu.x11.Application#Application
   */
  protected Application (String [] args, Option option) {
    this.option = option;
    help_option = option.flag ("help", 
      "display this help screen and exit");
  }


  /**
   * #about(String, String, String, String, String)
   */
  protected virtual void about (String version, String description,
    String author, String url) {
    
    about (version, description, author, url, "");
  }


  /**
   * Check if print "about" and possible options and then exit. This method
   * should be called only once after all options are specified.
   */
  protected virtual void about (String version, String description,
    String author, String url, String extra) {

    if (help_option) option.about (this, version, description, author, url,
      "[OPTION]...", extra);

    if (option.invalid () || help_option) exit ();
  }


  protected virtual void exit () {
    exit_now = true;
  }
}
}
