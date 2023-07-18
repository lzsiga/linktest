/* king_dl.h */

#ifndef KING_DL_H
#define KING_DL_H

#include "king.h"

/* wrapper-functions that help to use the class as plugin */
/* i.e. with with dlopen/dlsym */
/* NB virtual methods are okay, as they are called through VMT */

typedef King *King_Create_F();
typedef void  King_Destroy_F(King *);
typedef void  King_Intro_F(const King *);

extern "C" {
King_Create_F  King_Create;
King_Destroy_F King_Destroy;
King_Intro_F   King_Intro;
}

#endif
