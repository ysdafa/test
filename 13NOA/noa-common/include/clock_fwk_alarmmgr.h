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
#ifndef __CLK_FWK_ALARMMGR_H__
#define __CLK_FWK_ALARMMGR_H__

#include <alarm-engine.h>
#include <alarm.h>
#include "clock_fwk_define.h"

int clk_fwk_alarmmgr_remove(AData *alarm);
int clk_fwk_alarmmgr_create(AData *alarm);
int clk_fwk_alarmmgr_update(AData *alarm);

#endif				//__CLK_FWK_ALARMMGR_H__
