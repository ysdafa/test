/*
*
* Copyright 2013  Samsung Electronics Co., Ltd
*
* Licensed under the Flora License, Version 1.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*/
#ifndef __NOA_DETAIL_H__
#define __NOA_DETAIL_H__

#include "noa.h"

#define NOA_DETAIL "NOA Detail"
#define PATH_MAX 100
#define IMAGE_MAX 79

void _show_noa_detail(void *data, Evas_Object *obj, void *event_inaviframeo);
Evas_Object *create_layout(Evas_Object *parent, char *group);

#endif				

