#include <iostream>
#include <thread>
#include <vector>

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
            cout << "WORKER " << workerId << " HAS STARTED" << endl;
            state = STATE::RUNNING;
        }

        void onRunning() {
            cout << "WORKER " << workerId << " HAS ENDED" << endl;
            state = STATE::TERMINATED;
        }
};

int main(int argc, char *argv[]) {
    vector<Worker> workers;
    vector<thread> threads;

    for (int i = 0; i < 3; i++) {
        workers.push_back(Worker(i));
    }

    for (int i = 0; i < 3; i++) {
        threads.push_back(thread(&Worker::init, &workers[i]));
    }
 
    for (auto& t : threads) {
        t.join();
    }
}