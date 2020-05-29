#ifndef _CONTROL_H
#define _CONTROL_H

#include "TFTUtils.h"

#include "BasicLog.h"

class Control {
protected:
    TFT_eSPI *m_tft;
    Window *m_win;
    BasicLog *m_log;
    bool m_shown = false;
    LineProperties m_borderProps = DefaultBorder;
    uint16_t m_backgroundColor = TFT_BLACK;
    uint16_t m_fillColor = TFT_BLUE;
    uint8_t m_textFont = 1;
    uint8_t m_textAlign = TL_DATUM;
    uint8_t m_textPadding = 0;
    uint16_t m_textColor = TFT_WHITE;
    uint16_t m_textWidth = 0;
    Window m_textWin = {0, 0, 0, 0}; // Area the text takes up
    const char *m_text = NULL;
#ifdef LOAD_GFXFF
    GFXfont *m_gfxFont = NULL;
#endif

public:
    Control &init(BasicLog *log, TFT_eSPI *tft, Window *win); // Use TouchScreen.addControl() instead of calling directly
    virtual void init() = 0;                                  // Initialise any variables in child class
    Window *getWindow() { return m_win; }
    bool isShown() { return m_shown; }
    virtual void show() = 0;          // Pure virtual function that needs to be implemented in child
    virtual void update() { show(); } // Can be over-ridden
    virtual void hide();

    uint16_t getBackgroundColor() { return m_backgroundColor; }
    Control &setBackgroundColor(uint16_t c) {
        m_backgroundColor = c;
        return *this;
    }

    uint16_t getFillColor() { return m_fillColor; }
    Control &setFillColor(uint16_t c) {
        m_fillColor = c;
        return *this;
    }

    Control &setText(const char *str);
    Control &setTextAlign(uint8_t textAlign) {
        m_textAlign = textAlign;
        return *this;
    }
    uint8_t getTextAlign() { return m_textAlign; }
    Control &setTextColor(uint16_t color) {
        m_textColor = color;
        return *this;
    }
    uint16_t getTextColor() { return m_textColor; }
    Control &setTextPadding(uint8_t textPadding) {
        m_textPadding = textPadding;
        return *this;
    }
    uint8_t getTextPadding() { return m_textPadding; }

#ifdef LOAD_GFXFF
    GFXfont *getFreeFont() { return m_gfxFont; }
    Control &setFreeFont(const GFXfont *f = NULL);
    uint8_t getTextFont() { return m_textFont; }
    Control &setTextFont(uint8_t font);
#else
    uint8_t getFreeFont() { return m_textFont; }
    uint8_t getTextFont() { return m_textFont; }
    Control &setFreeFont(uint8_t font);
    Control &setTextFont(uint8_t font);
#endif

    Control &setBorderProperties(LineProperties &props) {
        m_borderProps = props;
        return *this;
    }
    LineProperties getBorderProperties() { return m_borderProps; }

    void copyTextPropsFrom(Control &ctl); // Call all setTextXXX() functions and setFreeFont(), get the  values from the control passed

protected:
    void paintBG();
    void updateTFTFont();     // Set the font on the TFT before drawing text
    virtual void paintText(); // Display text. Can be over-ridden
    virtual void before_paintText(){};
    virtual void after_paintText(){};
    virtual void paintBorder();
    virtual void paintFill();
    void paintBorderAndFill() { paintBorder(); paintFill(); };
};

#endif // #ifndef _CONTROL_H
