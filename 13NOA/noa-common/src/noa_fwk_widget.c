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

#include <time.h>
#include <appcore-efl.h>
#include <Ecore_X.h>
#include <vconf-keys.h>
#include <vconf.h>
#include "clock_fwk_widget.h"
#include "clock_fwk_util.h"

/**********************************************************************
******************Local function declear, extern function declear*************************************
***********************************************************************/

static void _widget_def_popup_response_cb(void *data, Evas_Object * obj,
					  void *event_info);
/**********************************************************************
******************Local function ref*************************************
***********************************************************************/

/**
* send
* This function is  used to be default cb in the elm_popup when get signle:"response"
* @param           data   pointer to data
* @param           obj    pointer to current evas object
* @param           event_info    pointer to current event
* @return          void
* @exception     I
*/
static void _widget_def_popup_response_cb(void *data, Evas_Object * obj,
					  void *event_info)
{
	EVAS_OBJECT_DELIF(obj);
}

static void _entry_changed_cb(void *data, Evas_Object * obj, void *event_info)
{

	if (elm_object_focus_get(data)) {
		if (elm_entry_is_empty(obj))
			elm_object_signal_emit(data, "elm,state,eraser,hide",
					       "elm");
		else
			elm_object_signal_emit(data, "elm,state,eraser,show",
					       "elm");
	}
}

static void _entry_focused_cb(void *data, Evas_Object * obj, void *event_info)
{
	if (!elm_entry_is_empty(obj))
		elm_object_signal_emit(data, "elm,state,eraser,show", "elm");
	elm_object_signal_emit(data, "elm,state,guidetext,hide", "elm");

}

static void _entry_unfocused_cb(void *data, Evas_Object * obj, void *event_info)
{

	if (elm_entry_is_empty(obj))
		elm_object_signal_emit(data, "elm,state,guidetext,show", "elm");
	elm_object_signal_emit(data, "elm,state,eraser,hide", "elm");
}

static void _eraser_clicked_cb(void *data, Evas_Object * obj,
			       const char *emission, const char *source)
{
	elm_entry_entry_set(data, "");
}

/**********************************************************************
******************Global function ref*************************************
***********************************************************************/

/**
* send
* This function is  used to set navigationbar's button's visible with icon
* @param           btn           pointer to button evas_object
* @param           bVisible      Eina_Bool for button visible(EINA_TRUE) or invisible(EINA_FALSE)
* @param           icon_path     char for button's icon path
* @return          when success, return SUCCESS, or return FAILED
* @exception
*/
int widget_button_set(Evas_Object * btn, Eina_Bool bVisible, char *icon_path)
{
	Evas_Object *icon = NULL;
	int nErr = SUCCESS;
	int ret = SUCCESS;
	// //CLK_FUN_BEG();
	CLK_RETVM_IF(!btn, FAILED, "btn is null");
	if (!icon_path) {
		elm_object_disabled_set(btn, !bVisible);
		goto End;
	}
	icon = widget_create_icon(btn, icon_path);
	CLK_RETVM_IF(!icon, FAILED, "icon is null");
	if (EINA_TRUE == bVisible) {
		elm_object_part_content_set(btn, "icon", icon);
		elm_object_disabled_set(btn, !bVisible);
	} else {
		elm_object_disabled_set(btn, !bVisible);
		elm_object_part_content_set(btn, "icon", icon);
	}
	evas_object_show(btn);
 End:
	// //CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to create navibar
* @param           navi_bar   pointer to Evas object, as navigationbar's pointer
* @param           title      string for navigationbar title
* @param           fn_btn1    pointer to evas object, as navigationbar's button1
* @param           fn_btn2    pointer to evas object, as navigationbar's button2
* @param           fn_btn3    pointer to evas object, as navigationbar's button3
* @param           content    pointer to evas object, as navigationbar's content
* @param           cbar       pointer to evas object, as controlbar's content
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Elm_Object_Item *widget_naviframe_push(Evas_Object * navi_bar,
				       const char *title_label,
				       Evas_Object * prev_btn,
				       Evas_Object * next_btn,
				       Evas_Object * content,
				       const char *item_style,
				       Evas_Object * cbar)
{
	CLK_FUN_BEG();
	retv_if(!navi_bar, NULL);
	Elm_Object_Item *item =
	    elm_naviframe_item_push(navi_bar, title_label, prev_btn, next_btn,
				    content, item_style);
	if (cbar) {
		elm_object_item_part_content_set(item, "controlbar", cbar);
	}
	CLK_FUN_END();
	return item;
}

//
Evas_Object *widget_create_controlbar(Evas_Object * parent, const char *style)
{
	retv_if(!parent, NULL);
	CLK_FUN_BEG();
	Evas_Object *ret = elm_toolbar_add(parent);
	elm_toolbar_shrink_mode_set(ret, ELM_TOOLBAR_SHRINK_EXPAND);
	if (style) {
		elm_object_style_set(ret, style);
		if (0 == strcmp(style, "tabbar")) {
			elm_toolbar_select_mode_set(ret,
						    ELM_OBJECT_SELECT_MODE_ALWAYS);
		}
	}
	CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to create button
* @param           parent       pointer to Evas object, as the  parent
* @param           label        string for  title
* @param           icon_path    string for  icon path
* @param           cb           as cb when get signle "clicked"
* @param           cb_data      as cb'data
* @param           style        as style
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Evas_Object *widget_create_button(Evas_Object * parent, char *style,
				  const char *label, const char *icon_path,
				  EO_SMART_CB cb, void *cb_data)
{
	Evas_Object *ret = NULL;
	Evas_Object *icon = NULL;
	int nErr = SUCCESS;
	CLK_FUN_BEG();
	ret = elm_button_add(parent);
	CLK_RETVM_IF(!ret, NULL, "elm_button_add error!");
	elm_object_style_set(ret, style);
	evas_object_size_hint_weight_set(ret, EVAS_HINT_EXPAND,
					 EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ret, EVAS_HINT_FILL, 0.5);
	if (icon_path) {
		icon = widget_create_icon(parent, icon_path);
	}
	if (label) {
		elm_object_text_set(ret, label);
	}
	if (icon) {
		elm_object_part_content_set(ret, "icon", icon);
	}
	if (cb && cb_data) {
		evas_object_smart_callback_add(ret, "clicked", cb, cb_data);
	}
	evas_object_show(ret);
 End:
	CLK_FUN_END();
	return ret;
}

//
Evas_Object *widget_create_slider(Evas_Object * parent, char *style,
				  char *indicator, double d_min, double d_max)
{
	Evas_Object *ret = NULL;
	int nErr = SUCCESS;
	//CLK_FUN_BEG();
	ret = elm_slider_add(parent);
	elm_object_style_set(ret, "expanded_indicator_button");
	CLK_RETVM_IF(!ret, NULL, "elm_slider_add error!");
//  elm_object_style_set(ret, style);
	evas_object_size_hint_weight_set(ret, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(ret, EVAS_HINT_FILL, 0.5);
	//evas_object_pass_events_set(ret, 1);
	evas_object_propagate_events_set(ret, 0);
	elm_slider_indicator_show_set(ret, EINA_TRUE);
	elm_slider_indicator_format_set(ret, indicator);
	elm_slider_min_max_set(ret, d_min, d_max);
 End:
	//CLK_FUN_END();
	return ret;
}

//
Evas_Object *widget_create_conformant(Evas_Object * parent, char *style,
				      Evas_Object * content)
{
	Evas_Object *ret = NULL;
	int nErr = SUCCESS;
	//CLK_FUN_BEG();
	elm_win_conformant_set(parent, 1);
	ret = elm_conformant_add(parent);
	CLK_RETVM_IF(!ret, NULL, "ret error!");
	elm_object_style_set(ret, style);
	elm_object_content_set(ret, content);
 End:
	//CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to create icon
* @param           parent       pointer to Evas object, as the  parent
* @param           path         string for  icon path
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Evas_Object *widget_create_icon(Evas_Object * parent, const gchar * path)
{
	Evas_Object *ret = NULL;
	int nErr = SUCCESS;
	//CLK_FUN_BEG();
	CLK_RETVM_IF(!path, NULL, "path is NULL");
	ret = elm_icon_add(parent);
	CLK_RETVM_IF(!ret, NULL, "elm_icon_add error!");
	elm_icon_file_set(ret, path, NULL);
 End:
	//CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to create editfield
* @param           parent           pointer to Evas object, as the  parent
* @param           title            string for title
* @param           str              string for guide text
* @param           clicked_cb       cb, when get single "clicked"
* @param           data_clicked     @clicked_cb data
* @param           unfocused_cb     cb, when get signle "unfocused"
* @param           data_unfocused   @unfocused data
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Evas_Object *widget_create_editfield(Evas_Object * parent, gchar * title,
				     gchar * str, EO_SMART_CB clicked_cb,
				     void *data_clicked,
				     EO_SMART_CB unfocused_cb,
				     void *data_unfocused)
{
	Evas_Object *ret = NULL;
	int nErr = SUCCESS;
	Evas_Object *layout = elm_layout_add(parent);
	elm_layout_theme_set(layout, "layout", "editfield", "title");
	Evas_Object *entry = elm_entry_add(parent);
	elm_object_part_content_set(layout, "elm.swallow.content", entry);
	ret = layout;
	CLK_RETVM_IF(!ret, NULL, "elm_editfield_add error!");
	elm_object_part_text_set(layout, "elm.text", title);
	elm_object_part_text_set(layout, "elm.text", str);
	elm_entry_single_line_set(entry, EINA_TRUE);
	elm_entry_scrollable_set(entry, EINA_TRUE);

	evas_object_size_hint_weight_set(ret, EVAS_HINT_EXPAND,
					 EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(ret, EVAS_HINT_FILL, 0);
	//cb
	evas_object_smart_callback_add(entry, "changed", _entry_changed_cb,
				       layout);

	evas_object_smart_callback_add(entry, "focused", _entry_focused_cb,
				       layout);

	evas_object_smart_callback_add(entry, "unfocused", _entry_unfocused_cb,
				       layout);
	elm_object_signal_callback_add(layout, "elm,eraser,clicked", "elm",
				       _eraser_clicked_cb, entry);
 End:
	//CLK_FUN_END();
	return ret;

}

/**
* send
* This function is  used to create box
* @param           parent           pointer to evas object, as the  parent
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Evas_Object *widget_create_box(Evas_Object * parent)
{
	Evas_Object *ret = NULL;
	int nErr = SUCCESS;
	//CLK_FUN_BEG();
	ret = elm_box_add(parent);
	CLK_RETVM_IF(!ret, NULL, "elm_box_add error!");
	//beat style
	elm_box_horizontal_set(ret, 0);
	evas_object_size_hint_weight_set(ret, EVAS_HINT_EXPAND, 0.0);
	evas_object_size_hint_align_set(ret, EVAS_HINT_FILL, 0.0);
 End:
	//CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to create layout
* @param           parent           pointer to evas object, as the  parent
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Evas_Object *widget_create_layout(Evas_Object * parent)
{
	Evas_Object *ret = elm_layout_add(parent);
	retvm_if(!ret, NULL, "elm_layout_add error!");
	elm_layout_theme_set(ret, "layout", "application", "noindicator");
	evas_object_size_hint_weight_set(ret, EVAS_HINT_EXPAND,
					 EVAS_HINT_EXPAND);
	evas_object_show(ret);
	return ret;
}

/**
* send
* This function is  used to create popup
* @param           parent[in]               pointer to evas object, as the  parent
* @param           content_str[in]          string for description text.
* @param           title_str[in]            string for label
* @param           timeout[double]          double for popup time
* @param           response_cb[in]          cb to get single "response"
* @param           data[in]                 @response_cb data
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Evas_Object *widget_create_popup(Evas_Object * parent, char *content_str,
				 char *title_str, double timeout,
				 EO_SMART_CB response_cb, void *data)
{
	Evas_Object *popup = elm_popup_add(parent);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND,
					 EVAS_HINT_EXPAND);
	if (content_str) {
		gchar r_str_text[200] = { 0 };
		snprintf(r_str_text, sizeof(r_str_text),
			 "<font_size=32><align=center>%s</align></font_size>",
			 content_str);
		elm_object_text_set(popup, r_str_text);
	}
	if (title_str) {
		elm_object_text_set(popup, title_str);
	}
	if (timeout > 0) {
		elm_popup_timeout_set(popup, timeout);
	}
	if (response_cb) {
		evas_object_smart_callback_add(popup, "response", response_cb,
					       data);
	} else {
		evas_object_smart_callback_add(popup, "response",
					       _widget_def_popup_response_cb,
					       data);
	}
	evas_object_show(popup);
	return popup;
}

/**
* send
* This function is  used to create blank
* @param           parent[in]               pointer to evas object, as the  parent
* @param           minw[in]                 Evas_Coord, as min width
* @param           minh[in]                 Evas_Coord, as min height
* @return          when success, return a pointer to evas object, or return NULL
* @exception
*/
Evas_Object *widget_create_rectangle_blank(Evas_Object * parent,
					   Evas_Object * parent_box,
					   Evas_Coord minw, Evas_Coord minh)
{
	Evas_Object *rect;
	//CLK_FUN_BEG();
	rect = evas_object_rectangle_add(evas_object_evas_get(parent));
	retvm_if(NULL_CHECK(rect), NULL, "rect null");
	evas_object_size_hint_min_set(rect, minw, minh);
	evas_object_size_hint_weight_set(rect, 0.0, 0.0);
	evas_object_size_hint_align_set(rect, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_color_set(rect, 0, 0, 0, 0);
	elm_box_pack_end(parent_box, rect);
	evas_object_show(rect);
	//CLK_FUN_END();
	return rect;
}

/**********************************************************************
****************** BEG: EDC Widget button*************************************
***********************************************************************/
//
static Edje_Color_Class g_Edje_Color_Class;
static Eina_Bool g_bPressed = EINA_FALSE;
//
static void _clk_btn_mouse_down_cb(void *data, Evas_Object * obj,
				   const char *emission, const char *source)
{
	Edje_Color_Class *color_class = (Edje_Color_Class *) data;
	edje_object_color_class_get(obj, color_class->name,
				    &g_Edje_Color_Class.r,
				    &g_Edje_Color_Class.g,
				    &g_Edje_Color_Class.b,
				    &g_Edje_Color_Class.a,
				    &g_Edje_Color_Class.r2,
				    &g_Edje_Color_Class.g2,
				    &g_Edje_Color_Class.b2,
				    &g_Edje_Color_Class.a2,
				    &g_Edje_Color_Class.r3,
				    &g_Edje_Color_Class.g3,
				    &g_Edje_Color_Class.b3,
				    &g_Edje_Color_Class.a3);
	edje_object_color_class_set(obj, color_class->name, color_class->r,
				    color_class->g, color_class->b,
				    color_class->a, color_class->r2,
				    color_class->g2, color_class->b2,
				    color_class->a2, color_class->r3,
				    color_class->g3, color_class->b3,
				    color_class->a3);
	g_bPressed = EINA_TRUE;
}

//
static void _clk_btn_mouse_up_cb(void *data, Evas_Object * obj,
				 const char *emission, const char *source)
{
	Edje_Color_Class *color_class = (Edje_Color_Class *) data;
	if (g_bPressed) {
		edje_object_color_class_set(obj, color_class->name,
					    g_Edje_Color_Class.r,
					    g_Edje_Color_Class.g,
					    g_Edje_Color_Class.b,
					    g_Edje_Color_Class.a,
					    g_Edje_Color_Class.r2,
					    g_Edje_Color_Class.g2,
					    g_Edje_Color_Class.b2,
					    g_Edje_Color_Class.a2,
					    g_Edje_Color_Class.r3,
					    g_Edje_Color_Class.g3,
					    g_Edje_Color_Class.b3,
					    g_Edje_Color_Class.a3);
		g_bPressed = EINA_FALSE;
	}
}

//
Evas_Object *clk_widget_create_button(Evas_Object * parent,
				      const char *file, const char *group,
				      Edje_Color_Class * color_class,
				      Edje_Signal_Cb clicked_cb, void *data)
{
	retvm_if(NULL_CHECK(parent), NULL, "parent null");
	retvm_if(NULL_CHECK(file), NULL, "file null");
	retvm_if(NULL_CHECK(group), NULL, "group null");
	retvm_if(NULL_CHECK(color_class), NULL, "color_class null");
	CLK_FUN_BEG();
	Evas_Object *ret = NULL;
	ret = load_edj(parent, file, group);
	retvm_if(NULL_CHECK(ret), NULL, "ret null");
	edje_object_signal_callback_add(_EDJ(ret), "mouse,down", "rect",
					_clk_btn_mouse_down_cb,
					(void *)color_class);
	edje_object_signal_callback_add(_EDJ(ret), "mouse,up", "rect",
					_clk_btn_mouse_up_cb,
					(void *)color_class);
	if (clicked_cb) {
		edje_object_signal_callback_add(_EDJ(ret), "mouse,clicked",
						"rect", clicked_cb, data);
	}
	CLK_FUN_END();
	return ret;
}

/**********************************************************************
****************** END: EDC Widget button*************************************
***********************************************************************/
