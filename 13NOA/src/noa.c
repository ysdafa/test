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

#include "noadetail.h"
#include "noamain.h"
#include "gengrid.h"
#include "clock_fwk_util.h"

/* Global variables */
static Elm_Genlist_Item_Class itc_newview, itc, itc2, nfc_itc, video_itc;
static Elm_Gengrid_Item_Class *photo_gic = NULL;
static Testitem ti[IMAGE_MAX*25];

static unsigned int REFREASH_FRAME = 1;
static unsigned int NFC_INSTANCE = 5;
bool WIFI_STATE = false;
int flag_network = 0;

demo_data_s *gl_ugd = NULL;

char videoNameList[APP_LIST_MAX_COUNT][50] = {
	"Video1", 	"Vdieo2", 	"Video3", 	"Video4", 	"Vdieo5",
	"Video6", 	"Video7",	"Vdieo8", 	"Video9",	"Video10",
	"Vdieo11",	"Video12",	"Video13",	"Vdieo14",	"Video15",
	"Video16",	"Vdieo17",	"Video18",	"Vdieo19",	"Video20"
};

char appNameList[APP_LIST_MAX_COUNT][50] = {{0}};

char appNameCancelList[APP_CANCEL_LIST_COUNT][50] =
{
	"Nomal style",
	"extraordinary style",
	"larger style"
};
/*
static const char entry_input_text[] = {
	"English is a application as a server, used to split screen display. "
	"User can select the application from the running application list. "
	"Its interface will be split screen display in two mobile phones. "
	"Then open the English application, the screen will be display in the client."
};
*/
static char *slider_itemlist[] = {
	"text1",
	"text2",
	"WIFI-DIRECTER State",
	"text3",
	NULL
};

/* declare function*/
void create_app_list_view(void *data);
static void _create_whats_new_gengrid(void *data);
static void _create_most_populer_gengrid(void *data);
static void _create_geners_gengrid(void *data);
void exit_process(void *data);

static void _set_back_btn_cb(void *data, Evas_Object *obj, void *event_info)
{
	/* do nothing */
}


static char *_gl_display_text_get(void *data, Evas_Object *obj, const char *part)
{
	int  index = (int)data;
	return strdup("Movies and TVShows");
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

	return sep;
}

static void _gl_text_list_sel(void *data, Evas_Object *obj, void *event_num)
{
	printf("come in _gl_text_list_sel\n");
	/*demo_data_s *ugd = (demo_data_s *) data;*/
	
	int index = (int)data;
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

void _create_whats_new_gengrid(void *data)
{	
	printf(	 "Entry _create_whats_new_gengrid\n");
	demo_data_s *para =(demo_data_s *)data;
	if(para == NULL)
	{
	    printf(  "Incorrect parameter(NULL)");
        return;
	}
	gengrid_create_view( data, "noa_default_gridtext");
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
	gengrid_groupindex_cb( data, NULL, NULL );

	printf(	 "Exit _create_geners_gengrid\n");		
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
	Evas_Object *genlist = NULL, *layout = NULL;
	int i = 0;
	int j = 0;
	bool flag = true;

	itc_newview.item_style = "dialogue/1text";
	itc_newview.func.text_get = _gl_display_text_get;
	itc_newview.func.content_get = NULL;
	itc_newview.func.state_get = NULL;
	itc_newview.func.del = NULL;

	//demo_data_s *para = (demo_data_s *) data;
	//genlist = elm_genlist_add(para->naviframe);
	
	layout = (Evas_Object *) data;
	genlist = elm_genlist_add(layout);

	/* add the video list */
/*	
	Elm_Object_Item* ret = elm_genlist_item_append(	genlist, 
														&itc_newview, 
														(void *)APP_LIST_MAX_COUNT, 
														NULL, 
														ELM_GENLIST_ITEM_NONE, 
														(Evas_Smart_Cb)_create_video_list, 
														(void *)para );
*/
	Elm_Object_Item* ret = elm_genlist_item_append(	genlist, 
														&itc_newview, 
														(void *)APP_LIST_MAX_COUNT, 
														NULL, 
														ELM_GENLIST_ITEM_NONE, 
														(Evas_Smart_Cb)_create_video_list, 
														(void *)layout );

	elm_genlist_mode_set( genlist, ELM_LIST_LIMIT );
	return genlist;
}

/* icon fetching callback */
static Evas_Object *
_photo_grid_content_get(void        *data,
               Evas_Object *obj,
               const char  *part)
{
	const Testitem *it = data;

	if (!strcmp(part, "elm.swallow.icon"))
	{
		Evas_Object *icon = elm_image_add(obj);
		char buf[PATH_MAX];

	    snprintf(buf, sizeof(buf), "%s",it->path);
		//printf("_photo_grid_content_get - %s\n",buf);

		elm_image_file_set(icon, buf, NULL);
		elm_image_aspect_fixed_set(icon, EINA_TRUE);
		evas_object_show(icon);
		return icon;
	}
	else if (!strcmp(part, "elm.swallow.end"))
	{
		return NULL;
	}
}

void create_app_list_view(void *data)
{
	demo_data_s *para =(demo_data_s *)data;
	Evas_Object *back_btn =NULL, *bghead = NULL, *tvshow_bt = NULL, *tvshow_layout = NULL;
	Elm_Object_Item *naviframe_item = NULL;

	/*Error prevent*/
	if(para == NULL)
	{
	    printf(  "Incorrect parameter(NULL)");
        return;
	}

	//add tv show layout
	tvshow_layout = create_layout(para->naviframe, "movies_layout" );
	if( NULL == tvshow_layout )
	{
		printf( "debug: create layout failed, delete objects and return directly." );
		exit_process( para );
		return;
	}

	//create gengrid
	printf( "create what's_view, most popular, geners buttons.\n");

	Evas_Object *layout_obj = elm_layout_edje_get(tvshow_layout);
	Evas_Object* whatsnew_btn = edje_object_part_object_get (layout_obj, "toolbar_whatsn"); //??edc??part object
	evas_object_event_callback_add(whatsnew_btn, EVAS_CALLBACK_MOUSE_DOWN, _create_whats_new_gengrid, para);

	Evas_Object* mostp_btn = edje_object_part_object_get (layout_obj, "toolbar_mostp"); 
	//evas_object_repeat_events_set  ( mostp_btn,EINA_FALSE );
	evas_object_event_callback_add(mostp_btn, EVAS_CALLBACK_MOUSE_DOWN, _create_most_populer_gengrid, para);
	
	Evas_Object* geners_btn = edje_object_part_object_get (layout_obj, "toolbar_geners"); //??edc??part object
	//evas_object_event_callback_add(geners_btn, EVAS_CALLBACK_MOUSE_DOWN, _create_geners_gengrid, para);

/*
	//Add three buttons
	para->whatsnew_button = elm_button_add(tvshow_layout);
	// "naviframe/toolbar/default"
	elm_object_style_set(para->whatsnew_button, "create_view/style1");
	elm_object_text_set(para->whatsnew_button, "What's New");
	para->eContentType = WHATSNEW_TYPE;
	evas_object_smart_callback_add(para->whatsnew_button, "clicked",(Evas_Smart_Cb)_create_whats_new_gengrid, (void*) para);
	elm_object_disabled_set(para->whatsnew_button, EINA_FALSE);
	evas_object_color_set(para->whatsnew_button, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	// set button as toolbar_button1 of layout
	elm_object_part_content_set(tvshow_layout, "toolbar_button1", para->whatsnew_button);
	printf( "exit create_app_list_view1111\n");

	para->mostpopular_button = elm_button_add(tvshow_layout);
	elm_object_style_set(para->mostpopular_button, "create_view/style1");
	elm_object_text_set(para->mostpopular_button, "Most Popular");
	para->eContentType = MOSTPOPULAR_TYPE;
	evas_object_smart_callback_add(para->mostpopular_button, "clicked",(Evas_Smart_Cb)_create_most_populer_gengrid, (void*) para);
	elm_object_disabled_set(para->mostpopular_button, EINA_FALSE);
	evas_object_color_set(para->mostpopular_button, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	// set button as toolbar_button2 of layout
	elm_object_part_content_set(tvshow_layout, "toolbar_button2", para->mostpopular_button);
	printf( "exit create_app_list_view2222\n");

	//third button is defined in our own edc
	para->genres_button = elm_button_add(tvshow_layout);
	elm_object_style_set(para->genres_button, "create_view/style1");
	elm_object_text_set(para->genres_button, "Genres");
	para->eContentType = GENRES_TYPE;
	evas_object_smart_callback_add(para->genres_button, "clicked",(Evas_Smart_Cb)_create_geners_gengrid, (void*) para);
	elm_object_disabled_set(para->genres_button, EINA_FALSE);
	evas_object_color_set(para->genres_button, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	// set button as toolbar_button3 of layout
	elm_object_part_content_set(tvshow_layout, "toolbar_button3", para->genres_button);
	printf( "exit create_app_list_view3333\n");	
*/

	Evas_Object *photo_grid = elm_gengrid_add(tvshow_layout);
	evas_object_size_hint_weight_set(photo_grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(photo_grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_gengrid_scroller_policy_set(photo_grid,ELM_SCROLLER_POLICY_OFF,ELM_SCROLLER_POLICY_OFF);
	
	double scale = elm_config_scale_get();
	double w = (int)(MOVIE_ITEM_WIDE * scale); //177 as per UX ver 1.7.
	double h = (int)(MOVIE_ITEM_HEIGHT* scale); //64 for textas per UX ver 1.7.
	elm_gengrid_item_size_set(photo_grid, w, h);
	elm_gengrid_align_set(photo_grid, 0.0, 0.0);
	elm_gengrid_horizontal_set(photo_grid, EINA_TRUE);
	elm_scroller_bounce_set(photo_grid, EINA_FALSE, EINA_TRUE);
	elm_gengrid_multi_select_set(photo_grid, EINA_TRUE);
	
	elm_object_part_content_set(tvshow_layout, "whatsn_gengrid", photo_grid);

	//naviframe_item = elm_naviframe_item_push(para->naviframe, NULL, back_btn, NULL, para->genlist, "empty");
	//set auto push to false,to avoid creating default prev_btn button
	elm_naviframe_prev_btn_auto_pushed_set( para->naviframe, EINA_FALSE );
	naviframe_item = elm_naviframe_item_push(para->naviframe, NULL, NULL, NULL, tvshow_layout, "empty");
	elm_naviframe_item_title_visible_set(naviframe_item, EINA_FALSE);

	if(naviframe_item == NULL)
	{
		printf( "create_app_list_view, push failed\n");
		return;
	}
	
	if(!photo_gic)
	{
		photo_gic = elm_gengrid_item_class_new();
		photo_gic->item_style = "default_grid";
		photo_gic->func.text_get = NULL;
		photo_gic->func.content_get = _photo_grid_content_get;
		photo_gic->func.state_get = NULL;
		photo_gic->func.del = NULL;
	}
	char *buf[100];
	int i, j, n;
	for (i = 0; i < IMAGE_MAX; i++) {
		n = i;
		snprintf(buf, sizeof(buf), "%s/%d.jpg", ICON_DIR, i+1);
		ti[n].index = i;
		ti[n].path = eina_stringshare_add(buf);
		//ti[n].item = elm_gengrid_item_append(gengrid, gic, &(ti[n]), _item_selected, &(ti[i]));
		ti[n].item = elm_gengrid_item_append(photo_grid, photo_gic, &(ti[n]), NULL, NULL);
		ti[n].checked = EINA_FALSE;
	}
	evas_object_show(photo_grid);	

	printf( "exit create_app_list_view \n"); 
}

void create_app_list_view_2(void *data)
{
	demo_data_s *para =(demo_data_s *)data;
	Evas_Object *back_btn =NULL, *bghead = NULL, *tvshow_bt = NULL, *tvshow_layout = NULL;
	Elm_Object_Item *naviframe_item = NULL;

	/*Error prevent*/
	if(para == NULL)
	{
	    printf(  "Incorrect parameter(NULL)");
        return;
	}

	printf("edj file: %s\n", VIEW_BUTTON_EDJ);
	printf("edj file: %s\n", VIEW_NAVIFRAME_EDJ);
	elm_theme_extension_add(NULL, VIEW_BUTTON_EDJ );
	elm_theme_extension_add(NULL, VIEW_NAVIFRAME_EDJ );

	//add tv show layout
	tvshow_layout = create_layout(para->naviframe, "tvshows_layout" );
	if( NULL == tvshow_layout )
	{
		printf( "debug: create layout failed, delete objects and return directly." );
		exit_process( para );
		return;
	}
	//create preview genlist
	//para->genlist = create_preview_genlist(para);
	para->genlist = create_preview_genlist(tvshow_layout);
	elm_object_style_set(para->genlist, "dialogue");
	evas_object_show(para->genlist);
	// set gengrid as elm.swallow.content of layout
	//elm_object_part_content_set(tvshow_layout, "elm.swallow.content", para->genlist);

	//create the back button
	back_btn = elm_button_add(tvshow_layout);
	elm_object_style_set(back_btn, "naviframe/back_btn/default");
	evas_object_smart_callback_add(back_btn, "clicked", (void *)exit_process, para);
	elm_object_focus_allow_set(back_btn,EINA_FALSE);
	evas_object_color_set(back_btn, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	evas_object_show(back_btn);
	// set gengrid as elm.swallow.content of layout
	elm_object_part_content_set(tvshow_layout, "elm.swallow.prev_btn", back_btn);
	
	//add for "elm.head"
	tvshow_bt = elm_button_add(tvshow_layout);
	elm_object_style_set(tvshow_bt, "naviframe/toolbar/default");
	elm_object_text_set(tvshow_bt, "TV Shows");
	elm_object_disabled_set(tvshow_bt, EINA_FALSE);
	evas_object_color_set(tvshow_bt, HEAD_BACKGROUND_RED, HEAD_BACKGROUND_GREEN, HEAD_BACKGROUND_BLUE, 255);
	evas_object_show(tvshow_bt);
	// set button as of elm.head.left layout
	elm_object_part_content_set(tvshow_layout, "elm.head.left", tvshow_bt );

	bghead = elm_bg_add(tvshow_layout);
	evas_object_size_hint_weight_set(bghead, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	//set bg color purple
	elm_bg_color_set(bghead, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE);
	// set button as elm.head.left of layout
	elm_object_part_content_set(tvshow_layout, "elm.head.right", bghead);
	evas_object_show(bghead);	

	printf( "create other what's_view buttons.\n");
	//Add three buttons
	para->whatsnew_button = elm_button_add(tvshow_layout);
	// "naviframe/toolbar/default"
	elm_object_style_set(para->whatsnew_button, "create_view/style1");
	elm_object_text_set(para->whatsnew_button, "What's New");
	para->eContentType = WHATSNEW_TYPE;
	evas_object_smart_callback_add(para->whatsnew_button, "clicked",(Evas_Smart_Cb)_create_whats_new_gengrid, (void*) para);
	elm_object_disabled_set(para->whatsnew_button, EINA_FALSE);
	evas_object_color_set(para->whatsnew_button, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	// set button as toolbar_button1 of layout
	elm_object_part_content_set(tvshow_layout, "toolbar_button1", para->whatsnew_button);
	printf( "exit create_app_list_view1111\n");

	para->mostpopular_button = elm_button_add(tvshow_layout);
	elm_object_style_set(para->mostpopular_button, "create_view/style1");
	elm_object_text_set(para->mostpopular_button, "Most Popular");
	para->eContentType = MOSTPOPULAR_TYPE;
	evas_object_smart_callback_add(para->mostpopular_button, "clicked",(Evas_Smart_Cb)_create_most_populer_gengrid, (void*) para);
	elm_object_disabled_set(para->mostpopular_button, EINA_FALSE);
	evas_object_color_set(para->mostpopular_button, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	// set button as toolbar_button2 of layout
	elm_object_part_content_set(tvshow_layout, "toolbar_button2", para->mostpopular_button);
	printf( "exit create_app_list_view2222\n");

	//third button is defined in our own edc
	para->genres_button = elm_button_add(tvshow_layout);
	elm_object_style_set(para->genres_button, "create_view/style1");
	elm_object_text_set(para->genres_button, "Genres");
	para->eContentType = GENRES_TYPE;
	evas_object_smart_callback_add(para->genres_button, "clicked",(Evas_Smart_Cb)_create_geners_gengrid, (void*) para);
	elm_object_disabled_set(para->genres_button, EINA_FALSE);
	evas_object_color_set(para->genres_button, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE, 255);
	// set button as toolbar_button3 of layout
	elm_object_part_content_set(tvshow_layout, "toolbar_button3", para->genres_button);
	printf( "exit create_app_list_view3333\n");	

	//naviframe_item = elm_naviframe_item_push(para->naviframe, NULL, back_btn, NULL, para->genlist, "empty");
	//set auto push to false,to avoid creating default prev_btn button
	elm_naviframe_prev_btn_auto_pushed_set( para->naviframe, EINA_FALSE );
	naviframe_item = elm_naviframe_item_push(para->naviframe, NULL, NULL, NULL, tvshow_layout, "empty");
	if(naviframe_item == NULL)
	{
		printf( "create_app_list_view, push failed\n");
		return;
	}
	

	printf( "exit create_app_list_view \n"); 
}


/**
* This function will be called when enter the app .
* @param data , the map app common data .
* @ingroup Map app
**/
static int __app_create(void *data)
{
	CLK_FUN_BEG();
	retv_if(NULL == data, -1);
	int ret = 0;

	demo_data_s *para =(demo_data_s *)data;

	/* init noa application  */
	ret = noa_init(data);

	/*set the background color as needed*/
	elm_bg_color_set(para->background, BACKGROUND_RED, BACKGROUND_GREEN, BACKGROUND_BLUE);
	
	create_app_list_view(para);

	CLK_FUN_END();
	return ret;
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

/**
 * app initialize/finalize finish 
 * Main entry point
 */
int main(int argc, char *argv[])
{
	CLK_FUN_BEG();
	CLK_INFO("\n\t<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>> : argc = %d\n",
		 argc);
	int i = 0;
	for (i = 0; i < argc; i++) {
		CLK_INFO( "\n\t<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>> : argv[%d] = %s\n", i, argv[i] );
	}

	demo_data_s *ugd = NULL;

	DAEMON_NEW(ugd, 1, demo_data_s);
	gl_ugd = ugd;

	struct appcore_ops ops =
	{
		.data 		= ugd,
		.create 	= __app_create,
		.terminate 	= __app_terminate,
		.pause 		= __app_pause,
		.resume 	= __app_resume,
		.reset 		= __app_reset,
	};

	appcore_set_i18n(PACKAGE, LOCALE_DIR);

	CLK_FUN_END();
	return appcore_efl_main(PACKAGE, &argc, &argv, &ops);
}
