/*
// This file is 'main.c'
// It is part of the 'gms' distribution.
//
//    gms (Gtk MineSweeper), yet another mine sweeper program
//    Copyright (C) 1999 Jean-Baptiste Nivoit <jbn@multimania.com>
//    The full LICENSE can be found in the 'License' file of the 
//    distribution.
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// Creation : 		03/01/1999 by JBN
// Last Modification : 	03/01/1999 by JBN
*/ 
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include "gtkmine.h"
#include "callbacks.h"
#include "scores.h"

GtkWidget *window, *mainvbox;
GtkWidget *mine;
int current_level = 0;
static void cleanup()
{
  saveScores(currentScores,currentScoresFile);
}

int main (int argc,char **argv)
{
  char *scorefile = (char*)NULL;
  
  gtk_init(&argc,&argv);
  gtk_rc_parse("~/.gtkrc");
  atexit(cleanup);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  gtk_window_set_title(GTK_WINDOW(window),"Yet Another Mine Sweeper");
  
  gtk_signal_connect(GTK_OBJECT(window),"destroy",
		     GTK_SIGNAL_FUNC(gtk_exit),EXIT_SUCCESS);
  
  gtk_container_border_width(GTK_CONTAINER(window),0);

  mainvbox = gtk_vbox_new(FALSE,TRUE);
  gtk_container_border_width(GTK_CONTAINER(mainvbox),0); 
  gtk_container_add(GTK_CONTAINER(window),mainvbox);
  gtk_widget_show(mainvbox);
  buildMenuBar(&menuBar,mainvbox);
  
  mine = gtk_mine_new_with_level(LEVEL_EASY);
  /*mine = gtk_mine_new_with_dimensions(levels[0].width,levels[0].height,levels[0].mines,levels[0].timeout);*/
  if(mine==(GtkWidget*)NULL) /* let's try again! */
    mine = gtk_mine_new();

  if(mine!=(GtkWidget*)NULL)
    {
      gtk_signal_connect(GTK_OBJECT(mine),"mine",GTK_SIGNAL_FUNC(MineCallback),NULL);
      gtk_container_add(GTK_CONTAINER(mainvbox),mine);
      gtk_widget_show(mine);
    }

  gtk_widget_show(window);

  /*readScores(scorefile);*/
  readScores("SCORES");
  
  gtk_main();
  
  return EXIT_SUCCESS;
}

