#ifndef _PRINTEXTBOX_H
#define _PRINTEXTBOX_H

#include "PrintExt.h"
#include "Control.h"

class PrintExtBox : public PrintExt, public Control {
public:
    void init();
    void paintBG();
    void show();
    Point &getCursor();
    void onWrite(TFTHandler fn) { onWriteFn = fn; };
    virtual size_t write(uint8_t ch);

private:
    Point m_cursor;
    TFTHandler onWriteFn = NULL;
};

#endif // #ifndef _PRINTEXTBOX_H
