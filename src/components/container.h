#pragma once
#include "element.h"
#include <vector>

class Container : public Element {
public:
    Container();
    ~Container() override = default;

    void add(Element* child);
    void remove(Element* child);

    void draw(bool focused) override;
    void handleInput(int key) override;

    size_t size() const { return children.size(); }
    bool empty() const { return children.empty(); }

private:
    std::vector<Element*> children;
    int focusedIndex = -1;
    
    void findFirstFocusable();
};
