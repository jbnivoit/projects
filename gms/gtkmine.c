/*
  // This file is 'gtkmine.c'
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
#include <sys/time.h>
#include <gtk/gtksignal.h>
#include <gtk/gtktable.h>
#include <gtk/gtktogglebutton.h>
#include <gtk/gtkstatusbar.h>
#include <gtk/gtkentry.h>
#include <gtk/gtkpixmap.h>
#include <gtk/gtkhseparator.h>
#include <gtk/gtklabel.h>
#include <gtk/gtkwindow.h>
#include <gdk/gdk.h>
#include <gdk/gdktypes.h>
#include <gdk/gdkprivate.h> /* Needed to access 'gdk_root_parent' which we need to create our pixmaps in advance */
#include "gtkmine.h"
#include "version.h"
#include "pixmaps/cool.xpm"
#include "pixmaps/happy.xpm"
#include "pixmaps/dead.xpm"
#include "pixmaps/fillface.xpm" /* mask */
#include "pixmaps/fillface.xbm" /* mask */
#include "pixmaps/press.xpm"
#include "pixmaps/question.xpm"
#include "pixmaps/mine.xpm"
#include "pixmaps/flag.xpm"
#include "pixmaps/uncovered.xpm"
#include "pixmaps/empty.xpm"
#include "pixmaps/1.xpm"
#include "pixmaps/2.xpm"
#include "pixmaps/3.xpm"
#include "pixmaps/4.xpm"
#include "pixmaps/5.xpm"
#include "pixmaps/6.xpm"
#include "pixmaps/7.xpm"
#include "pixmaps/8.xpm"

typedef struct {
  GtkMine *mine;
  gint x,y;
} GtkMineCbData;

enum {
  MINE_SIGNAL,
  LAST_SIGNAL
};

GtkMineLevel gtk_mine_levels[] = {
  { 10, 10, 10, 999 }, /* XXX implement time limit */
  { 16, 16, 40, 999 },
  { 30, 15, 99, 999 },
};

static void gtk_mine_class_init(GtkMineClass *klass);
static void gtk_mine_init      (GtkMine      *mine);
static void gtk_mine_toggle    (GtkWidget *widget, gpointer data);
static void gtk_mine_destroy   (GtkObject *object);
static void gtk_mine_dialog_open(gchar *text, gchar *title);

static gint default_width  = 16;
static gint default_height = 16;
gint current_width  = 16;
gint current_height = 16;
gint current_timeout = 20;
gint current_minecount = 20;

static guint gtk_mine_signals[LAST_SIGNAL] = { 0 };

static struct {
  gint dx, dy; 
} neighbor[] = {
  {-1,-1}, {-1,0}, {-1,1}, {0,1},
  {1,1}, {1,0}, {1,-1}, {0,-1},
};

static void gtk_mine_game_won_p(GtkMine *mine)
{
  DEBUG(("%s count:%d uncovered:%d flagged:%d\n",__PRETTY_FUNCTION__,mine->mines_count,mine->uncovered_count,mine->flagged_count));
  
  if(mine->uncovered_count+mine->flagged_count==mine->width*mine->height)
    {
      gtk_mine_dialog_open("You won!","Game over");
      gtk_timeout_remove(mine->tag); /* remove timed callback */
      gtk_statusbar_push(GTK_STATUSBAR(mine->status_bar),(gint)&(mine->context_id),"You won!");
      
      /* FIXME disable clicking on field squares */

      /* FIXME open up highscore panel if necessary */
    }  
}

static void gtk_mine_uncover_square(GtkMine *mine, gint orig_i, gint orig_j, gint i, gint j)
{
  gint k;
  guint state;
  
  /*
    DEBUG(("%s [%d,%d] [%d,%d] (%d:%d)\n",__PRETTY_FUNCTION__,orig_i,orig_j,i,j,mine->field[i][j],mine->uncovered[i][j]));
  */

  /*
    if(GTK_TOGGLE_BUTTON(mine->buttons[i][j])->active==TRUE)
    return;
  */
  if(mine->uncovered[i][j]==UNCOVERED || mine->uncovered[i][j]==FLAGGED)
    return;

  switch(state=mine->field[i][j])
    {
    case N_ZERO:
      for(k=0;k<8;k++) /* 8 is sizeof(neighbor)/2*sizeof(gint) */
	{
	  gint di, dj;

	  if(mine->uncovered[i][j]==COVERED)
	    {
	      mine->uncovered[i][j] = UNCOVERED;
	      mine->uncovered_count++;
	    }
	  gtk_signal_handler_block(GTK_OBJECT(mine->buttons[i][j]),mine->handlers[i][j]);
	  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(mine->buttons[i][j]),TRUE);
	  gtk_widget_set_sensitive(mine->buttons[i][j],FALSE);
	  gtk_signal_handler_unblock(GTK_OBJECT(mine->buttons[i][j]),mine->handlers[i][j]);
	  
	  di = i + neighbor[k].dx;
	  dj = j + neighbor[k].dy;
	  /*if (di!=orig_i && dj!=orig_j && di>=0 && dj>=0 && di<mine->width && dj<mine->height)*/
	  if (di>=0 && dj>=0 && di<mine->width && dj<mine->height)
	    gtk_mine_uncover_square(mine,i,j,di,dj);
	}
      break;/* fall through */
    case N_ONE: case N_TWO: case N_THREE: case N_FOUR:
    case N_FIVE: case N_SIX: case N_SEVEN: case N_EIGHT:
      /*if(mine->pixwid[i][j]==NULL)*/
      /* uncover the present square */
	{
	  GtkStyle *style; GdkPixmap *pixmap, *mask;
	  GtkWidget *w = mine->buttons[i][j];
	  
	  gtk_signal_handler_block(GTK_OBJECT(mine->buttons[i][j]),mine->handlers[i][j]);
	  gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(mine->buttons[i][j]),TRUE);
	  gtk_widget_set_sensitive(mine->buttons[i][j],FALSE);
	  style = gtk_widget_get_style(GTK_WIDGET(mine));

	  /*DEBUG(("%s [%d,%d](state: %d %d)\n",__PRETTY_FUNCTION__,i,j,state,N_ONE));*/
	  DEBUG(("%s [%d,%d] [%d,%d] (%d:%d:%d)\n",__PRETTY_FUNCTION__,orig_i,orig_j,i,j,mine->field[i][j],mine->uncovered[i][j],state));

#if 0
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[COOL],     cool_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[HAPPY],    happy_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[DEAD],     dead_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[PRESS],    press_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[QUESTION], question_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_ONE],    one_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_TWO],    two_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_THREE],  three_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_FOUR],   four_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_FIVE],   five_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_SIX],    six_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_SEVEN],  seven_data)); 
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[N_EIGHT],  eight_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[EMPTY],    empty_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[MINE],     mine_data));
  	  DEBUG(("%s (data: 0x%x 0x%x)\n",__PRETTY_FUNCTION__,mine->xpm_data[FLAG],     flag_data));
#endif
	  pixmap = mine->pixmap[state];
	  mask   = mine->mask[state];

	  /*
	  if(mine->pixwid[i][j]!=NULL)
	    gtk_widget_destroy(mine->pixwid[i][j]);
	  */
	  mine->pixwid[i][j] = gtk_pixmap_new(pixmap,mask);
	  gtk_widget_show(mine->pixwid[i][j]);
	  gtk_container_add(GTK_CONTAINER(w),mine->pixwid[i][j]);
	  gtk_signal_handler_unblock(GTK_OBJECT(mine->buttons[i][j]),mine->handlers[i][j]);
	  if(mine->uncovered[i][j]==COVERED) 
	    {
	      mine->uncovered[i][j] = UNCOVERED;
	      mine->uncovered_count++;
	    }
	}
      return;
      break; /* not really necessary, the first person to tell me about it wins a lollipop */
    case MINE: /* we should never get there! */
      /*printf("GtkMine: internal error.\n");
      gtk_exit(EXIT_FAILURE);
      break;*/
    default:      
    }
}

guint gtk_mine_get_type()
{
  static guint mine_type = 0;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  if(!mine_type)
    {
      GtkTypeInfo mine_info =
      {
	"Mine",
	sizeof(GtkMine),
	sizeof(GtkMineClass),
	(GtkClassInitFunc) gtk_mine_class_init,
	(GtkObjectInitFunc) gtk_mine_init,
	(GtkArgSetFunc) NULL,
	(GtkArgGetFunc) NULL
      };
      
      mine_type = gtk_type_unique(gtk_vbox_get_type(),&mine_info);
    }
  
  return mine_type;
}

static void gtk_mine_class_init(GtkMineClass *class)
{
  GtkObjectClass *object_class;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  object_class =(GtkObjectClass*) class;
  
  gtk_mine_signals[MINE_SIGNAL] = gtk_signal_new("mine",
						 GTK_RUN_FIRST,
						 object_class->type,
						 GTK_SIGNAL_OFFSET(GtkMineClass,gtkmine),
						 gtk_signal_default_marshaller,GTK_TYPE_NONE,0);
  
  
  gtk_object_class_add_signals(object_class,gtk_mine_signals,LAST_SIGNAL);
  
  class->gtkmine = NULL;
  object_class->destroy = gtk_mine_destroy;
}

#ifdef DEBUG
static void print_field(unsigned char **f, int width, int height)
{
  int i,j;
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  for(i=0;i<width;i++)
    {
      for(j=0;j<height;j++)
	printf("%d ",f[i][j]);
      printf("\n");
    }
}
#endif

static void gtk_mine_setup_field(GtkMine *mine)
{
  int c,i=0,j=0,k;
  struct timeval tp; struct timezone tzp;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  
  (void)gettimeofday(&tp,&tzp);
  (void)srand(tp.tv_sec%(86400 * 365) + tp.tv_usec%1000000);

  for(i=0;i<mine->width;i++) /* zero the field */
    for(j=0;j<mine->height;j++)
      {
	mine->field[i][j] = N_ZERO;
	mine->uncovered[i][j] = COVERED;
      }
  
  c = mine->mines_count;
  for(;c>0;c--)
    {
      int x,y;
      
      x = (rand()>>1) % mine->width;
      y = (rand()>>2) % mine->height;
      mine->field[x][y]=MINE;
    }
  
  for(i=0;i<mine->width;i++)
    for(j=0;j<mine->height;j++)
      {
	for(k=0;k<8;k++)
	  { 
	    int idx, jdy;
	    idx = i+neighbor[k].dx, jdy = j+neighbor[k].dy;
	    if(mine->field[i][j]!=MINE && idx>-1 && jdy>-1 && idx<mine->width && jdy<mine->height && mine->field[idx][jdy]==MINE)
	      mine->field[i][j]++;
	  }
      }
#if defined(DEBUG)
  print_field(mine->field,mine->width,mine->height);
#endif
}

static void gtk_mine_smiley_callback(GtkWidget *w, gpointer data)
{
  int i,j;
  GtkMine *mine = (GtkMine*)data;
  DEBUG(("%s\n",__PRETTY_FUNCTION__));

  for(i=0;i<mine->height;i++)
    for(j=0;j<mine->width;j++)
      {
	if(mine->pixwid[i][j]!=NULL && GTK_IS_WIDGET(mine->pixwid[i][j]))
	  gtk_widget_destroy(mine->pixwid[i][j]);
	gtk_signal_handler_block(GTK_OBJECT(mine->buttons[i][j]),mine->handlers[i][j]);
	gtk_widget_set_sensitive(mine->buttons[i][j],TRUE);
	gtk_signal_handler_unblock(GTK_OBJECT(mine->buttons[i][j]),mine->handlers[i][j]);
	/*gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(mine->buttons[i][j]),FALSE);*/
      }
  /* gtk_mine_init(mine); (work-alike) */
  mine->width   = current_width;
  mine->height  = current_height;
  mine->timeout = current_timeout;
  mine->mines_count = current_minecount;
  mine->uncovered_count = 0;
  mine->time    = 0;
  mine->game_started = 0;
  mine->flagged_count = 0;

  for(i=0;i<mine->width;i++)
    {
      memset(mine->field[i],0,mine->height); /* could have used bzero() */
      memset(mine->uncovered[i],COVERED,mine->height);
    }
  gtk_mine_setup_field(mine);
  gtk_entry_set_text(GTK_ENTRY(mine->time_entry),"0");  
  {
    gchar s[10];
    sprintf(&s[0],"%d",mine->mines_count);
    gtk_entry_set_text(GTK_ENTRY(mine->mines_entry),s);
  }
  gtk_statusbar_push(GTK_STATUSBAR(mine->status_bar), (gint)&(mine->context_id),"Gtk Minesweeper ready.");
  gtk_mine_clear(mine);
}

static gint gtk_mine_button_press_callback(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
  DEBUG(("%s button %d:%d pressed\n",__PRETTY_FUNCTION__,event->type,event->button));
  if(event->button==3)
    { /* capture events from button #3 */
      gint i,j;
      GtkMine *mine;
      GtkMineCbData *cbData = (GtkMineCbData*)data;
      
      mine = cbData->mine;
      i = cbData->y, j = cbData->x;
      DEBUG(("0x%x %d %d %d\n",mine,i,j,mine->field[i][j]));
      { /* now what we really want to do is show up a flag on the square, unless one is already displayed */
	GdkPixmap *pixmap, *mask;
	GtkStyle *style;
	GtkWidget *w = cbData->mine->buttons[i][j];
	
	if(mine->uncovered[i][j]==FLAGGED)
	  {
	    gtk_widget_destroy(mine->pixwid[i][j]);
	    mine->pixwid[i][j] = NULL;
	    mine->uncovered[i][j] = COVERED;
	    --mine->flagged_count;
	  } 
	else 
	  {
	    style = gtk_widget_get_style(GTK_WIDGET(mine));
#if 0
	    pixmap = gdk_pixmap_create_from_xpm_d(w->window,&mask,
						  &style->bg[GTK_STATE_NORMAL], mine->xpm_data[FLAG]);
#else
	    pixmap = mine->pixmap[FLAG];
	    mask   = mine->mask[FLAG];
#endif
	    mine->pixwid[i][j] = gtk_pixmap_new(pixmap,mask);
	    gtk_widget_show(mine->pixwid[i][j]);
	    gtk_container_add(GTK_CONTAINER(w),mine->pixwid[i][j]);
	    mine->uncovered[i][j] = FLAGGED; /* i shouldn't be doing this */
	    mine->flagged_count++;
	  }
      }
      gtk_mine_game_won_p(mine);
    }
}

static void gtk_mine_init(GtkMine *mine)
{
  GtkWidget *table, *htable, *time_hbox, *mines_hbox;
  GtkWidget *time_label, *mines_label;
  GtkWidget *pixmapwid;
  GdkPixmap *pixmap, *mask;
  GtkStyle  *style;
  gint i,j;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  mine->width   = current_width;
  mine->height  = current_height;
  mine->table   = table;
  mine->time    = 0;
  mine->uncovered_count = 0;
  mine->timeout = current_timeout;
  mine->game_started = 0;
  mine->mines_count = current_minecount;
  mine->flagged_count = 0;

  mine->field = (unsigned char**)g_malloc(sizeof(unsigned char*)*current_width);
  mine->uncovered = (unsigned char**)g_malloc(sizeof(unsigned char*)*current_width);
  for(i=0;i<current_width;i++)
    {
      mine->field[i] = (unsigned char*)g_malloc(sizeof(unsigned char)*current_height);
      mine->uncovered[i] = (unsigned char*)g_malloc(sizeof(unsigned char)*current_height);
    }
  
  gtk_mine_setup_field(mine);
  
  table = gtk_table_new(mine->height+4,mine->width,TRUE);
  gtk_container_border_width(GTK_CONTAINER(table), 4);
  
  time_label  = gtk_label_new(TIME_LABEL);
  gtk_label_set_justify(GTK_LABEL(time_label),GTK_JUSTIFY_RIGHT);
  gtk_widget_show(time_label);
  mines_label = gtk_label_new(MINES_LABEL);
  gtk_label_set_justify(GTK_LABEL(mines_label),GTK_JUSTIFY_RIGHT);
  gtk_widget_show(mines_label);
  mine->time_entry  = gtk_entry_new/*_with_max_length(5)*/();
  gtk_entry_set_editable(GTK_ENTRY(mine->time_entry),FALSE);
  gtk_entry_set_text(GTK_ENTRY(mine->time_entry),"0");
  gtk_widget_show(mine->time_entry);
  mine->mines_entry = gtk_entry_new/*_with_max_length(3)*/();
  gtk_entry_set_editable(GTK_ENTRY(mine->mines_entry),FALSE);
  {
    gchar s[10];
    sprintf(&s[0],"%d",mine->mines_count);
    gtk_entry_set_text(GTK_ENTRY(mine->mines_entry),s);
  }
  gtk_widget_show(mine->mines_entry);
  
  mine->smiley = gtk_button_new();
  mine->style = style = gtk_widget_get_style(GTK_WIDGET(mine)); 
  mask = gdk_bitmap_create_from_data((GdkWindow*)&gdk_root_parent,fillface_bits,fillface_width,fillface_height);
  pixmap = gdk_pixmap_create_from_xpm_d((GdkWindow *)&gdk_root_parent/*mine->smiley->window*/,&mask,
					&style->bg[GTK_STATE_NORMAL], (gchar**)happy_data);
  /* this should be performed with the macro defined a few lines down */

  pixmapwid = gtk_pixmap_new(pixmap,mask);
  gtk_widget_show(pixmapwid);
  gtk_container_add(GTK_CONTAINER(mine->smiley),pixmapwid);
  gtk_widget_show(mine->smiley);

  gtk_signal_connect(GTK_OBJECT(mine->smiley),"clicked",GTK_SIGNAL_FUNC(gtk_mine_smiley_callback),mine);
  
  mine->pixmap    = (GdkPixmap**)g_malloc(sizeof(GdkPixmap*)*NUMBER_OF_PIXMAPS);
  mine->mask      = (GdkPixmap**)g_malloc(sizeof(GdkPixmap*)*NUMBER_OF_PIXMAPS);
  /* next time i'll pack all this in a single struct, to avoid calling malloc that many times */

  mine->xpm_data  = (gchar***)g_malloc(sizeof(gchar**)*NUMBER_OF_PIXMAPS);  

#define make_pixmap(p,m,data) p = gdk_pixmap_create_from_xpm_d((GdkWindow *)&gdk_root_parent,&(m),&style->bg[GTK_STATE_NORMAL],(gchar**)data);
#define make_pixmap_nowidget(index,data) make_pixmap(mine->pixmap[index],mine->mask[index],data); mine->xpm_data[index]=(gchar**)data;

  make_pixmap_nowidget(COOL,     cool_data);
  make_pixmap_nowidget(HAPPY,    happy_data);
  make_pixmap_nowidget(DEAD,     dead_data);
  make_pixmap_nowidget(PRESS,    press_data);
  make_pixmap_nowidget(QUESTION, question_data);
  make_pixmap_nowidget(N_ONE,    one_data);
  make_pixmap_nowidget(N_TWO,    two_data);
  make_pixmap_nowidget(N_THREE,  three_data);
  make_pixmap_nowidget(N_FOUR,   four_data);
  make_pixmap_nowidget(N_FIVE,   five_data);
  make_pixmap_nowidget(N_SIX,    six_data);
  make_pixmap_nowidget(N_SEVEN,  seven_data); 
  make_pixmap_nowidget(N_EIGHT,  eight_data);
  make_pixmap_nowidget(EMPTY,    empty_data);
  make_pixmap_nowidget(MINE,     mine_data);
  make_pixmap_nowidget(FLAG,     flag_data);
  
  htable = gtk_table_new(1,7,FALSE);
  gtk_table_attach(GTK_TABLE(htable),time_label,         0,1,0,1,0/*GTK_EXPAND|GTK_FILL*/, 0/*GTK_EXPAND|GTK_FILL*/,0,0);
  gtk_table_attach(GTK_TABLE(htable),mine->time_entry,   1,2,0,1,GTK_SHRINK/*GTK_EXPAND|GTK_FILL*/, GTK_SHRINK/*GTK_EXPAND|GTK_FILL*/,0,0);
  gtk_table_attach(GTK_TABLE(htable),mine->smiley,       3,4,0,1,0,0,5,0);
  gtk_table_attach(GTK_TABLE(htable),mines_label,        5,6,0,1,0/*GTK_EXPAND|GTK_FILL*/, 0/*GTK_EXPAND|GTK_FILL*/,0,0);
  gtk_table_attach(GTK_TABLE(htable),mine->mines_entry,  6,7,0,1,GTK_SHRINK/*GTK_EXPAND|GTK_FILL*/, GTK_SHRINK/*GTK_EXPAND|GTK_FILL*/,0,0);
  gtk_widget_show(htable);
  gtk_table_attach_defaults(GTK_TABLE(table),htable,0,mine->width,0,2);  
  
  mine->status_bar = gtk_statusbar_new();
  gtk_table_attach_defaults(GTK_TABLE(table),mine->status_bar,0,mine->width,mine->height+3/*2*/,mine->height+4);
  mine->context_id = gtk_statusbar_get_context_id(GTK_STATUSBAR(mine->status_bar), "GtkMine");
  gtk_widget_show(mine->status_bar);
  gtk_statusbar_push(GTK_STATUSBAR(mine->status_bar), (gint)&(mine->context_id),"Gtk Minesweeper ready.");
  
  mine->buttons = (GtkWidget***)g_malloc(sizeof(GtkWidget**)*mine->width);
  mine->pixwid  = (GtkWidget***)g_malloc(sizeof(GtkWidget**)*mine->width);
  mine->handlers = (guint**)g_malloc(sizeof(guint*)*mine->width);
  /* next time i'll pack all this in a single struct, to avoid calling malloc that many times */
  
  for(i=0;i<mine->height; i++)
    {
      mine->buttons[i] = (GtkWidget**)g_malloc(sizeof(GtkWidget*)*mine->height);
      mine->pixwid[i] = (GtkWidget**)g_malloc(sizeof(GtkWidget*)*mine->height);
      mine->handlers[i] = (guint*)g_malloc(sizeof(guint)*mine->height);
      bzero(mine->uncovered[i],mine->height);
      for(j=0;j<mine->width; j++)
	{
	  GtkMineCbData *cbData = (GtkMineCbData*)g_malloc(sizeof(GtkMineCbData));
	  
	  cbData->mine = mine;
	  cbData->y = i;
	  cbData->x = j;
	  
	  /*mine->uncovered[i][j] = FALSE;*/
	  mine->buttons[i][j] = gtk_toggle_button_new();
	  gtk_widget_set_usize(mine->buttons[i][j],18,18); /* size of pixmap */
	  gtk_table_attach_defaults(GTK_TABLE(table),mine->buttons[i][j],
				    j,j+1,i+2,i+3);
	  mine->handlers[i][j] = gtk_signal_connect(GTK_OBJECT(mine->buttons[i][j]),"toggled",
						    GTK_SIGNAL_FUNC(gtk_mine_toggle),(gpointer)cbData);
	  DEBUG(("handler[%d,%d]=%d\n",i,j,mine->handlers[i][j]));
	  gtk_signal_connect(GTK_OBJECT(mine->buttons[i][j]), "button_press_event",
			     (GtkSignalFunc) gtk_mine_button_press_callback, (gpointer)cbData);

	  gtk_widget_set_usize(mine->buttons[i][j],20,20);
	  gtk_widget_show(mine->buttons[i][j]);
	}
    }
  gtk_container_add(GTK_CONTAINER(mine),table);
  gtk_widget_show(table);
}

GtkWidget* gtk_mine_new()
{
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  return GTK_WIDGET(gtk_type_new(gtk_mine_get_type()));
}

GtkWidget*     gtk_mine_new_with_level(gint level)
{
  if(level>=0 && level<=3)
    {
      return gtk_mine_new_with_dimensions(gtk_mine_levels[level].width,
					  gtk_mine_levels[level].height,
					  gtk_mine_levels[level].mines,
					  gtk_mine_levels[level].timeout);
    }
  return (GtkWidget*)NULL;
}

GtkWidget* gtk_mine_new_with_dimensions(gint w, gint h, gint m, gint t)
{
  DEBUG(("%s\n",__PRETTY_FUNCTION__)); 

  /* those variables are like class variables for the GtkMine class .. */
  current_width  = w;
  current_height = h;
  current_minecount = m;
  current_timeout = t;
  
  return gtk_mine_new();
}

static gint gtk_mine_refresh_count(gpointer data) /* called when a mine is correctly detected */
{ /* refresh mine count display entry */
  gchar s[10];
  GtkMine *mine = (GtkMine*)data;
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  
  mine->mines_count--;
  sprintf(&s[0],"%d",mine->mines_count); /* XXX convert between 'char' and 'gchar' */
  gtk_entry_set_text(GTK_ENTRY(mine->mines_entry),s);
  
}

static void gtk_mine_dialog_close_callback(GtkWidget *w, gpointer data)
{
  GtkWidget *window = GTK_WIDGET(data);
  gtk_widget_destroy(window);
}

static void gtk_mine_dialog_open(gchar *text, gchar *title)
{ 
  GtkWidget *window, *vbox, *button, *label, *hsep;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_usize(window,300,150);
  if(title!=NULL)
    gtk_window_set_title(GTK_WINDOW(window),title);
  gtk_window_set_policy (GTK_WINDOW(window), TRUE, TRUE, FALSE);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(gtk_mine_dialog_close_callback),window);
  gtk_container_border_width(GTK_CONTAINER(window),10);
  
  vbox = gtk_vbox_new(FALSE,TRUE);
  gtk_container_add(GTK_CONTAINER(window),vbox);
  gtk_widget_show(vbox);
  
  label = gtk_label_new(text);
  gtk_box_pack_start(GTK_BOX(vbox),label,TRUE,TRUE,0);    
  gtk_widget_show(label);
  
  hsep = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(vbox),hsep,FALSE,FALSE,0);
  gtk_widget_show(hsep);
  
  button = gtk_button_new_with_label("Ok");
  gtk_box_pack_end(GTK_BOX(vbox),button,TRUE,TRUE,0);
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(gtk_mine_dialog_close_callback),window);
  gtk_widget_show(button);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(button);
  gtk_widget_show(window);
}

static void gtk_mine_game_lost(GtkMine *mine)
{
  int i,j;
  
  gtk_timeout_remove(mine->tag); /* remove timed callback */
  
  for(i=0;i<mine->height;i++)
    for(j=0;j<mine->width;j++)
      { /* disable the game field */
	gtk_widget_set_state(mine->buttons[i][j],GTK_STATE_INSENSITIVE); 
      }
  gtk_mine_dialog_open("You lost!","Game over");
}

static gint gtk_mine_refresh_timer(gpointer data)
{
  gchar s[10];
  GtkMine *mine = (GtkMine *)data;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  mine->time++;
  sprintf(&s[0],"%d",mine->time);
  gtk_entry_set_text(GTK_ENTRY(mine->time_entry),s);
  DEBUG(("%s called (%d)\n",__PRETTY_FUNCTION__,mine->time));
  
  if(mine->time>=mine->timeout)
    {      
      DEBUG(("You lost!\n"));
      gtk_mine_game_lost(mine);
    }
  return TRUE;
}

void gtk_mine_clear(GtkMine *mine)
{
  int i,j;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  for(i=0;i<mine->height;i++)
    for(j=0;j<mine->width;j++)
      {
	/*gtk_signal_handler_block_by_data(GTK_OBJECT(mine->buttons[i][j]),mine);*/
	gtk_signal_disconnect(GTK_OBJECT(mine->buttons[i][j]),mine->handlers[i][j]); /* XXX whines when some were already disconnected! */
	gtk_toggle_button_set_state(GTK_TOGGLE_BUTTON(mine->buttons[i][j]),FALSE);
	{
	  GtkMineCbData *cbData = (GtkMineCbData*)g_malloc(sizeof(GtkMineCbData));
	  
	  cbData->mine = mine;
	  cbData->y = i;
	  cbData->x = j;
	  
	  mine->handlers[i][j] = gtk_signal_connect(GTK_OBJECT(mine->buttons[i][j]),"toggled",
						    GTK_SIGNAL_FUNC(gtk_mine_toggle),(gpointer)cbData);
	}
	/*gtk_signal_handler_unblock_by_data(GTK_OBJECT(mine->buttons[i][j]),mine);*/
      }
}

static void gtk_mine_toggle(GtkWidget *widget, gpointer data)
{
  gint i,j;
  GtkMine *mine;
  GtkMineCbData *cbData = (GtkMineCbData*)data;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  mine = cbData->mine;
  if(mine->game_started==0)
    {
      mine->game_started=1;
#ifdef ENABLE_TIMER /* disabled for debugging */
      mine->tag = gtk_timeout_add(1000 /* every second */,
				  gtk_mine_refresh_timer,(gpointer)mine);
#endif
    }
  
  i = cbData->y, j = cbData->x;
  DEBUG(("0x%x %d %d %d\n",mine,i,j,mine->field[i][j]));
  
  {
    GdkPixmap *pixmap, *mask;
    GtkWidget *pixmapwid, *w;
    GtkStyle *style;
    GameState res; gint state;
    
    switch(state=mine->field[i][j]) {
    case N_ONE: case N_TWO: case N_THREE: case N_FOUR:
    case N_FIVE: case N_SIX: case N_SEVEN: case N_EIGHT:
      /* duplicated code */
      w = cbData->mine->buttons[i][j];
      style = gtk_widget_get_style(GTK_WIDGET(mine));
#if 0
      pixmap = gdk_pixmap_create_from_xpm_d(w->window,&mask,
					    &style->bg[GTK_STATE_NORMAL], mine->xpm_data[state]);
#else
      pixmap = mine->pixmap[state];
      mask   = mine->mask[state];
#endif
      mine->pixwid[i][j] = gtk_pixmap_new(pixmap,mask);
      gtk_widget_show(mine->pixwid[i][j]);
      gtk_container_add(GTK_CONTAINER(w),mine->pixwid[i][j]);
      /* FIXME take care if the thingy is FLAGGED! */
      mine->uncovered[i][j] = UNCOVERED;
      mine->uncovered_count++;

      /*FIXME gtk_signal_disconnect_by_func(GTK_OBJECT(w),GTK_SIGNAL_FUNC(gtk_mine_toggle),(gpointer)cbData);*/
/*      #error "probably need to do that!"*/

      gtk_widget_set_state(w,GTK_STATE_INSENSITIVE); /* once the user has clicked, he can't undo it */
    case N_ZERO: /* fall through! */
      if(state!=N_ONE) 
	{ /* backtrack to uncover the appropriate squares */
	  gtk_mine_uncover_square(mine,-1,-1,i,j);
	}
      break;
    case MINE:
      gtk_statusbar_push(GTK_STATUSBAR(mine->status_bar),(gint)&(mine->context_id),"You lost!");
      {
	for(i=0;i<mine->width;i++)
	  for(j=0;j<mine->height;j++)
	    {
	      if(mine->field[i][j]==MINE)
		{
		  w = mine->buttons[i][j];
		  style = gtk_widget_get_style(GTK_WIDGET(mine));
#if 0
		  pixmap = gdk_pixmap_create_from_xpm_d(w->window,&mask,
							&style->bg[GTK_STATE_NORMAL], mine->xpm_data[MINE]);
#else
		  pixmap = mine->pixmap[MINE];
		  mask   = mine->mask[MINE];
#endif
		  if(mine->pixwid[i][j]!=NULL)
		    gtk_widget_destroy(mine->pixwid[i][j]);
		  mine->pixwid[i][j] = gtk_pixmap_new(pixmap,mask);
		  gtk_widget_show(mine->pixwid[i][j]);
		  gtk_container_add(GTK_CONTAINER(w),mine->pixwid[i][j]);
		}
	      /*gtk_widget_set_state(w,GTK_STATE_INSENSITIVE); */
	    }
      }
      gtk_mine_game_lost(mine);
      break;
    default:
      printf("Internal inconsistency detected, terminating..(%d)\n",state);
      gtk_exit(EXIT_FAILURE);
    }
  }
  
  gtk_mine_game_won_p(mine);
}

static void gtk_mine_destroy(GtkObject *object)
{
  GtkMine *mine;
  int i,j;
  
  DEBUG(("%s\n",__PRETTY_FUNCTION__));
  g_return_if_fail(object != NULL);
  g_return_if_fail(GTK_IS_MINE(object));
  
  mine = GTK_MINE(object);
  
  for(i=0;i<mine->height;i++)
    {
      for(j=0;j<mine->width;j++)
	{
	  g_free(mine->buttons[i][j]); /* ?? */
	}
      g_free(mine->pixwid[i]);
      g_free(mine->field[i]);
      g_free(mine->uncovered[i]);
      g_free(mine->handlers[i]);
    }
  g_free(mine->handlers);
  g_free(mine->pixmap);
  g_free(mine->pixwid);
  g_free(mine->mask);
  g_free(mine->pixmapwid);
  g_free(mine->xpm_data);
  g_free(mine->field);
  g_free(mine->uncovered);
}

#ifndef FORGET_ABOUT_G_LOG
void g_log(const gchar	*log_domain,GLogLevelFlags log_level,const gchar *format,...) 
{ /* this is a stub to satisfy the linker, which complains about this symbol being
   missing on my Gtk setup, for some reason */
}
#endif
