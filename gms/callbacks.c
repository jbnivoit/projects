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
#include <stdlib.h>
#include <string.h>
#include "callbacks.h"
#include "gtkmine.h"
#include "version.h"
#include "scores.h"

extern GtkWidget *mine, *mainvbox;

MenuEntry FileMenuEntries[] = {
  { NEW_MENUITEM_LABEL,        FileNewCallback         },
  { HIGHSCORES_MENUITEM_LABEL, FileHighscoresCallback  },
  { QUIT_MENUITEM_LABEL,       FileQuitCallback        },
};

MenuEntry GameMenuEntries[] = {
  { EASY_MENUITEM_LABEL,       GameEasyCallback        },
  { MEDIUM_MENUITEM_LABEL,     GameMediumCallback      },
  { HARD_MENUITEM_LABEL,       GameHardCallback        },
  { CUSTOMIZE_MENUITEM_LABEL,  GameCustomizeCallback   },
};

MenuEntry HelpMenuEntries[] = {
  { ABOUT_MENUITEM_LABEL,        HelpAboutCallback     },
  { LICENSE_MENUITEM_LABEL,      HelpLicenseCallback   },
  { HOWTOPLAY_MENUITEM_LABEL,    HelpHowtoplayCallback },
};

Menu theMenus[] = {
  { FILE_MENU_LABEL, 3, FileMenuEntries },
  { GAME_MENU_LABEL, 4, GameMenuEntries },
  { HELP_MENU_LABEL, 3, HelpMenuEntries },
};

MenuBar menuBar = { 3, theMenus };

static void make_new_level(int width, int height, int mines, int timeout)
{     
  int _width, _height, _mines, _timeout;

  _width   = width   !=0 ? width   : current_width;
  _height  = height  !=0 ? height  : current_height;
  _mines   = mines   !=0 ? mines   : current_minecount;
  _timeout = timeout !=0 ? timeout : current_timeout;

  current_width = _width;
  current_height = _height;
  current_minecount = _mines;
  current_timeout = _timeout;

  gtk_widget_destroy(mine);
  mine = gtk_mine_new_with_dimensions(_width,_height,_mines,_timeout);
  gtk_signal_connect(GTK_OBJECT(mine),"mine",GTK_SIGNAL_FUNC(MineCallback),NULL);
  gtk_container_add(GTK_CONTAINER(mainvbox),mine);
  gtk_widget_show(mine);
}

#define MAKE_NEW_LEVEL(i) make_new_level(gtk_mine_levels[i].width,gtk_mine_levels[i].height,gtk_mine_levels[i].mines,gtk_mine_levels[i].timeout); current_level = i
#define MAKE_NEW_EASY_LEVEL   MAKE_NEW_LEVEL(0)
#define MAKE_NEW_MEDIUM_LEVEL MAKE_NEW_LEVEL(1)
#define MAKE_NEW_HARD_LEVEL   MAKE_NEW_LEVEL(2)

DECLARE_CALLBACK(DialogCloseCallback)
{
  GtkWidget *window = GTK_WIDGET(data);
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  gtk_widget_destroy(window);
}

void ModalInfoBox(gchar *text, gchar *title)
{
  GtkWidget *window, *vbox, *button, *label, *hsep;
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  if(title!=NULL)
    gtk_window_set_title(GTK_WINDOW(window),title);
  gtk_window_set_policy (GTK_WINDOW(window), TRUE, TRUE, FALSE);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(DialogCloseCallback),window);
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
  gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(DialogCloseCallback),window);
  gtk_widget_show(button);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default(button);
  gtk_widget_show(window);
}

DECLARE_CALLBACK(FileNewCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  
  if(current_level>=0 && current_level<=2)
    {
      MAKE_NEW_LEVEL(current_level);
    }
  else /* otherwise re-use current (custom) settings */
    {
      make_new_level(0,0,0,0); current_level = 3;
    }
}

DECLARE_CALLBACK(FileHighscoresCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
}

DECLARE_CALLBACK(FileQuitCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  /* XXX maybe we should do some cleanup here? */
  gtk_main_quit();
}

DECLARE_CALLBACK(GameEasyCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  MAKE_NEW_EASY_LEVEL;
}

DECLARE_CALLBACK(GameMediumCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  MAKE_NEW_MEDIUM_LEVEL;
}

DECLARE_CALLBACK(GameHardCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  MAKE_NEW_HARD_LEVEL;
}

static GtkWidget *number_of_mines, *timeout;
static GtkWidget *field_width, *field_height;

DECLARE_CALLBACK(CustomizeDialogOkCallback)
{
  int cant_validate_number_of_mines = 0;
  int cant_validate_field_width = 0;
  int cant_validate_field_height = 0;
  int cant_validate_timeout = 0;
  gchar *text = (gchar*)NULL;
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  
  /* get and validate parameters for new customized game */
#define VALIDATE(entry,val) \
  { \
    int n; \
    text = gtk_entry_get_text(GTK_ENTRY(entry)); \
    if(sscanf(text,"%d",&n)!=1) \
      cant_validate_##entry = 1; \
    else \
      val =n; \
  }
  
  VALIDATE(number_of_mines, current_minecount);
  VALIDATE(timeout, current_timeout);
  VALIDATE(field_width, current_width);
  VALIDATE(field_height, current_height);
  
  gtk_widget_destroy(GTK_WIDGET(data));
  
  if(cant_validate_number_of_mines|cant_validate_field_width|
     cant_validate_field_height|cant_validate_timeout)
    ModalInfoBox("Can't validate the values you entered. Please Reenter.","Error");
  else 
    /* this will use the new values we just set as default */
    {
      make_new_level(0,0,0,0);
      current_level = 3; /* this is important */
    }

  timeout = number_of_mines = field_width = field_height = NULL;
}

DECLARE_CALLBACK(CustomizeDialogCancelCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  gtk_widget_destroy(GTK_WIDGET(data));
  timeout = number_of_mines = field_width = field_height = NULL;
}

DECLARE_CALLBACK(GameCustomizeCallback)
{
  GtkWidget *window, *vbox, *button, *table, *hsep, *label, *hbox;
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(window),"Game Customization");
  gtk_window_set_policy (GTK_WINDOW(window), TRUE, TRUE, FALSE);
  gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(CustomizeDialogCancelCallback),window);
  gtk_container_border_width(GTK_CONTAINER(window),10);
  
  vbox = gtk_vbox_new(FALSE,TRUE);
  gtk_container_add(GTK_CONTAINER(window),vbox);
  gtk_widget_show(vbox);
  
  table = gtk_table_new(4,2,TRUE);
  {
    label = gtk_label_new("Number Of Mines");
    gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,0,1);
    gtk_widget_show(label);
    number_of_mines = gtk_entry_new();
    gtk_entry_set_editable(GTK_ENTRY(number_of_mines),TRUE);
    gtk_table_attach_defaults(GTK_TABLE(table),number_of_mines,1,2,0,1);
    gtk_widget_show(number_of_mines);
    
    label = gtk_label_new("Field Width");
    gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,1,2);
    gtk_widget_show(label);
    field_width = gtk_entry_new();
    gtk_entry_set_editable(GTK_ENTRY(field_width),TRUE);
    gtk_table_attach_defaults(GTK_TABLE(table),field_width,1,2,1,2);
    gtk_widget_show(field_width);

    label = gtk_label_new("Field Height");
    gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,2,3);
    gtk_widget_show(label);
    field_height = gtk_entry_new();
    gtk_entry_set_editable(GTK_ENTRY(field_height),TRUE);
    gtk_table_attach_defaults(GTK_TABLE(table),field_height,1,2,2,3);
    gtk_widget_show(field_height);

    label = gtk_label_new("Timeout");
    gtk_table_attach_defaults(GTK_TABLE(table),label,0,1,3,4);
    gtk_widget_show(label);
    timeout = gtk_entry_new();
    gtk_entry_set_editable(GTK_ENTRY(timeout),TRUE);
    gtk_table_attach_defaults(GTK_TABLE(table),timeout,1,2,3,4);
    gtk_widget_show(timeout);
  }
  gtk_box_pack_start(GTK_BOX(vbox),table,TRUE,TRUE,0);
  gtk_widget_show(table);
  
  hsep = gtk_hseparator_new();
  gtk_box_pack_start(GTK_BOX(vbox),hsep,FALSE,FALSE,0);
  gtk_widget_show(hsep);

  hbox = gtk_hbox_new(TRUE,0);
  {
    button = gtk_button_new_with_label("Ok");
    gtk_box_pack_start(GTK_BOX(hbox),button,TRUE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CustomizeDialogOkCallback),window);
    gtk_widget_show(button);
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    gtk_widget_grab_default(button);

    button = gtk_button_new_with_label("Cancel");
    gtk_box_pack_end(GTK_BOX(hbox),button,TRUE,TRUE,0);
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(CustomizeDialogCancelCallback),window);
    gtk_widget_show(button);
  }
  gtk_box_pack_end(GTK_BOX(vbox),hbox,TRUE,TRUE,0);
  gtk_widget_show(hbox);
  gtk_widget_show(window);
}

DECLARE_CALLBACK(HelpAboutCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  ModalInfoBox(ABOUT_TEXT"\n\n" COPYRIGHT_XTEXT,"About "NAME);
}

DECLARE_CALLBACK(HelpLicenseCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  {
    GtkWidget *window, *button, *text, *vbox, *hsep;
    GtkWidget *hscrollbar, *vscrollbar, *table;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),NAME " License");
    gtk_window_set_policy(GTK_WINDOW(window), TRUE, TRUE, FALSE);
    gtk_widget_set_usize(window,500,400);
    gtk_signal_connect(GTK_OBJECT(window),"destroy",GTK_SIGNAL_FUNC(DialogCloseCallback),window);
    gtk_container_border_width(GTK_CONTAINER(window),10);
    
    vbox = gtk_vbox_new(FALSE,TRUE);
    gtk_container_add(GTK_CONTAINER(window),vbox);
    gtk_widget_show(vbox);
    
    table = gtk_table_new(2, 2, FALSE);
    gtk_table_set_row_spacing(GTK_TABLE(table), 0, 2);
    gtk_table_set_col_spacing(GTK_TABLE(table), 0, 2);
    gtk_box_pack_start(GTK_BOX(vbox), table, TRUE, TRUE, 0);
    gtk_widget_show(table);
    
    text = gtk_text_new(NULL, NULL);
    gtk_text_set_editable(GTK_TEXT(text), FALSE);
    gtk_text_set_word_wrap(GTK_TEXT(text),TRUE);
    gtk_table_attach(GTK_TABLE(table), text, 0, 1, 0, 1,
		     GTK_EXPAND | GTK_SHRINK | GTK_FILL,
		     GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
    gtk_widget_show(text);
    
    hscrollbar = gtk_hscrollbar_new(GTK_TEXT(text)->hadj);
    gtk_table_attach(GTK_TABLE(table), hscrollbar, 0, 1, 1, 2,
		     GTK_EXPAND | GTK_FILL | GTK_SHRINK, GTK_FILL, 0, 0);
    gtk_widget_show(hscrollbar);
    
    vscrollbar = gtk_vscrollbar_new(GTK_TEXT(text)->vadj);
    gtk_table_attach(GTK_TABLE(table), vscrollbar, 1, 2, 0, 1,
		     GTK_FILL, GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
    gtk_widget_show(vscrollbar);
    
    gtk_text_freeze(GTK_TEXT(text));
    
    gtk_widget_realize(text);
    
    gtk_text_insert(GTK_TEXT(text),NULL,NULL,NULL,LICENSE_TEXT,strlen(LICENSE_TEXT));
    
    gtk_text_thaw(GTK_TEXT(text));
    gtk_widget_show(text);
    hsep = gtk_hseparator_new();
    gtk_box_pack_start(GTK_BOX(vbox),hsep,FALSE,FALSE,0);
    gtk_widget_show(hsep);
    button = gtk_button_new_with_label("Ok");
    gtk_signal_connect(GTK_OBJECT(button),"clicked",GTK_SIGNAL_FUNC(DialogCloseCallback),window);
    gtk_box_pack_start(GTK_BOX(vbox),button,FALSE,FALSE,0);
    gtk_widget_show(button);
    GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
    gtk_widget_grab_default(button);
    gtk_widget_show(window);
  }
}

DECLARE_CALLBACK(HelpHowtoplayCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  ModalInfoBox(HOWTOPLAY_TEXT,"How to play "NAME);
}

DECLARE_CALLBACK(MineCallback)
{
  DEBUG_CALLBACK(__PRETTY_FUNCTION__);
  /* XXX update highscores table */
  gtk_mine_clear(GTK_MINE(widget));
}

void buildMenuBar(MenuBar *mb, GtkWidget *vbox)
{
  GtkWidget *main_menu, *menu, *menu_item, *menu_bar;
  int i, j, n, m;
  
  n = mb->num;
  menu_bar = gtk_menu_bar_new();
  
  for(i=0;i<n;i++)
    {
      main_menu = gtk_menu_item_new_with_label( mb->menus[i].label );
      gtk_widget_show(main_menu);
      
      menu = gtk_menu_new();
      m = mb->menus[i].num;
      
      for(j=0;j<m;j++) 
	{
	  menu_item = gtk_menu_item_new_with_label(mb->menus[i].entries[j].label);
	  gtk_menu_append(GTK_MENU(menu),menu_item);
	  gtk_signal_connect(GTK_OBJECT(menu_item),"activate", 
			     GTK_SIGNAL_FUNC(mb->menus[i].entries[j].cb),mb);
	  gtk_widget_show(menu_item);
	  gtk_menu_item_set_submenu(GTK_MENU_ITEM(main_menu),menu);  
	  
	}
      
      gtk_menu_bar_append(GTK_MENU_BAR(menu_bar),main_menu); 
    }
  
  gtk_box_pack_start(GTK_BOX(vbox),menu_bar,FALSE,FALSE,0);
  gtk_widget_show(menu_bar);
  
}


