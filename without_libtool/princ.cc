/* princ.cc */

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "princ.h"

void Princ::intro() const {
    fprintf(stderr, "Princ %s in only a sun of the king\n", this->name);
/*  ((King *)this)->intro(); that's how we could call parent's intro */
};

Princ::Princ(const char *pname) {
    this->name= strdup(pname);
}

Princ::~Princ() {
    fprintf(stderr, "Princ %s terminates (this=%p)\n", this->name, this);
    free (this->name);
}
