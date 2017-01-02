/*
 * Resets and loads any available configure with any data available
 */
void xbee_init();

/*
 * Reset radio and clear any non-const config
 */
void xbee_reset();

/*
 * Service xbee radio
 */
void xbee_tick();

void xbee_send_data(SensorData* data);