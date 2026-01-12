#pragma once
#include "element.h"
#include <string>

class Button : public Element {
public:
    explicit Button(const std::string& text);
    ~Button() override = default;

    void draw(bool focused) override;
    void handleInput(int key) override;

    void setText(const std::string& text) { label = text; }
    const std::string& getText() const { return label; }

private:
    std::string label;
};
