#pragma once
#include "element.h"
#include <vector>
#include <string>

class Menu : public Element {
public:
    explicit Menu(std::vector<std::string> opts);
    ~Menu() override = default;

    void draw(bool focused) override;
    void handleInput(int key) override;

    size_t getSelected() const { return selected; }
    void setSelected(size_t index) { 
        if (index < options.size()) selected = index; 
    }
    const std::vector<std::string>& getOptions() const { return options; }

private:
    std::vector<std::string> options;
    size_t selected = 0;
};
