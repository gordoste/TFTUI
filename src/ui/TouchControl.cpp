#include "TouchControl.h"

void TouchControl::handleTouch(uint16_t x, uint16_t y, bool absolute) {
    if (!m_shown) return;
    if (m_lastTouchTime + TFT_TOUCH_TIME > millis()) return;
    m_touchHandler(x, y, absolute);
    m_lastTouchTime = millis();
}
