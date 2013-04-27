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

#include "clock_fwk_sound.h"
#include <mm_player.h>
#include <vconf.h>
#include <vconf-keys.h>
/**********************************************************************
******************define, struct ,typedef, union, enum, global val *************************************
***********************************************************************/
#define MAGIC_VALUE 89738
#define MAGIC_SET(p) do {p->_magic = MAGIC_VALUE;} while (0);
#define MAGIC_CHECK_ERROR(p) p->_magic != MAGIC_VALUE

struct _clk_sound_mgr_t {
	int _magic;
	clk_sound_type_t create_type;	//control type
	MMHandleType pmm_player;	//for playing sound
	char file[MAX_TONE_NAME];	//file name
	MMMessageCallback msg_cb;	//msg callback fun
	Ecore_Timer *control_timer;	//set timer for stop
	int volume_value;	//volume init value
	int increased_volume_value;	//for increased volume
	volume_type_t volume_type;	//volume type
	int volume_step;	//volume step, max volume
	Eina_Bool bSoundPlayAg;	//when sound play end, receive MM_MESSAGE_END_OF_STREAM, play AG?
	Callback_end_fun end_fun;	//callback when control_timer out
	void *end_fun_data;	//end_fun data
	int time_sound;		//time for control when stop sound
//  system_audio_route_t saved_route;
};
static clk_sound_mgr_t *pMgr = NULL;

/**********************************************************************
******************Local function declear, extern function declear*************************************
***********************************************************************/
static Eina_Bool _clk_sound_timer_stop_cb(void *data);
static int _clk_sound_msg_default_cb(int message, void *data, void *user_data);
static int _clk_sound_create_player(clk_sound_mgr_t * pMgr);
static int _clk_stop_sound(clk_sound_mgr_t * pMgr);
static int _clk_sound_start_sound_mgr(clk_sound_mgr_t * pMgr);
static int _clk_play_sound(clk_sound_mgr_t * pMgr);
static int _clk_play_sound_continue(clk_sound_mgr_t * pMgr);
static int _clk_get_volume(clk_sound_mgr_t * pMgr);
/**********************************************************************
******************Local function ref*************************************
***********************************************************************/

/**
* send
* This function is  used to play sound again
* @param           pMgr[in]            pointer to clk_sound_mgr_t
* @return          when success, return SUCCESS  or FAILED if error
* @exception
*/
static int _clk_play_sound_continue(clk_sound_mgr_t * pMgr)
{
	retvm_if(!pMgr, FAILED, "pMgr null");
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	int ret = SUCCESS;
	ret = mm_player_stop(pMgr->pmm_player);
	ret |= mm_player_realize(pMgr->pmm_player);
	ret |= mm_player_start(pMgr->pmm_player);
	return ret;
}

/**
* send
* This function is  used to get volume
* @param           pMgr[in]            pointer to clk_sound_mgr_t
* @return          when success, return volume  or 0 if error
* @exception
*/
static int _clk_get_volume(clk_sound_mgr_t * pMgr)
{
	retvm_if(!pMgr, FAILED, "pMgr null");
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	switch (pMgr->create_type) {
	case CLK_SOUND_TYPE_MELODY:
		return pMgr->volume_value * CLK_SOUND_MULTI_RATE;
	default:
		return 0;
		// break;
	}
}

/**
* send
* This function is  used to set sound msg default cb
* @param           message[in]             int for message
* @param           data[in]                pointer to data
* @param           user_data[in]           pointer to user data
* @return          when success, return SUCCESS  or FAILED if error
* @exception
*/
static int _clk_sound_msg_default_cb(int message, void *data, void *user_data)
{
	retvm_if(!user_data, FAILED, "user_data null");
	clk_sound_mgr_t *pMgr = (clk_sound_mgr_t *) user_data;
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	switch (message) {
	case MM_MESSAGE_END_OF_STREAM:
		{
			/* because tone is short, so play continue */
			//maybe when on call, don't play. need some condition to protect
			if (EINA_TRUE == pMgr->bSoundPlayAg) {
				//play again
				_clk_play_sound_continue(pMgr);
			} else {
				//stop
				_clk_sound_timer_stop_cb(pMgr);
			}
		}
		break;

	default:
		break;
	}
	return SUCCESS;
}

/**
* send
* This function is  used to set timer cb
* @param           data[in]            pointer to data
* @return          return ECORE_CALLBACK_CANCEL  to stop the timer
* @exception
*/
static Eina_Bool _clk_sound_timer_stop_cb(void *data)
{
	retvm_if(!data, ECORE_CALLBACK_CANCEL, "data null");
	clk_sound_mgr_t *pMgr = (clk_sound_mgr_t *) data;
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	CLK_FUN_BEG();
	/* stop sound and vibe */
	_clk_stop_sound(pMgr);
	ECORE_TIMER_DELIF(pMgr->control_timer);
	//when end. do sth..
	if (pMgr->end_fun) {
		pMgr->end_fun(pMgr->end_fun_data);
	}
	CLK_FUN_END();
	return ECORE_CALLBACK_CANCEL;
}

/**
* send
* This function is  used to create music player
* @param           pMgr[in]            pointer to clk_sound_mgr_t
* @return          when success, return SUCCESS  or FAILED if error
* @exception
*/
static int _clk_sound_create_player(clk_sound_mgr_t * pMgr)
{
	retvm_if(!pMgr, FAILED, "pMgr null");
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	MMHandleType pmm_player = 0;
	int nErr = SUCCESS;
	int ret = SUCCESS;
	char *s_error = NULL;

	CLK_FUN_BEG();
	CLK_RETVM_IF(IS_EQUAL(NULL, pMgr), FAILED, "pMgr is null");
	if(IS_EQUAL(CLK_SOUND_TYPE_MELODY, pMgr->create_type)) {
		CLK_RETVM_IF(IS_EQUAL(NULL, pMgr->file), FAILED, "pMgr->file is null");
	}
	//I think the file name is always valid when call the function

	if (pMgr->pmm_player == 0) {
		ret = mm_player_create(&pmm_player);
		CLK_RETVM_IF(!IS_EQUAL(SUCCESS, ret), ret,
			     "mm_player_create ERROR, errorId=%d", ret);
		pMgr->pmm_player = pmm_player;
		ret = mm_player_set_attribute(pMgr->pmm_player, &s_error,
					      "sound_route",
					      MM_AUDIOROUTE_PLAYBACK_ALERT,
					      //"sound_volume_table", CLK_SOUND_MM_SOUND_VOLUME_TYPE,
					      "sound_volume_type",
					      CLK_SOUND_MM_SOUND_VOLUME_TYPE,
					      "profile_uri", pMgr->file,
					      strlen(pMgr->file), NULL);
		CLK_RETVM_IF(!IS_EQUAL(SUCCESS, ret), ret,
			     "mm_player_set_attribute error: %s", s_error);
		//ret = mm_player_realize(pMgr->pmm_player);
		CLK_RETVM_IF(!IS_EQUAL(SUCCESS, ret), ret,
			     "mm_player_realize errorId: %d", ret);
		ret =
		    mm_player_set_message_callback(pMgr->pmm_player,
						   pMgr->msg_cb, pMgr);
		CLK_RETVM_IF(!IS_EQUAL(SUCCESS, ret), ret,
			     "mm_player_set_message_callback errorId: %d", ret);
	}
	//
	clk_sound_set_volume_value(CLK_SOUND_VOLUME_TYPE, (unsigned int)
				   _clk_get_volume(pMgr));

 End:
	FREEIF(s_error);
	CLK_FUN_END();
	return ret;
}


/**
* send
* This function is  used to start music player
* @param           pMgr[in]            pointer to clk_sound_mgr_t
* @return          when success, return SUCCESS  or FAILED if error
* @exception
*/
static int _clk_sound_start_sound_mgr(clk_sound_mgr_t * pMgr)
{
	retvm_if(!pMgr, FAILED, "pMgr null");
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	switch (pMgr->create_type) {
	case CLK_SOUND_TYPE_MELODY:
		_clk_play_sound(pMgr);
		break;
	default:
		CLK_ERR("error type=%d", pMgr->create_type);
		break;
	}
	return SUCCESS;
}

/**
* send
* This function is  used to play sound
* @param           pMgr[in]            pointer to clk_sound_mgr_t
* @return          when success, return SUCCESS  or FAILED if error
* @exception
*/
static int _clk_play_sound(clk_sound_mgr_t * pMgr)
{
	retvm_if(!pMgr, FAILED, "pMgr null");
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	mm_player_realize(pMgr->pmm_player);
	return mm_player_start(pMgr->pmm_player);
}

/**
* send
* This function is  used to stop sound
* @param           pMgr[in]            pointer to clk_sound_mgr_t
* @return          when success, return SUCCESS  or FAILED if error
* @exception
*/
static int _clk_stop_sound(clk_sound_mgr_t * pMgr)
{
	retvm_if(!pMgr, FAILED, "pMgr null");
	retvm_if(MAGIC_CHECK_ERROR(pMgr), FAILED,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	retvm_if(pMgr->pmm_player <= 0, FAILED, "pMgr->pmm_player <= 0");
	int ret = SUCCESS;
	CLK_FUN_BEG();
	ret = mm_player_stop(pMgr->pmm_player);
	if(pMgr){
	ret |= mm_player_unrealize(pMgr->pmm_player);
	//ret |= mm_player_destroy(pMgr->pmm_player);
	      }
	CLK_FUN_END();

	return ret;
}

/**********************************************************************
******************Global function ref*************************************
***********************************************************************/

#ifdef ALARMAPP_FEATURE_KLOCKTEST_NOTUSED_FUNTION
/**
* send
* This function is  used to get volume type
* @param           void
* @return          when success, return volume_type_t  or FAILED if error
* @exception
*/
volume_type_t clk_sound_get_volume_type(void)
{
	int ret = 0;
	volume_type_t type = -1;

	ret = mm_sound_volume_get_current_playing_type(&type);
	//printf("[VOLUME] %s, %d, %x, %d\n", __func__, __LINE__, ret, type);
	switch (ret) {
	case MM_ERROR_NONE:
		return type;
	case MM_ERROR_SOUND_VOLUME_NO_INSTANCE:
		return VOLUME_TYPE_SYSTEM;
	default:
		CLK_ERR("ret error");
		return -1;
	}
}
#endif
/**
* send
* This function is  used to get volume step by volume type
* @param           type[in]            volume_type_t
* @return          when success, return step  or 0 if error
* @exception
*/
int clk_sound_get_volume_step(volume_type_t type)
{
	int ret = 0;
	int step = -1;
	ret = mm_sound_volume_get_step(type, &step);
	return IS_EQUAL(ret, MM_ERROR_NONE) ? (step - 1) : 0;
}

#ifdef ALARMAPP_FEATURE_KLOCKTEST_NOTUSED_FUNTION
/**
* send
* This function is  used to get volume value by volume type
* @param           type[in]            int
* @return          when success, return volume value  or 0 if error
* @exception
*/
int clk_sound_get_volume_value(volume_type_t type)
{
	int ret = 0;
	unsigned int value = 0;
	ret = mm_sound_volume_get_value(type, &value);
	return IS_EQUAL(ret, MM_ERROR_NONE) ? (value) : 0;
}
#endif
/**
* send
* This function is  used to set volume
* @param           type[in]            volume_type_t
* @param           value[in]           int value
* @return          when success, return SUCCESS  or errorId if error
* @exception
*/
int clk_sound_set_volume_value(volume_type_t type, unsigned int value)
{
	int ret = 0;
	ret = mm_sound_volume_set_value(type, value);
	return ret;
}

/**
* send
* This function is  used to play keysound
* @param           volume_value[in]            int volume value
* @return          when success, return SUCCESS  or errorId if error
* @exception
*/
int clk_play_keysound(int volume_value)
{
	volume_type_t type = CLK_SOUND_VOLUME_TYPE;
	int step = clk_sound_get_volume_step(type);
	int value = volume_value * CLK_SOUND_MULTI_RATE;
	int nErr = SUCCESS;
	if (value > step) {
		value = step;
	}
	if (value < 0) {
		value = 0;
	}
	clk_sound_set_volume_value(type, value);
	nErr = mm_sound_play_keysound(TOUCH_VOLUME_SOUND, type);
	return nErr;
}

/**
* send
* This function is  used to create sound mgr
* @param           type[in]             enum clk_sound_type_t
* @param           pFile[in]            string for tone path
* @param           volume_value[in]     init volume value
* @param           cb[in]               message callback function
* @return          when success, return clk_sound_mgr_t*  or NULL if error
* @exception
*/
clk_sound_mgr_t *clk_create_sound_mgr(clk_sound_type_t type,
				      const char *pFile,
				      int volume_value,
				      Eina_Bool bPlayAg,
				      MMMessageCallback cb,
				      Callback_end_fun end_fun,
				      void *end_fun_data, int time_sound)
{

	clk_sound_mgr_t *ret = NULL;
	int nErr = SUCCESS;
	CLK_FUN_BEG();
	if (!pMgr) {
		pMgr = CALLOC(1, clk_sound_mgr_t);
	}
	CLK_RETVM_IF(NULL_CHECK(pMgr), NULL, "malloc error");
	MAGIC_SET(pMgr);
	pMgr->create_type = type;
	if (pFile) {
		snprintf(pMgr->file, sizeof(pMgr->file), "%s", pFile);
	}
	pMgr->msg_cb = cb ? cb : _clk_sound_msg_default_cb;
	pMgr->volume_value = volume_value;
	pMgr->increased_volume_value = volume_value;
	pMgr->volume_type = CLK_SOUND_VOLUME_TYPE;
	pMgr->volume_step = clk_sound_get_volume_step(CLK_SOUND_VOLUME_TYPE);
	pMgr->bSoundPlayAg = bPlayAg;
	if (!pMgr) {
		pMgr->pmm_player = 0;
	}
	if (end_fun) {
		pMgr->end_fun = end_fun;
		pMgr->end_fun_data = end_fun_data;
	}
	if (!IS_EQUAL(pMgr->create_type, CLK_SOUND_TYPE_OFF)) {
		_clk_sound_create_player(pMgr);
		_clk_sound_start_sound_mgr(pMgr);
	}
	//set a timer for stop  music
	pMgr->control_timer = ecore_timer_add(time_sound,
					      _clk_sound_timer_stop_cb, pMgr);
	ret = pMgr;
 End:
	CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to delete sound mgr
* @param           pMgr[in]            pointer to clk_sound_mgr_t
* @return          when success, return SUCCESS  or FAILED if error
* @exception
*/
int clk_delete_sound_mgr(clk_sound_mgr_t * pMgr)
{
	retvm_if(!pMgr, SUCCESS, "pMgr null");
	retvm_if(MAGIC_CHECK_ERROR(pMgr), SUCCESS,
		 "MAGIC_CHECK_ERROR(pMgr) error");
	CLK_FUN_BEG();
	ECORE_TIMER_DELIF(pMgr->control_timer);

	_clk_stop_sound(pMgr);
	//
	// mm_sound_route_set_system_policy(pMgr->saved_route);
	//FREEIF(pMgr);
	CLK_FUN_END();
	return SUCCESS;
}

void clk_free_mm_player()
{
	retm_if(!pMgr, "pMgr null");
	CLK_FUN_BEG();
	//mm_player_unrealize(pMgr->pmm_player);
	mm_player_destroy(pMgr->pmm_player);
	pMgr->pmm_player = 0;
	FREEIF(pMgr);
	CLK_FUN_END();

}
