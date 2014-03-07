/*
// This file is 'gtkmine.h'
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
#ifndef __GtkMine_H__
#define __GtkMine_H__

#include <gdk/gdk.h>
#include <gtk/gtkvbox.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define GTK_MINE(obj)          GTK_CHECK_CAST (obj, gtk_mine_get_type (), GtkMine)
#define GTK_MINE_CLASS(klass)  GTK_CHECK_CLASS_CAST (klass, gtk_mine_get_type (), GtkMineClass)
#define IS_GTK_MINE(obj)       GTK_CHECK_TYPE (obj, gtk_mine_get_type ())
#define GTK_IS_MINE(obj)       IS_GTK_MINE(obj)       


  typedef struct _GtkMine       GtkMine;
  typedef struct _GtkMineClass  GtkMineClass;

#define TIME_LABEL  "Time"
#define MINES_LABEL "Mines"

typedef enum {
  COVERED=FALSE,
  UNCOVERED=TRUE,
  FLAGGED,
} CoverState;

typedef enum {
  N_ZERO=0,
  N_ONE, N_TWO, N_THREE, N_FOUR, /* number of neighbor square with a mine */
  N_FIVE, N_SIX, N_SEVEN, N_EIGHT,
  COOL, HAPPY, DEAD, PRESS, QUESTION,
  EMPTY, MINE, FLAG, 
  NUMBER_OF_PIXMAPS
} SquareState;

typedef enum { 
  LEVEL_EASY=0, LEVEL_MEDIUM=1, LEVEL_HARD=2, LEVEL_CUSTOM, 
} Difficulty;

typedef enum {
  PLAY_AGAIN, YOU_WON, YOU_LOST,
} GameState;

struct _GtkMine
{
  GtkVBox vbox;
  
  GtkWidget ***buttons;
  gint width, height;
  GtkWidget *status_bar;
  GtkWidget *time_entry, *mines_entry;
  GtkWidget *smiley;
  GtkWidget *table;
  gint context_id;
  /*  MineSweeper *ms;*/
  
  gint mines_count;
  gint time;
  gint timeout;
  gint game_started;
  gint tag; /* tag used for the timeout function used to refresh the timer */
  
  GdkPixmap **pixmap;
  GdkPixmap **mask;
  gchar ***xpm_data;
  GtkWidget ***pixmapwid;
  GtkWidget ***pixwid;
  GtkStyle *style;
  
  guint **handlers;

  /*Level level;*/
  unsigned char **field; 
  unsigned char **uncovered; 
  unsigned int uncovered_count;
  unsigned int flagged_count;
};

struct _GtkMineClass
{
  GtkVBoxClass parent_class;

  void (*gtkmine)(GtkMine *mine);
};

guint          gtk_mine_get_type            (void);
GtkWidget*     gtk_mine_new                 (void);
GtkWidget*     gtk_mine_new_with_dimensions (gint,gint,gint,gint);
GtkWidget*     gtk_mine_new_with_level      (gint);
void	       gtk_mine_clear               (GtkMine *mine);
void           gtk_mine_set_dimensions      (gint, gint);

extern gint current_width, current_height, current_timeout, current_minecount;

typedef struct {
  int width;
  int height;
  int mines;
  int timeout;
} GtkMineLevel;

extern GtkMineLevel gtk_mine_levels[];


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __GtkMine_H__ */
