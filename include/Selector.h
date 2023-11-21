#ifndef Selector_H
#define Selector_H

#include "Component.h"
class Selector : public Component {
    int selected;
    void RenderSelected();
public:
    Selector(GameObject& assoc);
    ~Selector();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
};

#endif