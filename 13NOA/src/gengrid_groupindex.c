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



static int total_count;
static Evas_Object *gengrid, *box;
static Elm_Gengrid_Item_Class *gic;
static Elm_Gengrid_Item_Class ggic;
static Testitem ti[IMAGE_MAX*25];

char *group_names[] = {	"A", "B", "C", "D", "E", NULL};

static Evas_Object *
grid_content_get(void *data, Evas_Object *obj, const char *part)
{
	Testitem *ti = (Testitem *)data;

	if (ti->index == 1) {
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
	}

	return NULL;
}

static void
_item_selected(void *data, Evas_Object *obj, void *event_info)
{
	printf("--------------------------\nSelected Items :");
}


static char *
grid_text_get(void *data, Evas_Object *obj, const char *part)
{
	int index = (int)data;
	if (!strcmp(part, "elm.text")) {
		return strdup(group_names[index]);
	}
	return NULL;
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

	double scale = elm_config_scale_get();
	w = h = (int)(177 * scale) + 100; //177 as per UX ver 1.7.
	elm_gengrid_item_size_set(gengrid, w, h);

	w = (int)(720 * scale); //Should be equal to the width of the grid parent
	h = (int)(60 * scale); //Same as genlist, will update later as per UX.
	elm_gengrid_group_item_size_set(gengrid, w, h);
	elm_gengrid_align_set(gengrid, 0.0, 0.0);
	elm_gengrid_horizontal_set(gengrid, EINA_FALSE);

	elm_scroller_bounce_set(gengrid, EINA_FALSE, EINA_TRUE);
	elm_gengrid_multi_select_set(gengrid, EINA_TRUE);

	gic = elm_gengrid_item_class_new();
	gic->item_style="default_grid";

	gic->func.text_get = NULL;
	gic->func.content_get = grid_content_get;
	gic->func.state_get = NULL;
	gic->func.del = NULL;

	ggic.item_style = "group_index";
	ggic.func.text_get = grid_text_get;
	ggic.func.content_get = NULL;
	ggic.func.state_get = NULL;
	ggic.func.del = NULL;

	for (j = 0; j < 25; j++) {
		for (i = 0; i < IMAGE_MAX; i++) {
			n = i+(j*IMAGE_MAX);
			snprintf(buf, sizeof(buf), "%s/%d_raw.jpg", ICON_DIR, i+1);
			ti[n].index = buf;
			ti[n].path = eina_stringshare_add(buf);
			ti[i].item = elm_gengrid_item_append(gengrid, &ggic, (void *)(i%10), NULL, NULL);

/*			if (i == 0 || i == 11 || i == 22 || i == 33 || i == 44)
			  ti[i].item = elm_gengrid_item_append(gengrid, &ggic, (void *)(i%10), NULL, NULL);
			else
			  ti[i].item = elm_gengrid_item_append(gengrid, gic, &(ti[n]), _item_selected, &(ti[i]));
			ti[n].checked = EINA_FALSE;
*/			
		}
	}

	total_count = n + 1;

	printf( "Eixt _create_gengrid\n" );
}

static void
_back_btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	printf( "Entry groupindex _back_btn_cb\n");
/*
	// delete box
	if( NULL != box)
	{
		evas_object_del(box);
		box = NULL;
	}
*/	
	// delete gengrid
	if( gengrid )
	{
		printf( "debug: clear gengrid \n" );
		elm_gengrid_clear(gengrid);
		evas_object_del(gengrid);
		gengrid = NULL;
		//elm_gengrid_item_class_free(gic);
	}
/*	
	demo_data_s *ugd = (demo_data_s *)data;
	//promote current Elm_Object_Item to top
//	if( ugd && ugd->naviframe_item_mostpo )
	if( ugd->naviframe_item_mostpo )
	{
		printf( "debug: pop top item from naviframe \n" );
//		elm_naviframe_item_promote( ugd->naviframe_item_mostpo);
		elm_naviframe_item_pop(ugd->naviframe);
		// delete ugd->naviframe_item_whatsn
		elm_object_item_del(ugd->naviframe_item_mostpo);
		ugd->naviframe_item_mostpo = NULL;	
	}	
*/
	printf( "Eixt _back_btn_cb\n");

}

void gengrid_groupindex_release( void* data )
{
	printf( "Debug: release default gengrid.\n");
	_back_btn_cb( data, NULL, NULL );
}

void
gengrid_groupindex_cb(void *data, Evas_Object *obj, void *event_info)
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
	Elm_Object_Item *naviframe_item = NULL;

	ad = (demo_data_s *)data;
	if (ad == NULL) return;

	_create_gengrid(ad);

	box = elm_box_add(ad->naviframe);
	evas_object_size_hint_weight_set(box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_show(box);
	elm_box_pack_end(box, gengrid);
	evas_object_show(gengrid);

	//wrong method to assign item to a local variable, then assign to ad->naviframe_item_geners
	naviframe_item = elm_naviframe_item_push (ad->naviframe, _("Group Index Sample") , NULL, NULL, box, NULL);
	if( NULL == naviframe_item )
	{
		printf( "debug: elm_naviframe_item_push failed, delete objects and return directly." );
		_back_btn_cb( ad, NULL, NULL );
		return;
	}

	back_btn = elm_object_item_part_content_get(naviframe_item, "prev_btn");
	evas_object_smart_callback_add(back_btn, "clicked", _back_btn_cb, ad);
}


