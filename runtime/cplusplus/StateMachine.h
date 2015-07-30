#ifndef __STATEMACHINE_H__
#define __STATEMACHINE_H__

#include <functional>
#include <string>
#include <vector>
#include <utility>

class StateMachine {
 public:
  typedef std::pair<std::function<void()>, std::string> state_t;
  typedef std::vector<state_t> states_t;

 private:
  states_t _currentStates;
  states_t _nextStates;
  state_t _currentState;
  state_t _nextState;
  bool _yield;
  bool _exit;
  bool _executing;

 public:
  StateMachine() { Init(); }

  void Init() {
    _currentStates.clear();
    _nextStates.clear();
    _executing = false;
  }

  void Exec() {
    _currentStates = _nextStates;
    _executing = true;
    _nextStates.clear();

    for (auto state : _currentStates) {
      _yield = false;
      _exit = false;
      _nextState.first = NULL;

      _currentState = state;
      _currentState.first();

      if (_exit) continue;

      while (_nextState.first != NULL && !_yield) {
        _currentState = _nextState;
        _nextState.first = NULL;
        _currentState.first();

        if (_exit) break;
      }

      if (_exit) continue;

      _nextStates.push_back(_nextState.first != NULL ? _nextState : _currentState);
    }

    _executing = false;
  }

  void Spawn(state_t state) { _nextStates.push_back(state); }

  void SwitchTo(state_t state) {
    _nextState = state;
    _yield = false;
  }

  void YieldTo(state_t state) {
    _nextState = state;
    _yield = true;
  }

  void Exit() { _exit = true; }

  std::string to_string() const {
    std::string s;
    const states_t *states = _executing ? &_currentStates : &_nextStates;

    for (auto state : *states) s += state.second + ":";

    return s;
  }
};

#endif  // __STATEMACHINE_H__
