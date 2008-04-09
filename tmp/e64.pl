
use MIME::Base64 qw(encode_base64);

local *IN;
local *OUT;
open(IN, "test.txt") or die "$!";
open OUT, ">test.uue" or die "$!";
while (<IN>) {
  print OUT encode_base64($_);
}
close IN;
close OUT;


