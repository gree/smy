#include "Main.h"
namespace kms {

#define TO_STRING() \
  _stateMachine.to_string()
#define EXEC() \
  _stateMachine.Exec()
#define SPAWN(state) \
  _stateMachine.Spawn(std::make_pair([&]{state();}, #state))
#define SWITCH_TO(state) \
  _stateMachine.SwitchTo(std::make_pair([&]{state();}, #state))
#define YIELD_TO(state) \
  _stateMachine.YieldTo(std::make_pair([&]{state();}, #state))
#define EXIT() _stateMachine.Exit()

std::string Main::DumpState() const {
    return TO_STRING();
}

void Main::ExecState() {
    EXEC();
}

void Main::StartState() {
    SPAWN(StateStart);
}

// [state2cpp]Start:247d6b64bed69a9184cded5336827b253db2ae0d

void Main::StateStart() {

    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateInit);
}

// [state2cpp]Init:f4b63a8d8496112aa285662da2b7804c5ac031dd

void Main::StateInit() {

    //  TODO: Something to execute every frame while this state.

    if (false) { //  application version is same
        SWITCH_TO(StateAppInit);
    } else if (false) {  //  application version is changed?
        SWITCH_TO(StateInstallFirstPrioriryAssets);
    }
}

// [state2cpp]AppInit:2468ddadfec5a389645c0046d70dd0e692e53020

void Main::StateAppInit() {

    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitAppInit);
}

// [state2cpp]InstallFirstPrioriryAssets:4d29de41e19021ca8365df3b82047e85fe3a8641

void Main::StateInstallFirstPrioriryAssets() {

    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitInstallingFirstPriorityAssets);
}

// [state2cpp]WaitInstallingFirstPriorityAssets:c4810109fc44b25e63e76b9aa08a94d7ffa00e56

void Main::StateWaitInstallingFirstPriorityAssets() {

    //  TODO: Something to execute every frame while this state.

    if (false) { //  Priority assets are installed
        SWITCH_TO(StateShowTitle);
    } else if (false) {  //  Priority assets are installed and first launch?
        SWITCH_TO(StateStartAgreementDialog);
    }
}

// [state2cpp]StartAgreementDialog:154c36ee47084edf2e313f31075b7a661ac3cb03

void Main::StateStartAgreementDialog() {

    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitAgreementDialog);
}

// [state2cpp]ShowTitle:1594805f7c63bc9294c39e591867835e201cb165

void Main::StateShowTitle() {

    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateInstallAllStartUpAssets);
}

// [state2cpp]WaitAgreementDialog:4fe6fe3f12fbb2b65637f062f2bcf724893c369b

void Main::StateWaitAgreementDialog() {

    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Agreed?
        SWITCH_TO(StateShowTitle);
    }
}

// [state2cpp]InstallAllStartUpAssets:523bee1c87af31b972ef1b6c1e21d295d068032e

void Main::StateInstallAllStartUpAssets() {

    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitAllStartUpAssetsInstalled);
}

// [state2cpp]WaitAllStartUpAssetsInstalled:9452977fa9493c603c06e14622d4115e533c91b5

void Main::StateWaitAllStartUpAssetsInstalled() {

    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateAppInit);
}

// [state2cpp]WaitAppInit:9d467568f56c0b61d7ddf851bb3d817860a79e53

void Main::StateWaitAppInit() {

    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Application init done?
        SWITCH_TO(StateWaitUserData);
    }
}

// [state2cpp]WaitUserData:50cb2e003d13c3710f7138e98f3b2b190fa29a7d

void Main::StateWaitUserData() {

    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Receive UserData?
        SWITCH_TO(StateWaitTouch);
    }
}

// [state2cpp]WaitTouch:59bbf3f56f49283952587d17c8037532dea6b13c

void Main::StateWaitTouch() {

    //  TODO: Something to execute every frame while this state.

    if (false) {  //  Tapped?
        SWITCH_TO(StateWaitGame);
    }
}

// [state2cpp]WaitGame:70e65dd69720ce6deda33d25cad85fec7d992381

void Main::StateWaitGame() {

    //  TODO: Something to execute every frame while this state.

    if (false) {
        EXIT();
    }
}
} // namespace kms
