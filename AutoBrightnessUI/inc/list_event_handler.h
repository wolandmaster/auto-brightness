#ifndef LIST_EVENT_HANDLER_H_
#define LIST_EVENT_HANDLER_H_

#include "list_view.h"

char* on_list_item_text_get(void*, Evas_Object*, const char*);
void on_list_item_del(void*, Evas_Object*);
void on_data_iterate(const char*, const char*, void*);
void on_add_clicked(list_view_context*, Evas_Object*, void*);
void on_item_selected(list_view_context*, Evas_Object*, void*);

#endif /* LIST_EVENT_HANDLER_H_ */
