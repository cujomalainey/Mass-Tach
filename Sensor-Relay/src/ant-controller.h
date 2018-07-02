#ifndef ANT_CONTROLLER
#define ANT_CONTROLLER

enum ant_device_type
{
	ANT_DEVICE_BIKE_CADENCE = 0,
	ANT_DEVICE_BIKE_SPEED = 1,
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
