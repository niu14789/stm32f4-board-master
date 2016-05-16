/*
 * gui.h
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */

#ifndef __GUI_H__
#define __GUI_H__

struct widget_pic_t
{
	char *pic_path;
};


enum widget_type_t
{
	button = 0,      /*type button*/
	check_box,
	edit,
	filelistbox,
	icos,
	listbox,
	memo,
	progressbar,
	scrollbar,
	window
};

enum widget_shape_t
{
  rect = 0,       /* right angle       */
  round,          /* round angle       */
  oct,            /* octa  angle       */
  rounded_rect    /* rounded and rect  */
};

enum event_type
{
   onfocus = 0,
   losefocus,
   onclick,
   doubleclick,
   widget_move,
   left_slider,
   right_slider,
   long_press,
   change_caption,
   key_click,
   key_long_press,
   OTHER_NPI
};

struct gui_msg_t
{
	unsigned short x;
	unsigned short y;
	unsigned short xsize;
	unsigned short ysize;
	char *caption;
	char mode;
};

struct gui_operations{
	int (*create)(struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));
	int (*draw_again)(struct gui_msg_t*p_msg);
	int (*onfocus)(struct gui_msg_t*p_msg);
	int (*losefocus)(struct gui_msg_t*p_msg);
	int (*onclick)(struct gui_msg_t*p_msg);
};

struct nxgui_object
{
    struct nxgui_object                *link;
    enum widget_type_t           widget_type;
    struct gui_msg_t                *gui_msg;
    int (*callback)(enum event_type,void *data);
};

/*  */
struct gui_handler{
	struct gui_handler            *link;
	unsigned short                   id;
	struct gui_operations      *gui_ops;
    struct gui_msg_t        widget_msg;
	int (*callback)(enum event_type,void *data);
};


/* the gui system callback typedef */

typedef int (*callback)(enum event_type event,void *data);

/* gui msg typedef
 *
 * message check
 *
 * send from anywhere
 *
 * */

typedef struct
{
  enum event_type  event_type;
  struct gui_handler* handler;
  void *data;
}gui_msg;

/* function */

int gui_create(const char *device_availdable_list);
struct gui_handler** gui_sched_root(void);
int widget_create(enum widget_type_t widget_type,struct gui_msg_t *p_gui_msg,int (*callback)(enum event_type,void *data));
/* end nuttx */

#endif /* __GUI_H__ */



