/*
 * InstMemory.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstMemory.hpp"

namespace inst {

InstMemory::MemoryPage::MemoryPage() {
    this->cycle = 0;
    this->size = 0;
    this->data = nullptr;
}

InstMemory::MemoryPage::MemoryPage(const InstMemory::MemoryPage& that) {
    if (this != &that) {
        if (that.data) {
            this->cycle = that.cycle;
            this->size = that.size;
            this->data = new unsigned[this->size >> 2];
            memcpy(this->data, that.data, sizeof(unsigned) * (this->size >> 2));
        }
        else {
            this->cycle = 0;
            this->size = 0;
            this->data = nullptr;
        }
    }
}

InstMemory::MemoryPage::~MemoryPage() {
    delete[] this->data;
}

void InstMemory::MemoryPage::init(const unsigned size) {
    delete[] this->data;
    this->cycle = 0;
    this->size = size;
    this->data = new unsigned[this->size >> 2];
}

InstMemory::MemoryPage& InstMemory::MemoryPage::operator=(const InstMemory::MemoryPage& that) {
    if (this != &that) {
        delete[] this->data;
        if (that.data) {
            this->cycle = that.cycle;
            this->size = that.size;
            this->data = new unsigned[this->size >> 2];
            memcpy(this->data, that.data, sizeof(unsigned) * (this->size >> 2));
        }
        else {
            this->cycle = 0;
            this->size = 0;
            this->data = nullptr;
        }
    }
    return *this;
}

InstMemory::InstMemory() {
    this->size = 0;
    this->valid = nullptr;
    this->data = nullptr;
}

InstMemory::~InstMemory() {
    delete[] valid;
    delete[] data;
}

void InstMemory::init(const unsigned size, const unsigned pageSize) {
    delete[] this->valid;
    delete[] this->data;
    this->size = size;
    this->entry = size / pageSize;
    this->valid = new bool[this->entry];
    this->data = new MemoryPage[this->entry];
    memset(this->valid, false, sizeof(bool) * this->entry);
}

unsigned InstMemory::getSize() const {
    return size;
}

unsigned InstMemory::getEntry() const {
    return entry;
}

} /* namespace inst */
