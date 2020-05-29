#ifndef _TOUCHSCREEN_H
#define _TOUCHSCREEN_H

#include <list>

#include "Control.h"
#include "TFTUtils.h"
#include "TouchControl.h"

class TouchScreen {
public:
    void init(BasicLog *log, TFT_eSPI *tft);
    void addControl(Control *ctl, Window *win);
    void addTouchControl(TouchControl *ctl, Window *win);
    TouchControl *checkForTouch(); // Return the control that handled the touch
    void showAll();
    void updateAll();

private:
    BasicLog *m_log;
    TFT_eSPI *m_tft;
    std::list<Control *> m_listOfControls;
    std::list<TouchControl *> m_listOfTouchControls;
    uint16_t m_touchX, m_touchY;                        // Store touch co-ordinates
    std::list<Control *>::iterator m_ctlIter;           // Iterator over controls
    std::list<TouchControl *>::iterator m_touchCtlIter; // Iterator over controls
};

#endif // #ifndef _TOUCHSCREEN_H