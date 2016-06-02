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
    this->vpn = 0;
    this->data = nullptr;
}

InstMemory::MemoryPage::MemoryPage(const InstMemory::MemoryPage& that) {
    if (this != &that) {
        if (that.data) {
            this->cycle = that.cycle;
            this->size = that.size;
            this->vpn = that.vpn;
            this->data = new unsigned[this->size >> 2];
            memcpy(this->data, that.data, sizeof(unsigned) * (this->size >> 2));
        }
        else {
            this->cycle = 0;
            this->size = 0;
            this->vpn = 0;
            this->data = nullptr;
        }
    }
}

InstMemory::MemoryPage::~MemoryPage() {
    delete[] this->data;
}

void InstMemory::MemoryPage::init(const unsigned size, const unsigned vpn) {
    delete[] this->data;
    this->cycle = 0;
    this->size = size;
    this->vpn = vpn;
    this->data = new unsigned[this->size >> 2];
}

InstMemory::MemoryPage& InstMemory::MemoryPage::operator=(const InstMemory::MemoryPage& that) {
    if (this != &that) {
        delete[] this->data;
        if (that.data) {
            this->cycle = that.cycle;
            this->size = that.size;
            this->vpn = that.vpn;
            this->data = new unsigned[this->size >> 2];
            memcpy(this->data, that.data, sizeof(unsigned) * (this->size >> 2));
        }
        else {
            this->cycle = 0;
            this->size = 0;
            this->vpn = 0;
            this->data = nullptr;
        }
    }
    return *this;
}

InstMemory::InstMemory() {
    this->size = 0;
    this->entry = 0;
    this->pageSize = 0;
    this->valid = nullptr;
    this->page = nullptr;
}

InstMemory::~InstMemory() {
    delete[] valid;
    delete[] page;
}

void InstMemory::init(const unsigned size, const unsigned pageSize) {
    delete[] this->valid;
    delete[] this->page;
    this->size = size;
    this->entry = size / pageSize;
    this->pageSize = pageSize;
    this->valid = new bool[this->entry];
    this->page = new MemoryPage[this->entry];
    memset(this->valid, false, sizeof(bool) * this->entry);
}

void InstMemory::update(const unsigned ppn, const unsigned cycle) {
    if (ppn >= entry || !valid[ppn]) {
        return;
    }
    page[ppn].cycle = cycle;
}

unsigned InstMemory::flushLeast(InstDisk& disk) {
    unsigned index = 0;
    for (unsigned i = 0; i < entry; ++i) {
        if (valid[i] && page[i].cycle < page[index].cycle) {
            index = i;
        }
    }
    for (unsigned i = 0; i < page[index].size; i += 4) {
        disk.setData(page[index].vpn + i, page[index].data[i >> 2]);
    }
    return index;
}

std::pair<unsigned, bool> InstMemory::requestPage(const unsigned vpn) {
    for (unsigned i = 0; i < entry; ++i) {
        if (!valid[i]) {
            valid[i] = true;
            page[i].init(pageSize, vpn);
            return std::make_pair(i * pageSize, true);
        }
    }
    return std::make_pair(0, false);
}

unsigned InstMemory::getSize() const {
    return this->size;
}

unsigned InstMemory::getEntry() const {
    return this->entry;
}

unsigned InstMemory::getPageSize() const {
    return this->pageSize;
}

} /* namespace inst */
