#include <app.h>
#include <app_alarm.h>
#include "list_event_handler.h"
#include "modify_event_handler.h"

char* on_list_item_text_get(void *data, Evas_Object *obj, const char *part) {
	item_data *list_item_data = (item_data*) data;
	if (strcmp(part, "elm.text") == 0) {
		char time[6];
		snprintf(time, sizeof(time), "%02d:%02d", list_item_data->hour, list_item_data->min);
		return strdup(time);
	} else if (strcmp(part, "elm.text.sub") == 0) {
		char brightness[64];
		snprintf(brightness, sizeof(brightness), _("IDS_BRIGHTNESS_TEXT"), list_item_data->brightness);
		return strdup(brightness);
	} else {
		return NULL;
	}
}

void on_list_item_del(void *data, Evas_Object *obj) {
	item_data *list_item_data = (item_data*) data;
	if (list_item_data) {
		free(list_item_data);
	}
}

void on_data_iterate(const char *key, const char *value, void *data) {
	list_view_context *context = data;
	context->create(context, data_decode_value(key, value));
}

void on_add_clicked(list_view_context *context, Evas_Object *obj, void *event_info) {
	struct tm date;
	alarm_get_current_time(&date);
	context->selected_item = NULL;
	context->modify_context = modify_view_create(context->naviframe);
	elm_spinner_value_set(context->modify_context->hour_spinner, date.tm_hour);
	elm_spinner_value_set(context->modify_context->min_spinner, date.tm_min);
	elm_spinner_value_set(context->modify_context->brightness_spinner, 5);
	elm_object_text_set(context->modify_context->delete, _("IDS_CANCEL"));
	evas_object_smart_callback_add(context->modify_context->save, "clicked", (Evas_Smart_Cb) on_save_clicked, context);
	evas_object_smart_callback_add(context->modify_context->delete, "clicked", (Evas_Smart_Cb) on_delete_clicked,
			context);
	Elm_Object_Item* naviframe_item = context->modify_context->show(context->modify_context);
	elm_naviframe_item_pop_cb_set(naviframe_item, on_naviframe_pop, context);
}

void on_item_selected(list_view_context *context, Evas_Object *obj, void *event_info) {
	Elm_Object_Item *selected_item = (Elm_Object_Item*) event_info;
	item_data *list_item_data = elm_object_item_data_get(selected_item);
	context->selected_item = selected_item;
	context->modify_context = modify_view_create(context->naviframe);
	elm_spinner_value_set(context->modify_context->hour_spinner, list_item_data->hour);
	elm_spinner_value_set(context->modify_context->min_spinner, list_item_data->min);
	elm_spinner_value_set(context->modify_context->brightness_spinner, list_item_data->brightness);
	elm_object_text_set(context->modify_context->delete, _("IDS_DELETE"));
	evas_object_smart_callback_add(context->modify_context->save, "clicked", (Evas_Smart_Cb) on_save_clicked, context);
	evas_object_smart_callback_add(context->modify_context->delete, "clicked", (Evas_Smart_Cb) on_delete_clicked,
			context);
	Elm_Object_Item* naviframe_item = context->modify_context->show(context->modify_context);
	elm_naviframe_item_pop_cb_set(naviframe_item, on_naviframe_pop, context);
	elm_genlist_item_selected_set(selected_item, EINA_FALSE);
}
