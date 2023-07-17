/* main.cc */

#include <cstdio>

#include "king.h"
#include "princ.h"

int main (void) {
    King Mathias;
    Mathias.intro();

    Princ Leslie;
    Leslie.intro();

    King *leslie_as_baseclass= &Leslie;
    printf("\ncalling intro (non-virtual method):\n");
    leslie_as_baseclass->intro();
    printf("\ncalling virtIntro (virtual method):\n");
    leslie_as_baseclass->virtIntro();

    return 0;
}
