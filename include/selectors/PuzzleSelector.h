#ifndef PuzzleSelector_H
#define PuzzleSelector_H

#include "Component.h"

class PuzzleSelector : public Component {
    int selected;
    void RenderSelected();
public:
    PuzzleSelector(GameObject& assoc);
    ~PuzzleSelector();

    void Update(float dt);
    void Render();
    bool Is(std::string type);
};

#endif
