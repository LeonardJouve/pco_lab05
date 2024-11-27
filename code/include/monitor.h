#include <pcosynchro/pcoconditionvariable.h>

template <typename T>
struct Task {
    sts::vector<T> &values;
    size_t begin;
    size_t end;
};

template <typename T>
class Monitor {
    PcoConditionVariable conditionVariable;
    PcoMutex mutex;
    std::vector<struct Task<T>> tasks;
    
    void scheduleTask(struct Task<T> task) {
        tasks.push_back(task);
        conditionVariable.notifyOne();
    }

    void executeTask() {
        mutex.lock();
        conditionVariable.wait(&mutex);
        struct Task task = vector.pop_back();
    }
};