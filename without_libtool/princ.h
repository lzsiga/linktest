/* princ.h */

#ifndef PRINC_H
#define PRINC_H

#include "king.h"

class Princ: public King {
public:
    void intro() const;
    virtual void virtIntro() const { intro(); }
};

typedef Princ *Princ_Create_F();
typedef void   Princ_Intro_F(Princ *);

/* to use with dlopen/dlsym: */
extern "C" {
Princ_Create_F Princ_Create;
Princ_Intro_F  Princ_Intro;
}

#endif
