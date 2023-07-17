/* main_dl.cc */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

#include "king.h"
#include "princ.h"

static void    *e_dlopen(const char *name);
static intptr_t e_dlsym(void *, const char *name);

int main (void) {
    void *libKing=  e_dlopen("libking.so");
    void *libPrinc= e_dlopen("libprinc.so");

    King_Create_F  *King_Create_FP=  (King_Create_F  *)e_dlsym(libKing,  "King_Create");
    King_Intro_F   *King_Intro_FP=   (King_Intro_F   *)e_dlsym(libKing,  "King_Intro");
    Princ_Create_F *Princ_Create_FP= (Princ_Create_F *)e_dlsym(libPrinc, "Princ_Create");
    Princ_Intro_F  *Princ_Intro_FP=  (Princ_Intro_F  *)e_dlsym(libPrinc, "Princ_Intro");

    King *Mathias= (*King_Create_FP)();
    (*King_Intro_FP)(Mathias);

    Princ *Leslie= (*Princ_Create_FP)();
    (*Princ_Intro_FP)(Leslie);

    King *leslie_as_baseclass= Leslie;
    printf("\ncalling intro (non-virtual method):\n");
    leslie_as_baseclass->intro();
    printf("\ncalling virtIntro (virtual method):\n");
    leslie_as_baseclass->virtIntro();

    return 0;
}

static void *e_dlopen(const char *name) {
    void *h= dlopen(name, RTLD_GLOBAL|RTLD_LAZY);
    if (!h) {
        fprintf(stderr, "*** dlopen('%s') error %s\n",
            name, dlerror());
        exit(12);
    }
    return h;
}

static intptr_t e_dlsym(void *hlib, const char *name) {
    void *fp= dlsym(hlib, name);
    if (!fp) {
        fprintf(stderr, "*** dlsym('%s') error %s\n",
            name, dlerror());
        exit(12);
    }
    return (intptr_t)fp;
}
