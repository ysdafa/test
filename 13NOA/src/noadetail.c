
#include "noadetail.h"

static Evas_Object *gengrid, *box;
static Elm_Gengrid_Item_Class *gic,*gic2;
static Elm_Gengrid_Item_Class ggic;

static char *group_names[] = {"Other Episodes", "Cast&Crew", "Related Content", NULL};

static const char entry_input_text[] = {
	"English is a application as a server, used to split screen display. "
	"User can select the application from the running application list. "
	"Its interface will be split screen display in two mobile phones. "
	"Then open the English application, the screen will be display in the client."
	"Its interface will be split screen display in two mobile phones. "
	"Then open the English application, the screen will be display in the client."

};


static void _watch_now_view(void *data, Evas_Object *btn, void *ev)
{
	printf( "watch now button clicked\n");
}
Evas_Object *create_layout(Evas_Object *parent, char *group)
{
		Evas_Object *layout = NULL;
		if (parent == NULL) {
			printf( "PARENT IS NULL");
		}
		
		layout = elm_layout_add(parent);
		if (layout) { 
			if (!elm_layout_file_set(layout, VIEW_EDJ, group)) {
				evas_object_del(layout);  
				return NULL;                                                      
			} else {
				evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
				return layout;																			
			}                                                                     
		} else {
			return NULL;
		} 
}

static Evas_Object * grid_content_get(void *data, Evas_Object *obj, const char *part)
{
	printf("entry  grid_content_get");

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
	}

	return NULL;
}

static char * grid_text_get(void *data, Evas_Object *obj, const char *part)
{
	printf("entry  grid_text_get");

	Testitem *ti = (Testitem *)data;

	if(1 == ti->index || 3 == ti->index || 5 == ti->index)
	{
		if (!strcmp(part, "elm.text.up")) 
		{
			return strdup(ti->text);
		}
		if ((5 == ti->index)&&(!strcmp(part, "elm.text")))
		{
			return strdup("test!!!");
		}
	}
	else
	{
		if (!strcmp(part, "elm.text")) 
		{
			return strdup(ti->text);
		}	
	}
	return NULL;
}

static void _item_selected(void *data, Evas_Object *obj, void *event_info)
{
	printf("--------------------------\nSelected Items ");
}

static void
_detail_back_btn_cb(void *data, Evas_Object *obj, void *event_inaviframeo)
{
	printf( "Entry _detail_back_btn_cb\n");

	// delete gengrid
	if( gengrid)
	{
		printf( "debug: clear gengrid items \n" );
		elm_gengrid_clear(gengrid);
		evas_object_del(gengrid);
		gengrid = NULL;
	}
	
	demo_data_s *ugd = (demo_data_s *)data;
	if( ugd )
	{
		elm_naviframe_item_pop(ugd->naviframe);
	}
	printf( "Eixt _detail_back_btn_cb\n");
}


void _show_noa_detail(void *data, Evas_Object *obj, void *event_inaviframeo)
{
	printf( "entry _show_noa_detail\n");

	int i,high,width;
	Evas_Object *btn,*ic, *back_btn;
	char buf[PATH_MAX];
	static Testitem ti[IMAGE_MAX];
	
	Testitem *para = (Testitem *)data;

	elm_theme_extension_add(NULL, GENGRID_EDJ);	//use gengrid_custom.edc for gengrid style
	
	Evas_Object *layout = create_layout(para->naviframe, "set_contact_view");
	
	Evas_Object *entry = elm_entry_add(layout);
	elm_entry_entry_set(entry, entry_input_text);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	elm_entry_scrollbar_policy_set(entry, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	elm_entry_editable_set(entry, EINA_FALSE);
	elm_object_part_content_set(layout, "entry", entry);

	//if(NULL == elm_naviframe_item_push(para->naviframe, NOA_DETAIL, NULL, NULL, layout, NULL))
	if(NULL == elm_naviframe_item_push(para->naviframe, NULL, NULL, NULL, layout, "empty"))
    { 
        printf( "_show_noa_detail, push failed\n");
	    return;
	}

	/* button_watch_now */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style2");
	elm_object_text_set(btn, "Watch Now");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_watch_now", btn);

	/* button_love */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_love", btn);
	
	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_favorite.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_BOTH, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	/* button_good */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	elm_object_text_set(btn, "361");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_good", btn);

	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_recommendation_up.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);
	

	/* button_bad */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	elm_object_text_set(btn, "23");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_bad", btn);

	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_recommendation_down.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	/* button_facebook */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_facebook", btn);

	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_facebook.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_BOTH, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	/* button_twitter */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_twitter", btn);

	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_twitter.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_BOTH, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	// button back
	back_btn = elm_button_add(layout);
	elm_object_style_set(back_btn, "naviframe/back_btn/default");
    evas_object_smart_callback_add(back_btn, "clicked", (void *)_detail_back_btn_cb, para);
    elm_object_focus_allow_set(back_btn,EINA_FALSE);
	evas_object_show(back_btn);
	evas_object_color_set(back_btn, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	// set back button for  mostp_layout
	elm_object_part_content_set(layout, "prev_btn", back_btn);

	/* gengrid group */
	gengrid = elm_gengrid_add(layout);
	evas_object_size_hint_weight_set(gengrid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(gengrid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_part_content_set(layout, "gengrid_group", gengrid);
	
	double scale = elm_config_scale_get();
	width = high= (int)(220 * scale); //177 as per UX ver 1.7.
	elm_gengrid_item_size_set(gengrid, width, high);
	elm_gengrid_group_item_size_set(gengrid, (int)width/8, high);
	elm_gengrid_align_set(gengrid, 0.0, 0.5);
	elm_gengrid_horizontal_set(gengrid, EINA_TRUE);

	elm_scroller_bounce_set(gengrid, EINA_FALSE, EINA_TRUE);
	elm_gengrid_multi_select_set(gengrid, EINA_TRUE);

	
	gic = elm_gengrid_item_class_new();
	
	gic->item_style="noa_default_gridtext";
	gic->func.text_get = grid_text_get;
	gic->func.content_get = grid_content_get;
	gic->func.state_get = NULL;
	gic->func.del = NULL;
	
	gic2= elm_gengrid_item_class_new();

	gic2->item_style="noa_default_gridtext";
	gic2->func.text_get = grid_text_get;
	gic2->func.content_get = grid_content_get;
	gic2->func.state_get = NULL;
	gic2->func.del = NULL;

	ggic.item_style = "group_index";
	ggic.func.text_get = NULL;
	ggic.func.content_get = NULL;
	ggic.func.state_get = NULL;
	ggic.func.del = NULL;

	for (i = 0; i < IMAGE_MAX; i++) 
	{
		snprintf(buf, sizeof(buf), "%s/grid_image/%d_raw.jpg", ICON_DIR, i+1);
		ti[i].index = i;
		ti[i].path = eina_stringshare_add(buf);
		
		if (0 == i || 2 == i || 4 == i )
		{
			ti[i].item = elm_gengrid_item_append(gengrid, &ggic, (void *)i, NULL, NULL);
		}
		else if(1 == i || 3 == i || 5 == i )
		{

			ti[i].item = elm_gengrid_item_append(gengrid, gic2, &(ti[i]), _item_selected, &(ti[i]));
			if(1 == i)
				{ ti[i].text = strdup("Other Episodes"); }
			else if(3 == i)
				{ ti[i].text = strdup("Cast Crew"); }
			else 
				{ ti[i].text = strdup("Related Content"); }
		}
		else
		{
			ti[i].item = elm_gengrid_item_append(gengrid, gic, &(ti[i]), _item_selected, &(ti[i]));	
			snprintf(buf, sizeof(buf), "%d_raw.jpg", i+1);
			ti[i].text = strdup(buf);
		}
		
			ti[i].checked = EINA_FALSE;
			
	}	


}

