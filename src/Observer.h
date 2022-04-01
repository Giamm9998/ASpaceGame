//
// Created by gianmarco on 12/07/19.
//

#ifndef ASPACEGAME_OBSERVER_H
#define ASPACEGAME_OBSERVER_H


class Observer {
public:
    virtual ~Observer() = default;

    virtual void update() = 0;

    virtual void attach() = 0;

    virtual void detach() = 0;
};


#endif //ASPACEGAME_OBSERVER_H
