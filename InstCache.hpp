/*
 * InstCache.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_

namespace inst {

class InstCache {
private:
    class CacheBlock {
    public:
        CacheBlock();

        ~CacheBlock();

        void init(const unsigned size);

    public:
        unsigned tag;
        unsigned* content;
    };

    class CacheData {
    public:
        CacheData();

        ~CacheData();

        void init(const unsigned setAssociativity, const unsigned blockSize);

    public:
        unsigned size;
        bool* valid;
        bool* mru;
        CacheBlock* block;
    };

public:
    InstCache();

    ~InstCache();

    void init(const unsigned cacheSize, const unsigned blockSize, const unsigned setAssociativity);

    unsigned getCacheSize() const;

    unsigned getBlockSize() const;

    unsigned getSetAssociativity() const;

    unsigned getEntry() const;

private:
    unsigned cacheSize;
    unsigned blockSize;
    unsigned setAssociativity;
    unsigned entry;
    CacheData* data;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_ */
