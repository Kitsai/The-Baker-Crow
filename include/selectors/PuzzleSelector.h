#ifndef PuzzleSelector_H
#define PuzzleSelector_H

#include <stack>
#include "selectors/Selector.h"

class PuzzleSelector : public Selector {
    public:
        PuzzleSelector(std::vector<std::shared_ptr<Button>> buttons);
    
        void Update(float dt) override;
};

#endif
