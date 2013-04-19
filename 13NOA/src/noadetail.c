
#include "noadetail.h"


static const char entry_input_text[] = {
	"English is a application as a server, used to split screen display. "
	"User can select the application from the running application list. "
	"Its interface will be split screen display in two mobile phones. "
	"Then open the English application, the screen will be display in the client."
};

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

	Testitem *para = (Testitem *)data;
	
	Evas_Object *layout = create_layout(para->naviframe, "set_contact_view");

	Evas_Object *entry = elm_entry_add(layout);
	elm_entry_entry_set(entry, entry_input_text);
	elm_entry_scrollable_set(entry, EINA_TRUE);
	elm_entry_scrollbar_policy_set(entry, ELM_SCROLLER_POLICY_OFF, ELM_SCROLLER_POLICY_AUTO);
	elm_entry_editable_set(entry, EINA_FALSE);
	elm_object_part_content_set(layout, "entry", entry);	
	
	elm_naviframe_item_push(para->naviframe, APP_ABOUT, NULL, NULL, layout, NULL);	

}

