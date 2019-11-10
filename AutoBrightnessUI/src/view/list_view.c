#include <app.h>
#include <Elementary.h>
#include "list_view.h"
#include "list_event_handler.h"

static Elm_Object_Item* list_item_create(list_view_context *context, item_data *list_item_data) {
	Elm_Genlist_Item_Class *list_item_class = elm_genlist_item_class_new();
	list_item_class->item_style = "2text";
	list_item_class->func.text_get = on_list_item_text_get;
	list_item_class->func.del = on_list_item_del;
	return elm_genlist_item_append(context->list, list_item_class, list_item_data, NULL, ELM_GENLIST_ITEM_NONE,
			(Evas_Smart_Cb) on_item_selected, context);
}

static Elm_Object_Item* list_view_show(list_view_context* context) {
	Elm_Object_Item* naviframe_item = elm_naviframe_item_push(context->naviframe, _("IDS_AUTO_BRIGHTNESS"), NULL, NULL,
			context->box, NULL);
	evas_object_show(context->list);
	evas_object_show(context->add);
	evas_object_show(context->box);
	return naviframe_item;
}

list_view_context* list_view_create(Evas_Object *naviframe) {
	list_view_context *context = calloc(1, sizeof(list_view_context));
	context->naviframe = naviframe;
	context->show = &list_view_show;
	context->create = &list_item_create;

	/* Box */
	context->box = elm_box_add(context->naviframe);
	evas_object_size_hint_weight_set(context->box, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->box, EVAS_HINT_FILL, EVAS_HINT_FILL);

	/* List */
	context->list = elm_genlist_add(context->box);
	evas_object_size_hint_weight_set(context->list, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
	evas_object_size_hint_align_set(context->list, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_genlist_mode_set(context->list, ELM_LIST_COMPRESS);
	elm_scroller_policy_set(context->list, (Elm_Scroller_Policy) ELM_SCROLLER_POLICY_OFF,
			(Elm_Scroller_Policy) ELM_SCROLLER_POLICY_AUTO);
	data_iterate(on_data_iterate, context);
	elm_box_pack_end(context->box, context->list);

	/* Add */
	context->add = elm_button_add(context->box);
	evas_object_size_hint_weight_set(context->add, EVAS_HINT_EXPAND, 0);
	evas_object_size_hint_align_set(context->add, EVAS_HINT_FILL, EVAS_HINT_FILL);
	elm_object_translatable_text_set(context->add, "Add");
	evas_object_smart_callback_add(context->add, "clicked", (Evas_Smart_Cb) on_add_clicked, context);
	elm_box_pack_end(context->box, context->add);

	return context;
}
