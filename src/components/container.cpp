#include "container.h"
#include <algorithm>

Container::Container() = default;

void Container::findFirstFocusable() {
    focusedIndex = -1;
    for (size_t i = 0; i < children.size(); ++i) {
        if (children[i]->canFocus()) {
            focusedIndex = i;
            break;
        }
    }
}

void Container::add(Element* child) {
    children.push_back(child);
    if (focusedIndex == -1) {
        findFirstFocusable();
    }
}

void Container::remove(Element* child) {
    children.erase(
        std::remove(children.begin(), children.end(), child),
        children.end()
    );
    if (focusedIndex >= (int)children.size()) {
        findFirstFocusable();
    }
}

void Container::draw(bool focused) {
    for (size_t i = 0; i < children.size(); ++i) {
        children[i]->draw(focused && (int)i == focusedIndex);
    }
}

void Container::handleInput(int key) {
    if (children.empty() || focusedIndex < 0) return;

    if (key == 9) { // Tab key
        // Find next focusable element
        int attempts = 0;
        do {
            focusedIndex = (focusedIndex + 1) % children.size();
            attempts++;
        } while (!children[focusedIndex]->canFocus() && attempts < (int)children.size());
    } else {
        children[focusedIndex]->handleInput(key);
    }
}
