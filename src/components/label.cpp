#include "label.h"
#include <iostream>

Label::Label(const std::string& text) : text(text) {}

void Label::draw(bool focused) {
    (void)focused; // A label's appearance doesn't change with focus.
    std::cout << text << "\n";
}
