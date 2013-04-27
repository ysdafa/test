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
#ifndef __CLK_FWK_VIEW_H__
#define __CLK_FWK_VIEW_H__

#include <Elementary.h>
#include "clock_fwk_define.h"
/**********************************************************************
******************define, struct ,typedef, union, enum, global val *************************************
***********************************************************************/

#define MAX_CLK_FWK_VIEW_LAYER (10)
//
typedef struct _clk_layout {
	Evas_Object *ly_main;

} clk_layout;
//
typedef struct _clk_view {
	int (*create) (void *cb);
	int (*destroy) (void *cb);
	int (*update) (void *cb);
	int (*cleanup) (void *cb);

	Eina_Bool is_create;	// EINA_TRUE:exist
	int layer;		//layer

} clk_view;

/**********************************************************************
******************Global function ref*************************************
***********************************************************************/
int clk_view_node_set_cur_view(clk_view *view);
int clk_view_node_table_intialize();
int clk_view_node_table_register(clk_view *view, clk_view *topview);
int clk_view_cb_at_endKey(void *cb);

extern int clk_view_create(clk_view *view, void *cb);
extern int clk_view_update(clk_view *view, void *cb);
extern int clk_view_destroy(clk_view *view, void *cb);
extern int clk_view_cleanup(clk_view *view, void *cb);
extern int clk_view_change(clk_view *from_view, clk_view *to_view, void *cb);

#endif				/* __CLK_FWK_VIEW_H__ */
