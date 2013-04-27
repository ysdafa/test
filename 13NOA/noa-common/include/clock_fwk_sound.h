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
#ifndef __CLK_FWK_SOUND_H__
#define __CLK_FWK_SOUND_H__

#include <mm_sound_private.h>
#include <mm_message.h>
#include <Ecore.h>
#include <glib.h>
#include "clock_fwk_define.h"
/**********************************************************************
******************define, struct ,typedef, union, enum, global val *************************************
***********************************************************************/

//******************define*************************************
#define TOUCH_VOLUME_SOUND "/usr/share/keysound/SVI/Touch.wav"
#define MAX_RINGING_TIME                            (60)	/* sec */
#define MAX_VIBE_TIME                               (6)	/* sec */
#define RAISING_VOLUME_INTERVAL                     (2)	/* sec */
#define MAX_TONE_NAME                               (128)

#define CLK_SOUND_VOLUME_TYPE (VOLUME_TYPE_ALARM)
#define CLK_SOUND_MM_SOUND_VOLUME_TYPE (MM_SOUND_VOLUME_TYPE_ALARM)
#define CLK_SOUND_MULTI_RATE (1)
//******************enum*************************************
typedef enum {
	CLK_SOUND_TYPE_OFF = -1,
	CLK_SOUND_TYPE_MELODY = 0,
	CLK_SOUND_TYPE_MAX,
} clk_sound_type_t;
//******************typedef*************************************
typedef void (*Callback_end_fun) (void *data);
typedef struct _clk_sound_mgr_t clk_sound_mgr_t;
/**********************************************************************
******************global function rel *************************************
***********************************************************************/
#ifdef ALARMAPP_FEATURE_KLOCKTEST_NOTUSED_FUNTION
volume_type_t clk_sound_get_volume_type(void);
#endif
int clk_sound_get_volume_step(volume_type_t type);
#ifdef ALARMAPP_FEATURE_KLOCKTEST_NOTUSED_FUNTION
int clk_sound_get_volume_value(volume_type_t type);
#endif
int clk_sound_set_volume_value(volume_type_t type, unsigned int value);

int clk_play_keysound(int volume_value);

clk_sound_mgr_t *clk_create_sound_mgr(clk_sound_type_t type,
				      const char *pFile,
				      int volume_value,
				      Eina_Bool bPlayAg,
				      MMMessageCallback cb,
				      Callback_end_fun end_fun,
				      void *end_fun_data, int time_sound);
int clk_delete_sound_mgr(clk_sound_mgr_t * pMgr);
void clk_free_mm_player();

#endif /**__CLK_FWK_SOUND_H__*/
