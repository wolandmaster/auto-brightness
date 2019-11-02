#ifndef MODIFY_VIEW_H_
#define MODIFY_VIEW_H_

#include <Elementary.h>

typedef struct modify_view_context modify_view_context;
struct modify_view_context {
	Evas_Object *naviframe;
	Evas_Object *grid;
	Evas_Object *hour_spinner;
	Evas_Object *hour_label;
	Evas_Object *min_spinner;
	Evas_Object *min_label;
	Evas_Object *brightness_spinner;
	Evas_Object *brightness_label;
	Evas_Object *save;
	Evas_Object *delete;

	Elm_Object_Item* (*show)(modify_view_context*);
};

/* Gear Fit 2 (Pro) */
#define SCREEN_WIDTH 216
#define SCREEN_HEIGHT 432

#define SPINNER_HEIGHT 76
#define LABEL_HEIGHT 32
#define BUTTON_HEIGHT 64

#define TOP_PADDING 10
#define LABEL_PADDING -29
#define SPINNER_PADDING -14
#define BUTTON_PADDING 8

#define HOUR_SPINNER_INTERVAL 0.2
#define MIN_SPINNER_INTERVAL 0.1

modify_view_context* modify_view_create(Evas_Object*);

#endif /* MODIFY_VIEW_H_ */
