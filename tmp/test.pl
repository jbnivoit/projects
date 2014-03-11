use Win32::TieRegistry ( Delimiter=>"/" );
#, ArrayValues=>1 );
	
$Registry->Delimiter("/");

my @hkeys = (
	#	"Classes/CLSID/$CLSID" ,
	"Classes/CLSID/$CLSID/InProcServer32/ThreadingModel",
	"Classes/CLSID/$CLSID/InProcServer32/PerlShellExtScript",
	"Classes/CLSID/$CLSID/InProcServer32/PerlPackage",
	"LMachine/SOFTWARE/Microsoft/Windows/CurrentVersion/Shell Extensions/Approved/$CLSID" ,
#	"Classes/CLSID/$CLSID",
	"Classes/*/shellex/ContextMenuHandlers/$alias",
	"LMachine/SOFTWARE/Microsoft/Windows/CurrentVersion/Shell Extensions/Approved/$CLSID"
);

my $hkey;

while ($hkey = pop @hkeys) {
	my $val = $Registry->{$hkey};
	  print "$hkey => " . $val ."\n";
	if(ref($val)) {
		print join ',', keys %$val;
		print "\n";
	}
}
