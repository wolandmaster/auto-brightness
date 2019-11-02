#include <app.h>
#include "modify_event_handler.h"
#include "alarm.h"
#include "tools.h"

void on_save_clicked(list_view_context *context, Evas_Object *obj, void *event_info) {
	int hour = elm_spinner_value_get(context->modify_context->hour_spinner);
	int min = elm_spinner_value_get(context->modify_context->min_spinner);
	int brightness = elm_spinner_value_get(context->modify_context->brightness_spinner);
	int already_existing_id = data_get_value_key(hour, min);
	if (context->selected_item == NULL) {
		if (already_existing_id != -1) {
			// item with the same time already exists
			char message[64];
			snprintf(message, sizeof(message), _("IDS_ALREADY_EXISTS"), hour, min);
			popup_toast(message);
		} else {
			// add new item
			int alarm_id = alarm_add_trigger(hour, min, brightness);
			item_data *list_item_data = data_save_item(alarm_id, hour, min, brightness);
			context->create(context, list_item_data);
			elm_naviframe_item_pop(context->naviframe);
			popup_toast(_("IDS_SAVED"));
		}
	} else {
		item_data *selected_item_data = elm_object_item_data_get(context->selected_item);
		int previous_id = selected_item_data->id;
		if (already_existing_id != -1 && already_existing_id != previous_id) {
			// item with the same time already exists
			char message[64];
			snprintf(message, sizeof(message), _("IDS_ALREADY_EXISTS"), hour, min);
			popup_toast(message);
		} else {
			// update existing item
			int alarm_id = alarm_add_trigger(hour, min, brightness);
			alarm_delete_trigger(previous_id);
			selected_item_data->id = alarm_id;
			selected_item_data->hour = hour;
			selected_item_data->min = min;
			selected_item_data->brightness = brightness;
			data_update_item(previous_id, selected_item_data);
			elm_genlist_item_update(context->selected_item);
			elm_naviframe_item_pop(context->naviframe);
			popup_toast(_("IDS_UPDATED"));
		}
	}
}

void on_delete_clicked(list_view_context *context, Evas_Object *obj, void *event_info) {
	if (context->selected_item != NULL) {
		// delete existing item
		item_data *selected_item_data = elm_object_item_data_get(context->selected_item);
		alarm_delete_trigger(selected_item_data->id);
		data_delete_item(selected_item_data->id);
		elm_object_item_del(context->selected_item);
		popup_toast(_("IDS_DELETED"));
	}
	elm_naviframe_item_pop(context->naviframe);
}

Eina_Bool on_naviframe_pop(void *data, Elm_Object_Item *naviframe_item) {
	list_view_context *context = (list_view_context*) data;
	free(context->modify_context);
	context->modify_context = NULL;
	return EINA_TRUE;
}

