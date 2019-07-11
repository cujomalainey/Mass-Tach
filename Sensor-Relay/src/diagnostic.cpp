#include <config.h>
#include <SerialDebug.h>
#include <diagnostic.h>
#include <display-controller.h>

static int diagnostic_check_input() {
    return 0;
}

void diagnostic_init() {
    DEBUG("Diagnostic: Started wait for controller");
    display_message(DISPLAY_DIAG);
    for (auto i = 0; i < DIAGNOSTIC_BOOT_ATTEMPTS; i++) {

    	USB_SERIAL.println("BOOT!");
	delay(DIAGNOSTIC_BOOT_TIME / DIAGNOSTIC_BOOT_ATTEMPTS);

	if (diagnostic_check_input()) {
	    ESP.restart();
	    break;
	}
    }
}

// handle diagnostic informations given by assertion and abort program execution:
void __assert(const char *__func, const char *__file, int __lineno, const char *__sexp) {
    // transmit diagnostic informations through serial link.
    Serial.println(__func);
    Serial.println(__file);
    Serial.println(__lineno, DEC);
    Serial.println(__sexp);
    Serial.flush();
    // abort program execution.
    abort();
}
