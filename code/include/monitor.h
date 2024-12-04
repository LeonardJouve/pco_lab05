#include <pcosynchro/pcoconditionvariable.h>
#include <vector>
#include <iostream>

template <typename T>
struct Task {
    std::vector<T> &values;
    int begin;
    int end;
};

template <typename T>
class Quicksort;

template <typename T>
class Monitor {
    PcoConditionVariable conditionVariable;
    PcoMutex mutex;
    std::vector<Task<T>> tasks;
    bool flag;
    Quicksort<T> *quicksort;

public:
    Monitor(Quicksort<T> *quicksort) : quicksort(quicksort), conditionVariable(false), mutex(), flag(false) {}

    void scheduleTask(Task<T> task) {

        std::cout << "schedule task " << task.begin << " " << task.end << std::endl;
        mutex.lock();
        tasks.push_back(task);
        mutex.unlock();
        conditionVariable.notifyOne();
    }

    void executeTask() {
        if (flag && tasks.empty()) return; // TODO execute left tasks even if flag

        std::cout << "execute task" << std::endl;

        mutex.lock();
        while (tasks.empty()) conditionVariable.wait(&mutex);
        if (flag) {
            mutex.unlock();
            return;
        }

        Task<T> task = tasks.back();
        tasks.pop_back();

        mutex.unlock();

        std::cout << "start task " << task.begin << " "<< task.end << std::endl;

        quicksort->quicksort(task);
    }

    void flushTasks() {
        std::cout << "flush tasks" << std::endl;
        flag = true;
        conditionVariable.notifyAll();
    }
};
