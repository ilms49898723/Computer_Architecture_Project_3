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

        void init(const unsigned vpn, const unsigned cycle);

    public:
        unsigned cycle;
        unsigned vpn;
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
     * Erase least recently used page
     */
    void eraseLeastUsed();

    /**
     * Get least used page vpn, ppn
     */
    std::pair<unsigned, unsigned> getLeastUsed();

    /**
     * Request a Memory Page
     *
     * Return a valid ppn only when there is empty space in memory
     *
     * @param vpn virtual page number
     * @param cycle cycle
     */
    std::pair<unsigned, bool> requestPage(const unsigned vpn, const unsigned cycle);

    /**
     * Get string representation of current state
     */
    std::string toString() const;

private:
    unsigned size;
    unsigned entry;
    MemoryPage* page;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
