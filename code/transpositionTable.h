// Transposition table

#pragma once

#ifndef DECLARS
#define DECLARS

#include "declars.h"

#endif /* DECLARS */

#include <cstdlib>
#if defined(__linux__)
#include <sys/mman.h>
#endif

struct Flag {
    int8_t flags = 0;

    Flag() {}
    Flag(int8_t type, int8_t ttpv) {
        flags = type + (ttpv << 2);
    }

    int8_t type() {
        return flags&3;
    }

    int8_t ttpv() {
        return (flags>>2)&1;
    }
};

struct __attribute__ ((packed)) TableEntry {
    uint16_t key = 0;
    int16_t score = NO_EVAL;
    int16_t eval = NO_EVAL;
    int16_t move = 0;
    char depth = 0;
    Flag flag;

    TableEntry() {
        key = 0;
        score = NO_EVAL;
        depth = 0;
        move = 0;
        flag = Flag(NONE, 0);
    }

    TableEntry(uint16_t key_, int score_, int eval_, char depth_, char type_, int16_t bestMove_, bool ttpv_) {
        key = key_;
        score = score_;
        eval = eval_;
        depth = depth_;
        move = bestMove_;
        flag = Flag(type_, ttpv_);
    }
};

bool alwaysReplace = false;

struct TranspositionTable {
    constexpr static size_t HUGEPAGE_SIZE = 2 << 20;

    ll tableSize = 0;
    TableEntry *table = nullptr;
    int b16 = 0b1111'1111'1111'1111;

    // mutex TTmutex;

    ~TranspositionTable() {
        free(table);
    }

    void resize(ll numEntries, int threadCount) {
        free(table);
        tableSize = numEntries;
        auto num_hugepages = [](size_t bytes) {
            return bytes / HUGEPAGE_SIZE + (bytes % HUGEPAGE_SIZE != 0);
        };
        size_t bytes = size_t(tableSize) * sizeof(TableEntry);
        size_t pages = num_hugepages(bytes);
        size_t aligned_bytes = pages * HUGEPAGE_SIZE;
        table = static_cast<TableEntry *>(aligned_alloc(HUGEPAGE_SIZE, aligned_bytes));
#if defined(__linux__)
        madvise(table, bytes, MADV_HUGEPAGE);
#endif
        clear(threadCount);
    }

    void clear(int threadCount) {
        assert(table && tableSize);
        threadCount = clamp<ll>(threadCount, 1, tableSize);

        vector<thread> pool;
        pool.reserve(threadCount);
        for (int t = 0; t < threadCount; t++) {
            pool.emplace_back([this, t, threadCount]() {
                ll lo = tableSize * t / threadCount;
                ll hi = min<ll>(tableSize, tableSize * (t + 1) / threadCount);
                for (ll i = lo; i < hi; i++)
                    new (table + i) TableEntry();
            });
        }
        for (thread &th : pool)
            th.join();
    }

    inline void write(Board &board, ull key, int score, int eval, int depth, int type, int age, Move bestMove,
                      int depthFromRoot, bool ttpv) {
        // if (tableSize == 0)
        //     return;
        if (abs(score) >= MATE_SCORE_MAX_PLY){
            if (score > 0)
                score += depthFromRoot;
            else
                score -= depthFromRoot;
        }
        ll index = (__uint128_t(key) * __uint128_t(tableSize)) >> 64;
        uint16_t key16 = key & b16;
        if (table[index].flag.type() != NONE) {
            if (table[index].key == key16) {
                if (table[index].depth > depth)
                    return;
                if (table[index].depth == depth && table[index].flag.type() == EXACT)
                    return;
            }
        }
        // TTmutex.lock();
        table[index] = {key16, score, eval, char(depth), char(type), bestMove.move, ttpv};
        // TTmutex.unlock();
    }

    inline void writeStaticEval(ull key, int eval) {
        ll index = (__uint128_t(key) * __uint128_t(tableSize)) >> 64;
        uint16_t key16 = key & b16;
        if (table[index].flag.type() != NONE && table[index].key == key16)
            table[index].eval = eval;
    }

    inline TableEntry get(Board &board, ull key, int depthFromRoot) {
        // if (tableSize == 0)
        //     return TableEntry();
        ll index = (__uint128_t(key) * __uint128_t(tableSize)) >> 64;
        uint16_t key16 = key & b16;
        if (table[index].flag.type() == NONE)
            return TableEntry();
        if (table[index].key != key16)
            return TableEntry();

        auto entry = table[index];

        if (abs(entry.score) >= MATE_SCORE_MAX_PLY && entry.score != NO_EVAL){
            if (entry.score > 0)
                entry.score -= depthFromRoot;
            else
                entry.score += depthFromRoot;
        }

        return entry;
    }

    inline void prefetch(ull key) {
        // if (tableSize == 0)
        //     return;
        __builtin_prefetch(&table[(__uint128_t(key) * __uint128_t(tableSize)) >> 64]);
    }

    int getHashfull() {
        int hits = 0;
        for (int i = 0; i < min(1000ll, tableSize); i++)
            hits += (table[i].flag.type() != NONE);
        if (tableSize && tableSize < 1000)
            hits = hits * 1000 / tableSize;
        return hits;
    }
};

TranspositionTable transpositionTable;
