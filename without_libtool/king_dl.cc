/* king_dl.cc */

#include <cstdio>

#include "king_dl.h"

extern "C" {
King *King_Create () { return new King(); }
void  King_Destroy (King *self) { delete self; }
void  King_Intro (const King *self) { self->intro(); }
}
