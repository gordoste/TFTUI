#include "Label.h"

void Label::init() {
    m_borderProps = { TFT_WHITE, 1 };
}

void Label::show() {
    paintBG();
    m_shown = true;
    paintBorder();
    if (m_fillColor != m_backgroundColor) paintFill();
    paintText(); // Necessary to initialise m_textWin
    update();
}

void Label::update() {
    if (!m_shown) return;
    paintFill();
    paintText();
}

uint16_t Label::getMinWidth() {
    return m_textWin.width + 2*m_textPadding + 2*m_borderProps.width;
}