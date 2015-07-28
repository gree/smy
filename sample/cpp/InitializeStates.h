// [state2cpp] please include this file ins the declaration of class Initialize.

private:
  StateMachine _stateMachine;
public:
  void StartState();
  void ExecState();
  std::string DumpState() const;

private:
  void StateLogin();
  void StateLoginGameCenter();
  void StateDevCheckInstall();
  void StateCheckMaintenance();
  void StateGGLLogin();
  void StateGGLLoginWait();
  void StateMaintenance();
  void StateGGLQueryXuid();
  void StateGGLQueryXuidWait();
  void StateGGLKeywordFilterLogin();
  void StateRegisterGrowthPush();
  void StateCheckNewApp();
  void StateShowNewApp();
  void StateRequestMeta();
  void StateWaitForever();
  void StateShowMaintenanceDialog();
  void StateWaitMeta();
  void StateCheckMeta();
  void StateRtsConnect();
  void StateRequestMaster();
  void StateLoadMaster();
  void StateWaitRtsConnect();
  void StateDefending();
  void StateWaitPreviousBattle();
  void StateWaitMaster();
  void StateCheckDownloadAssets();
  void StateStartAssetDownload();
  void StateStartUnarchiveFile();
  void StateWaitAssetDownload();
  void StateWaitUnarchiveFile();
  void StateStartAssetPreload();
  void StateWaitAssetPreload();
  void StateDone();
  void StateDevCheckMaintenanceForNewUser();
  void StateDevRequestXuid();
  void StateDevRequestInstall();
  void StateDevRequestInstallWait();
  void StateDevRequestXuidWait();
