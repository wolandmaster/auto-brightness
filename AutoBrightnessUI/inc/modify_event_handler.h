#ifndef MODIFY_EVENT_HANDLER_H_
#define MODIFY_EVENT_HANDLER_H_

#include "list_view.h"

void on_save_clicked(list_view_context*, Evas_Object*, void*);
void on_delete_clicked(list_view_context*, Evas_Object*, void*);
Eina_Bool on_naviframe_pop(void*, Elm_Object_Item*);

#endif /* MODIFY_EVENT_HANDLER_H_ */
