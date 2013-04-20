/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#include "noa.h"
#include "elmdemo_util.h"
#include "gengrid.h"

#define IMAGE_MAX 20
#define VIEW_MODE 0
#define EDIT_MODE 1

#define ICON_DIR "images"



static int mode;
static int total_count;
static int checked_count;
static Eina_Bool select_all_checked = EINA_FALSE;
static Eina_Bool longpressed = EINA_FALSE;
static Evas_Object *edit_btn, *del_btn, *box;
static Evas_Object *select_all_layout, *select_all_checkbox;
static Elm_Gengrid_Item_Class *gic;
static Testitem ti[IMAGE_MAX*25];

static Evas_Object *gengrid = NULL;
static Elm_Object_Item *naviframe_item = NULL;

static void
grid_moved(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *moved_item = (Elm_Object_Item *)event_info;

	Testitem *moved_ti = (Testitem *)elm_object_item_data_get(moved_item);
	printf("moved item index = %d", moved_ti->index);

	if (elm_gengrid_item_prev_get(moved_item)) {
		Testitem *prev_ti = (Testitem *)elm_object_item_data_get(elm_gengrid_item_prev_get(moved_item));
		printf(", prev index = %d", prev_ti->index);
	}
	if (elm_gengrid_item_next_get(moved_item)) {
		Testitem *next_ti = (Testitem *)elm_object_item_data_get(elm_gengrid_item_next_get(moved_item));
		printf(", next index = %d", next_ti->index);
	}
	printf("\n");

	// If you want change your data, you can here.
}

static void
grid_longpress(void *data, Evas_Object *obj, void *event_info)
{
	longpressed = (mode == EDIT_MODE ? EINA_TRUE : EINA_FALSE);
}

static void
_item_check_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	Testitem *ti = (Testitem *)data;

	if (longpressed) {
		ti->checked = !elm_check_state_get(obj);
		elm_check_state_set(obj, ti->checked);
		longpressed = EINA_FALSE;
	} else {
		ti->checked = elm_check_state_get(obj);

		if (ti->checked) checked_count++;
		else checked_count--;

		if (select_all_layout) {
			if (total_count == checked_count)
				select_all_checked = EINA_TRUE;
			else
				select_all_checked = EINA_FALSE;

			elm_check_state_pointer_set(select_all_checkbox, &select_all_checked);
		}
	}

	elm_gengrid_item_selected_set(ti->item, ti->checked);
}

static Evas_Object *
grid_content_get(void *data, Evas_Object *obj, const char *part)
{
	Testitem *ti = (Testitem *)data;
	Elm_Object_Item *it = elm_gengrid_last_item_get(obj);
	int last_idx = elm_gengrid_item_index_get(it);

	if (ti->index == (last_idx - 1)) {
		if (!strcmp(part, "elm.swallow.end")) {
			Evas_Object *progressbar = elm_progressbar_add(obj);
			elm_object_style_set(progressbar, "list_process_small");
			evas_object_size_hint_align_set(progressbar, EVAS_HINT_FILL, 0.5);
			evas_object_size_hint_weight_set(progressbar, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_show(progressbar);
			elm_progressbar_pulse(progressbar, EINA_TRUE);
			return progressbar;
		} else return NULL;
	} else if (!strcmp(part, "elm.swallow.icon")) {
		Evas_Object *icon = elm_image_add(obj);
		elm_image_file_set(icon, ti->path, NULL);
		elm_image_aspect_fixed_set(icon, EINA_FALSE);
		evas_object_show(icon);
		return icon;
	} else if (!strcmp(part, "elm.swallow.end") && mode == EDIT_MODE) {
		Evas_Object *ck = elm_check_add(obj);
		elm_object_style_set(ck, "grid");
		evas_object_propagate_events_set(ck, EINA_FALSE);
		elm_check_state_set(ck, ti->checked);
		elm_gengrid_item_selected_set(ti->item, ti->checked);
		evas_object_smart_callback_add(ck, "changed", _item_check_changed_cb, data);
		evas_object_show(ck);
		return ck;
	}

	return NULL;
}

static void
_show_selected_items(Testitem *ti)
{
	/*const Eina_List* list = elm_gengrid_selected_items_get(grid);
	const Eina_List* l = NULL;
	Elm_Object_Item *recv = NULL;
	printf("--------------------------\nSelected Items :");
	EINA_LIST_FOREACH(list, l, recv) {
		Testitem *ti = (Testitem *)elm_object_item_data_get(recv);
		printf("%d ",ti->index);
	}
	printf("\n--------------------------\n");*/
}

static void
_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	Testitem *ti = (Testitem *)data;
	printf("item selected: %p\n", event_info);

	_show_selected_items(ti);

	if (mode == VIEW_MODE)
		elm_gengrid_item_selected_set(ti->item, EINA_FALSE);
}

static void
_create_gengrid (void *data)
{
	printf( "Entry _create_gengrid\n" );
	demo_data_s *ad = (demo_data_s *)data;
	int i, j, n, w, h;
	char buf[PATH_MAX];
	char imagename[PATH_MAX];

	gengrid = elm_gengrid_add(ad->naviframe);
	evas_object_size_hint_weight_set(gengrid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(gengrid, EVAS_HINT_FILL, EVAS_HINT_FILL);

	//set gengrid size 
	ecore_x_window_size_get(ecore_x_window_root_first_get(), &w, &h);
	printf( "windows size are w -> %d, h -> %d \n", w, h );
	evas_object_resize(gengrid, w, THUMB_IMAGE_HEIGHT );	

	double scale = elm_config_scale_get();
	w = (int)THUMB_IMAGE_WIDTH * scale; 
	h = (int)THUMB_IMAGE_HEIGHT * scale;
	printf( "item size are w -> %d, h -> %d \n", w, h );
	elm_gengrid_item_size_set(gengrid, w, h);
	
	//elm_gengrid_align_set(gengrid, 0.5, 0.0);
	elm_gengrid_horizontal_set(gengrid, EINA_TRUE);
	elm_scroller_bounce_set(gengrid, EINA_FALSE, EINA_TRUE);
	elm_gengrid_multi_select_set(gengrid, EINA_TRUE);
	evas_object_smart_callback_add(gengrid, "moved", grid_moved, NULL);
	evas_object_smart_callback_add(gengrid, "longpressed", grid_longpress, NULL);

	// set page size
	//elm_gengrid_page_size_set( gengrid, 1024, h );
	elm_scroller_page_size_set(gengrid, 1024, h );
	// set align
	elm_gengrid_align_set(gengrid, 0.0, 0.3);	 

	gic = elm_gengrid_item_class_new();
	gic->item_style="default_grid";

	gic->func.text_get = NULL;
	gic->func.content_get = grid_content_get;
	gic->func.state_get = NULL;
	gic->func.del = NULL;

	for (j = 0; j < 25; j++) {
		for (i = 0; i < IMAGE_MAX; i++) {
			n = i+(j*IMAGE_MAX);
			snprintf(buf, sizeof(buf), "%s/%d_raw.jpg", ICON_DIR, i+1);
			ti[n].index = n;
			ti[n].path = eina_stringshare_add(buf);
			ti[n].item = elm_gengrid_item_append(gengrid, gic, &(ti[n]), _item_selected, &(ti[i]));
			ti[n].checked = EINA_FALSE;
		}
	}

	total_count = n + 1;

	printf( "Eixt _create_gengrid\n" );
}

static void
_check_select_all()
{
	Elm_Object_Item *it;
	Testitem *ti;

	if (select_all_checked) checked_count = total_count;
	else checked_count = 0;

	it = elm_gengrid_first_item_get(gengrid);
	while(it) {
		ti = elm_object_item_data_get(it);
		if (ti) ti->checked = select_all_checked;
		elm_gengrid_item_selected_set(it, select_all_checked);
		elm_gengrid_item_update (it);
		it = elm_gengrid_item_next_get(it);
	}
}

static void
_select_all_layout_mouse_down_cb(void *data, Evas *evas, Evas_Object *obj, void *event_info)
{
	select_all_checked = !select_all_checked;
	elm_check_state_pointer_set(select_all_checkbox, &select_all_checked);

	_check_select_all();
}

static void _select_all_check_changed_cb(void *data, Evas_Object *obj, void *event_info)
{
	_check_select_all(data);
}

static void _delete_button_cb(void *data, Evas_Object *obj, void *event_info)
{
	Testitem *ti;
	Elm_Object_Item *it;

	it = elm_gengrid_first_item_get(gengrid);
	while (it) {
		ti = (Testitem *)elm_object_item_data_get(it);
		it = elm_gengrid_item_next_get(it);

		if ((ti) && (ti->checked)) {
			elm_object_item_del(ti->item);
			total_count--;
			checked_count--;
		}
	}
}

static void
_edit_btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	Elm_Object_Item *navi_it = (Elm_Object_Item *)data;

	if (mode == VIEW_MODE) {
		mode = EDIT_MODE;
		elm_object_text_set(edit_btn, _("Done"));

		if (!del_btn) {
			del_btn = elm_button_add(box);
			elm_object_style_set(del_btn, "naviframe/toolbar/default");
			evas_object_size_hint_weight_set(del_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
			evas_object_size_hint_align_set(del_btn, EVAS_HINT_FILL, 0.5);
			elm_object_text_set(del_btn, _("Delete"));
			elm_object_item_part_content_set(navi_it, "toolbar_button1", del_btn);
			evas_object_smart_callback_add(del_btn, "clicked", _delete_button_cb, NULL);
			evas_object_show(del_btn);
		}

		select_all_layout = elm_layout_add(box);
		elm_layout_theme_set(select_all_layout, "genlist", "item", "select_all/default");
		evas_object_size_hint_weight_set(select_all_layout, EVAS_HINT_EXPAND, EVAS_HINT_FILL);
		evas_object_size_hint_align_set(select_all_layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
		evas_object_event_callback_add(select_all_layout, EVAS_CALLBACK_MOUSE_DOWN, _select_all_layout_mouse_down_cb, NULL);

		select_all_checkbox = elm_check_add(select_all_layout);
		elm_check_state_pointer_set(select_all_checkbox, &select_all_checked);
		evas_object_smart_callback_add(select_all_checkbox, "changed", _select_all_check_changed_cb, NULL);
		evas_object_propagate_events_set(select_all_checkbox, EINA_FALSE);
		elm_object_part_content_set(select_all_layout, "elm.icon", select_all_checkbox);

		elm_object_part_text_set(select_all_layout, "elm.text", "Select All");
		elm_box_pack_start(box, select_all_layout);
		evas_object_show(select_all_layout);

		elm_gengrid_reorder_mode_set(gengrid, EINA_TRUE);
	} else {
		mode = VIEW_MODE;
		elm_object_text_set(edit_btn, _("Edit"));

		elm_object_item_part_content_unset(navi_it, "toolbar_button1");
		evas_object_del(del_btn);
		del_btn = NULL;

		elm_box_unpack(box, select_all_layout);
		evas_object_del(select_all_layout);
		select_all_layout = NULL;

		elm_gengrid_reorder_mode_set(gengrid, EINA_FALSE);
	}

	select_all_checked = EINA_FALSE;
	_check_select_all();
}

static void
_back_btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf( "Entry default grid _back_btn_cb\n");

/*	
	if(edit_btn)
	{
		evas_object_del(edit_btn);
		edit_btn = NULL;
	}
	if( del_btn )
	{
		evas_object_del(del_btn);
		del_btn = NULL;
	}

	if( select_all_layout )
	{
		elm_box_unpack(box, select_all_layout);
		evas_object_del(select_all_layout);
		select_all_layout = NULL;
	}
	if(select_all_checkbox)
	{
		evas_object_del(select_all_checkbox);
		select_all_checkbox = NULL;
	}

*/	

	// delete box
	if( NULL != box)
	{
		printf( "debug: clear box in default \n" );
		evas_object_del(box);
		box = NULL;
	}

	// delete gengrid
	if( gengrid )
	{
		printf( "debug: clear gengrid items \n" );
		elm_gengrid_clear(gengrid);
		//delete object
		evas_object_del(gengrid);
		gengrid = NULL;
		// free gic cause coredump ???
		//elm_gengrid_item_class_free(gic);
	}

	demo_data_s *ugd = (demo_data_s *)data;
	if( ugd && naviframe_item)
	{
		//elm_naviframe_item_pop(ugd->naviframe);
		// delete naviframe_item_mostpo
		elm_object_item_del( naviframe_item);
		naviframe_item = NULL;	
	}
	
/*
	demo_data_s *ugd = (demo_data_s *)data;
	//promote current Elm_Object_Item to top
//	if( ugd && ugd->naviframe_item_mostpo )
	if( ugd->naviframe_item_mostpo )
	{
		printf( "debug: pop top item from naviframe \n" );
//		elm_naviframe_item_promote( ugd->naviframe_item_mostpo );
		elm_naviframe_item_pop(ugd->naviframe);
		// delete naviframe_item_mostpo
		elm_object_item_del(ugd->naviframe_item_mostpo);
		ugd->naviframe_item_mostpo = NULL;	
	}
*/
	printf( "Eixt _back_btn_cb\n");
}

void gengrid_default_release( void* data )
{
	printf( "Debug: release default gengrid.\n");
	_back_btn_cb( data, NULL, NULL );
}

void
gengrid_default_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf( "Entry gengrid_create_view\n" );
	if( gengrid )
	{
		printf( "Entry gengrid default already existed.\n" );
		return;
	}
	demo_data_s *ad;
	Evas_Object *back_btn;
	Elm_Object_Item *it = NULL;

	ad = (demo_data_s *)data;
	if (ad == NULL) return;

	mode = VIEW_MODE;

	_create_gengrid(ad);
	it = elm_gengrid_last_item_get(gengrid);
//	elm_gengrid_item_show(it, ELM_GENGRID_ITEM_SCROLLTO_IN);
	elm_gengrid_item_show(it, ELM_GENGRID_ITEM_SCROLLTO_TOP);

	box = elm_box_add(ad->naviframe);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(box);
	elm_box_pack_end(box, gengrid);
	evas_object_show(gengrid);

	naviframe_item = elm_naviframe_item_push (ad->naviframe, _("Default") , NULL, NULL, box, NULL);
	if( NULL == naviframe_item )
	{
		printf( "debug: elm_naviframe_item_push failed, delete objects and return directly." );
		_back_btn_cb( ad, NULL, NULL );
		return;
	}

/*	edit_btn = elm_button_add(ad->naviframe);
	evas_object_smart_callback_add(edit_btn, "clicked", _edit_btn_cb, navi_it);
	elm_object_style_set(edit_btn, "naviframe/toolbar/default");
	evas_object_size_hint_weight_set(edit_btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(edit_btn, EVAS_HINT_FILL, 0.5);
	elm_object_text_set(edit_btn, _("Edit"));
	evas_object_show(edit_btn);
	elm_object_item_part_content_set(ad->naviframe_item_mostpo, "toolbar_button2", edit_btn);
*/
	back_btn = elm_object_item_part_content_get(naviframe_item, "prev_btn");
	evas_object_smart_callback_add(back_btn, "clicked", _back_btn_cb, ad);

}
