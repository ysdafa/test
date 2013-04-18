/**
 * Init noa application
 *
 * @param[in]  data      data used in this function
 *
 * @return     FAILED if init failed
 *             SUCCESS if init successfully
 */
#include "noamain.h"
#include "clock_fwk_util.h"

static Evas_Object *create_base_layout(Evas_Object *parent)
{
	Evas_Object *layout = NULL;

	layout = elm_layout_add(parent);

	elm_layout_theme_set(layout, "layout", "application", "default");
	evas_object_size_hint_weight_set(layout, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(layout, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_win_resize_object_add(parent, layout);
	evas_object_show(layout);

	return layout;
}


int noa_init(void *data)
{
	CLK_FUN_BEG();
	demo_data_s *para =(demo_data_s *)data;

	/*create win*/
	para->win = create_win(PACKAGE);
	
	/*create base layout*/
	para->base_layout = create_base_layout(para->win);
	
	/*create background*/
	para->background = create_bg(para->win);
	elm_object_part_content_set(para->base_layout, "elm.swallow.bg", para->background);
	
	/* show indicator */
	elm_win_indicator_mode_set(para->win, ELM_WIN_INDICATOR_SHOW);
	
	/*create navigation bar*/
	para->naviframe = elm_naviframe_add(para->base_layout);
	
	//DAEMON_RETURN_VAL_IF_FAILED(para->naviframe, -1);
	elm_object_part_content_set(para->base_layout, "elm.swallow.content", para->naviframe);
	evas_object_show(para->naviframe);
	
	evas_object_show(para->win);
	CLK_FUN_END();
	return SUCCESS;
}
