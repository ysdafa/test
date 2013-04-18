#include <Ecore.h>
#include <Ecore_Evas.h>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <app_manager.h>
#include <math.h>
#include <sys/sysinfo.h>
#include <sched.h>
#include <pthread.h>
#include "demo.h"

#include"gengrid.h"

#define PACKAGE "create_view"
#define APP_LIST "Home Panel"
#define APP_LIST_MAX_COUNT 20
#define APP_CANCEL_LIST_COUNT 7
#define LOCALE_DIR APP_DIR"/res/locale"
#define APP_DIR	"/usr/apps/com.samsung.create_view"
#define APP_ABOUT "About create_view"
#define EDJ_DIR APP_DIR"/res/edje"
#define VIEW_EDJ EDJ_DIR"/create_view.edj"
#define NUM_OF_ITEMS 7  //setting interface item number
#define VIDEO_FILE_LIST "Movies"
#define ICON_DIR PREFIX"/res/images"

//static Evas_Object* ctxpopup = NULL;
static Elm_Genlist_Item_Class itc_newview, itc, itc2, nfc_itc, video_itc;
static unsigned int REFREASH_FRAME = 1;
static unsigned int NFC_INSTANCE = 5;
bool WIFI_STATE = false;
int flag_network = 0;
void create_app_list_view(void *data);
demo_data_s *gl_ugd = NULL;

char videoNameList[APP_LIST_MAX_COUNT][50] = {
        "Video1",
        "Vdieo2",
        "Video3",
	"Video4",
        "Vdieo5",
        "Video6",
        "Video7",
        "Vdieo8",
        "Video9",
	"Video10",
        "Vdieo11",
        "Video12",
        "Video13",
        "Vdieo14",
        "Video15",
	"Video16",
        "Vdieo17",
        "Video18",
	"Vdieo19",
	"Video20"
};

char appNameList[APP_LIST_MAX_COUNT][50] = {{0}};
char appNameCancelList[APP_CANCEL_LIST_COUNT][50] = 
{
	"Nomal style",
	"extraordinary style",
	"larger style"
};

static const char entry_input_text[] = {
        "English is a application as a server, used to split screen display. "
	"User can select the application from the running application list. "
	"Its interface will be split screen display in two mobile phones. "
	"Then open the English application, the screen will be display in the client."
};

static char *slider_itemlist[] = {
	"text1",
	"text2",
	"WIFI-DIRECTER State",
	"text3",
	NULL
};

/* declare function*/
static void _create_whats_new_gengrid(void *data);
static void _create_most_populer_gengrid(void *data);
static void _create_geners_gengrid(void *data);
void exit_process(void *data);

static char *_gl_text_get(void *data, Evas_Object *obj, const char *part)
{
	int index = ((int)(long)data) / 2;
	return strdup(slider_itemlist[index]);
}

void _change_frame_cb(void *data, Evas_Object *obj, void *event_info)
{
        double val = elm_slider_value_get(obj);
        elm_slider_value_set(data, val);
	REFREASH_FRAME = (unsigned int)val;
	printf(	 "Entry _change_frame_cb val=%u\n", REFREASH_FRAME);
}

void _change_nfc_cb(void *data, Evas_Object *obj, void *event_info)
{
        double val = elm_slider_value_get(obj);
        elm_slider_value_set(data, val);
	NFC_INSTANCE = (unsigned int)val;
	printf(	 "Entry _change_nfc_cb val=%u\n", NFC_INSTANCE);
}

static Evas_Object *_gl_content_get(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *slider;
	int index = ((int)(long)data);

	slider = elm_slider_add(obj);
	elm_slider_indicator_show_set(slider, EINA_TRUE);
	evas_object_size_hint_weight_set(slider, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(slider, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_slider_indicator_format_set(slider, "%1.0f");
	//elm_slider_unit_format_set(slider, "%1.0f");
	printf( "Entry _gl_content_get");
	if (index == 1) {	
		elm_slider_min_max_set(slider, 1, 5);
		printf(	 "Entry _gl_content_get REFREASH_FRAME=%u\n", REFREASH_FRAME);
		elm_slider_value_set(slider, REFREASH_FRAME);
                elm_object_text_set(slider, "changes");
		evas_object_smart_callback_add(slider, "changed", _change_frame_cb, slider);
	}
	else if (index == 3) {	
		elm_slider_min_max_set(slider, 1, 10);
		elm_slider_value_set(slider, NFC_INSTANCE);
		printf(	 "Entry _gl_content_get NFC_INSTANCE=%u\n", NFC_INSTANCE);
		evas_object_smart_callback_add(slider, "changed", _change_nfc_cb, slider);
	}
	else if (index == 5) {	
		elm_slider_min_max_set(slider, 1, 10);
		elm_slider_value_set(slider, NFC_INSTANCE);
		printf(	 "Entry _gl_content_get NFC_INSTANCE=%u\n", NFC_INSTANCE);
		evas_object_smart_callback_add(slider, "changed", _change_nfc_cb, slider);
	}
	
	return slider;
}

static void _go_check_clicked_cb(void *data, Evas_Object *obj, void *event_info)
{
	if ( WIFI_STATE == true )
	{
		WIFI_STATE = false;
	}
	else if ( WIFI_STATE == false )
	{
		WIFI_STATE = true;
	}
}

static Evas_Object *_gl_wifi_content_get(void *data, Evas_Object *obj, const char *part)
{
	Evas_Object *check = NULL;
	printf( "Entry _gl_content_get");
	check = elm_check_add(obj);
	if ( WIFI_STATE == true )
	{
		elm_check_state_set(check, EINA_TRUE);
	}
	else if ( WIFI_STATE == false )
	{
		elm_check_state_set(check, EINA_FALSE);
	}
	
	elm_object_style_set(check, "favorite");
	evas_object_size_hint_weight_set(check, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(check, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_smart_callback_add(check, "changed", _go_check_clicked_cb, NULL);

	return check;
}

static Evas_Object* _create_parameter_set_genlist(Evas_Object* parent)
{
	Evas_Object *genlist;
	Elm_Object_Item *gl_item = NULL;
	int index;

	genlist = elm_genlist_add(parent);

	itc.item_style = "dialogue/1text";
	itc.func.text_get = _gl_text_get;
	itc.func.content_get = NULL;
	itc.func.state_get = NULL;
	itc.func.del = NULL;

	itc2.item_style = "dialogue/1icon";
	itc2.func.text_get = NULL;
	itc2.func.content_get = _gl_content_get;
	itc2.func.state_get = NULL;
	itc2.func.del = NULL;

	nfc_itc.item_style = "1text.1icon";
	nfc_itc.func.text_get = _gl_text_get;
	nfc_itc.func.content_get = _gl_wifi_content_get;
	nfc_itc.func.state_get = NULL;
	nfc_itc.func.del = NULL;

	evas_object_size_hint_weight_set(genlist, 0.0, 0.0);
	evas_object_size_hint_align_set(genlist, EVAS_HINT_FILL, EVAS_HINT_FILL);
	evas_object_show(genlist);

	for (index = 0; index < NUM_OF_ITEMS; index++) 
	{
		if ( index % 2 == 0 ) 
		{
			if ( index == 4 )
			{
				gl_item = elm_genlist_item_append(genlist, &nfc_itc, (void *) index, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
				elm_genlist_item_select_mode_set(gl_item, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);
				continue;
			}
			gl_item = elm_genlist_item_append(genlist, &itc, (void *) index, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
			elm_genlist_item_select_mode_set(gl_item, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);
		} 
		else 
		{
			gl_item = elm_genlist_item_append(genlist, &itc2, (void *) index, NULL, ELM_GENLIST_ITEM_NONE, NULL, NULL);
			elm_genlist_item_select_mode_set(gl_item, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);
		}
	}
	return genlist;
}

static void _set_back_btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	/* do nothing */
}

void set_app_parameter(void *data)
{	
	printf(	 "Entry set_app_parameter\n");
	demo_data_s *para = (demo_data_s *)data;
	Evas_Object *genlist, *back_btn;
	Elm_Object_Item *item;

	genlist = _create_parameter_set_genlist(para->naviframe);
	if(genlist == NULL)
        {
             printf( "Failed to _create_parameter_set_genlist\n");
             return;
        }

	elm_object_style_set (genlist, "dialogue");
	evas_object_show(genlist);
	item = elm_naviframe_item_push(para->naviframe, _("Set App Parameters"), NULL, NULL, genlist, NULL);
	back_btn = elm_object_item_part_content_get(item, "prev_btn");
	evas_object_smart_callback_add(back_btn, "clicked", _set_back_btn_cb, NULL);
	
}

static char *_gl_display_text_get(void *data, Evas_Object *obj, const char *part)
{
	int  index = (int)data;
	if ( index < APP_LIST_MAX_COUNT )
	{
		//printf(  "_gl_display_text_get %d name=%s\n", index, appNameList[index]);
		//return strdup(appNameList[index]);//appNameList[index]
		return "";
	}
	else
	{
		return strdup("Movies and TVShows");
	}
}

static char *_gl_video_text_get(void *data, Evas_Object *obj, const char *part)
{
	int  index = (int)data;
	
	return strdup(videoNameList[index]);
}

static void __wfdsp_separator_del(void *data, Evas_Object *obj)
{
	elm_genlist_item_class_free(data);
	return;
}

Elm_Object_Item* wfdsp_add_dialogue_separator(Evas_Object* genlist, const char *separator_style)
{
	//__FUNC_ENTER__;
        printf( "come in wfdsp_add_dialogue_separator\n");
	if ( genlist == NULL )
	{
		printf( "genlist == NULL\n");
		return NULL;
	}

	static Elm_Genlist_Item_Class *separator_itc;
	separator_itc = elm_genlist_item_class_new();
	separator_itc->item_style = separator_style;
	separator_itc->func.text_get = NULL;
	separator_itc->func.content_get = NULL;
	separator_itc->func.state_get = NULL;
	separator_itc->func.del = __wfdsp_separator_del;

	Elm_Object_Item* sep = elm_genlist_item_append(
					genlist,
					separator_itc,
					separator_itc,
					NULL,
					ELM_GENLIST_ITEM_GROUP,
					NULL,
					NULL);

	if ( sep == NULL )
	{
		printf( "sep == NULL\n");
		return NULL;
	}

	elm_genlist_item_select_mode_set(sep, ELM_OBJECT_SELECT_MODE_DISPLAY_ONLY);

	//__FUNC_EXIT__;
	return sep;
}

static void _gl_text_list_sel(void *data, Evas_Object *obj, void *event_num)
{
     printf("come in _gl_text_list_sel\n");
     //demo_data_s *ugd = (demo_data_s *) data;
     int index = (int)data;
     if ( index == 1 )
     {
//         ug_warn_popup(gl_ugd, "Connection wifi device", APP_LIST_TYPE);	
     }
     else if( index == 0 )
     {
//         ug_warn_popup(gl_ugd, "Connection nfc device", APP_LIST_TYPE);
     }
     else if( index == 2 )
     {
//         ug_warn_popup(gl_ugd, "Connection network device", APP_LIST_TYPE);
     }
}

static void _ug_warn_popup_cb(void *data, Evas_Object *obj)
{
   printf( "Entry _ug_warn_popup_cb\n");
   demo_data_s *ugd = (demo_data_s *)data;
   elm_naviframe_item_pop(ugd->naviframe);
}

static Evas_Object* _create_video_list_genlist(void *data)
{
	printf( "come in _create_video_list_genlist\n");
	demo_data_s *ugd = (demo_data_s *) data;
	Evas_Object *genlist;
	int i = 0;
	
	video_itc.item_style = "dialogue/1text";
	video_itc.func.text_get = _gl_video_text_get;
	video_itc.func.content_get = NULL;
	video_itc.func.state_get = NULL;
	video_itc.func.del = NULL;

	genlist = elm_genlist_add(ugd->naviframe);
	
	for ( i = 0; i < APP_LIST_MAX_COUNT; i++ )
	{
		if ( strlen(videoNameList[i] ) == 0 )
		{
			printf( "appNameList[%d] is NULL\n", i);
			continue;
		}
		
		wfdsp_add_dialogue_separator(genlist, "dialogue/separator");
		Elm_Object_Item* ret = elm_genlist_item_append(genlist, &video_itc, (void *)i, NULL, ELM_GENLIST_ITEM_NONE, _gl_text_list_sel, (void*) i);
		if ( ret == NULL )
		{
			printf( "append fialed!\n");
		}
		printf( "append success!\n");
	}
	
	//__FUNC_EXIT__;
	return genlist;
}

void _create_video_list(void *data)
{	
	printf(	 "Entry _create_video_list\n");
	demo_data_s *ugd = (demo_data_s *)data;
	Evas_Object *back_btn;
	Elm_Object_Item *it;

	ugd->video_genlist = _create_video_list_genlist(ugd->naviframe);
	if(ugd->video_genlist == NULL)
        {
             printf( "Failed to _create_video_list_genlist\n");
             return;
        }

	back_btn = elm_button_add(ugd->naviframe);
        elm_object_style_set(back_btn, "naviframe/back_btn/default");
        evas_object_smart_callback_add(back_btn, "clicked", (void *)_ug_warn_popup_cb, ugd);
        elm_object_focus_allow_set(back_btn, EINA_FALSE);

	//elm_object_style_set (ugd->video_genlist, "dialogue");
	evas_object_show(ugd->video_genlist);

	switch (ugd->eContentType)
	{
		case WHATSNEW_TYPE:
			it = elm_naviframe_item_push(ugd->naviframe, "What's New", back_btn, NULL, ugd->video_genlist, NULL);
			break;
		case MOSTPOPULAR_TYPE:
			it = elm_naviframe_item_push(ugd->naviframe, "Most Popular", back_btn, NULL, ugd->video_genlist, NULL);
			break;
		case GENRES_TYPE:
			it = elm_naviframe_item_push(ugd->naviframe, "Genres", back_btn, NULL, ugd->video_genlist, NULL);
			break;
		default:
			it = elm_naviframe_item_push(ugd->naviframe, VIDEO_FILE_LIST, back_btn, NULL, ugd->video_genlist, NULL);
			break;
	}
		
}

static void _create_whats_new_gengrid(void *data)
{	
	printf(	 "Entry _create_whats_new_gengrid\n");
	demo_data_s *para =(demo_data_s *)data;
	if(para == NULL)
	{
	    printf(  "Incorrect parameter(NULL)");
        return;
	}
/*
	if( para->naviframe_item_whatsn )
	{
	    printf(  "naviframe already existed, switch to top and show. \n");
		//switch to top
		elm_naviframe_item_promote(para->naviframe_item_whatsn);
		evas_object_show(para->naviframe);
		return;
	}
*/
	gengrid_gridtext_cb( data, NULL, NULL );
	
	printf(	 "Exit _create_whats_new_gengrid\n");		
}

static void _create_most_populer_gengrid(void *data)
{	
	printf(	 "Entry _create_most_populer_gengrid\n");

	demo_data_s *para =(demo_data_s *)data;
	if(para == NULL)
	{
	    printf(  "Incorrect parameter(NULL)");
        return;
	}
	
	/*
	Elm_Object_Item *naviframe_item = para->naviframe_item_mostpo;
	if( naviframe_item )
	{
	    printf(  "naviframe already existed, switch to top and show. \n");
		//switch to top
		elm_naviframe_item_promote(naviframe_item);
		evas_object_show(para->naviframe);
		return;
	}
	
	Evas_Object *back_btn =NULL;
	back_btn = elm_button_add(para->naviframe);
	elm_object_style_set(back_btn, "naviframe/back_btn/default");
     evas_object_smart_callback_add(back_btn, "clicked", (void *)exit_process, para);
     elm_object_focus_allow_set(back_btn,EINA_FALSE);
*/
	gengrid_default_cb( data, NULL, NULL );

	printf(	 "Exit _create_most_populer_gengrid\n");		
}

static void _create_geners_gengrid(void *data)
{	
	printf(	 "Entry _create_geners_gengrid\n");
	demo_data_s *para =(demo_data_s *)data;
	if(para == NULL)
	{
	    printf(  "Incorrect parameter(NULL)");
        return;
	}
	
/*	Elm_Object_Item *naviframe_item = para->naviframe_item_geners;
	if( naviframe_item )
	{
	    printf(  "naviframe already existed, switch to top and show. \n");
		//switch to top
		elm_naviframe_item_promote(naviframe_item);
		evas_object_show(para->naviframe);
		return;
	}
*/

/*	Evas_Object *back_btn =NULL;
	back_btn = elm_button_add(para->naviframe);
	elm_object_style_set(back_btn, "naviframe/back_btn/default");
     evas_object_smart_callback_add(back_btn, "clicked", (void *)exit_process, para);
     elm_object_focus_allow_set(back_btn,EINA_FALSE);
*/
	gengrid_groupindex_cb( data, NULL, NULL );

	printf(	 "Exit _create_geners_gengrid\n");		
}


static void _quit_cb(void *data, Evas_Object *obj, void *event)
{
	//JOINTSCREEN_RETURN_IF_FAILED(data);
	Evas_Object *win = (Evas_Object *) data;
	elm_win_lower(win);
}

static Evas_Object *create_base_layout(Evas_Object *parent)
{
	Evas_Object *layout = NULL;

	layout = elm_layout_add(parent);

	//elm_layout_theme_set(layout, "layout", "application", "default");
	elm_layout_theme_set(layout, "layout", "application", "default");
	
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_win_resize_object_add(parent, layout);
	evas_object_show(layout);

	return layout;
}

void exit_process(void *data)
{
    demo_data_s *para = (demo_data_s *)data;
	printf("enter exit_process \n");
    if(para!=NULL)
    {
    	if (para->genlist != NULL)
		{
			evas_object_del(para->genlist);
			para->genlist = NULL;
        	printf(   "1111111111111111\n");
		}

		if (para->video_genlist != NULL)
		{
			evas_object_del(para->video_genlist);
			para->video_genlist = NULL;
            printf(   "22222222222222\n");
		}

		if (para->about_genlist != NULL)
		{
			evas_object_del(para->about_genlist);
			para->about_genlist = NULL;
            printf(   "3333333333333\n");
		}

		gengrid_default_release( para );
		gengrid_groupindex_release( para );
		gengrid_gridtext_release( para );
	}
    printf(   "exit_process exit3\n");
	elm_exit();
}


static Evas_Object *create_preview_genlist(void *data)
{
    demo_data_s *para = (demo_data_s *) data;
	Evas_Object *genlist;
	int i = 0;
	int j = 0;
	bool flag = true;

	itc_newview.item_style = "dialogue/1text";
	itc_newview.func.text_get = _gl_display_text_get;
	itc_newview.func.content_get = NULL;
	itc_newview.func.state_get = NULL;
	itc_newview.func.del = NULL;

	genlist = elm_genlist_add(para->naviframe);
        /* add the video list */
	Elm_Object_Item* ret = elm_genlist_item_append(genlist, &itc_newview, (void *)APP_LIST_MAX_COUNT, NULL, ELM_GENLIST_ITEM_NONE, (Evas_Smart_Cb)_create_video_list, (void *)para);
	if ( ret == NULL )
	{
		printf( "append fialed!\n");
	}
	//printf("come in _create_basic_genlist111111111\n");
	for ( i = 0; i < APP_LIST_MAX_COUNT; i++ )
	{
		if ( strlen(appNameList[i] ) == 0 )
		{
			continue;
		}

		flag = true;
		//printf("come in _create_basic_genlist5555555\n");
		for ( j = 0; j < APP_CANCEL_LIST_COUNT; j++ )
		{
			if ( strncmp(appNameList[i], appNameCancelList[j], strlen(appNameCancelList[j])) == 0 )
			{
				flag = false;
				break;
			}
		}
		//printf("come in _create_basic_genlist6666\n");
		if ( flag == false )
		{
			continue;
		}
		//printf("come in _create_basic_genlist33333333333\n");
		//wfdsp_add_dialogue_separator(genlist, "dialogue/separator");
		Elm_Object_Item* ret = elm_genlist_item_append(genlist, &itc_newview, (void *)i, NULL, ELM_GENLIST_ITEM_NONE,NULL, (void*) i);
		if ( ret == NULL )
		{
			printf( "append fialed!\n");
		}
		//printf("come in _create_basic_genlist444444444444\n");
		//printf( "append success!\n");
	}
	
	//__FUNC_EXIT__;
	//printf("come in _create_basic_genlist222222222\n");
	elm_genlist_mode_set( genlist, ELM_LIST_LIMIT );
	return genlist;
}


void create_app_list_view(void *data)
{
    demo_data_s *para =(demo_data_s *)data;
	Evas_Object *back_btn =NULL, *bghead = NULL, *tvshow_bt = NULL;
	Elm_Object_Item *naviframe_item = NULL;
	if(para == NULL)
	{
	    printf(  "Incorrect parameter(NULL)");
        return;
	}
	back_btn = elm_button_add(para->naviframe);
	elm_object_style_set(back_btn, "naviframe/back_btn/default");
    evas_object_smart_callback_add(back_btn, "clicked", (void *)exit_process, para);
    elm_object_focus_allow_set(back_btn,EINA_FALSE);
	evas_object_show(back_btn);

	//create preview genlist
	//para->genlist = create_preview_genlist(para);
	//elm_object_style_set(para->genlist, "dialogue");
	//evas_object_show(para->genlist);

	//naviframe_item = elm_naviframe_item_push(para->naviframe, APP_LIST, back_btn, NULL, NULL, NULL);
	naviframe_item = elm_naviframe_item_push(para->naviframe, NULL, back_btn, NULL, NULL, NULL);

	if(naviframe_item == NULL)
    { 
        printf( "create_app_list_view, push failed\n");
	    return;
	}
	
	printf( "create other what's_view buttons.\n");
	//Add three buttons
	para->whatsnew_button = elm_button_add(para->naviframe);
	elm_object_style_set(para->whatsnew_button, "naviframe/toolbar/default");
	elm_object_text_set(para->whatsnew_button, "What's New");
	para->eContentType = WHATSNEW_TYPE;
	evas_object_smart_callback_add(para->whatsnew_button, "clicked",(Evas_Smart_Cb)_create_whats_new_gengrid, (void*) para);
	elm_object_disabled_set(para->whatsnew_button, EINA_FALSE);
	// set button as content of naviframe
	elm_object_item_part_content_set(naviframe_item, "toolbar_button1", para->whatsnew_button);
	printf( "exit create_app_list_view1111\n");

	//add for "elm.swallow.title"
	tvshow_bt = elm_button_add(para->naviframe);
	elm_object_style_set(tvshow_bt, "base/text_only/styletv");
	elm_object_text_set(tvshow_bt, "TV Shows");
	//evas_object_smart_callback_add(para->whatsnew_button, "clicked",(Evas_Smart_Cb)_create_whats_new_gengrid, (void*) para);
	elm_object_disabled_set(tvshow_bt, EINA_FALSE);
	evas_object_color_set(tvshow_bt, BACKGROUND_RED + 20, BACKGROUND_GREEN, BACKGROUND_BLUE + 20, 255);
	//elm_bg_file_set(tvshow_bt, "images/11_raw.jpg", NULL);
	// set button as content of naviframe
	elm_object_item_part_content_set(naviframe_item, "elm.swallow.title", tvshow_bt );
	evas_object_show(tvshow_bt);	

/*
   Evas_Object *entry = elm_entry_add(para->naviframe);     
   //Set the entry text  
   elm_entry_entry_set(entry, "TV Shows" );
   //Give some hints to entry object. This info. can be affected to entry size when it is contained to naviframe
   evas_object_size_hint_weight_set(entry, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(entry, EVAS_HINT_FILL, EVAS_HINT_FILL);
   // set button as content of naviframe
   elm_object_item_part_content_set(naviframe_item, "elm.swallow.title", entry);
   evas_object_show(entry);
*/
   bghead = elm_bg_add(para->naviframe);
	evas_object_size_hint_weight_set(bghead, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	//set bg color purple
	elm_bg_color_set(bghead, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE);
	// set button as content of naviframe
	elm_object_item_part_content_set(naviframe_item, "elm.swallow.title2", bghead);
	evas_object_show(bghead);	
	
	/*

	para->whatsnew_button = elm_button_add(para->naviframe);
	elm_object_style_set(para->whatsnew_button, "naviframe/toolbar/default");
	elm_object_text_set(para->whatsnew_button, "Most Popular");
	para->eContentType = MOSTPOPULAR_TYPE;
	evas_object_smart_callback_add(para->whatsnew_button, "clicked",(Evas_Smart_Cb)_create_most_populer_gengrid, (void*) para);
	elm_object_disabled_set(para->whatsnew_button, EINA_FALSE);
	// set button as content of naviframe
	elm_object_item_part_content_set(naviframe_item, "toolbar_button2", para->whatsnew_button);
	printf( "exit create_app_list_view2222\n");

	//Why the third button not showing??
	para->genres_button = elm_button_add(para->naviframe);
	elm_object_style_set(para->genres_button, "naviframe/toolbar/default");
	elm_object_text_set(para->genres_button, "Genres");
	para->eContentType = GENRES_TYPE;
	evas_object_smart_callback_add(para->genres_button, "clicked",(Evas_Smart_Cb)_create_geners_gengrid, (void*) para);
	elm_object_disabled_set(para->genres_button, EINA_FALSE);
	// set button as content of naviframe
	elm_object_item_part_content_set(naviframe_item, "toolbar_button3", para->genres_button);
	printf( "exit create_app_list_view3333\n");	
*/

}

Evas_Object *create_win(const char *name)
{
	Evas_Object *eo = NULL;
	int w, h;

	eo = elm_win_add(NULL, name, ELM_WIN_BASIC);

	elm_win_rotation_set(eo, 270);

	elm_win_title_set(eo, name);
	elm_win_borderless_set(eo, EINA_TRUE);
	elm_win_alpha_set(eo, EINA_TRUE);
	evas_object_smart_callback_add(eo, "delete,request", _quit_cb, NULL);
	ecore_x_window_size_get(ecore_x_window_root_first_get(), &w, &h);
	evas_object_resize(eo, w, h);
	evas_object_raise(eo);

	return eo;
}

static Evas_Object *create_bgimg(Evas_Object *parent, char *style)
{
	Evas_Object *bg = NULL;
	printf("_create_bgimg\n");
	bg = elm_bg_add(parent);

	evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_object_style_set(bg, style);
	elm_win_resize_object_add(parent, bg);

	//set bg color purple
	elm_bg_color_set(bg, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE);
	evas_object_show(bg);
	return bg;
}


/**
* This function will be called when enter the app .
* @param data , the map app common data .
* @ingroup Map app
**/
static int __app_create(void *data)
{
	demo_data_s *para =(demo_data_s *)data;
	/*create win*/
	para->win = create_win(PACKAGE);
	/*create base layout*/
	para->base_layout = create_base_layout(para->win);
	//create background
	para->background = create_bgimg(para->win, "group_list");
	elm_object_part_content_set(para->base_layout, "elm.swallow.bg", para->background);
	// show indicator 
	elm_win_indicator_mode_set(para->win, ELM_WIN_INDICATOR_SHOW);
	//create navigation bar
	para->naviframe = elm_naviframe_add(para->base_layout);
	//DAEMON_RETURN_VAL_IF_FAILED(para->naviframe, -1);
	elm_object_part_content_set(para->base_layout, "elm.swallow.content", para->naviframe);
	evas_object_show(para->naviframe);
	//evas_object_show(para->win);

	create_app_list_view(para);

	evas_object_show(para->win);
	
	return 0;
}


/**
 * This function will be called when exit the app .
 * @param data , the map app common data .
 * @ingroup Map app
 */
static int __app_terminate(void *data)
{
	/* do nothing */
	return 0;
}

/**
 * This function will be called when the app pause .
 * @param data , the map app common data .
 * @ingroup Map app
 */
static int __app_pause(void *user_data)
{
	return 0;
}

/**
 * This function will be called when the app resume .
 * @param data , the map app common data .
 * @ingroup Map app
 */
static int __app_resume(void *user_data)
{
	return 0;
}

static int __app_reset(bundle *b, void *data)
{
	demo_data_s *md = (demo_data_s *)data;

	if (md->win) {
		elm_win_activate(md->win);
	}
	return 0;
}

/*
main function entry pointer
*/
int main(int argc, char *argv[])
{	
	demo_data_s *ugd = NULL;
	
	DAEMON_NEW(ugd, 1, demo_data_s);
    gl_ugd = ugd;
	
	struct appcore_ops ops = 
	{
		.create = __app_create,
		.terminate = __app_terminate,
		.pause = __app_pause,
		.resume = __app_resume,
		.reset = __app_reset,
	};

	ops.data = ugd;

	appcore_set_i18n(PACKAGE, LOCALE_DIR);

	return appcore_efl_main(PACKAGE, &argc, &argv, &ops);
}
