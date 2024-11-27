#include <pcosynchro/pcoconditionvariable.h>

template <typename T>
struct Task {
    std::vector<T> &values;
    size_t begin;
    size_t end;
};

template <typename T>
class Monitor {
    PcoConditionVariable conditionVariable{ false };
    PcoMutex mutex;
    std::vector<Task<T>> tasks;
    bool flag = false;

public:
    void scheduleTask(Task<T> task) {
        tasks.push_back(task);
        conditionVariable.notifyOne();
    }

    void executeTask() {
        mutex.lock();
        conditionVariable.wait(&mutex);
        if (flag) {
            mutex.unlock();
            return;
        }

        Task<T> task = tasks.back();
        tasks.pop_back();

        mutex.unlock();
    }

    void flushTasks() {
        flag = true;
        conditionVariable.notifyAll();
    }
};
