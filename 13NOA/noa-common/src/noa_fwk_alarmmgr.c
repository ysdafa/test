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

#include "clock_fwk_alarmmgr.h"
#include "clock_fwk_util.h"

/**********************************************************************
******************Global function ref*************************************
***********************************************************************/

/**
* send
* This function is  used to create mgr
* @param           data[in]         pointer to AData
* @return          when success, return EINA_TRUE or EINA_FALSE if error
* @exception
*/
int clk_fwk_alarmmgr_create(AData * alarm)
{
	int ret = SUCCESS;
	int nErr = SUCCESS;
	alarm_entry_t *alarm_entry = NULL;
	alarm_date_t alarm_data;
	CLK_FUN_BEG();
	CLK_RETVM_IF(!alarm, FAILED, "para error");
	/*create alarm */
	alarm_entry = alarmmgr_create_alarm();
	CLK_RETVM_IF(!alarm_entry, FAILED, "alarmmgr_create_alarm error");
	/*set repeat */
	int repeat_value = 0;
	alarm_repeat_mode_t repeat_mode = 0;
	if (alarm->repeat_once) {
		repeat_mode = ALARM_REPEAT_MODE_ONCE;
	} else if (alarm->repeat_weekly) {
		repeat_mode = ALARM_REPEAT_MODE_WEEKLY;
	}
	repeat_value = alarm->repeat_weekly;
	nErr = alarmmgr_set_repeat_mode(alarm_entry, repeat_mode, repeat_value);
	CLK_RETVM_IF(nErr != SUCCESS, FAILED, "alarmmgr_set_repeat_mode error");
	/*set time_data */
	struct tm pt;
	localtime_r(&alarm->atime, &pt);
//    CLK_RETVM_IF(!pt, FAILED, "localtime NULL");
	if (IS_EQUAL(alarm->author, ALARM_DB_AUTHOR_TIMER)) {
		SET_TIME_DATA_T(&alarm_data, pt.tm_year + 1900,
				pt.tm_mon + 1, pt.tm_mday, pt.tm_hour,
				pt.tm_min, pt.tm_sec);
	} else if (IS_EQUAL(repeat_mode, ALARM_REPEAT_MODE_ONCE)) {
		SET_TIME_DATA_T(&alarm_data, pt.tm_year + 1900, pt.tm_mon + 1,
				pt.tm_mday, pt.tm_hour, pt.tm_min, 0);
		if (difftime((double)alarm->atime, (double)time(NULL)) <= 0.0) {
			alarm->atime += 7 * 24 * 3600;
			localtime_r(&alarm->atime, &pt);
			SET_TIME_DATA_T(&alarm_data, pt.tm_year + 1900,
					pt.tm_mon + 1, pt.tm_mday,
					pt.tm_hour, pt.tm_min, 0);
		}
	} else {
		SET_TIME_DATA_T(&alarm_data, 0, 0, 0, pt.tm_hour, pt.tm_min, 0);
	}

	nErr |= alarmmgr_set_time(alarm_entry, alarm_data);
	CLK_RETVM_IF(nErr != SUCCESS, FAILED, "alarmmgr_set_time error");
	/*set type   */
	nErr = alarmmgr_set_type(alarm_entry, ALARM_TYPE_DEFAULT);
	CLK_RETVM_IF(nErr != SUCCESS, FAILED, "alarmmgr_set_type error");
	/*create new    */
	int alarm_mgr_id = 0;
	nErr =
	    alarmmgr_add_alarm_with_localtime(alarm_entry, ALARMRING_PKGNAME,
					      &alarm_mgr_id);
	CLK_RETVM_IF(SUCCESS != nErr, FAILED,
		     "alarmmgr_add_alarm_with_localtime error,nErr=%d", nErr);

	alarm->alarm_mgr_id = alarm_mgr_id;
 End:
	if (alarm_entry) {
		alarmmgr_free_alarm(alarm_entry);
	}
	CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to remove mgr
* @param           data[in]         pointer to AData
* @return          when success, return EINA_TRUE or EINA_FALSE if error
* @exception
*/
int clk_fwk_alarmmgr_remove(AData * alarm)
{
	int ret = SUCCESS;
	ret = alarmmgr_remove_alarm(alarm->alarm_mgr_id);
	if (ret != SUCCESS) {
		CLK_ERR("Failed to remove alarm[%d], error code: %d\n",
			alarm->alarm_mgr_id, ret);
	}
	alarm->alarm_mgr_id = -1;
	return ret;
}

/**
* send
* This function is  used to update mgr
* @param           data[in]         pointer to AData
* @return          when success, return EINA_TRUE or EINA_FALSE if error
* @exception
*/
int clk_fwk_alarmmgr_update(AData * alarm)
{
	int ret = SUCCESS;
	ret = clk_fwk_alarmmgr_remove(alarm);
	ret |= clk_fwk_alarmmgr_create(alarm);
	return ret;
}
