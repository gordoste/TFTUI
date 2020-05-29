#ifndef _PROGRESS_BAR_H
#define _PROGRESS_BAR_H

#include "Control.h"

class ProgressBar : public Control {
private:
    uint16_t m_progress = 0;     // How many pixels of progress to paint
    uint16_t m_lastProgress = 0; // How many pixels of progress we painted last time
    uint32_t m_progressX;        // Where to paint the bar to (absolute co-ordinate)
    uint16_t m_fillColor = TFT_BLUE;

public:
    using Control::init;
    void init() { m_borderProps = { TFT_WHITE, 1 }; };
    void setProgress(uint32_t progress, uint32_t total);
    void show();
    void update();

    uint16_t getFillColor() { return m_fillColor; }
    void setFillColor(uint16_t c) { m_fillColor = c; }

    void before_paintText();
};

#endif // #ifndef _PROGRESS_BAR_H