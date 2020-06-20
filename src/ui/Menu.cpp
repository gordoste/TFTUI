#include "Menu.h"

Menu *Menu::setSelectedBorderProps(LineProperties &_props) {
    m_selectedBorderProps.color = _props.color;
    m_selectedBorderProps.width = _props.width;
    return this;
}

Menu *Menu::setNumChoices(uint8_t _n, uint8_t _x, uint8_t _y) {
    m_numChoices = _n;
    m_xDivs = _x > 0 ? _x : 1;
    m_yDivs = _y > 0 ? _y : 1;
    m_divX = m_win.width / m_xDivs; // size of each cell
    m_divY = m_win.height / m_yDivs;
    m_shown = false;
    setSelectedChoice(-1);
    return this;
}

void Menu::show() {
    uint8_t cellNum;
    for (cellNum = 0; cellNum < m_numChoices; cellNum++)
        drawCell(cellNum);
    m_touchHandler = [this](uint16_t x, uint16_t y, bool absolute) {
        if (!absolute) { // handle relative co-ordinates
            x += m_win.x;
            y += m_win.y;
        }

        int8_t sel = -1;
        for (uint8_t t = 0; t < m_numChoices; t++) {
            getCell(t);
            if (TFTUtils::contains(m_currentCell, x, y)) {
                sel = t;
            }
        }
        setSelectedChoice(sel);
    };
    m_shown = true;
    return;
}

int8_t Menu::getSelectedChoice() { return m_selectedChoice; }
Menu *Menu::setSelectedChoice(int8_t _cellNum) {
    if (_cellNum == m_selectedChoice) return this;
    if (_cellNum >= m_numChoices) return this;
    int8_t oldSel = m_selectedChoice;
    m_selectedChoice = _cellNum;
    if (m_shown) {
        if (oldSel != -1) drawCell(oldSel);                     // Redraw previously selected cell
        if (m_selectedChoice != -1) drawCell(m_selectedChoice); // Draw newly selected cell
    }
    return this;
};

void Menu::getCell(uint8_t c) {
    m_currentDiv[0] = c % m_xDivs;
    m_currentDiv[1] = c / m_xDivs;
    m_currentCell.x = m_win.x + m_currentDiv[0] * m_divX;
    m_currentCell.y = m_win.y + m_currentDiv[1] * m_divY;
    m_currentCell.width = m_currentDiv[0] == m_xDivs - 1 ? m_win.width - (m_divX * m_currentDiv[0]) : m_divX;   // if last cell in row, use remaining pixels
    m_currentCell.height = m_currentDiv[1] == m_yDivs - 1 ? m_win.height - (m_divY * m_currentDiv[1]) : m_divY; // if last row in grid, use remaining pixels
    m_currentCellNum = c;
}

void Menu::drawCell(uint8_t _cellNum) {
    getCell(_cellNum);
    Label lbl = Label();
    lbl.Control::init(m_tft, m_currentCell);
    lbl.setBackgroundColor(m_backgroundColor).setFillColor(m_fillColorGetter(m_currentCellNum));
    lbl.copyTextPropsFrom(*this);
    const char *labelStr = NULL;
    if (m_labelGetter != NULL) {
        labelStr = m_labelGetter(m_currentCellNum);
        if (labelStr != NULL && strlen(labelStr) > 0) {
            lbl.setText(labelStr);
        }
    }
    if (m_currentCellNum == m_selectedChoice) {
        lbl.setBorderProperties(m_selectedBorderProps);
    }
    else {
        lbl.setBorderProperties(m_borderProps);
    }
    lbl.show();
}