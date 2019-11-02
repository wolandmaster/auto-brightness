#include <stdio.h>
#include <stdlib.h>
#include <app_alarm.h>
#include <dlog.h>
#include "alarm.h"
#include "autobrightnessui.h"

int alarm_add_trigger(int hour, int min, int brightness) {
	int alarm_id;
	char brightness_str[3];
	struct tm date;
	app_control_h app_control = NULL;

	app_control_create(&app_control);
	app_control_set_operation(app_control, APP_CONTROL_OPERATION_DEFAULT);
	app_control_set_app_id(app_control, "com.github.wolandmaster.autobrightnessservice");
	snprintf(brightness_str, sizeof(brightness_str), "%d", brightness);
	app_control_add_extra_data(app_control, BRIGHTNESS_EXTRA_DATA_KEY, brightness_str);
	alarm_get_current_time(&date);
	date.tm_sec = 0;
	date.tm_hour = hour;
	date.tm_min = min;
	alarm_schedule_with_recurrence_week_flag(app_control, &date, ALARM_EVERY_DAY, &alarm_id);
	app_control_destroy(app_control);
	return alarm_id;
}

void alarm_delete_trigger(int alarm_id) {
	alarm_cancel(alarm_id);
}

static bool on_alarm_list(int alarm_id, void *data) {
	struct tm date;
	app_control_h app_control = NULL;
	char *brightness_str;
	int brightness;

	alarm_get_scheduled_date(alarm_id, &date);
	alarm_get_app_control(alarm_id, &app_control);
	app_control_get_extra_data(app_control, BRIGHTNESS_EXTRA_DATA_KEY, &brightness_str);
	sscanf(brightness_str, "%d", &brightness);
	free(brightness_str);
	dlog_print(DLOG_DEBUG, LOG_TAG, "trigger id: %d at %02d:%02d with brightness: %d", alarm_id,
			date.tm_hour, date.tm_min, brightness);
	return true;
}

void alarm_list_triggers() {
	alarm_foreach_registered_alarm(on_alarm_list, NULL);
}
