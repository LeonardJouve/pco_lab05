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
    Quicksort(unsigned int nbThreads) : MultithreadedSort<T>(nbThreads), threads(nbThreads) {
        monitor = new Monitor<T>(this);
        for (int i = 0; i < nbThreads; ++i) {
            threads[i] = new PcoThread(&Monitor<T>::executeTask, &monitor);
        }
    }

    /**
     * @brief sort Manages the threads to sort the given sequence.
     * @param array is the sequence to sort
     */
    void sort(std::vector<T> &array) override {
        //quicksort({ array, 0, array.size() });
        monitor->scheduleTask({ array, 0, array.size() });

        for (size_t i = 0; i < threads.size(); ++i) {
            threads[i]->join();
            delete threads[i];
        }
    }

    void quicksort(Task<T> task) {
        if (task.begin >= task.end || task.begin < 0) {
            monitor->flushTasks();
            return;
        }

        size_t pivot = partition(task);

        monitor.scheduleTask({ task.values, task.begin, pivot - 1 });
        monitor.scheduleTask({ task.values, pivot + 1, task.end });

        monitor.executeTask();
        //quicksort({ task.values, task.begin, pivot - 1 });
        //quicksort({ task.values, pivot + 1, task.end });
    }

private:

    size_t partition(Task<T> task) {
        T p = task.values[task.end];
        size_t pivot = task.begin;

        for (size_t i = task.begin; i < task.end; ++i) {
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
