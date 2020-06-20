#include "List.h"

List *List::setNumItems(uint8_t _n, uint8_t _x, uint8_t _y) {
    m_numItems = _n;
    m_xDivs = _x > 0 ? _x : 1;
    m_yDivs = _y > 0 ? _y : 1;
    m_divX = m_win.width / m_xDivs; // size of each cell
    m_divY = m_win.height / m_yDivs;
    m_shown = false;
    return this;
}

void List::show() {
    uint8_t cellNum;
    for (cellNum = 0; cellNum < m_numItems; cellNum++)
        drawCell(cellNum);
    m_shown = true;
    return;
}

void List::getCell(uint8_t c) {
    m_currentDiv[0] = c % m_xDivs;
    m_currentDiv[1] = c / m_xDivs;
    m_currentCell.x = m_win.x + m_currentDiv[0] * m_divX;
    m_currentCell.y = m_win.y + m_currentDiv[1] * m_divY;
    m_currentCell.width = m_currentDiv[0] == m_xDivs - 1 ? m_win.width - (m_divX * m_currentDiv[0]) : m_divX;   // if last cell in row, use remaining pixels
    m_currentCell.height = m_currentDiv[1] == m_yDivs - 1 ? m_win.height - (m_divY * m_currentDiv[1]) : m_divY; // if last row in grid, use remaining pixels
    m_currentCellNum = c;
}

void List::drawCell(uint8_t _cellNum) {
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
    lbl.setBorderProperties(m_borderProps);
    lbl.show();
}