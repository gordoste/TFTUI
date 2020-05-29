#ifndef _MENU_H
#define _MENU_H

#include "Label.h"
#include "TouchControl.h"

typedef std::function<const char *(uint8_t cell_nr)> TLabel_Getter;
typedef std::function<uint32_t(uint8_t cell_nr)> TColor_Getter;

class Menu : public TouchControl {
    static const char *DEFAULT_LABEL_GETTER(uint8_t _cellNum) { return "-"; }
    static uint32_t MENU_WHITE_GETTER(uint8_t _cellNum) { return TFT_WHITE; }
    static uint32_t MENU_BLACK_GETTER(uint8_t _cellNum) { return TFT_BLACK; }

public:
    void init(){};
    void show();
    bool isShown() { return m_shown; }

    int8_t getSelectedChoice();        // choice is 0-based
    Menu *setSelectedChoice(int8_t c); // choice is 0-based

    Menu *setSelectedBorderProps(LineProperties &_props);

    Menu *setNumChoices(uint8_t _n, uint8_t _x, uint8_t _y);              // Do this right before show() as it calculates cell sizes
    Menu *setNumChoices(uint8_t _n) { return setNumChoices(_n, 1, _n); }; // Creates menu with 1 column
    uint8_t getNumChoices() { return m_numChoices; }

    Menu *setLabelGetter(TLabel_Getter _lg) {
        m_labelGetter = _lg;
        return this;
    }
    Menu *setFillColorGetter(TColor_Getter _cg) {
        m_fillColorGetter = _cg;
        return this;
    }

protected:
    uint32_t m_divX, m_divY;
    uint8_t m_currentDiv[2] = {0, 0}; // which cell are we drawing
    uint8_t m_xDivs, m_yDivs;
    int8_t m_selectedChoice;
    uint8_t m_numChoices;
    Window m_currentCell;
    uint8_t m_currentCellNum;
    TLabel_Getter m_labelGetter = DEFAULT_LABEL_GETTER;
    TColor_Getter m_fillColorGetter = MENU_BLACK_GETTER;
    LineProperties m_selectedBorderProps = {TFT_RED, 3};

private:
    void getCell(uint8_t c);
    void drawCell(uint8_t _cellNum);
};

#endif //#ifndef _MENU_H