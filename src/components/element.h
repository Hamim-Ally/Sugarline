#pragma once
#include "event_emitter.h"

class Element : public EventEmitter {
public:
    virtual void draw(bool focused) = 0;
    virtual void handleInput(int key) {}
    virtual bool canFocus() { return true; }
    virtual ~Element();
};
