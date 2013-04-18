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

#include "clock_fwk_effect.h"
#include "clock_fwk_util.h"
//
void clk_transit_effect_image_animation_add(Evas_Object *obj,
					    Eina_List *image_path,
					    Elm_Transit_Del_Cb effect_comp,
					    void *data)
{
	Elm_Transit_Effect *effect = NULL;
	Elm_Transit *transit = elm_transit_add();
	elm_transit_object_add(transit, obj);
	effect = elm_transit_effect_image_animation_add(transit, image_path);
	if (NOT_NULL(effect_comp)) {
		elm_transit_del_cb_set(transit, effect_comp, data);
	}
	elm_transit_duration_set(transit, 1.0);
	elm_transit_auto_reverse_set(transit, EINA_TRUE);
	elm_transit_go(transit);
}
