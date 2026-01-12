# Sugarline - A Terminal User Interface (TUI) Library

A lightweight, header-only C++ TUI library for creating interactive terminal applications with components like buttons, menus, labels, and containers.

## Features

- **Component-based architecture**: Easy-to-use UI components (Button, Menu, Label, Container)
- **Event-driven**: Event emitter pattern for handling user interactions
- **Focus management**: Automatic focus handling and navigation between components
- **Cross-platform**: Works on Windows (MSVC) and Unix-like systems
- **Minimal dependencies**: Uses only standard C++ and platform-specific APIs

## Components

### Element (Base Class)
- Base class for all UI components
- Provides event emission capabilities
- Handles drawing and input handling

### Container
- Groups multiple child elements
- Manages focus and input routing
- Supports Tab key navigation between focusable elements

### Button
- Interactive button component
- Emits "click" event on Enter or Space
- Visual focus indicator

### Menu
- Dropdown-style menu with selectable options
- Navigation with arrow keys or W/S keys
- Emits "select" event with selected index

### Label
- Static text display
- Non-focusable element

## Usage Example

```cpp
#include "container.h"
#include "menu.h"
#include "button.h"
#include "label.h"
#include "utils/terminal.h"

int main() {
    Terminal::hideCursor();

    Label title("--- My TUI App ---");
    Menu menu({"New", "Open", "Save", "Exit"});
    Button btn("Confirm");

    Container root;
    root.add(&title);
    root.add(&menu);
    root.add(&btn);

    menu.on<int>("select", [&](int i) {
        if (i == 3) exit(0);
    });

    btn.on<>("click", []() {
        std::cout << "Button clicked!\n";
    });

    while (true) {
        Terminal::clear();
        root.draw(true);
        
        int key = Terminal::getKey();
        root.handleInput(key);
    }

    Terminal::showCursor();
    return 0;
}
```

## Building

Using SugarBuilder:
```bash
cd sugar-shell
sugar build
```

Or manually with MSVC (Windows):
```bash
cl /EHsc /std:c++17 src/main.cpp src/components/*.cpp src/events/*.cpp /Fe:bin/sugar-shell.exe
```

## Running

```bash
./bin/sugar-shell.exe
```

## Controls

- **Tab**: Navigate between focusable elements
- **Arrow Keys / W/S**: Navigate menu items
- **Enter / Space**: Activate buttons or select menu items
- **ESC**: Exit (can be customized in your application)

## Architecture

The library uses an event-driven architecture:
- Elements inherit from `EventEmitter` for event handling
- Events are typed with template parameters (e.g., `on<int>("select", handler)`)
- Components can emit events and register handlers
- Focus is managed automatically by containers

## License

This project is created with SugarBuilder.

