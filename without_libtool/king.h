/* king.h */

#ifndef KING_H
#define KING_H

class King {
public:
    void intro() const;
    virtual void virtIntro() const { intro(); }
    virtual ~King();
};

#endif
