// [state2cpp] please include this file ins the declaration of class Game.

private:
  StateMachine _stateMachine;
public:
  void StartState();
  void ExecState();
  std::string DumpState() const;

private:
  void StateStartGame();
  void StateWaitPlayerData();
  void StateStartBuilding();
  void StateWaitTutorialBattleData();
  void StateStartBattle();
  void StateBuilding();
  void StateStartReplay();
  void StateStartVisit();
  void StateBattle();
  void StateReplay();
  void StateVisit();
