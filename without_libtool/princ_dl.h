/* princ_dl.h */

#ifndef PRINC_DL_H
#define PRINC_DL_H

#include "princ.h"

typedef Princ *Princ_Create_F(const char *name);
typedef void   Princ_Destroy_F(Princ *);
typedef void   Princ_Intro_F(const Princ *);

/* to use with dlopen/dlsym: */
extern "C" {
Princ_Create_F  Princ_Create;
Princ_Destroy_F Princ_Destroy;
Princ_Intro_F   Princ_Intro;
}

#endif
