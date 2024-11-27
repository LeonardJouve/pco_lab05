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
class Quicksort: public MultithreadedSort<T>
{
public:
    Quicksort(unsigned int nbThreads) : MultithreadedSort<T>(nbThreads), threads(nbThreads) {
    }

    void quicksort(struct Task task) {
        
    }

    /**
     * @brief sort Manages the threads to sort the given sequence.
     * @param array is the sequence to sort
     */
    void sort(std::vector<T>& array) override {
        // TODO
    }
private:

    std::vector<PcoThread> threads;
};


#endif // QUICKSORT_H
