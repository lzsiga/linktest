/* king.cc */

#include <cstdio>

#include "king.h"

void King::intro() const {
    fprintf(stderr, "I am the king (this=%p)\n", (void *)this);
}

King::~King() {
    fprintf(stderr, "King at %p terminates\n", (void *)this);
}
