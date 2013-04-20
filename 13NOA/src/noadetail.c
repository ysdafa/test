
#include "noadetail.h"


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


void _show_noa_detail(void *data, Evas_Object *obj, void *event_inaviframeo)
{
	printf( "entry _show_noa_detail\n");

	Evas_Object *btn,*ic;
	char buf[PATH_MAX];
	
	Testitem *para = (Testitem *)data;

	
	Evas_Object *layout = create_layout(para->naviframe, "set_contact_view");
	
	Evas_Object *entry = elm_entry_add(layout);
	elm_entry_entry_set(entry, entry_input_text);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	elm_entry_scrollbar_policy_set(entry, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	elm_entry_editable_set(entry, EINA_FALSE);
	elm_object_part_content_set(layout, "entry", entry);		
	if(NULL == elm_naviframe_item_push(para->naviframe, NOA_DETAIL, NULL, NULL, layout, NULL))
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
	//elm_object_text_set(btn, "love");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_love", btn);
	
	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_favorite.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	/* button_good */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	elm_object_text_set(btn, "361");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_good", btn);

	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_recommendation_down.png", ICON_DIR);
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
	snprintf(buf, sizeof(buf), "%s/icon_recommendation_up.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	/* button_facebook */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	//elm_object_text_set(btn, "f");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_facebook", btn);

	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_facebook.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	/* button_twitter */
	btn = elm_button_add(layout);
	elm_object_style_set(btn, "style1");
	//elm_object_text_set(btn, "t");
	evas_object_smart_callback_add(btn, "clicked", _watch_now_view, para);
	elm_object_part_content_set(layout, "button_twitter", btn);

	ic = elm_image_add(layout);
	snprintf(buf, sizeof(buf), "%s/icon_twitter.png", ICON_DIR);
	elm_image_file_set(ic, buf, NULL);
	evas_object_size_hint_aspect_set(ic, EVAS_ASPECT_CONTROL_VERTICAL, 1, 1);
	elm_image_resizable_set(ic, EINA_TRUE, EINA_TRUE);
	elm_object_part_content_set(btn, "icon", ic);

	


	
}

