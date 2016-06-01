/*
 * InstMemory.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstMemory.hpp"

namespace inst {

InstMemory::InstMemory() {
    this->size = 0;
    this->data = nullptr;
}

InstMemory::InstMemory(const InstMemory& that) {
    if (this != &that) {
        if (!that.data) {
            this->size = that.size;
            this->data = new unsigned[this->size >> 2];
            memcpy(this->data, that.data, sizeof(unsigned) * (this->size >> 2));
            this->lruSet = that.lruSet;
        }
        else {
            this->size = 0;
            this->data = nullptr;
        }
    }
}

InstMemory::InstMemory(InstMemory&& that) {
    if (this != &that) {
        this->size = that.size;
        this->data = that.data;
        that.data = nullptr;
        this->lruSet = std::move(that.lruSet);
    }
}

InstMemory::~InstMemory() {
    delete[] data;
}

void InstMemory::init(const unsigned size) {
    delete[] this->data;
    this->size = size;
    this->data = new unsigned[size >> 2];
    memset(this->data, 0, sizeof(unsigned) * (size >> 2));
    while (!lruSet.empty()) {
        lruSet.pop();
    }
    for (unsigned i = 0; i < size; i += 4) {
        lruSet.push(MemoryLRU(i, 0));
    }
}

unsigned InstMemory::getData(const unsigned addr, const unsigned size) const {
    switch (size) {
        case 4u:
            return getData(addr, InstSize::WORD);
        case 2u:
            return getData(addr, InstSize::HALF);
        case 1u:
            return getData(addr, InstSize::BYTE);
        default:
            return 0u;
    }
}

unsigned InstMemory::getData(const unsigned addr, const InstSize size) const {
    if (size == InstSize::WORD) {
        return data[addr >> 2] & 0xFFFFFFFFu;
    }
    else if (size == InstSize::HALF) {
        return data[addr >> 2] & 0xFFFFu;
    }
    else {
        return data[addr >> 2] & 0xFFu;
    }
}

unsigned InstMemory::getSize() const {
    return size;
}

void InstMemory::setData(const unsigned addr, const unsigned val, const unsigned size) {
    switch (size) {
        case 4u:
            setData(addr, val, InstSize::WORD);
            return;
        case 2u:
            setData(addr, val, InstSize::HALF);
            return;
        case 1u:
            setData(addr, val, InstSize::BYTE);
            return;
        default:
            return;
    }
}

void InstMemory::setData(const unsigned addr, const unsigned val, const InstSize size) {
    if (size == InstSize::WORD) {
        data[addr >> 2] = val;
    }
    else if (size == InstSize::HALF) {
        data[addr >> 2] &= 0xFFFF0000u;
        data[addr >> 2] |= (val & 0xFFFFu);
    }
    else {
        data[addr >> 2] &= 0xFFFFFF00u;
        data[addr >> 2] |= (val & 0xFFu);
    }
}

InstMemory& InstMemory::operator=(const InstMemory& that) {
    if (this != &that) {
        delete[] this->data;
        if (!that.data) {
            this->size = that.size;
            this->data = new unsigned[this->size >> 2];
            memcpy(this->data, that.data, sizeof(unsigned) * (this->size >> 2));
            this->lruSet = that.lruSet;
        }
        else {
            this->size = 0;
            this->data = nullptr;
        }
    }
    return *this;
}

InstMemory& InstMemory::operator=(InstMemory&& that) {
    if (this != &that) {
        delete[] this->data;
        this->size = that.size;
        this->data = that.data;
        that.data = nullptr;
        this->lruSet = std::move(lruSet);
    }
    return *this;
}

} /* namespace inst */
