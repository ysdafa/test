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

#ifndef __CLK_FWK_EFFECT_H__
#define __CLK_FWK_EFFECT_H__

#include <Elementary.h>
#include "clock_fwk_define.h"

void clk_transit_effect_image_animation_add(Evas_Object *obj,
					    Eina_List *image_path,
					    Elm_Transit_Del_Cb effect_comp,
					    void *data);

#endif				//__CLK_FWK_EFFECT_H__
