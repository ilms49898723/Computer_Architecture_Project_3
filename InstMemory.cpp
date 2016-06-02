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
    this->valid = false;
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
    this->valid = true;
}

InstMemory::InstMemory() {
    this->size = 0;
    this->entry = 0;
    this->pageSize = 0;
    this->page = nullptr;
}

InstMemory::~InstMemory() {
    delete[] page;
}

void InstMemory::init(const unsigned size, const unsigned pageSize) {
    delete[] this->page;
    this->size = size;
    this->entry = size / pageSize;
    this->pageSize = pageSize;
    this->page = new MemoryPage[this->entry];
}

void InstMemory::update(const unsigned ppn, const unsigned cycle) {
    if (ppn >= entry || !page[ppn].valid) {
        return;
    }
    page[ppn].cycle = cycle;
}

std::pair<unsigned, unsigned> InstMemory::eraseLeastUsed(InstDisk& disk) {
    unsigned index = 0;
    for (unsigned i = 0; i < entry; ++i) {
        if (page[i].valid && page[i].cycle < page[index].cycle) {
            index = i;
        }
    }
    for (unsigned i = 0; i < (page[index].size >> 2); ++i) {
        disk.setData(page[index].vpn + (i << 2), page[index].data[i]);
    }
    page[index].valid = false;
    return std::make_pair(page[index].vpn, index * pageSize);
}

std::pair<unsigned, bool> InstMemory::requestPage(const unsigned vpn) {
    for (unsigned i = 0; i < entry; ++i) {
        if (!page[i].valid) {
            page[i].init(pageSize, vpn);
            return std::make_pair(i * pageSize, true);
        }
    }
    return std::make_pair(0, false);
}

void InstMemory::setData(const unsigned ppn, const unsigned offset, const unsigned val) {
    if (!this->page[ppn].valid) {
        return;
    }
    this->page[ppn].data[offset >> 2] = val;
}

unsigned InstMemory::getData(const unsigned ppn, const unsigned offset) {
    if (!this->page[ppn].valid) {
        return 0;
    }
    return this->page[ppn].data[offset >> 2];
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
