#ifndef DISPLAY_h
#define DISPLAY_h

enum display_msgs {
    DISPLAY_ANT,
    DISPLAY_BOOT,
    DISPLAY_CONF,
    DISPLAY_DIAG,
    DISPLAY_ME,
    DISPLAY_USB,
    DISPLAY_WIFI,
    /* Count for compilation enforcement */
    DISPLAY_COUNT,
    DISPLAY_NONE,
};

void display_init(void);
void display_tick(void);
void display_message(enum display_msgs);
void display_error(enum display_msgs);

#endif // DISPLAY_h
