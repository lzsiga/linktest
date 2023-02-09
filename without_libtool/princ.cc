/* princ.cc */

#include <cstdio>

#include "princ.h"

void Princ::intro() const {
    fprintf(stderr, "I'm only descendant of the king (this=%p)\n", (void *)this);
    ((King *)this)->intro();
};
