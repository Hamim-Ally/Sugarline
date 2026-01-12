#pragma once
#include "components/container.h"

class TuiApp {
public:
    TuiApp();
    void setRoot(Container* root);
    void run();
    void stop(); // user or UI can set this to exit main loop
private:
    Container* rootContainer = nullptr;
    bool running = true;
    void redraw();
};
