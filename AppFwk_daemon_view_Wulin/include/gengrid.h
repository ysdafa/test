/*
 * Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 */

#ifndef __DEF_test_gengrid_H_
#define __DEF_test_gengrid_H_

#include <Elementary.h>

#define THUMB_IMAGE_WIDTH 354   //Wide is 354 pix
#define THUMB_IMAGE_HEIGHT 308  //Heigt is 308 pix

#define BACKGROUND_RED 30
#define BACKGROUND_GREEN 0
#define BACKGROUND_BLUE 34

void gengrid_cb(void *data, Evas_Object *obj, void *event_info);
void gengrid_default_cb(void *data, Evas_Object *obj, void *event_info);
void gengrid_gridtext_cb(void *data, Evas_Object *obj, void *event_info);
void gengrid_gridtext2_cb(void *data, Evas_Object *obj, void *event_info);
void gengrid_theme_cb(void *data, Evas_Object *obj, void *event_info);
void gengrid_groupindex_cb(void *data, Evas_Object *obj, void *event_info);
void gengrid_create_view(void *data, char *type);

void gengrid_default_release();
void gengrid_gridtext_release();
void gengrid_groupindex_release();


#endif /* __DEF_test_gengrid_H__ */

