#include "TFTUtils.h"

void TFTUtils::fillWindow(TFT_eSPI *tft, Window win, uint32_t fillColor) {
    tft->fillRect(win.x, win.y, win.width, win.height, fillColor);
}

void TFTUtils::ignoreTouch(uint16_t x, uint16_t y, bool absolute) { return; }

void TFTUtils::drawBorderRect(TFT_eSPI *tft, Window win, uint32_t fillColor, LineProperties borderProps, bool fill) {
    for (int i = 0; i < borderProps.width; i++) {
        tft->drawRect(win.x + i, win.y + i, win.width - (2 * i), win.height - (2 * i), borderProps.color);
    }
    if (fill) {
        tft->fillRect(win.x + borderProps.width, win.y + borderProps.width,
                      win.width - (2 * borderProps.width), win.height - (2 * borderProps.width), fillColor);
    }
}

void TFTUtils::touchCalibrate(TFT_eSPI *tft, const char *calFileName, bool forceCalibrate) {
    uint16_t calData[5];
    uint8_t calDataOK = 0;

    // check if calibration file exists
    if (SPIFFS.exists(calFileName)) {
        File f = SPIFFS.open(calFileName, "r");
        if (f) {
            size_t rd = f.readBytes((char *)calData, 14);
            if (rd == 14) {
                calDataOK = 1;
            }
            f.close();
        }
    }
    if (calDataOK && !forceCalibrate) {
        // calibration data valid
        tft->setTouch(calData);
    } else {
        tft->fillScreen(TFT_BLACK);
        tft->setTextColor(TFT_WHITE, TFT_BLACK);
        tft->setTextSize(1);
        tft->setCursor(20, 0, 2);
        tft->println("calibration run");
        // data not valid. recalibrate
        tft->calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);
        // store data
        File f = SPIFFS.open(calFileName, "w");
        if (f) {
            f.write((const unsigned char *)calData, 14);
            f.close();
        }
    }
}

bool TFTUtils::contains(Window &w, uint16_t x, uint16_t y) {
    if (x < w.x || x > w.x + w.width) return false;
    if (y < w.y || y > w.y + w.height) return false;
    return true;
}

bool TFTUtils::overlaps(Window &w1, Window &w2) {
    if (w1.x <= w2.x && w1.y <= w2.y) { // TL1 up & left of TL2
        return w1.x + w1.width > w2.x && w1.y + w1.height > w2.y;
    }
    if (w1.x <= w2.x && w1.y > w2.y) { // TL1 down & left of TL2
        return w1.x + w1.width > w2.x && w1.y < w2.y + w2.height;
    }
    if (w1.x > w2.x && w1.y <= w2.y) { // TL1 up & right of TL2
        return w1.x < w2.x + w2.width && w1.y + w1.height > w2.y;
    }
    if (w1.x > w2.x && w1.y > w2.y) { // TL1 down & right of TL2
        return w1.x < w2.x + w2.width && w1.y < w2.y + w2.height;
    }
    return false;
}

bool TFTUtils::contains(Window *w, uint16_t x, uint16_t y) {
    return contains(*w, x, y);
}