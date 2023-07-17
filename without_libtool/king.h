/* king.h */

#ifndef KING_H
#define KING_H

class King {
public:
    void intro() const;
    virtual void virtIntro() const { intro(); }
};

typedef King *King_Create_F();
typedef void  King_Intro_F(King *);

/* to use with dlopen/dlsym: */
extern "C" {
King_Create_F King_Create;
King_Intro_F  King_Intro;
}

#endif
