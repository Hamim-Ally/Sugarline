#include <iostream>
#include "menu.h"

Menu::Menu(std::vector<std::string> opts) : options(std::move(opts)) {}

void Menu::draw(bool focused) {
    for (size_t i = 0; i < options.size(); ++i) {
        if (i == selected && focused) {
            std::cout << "> " << options[i];
        } else {
            std::cout << "  " << options[i];
        }
        std::cout << "\n";
    }
}

void Menu::handleInput(int key) {
    // Arrow keys on Windows: 72 = Up, 80 = Down
    // These are passed directly from main after handling two-byte sequences
    if (key == 72 || key == 'w' || key == 'W') {  // Up arrow or 'w'
        selected = (selected == 0) ? options.size() - 1 : selected - 1;
    } else if (key == 80 || key == 's' || key == 'S') {  // Down arrow or 's'
        selected = (selected + 1) % options.size();
    } else if (key == 13 || key == 32) {  // Enter or Space
        emit<int>("select", static_cast<int>(selected));
    }
}
