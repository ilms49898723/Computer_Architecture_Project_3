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
    this->valid = false;
    this->mru = false;
}

InstCache::CacheBlock::~CacheBlock() {

}

void InstCache::CacheBlock::init(const unsigned tag) {
    this->tag = tag;
    this->valid = true;
    this->mru = true;
}

InstCache::CacheData::CacheData() {
    this->size = 0;
    this->block = nullptr;
}

InstCache::CacheData::CacheData(const InstCache::CacheData& that) {
    if (this != &that) {
        this->size = that.size;
        if (that.block) {
            this->block = new CacheBlock[this->size];
            for (unsigned i = 0; i < this->size; ++i) {
                this->block[i] = that.block[i];
            }
        }
        else {
            this->block = nullptr;
        }
    }
}

InstCache::CacheData::CacheData(InstCache::CacheData&& that) {
    if (this != &that) {
        this->size = that.size;
        this->block = that.block;
        that.block = nullptr;
    }
}

InstCache::CacheData::~CacheData() {
    delete[] this->block;
}

InstCache::CacheData& InstCache::CacheData::operator=(const InstCache::CacheData& that) {
    if (this != &that) {
        this->size = that.size;
        if (that.block) {
            this->block = new CacheBlock[this->size];
            for (unsigned i = 0; i < this->size; ++i) {
                this->block[i] = that.block[i];
            }
        }
        else {
            this->block = nullptr;
        }
    }
    return *this;
}

InstCache::CacheData& InstCache::CacheData::operator=(InstCache::CacheData&& that) {
    if (this != &that) {
        this->size = that.size;
        this->block = that.block;
        that.block = nullptr;
    }
    return *this;
}

void InstCache::CacheData::init(const unsigned setAssociativity) {
    delete[] this->block;
    this->size = setAssociativity;
    this->block = new CacheBlock[setAssociativity];
}

InstCache::InstCache() {
    this->blockSize = 0;
    this->setAssociativity = 0;
    this->entry = 0;
    this->data = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstCache::InstCache(const InstCache& that) {
    if (this != &that) {
        this->blockSize = that.blockSize;
        this->setAssociativity = that.setAssociativity;
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        if (that.data) {
            this->data = new CacheData[this->entry];
            for (unsigned i = 0; i < this->entry; ++i) {
                this->data[i] = that.data[i];
            }
        }
        else {
            this->data = nullptr;
        }
    }
}

InstCache::InstCache(InstCache&& that) {
    if (this != &that) {
        this->blockSize = that.blockSize;
        this->setAssociativity = that.setAssociativity;
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        this->data = that.data;
        that.data = nullptr;
    }
}

InstCache::~InstCache() {
    delete[] this->data;
}

InstCache& InstCache::operator=(const InstCache& that) {
    if (this != &that) {
        this->blockSize = that.blockSize;
        this->setAssociativity = that.setAssociativity;
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        if (that.data) {
            this->data = new CacheData[this->entry];
            for (unsigned i = 0; i < this->entry; ++i) {
                this->data[i] = that.data[i];
            }
        }
        else {
            this->data = nullptr;
        }
    }
    return *this;
}

InstCache& InstCache::operator=(InstCache&& that) {
    if (this != &that) {
        this->blockSize = that.blockSize;
        this->setAssociativity = that.setAssociativity;
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        this->data = that.data;
        that.data = nullptr;
    }
    return *this;
}

void InstCache::init(const unsigned cacheSize, const unsigned blockSize, const unsigned setAssociativity) {
    this->blockSize = blockSize;
    this->setAssociativity = setAssociativity;
    this->entry = cacheSize / setAssociativity / blockSize;
    this->data = new CacheData[this->entry];
    for (unsigned i = 0; i < this->entry; ++i) {
        this->data[i].init(setAssociativity);
    }
    this->hit = 0;
    this->miss = 0;
}

void InstCache::eraseSpecified(const unsigned physicalAddr) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            targetSet.block[i].mru = false;
            targetSet.block[i].valid = false;
        }
    }
}

void InstCache::eraseLeastUsed(const unsigned physicalAddr) {
    unsigned index = getIndex(physicalAddr);
    CacheData& targetSet = data[index];
    unsigned target = 0;
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && !targetSet.block[i].mru) {
            target = i;
            break;
        }
    }
    targetSet.block[target].mru = false;
    targetSet.block[target].valid = false;
}

bool InstCache::requestBlock(const unsigned physicalAddr) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (!targetSet.block[i].valid) {
            targetSet.block[i].init(tag);
            checkMRU(index, tag);
            return true;
        }
    }
    return false;
}

bool InstCache::search(const unsigned physicalAddr) {
    unsigned tag = getTag(physicalAddr);
    unsigned index = getIndex(physicalAddr);
    CacheData& targetSet = data[index];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        if (targetSet.block[i].valid && targetSet.block[i].tag == tag) {
            targetSet.block[i].mru = true;
            checkMRU(index, tag);
            ++hit;
            return true;
        }
    }
    ++miss;
    return false;
}

unsigned InstCache::getTag(const unsigned physicalAddr) const {
    return physicalAddr / blockSize / entry;
}

unsigned InstCache::getIndex(const unsigned physicalAddr) const {
    return physicalAddr / blockSize % entry;
}

unsigned InstCache::getHit() const {
    return this->hit;
}

unsigned InstCache::getMiss() const {
    return this->miss;
}

std::string InstCache::toString() const {
    std::string content = "Cache [valid, tag]\n";
    char temp[2048];
    for (unsigned i = 0; i < entry; ++i) {
        for (unsigned j = 0; j < setAssociativity; ++j) {
            snprintf(temp, 2048, "[%u, %u] ", data[i].block[j].valid, data[i].block[j].tag);
            content += temp;
        }
        content += "\n";
    }
    return content;
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

} /* namespace inst */
