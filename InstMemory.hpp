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
#include <queue>
#include "InstUtility.hpp"
#include "InstType.hpp"

namespace inst {

/**
 * Memory
 */
class InstMemory {
private:
    struct MemoryLRU {
        unsigned addr;
        unsigned cycle;
        MemoryLRU(const unsigned addr = 0, const unsigned cycle = 0) :
                addr(addr), cycle(cycle) {}
        bool operator<(const MemoryLRU& that) const {
            return cycle < that.cycle || (cycle == that.cycle && addr < that.addr);
        }
    };

public:
    /**
     * Default constructor
     */
    InstMemory();

    /**
     * Copy constructor
     */
    InstMemory(const InstMemory& that);

    /**
     * Move constructor
     */
    InstMemory(InstMemory&& that);

    /**
     * Default destructor
     */
    ~InstMemory();

public:
    /**
     * Initialize(set all content to zero)
     */
    void init(const unsigned size);

    /**
     * Get data value at specified address with size
     *
     * @param addr address to get
     * @param size size to get
     */
    unsigned getData(const unsigned addr, const unsigned size) const;

    /**
     * Get data value at specified address with size
     *
     * @param addr address to get
     * @param size size to get
     */
    unsigned getData(const unsigned addr, const InstSize size) const;

    /**
     * Get memory size in bytes
     */
    unsigned getSize() const;

    /**
     * Set data value at specified address with size
     *
     * @param addr address to set
     * @param val value to set
     * @param size size to set
     */
    void setData(const unsigned addr, const unsigned val, const unsigned size);

    /**
     * Set data value at specified address with size
     *
     * @param addr address to set
     * @param val value to set
     * @param size size to set
     */
    void setData(const unsigned addr, const unsigned val, const InstSize size);

    /**
     * Copy assignment
     */
    InstMemory& operator=(const InstMemory& that);

    /**
     * Move assignment
     */
    InstMemory& operator=(InstMemory&& that);

private:
    unsigned size;
    unsigned* data;
    std::priority_queue<MemoryLRU> lruSet;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
