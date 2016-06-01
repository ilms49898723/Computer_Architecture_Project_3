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
    class MemoryPage {
    public:
        MemoryPage();

        MemoryPage(const MemoryPage& that);

        ~MemoryPage();

        void init(const unsigned size);

        MemoryPage& operator=(const MemoryPage& that);

    public:
        unsigned cycle;
        unsigned size;
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
     */
    void init(const unsigned size, const unsigned pageSize);

    // TODO add getData, setData

    /**
     * Get memory size in bytes
     */
    unsigned getSize() const;

    /**
     * Get number of memory entry
     */
    unsigned getEntry() const;

private:
    unsigned size;
    unsigned entry;
    bool* valid;
    MemoryPage* data;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
