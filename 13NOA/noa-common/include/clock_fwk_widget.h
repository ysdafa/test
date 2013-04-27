/*
*
* Copyright 2012  Samsung Electronics Co., Ltd
*
* Licensed under the Flora License, Version 1.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*    http://www.tizenopensource.org/license
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#ifndef __CLK_FWK_WIDGET_H__
#define __CLK_FWK_WIDGET_H__

#include "clock_fwk_define.h"
#include <Elementary.h>
#include <alarm-engine.h>
#include <glib.h>
/**********************************************************************
******************define, struct ,typedef, union, enum, global val *************************************
***********************************************************************/

//******************define *************************************

//
typedef enum {
	DG_SYTLE_TOP,
	DG_SYTLE_MID,
	DG_SYTLE_BOT,
	DG_SYTLE_MAX,
} DialogueGroupStyle;
//******************typedef *************************************
typedef struct _RGBA_color RGBA_color;
typedef void (*EO_SMART_CB) (void *data, Evas_Object *obj, void *event_info);
//******************struct *************************************
struct _RGBA_color {
	unsigned char r, g, b, a;
};
/**********************************************************************
******************Global function ref*************************************
***********************************************************************/
int widget_button_set(Evas_Object *btn, Eina_Bool bVisible, char *icon_path);

Elm_Object_Item *widget_naviframe_push(Evas_Object *navi_bar,
				       const char *title_label,
				       Evas_Object *prev_btn,
				       Evas_Object *next_btn,
				       Evas_Object *content,
				       const char *item_style,
				       Evas_Object *cbar);
Evas_Object *widget_create_controlbar(Evas_Object *parent, const char *style);

Evas_Object *widget_create_button(Evas_Object *parent, char *style,
				  const char *label, const char *icon_path,
				  EO_SMART_CB cb, void *cb_data);
Evas_Object *widget_create_slider(Evas_Object *parent, char *style,
				  char *indicator, double d_min, double d_max);
Evas_Object *widget_create_conformant(Evas_Object *win_main, char *style,
				      Evas_Object *content);
Evas_Object *widget_create_icon(Evas_Object *parent, const gchar *path);

Evas_Object *widget_create_box(Evas_Object *parent);
Evas_Object *widget_create_rectangle_blank(Evas_Object *obj,
					   Evas_Object *parent_box,
					   Evas_Coord minw, Evas_Coord minh);

Evas_Object *widget_create_layout(Evas_Object *parent);

Evas_Object *widget_create_editfield(Evas_Object *parent, gchar *title,
				     gchar *str, EO_SMART_CB clicked_cb,
				     void *data_clicked,
				     EO_SMART_CB unfocused_cb,
				     void *data_unfocused);

Evas_Object *widget_create_popup(Evas_Object *parent, char *content_str,
				 char *title_str, double timeout,
				 EO_SMART_CB response_cb, void *data);

Evas_Object *clk_widget_create_button(Evas_Object *parent,
				      const char *file, const char *group,
				      Edje_Color_Class *color_class,
				      Edje_Signal_Cb clicked_cb, void *data);

#endif				//__CLK_FWK_WIDGET_H__
