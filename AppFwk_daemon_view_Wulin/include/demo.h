#include <stdbool.h>
//#include <glib.h>
#include <appcore-common.h>
#include <appsvc/appsvc.h>
#include <appcore-efl.h>
#include <Ecore_X.h>
#include <Elementary.h>
#include <aul.h>
#include <libintl.h>
//#include "location/locations.h"
//#include <geocoder.h>
#include <Ecore_X.h>
#include <stdio.h>      
#include <stdlib.h>       
#include <string.h> 

#include "elmdemo_test.h"
#include "elmdemo_util.h"

#define _EDJ(x) elm_layout_edje_get(x)

typedef enum _MOVING_TYPE
{
	NONE,
	FLICK_L2R,
	FLICK_R2L,
} MOVING_TYPE;

struct _Touch_Info
{
   Evas_Coord cur_x, cur_y, cur_mx, cur_my;
   Evas_Coord prev_x, prev_y, prev_mx, prev_my;

   Eina_Bool multitouch_detected : 1;
   Eina_Bool touchtype_detected : 1;

   int moving_type;
   int magic_num;
};
typedef struct _Touch_Info Touch_Info;

struct _menu_item {
	char *name;
	void (*func)(void *data, Evas_Object *obj, void *event_info);
};

struct _group_menu_item {
	Eina_Bool is_group;
	char *name;
	void (*func)(void *data, Evas_Object *obj, void *event_info);
};


#define DAEMON_NEW(ptr, num_elements, type)	 \
			do { \
				if ((int)(num_elements) <= 0) { \
					ptr = NULL; \
				} else { \
					ptr = (type *) calloc(num_elements, sizeof(type)); \
				} \
			} while (0)

				
typedef enum
{
	WHATSNEW_TYPE,
	MOSTPOPULAR_TYPE,
	GENRES_TYPE,
	MAX_TYPE
}ContentViewType;


typedef struct {
	Evas_Object *win;
	Evas_Object *naviframe;
    Evas_Object *base_layout;
	Evas_Object *genlist;
	Evas_Object *about_genlist;
	Evas_Object *video_genlist;
	Evas_Object *bg;
	Evas_Object *background;
	Evas *evas;
    Evas_Object *mostpopular_button;
	Evas_Object *whatsnew_button;
	Evas_Object *genres_button;
    Evas_Object *warn_popup;
    Evas_Object *toolbar_btn;
	ContentViewType eContentType;
	//set naviframe item
	//Elm_Object_Item *naviframe_item_whatsn;	
	//Elm_Object_Item *naviframe_item_mostpo;	
	//Elm_Object_Item *naviframe_item_geners;	

	//added for gengrid demo
	Evas_Coord root_w;
	Evas_Coord root_h;
	Evas_Object *conform;
	//Evas_Object *layout_main;
	Touch_Info ti;	
} demo_data_s;

typedef enum
{
	APP_LIST_TYPE,
	VIDEO_LIST_TYPE,
	WIFI_DISCONNECT,
	WIFI_UNCONNECTED,
	VIDEO_OVER
}ListType;


