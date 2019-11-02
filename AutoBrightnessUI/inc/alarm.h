#ifndef ALARM_H_
#define ALARM_H_

#define ALARM_EVERY_DAY ALARM_WEEK_FLAG_SUNDAY | ALARM_WEEK_FLAG_MONDAY \
	| ALARM_WEEK_FLAG_TUESDAY | ALARM_WEEK_FLAG_WEDNESDAY | ALARM_WEEK_FLAG_THURSDAY \
	| ALARM_WEEK_FLAG_FRIDAY | ALARM_WEEK_FLAG_SATURDAY

#define BRIGHTNESS_EXTRA_DATA_KEY "brightness"

int alarm_add_trigger(int, int, int);
void alarm_delete_trigger(int);
void alarm_list_triggers();

#endif /* ALARM_H_ */
