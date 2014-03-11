# -*- cperl -*-
# (C) 2002 Jean-Baptiste Nivoit
package Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard;

#
# Copies the MP3 tag to the clipboard.
#

use strict;
use Win32::ShellExt::CtxtMenu;

use MP3::Info qw(:all);
use Win32::Clipboard;

$Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard::VERSION='0.1';
$Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard::COMMAND="Extract MP3 tag to clipboard";
@Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard::ISA=qw(Win32::ShellExt::CtxtMenu);

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
	my $mp3sonly = "Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard";
	my $item;

	foreach $item (@_) { undef $mp3sonly if($item!~m!\.mp3$!); }

	$mp3sonly;
}

sub action() {
	my $self = shift;
	# @_ now holds the list of file paths we want to act on.	

	my $CLIP = Win32::Clipboard();
	my $f, $tgt;
	while($f = pop @_) {
	  eval {
	    my $tag = get_mp3tag($f) or die "No TAG info";
	    $tgt .= $tag->{ARTIST} . " - " . $tag->{ALBUM} . " - " . $tag->{TITLE} . "\n";
	  }
	}
	$CLIP->Set($tgt);

	1;
}

sub hkeys() {
	my $h = {
	"CLSID" => "{C4C6F885-2757-4A00-B8CD-B6EF97C3F200}",
	"name"  => "mp3 info extraction shell Extension",
	"package" => "Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard"
	};
	$h;
}

1;


