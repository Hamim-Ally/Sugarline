#include "app.h"
#include "utils/terminal.h"
#include <iostream>

TuiApp::TuiApp() {}

void TuiApp::setRoot(Container* root) {
    rootContainer = root;
}

void TuiApp::redraw() {
    Terminal::moveCursor(1, 1);
    rootContainer->draw(true);
    std::cout.flush();
}

void TuiApp::run() {
    if (!rootContainer) return;
    Terminal::hideCursor();
    Terminal::clear();
    redraw();
    while (running) {
        int key = Terminal::getKey();
        rootContainer->handleInput(key);
        redraw();
    }
    Terminal::showCursor();
}

void TuiApp::stop() {
    running = false;
}
