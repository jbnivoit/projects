## This file is 'Makefile'
## It is part of the 'gms' distribution.
##
##    gms (Gtk MineSweeper), yet another mine sweeper program
##    Copyright (C) 1999 Jean-Baptiste Nivoit <jbn@multimania.com>
##    The full LICENSE can be found in the 'License' file of the 
##    distribution.
##
##    This program is free software; you can redistribute it and/or modify
##    it under the terms of the GNU General Public License as published by
##    the Free Software Foundation; either version 2 of the License, or
##    (at your option) any later version.
##
##    This program is distributed in the hope that it will be useful,
##    but WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##    GNU General Public License for more details.
##
##    You should have received a copy of the GNU General Public License
##    along with this program; if not, write to the Free Software
##    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
##
## Creation : 		03/01/1999 by JBN
## Last Modification : 	03/01/1999 by JBN

VERSION=0.2
#CC=g++
CC=gcc
CFLAGS=-g `gtk-config --cflags` -D_DEBUG
##LINK=`gtk-config --libs` # release!
#LINK= -L/usr/X11R6/lib -lXext -lX11 -lm -L/usr/local/lib -lgtk -lgdk -lglib
LINK=../gtk/gtk+-1.0.5/gtk/.libs/libgtk.a \
	../gtk/gtk+-1.0.5/gdk/.libs/libgdk.a \
	../gtk/gtk+-1.0.5/glib/.libs/libglib.a \
	-lm -L/usr/X11R6/lib -lXext -lX11


all : gms

gms : main.o gtkmine.o callbacks.o scores.o # minesweeper.o 
	$(CC) $(CFLAGS) -o gms main.o gtkmine.o callbacks.o scores.o $(LINK)

gtkmine.o : gtkmine.c gtkmine.h
	$(CC) $(CFLAGS) -o gtkmine.o -c gtkmine.c

minesweeper.o : minesweeper.c minesweeper.h
	$(CC) $(CFLAGS) -o minesweeper.o -c minesweeper.c

callbacks.o : callbacks.c callbacks.h
	$(CC) $(CFLAGS) -o callbacks.o -c callbacks.c

scores.o : scores.c scores.h
	$(CC) $(CFLAGS) -o scores.o -c scores.c

main.o : main.c gtkmine.h
	$(CC) $(CFLAGS) -o main.o -c main.c

clean :
	$(RM) *.o *~ *.core gms

tar : 
	@(export T_PWD=`pwd` ; export T_DIR=`basename $$T_PWD`; cd ..; \
		export T_FILE=gms-$(VERSION).tar.gz ; \
		tar -z -c -v -f $$T_FILE $$T_DIR ; \
		mv $$T_FILE $$T_DIR \
	)

