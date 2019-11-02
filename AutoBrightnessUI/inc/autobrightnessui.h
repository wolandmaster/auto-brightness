#ifndef AUTOBRIGHTNESSUI_H_
#define AUTOBRIGHTNESSUI_H_

#include "list_view.h"

#ifdef  LOG_TAG
#undef  LOG_TAG
#endif
#define LOG_TAG "auto-brightness-ui"

#if !defined(PACKAGE)
#define PACKAGE "com.github.wolandmaster.autobrightnessui"
#endif

typedef struct {
	Evas_Object *window;
	Evas_Object *conform;
	Evas_Object *naviframe;

	list_view_context *list_context;
} app_context;

#endif /* AUTOBRIGHTNESSUI_H_ */
