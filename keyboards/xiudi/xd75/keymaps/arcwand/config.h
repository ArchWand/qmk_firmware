#pragma once

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NKRO_DEFAULT_ON true

// Reduce compiled size
#define NO_ACTION_ONESHOT
#define NO_ACTION_TAPPING

// Enable rapid switch from tap to hold, disables double tap hold auto-repeat.
#define QUICK_TAP_TERM 0

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL
