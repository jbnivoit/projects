#! /bin/sh
perl -pe "s#\\\"(.*)\\\"#\"\${\join('',reverse(split//,\$1))}\"#g;" 2.xpm > 5.xpm
