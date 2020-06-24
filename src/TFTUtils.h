#ifndef _TFT_UTILS_H
#define _TFT_UTILS_H

#include "FS.h"

#ifdef TFT_ENABLED

#include "TFTTypes.h"

#define TFT_TOUCH_TIME 100 // ms to ignore touches after processing one

class TFTUtils {
public:
    static void ignoreTouch(uint16_t x, uint16_t y, bool absolute);
    static bool contains(Window &w, uint16_t x, uint16_t y);
    static bool contains(Window *w, uint16_t x, uint16_t y);
    static bool overlaps(Window &w1, Window &w2);
    static void fillWindow(TFT_eSPI *tft, Window &win, uint32_t fillColor);
    static void drawBorderRect(TFT_eSPI *tft, Window &win, uint32_t fillColor, LineProperties borderProps = DefaultBorder, bool fill = true);
    // Read calibration data from file given, or calibrate and then save it there
    static void touchCalibrate(TFT_eSPI *tft, const char *calFileName, bool forceCalibrate = false);
}; // class TFTUtils

#endif // #ifdef TFT_ENABLED

#endif // #ifndef _TFT_UTILS_H