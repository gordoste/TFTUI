#include "TouchScreen.h"

void TouchScreen::init(TFT_eSPI *tft) {
    m_tft = tft;
}

void TouchScreen::addControl(Control *ctl, uint32_t _x, uint32_t _y, int16_t _w, int16_t _h) {
    ctl->init(m_tft, _x, _y, _w, _h);
    m_listOfControls.push_back(ctl);
}

void TouchScreen::addControl(Control *ctl, Window &win) {
    ctl->init(m_tft, win);
    m_listOfControls.push_back(ctl);
}

void TouchScreen::addTouchControl(TouchControl *ctl, uint32_t _x, uint32_t _y, int16_t _w, int16_t _h) {
    m_listOfTouchControls.push_back(ctl);
    addControl(ctl, _x, _y, _w, _h);
}

void TouchScreen::addTouchControl(TouchControl *ctl, Window &win) {
    m_listOfTouchControls.push_back(ctl);
    addControl(ctl, win);
}

TouchControl *TouchScreen::checkForTouch() {
#ifdef TOUCH_CS
    if (m_tft->getTouch(&m_touchX, &m_touchY)) {
        for (m_touchCtlIter = m_listOfTouchControls.begin(); m_touchCtlIter != m_listOfTouchControls.end(); m_touchCtlIter++) {
            Window &ctlWin = (*m_touchCtlIter)->getWindow();
            if ((*m_touchCtlIter)->isShown() && TFTUtils::contains(ctlWin, m_touchX, m_touchY)) {
                (*m_touchCtlIter)->handleTouch(m_touchX, m_touchY, true);
                return (*m_touchCtlIter);
            }
        }
    }
#else
#pragma message("Touch is disabled")
#endif
    return NULL;
}

void TouchScreen::hideAll() {
    for (m_ctlIter = m_listOfControls.begin(); m_ctlIter != m_listOfControls.end(); m_ctlIter++) {
        (*m_ctlIter)->hide();
    }
}

void TouchScreen::showAll() {
    for (m_ctlIter = m_listOfControls.begin(); m_ctlIter != m_listOfControls.end(); m_ctlIter++) {
        (*m_ctlIter)->show();
    }
}

void TouchScreen::updateAll() {
    for (m_ctlIter = m_listOfControls.begin(); m_ctlIter != m_listOfControls.end(); m_ctlIter++) {
        (*m_ctlIter)->update();
    }
}