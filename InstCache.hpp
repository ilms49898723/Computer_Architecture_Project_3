/*
 * InstCache.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_

#include <utility>
#include "InstMemory.hpp"

namespace inst {

class InstCache {
private:
    class CacheBlock {
    public:
        CacheBlock();

        ~CacheBlock();

        void allocate(const unsigned size);

        void init(const unsigned tag, const unsigned ppn);

    public:
        unsigned tag;
        unsigned ppn;
        unsigned* content;
        bool valid;
        bool mru;
    };

    class CacheData {
    public:
        CacheData();

        ~CacheData();

        void init(const unsigned setAssociativity, const unsigned blockSize);

    public:
        unsigned size;
        unsigned blockSize;
        CacheBlock* block;
    };

public:
    /**
     * Default constructor
     */
    InstCache();

    /**
     * Default destructor
     */
    ~InstCache();

    /**
     * Initialize
     *
     * @param cacheSize cache size
     * @param blockSize block size
     * @param setAssociativity cache set associativity
     */
    void init(const unsigned cacheSize, const unsigned blockSize, const unsigned setAssociativity);

    /**
     * Erase least recently used block, flush to memory
     *
     * @param physicalAddr
     */
    unsigned eraseLeastUsed(const unsigned index, InstMemory& memory);

    /**
     * Request a cache block
     *
     * @param physicalAddr physical address
     * @param ppn physical page number of the address
     */
    bool requestBlock(const unsigned physicalAddr, const unsigned ppn);

    /**
     * Search data in cache at physical address
     *
     * @param physicalAddr physical address to search
     */
    std::pair<unsigned, bool> search(const unsigned physicalAddr);

    /**
     * Set value to the block in cache relative to physical address
     *
     * @param physicalAddr physical address
     * @param val value to set
     */
    void setData(const unsigned physicalAddr, const unsigned val);

    /**
     * Get value at the block in cache relative to physical address
     *
     * @param physicalAddr physical address
     */
    unsigned getData(const unsigned physicalAddr);

    /**
     * Get cache size in bytes
     */
    unsigned getCacheSize() const;

    /**
     * Get cache block size in bytes
     */
    unsigned getBlockSize() const;

    /**
     * Get set associativity
     */
    unsigned getSetAssociativity() const;

    /**
     * Get number of cache entry
     */
    unsigned getEntry() const;

    /**
     * Get hit
     */
    unsigned getHit() const;

    /**
     * Get miss
     */
    unsigned getMiss() const;

private:
    unsigned getTag(const unsigned physicalAddr) const;

    unsigned getIndex(const unsigned physicalAddr) const;

    unsigned getOffset(const unsigned physicalAddr) const;

private:
    unsigned cacheSize;
    unsigned blockSize;
    unsigned setAssociativity;
    unsigned entry;
    CacheData* data;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_ */
