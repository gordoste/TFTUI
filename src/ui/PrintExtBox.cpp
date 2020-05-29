#include "PrintExtBox.h"

void PrintExtBox::init() {
    m_textPadding = 1;
    if (m_win == NULL) {
        m_cursor = {0, 0};
    } else {
        m_cursor = {m_win->x, m_win->y};
    }
}

void PrintExtBox::paintBG() {
    Control::paintBG();
    m_tft->setCursor(m_win->x + m_borderProps.width + m_textPadding, m_win->y + m_borderProps.width + m_textPadding);
    m_cursor = {m_tft->getCursorX(), m_tft->getCursorY()};
}

Point &PrintExtBox::getCursor() { return m_cursor; }

size_t PrintExtBox::write(uint8_t ch) {
    if (!m_shown) return 0;
    if (ch == 0) return 0;
    if (ch != '\r') {
        if (onWriteFn != NULL) {
            onWriteFn(m_tft);
        }
        m_tft->setCursor(m_cursor.x, m_cursor.y);
        m_tft->setTextColor(m_textColor);
        m_tft->write(ch);
        if (m_tft->getCursorY() >= m_tft->height()) paintBG();
        m_cursor = {m_tft->getCursorX(), m_tft->getCursorY()};
    }
    if (ch == '\r' || ch == '\n') m_cursor.x = m_win->x + m_borderProps.width + m_textPadding;
    return 1; // Processed 1 character
}

void PrintExtBox::show() {
    paintBG();
    m_shown = true;
    paintBorder();
}
