#include <pcosynchro/pcoconditionvariable.h>
#include <vector>
#include <queue>
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
    std::queue<Task<T>> tasks;
    bool flag;
    Quicksort<T> *quicksort;
    int nbWorking = 0;

    PcoConditionVariable started;
    bool isStarted = false;

public:
    Monitor(Quicksort<T> *quicksort) : quicksort(quicksort), conditionVariable(false), mutex(), flag(false) {}

    void reset() {
        isStarted = false;
        flag = false;
        //while (!tasks.empty()) tasks.pop();//just in case
    }

    bool tasksIsEmpty() {
        mutex.lock();
        int temp = nbWorking;
        mutex.unlock();
        return tasks.empty() && temp == 0;
    }

    void decrementNbWorking() {
        mutex.lock();
        --nbWorking;
        mutex.unlock();
    }

    void scheduleTask(Task<T> task) {
        mutex.lock();
        if (!isStarted) {
            //flag = false;
            isStarted = true;
            started.notifyAll();
        }
        tasks.push(task);
        conditionVariable.notifyOne();
        mutex.unlock();
    }

    void executeTask() {
        if (flag) {
            return;
        }
        mutex.lock();
        while (!isStarted) started.wait(&mutex);

        mutex.unlock();

        if (tasksIsEmpty()) {
            flushTasks();
            return;
        }

        mutex.lock();
        while (tasks.empty() && !flag) conditionVariable.wait(&mutex);
        if (flag) {
            mutex.unlock();
            return;
        }

        Task<T> task = tasks.front();
        tasks.pop();
        ++nbWorking;
        mutex.unlock();

        quicksort->quicksort(task);
    }

    void flushTasks() {
        mutex.lock();
        flag = true;
        conditionVariable.notifyAll();
        //isStarted = false;
        mutex.unlock();
    }
};
