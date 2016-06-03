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

InstMemory::~InstMemory() {
    delete[] page;
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
    std::string content;
    char temp[2048];
    for (unsigned i = 0; i < entry; ++i) {
        snprintf(temp, 2048, "ppn %u: valid %d, vpn %u\n", i, page[i].valid, page[i].vpn);
        content += temp;
    }
    return content;
}

} /* namespace inst */
