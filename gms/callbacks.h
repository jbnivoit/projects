/*
// This file is 'callbacks.h'
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
#ifndef __CallBacks_H__
#define __CallBacks_H__
#include <gtk/gtk.h>
#include "version.h"

#define DECLARE_CALLBACK(cb) \
 void cb(GtkWidget *widget, gpointer data)

#define FILE_MENU_LABEL "File"
#define GAME_MENU_LABEL "Game"
#define HELP_MENU_LABEL "Help"

#define NEW_MENUITEM_LABEL        "New Game"
#define HIGHSCORES_MENUITEM_LABEL "High Scores"
#define QUIT_MENUITEM_LABEL       "Quit"
#define EASY_MENUITEM_LABEL       "Easy"
#define MEDIUM_MENUITEM_LABEL     "Medium"
#define HARD_MENUITEM_LABEL       "Hard"
#define CUSTOMIZE_MENUITEM_LABEL  "Customize"
#define ABOUT_MENUITEM_LABEL      "About"
#define LICENSE_MENUITEM_LABEL    "License"
#define HOWTOPLAY_MENUITEM_LABEL "How To Play"

DECLARE_CALLBACK(FileNewCallback);
DECLARE_CALLBACK(FileHighscoresCallback);
DECLARE_CALLBACK(FileQuitCallback);

DECLARE_CALLBACK(GameEasyCallback);
DECLARE_CALLBACK(GameMediumCallback);
DECLARE_CALLBACK(GameHardCallback);
DECLARE_CALLBACK(GameCustomizeCallback);

DECLARE_CALLBACK(HelpAboutCallback);
DECLARE_CALLBACK(HelpLicenseCallback);
DECLARE_CALLBACK(HelpHowtoplayCallback);

DECLARE_CALLBACK(MineCallback);

#ifndef _DEBUG
#define DEBUG_CALLBACK(f)
#else
#include <stdio.h>
#define DEBUG_CALLBACK(f) printf("%s called\n",f);
#endif

void ModalInfoBox(gchar *text, gchar *title);

typedef struct { 
  char *label;
  DECLARE_CALLBACK((*cb));
} MenuEntry;

typedef struct {
  char *label;
  int num;
  MenuEntry *entries;
} Menu;

typedef struct {
  int num;
  Menu *menus;
} MenuBar;

void buildMenuBar(MenuBar *, GtkWidget *);

extern MenuBar menuBar;

extern int current_level;

#endif
