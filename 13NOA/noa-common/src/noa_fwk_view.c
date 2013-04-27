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

#include "clock_fwk_view.h"
/**********************************************************************
******************define, struct ,typedef, union, enum, global val *************************************
***********************************************************************/
#define MAX_VIEWNODE_NUM    15

typedef struct _ClkViewNode {
	clk_view *view;
	clk_view *topview;
} ClkViewNode;

/**********************************************************************
******************Global val , static global val*************************************
***********************************************************************/

static clk_view *g_cur_view;;	//use by 'End Key' process
static ClkViewNode g_view_node_table[MAX_VIEWNODE_NUM];
static int g_view_node_table_cur_size = 0;

/**********************************************************************
******************Global function ref*************************************
***********************************************************************/
//
int clk_view_node_set_cur_view(clk_view * view)
{
	g_cur_view = view;
	return SUCCESS;
}

//
int clk_view_node_table_intialize()
{
	g_cur_view = NULL;
	g_view_node_table_cur_size = 0;
	return SUCCESS;
}

//
int clk_view_node_table_register(clk_view * view, clk_view * topview)
{
	if (g_view_node_table_cur_size >= MAX_VIEWNODE_NUM) {
		return FAILED;
	}

	g_view_node_table[g_view_node_table_cur_size].view = view;
	g_view_node_table[g_view_node_table_cur_size].topview = topview;
	g_view_node_table_cur_size++;
	return SUCCESS;
}

//
int clk_view_cb_at_endKey(void *cb)
{
	int idx = 0;
	ClkViewNode *viewnode = NULL;
	for (; idx < g_view_node_table_cur_size; idx++) {
		if (g_cur_view == g_view_node_table[idx].view) {
			viewnode = &(g_view_node_table[idx]);
			break;
		}
	}
	if (viewnode && viewnode->view && viewnode->topview) {
		clk_view_change(viewnode->view, viewnode->topview, cb);
	}
	return SUCCESS;
}

/**
* send
* This function is  used to be default cb in the elm_popup when get signle:"response"
* @param            data[in]   pointer to data
* @return           when success, return SUCCESS or FAILED if error
* @exception
*/
int clk_view_create(clk_view * view, void *cb)
{
	int nErr = SUCCESS;
	int ret = SUCCESS;
	CLK_RETVM_IF(!cb, FAILED, "cb==null");
	CLK_RETVM_IF(!view, FAILED, "view==null");
	if (view->create) {
		ret = view->create(cb);
	}
 End:
	return ret;
}

/**
* send
* This function is  used to be default cb in the elm_popup when get signle:"response"
* @param            data[in]   pointer to data
* @return           when success, return SUCCESS or FAILED if error
* @exception
*/
int clk_view_destroy(clk_view * view, void *cb)
{
	int nErr = SUCCESS;
	int ret = SUCCESS;
	CLK_RETVM_IF(!cb, FAILED, "cb==null");
	CLK_RETVM_IF(!view, FAILED, "view==null");
	if (view->destroy) {
		ret = view->destroy(cb);
	}
 End:
	return ret;
}

/**
* send
* This function is  used to be default cb in the elm_popup when get signle:"response"
* @param            data[in]   pointer to data
* @return           when success, return SUCCESS or FAILED if error
* @exception
*/
int clk_view_update(clk_view * view, void *cb)
{
	int nErr = SUCCESS;
	int ret = SUCCESS;
	CLK_FUN_BEG();
	CLK_RETVM_IF(!cb, FAILED, "cb==null");
	CLK_RETVM_IF(!view, FAILED, "view==null");
	if (view && view->update) {
		ret = view->update(cb);
	}
 End:
	CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to be default cb in the elm_popup when get signle:"response"
* @param            data[in]   pointer to data
* @return           when success, return SUCCESS or FAILED if error
* @exception
*/
int clk_view_cleanup(clk_view * view, void *cb)
{
	int nErr = SUCCESS;
	int ret = SUCCESS;
	CLK_FUN_BEG();
	CLK_RETVM_IF(!cb, FAILED, "cb==null");
	CLK_RETVM_IF(!view, FAILED, "view==null");
	if (view->cleanup) {
		ret = view->cleanup(cb);
	}
 End:
	CLK_FUN_END();
	return ret;
}

/**
* send
* This function is  used to be default cb in the elm_popup when get signle:"response"
* @param            data[in]   pointer to data
* @return           when success, return SUCCESS or FAILED if error
* @exception
*/
int clk_view_change(clk_view * from_view, clk_view * to_view, void *cb)
{
	int nErr = SUCCESS;
	int ret = SUCCESS;
	CLK_RETVM_IF(!cb, FAILED, "cb==null");
	CLK_RETVM_IF(!from_view, FAILED, "from_view==null");
	CLK_RETVM_IF(!to_view, FAILED, "to_view==null");
	CLK_FUN_BEG();
	if (from_view->layer >= to_view->layer) {	//high layer->low layer, destroy high layer
		nErr = clk_view_destroy(from_view, cb);
		CLK_RETVM_IF(ret != SUCCESS, FAILED, "clk_view_destroy error");
	} else {		//low layer->high layer, clean low layer
		nErr = clk_view_cleanup(from_view, cb);
		CLK_RETVM_IF(ret != SUCCESS, FAILED, "clk_view_cleanup error");
	}
	if (EINA_TRUE == to_view->is_create) {
		ret = clk_view_update(to_view, cb);
	} else {
		ret = clk_view_create(to_view, cb);
	}
	g_cur_view = to_view;	//compute new value of g_cur_view.
 End:
	CLK_FUN_END();
	return ret;
}
