# -*- cperl -*-
# (C) 2002 Jean-Baptiste Nivoit
package Win32::ShellExt::CtxtMenu::RenameWithPrefix;

use strict;
use Win32::ShellExt::CtxtMenu;

use MP3::Info qw(:all);
use Win32API::File 0.08 qw( :ALL );

$Win32::ShellExt::CtxtMenu::RenameWithPrefix::VERSION='0.1';
$Win32::ShellExt::CtxtMenu::RenameWithPrefix::COMMAND="Rename sequentially";
@Win32::ShellExt::CtxtMenu::RenameWithPrefix::ISA=qw(Win32::ShellExt::CtxtMenu);

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

  return undef if($#_==0);

  my $val = "Win32::ShellExt::CtxtMenu::RenameWithPrefix";
  my $ext = pop @_;
  $ext =~ s!^.*\.([^.]+)!$1!g;
  my $item;
  foreach $item (@_) {
    $item =~ s!^.*\.([^.]+)!$1!g;
    undef $val unless ($item eq $ext);
  }
  $val;
}

sub action() {
  my $self = shift;
  # @_ now holds the list of file paths we want to act on.	

  @_ = reverse sort @_;

  my @alphabet = split //, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  my $idx = 0;
  my $i=0;


    my $f = pop @_;
    my $ext = $f;
    $ext =~ s!^.*\.([^.]+)!$1!g;
    do {
      $i++;

      my $s = sprintf "%s%03d.%s", $alphabet[$idx], $i, $ext;
      #print "f=$f, s=$s\n";
      if($i==1) { # only allow prefix change for first element: this forces the whole series to have the same prefix all along.
	if(-e $s) {
	  # first prefix tried is not acceptable, try another one.
	  do {
	    $idx++;
	    $s = sprintf "%s%03d.%s", $alphabet[$idx], $i, $ext;
	  } while(-e $s);
	}
      }

      eval {
	#print "move $f => $s\n";

	# todo: check that we're moving the file in the same directory..
	my $p = $f;
	$p =~ s!\\[^\\]+$!\\!g; # extract target directory from path
	MoveFile( $f, "$p$s" );
      }
    } while ($f = pop @_);

  # do nothing in the base class for extensions.
  1;
}

sub hkeys() {
  my $h = {
	   "CLSID" => "{226D19F2-6964-497E-9FAE-354B49689168}",
	   "name"  => "file renaming shell Extension",
	   "package" => "Win32::ShellExt::CtxtMenu::RenameWithPrefix"
	  };
  $h;
}

sub test() {
  shift; # skip package/instance
  my $ref = Win32::ShellExt::CtxtMenu::RenameWithPrefix->new;

  my @args;
  if(defined(@_)) {
    @args = @_;
    printf "%s\n", $ref->query_context_menu(@_);
    $ref->action(@args);
    return;
  }

  @args = qw/001.jpg 002.jpg 003.jpg/;
  printf "%s\n", $ref->query_context_menu(@args);
  @args = qw/001.jpg 002.jpg 003.gif/;
  printf "%s\n", $ref->query_context_menu(@args);

  @args = qw/001.jpg 002.jpg 003.jpg/;
  $ref->action(@args);

}

1;
