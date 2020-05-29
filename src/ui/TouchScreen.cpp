#include "TouchScreen.h"

void TouchScreen::init(BasicLog *log, TFT_eSPI *tft) {
    m_log = log;
    m_tft = tft;
}

void TouchScreen::addControl(Control *ctl, Window *win) {
    ctl->init(m_log, m_tft, win);
    m_listOfControls.push_back(ctl);
}

void TouchScreen::addTouchControl(TouchControl *ctl, Window *win) {
    m_listOfTouchControls.push_back(ctl);
    addControl(ctl, win);
}

TouchControl *TouchScreen::checkForTouch() {
    if (m_tft->getTouch(&m_touchX, &m_touchY)) {
        for (m_touchCtlIter = m_listOfTouchControls.begin(); m_touchCtlIter != m_listOfTouchControls.end(); m_touchCtlIter++) {
            Window *ctlWin = (*m_touchCtlIter)->getWindow();
            if ((*m_touchCtlIter)->isShown() && TFTUtils::contains((*ctlWin), m_touchX, m_touchY)) {
                (*m_touchCtlIter)->handleTouch(m_touchX, m_touchY, true);
                return (*m_touchCtlIter);
            }
        }
    }
    return NULL;
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