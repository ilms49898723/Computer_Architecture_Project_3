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

        ~MemoryPage();

        void allocate(const unsigned size);

        void init(const unsigned vpn);

    public:
        unsigned cycle;
        unsigned size;
        unsigned vpn;
        unsigned char* data;
        bool valid;
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

    /**
     * Initialize
     *
     * @param size total memory size(in bytes)
     * @param pageSize page size(in bytes)
     */
    void init(const unsigned size, const unsigned pageSize);

    /**
     * Update LRU cycle in physical page number ppn
     *
     * @param ppn physical page number to update
     * @param cycle cycle to update
     */
    void update(const unsigned ppn, const unsigned cycle);

    /**
     * Erase least recently used page, flush to disk
     *
     * @param disk disk
     */
    std::pair<unsigned, unsigned> eraseLeastUsed(InstDisk& disk);

    /**
     * Request a Memory Page
     *
     * Return a valid ppn only when there is empty space in memory
     */
    std::pair<unsigned, bool> requestPage(const unsigned vpn);

    /**
     * Set data at specified ppn, offset
     *
     * @param ppn physical page number
     * @param offset page offset in bytes
     * @param val value to set
     * @param size size
     */
    void setData(const unsigned ppn, const unsigned offset, const unsigned val, const unsigned size = 4);

    /**
     * Get data at specified ppn, offset
     *
     * @param ppn physical page number
     * @param offset page offset in bytes
     */
    unsigned getData(const unsigned ppn, const unsigned offset, const unsigned size = 4);

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
    MemoryPage* page;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
