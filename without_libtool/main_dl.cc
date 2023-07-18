/* main_dl.cc */

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <dlfcn.h>

#include "king_dl.h"
#include "princ_dl.h"

static void    *e_dlopen(const char *name);
static intptr_t e_dlsym(void *, const char *name);

int main (void) {
    void *lib=  e_dlopen("libwrapper.so");

    King_Create_F   *King_Create_FP=   (King_Create_F   *)e_dlsym(lib, "King_Create");
    King_Destroy_F  *King_Destroy_FP=  (King_Destroy_F  *)e_dlsym(lib, "King_Destroy");
    King_Intro_F    *King_Intro_FP=    (King_Intro_F    *)e_dlsym(lib, "King_Intro");
    Princ_Create_F  *Princ_Create_FP=  (Princ_Create_F  *)e_dlsym(lib, "Princ_Create");
    Princ_Destroy_F *Princ_Destroy_FP= (Princ_Destroy_F *)e_dlsym(lib, "Princ_Destroy");
    Princ_Intro_F   *Princ_Intro_FP=   (Princ_Intro_F   *)e_dlsym(lib, "Princ_Intro");

    King *Mathias= (*King_Create_FP)();
    (*King_Intro_FP)(Mathias);

    Princ *Leslie= (*Princ_Create_FP)("Leslie");
    (*Princ_Intro_FP)(Leslie);

    King *leslie_as_baseclass= Leslie;
    printf("\ncalling King::intro (non-virtual method) on down-casted Princ:\n");
    (*King_Intro_FP)(leslie_as_baseclass);

    printf("\ncalling virtIntro (virtual method) on down-casted Princ:\n");
    leslie_as_baseclass->virtIntro();

    (*King_Destroy_FP)(Mathias);
    (*Princ_Destroy_FP)(Leslie);

    /* in this example we have virtual destructors, so it could be simply:
    delete Mathias;
    delete Leslie;
    */
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
