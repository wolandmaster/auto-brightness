#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <app_preference.h>
#include <dlog.h>
#include "data.h"
#include "autobrightnessui.h"

static bundle *bundle_items = NULL;

static void bundle_load() {
	char *str;
	bundle_raw *raw;
	int len;
	preference_get_string(DATA_BUNDLE_RAW, &str);
	preference_get_int(DATA_BUNDLE_LEN, &len);
	raw = (bundle_raw *) str;
	bundle_items = bundle_decode(raw, len);
	free(str);
}

static void bundle_save() {
	bundle_raw *raw;
	int len;
	if (bundle_encode(bundle_items, &raw, &len) == BUNDLE_ERROR_NONE) {
		preference_set_string(DATA_BUNDLE_RAW, (const char *) raw);
		preference_set_int(DATA_BUNDLE_LEN, len);
	}
}

void data_initialize() {
	if (bundle_items == NULL) {
		bool bundle_raw_exists, bundle_len_exists;
		preference_is_existing(DATA_BUNDLE_RAW, &bundle_raw_exists);
		preference_is_existing(DATA_BUNDLE_LEN, &bundle_len_exists);
		if (bundle_raw_exists && bundle_len_exists) {
			bundle_load();
		} else {
			bundle_items = bundle_create();
		}
	}
}

void data_terminate() {
	bundle_free(bundle_items);
	bundle_items = NULL;
}

static void data_add_item(bundle *target_bundle, item_data *data) {
	char key[11];
	char value[9];
	snprintf(key, sizeof(key), "%d", data->id);
	snprintf(value, sizeof(value), ITEM_VALUE_FORMAT, data->hour, data->min, data->brightness);
	bundle_add_str(target_bundle, key, value);
}

item_data* data_save_item(int id, int hour, int min, int brightness) {
	item_data *data = calloc(1, sizeof(item_data));
	data->id = id;
	data->hour = hour;
	data->min = min;
	data->brightness = brightness;
	data_add_item(bundle_items, data);
	bundle_save();
	return data;
}

static void on_update_iterate(const char *key, const char *value, void *data) {
	update_data *update = (update_data*) data;
	int id;
	sscanf(key, "%d", &id);
	if (id == update->previous_id) {
		data_add_item(update->bundle, update->data);
	} else {
		bundle_add_str(update->bundle, key, value);
	}
}

void data_update_item(int previous_id, item_data* data) {
	// Workaround for keep the item order
	update_data *update_data = calloc(1, sizeof(update_data));
	update_data->previous_id = previous_id;
	update_data->data = data;
	update_data->bundle = bundle_create();
	bundle_iterate(bundle_items, on_update_iterate, update_data);
	bundle_free(bundle_items);
	bundle_items = update_data->bundle;
	bundle_save();
	update_data->data = NULL;
	update_data->bundle = NULL;
	free(update_data);
}

void data_delete_item(int id) {
	char key[11];
	snprintf(key, sizeof(key), "%d", id);
	if (bundle_del(bundle_items, key) == BUNDLE_ERROR_NONE) {
		bundle_save();
	}
}

static void on_find_value_key_iterate(const char *key, const char *value, void *data) {
	find_data *find_data = data;
	if (strncmp(value, find_data->value, 5) == 0) {
		sscanf(key, "%d", &find_data->id);
	}
}

int data_get_value_key(int hour, int min) {
	char find_value[9];
	snprintf(find_value, sizeof(find_value), ITEM_VALUE_FORMAT, hour, min, 0);
	find_data *find_data = calloc(1, sizeof(find_data));
	find_data->value = strdup(find_value);
	find_data->id = -1;
	bundle_iterate(bundle_items, on_find_value_key_iterate, find_data);
	int id = find_data->id;
	free(find_data->value);
	free(find_data);
	return id;
}

item_data* data_decode_value(const char *key, const char *value) {
	item_data *data = calloc(1, sizeof(item_data));
	int id;
	sscanf(key, "%d", &id);
	data->id = id;
	sscanf(value, ITEM_VALUE_FORMAT, &data->hour, &data->min, &data->brightness);
	return data;
}

void data_iterate(bundle_iterate_cb_t callback, void* data) {
	bundle_iterate(bundle_items, callback, data);
}
