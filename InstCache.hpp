/*
 * InstCache.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_

#include <string>
#include <utility>

namespace inst {

class InstCache {
private:
    class CacheBlock {
    public:
        CacheBlock();

        ~CacheBlock();

        void init(const unsigned tag);

    public:
        unsigned tag;
        bool valid;
        bool mru;
    };

    class CacheData {
    public:
        CacheData();

        ~CacheData();

        void init(const unsigned int setAssociativity);

    public:
        unsigned size;
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
     * Erase specified data
     *
     * @param physicalAddr physical address
     */
    void eraseSpecified(const unsigned physicalAddr);

    /**
     * Erase least recently used block
     *
     * @param physicalAddr physical address
     */
    void eraseLeastUsed(const unsigned physicalAddr);

    /**
     * Request a cache block
     *
     * @param physicalAddr physical address
     */
    bool requestBlock(const unsigned int physicalAddr);

    /**
     * Search data in cache at physical address
     *
     * @param physicalAddr physical address to search
     */
    bool search(const unsigned int physicalAddr);

    /**
     * Get tag of physical address
     *
     * @param physicalAddr physical address
     */
    unsigned getTag(const unsigned physicalAddr) const;

    /**
     * Get index of physical address
     *
     * @param physicalAddr physical address
     */
    unsigned getIndex(const unsigned physicalAddr) const;

    /**
     * Get hit
     */
    unsigned getHit() const;

    /**
     * Get miss
     */
    unsigned getMiss() const;

    /**
     * Get string representation of current state
     */
    std::string toString() const;

private:
    void checkMRU(const unsigned index, const unsigned tag);

private:
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
