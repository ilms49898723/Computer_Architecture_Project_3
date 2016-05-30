/*
 * InstCache.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstCache.hpp"

namespace inst {

InstCache::InstCache() {
    this->cacheSize = 0u;
    this->blockSize = 0u;
    this->setAssociativity = 0u;
}

InstCache::~InstCache() {

}

void InstCache::init(const unsigned cacheSize, const unsigned blockSize, const unsigned setAssociativity) {
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->setAssociativity = setAssociativity;
}

} /* namespace inst */
