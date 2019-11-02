#include <tools.h>

static app_context *context;

void tool_initialize(app_context *app_context) {
	context = app_context;
}

static void on_toast_hide(void *data, Evas_Object *obj, void *event_info) {
	evas_object_del(obj);
}

void popup_toast(const char *message) {
	Evas_Object *popup = elm_popup_add(context->window);
	elm_object_style_set(popup, "toast");
	elm_popup_orient_set(popup, ELM_POPUP_ORIENT_BOTTOM);
	evas_object_size_hint_weight_set(popup, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	elm_popup_align_set(popup, ELM_NOTIFY_ALIGN_FILL, 1.0);
	elm_object_part_text_set(popup, "elm.text", message);
	evas_object_smart_callback_add(popup, "block,clicked", on_toast_hide, NULL);
	evas_object_smart_callback_add(popup, "timeout", on_toast_hide, NULL);
	elm_popup_timeout_set(popup, 1.5);
	evas_object_show(popup);
}
