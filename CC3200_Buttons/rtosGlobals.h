/* This header file contains the global variables that are accessable to all tabs
*/

// Core library
#include "Energia.h"

#ifndef rtosGlobals_h
#define rtosGlobals_h

// Include application, user and local libraries
#include "Event.h"

#define PIN1 PUSH1
#define DEBOUNCE_COUNT 10
#define DEBOUNCE_DELAY 5

// Create event object(s)
Event pressEvent;

#endif
