#include <k5/k5.h>
#include "modelframe.h"

int main(int argc, char** argv) {
    CEngine& game = CEngine::Instance();
    game.CreateWindow("wintermute", 1280, 720, false);
    game.ChangeFrame(ModelFrame::Instance());
    while (game.Running()) {
        game.Tick();
    }
    game.Cleanup();
    return 0;
}
