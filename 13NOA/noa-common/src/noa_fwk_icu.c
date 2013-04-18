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
#define __CLK_FWK_ICU_C__
#include "clock_fwk_icu.h"
#include <vconf.h>
#include <unicode/udatpg.h>
#include <unicode/ucnv.h>
#include <unistd.h>
//
CLK_DATE_FORMAT clk_fwk_icu_date_format_get()
{
	CLK_DATE_FORMAT dateStyle = CLK_DATE_FORMAT_DD_MM_YYYY;
	int value = 0;
	int ret = -1;
	ret = vconf_get_int(VCONFKEY_SETAPPL_DATE_FORMAT_INT, &value);
	if (-1 == ret) {
		value = SETTING_DATE_FORMAT_DD_MM_YYYY;
	}
	switch (value) {
	case SETTING_DATE_FORMAT_DD_MM_YYYY:
		dateStyle = CLK_DATE_FORMAT_DD_MM_YYYY;
		break;
	case SETTING_DATE_FORMAT_MM_DD_YYYY:
		dateStyle = CLK_DATE_FORMAT_MM_DD_YYYY;
		break;
	case SETTING_DATE_FORMAT_YYYY_MM_DD:
		dateStyle = CLK_DATE_FORMAT_YYYY_MM_DD;
		break;
	case SETTING_DATE_FORMAT_YYYY_DD_MM:
		dateStyle = CLK_DATE_FORMAT_YYYY_DD_MM;
		break;
	default:
		break;
	}
	return dateStyle;
}

//
CLK_TIME_FORMAT clk_fwk_icu_time_format_get()
{
	CLK_TIME_FORMAT time_format = CLK_TIME_FORMAT_12HOUR;
	int ret = 0;
	int value = 0;
	CLK_FUN_BEG();
	ret = vconf_get_int(VCONFKEY_REGIONFORMAT_TIME1224, &value);
	// if failed, set default time format
	if (-1 == ret) {
		value = VCONFKEY_TIME_FORMAT_12;
	}
	switch (value) {
	case VCONFKEY_TIME_FORMAT_12:
		time_format = CLK_TIME_FORMAT_12HOUR;
		break;
	case VCONFKEY_TIME_FORMAT_24:
		time_format = CLK_TIME_FORMAT_24HOUR;
		break;
	default:
		break;
	}
	CLK_FUN_END();
	return time_format;
}

//
int clk_fwk_icu_get_data(time_t intime, char *dstStr, int dstStr_num, char *loc,
			 char *pattern, int pattern_num, const char *timezone)
{
	int ret = SUCCESS;
	int nErr = SUCCESS;
	UDateFormat *date_fmt = NULL;
	UErrorCode status = U_ZERO_ERROR;
	const char *locale = timezone;
	UDate tmpdate;
	UChar *tmpstr = NULL;
	int32_t tmplen = 0;
	UChar bestPattern[MAX_PATTERN_LENGHT] = { 0, };
	int32_t bestPatternCapacity;
	int32_t bestPatternLength;
	UDateTimePatternGenerator *generator = NULL;

	CLK_FUN_BEG();
	CLK_RETVM_IF(!dstStr, FAILED, "str NULL");
	CLK_RETVM_IF(dstStr_num <= 0, FAILED, "dstStr_num<=0");
	CLK_RETVM_IF(!pattern, FAILED, "pattern NULL");
	CLK_RETVM_IF(pattern_num <= 0, FAILED, "pattern_num<=0");
	//
	//date = ucal_getNow();
	tmpdate = (double)1000 *intime;
	uloc_setDefault((const char *)__secure_getenv("LC_TIME"), &status);
	locale = loc ? loc : uloc_getDefault();
	CLK_RETVM_IF(!locale, FAILED, "locale NULL");

	UChar timezoneID[MAX_TIMEZONE_LENGHT] = { 0 };
	if (timezone) {
		u_uastrncpy(timezoneID, timezone, MAX_TIMEZONE_LENGHT);
	}
	//set pattern
	UChar upattern[MAX_PATTERN_LENGHT] = { 0 };
	u_uastrncpy(upattern, pattern, MAX_PATTERN_LENGHT);
	// generate best pattern for locale region
	generator = udatpg_open(locale, &status);
	bestPatternCapacity =
	    (int32_t) (sizeof(bestPattern) / sizeof((bestPattern)[0]));
	bestPatternLength =
	    udatpg_getBestPattern(generator, upattern, u_strlen(upattern),
				  bestPattern, bestPatternCapacity, &status);

	if (timezone) {
		date_fmt =
		    udat_open(UDAT_IGNORE, UDAT_DEFAULT, locale, timezoneID, -1,
			      bestPattern, bestPatternLength, &status);
	} else {
		date_fmt =
		    udat_open(UDAT_IGNORE, UDAT_DEFAULT, locale, NULL, -1,
			      bestPattern, bestPatternLength, &status);
	}
	CLK_RETVM_IF(!date_fmt, FAILED, "udat_open failed");
	//frist, get len
	tmplen = udat_format(date_fmt, tmpdate, NULL, tmplen, NULL, &status);
	CLK_RETVM_IF(IS_EQUAL(0, tmplen), FAILED, "tmplen=0");
	//then,malloc
	if (IS_EQUAL(status, U_BUFFER_OVERFLOW_ERROR)) {
		status = U_ZERO_ERROR;
		tmpstr = (UChar *) malloc(sizeof(UChar) * (tmplen + 1));
		CLK_RETVM_IF(NULL_CHECK(tmpstr), FAILED, "malloc failed");

		udat_format(date_fmt, tmpdate, tmpstr, tmplen + 1, NULL,
			    &status);
	}
	//
	dstStr = u_austrncpy(dstStr, tmpstr, dstStr_num);
	CLK_INFO_PURPLE("result:%s", dstStr);
	ret = status;
 End:
	if (generator) {
		udatpg_close(generator);
	}
	if (date_fmt) {
		udat_close(date_fmt);
	}
	FREEIF(tmpstr);
	CLK_FUN_END();
	return ret;
}

int clk_timezone_get(char *dst, size_t number)
{
	retv_if(!dst || number < 1, FAILED);
	CLK_FUN_BEG();
	UChar timezoneID[MAX_TIMEZONE_LENGHT] = { 0 };
	UErrorCode status = U_ZERO_ERROR;
	ucal_getDefaultTimeZone(timezoneID, MAX_TIMEZONE_LENGHT, &status);
	retv_if(status != SUCCESS, FAILED);

	dst = u_austrncpy(dst, timezoneID, number);
	CLK_INFO_PURPLE("default timezone is %s: ", dst);
	CLK_FUN_END();
	return SUCCESS;
}

void clk_timezone_update()
{
	UErrorCode status = U_ZERO_ERROR;
	UChar uOlsonID[BUF_SIZE_64] = { 0 };

	char *timezone = vconf_get_str(VCONFKEY_SETAPPL_TIMEZONE_ID);
	ret_if(!timezone);
	CLK_INFO_PURPLE("current timezone is :  %s", timezone);
	u_uastrcpy(uOlsonID, timezone);
	ucal_setDefaultTimeZone(uOlsonID, &status);

	free(timezone);
	retm_if(U_FAILURE(status), "error value is %s", u_errorName(status));
}
