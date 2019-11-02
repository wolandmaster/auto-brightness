#include <stdio.h>
#include <stdlib.h>
#include <service_app.h>
#include <device/display.h>
#include <dlog.h>
#include "autobrightnessservice.h"

static bool on_service_create(void *data) {
	dlog_print(DLOG_DEBUG, LOG_TAG, "service create");
	return true;
}

static void on_service_terminate(void *data) {
	dlog_print(DLOG_DEBUG, LOG_TAG, "service terminate");
}

static void on_service_app_control(app_control_h app_control, void *data) {
	char *brightness_str;
	int brightness;
	app_control_get_extra_data(app_control, "brightness", &brightness_str);
	sscanf(brightness_str, "%d", &brightness);
	free(brightness_str);
	int brightness_values[] = { 0, 1, 20, 40, 50, 60, 70, 80, 90, 95, 100 };
	int brightness_value = brightness_values[brightness];
	dlog_print(DLOG_INFO, LOG_TAG, "set display brightness to %d%% (%d)", brightness_value, brightness);
	device_display_set_brightness(0, brightness_value);
}

int main(int argc, char* argv[]) {
	service_app_lifecycle_callback_s event_callback;

	event_callback.create = on_service_create;
	event_callback.terminate = on_service_terminate;
	event_callback.app_control = on_service_app_control;

	return service_app_main(argc, argv, &event_callback, NULL);
}
