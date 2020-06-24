#ifndef _TFTTYPES_H
#define _TFTTYPES_H

#include <Arduino.h>

#include <functional>

#include "TFT_eSPI.h"

struct Point {
    uint32_t x;
    uint32_t y;
};

struct Window {
    uint32_t x;
    uint32_t y;
    int16_t width;
    int16_t height;
    Window() : Window(0, 0, 0, 0){};
    Window(uint32_t _x, uint32_t _y, int16_t _w, int16_t _h) {
        x = _x;
        y = _y;
        width = _w;
        height = _h;
    };
};

struct LineProperties {
    uint32_t color;
    uint8_t width;
};

const LineProperties DefaultBorder = {TFT_WHITE, 1};

typedef std::function<void(TFT_eSPI *tft)> TFTHandler;
typedef std::function<void(uint16_t x, uint16_t y, bool absolute)> TouchHandler;

typedef std::function<const void *(uint16_t elem_num)> DataProvider;
typedef std::function<void(int action, void *arg)> ActionHandler;

#endif // #ifndef _TFTTYPES_H