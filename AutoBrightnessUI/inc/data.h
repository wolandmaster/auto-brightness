#ifndef DATA_H_
#define DATA_H_

#include <bundle.h>
#include <stdbool.h>

typedef struct {
	int id;
	int hour;
	int min;
	int brightness;
} item_data;

typedef struct {
	int previous_id;
	item_data *data;
	bundle *bundle;
} update_data;

typedef struct {
	char *value;
	int id;
} find_data;

#define DATA_BUNDLE_RAW "item-data-bundle-raw"
#define DATA_BUNDLE_LEN "item-data-bundle-len"

#define ITEM_VALUE_FORMAT "%02d:%02d>%02d"

void data_initialize();
void data_terminate();
item_data* data_save_item(int, int, int, int);
void data_update_item(int, item_data*);
item_data* data_decode_value(const char *key, const char *value);
void data_delete_item(int);
int data_get_value_key(int, int);
void data_iterate(bundle_iterate_cb_t callback, void*);

#endif /* DATA_H_ */
