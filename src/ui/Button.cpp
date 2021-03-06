#include "Button.h"

void Button::show() {
    paintBG();
    m_shown = true;
    paintBorder();
    paintFill();
    paintText(); // Necessary to initialise m_textWin
    update();
}

void Button::update() {
    if (!m_shown) return;
    paintFill();
    paintText();
}