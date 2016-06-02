/*
 * InstCache.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstCache.hpp"

namespace inst {

InstCache::CacheBlock::CacheBlock() {
    this->tag = 0;
    this->ppn = 0;
    this->content = nullptr;
    this->valid = false;
    this->mru = false;
}

InstCache::CacheBlock::~CacheBlock() {
    delete[] this->content;
}

void InstCache::CacheBlock::allocate(const unsigned size) {
    delete[] this->content;
    this->content = new unsigned[size >> 2];
}

void InstCache::CacheBlock::init(const unsigned tag, const unsigned ppn) {
    this->tag = tag;
    this->ppn = ppn;
    this->valid = true;
    this->mru = true;
}

InstCache::CacheData::CacheData() {
    this->size = 0;
    this->blockSize = 0;
    this->block = nullptr;
}

InstCache::CacheData::~CacheData() {
    delete[] this->block;
}

void InstCache::CacheData::init(const unsigned setAssociativity, const unsigned blockSize) {
    delete[] this->block;
    this->size = setAssociativity;
    this->blockSize = blockSize;
    this->block = new CacheBlock[setAssociativity];
    for (unsigned i = 0; i < this->size; ++i) {
        this->block[i].allocate(this->blockSize);
    }
}

InstCache::InstCache() {
    this->cacheSize = 0;
    this->blockSize = 0;
    this->setAssociativity = 0;
    this->entry = 0;
    this->data = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstCache::~InstCache() {
    delete[] this->data;
}

void InstCache::init(const unsigned cacheSize, const unsigned blockSize, const unsigned setAssociativity) {
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->setAssociativity = setAssociativity;
    this->entry = cacheSize / setAssociativity / blockSize;
    this->data = new CacheData[this->entry];
    for (unsigned i = 0; i < this->entry; ++i) {
        this->data[i].init(setAssociativity, blockSize);
    }
    this->hit = 0;
    this->miss = 0;
}

unsigned InstCache::eraseLeastUsed(const unsigned index, InstMemory& memory) {
    CacheData& targetSet = data[index];
    unsigned target = 0;
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && !targetSet.block[i].mru) {
            target = i;
            break;
        }
    }
    for (unsigned i = 0; i < blockSize; ++i) {
        memory.setData(targetSet.block[target].ppn, i << 2, targetSet.block[target].content[i]);
    }
    targetSet.block[target].valid = false;
    return target;
}

bool InstCache::requestBlock(const unsigned physicalAddr, const unsigned ppn) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    const CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (!targetSet.block[i].valid) {
            targetSet.block[i].init(tag, ppn);
            return true;
        }
    }
    return false;
}

std::pair<unsigned, bool> InstCache::search(const unsigned physicalAddr) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    unsigned offset = getOffset(physicalAddr);
    const CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            ++hit;
            return std::make_pair(targetSet.block[i].content[offset >> 2], true);
        }
    }
    ++miss;
    return std::make_pair(0, false);
}

void InstCache::setData(const unsigned physicalAddr, const unsigned val) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    unsigned offset = getOffset(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            targetSet.block[i].content[offset >> 2] = val;
        }
    }
}

unsigned InstCache::getData(const unsigned physicalAddr) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    unsigned offset = getOffset(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            return targetSet.block[i].content[offset >> 2];
        }
    }
    return 0;
}

unsigned InstCache::getCacheSize() const {
    return this->cacheSize;
}

unsigned InstCache::getBlockSize() const {
    return this->blockSize;
}

unsigned InstCache::getSetAssociativity() const {
    return this->setAssociativity;
}

unsigned InstCache::getEntry() const {
    return this->entry;
}

unsigned InstCache::getHit() const {
    return this->hit;
}

unsigned InstCache::getMiss() const {
    return this->miss;
}

unsigned InstCache::getTag(const unsigned physicalAddr) const {
    return physicalAddr / blockSize / entry;
}

unsigned InstCache::getIndex(const unsigned physicalAddr) const {
    return physicalAddr / blockSize % entry;
}

unsigned InstCache::getOffset(const unsigned physicalAddr) const {
    return physicalAddr % blockSize;
}

} /* namespace inst */
