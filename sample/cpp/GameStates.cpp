#include "Game.h"
#include "StateMachineMacros.h"
namespace kms {

// [state2cpp]__common__

std::string Game::DumpState() const { return TO_STRING(); }
void Game::ExecState() { EXEC(); }
void Game::StartState() {
}

// [state2cpp]StartGame:bf4b1d8f740dc621fbef6989ed442841bf0e6810

void Game::StateStartGame() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitPlayerData);
}

// [state2cpp]WaitPlayerData:00db9a0549bd73a4c241f1ef5bdd5c069770b3f0

void Game::StateWaitPlayerData() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  tutorial battle?
        SWITCH_TO(StateWaitTutorialBattleData);
    } else {
        SWITCH_TO(StateStartBuilding);
    }
}

// [state2cpp]StartBuilding:9dd1f6b28d7b8b0fb63a3d23be0e4c40b89e3cb6

void Game::StateStartBuilding() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateBuilding);
}

// [state2cpp]WaitTutorialBattleData:ba815b36cec8d8421e9250658e56f95f16a408e6

void Game::StateWaitTutorialBattleData() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  data loaded?
        SWITCH_TO(StateStartBattle);
    }
}

// [state2cpp]StartBattle:62691ba27534b258b5dbf73a34287c89ce94869b

void Game::StateStartBattle() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateBattle);
}

// [state2cpp]Building:8df9847bf20bff77938c841450325db7c1ede2b7

void Game::StateBuilding() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Button for Battle is pressed?
        SWITCH_TO(StateStartBattle);
    } else if (false) {  //  Someone asks replay?
        SWITCH_TO(StateStartReplay);
    } else if (false) {  //  Button for Visit is pressed?
        SWITCH_TO(StateStartVisit);
    } else if (false) {  //  Tutorial battle?
        SWITCH_TO(StateWaitTutorialBattleData);
    }
}

// [state2cpp]StartReplay:9da260ca348d0cc2c98baaa72dba8e3932014307

void Game::StateStartReplay() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateReplay);
}

// [state2cpp]StartVisit:c73e45d56bf3ddc03ccd64eb6805482aaa2876d9

void Game::StateStartVisit() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateVisit);
}

// [state2cpp]Battle:9bb81be513fc30ff95111ad766b78fc69f5c3b5a

void Game::StateBattle() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Battle is finished?
        SWITCH_TO(StateStartBuilding);
    } else if (false) {  //  Battle is canceled?
        SWITCH_TO(StateStartGame);
    }
}

// [state2cpp]Replay:86bb9bc82225c8fe0575f20e8eebd82f768e1048

void Game::StateReplay() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Replay is finished?
        SWITCH_TO(StateStartGame);
    }
}

// [state2cpp]Visit:7b94d9bef1f918dd988a9ffeb4ae2df5ad229b07

void Game::StateVisit() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Button for Building is pressed?
        SWITCH_TO(StateStartGame);
    }
}
} // namespace kms
