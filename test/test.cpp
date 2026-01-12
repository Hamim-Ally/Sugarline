#include <iostream>
#include "app.h"
#include "menu.h"
#include "button.h"
#include "label.h"

int main() {
    Label title("--- Sugar Shell TUI Library ---");
    Menu menu({"New", "Open", "Save", "Exit"});
    Button btn("Confirm");

    Container root;
    root.add(&title);
    root.add(&menu);
    root.add(&btn);

    // When the user selects Exit, stop the event loop
    menu.on<int>("select", std::function<void(int)>([&](int i) {
        if (i == 3) {
            // Access the global/static app pointer, or use a lambda/callback
            // In a real app, inject an app pointer or implement via a stop event
        }
    }));

    btn.on<>("click", std::function<void()>([]() {
        std::cout << "\nConfirm button clicked!\n";
    }));

    TuiApp app;
    app.setRoot(&root);
    app.run();
    return 0;
}
