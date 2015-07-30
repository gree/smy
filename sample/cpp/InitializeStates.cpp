#include "Initialize.h"
#include "StateMachineMacros.h"
namespace kms {

// [state2cpp]__common__

std::string Initialize::DumpState() const { return TO_STRING(); }
void Initialize::ExecState() { EXEC(); }
void Initialize::StartState() {
    SPAWN(StateLogin);
}

// [state2cpp]Login:83cef36f308f1c322a60880061be12943b341d47

void Initialize::StateLogin() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  on editor?
        SWITCH_TO(StateDevCheckInstall);
    } else if (false) {  //  on device?
        SWITCH_TO(StateLoginGameCenter);
    }
}

// [state2cpp]LoginGameCenter:fafa5788c7f22d862ff039121978f15baf4dde0d

void Initialize::StateLoginGameCenter() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  not first time?
        SWITCH_TO(StateCheckMaintenance);
    } else if (false) {  //  first time?
        SWITCH_TO(StateGGLLogin);
    }
}

// [state2cpp]DevCheckInstall:7748097ba4196203b6bf08846ad86ff080491f7b

void Initialize::StateDevCheckInstall() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  no uuid found?
        SWITCH_TO(StateDevCheckMaintenanceForNewUser);
    } else if (false) {  //  has uuid?
        SWITCH_TO(StateDevRequestXuid);
    }
}

// [state2cpp]CheckMaintenance:1111066dbfaabd5a9752e994ee487ed915a8480f

void Initialize::StateCheckMaintenance() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  While Maintenance?
        SWITCH_TO(StateMaintenance);
    } else {
        SWITCH_TO(StateCheckNewApp);
    }
}

// [state2cpp]GGLLogin:2d07fc6f0f849f192a70832b6fb947ce80407925

void Initialize::StateGGLLogin() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateGGLLoginWait);
}

// [state2cpp]GGLLoginWait:1dfe5320924aabdfa6765cabfef52680fe510093

void Initialize::StateGGLLoginWait() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  login done?
        SWITCH_TO(StateGGLQueryXuid);
    } else if (false) {  //  replied maintenance?
        SWITCH_TO(StateMaintenance);
    }
}

// [state2cpp]Maintenance:b7858768bee10eb5d2d6ec64133163aac41fa9ec

void Initialize::StateMaintenance() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  mentenanceMessage Changed?
        SWITCH_TO(StateShowMaintenanceDialog);
    }
}

// [state2cpp]GGLQueryXuid:a49eaa97910ef1b38610988f8743cccc38ab69f7

void Initialize::StateGGLQueryXuid() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateGGLQueryXuidWait);
}

// [state2cpp]GGLQueryXuidWait:8f2fafde7ff423916e85feeeac98f9e7f772fc48

void Initialize::StateGGLQueryXuidWait() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  xuid received?
        SWITCH_TO(StateGGLKeywordFilterLogin);
    }
}

// [state2cpp]GGLKeywordFilterLogin:d92943d260e2bec5fc638c3ffe3372296cf92bcd

void Initialize::StateGGLKeywordFilterLogin() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateRegisterGrowthPush);
}

// [state2cpp]RegisterGrowthPush:a545d7e26616a2fa946e5c86cfe7b6105822f320

void Initialize::StateRegisterGrowthPush() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateCheckMaintenance);
}

// [state2cpp]CheckNewApp:3af49a9ca9c2240705116cd8b8f2c33df1fec4c7

void Initialize::StateCheckNewApp() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  application Update is needed?
        SWITCH_TO(StateShowNewApp);
    } else {
        SWITCH_TO(StateRequestMeta);
    }
}

// [state2cpp]ShowNewApp:7fe0c6250114e9bbd1234c0b75d218a27769f243

void Initialize::StateShowNewApp() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitForever);
}

// [state2cpp]RequestMeta:954953d280d0e3b0a82d44f71c35eff5fa690279

void Initialize::StateRequestMeta() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitMeta);
}

// [state2cpp]WaitForever:c135f8713af76023923a68642b5ce9a215b95230

void Initialize::StateWaitForever() {
    //  TODO: Something to execute every frame while this state.

    if (false) {
        EXIT();
    }
}

// [state2cpp]ShowMaintenanceDialog:deb76aa7a78e8b611553e6923608c16f573d7f63

void Initialize::StateShowMaintenanceDialog() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateMaintenance);
}

// [state2cpp]WaitMeta:19e1e3f1b8b8db1c5ccb2066c2d523db3597a1ac

void Initialize::StateWaitMeta() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  [development] not use rts?
        SWITCH_TO(StateCheckMeta);
    } else if (false) {  //  replied maintenance?
        SWITCH_TO(StateMaintenance);
    } else if (false) {  //  replied new application is needed?
        SWITCH_TO(StateShowNewApp);
    } else {
        SWITCH_TO(StateRtsConnect);
    }
}

// [state2cpp]CheckMeta:5e4522b00f727847c59378130ea2e880e69a2ce6

void Initialize::StateCheckMeta() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  has latest master?
        SWITCH_TO(StateLoadMaster);
    } else if (false) {  //  any master needs to be loaded?
        SWITCH_TO(StateRequestMaster);
    }
}

// [state2cpp]RtsConnect:2bf33228b670846f47d0b3410fb87396872d0c05

void Initialize::StateRtsConnect() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  get information of RTS?
        SWITCH_TO(StateWaitRtsConnect);
    }
}

// [state2cpp]RequestMaster:7f4ac8b2b8fc25c2b62c513419cc81489c6ea6d7

void Initialize::StateRequestMaster() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitMaster);
}

// [state2cpp]LoadMaster:4d736f28e8127455e2cdc94f6ca9ac5015640e33

void Initialize::StateLoadMaster() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateCheckDownloadAssets);
}

// [state2cpp]WaitRtsConnect:e174b171446d9d2d3730bc8245792a3f644a27ec

void Initialize::StateWaitRtsConnect() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  success of connect to RTS?
        SWITCH_TO(StateCheckMeta);
    } else if (false) {  //  defending?
        SWITCH_TO(StateDefending);
    } else if (false) {  //  previous battle is running on RTS?
        SWITCH_TO(StateWaitPreviousBattle);
    }
}

// [state2cpp]Defending:490e8a46da6d3b769b63f299c6d8d839baa40452

void Initialize::StateDefending() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  polling?
        SWITCH_TO(StateRtsConnect);
    }
}

// [state2cpp]WaitPreviousBattle:3c26bd41df32b86d4db8dad61169ea1d5edc4f75

void Initialize::StateWaitPreviousBattle() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  polling?
        SWITCH_TO(StateRtsConnect);
    }
}

// [state2cpp]WaitMaster:6f382281ab64a5e75472536b1b83c31f62490423

void Initialize::StateWaitMaster() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  master received?
        SWITCH_TO(StateLoadMaster);
    }
}

// [state2cpp]CheckDownloadAssets:305526f720ab612a257661d3a04bd6e2b8fed301

void Initialize::StateCheckDownloadAssets() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  download is needed.?
        SWITCH_TO(StateStartAssetDownload);
    } else {
        SWITCH_TO(StateStartUnarchiveFile);
    }
}

// [state2cpp]StartAssetDownload:6ac95b63e76b5ccc7660a06953d803770a6c715a

void Initialize::StateStartAssetDownload() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitAssetDownload);
}

// [state2cpp]StartUnarchiveFile:0ad5fb1923f536b21acafcd023d2ea745cf0c615

void Initialize::StateStartUnarchiveFile() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitUnarchiveFile);
}

// [state2cpp]WaitAssetDownload:13ad5adf7811ddfb963468aef6913053c2ed065c

void Initialize::StateWaitAssetDownload() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateStartUnarchiveFile);
}

// [state2cpp]WaitUnarchiveFile:57fb7eb6ad6dbcdc36d6a7af9eda196eed65f15a

void Initialize::StateWaitUnarchiveFile() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateStartAssetPreload);
}

// [state2cpp]StartAssetPreload:9e38516f89cdfddd94c63cf1ad4c1eed0c3bac0d

void Initialize::StateStartAssetPreload() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateWaitAssetPreload);
}

// [state2cpp]WaitAssetPreload:ad69138afe5e92675ee7f15f09409c9e9559108c

void Initialize::StateWaitAssetPreload() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateDone);
}

// [state2cpp]Done:160544a82497caa79ba820426399b26c095f5c46

void Initialize::StateDone() {
    //  TODO: Something to execute every frame while this state.

    if (false) {
        EXIT();
    }
}

// [state2cpp]DevCheckMaintenanceForNewUser:a2aaa0e3a0b1b05f63d7890dcfd890115a6b599d

void Initialize::StateDevCheckMaintenanceForNewUser() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  While Maintenance?
        SWITCH_TO(StateMaintenance);
    } else {
        SWITCH_TO(StateDevRequestInstall);
    }
}

// [state2cpp]DevRequestXuid:f257250ba1e776db623d7420455a056693d9786a

void Initialize::StateDevRequestXuid() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateDevRequestXuidWait);
}

// [state2cpp]DevRequestInstall:0cf23ac56e1fa0eeef01724e768b8fe98323d5cb

void Initialize::StateDevRequestInstall() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateDevRequestInstallWait);
}

// [state2cpp]DevRequestInstallWait:b1a21602ab62eed02628444e6ee210cdc98011c1

void Initialize::StateDevRequestInstallWait() {
    //  TODO: Something to execute every frame while this state.

    if (false) {  //  uuid received?
        SWITCH_TO(StateDevRequestXuid);
    }
}

// [state2cpp]DevRequestXuidWait:b9073a5d3fb20351e9246209e3cfd0b05042fd61

void Initialize::StateDevRequestXuidWait() {
    //  TODO: Something to execute every frame while this state.

    SWITCH_TO(StateCheckMaintenance);
}
} // namespace kms
