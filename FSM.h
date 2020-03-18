//
// Created by GuJun on 2020/3/18.
//

#ifndef FSM_FSM_H
#define FSM_FSM_H

#include <unordered_map>

using namespace std;

typedef int StateType;

class FSM;

// 状态基类
class State {
public:
    virtual void onStateEnter() = 0;
    virtual void onStateTick() = 0;
    virtual void onStateExit() = 0;

    explicit State(FSM* fsm) : fsm_(fsm) {}

protected:
    FSM* fsm_ = nullptr;
};

// 状态机
class FSM {
public:
    FSM() : curState_(-1) {
    }

    // 注册新的状态
    bool registerNewState(StateType state, State* pState) {
        allStates[state] = pState;
        return true;
    }

    // 需要状态转移则调用此函数
    bool trans(StateType newState) {
        allStates[curState_]->onStateExit();
        allStates[newState]->onStateEnter();
        curState_ = newState;
        return true;
    }

    // 设置初始状态
    void setInitState(StateType state) {
        curState_ = state;
    }

    // 每帧调用
    void tick() {
        allStates[curState_]->onStateTick();
    }

private:
    unordered_map<StateType, State*> allStates;
    StateType curState_;
};


#endif //FSM_FSM_H
