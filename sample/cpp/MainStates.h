// [state2cpp] please include this file ins the declaration of class Main.

private:
  StateMachine _stateMachine;
public:
  void StartState();
  void ExecState();
  std::string DumpState() const;

private:
  void StateStart();
  void StateInit();
  void StateAppInit();
  void StateInstallFirstPrioriryAssets();
  void StateWaitInstallingFirstPriorityAssets();
  void StateStartAgreementDialog();
  void StateShowTitle();
  void StateWaitAgreementDialog();
  void StateInstallAllStartUpAssets();
  void StateWaitAllStartUpAssetsInstalled();
  void StateWaitAppInit();
  void StateWaitUserData();
  void StateWaitTouch();
  void StateWaitGame();
