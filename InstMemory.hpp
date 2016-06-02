/*
 * InstMemory.hpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_

#include <cstring>
#include <string>
#include <utility>
#include <vector>
#include "InstDisk.hpp"
#include "InstUtility.hpp"
#include "InstType.hpp"

namespace inst {

/**
 * Memory
 */
class InstMemory {
private:
    class MemoryPage {
    public:
        MemoryPage();

        MemoryPage(const MemoryPage& that);

        ~MemoryPage();

        void init(const unsigned size, const unsigned vpn);

        MemoryPage& operator=(const MemoryPage& that);

    public:
        unsigned cycle;
        unsigned size;
        unsigned vpn;
        unsigned* data;
    };

public:
    /**
     * Default constructor
     */
    InstMemory();

    /**
     * Default destructor
     */
    ~InstMemory();

public:
    /**
     * Initialize
     *
     * @param size memory size(in bytes)
     * @param pageSize page size(in bytes)
     */
    void init(const unsigned size, const unsigned pageSize);

    // TODO add getData, setData

    /**
     * Update LRU cycle in page number ppn
     *
     * @param ppn physical-page-number to update
     * @param cycle cycle
     */
    void update(const unsigned ppn, const unsigned cycle);

    /**
     * Flush Least recently used page to disk, return vpn flushed
     *
     * @param disk disk
     */
    unsigned flushLeast(InstDisk& disk);

    /**
     * Request a Memory Page
     *
     * Return a valid index only when there is empty space in memory
     */
    std::pair<unsigned, bool> requestPage(const unsigned vpn);

    /**
     * Get memory size in bytes
     */
    unsigned getSize() const;

    /**
     * Get number of memory entry
     */
    unsigned getEntry() const;

    /**
     * Get page size
     */
    unsigned getPageSize() const ;

private:
    unsigned size;
    unsigned entry;
    unsigned pageSize;
    bool* valid;
    MemoryPage* page;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
