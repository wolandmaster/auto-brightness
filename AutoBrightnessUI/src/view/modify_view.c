#include <app.h>
#include "modify_view.h"

static void spinner_label_text_set(Evas_Object *obj, const char *text) {
	char buf[128];
	snprintf(buf, sizeof(buf), "<color=#999999><font_size=25><align=center>%s</align></font_size></color>", text);
	elm_object_text_set(obj, buf);
}

Elm_Object_Item* modify_view_show(modify_view_context* context) {
	Elm_Object_Item* naviframe_item = elm_naviframe_item_push(context->naviframe, "", NULL, NULL, context->grid, NULL);
	elm_naviframe_item_title_enabled_set(naviframe_item, EINA_FALSE, EINA_FALSE);
	evas_object_show(context->hour_spinner);
	evas_object_show(context->hour_label);
	evas_object_show(context->min_spinner);
	evas_object_show(context->min_label);
	evas_object_show(context->brightness_spinner);
	evas_object_show(context->brightness_label);
	evas_object_show(context->save);
	evas_object_show(context->delete);
	evas_object_show(context->grid);
	return naviframe_item;
}

modify_view_context* modify_view_create(Evas_Object* naviframe) {
	modify_view_context* context = calloc(1, sizeof(modify_view_context));
	context->naviframe = naviframe;
	context->show = &modify_view_show;
	int widget_top = TOP_PADDING;

	/* Grid */
	context->grid = elm_grid_add(naviframe);
	evas_object_size_hint_weight_set(context->grid, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->grid, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_grid_size_set(context->grid, SCREEN_WIDTH, SCREEN_HEIGHT);

	/* Hour spinner */
	context->hour_spinner = elm_spinner_add(context->grid);
	evas_object_size_hint_weight_set(context->hour_spinner, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->hour_spinner, 0.5, 0.0);
	elm_spinner_min_max_set(context->hour_spinner, 0, 23);
	elm_spinner_step_set(context->hour_spinner, 1);
	elm_spinner_wrap_set(context->hour_spinner, EINA_TRUE);
	elm_spinner_interval_set(context->hour_spinner, HOUR_SPINNER_INTERVAL);
	elm_spinner_label_format_set(context->hour_spinner, "%02.0f");
	elm_grid_pack(context->grid, context->hour_spinner, 0, widget_top, SCREEN_WIDTH, SPINNER_HEIGHT);
	widget_top += SPINNER_HEIGHT;

	/* Hour label */
	context->hour_label = elm_label_add(context->grid);
	evas_object_size_hint_weight_set(context->hour_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->hour_label, 0.5, 0.0);
	spinner_label_text_set(context->hour_label, _("IDS_HOUR"));
	elm_grid_pack(context->grid, context->hour_label, 0, widget_top + LABEL_PADDING, SCREEN_WIDTH, LABEL_HEIGHT);
	widget_top += LABEL_HEIGHT;

	/* Min spinner */
	context->min_spinner = elm_spinner_add(context->grid);
	evas_object_size_hint_weight_set(context->min_spinner, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->min_spinner, 0.5, 0.0);
	elm_spinner_min_max_set(context->min_spinner, 0, 59);
	elm_spinner_step_set(context->min_spinner, 1);
	elm_spinner_wrap_set(context->min_spinner, EINA_TRUE);
	elm_spinner_interval_set(context->min_spinner, MIN_SPINNER_INTERVAL);
	elm_spinner_label_format_set(context->min_spinner, "%02.0f");
	widget_top += SPINNER_PADDING;
	elm_grid_pack(context->grid, context->min_spinner, 0, widget_top, SCREEN_WIDTH, SPINNER_HEIGHT);
	widget_top += SPINNER_HEIGHT;

	/* Min label */
	context->min_label = elm_label_add(context->grid);
	evas_object_size_hint_weight_set(context->min_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->min_label, 0.5, 0.0);
	spinner_label_text_set(context->min_label, _("IDS_MIN"));
	elm_grid_pack(context->grid, context->min_label, 0, widget_top + LABEL_PADDING, SCREEN_WIDTH, LABEL_HEIGHT);
	widget_top += LABEL_HEIGHT;

	/* Brightness spinner */
	context->brightness_spinner = elm_spinner_add(context->grid);
	evas_object_size_hint_weight_set(context->brightness_spinner, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->brightness_spinner, 0.5, 0.0);
	elm_spinner_min_max_set(context->brightness_spinner, 1, 10);
	elm_spinner_step_set(context->brightness_spinner, 1);
	widget_top += SPINNER_PADDING;
	elm_grid_pack(context->grid, context->brightness_spinner, 0, widget_top, SCREEN_WIDTH, SPINNER_HEIGHT);
	widget_top += SPINNER_HEIGHT;

	/* Brightness label */
	context->brightness_label = elm_label_add(context->grid);
	evas_object_size_hint_weight_set(context->brightness_label, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->brightness_label, 0.5, 0.0);
	spinner_label_text_set(context->brightness_label, _("IDS_BRIGHTNESS"));
	elm_grid_pack(context->grid, context->brightness_label, 0, widget_top + LABEL_PADDING, SCREEN_WIDTH, LABEL_HEIGHT);
	widget_top += LABEL_HEIGHT;

	/* Save */
	context->save = elm_button_add(context->grid);
	evas_object_size_hint_weight_set(context->save, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->save, 0.5, 0.0);
	elm_object_text_set(context->save, _("IDS_SAVE"));
	elm_grid_pack(context->grid, context->save, 0, SCREEN_HEIGHT - 2 * BUTTON_HEIGHT - BUTTON_PADDING, SCREEN_WIDTH,
	BUTTON_HEIGHT);

	/* Delete */
	context->delete = elm_button_add(context->grid);
	evas_object_size_hint_weight_set(context->delete, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->delete, 0.5, 0.0);
	elm_object_text_set(context->delete, _("IDS_DELETE"));
	elm_grid_pack(context->grid, context->delete, 0, SCREEN_HEIGHT - BUTTON_HEIGHT, SCREEN_WIDTH, BUTTON_HEIGHT);

	return context;
}

