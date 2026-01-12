#pragma once
#include "element.h"
#include <string>

class Label : public Element {
public:
    Label(const std::string& text);
    ~Label() override = default;

    void draw(bool focused) override;
    bool canFocus() override { return false; }

    void setText(const std::string& t) { text = t; }
    const std::string& getText() const { return text; }

private:
    std::string text;
};
