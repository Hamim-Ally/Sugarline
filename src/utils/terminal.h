#pragma once
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#endif

namespace Terminal {
    // Clear the screen
    inline void clear() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }

    // Move cursor to position (x, y) - 1-indexed
    inline void moveCursor(int x, int y) {
#ifdef _WIN32
        COORD coord;
        coord.X = static_cast<SHORT>(x - 1);
        coord.Y = static_cast<SHORT>(y - 1);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
        std::cout << "\033[" << y << ";" << x << "H";
        std::cout.flush();
#endif
    }

    // Hide cursor
    inline void hideCursor() {
#ifdef _WIN32
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#else
        std::cout << "\033[?25l";
        std::cout.flush();
#endif
    }

    // Show cursor
    inline void showCursor() {
#ifdef _WIN32
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = true;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#else
        std::cout << "\033[?25h";
        std::cout.flush();
#endif
    }

    // Get a single key press (handles arrow keys on Windows)
    inline int getKey() {
#ifdef _WIN32
        int key = _getch();
        // Handle Windows arrow keys (two-byte sequence: 224/0 followed by actual key)
        if (key == 224 || key == 0) {
            key = _getch();
        }
        return key;
#else
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
#endif
    }

    // Set text color (Windows only, ANSI codes for Unix)
    inline void setColor(int color) {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
#else
        std::cout << "\033[" << color << "m";
        std::cout.flush();
#endif
    }

    // Reset text color
    inline void resetColor() {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // Default gray
#else
        std::cout << "\033[0m";
        std::cout.flush();
#endif
    }
}
