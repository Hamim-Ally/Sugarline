#include "button.h"
#include <iostream>

Button::Button(const std::string& text) : label(text) {}

void Button::draw(bool focused) {
    if (focused) {
        std::cout << "> [" << label << "]";
    } else {
        std::cout << "  [" << label << "]";
    }
    std::cout << "\n";
}

void Button::handleInput(int key) {
    if (key == 13 || key == 32) {  // Enter or Space
        emit("click");
    }
}
