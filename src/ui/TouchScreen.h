#ifndef _TOUCHSCREEN_H
#define _TOUCHSCREEN_H

#include <vector>

#include "Control.h"
#include "TFTTypes.h"
#include "TFTUtils.h"
#include "TouchControl.h"

class TouchScreen {
public:
    void addControl(Control *ctl, uint32_t _x, uint32_t _y, int16_t _w, int16_t _h);
    void addControl(Control *ctl, Window &win);
    void addTouchControl(TouchControl *ctl, uint32_t _x, uint32_t _y, int16_t _w, int16_t _h);
    void addTouchControl(TouchControl *ctl, Window &win);
    TouchControl *checkForTouch(); // Return the control that handled the touch
    void hideAll();
    void showAll();
    void updateAll();

    virtual void setup(TFT_eSPI *tft, DataProvider _dataProvider = DEFAULT_DATA_PROVIDER, ActionHandler _actionCallback = DEFAULT_ACTION_HANDLER) {
        m_tft = tft;
        m_dataProvider = _dataProvider;
        m_actionCallback = _actionCallback;
    };
    virtual void show() = 0; // Call when first showing this screen
    virtual void loop() = 0;
    virtual void refresh() = 0; // Data updated, refresh data displayed

    static const void *DEFAULT_DATA_PROVIDER(uint16_t elem_num) { return (const void *)NULL; };
    static void DEFAULT_ACTION_HANDLER(int action, void *arg) { return; };

protected:
    TFT_eSPI *m_tft;
    ActionHandler m_actionCallback;
    DataProvider m_dataProvider;
    std::vector<Control *> m_listOfControls;
    std::vector<TouchControl *> m_listOfTouchControls;
    std::vector<Control *>::iterator m_ctlIter;           // Iterator over controls
    std::vector<TouchControl *>::iterator m_touchCtlIter; // Iterator over controls
private:
    uint16_t m_touchX, m_touchY; // Store touch co-ordinates
};

#endif // #ifndef _TOUCHSCREEN_H