//
// Created by gianmarco on 12/07/19.
//

#ifndef ASPACEGAME_SUBJECT_H
#define ASPACEGAME_SUBJECT_H


#include "Observer.h"

class Subject {
public:
    virtual ~Subject() = default;

    virtual void subscribe(Observer *o) = 0;

    virtual void unsubscribe(Observer *o) = 0;

    virtual void notify() = 0;
};


#endif //ASPACEGAME_SUBJECT_H
