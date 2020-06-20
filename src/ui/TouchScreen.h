#ifndef _TOUCHSCREEN_H
#define _TOUCHSCREEN_H

#include <vector>

#include "Control.h"
#include "TFTUtils.h"
#include "TouchControl.h"

class TouchScreen {
public:
    void init(BasicLog *log, TFT_eSPI *tft);
    void addControl(Control *ctl, uint32_t _x, uint32_t _y, int16_t _w, int16_t _h);
    void addControl(Control *ctl, Window &win);
    void addTouchControl(TouchControl *ctl, uint32_t _x, uint32_t _y, int16_t _w, int16_t _h);
    void addTouchControl(TouchControl *ctl, Window &win);
    TouchControl *checkForTouch(); // Return the control that handled the touch
    void hideAll();
    void showAll();
    void updateAll();

private:
    BasicLog *m_log;
    TFT_eSPI *m_tft;
    std::vector<Control *> m_listOfControls;
    std::vector<TouchControl *> m_listOfTouchControls;
    uint16_t m_touchX, m_touchY;                        // Store touch co-ordinates
    std::vector<Control *>::iterator m_ctlIter;           // Iterator over controls
    std::vector<TouchControl *>::iterator m_touchCtlIter; // Iterator over controls
};

#endif // #ifndef _TOUCHSCREEN_H