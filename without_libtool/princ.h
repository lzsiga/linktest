/* princ.h */

#ifndef PRINC_H
#define PRINC_H

#include "king.h"

class Princ: public King {
public:
    Princ(const char *pname);
    virtual ~Princ();
    void intro() const;
    virtual void virtIntro() const { intro(); };
private:
    char *name;
};

#endif
