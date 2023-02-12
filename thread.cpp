#include <iostream>
#include <thread>

using namespace std;

enum STATE {
    NOT_STARTED,
    RUNNING,
    TERMINATED
};

class Worker {
    public:
        Worker(int id) : workerId(id), state(STATE::NOT_STARTED) {}

        void init() {
            run();
        }
    
    private:
        int workerId;
        STATE state;

        void run() {
            while (state != STATE::TERMINATED) {
                switch (state) {
                    case STATE::NOT_STARTED:
                        onStart();
                        break;
                    case STATE::RUNNING:
                        onRunning();
                        break;
                    default:
                        break;

                }
            }
        }

        void onStart() {
            state = STATE::RUNNING;
        }

        void onRunning() {
            state = STATE::TERMINATED;
        }
};

int main(int argc, char *argv[]) {
    cout << "hi" << endl;
}