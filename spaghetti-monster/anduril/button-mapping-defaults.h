#pragma once

#if defined(USE_MOMENTARY_MODE) && !defined(EVENT_MOMENTARY)
#define EVENT_MOMENTARY EV_5clicks
#endif

#if defined(EVENT_MOMENTARY) && !defined(EVENT_MOMENTARY_STROBE)
#define EVENT_MOMENTARY_STROBE EVENT_MOMENTARY
#endif

#if defined(USE_SUNSET_TIMER) && !defined(EVENT_HOLD_SUNSET_TIMER)
#define EVENT_HOLD_SUNSET_TIMER EV_click5_hold
#endif
