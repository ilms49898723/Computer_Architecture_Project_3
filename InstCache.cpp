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
    this->content = new unsigned char[size];
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

void InstCache::eraseSpecified(const unsigned physicalAddr, InstMemory& memory) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    const CacheData& targetSet = data[index];
    unsigned target = 0;
    bool found = false;
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            target = i;
            found = true;
            break;
        }
    }
    if (found) {
        for (unsigned i = 0; i < blockSize; ++i) {
            memory.setData(targetSet.block[target].ppn, i, targetSet.block[target].content[i], 1);
        }
        targetSet.block[target].valid = false;
    }
}

unsigned InstCache::eraseLeastUsed(const unsigned physicalAddr, InstMemory& memory) {
    unsigned index = getIndex(physicalAddr);
    CacheData& targetSet = data[index];
    unsigned target = 0;
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && !targetSet.block[i].mru) {
            target = i;
            break;
        }
    }
    for (unsigned i = 0; i < blockSize; ++i) {
        memory.setData(targetSet.block[target].ppn, i, targetSet.block[target].content[i], 1);
    }
    targetSet.block[target].valid = false;
    return target;
}

bool InstCache::requestBlock(const unsigned physicalAddr, const unsigned ppn) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (!targetSet.block[i].valid) {
            targetSet.block[i].init(tag, ppn);
            checkMRU(index, tag);
            return true;
        }
    }
    return false;
}

std::pair<unsigned, bool> InstCache::search(const unsigned physicalAddr, const unsigned size) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    unsigned offset = getOffset(physicalAddr);
    const CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            ++hit;
            targetSet.block[i].mru = true;
            checkMRU(index, tag);
            unsigned ret = 0;
            if (size == 4) {
                ret = (targetSet.block[i].content[offset] << 24) |
                      (targetSet.block[i].content[offset + 1] << 16) |
                      (targetSet.block[i].content[offset + 2] << 8) |
                      (targetSet.block[i].content[offset + 3]);
            }
            else if (size == 2) {
                ret = (targetSet.block[i].content[offset] << 8) |
                      (targetSet.block[i].content[offset + 1]);
            }
            else {
                ret = (targetSet.block[i].content[offset]);
            }
            return std::make_pair(ret, true);
        }
    }
    ++miss;
    return std::make_pair(0, false);
}

void InstCache::setData(const unsigned physicalAddr, const unsigned val, const unsigned size) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    unsigned offset = getOffset(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            if (size == 4) {
                targetSet.block[i].content[offset] = static_cast<unsigned char>((val >> 24) & 0xFFu);
                targetSet.block[i].content[offset + 1] = static_cast<unsigned char>((val >> 16) & 0xFFu);
                targetSet.block[i].content[offset + 2] = static_cast<unsigned char>((val >> 8) & 0xFFu);
                targetSet.block[i].content[offset + 3] = static_cast<unsigned char>((val) & 0xFFu);
            }
            else if (size == 2) {
                targetSet.block[i].content[offset] = static_cast<unsigned char>((val >> 8) & 0xFFu);
                targetSet.block[i].content[offset + 1] = static_cast<unsigned char>((val) & 0xFFu);
            }
            else {
                targetSet.block[i].content[offset] = static_cast<unsigned char>((val) & 0xFFu);
            }
        }
    }
}

unsigned InstCache::getData(const unsigned physicalAddr, const unsigned size) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    unsigned offset = getOffset(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            if (size == 4) {
                return (targetSet.block[i].content[offset] << 24) |
                       (targetSet.block[i].content[offset + 1] << 16) |
                       (targetSet.block[i].content[offset + 2] << 8) |
                       (targetSet.block[i].content[offset + 3]);
            }
            else if (size == 2) {
                return (targetSet.block[i].content[offset] << 8) |
                       (targetSet.block[i].content[offset + 1]);
            }
            else {
                return (targetSet.block[i].content[offset]);
            }
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

void InstCache::checkMRU(const unsigned index, const unsigned tag) {
    bool isAllTrue = true;
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        isAllTrue &= targetSet.block[i].mru;
    }
    if (isAllTrue) {
        for (unsigned i = 0; i < setAssociativity; ++i) {
            targetSet.block[i].mru = (targetSet.block[i].tag == tag);
        }
    }
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
