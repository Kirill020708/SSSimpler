#pragma once

#ifndef DECLARS
#define DECLARS

#include "declars.h"

#endif

#include <exception>
#include <new>

#ifdef USE_LIBNUMA
#include <numa.h>
#include <sched.h>
#include <pthread.h>
#endif

namespace numa {

#ifdef USE_LIBNUMA

    inline const vector<cpu_set_t> &threadMapping() {
        static const vector<cpu_set_t> mapping = [] {
            if (numa_available() < 0) {
                cerr << "built with USE_LIBNUMA but NUMA is not available" << endl;
                std::terminate();
            }

            const int maxNode = numa_max_node();

            vector<cpu_set_t> masks;
            masks.reserve(maxNode + 1);

            for (int node = 0; node <= maxNode; node++) {
                bitmask *cpumask = numa_allocate_cpumask();

                if (numa_node_to_cpus(node, cpumask) != 0) {
                    cerr << "failed to get CPU mask for NUMA node " << node << endl;
                    std::terminate();
                }

                cpu_set_t cpuset;
                CPU_ZERO(&cpuset);

                for (unsigned cpu = 0; cpu < cpumask->size; cpu++)
                    if (numa_bitmask_isbitset(cpumask, cpu))
                        CPU_SET(cpu, &cpuset);

                numa_free_cpumask(cpumask);
                masks.push_back(cpuset);
            }

            return masks;
        }();

        return mapping;
    }

    inline int nodeCount() {
        return int(threadMapping().size());
    }

    inline int getNode(unsigned numaId) {
        return int(numaId % unsigned(nodeCount()));
    }

    inline bool init() {
        threadMapping();
        cerr << "info string " << nodeCount() << " NUMA nodes" << endl;
        return true;
    }

    inline void bindThread(unsigned numaId) {
        const int node = getNode(numaId);
        const pthread_t handle = pthread_self();
        const cpu_set_t *cpuSet = &threadMapping()[node];
        pthread_setaffinity_np(handle, sizeof(cpu_set_t), cpuSet);
    }

    template <typename T>
    T *allocOnNode(unsigned numaId) {
        void *raw = numa_alloc_onnode(sizeof(T), getNode(numaId));
        return new (raw) T();
    }

    template <typename T>
    void freeOnNode(T *ptr) {
        ptr->~T();
        numa_free(ptr, sizeof(T));
    }

#else

    inline bool init() {
        return true;
    }

    inline void bindThread(unsigned numaId) {
        (void)numaId;
    }

    inline int nodeCount() {
        return 1;
    }

    inline int getNode(unsigned numaId) {
        (void)numaId;
        return 0;
    }

    template <typename T>
    T *allocOnNode(unsigned numaId) {
        (void)numaId;
        return new T();
    }

    template <typename T>
    void freeOnNode(T *ptr) {
        delete ptr;
    }

#endif

    template <typename T>
    struct NumaReplicated {
        vector<T *> data;

        NumaReplicated() {
            for (int node = 0; node < nodeCount(); node++)
                data.push_back(allocOnNode<T>(node));
        }

        ~NumaReplicated() {
            for (T *ptr : data)
                freeOnNode(ptr);
        }

        T *get(unsigned numaId) {
            return data[getNode(numaId)];
        }
    };

}
