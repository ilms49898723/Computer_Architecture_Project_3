/*
 * InstCache.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstCache.hpp"

namespace inst {

InstCache::CacheBlock::CacheBlock() {
    this->content = nullptr;
    this->tag = 0;
}

InstCache::CacheBlock::~CacheBlock() {
    delete[] this->content;
}

void InstCache::CacheBlock::init(const unsigned size) {
    delete[] this->content;
    this->content = new unsigned[size];
}

InstCache::CacheData::CacheData() {
    this->size = 0;
    this->valid = nullptr;
    this->mru = nullptr;
    this->block = nullptr;
}

InstCache::CacheData::~CacheData() {
    delete[] this->valid;
    delete[] this->mru;
    delete[] this->block;
}

void InstCache::CacheData::init(const unsigned setAssociativity, const unsigned blockSize) {
    delete[] this->valid;
    delete[] this->mru;
    delete[] this->block;
    this->size = setAssociativity;
    this->valid = new bool[setAssociativity];
    this->mru = new bool[setAssociativity];
    this->block = new CacheBlock[setAssociativity];
    for (unsigned i = 0; i < setAssociativity; ++i) {
        this->block[i].init(blockSize);
    }
}

InstCache::InstCache() {
    this->cacheSize = 0;
    this->blockSize = 0;
    this->setAssociativity = 0;
    this->entry = 0;
    this->data = nullptr;
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

} /* namespace inst */
