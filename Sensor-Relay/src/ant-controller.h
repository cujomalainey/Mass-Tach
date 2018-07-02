#ifndef ANT_CONTROLLER
#define ANT_CONTROLLER
#define ANT_NUM_CHANNELS 15

enum ant_device_type
{
	ANT_DEVICE_BIKE_CADENCE = 0,
	ANT_DEVICE_BIKE_SPEED = 1,
	ANT_DEVICE_HR_MONITOR = 2
};

/*
 * Resets and loads any available configure with any data available
 */
void ant_init();

/*
 * Reset radio and clear any non-const config
 */
void ant_reset();

/*
 * Service ant radio
 */
void ant_tick();

#endif
