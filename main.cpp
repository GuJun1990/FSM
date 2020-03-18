#include <iostream>
#include <thread>
#include "FSM.h"

using namespace std;

StateType idleState = 1;
StateType attackState = 2;
StateType goHomeState = 3;

class StateIdle : public State {
public:
    StateIdle(FSM* fsm) : State(fsm) {
        tickCount_ = 0;
    }

    void onStateEnter() override {
        cout << "------- Idle Enter -------" << endl;
    }

    void onStateTick() override {
        cout << "------- Idle Tick -------" << endl;
        if (++tickCount_ >= 5) {
            State::fsm_->trans(attackState);
        }
    }

    void onStateExit() override {
        cout << "------- Idle Exit ------" << endl;
    }

private:
    int tickCount_;
};

class StateAttack : public State {
public:
    explicit StateAttack(FSM* fsm) : State(fsm) {
        tickCount_ = 0;
    }

    void onStateEnter() override {
        cout << "------- Attack Enter -------" << endl;
    }

    void onStateTick() override {
        cout << "------- Attack Tick -------" << endl;
        if (++tickCount_ >= 3) {
            State::fsm_->trans(goHomeState);
        }
    }

    void onStateExit() override {
        cout << "------- Attack Exit ------" << endl;
    }

    int tickCount_;
};

class StateGoHome : public State {
public:
    explicit StateGoHome(FSM* fms) : State(fms) {

    }

    void onStateEnter() override {
        cout << "------- GoHome Enter -------" << endl;
    }

    void onStateTick() override {
        cout << "------- GoHome Tick -------" << endl;
    }

    void onStateExit() override {
        cout << "------- GoHome Exit ------" << endl;
    }
};

int main() {

    // 构造状态机
    FSM* fsm = new FSM();
    fsm->registerNewState(idleState, new StateIdle(fsm));
    fsm->registerNewState(attackState, new StateAttack(fsm));
    fsm->registerNewState(goHomeState, new StateGoHome(fsm));
    fsm->setInitState(idleState);

    while (true) {
        fsm->tick();
        this_thread::sleep_for(chrono::seconds(1));
    }
    delete fsm;
    return 0;
}
