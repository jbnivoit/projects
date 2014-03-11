@rem 	perl -MWin32::ShellExt::FIGlet -e "Win32::ShellExt::FIGlet->uninstall;"
@rem removing 
@rem removing Classes/CLSID/{8DFDEE29-021D-49A1-AD5F-AEE95EA6B291}
@rem removing Classes/*/shellex/ContextMenuHandlers/Win32::ShellExt::FIGlet menu
@rem removing LMachine/SOFTWARE/Microsoft/Windows/CurrentVersion/Shell Extensions/Approved/{8DFDEE29-021D-49A1-AD5F-AEE95EA6B291}

@rem perl  -MWin32::TieRegistry -e "	$Registry->Delimiter('/'); delete $Registry->{Classes/CLSID/{8DFDEE29-021D-49A1-AD5F-AEE95EA6B291}/InProcServer32}; "

perl -e ' use Win32::TieRegistry; $Registry->Delimiter->("/"); delete $Registry->{"Classes/*/shellex/ContextMenuHandlers/$alias";'
