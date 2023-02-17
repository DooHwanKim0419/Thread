#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;
static mutex cout_handler;

enum STATE {
    NOT_STARTED,
    RUNNING,
    TERMINATED
};

class Worker {
    public:
        Worker(int id) : workerId(id), state(STATE::NOT_STARTED) {}
        ~Worker() {}

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

        virtual void onStart() {
            cout_handler.lock();
            cout << "WORKER " << workerId << " HAS STARTED" << endl;
            state = STATE::RUNNING;
            cout_handler.unlock();
        }

        virtual void onRunning() {
            cout_handler.lock();
            cout << "WORKER " << workerId << " HAS ENDED" << endl;
            state = STATE::TERMINATED;
            cout_handler.unlock();
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