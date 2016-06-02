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

void InstMemory::MemoryPage::allocate(const unsigned size) {
    delete[] this->data;
    this->size = size;
    this->data = new unsigned char[this->size];
}

void InstMemory::MemoryPage::init(const unsigned vpn) {
    this->cycle = 0;
    this->vpn = vpn;
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
    for (unsigned i = 0; i < this->entry; ++i) {
        this->page[i].allocate(pageSize);
    }
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
    for (unsigned i = 0; i < page[index].size; ++i) {
        disk.setData(page[index].vpn + i, page[index].data[i], 1);
    }
    page[index].valid = false;
    return std::make_pair(page[index].vpn, index * pageSize);
}

std::pair<unsigned, bool> InstMemory::requestPage(const unsigned vpn) {
    for (unsigned i = 0; i < entry; ++i) {
        if (!page[i].valid) {
            page[i].init(vpn);
            return std::make_pair(i * pageSize, true);
        }
    }
    return std::make_pair(0, false);
}

void InstMemory::setData(const unsigned ppn, const unsigned offset, const unsigned val, const unsigned size) {
    if (!this->page[ppn].valid) {
        return;
    }
    if (size == 4) {
        this->page[ppn].data[offset] = static_cast<unsigned char>((val >> 24) & 0xFFu);
        this->page[ppn].data[offset + 1] = static_cast<unsigned char>((val >> 16) & 0xFFu);
        this->page[ppn].data[offset + 2] = static_cast<unsigned char>((val >> 8) & 0xFFu);
        this->page[ppn].data[offset + 3] = static_cast<unsigned char>((val) & 0xFFu);
    }
    else if (size == 2) {
        this->page[ppn].data[offset] = static_cast<unsigned char>((val >> 16) & 0xFFu);
        this->page[ppn].data[offset + 1] = static_cast<unsigned char>((val) & 0xFFu);
    }
    else {
        this->page[ppn].data[offset] = static_cast<unsigned char>((val) & 0xFFu);
    }
}

unsigned InstMemory::getData(const unsigned ppn, const unsigned offset, const unsigned size) {
    if (!this->page[ppn].valid) {
        return 0;
    }
    if (size == 4) {
        return (this->page[ppn].data[offset] << 24) |
               (this->page[ppn].data[offset + 1] << 16) |
               (this->page[ppn].data[offset + 2] << 8) |
               (this->page[ppn].data[offset + 3]);
    }
    else if (size == 2) {
        return (this->page[ppn].data[offset] << 8) |
               (this->page[ppn].data[offset + 1]);
    }
    else {
        return (this->page[ppn].data[offset]);
    }
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
