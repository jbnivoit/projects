# -*- cperl -*-
# (C) 2002 Jean-Baptiste Nivoit
package Win32::ShellExt::CtxtMenu::MagickConvertJPG;

use Image::Magick 5.41;
use Win32::ShellExt::CtxtMenu;

$Win32::ShellExt::CtxtMenu::MagickConvertJPG::VERSION='0.1';
$Win32::ShellExt::CtxtMenu::MagickConvertJPG::COMMAND="Convert to JPEG";
@Win32::ShellExt::CtxtMenu::MagickConvertJPG::ISA=qw(Win32::ShellExt::CtxtMenu);

sub new() {
  my $proto = shift;
  my $class = ref($proto) || $proto;
  my $self  = {};
  bless ($self, $class);
  return $self;
}

sub query_context_menu() {
	my $self = shift;
	# @_ now holds a list of file paths to test to decide whether or not to pop our extension's menu.

	# return false if the menu item is not to be included, or a string to 
	# be used as display value if it is.
	my $ok = "Win32::ShellExt::CtxtMenu::MagickConvertJPG";

	$ok;
}

sub action() {
	my $self = shift;
	# @_ now holds the list of file paths we want to act on.	

	# this probably would be a good place to start a separate thread to do the job, otherwise it'll block the explorer.
	map {
	  unless(/\.je?pg$/i) { # nothing to do if it's already a jpg file.
	    my $img=Image::Magick->new;
	    my ($infile,$outfile)= ($_,$_);
	    $outfile =~ s!\.([^.]+)$!\.jpg!g;
	    my $status=$img->ReadImage($infile);
	    $status=$img->WriteImage( filename=>"$outfile" ) ;
	  }
	} @_;

	1;
}

sub hkeys() {
	my $h = {
	"CLSID" => "{EBC2A291-B2B1-4400-99C3-1AD296A3BEB9}",
	"name"  => "MagickConvertJPG shell Extension",
	"package" => "Win32::ShellExt::CtxtMenu::MagickConvertJPG"
	};
	$h;
}

1;
