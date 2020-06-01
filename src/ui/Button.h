#ifndef _BUTTON_H
#define _BUTTON_H

#include "TouchControl.h"

class Button : public TouchControl {
private:
    uint16_t m_borderColor = TFT_WHITE;

public:
    using Control::init;
    void init() { m_borderProps = {TFT_WHITE, 1}; };

    void show();
    void update();

    uint16_t getBorderColor() { return m_borderColor; }
    void setBorderColor(uint16_t c) { m_borderColor = c; }
};

#endif // #ifndef _BUTTON_H