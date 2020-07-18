#include <app.h>
#include <system_settings.h>
#include <efl_extension.h>
#include <tools.h>
#include <dlog.h>
#include "autobrightnessui.h"
#include "alarm.h"

static void on_win_delete_request(void *data, Evas_Object *obj, void *event_info) {
	ui_app_exit();
}

static void on_hw_key_back(void *data, Evas_Object *obj, void *event_info) {
	app_context *context = data;
	if (elm_naviframe_top_item_get(context->naviframe) == elm_naviframe_bottom_item_get(context->naviframe)) {
		elm_win_lower(context->window);
	} else {
		elm_naviframe_item_pop(context->naviframe);
	}
}

static void on_app_terminate(void *data) {
	dlog_print(DLOG_DEBUG, LOG_TAG, "app terminate");
	app_context *context = data;
	data_terminate();
	free(context->list_context);
	evas_object_del(context->window);
	free(context);
	context = NULL;
}

static void on_app_control(app_control_h app_control, void *data) {
	dlog_print(DLOG_DEBUG, LOG_TAG, "app control");
}

static void on_app_pause(void *data) {
	dlog_print(DLOG_DEBUG, LOG_TAG, "app pause");
}

static void on_app_resume(void *data) {
	dlog_print(DLOG_DEBUG, LOG_TAG, "app resume");
}

static void on_language_changed(app_event_info_h event_info, void *data) {
	char *language = NULL;
	system_settings_get_value_string(SYSTEM_SETTINGS_KEY_LOCALE_LANGUAGE, &language);
	elm_language_set(language);
	free(language);
}

static void create_base_gui(app_context *context) {
	/* Window */
	context->window = elm_win_util_standard_add(PACKAGE, PACKAGE);
	elm_win_autodel_set(context->window, EINA_TRUE);
	evas_object_smart_callback_add(context->window, "delete,request", on_win_delete_request, NULL);
	eext_object_event_callback_add(context->window, EEXT_CALLBACK_BACK, on_hw_key_back, context);

	/* Conformant */
	context->conform = elm_conformant_add(context->window);
	evas_object_size_hint_weight_set(context->conform, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->conform, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_win_indicator_mode_set(context->window, ELM_WIN_INDICATOR_SHOW);
	elm_win_indicator_opacity_set(context->window, ELM_WIN_INDICATOR_OPAQUE);
	elm_win_resize_object_add(context->window, context->conform);

	/* Naviframe */
	context->naviframe = elm_naviframe_add(context->conform);
	elm_object_content_set(context->conform, context->naviframe);

	context->list_context = list_view_create(context->naviframe);
	context->list_context->show(context->list_context);
	evas_object_show(context->naviframe);
	evas_object_show(context->conform);
	evas_object_show(context->window);
}

static bool on_app_create(void *data) {
	dlog_print(DLOG_DEBUG, LOG_TAG, "app create");
	app_context *context = (app_context*) data;

	alarm_list_triggers();
	data_initialize();
	tool_initialize(context);
	create_base_gui(context);
	return true;
}

int main(int argc, char *argv[]) {
	app_context *context = { 0, };

	ui_app_lifecycle_callback_s event_callback = { 0, };
	app_event_handler_h handlers[5] = { NULL, };

	event_callback.create = on_app_create;
	event_callback.terminate = on_app_terminate;
	event_callback.pause = on_app_pause;
	event_callback.resume = on_app_resume;
	event_callback.app_control = on_app_control;

	ui_app_add_event_handler(&handlers[APP_EVENT_LANGUAGE_CHANGED], APP_EVENT_LANGUAGE_CHANGED, on_language_changed,
			&context);

	return ui_app_main(argc, argv, &event_callback, &context);
}
