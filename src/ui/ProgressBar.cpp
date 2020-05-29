#include "ProgressBar.h"

void ProgressBar::setProgress(uint32_t progress, uint32_t total) {
    while (total < 0x8000U) {
        progress <<= 1;
        total <<= 1;
    }                                           // Scale up to make math easier
    uint32_t step = total / (m_win->width - 2); // Figure out value of one pixel
    m_progress = progress / step;
    update();
}

void ProgressBar::show() {
    paintBG();
    m_shown = true;
    paintBorder();
    paintText(); // Necessary to initialise m_textWin
    update();
}

void ProgressBar::update() {
    if (!m_shown) return;
    if (m_progress == m_lastProgress) return;
    m_progressX = m_win->x + 1 + m_progress;
    uint32_t lastProgressX = m_win->x + 1 + m_lastProgress;
    Window fillWin;
    uint16_t fillColor = m_fillColor;
    fillWin.y = m_win->y + 1;
    fillWin.height = m_win->height - 2;
    if (m_progressX > lastProgressX) {
        fillWin.x = lastProgressX;
        fillWin.width = m_progressX - lastProgressX;
        fillColor = m_fillColor;
    }
    if (m_progressX < lastProgressX) {
        fillWin.x = m_progressX;
        fillWin.width = lastProgressX - m_progressX;
        fillColor = m_backgroundColor;
    }
    m_tft->fillRect(fillWin.x, fillWin.y, fillWin.width, fillWin.height, fillColor);
    if (TFTUtils::overlaps(m_textWin, fillWin)) paintText();

    m_lastProgress = m_progress;
}

void ProgressBar::before_paintText() {
    if (m_text[0] != '\0') {
        if (m_progressX < m_textWin.x) {
            m_tft->fillRect(m_textWin.x, m_textWin.y, m_textWin.width, m_textWin.height, m_backgroundColor);
        }
        if (m_progressX >= m_textWin.x && m_progressX < m_textWin.x + m_textWin.width) {
            m_tft->fillRect(m_textWin.x, m_textWin.y, m_progressX - m_textWin.x, m_textWin.height, m_fillColor);
            m_tft->fillRect(m_progressX + 1, m_textWin.y, m_textWin.x + m_textWin.width - m_progressX - 1, m_textWin.height, m_backgroundColor);
        }
        if (m_progressX >= m_textWin.x + m_textWin.width) {
            m_tft->fillRect(m_textWin.x, m_textWin.y, m_textWin.width, m_textWin.height, m_fillColor);
        }
    }
}