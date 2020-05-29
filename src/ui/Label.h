#ifndef _LABEL_H
#define _LABEL_H

#include "Control.h"

class Label : public Control {
private:
    uint16_t m_borderColor = TFT_WHITE;

public:
    void init();

    void show();
    void update();

    uint16_t getBorderColor() { return m_borderColor; }
    void setBorderColor(uint16_t c) { m_borderColor = c; }

    uint16_t getMinWidth();
};

#endif // #ifndef _LABEL_H