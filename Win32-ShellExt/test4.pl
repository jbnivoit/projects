# -*- cperl -*-

use Win32::ShellExt::CtxtMenu::RenameWithPrefix;

unlink "a001.jpg";
unlink "b001.jpg";

print "######### test with no existing file\n";
Win32::ShellExt::CtxtMenu::RenameWithPrefix->test;

local *F;
open F, ">a001.jpg";
print F "test file";
close F;

print "######### test with existing file\n";
Win32::ShellExt::CtxtMenu::RenameWithPrefix->test;

open F, ">b001.jpg";
print F "test file";
close F;

print "######### test with existing file\n";
Win32::ShellExt::CtxtMenu::RenameWithPrefix->test;

my @args = qw/11908r128.jpg 11908r130.jpg 11908r131.jpg 11908r134.jpg 11908r135.jpg 11908r137.jpg 11908r139.jpg 11908r142.jpg 11908r144.jpg 11908r145.jpg 11908r148.jpg 11908r151.jpg 11908r156.jpg 11908r158.jpg 11908r161.jpg 11908r162.jpg 11908r164.jpg 11908r167.jpg 11908r168.jpg 11908r169.jpg/;

print "######### test with existing file\n";
Win32::ShellExt::CtxtMenu::RenameWithPrefix->test(@args);

