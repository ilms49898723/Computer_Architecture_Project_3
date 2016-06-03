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
    this->vpn = 0;
    this->valid = false;
}

InstMemory::MemoryPage::~MemoryPage() {

}

void InstMemory::MemoryPage::init(const unsigned vpn, const unsigned cycle) {
    this->cycle = cycle;
    this->vpn = vpn;
    this->valid = true;
}

InstMemory::InstMemory() {
    this->size = 0;
    this->entry = 0;
    this->page = nullptr;
}

InstMemory::InstMemory(const InstMemory& that) {
    if (this != &that) {
        this->size = that.size;
        this->entry = that.entry;
        if (that.page) {
            this->page = new MemoryPage[this->size];
            for (unsigned i = 0; i < this->size; ++i) {
                this->page[i] = that.page[i];
            }
        }
        else {
            this->page = nullptr;
        }
    }
}

InstMemory::InstMemory(InstMemory&& that) {
    if (this != &that) {
        this->size = that.size;
        this->entry = that.entry;
        this->page = that.page;
        that.page = nullptr;
    }
}

InstMemory::~InstMemory() {
    delete[] page;
}

InstMemory& InstMemory::operator=(const InstMemory& that) {
    if (this != &that) {
        this->size = that.size;
        this->entry = that.entry;
        if (that.page) {
            this->page = new MemoryPage[this->size];
            for (unsigned i = 0; i < this->size; ++i) {
                this->page[i] = that.page[i];
            }
        }
        else {
            this->page = nullptr;
        }
    }
    return *this;
}

InstMemory& InstMemory::operator=(InstMemory&& that) {
    if (this != &that) {
        this->size = that.size;
        this->entry = that.entry;
        this->page = that.page;
        that.page = nullptr;
    }
    return *this;
}

void InstMemory::init(const unsigned size, const unsigned pageSize) {
    delete[] this->page;
    this->size = size;
    this->entry = size / pageSize;
    this->page = new MemoryPage[this->entry];
}

void InstMemory::update(const unsigned ppn, const unsigned cycle) {
    if (ppn >= entry || !page[ppn].valid) {
        return;
    }
    page[ppn].cycle = cycle;
}

void InstMemory::eraseLeastUsed() {
    std::pair<unsigned, unsigned> target = getLeastUsed();
    page[target.second].valid = false;
    page[target.second].cycle = 0;
}

std::pair<unsigned, unsigned> InstMemory::getLeastUsed() {
    unsigned index = 0;
    for (unsigned i = 0; i < entry; ++i) {
        if (page[i].valid && page[i].cycle < page[index].cycle) {
            index = i;
        }
    }
    return std::make_pair(page[index].vpn, index);
}

std::pair<unsigned, bool> InstMemory::requestPage(const unsigned vpn, const unsigned cycle) {
    for (unsigned i = 0; i < entry; ++i) {
        if (!page[i].valid) {
            page[i].init(vpn, cycle);
            return std::make_pair(i, true);
        }
    }
    return std::make_pair(0, false);
}

std::string InstMemory::toString() const {
    std::string content = "Memory\n";
    char temp[2048];
    for (unsigned i = 0; i < entry; ++i) {
        snprintf(temp, 2048, "ppn %u: vpn %u, valid %u\n", i, page[i].vpn, page[i].valid);
        content += temp;
    }
    return content;
}

} /* namespace inst */
