#ifndef DEBUG_h
#define DEBUG_h

#include "defines.h"

#if (USB_DEBUG_LEVEL >= DEBUG_LEVEL_INFO && USB_DEBUG_ENABLED)
#define DEBUG_INFO(X) DEBUG_SERIAL.print("I: "); DEBUG_SERIAL.println(X)
#else
#define DEBUG_INFO(X)
#endif

#if (USB_DEBUG_LEVEL >= DEBUG_LEVEL_WARNING && USB_DEBUG_ENABLED)
#define DEBUG_WARNING(X) DEBUG_SERIAL.print("W: "); DEBUG_SERIAL.println(X)
#else
#define DEBUG_WARNING(X)
#endif

#if (USB_DEBUG_LEVEL >= DEBUG_LEVEL_ERROR && USB_DEBUG_ENABLED)
#define DEBUG_ERROR(X) DEBUG_SERIAL.print("E: "); DEBUG_SERIAL.println(X)
#else
#define DEBUG_ERROR(X)
#endif

#endif // DEBUG_h
