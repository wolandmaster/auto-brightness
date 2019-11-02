#ifndef LIST_VIEW_H_
#define LIST_VIEW_H_

#include "data.h"
#include "modify_view.h"

typedef struct list_view_context list_view_context;
struct list_view_context {
	Evas_Object *naviframe;
	Evas_Object *box;
	Evas_Object *list;
	Elm_Object_Item *selected_item;
	Evas_Object *add;

	modify_view_context *modify_context;

	Elm_Object_Item* (*create)(list_view_context*, item_data*);
	Elm_Object_Item* (*show)(list_view_context*);
};

list_view_context* list_view_create(Evas_Object*);

#endif /* LIST_VIEW_H_ */
