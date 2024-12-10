#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <iostream>
#include <queue>

#include <pcosynchro/pcothread.h>
#include <pcosynchro/pcomutex.h>
#include <pcosynchro/pcoconditionvariable.h>

#include "multithreadedsort.h"
#include "monitor.h"

/**
 * @brief The Quicksort class implements the multi-threaded Quicksort algorithm.
 */
template<typename T>
class Quicksort : public MultithreadedSort<T> {
public:
    Quicksort(unsigned int nbThreads) : MultithreadedSort<T>(nbThreads), threads(nbThreads), monitor(this) {

    }

    /**
     * @brief sort Manages the threads to sort the given sequence.
     * @param array is the sequence to sort
     */
    void sort(std::vector<T> &array) override {
        for (int i = 0; i < threads.size(); ++i) {
            threads[i] = new PcoThread(&Monitor<T>::executeTask, &monitor);
        }
        monitor.scheduleTask({ array, 0, (int)array.size() });

        for (size_t i = 0; i < threads.size(); ++i) {
            threads[i]->join();
            delete threads[i];
        }

        monitor.reset();
    }

    void quicksort(Task<T> task) {
        if (task.begin >= task.end || task.begin < 0) {
            monitor.decrementNbWorking();
            monitor.executeTask();
            return;
        }

        int pivot = partition(task);

        monitor.scheduleTask({ task.values, task.begin, pivot - 1 });
        monitor.scheduleTask({ task.values, pivot + 1, task.end });

        monitor.decrementNbWorking();
        monitor.executeTask();
    }

private:

    int partition(Task<T> task) {
        T p = task.values[task.end];
        int pivot = task.begin;

        for (int i = task.begin; i < task.end; ++i) {
            if (task.values[i] <= p) {
                std::swap(task.values[i], task.values[pivot]);
                ++pivot;
            }
        }

        std::swap(task.values[task.end], task.values[pivot]);
        return pivot;
    }

    std::vector<PcoThread *> threads;
    Monitor<T> monitor;
};


#endif // QUICKSORT_H
