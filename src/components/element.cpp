#include "element.h"

Element::~Element() {
    emit("destroy");
}
