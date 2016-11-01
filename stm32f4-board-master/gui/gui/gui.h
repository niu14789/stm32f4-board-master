/*
 * gui.h
 *
 *  Created on: 2016��5��14��
 *      Author: Administrator
 */

#ifndef __GUI_H__
#define __GUI_H__

#define  FOCUS_ON   1
#define  FOCUS_OFF  0

#define __GUI_WIDGET_MODE_0           ( 0x1 << 0 ) /* standard mode , no pic */
#define __GUI_WIDGET_MODE_1           ( 0x1 << 1 ) /* pic mode , without caption */
#define __GUI_WIDGET_MODE_2           ( 0x1 << 2 ) /* pic mode , with caption */

#define __GUI_WIDGET_MOVE             ( 0x1 << 3 ) /* will be move ? or not */

#define __GUI_WIDGET_TYPE_CIRCULAR    ( 0x1 << 4 ) /* cirular mode */
#define __GUI_WIDGET_TYPE_OCT         ( 0x1 << 5 ) /* right angle mode */

#define __GUI_WIDGET_FRAME_STANDARD   ( 0x1 << 6 ) /* standard frame */
#define __GUI_WIDGET_FRAME_LINE       ( 0x1 << 7 ) /* line frame */
#define __GUI_WIDGET_FRAME_NONE       ( 0x1 << 8 ) /* without frame */

#define __GUI_WIDGET_THEME_0          ( 0x1 << 9 ) /* theme mode 0 */
#define __GUI_WIDGET_THEME_1          ( 0x1 << 10) /* theme mode 1 */
#define __GUI_WIDGET_THEME_2          ( 0x1 << 11) /* theme mode 2 */
#define __GUI_WIDGET_THEME_3          ( 0x1 << 12) /* theme mode 3 */
#define __GUI_WIDGET_THEME_4          ( 0x1 << 13) /* theme mode 4 */
#define __GUI_WIDGET_THEME_5          ( 0x1 << 14) /* theme mode 5 */
#define __GUI_WIDGET_THEME_6          ( 0x1 << 15) /* theme mode 6 */

#define __GUI_WIDGET_HANDLE           ( 0x1 << 16) /* 1:child or 0:parent */
#define __GUI_WIDGET_SAME             ( 0x1 << 17) /* insert as parent window `s child window */


typedef struct window_hwnd_t window_hwnd;

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

typedef struct gui_msg_t
{
	unsigned short x;
	unsigned short y;
	unsigned short xsize;
	unsigned short ysize;
	char *caption;
	char * pic_path;
	unsigned short x_size_pic;
	unsigned short y_size_pic;
	unsigned int mode;
}gui_message;

struct nxgui_object
{
    struct nxgui_object                *link;
    enum widget_type_t           widget_type;
    struct gui_msg_t                *gui_msg;
    int (*callback)(enum event_type,void *data);
};

/* gui widget handler
 *
 * as child
 *
 * */
typedef struct gui_handler{
	struct gui_handler           *link;
	unsigned short                  id;
	unsigned short              status;
	struct gui_operations     *gui_ops;
    struct gui_msg_t        widget_msg;
    window_hwnd * parent_window;
	int (*callback)(enum event_type,void *data);
}widget_hwnd;

/* handler window describe
 * as parent
 * */
struct gui_hwnd{
	struct gui_handler *handle_root;
};

typedef struct window_hwnd_t{
	struct window_hwnd_t *child;         // support  child windows
	struct window_hwnd_t *parent;        // parent window
	struct window_hwnd_t *same_next;     // support same class window:next link
	struct window_hwnd_t *same_pre;      // support same class windiw:precise link
	widget_hwnd  window;
}window_hwnd;


struct gui_operations{
	window_hwnd  * (*create)(window_hwnd * hwnd,struct gui_msg_t*p_msg,int (*callback)(enum event_type,void *data));
	int (*show)(struct gui_handler * g_hmd);
	int (*event_process)(struct gui_handler * h_hmd,enum event_type event , void * data);
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


/* gui l0 msg
 *
 * send form anywhere
 *
 *
 * */

typedef struct
{
	enum event_type  event_type;
	unsigned short           id;
	unsigned short        x_pos;
	unsigned short        y_pos;
	void              *pri_data;
}gui_msg_l0;

/* function */
window_hwnd * handler_current(void);
struct gui_handler * handler_insert(window_hwnd * hwnd,struct gui_handler *insert_one);
int gui_create(const char *device_availdable_list);
int widget_create(enum widget_type_t widget_type,struct gui_msg_t *p_gui_msg,int (*callback)(enum event_type,void *data));
int refresh(void);
void set_handler_current(window_hwnd *hwnd);
/* end nuttx */

#endif /* __GUI_H__ */























