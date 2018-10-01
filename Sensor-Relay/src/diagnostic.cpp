#include <config.h>
#include <SerialDebug.h>
#include <diagnostic.h>
#include <display-controller.h>

static int diagnostic_check_input() {
    return 0;
}

void diagnostic_init() {
    DEBUG("Diagnostic: Started wait for controller");
    for (auto i = 0; i < DIAGNOSTIC_BOOT_ATTEMPTS; i++) {

    	USB_SERIAL.println("BOOT!");
	delay(DIAGNOSTIC_BOOT_TIME / DIAGNOSTIC_BOOT_ATTEMPTS);

	if (diagnostic_check_input()) {
	    break;
	}
    }
}
