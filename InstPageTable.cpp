/*
 * InstPageTable.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstPageTable.hpp"

namespace inst {

InstPageTable::InstPageTable() {
    this->pageSize = 0;
    this->pageEntry = 0;
    this->data = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstPageTable::InstPageTable(const InstPageTable& that) {
    if (this != &that) {
        if (that.data) {
            this->pageSize = that.pageSize;
            this->pageEntry = that.pageEntry;
            this->data = new PageTableData[this->pageEntry];
            this->hit = that.hit;
            this->miss = that.miss;
            for (unsigned i = 0; i < this->pageEntry; ++i) {
                this->data[i] = that.data[i];
            }
        }
        else {
            this->pageSize = 0;
            this->pageEntry = 0;
            this->data = nullptr;
            this->hit = 0;
            this->miss = 0;
        }
    }
}

InstPageTable::InstPageTable(InstPageTable&& that) {
    if (this != &that) {
        this->pageSize = that.pageSize;
        this->pageEntry = that.pageEntry;
        this->data = that.data;
        that.data = nullptr;
        this->hit = that.hit;
        this->miss = that.miss;
    }
}

InstPageTable::~InstPageTable() {
    delete[] this->data;
}

void InstPageTable::init(const unsigned pageSize) {
    delete[] this->data;
    this->pageSize = pageSize;
    this->pageEntry = 1024u / pageSize;
    this->data = new PageTableData[this->pageEntry];
    this->hit = 0;
    this->miss = 0;
}

void InstPageTable::push(const unsigned vpn, const unsigned ppn) {
    data[vpn] = PageTableData(ppn, true);
}

void InstPageTable::remove(const unsigned vpn) {
    data[vpn].valid = false;
}

std::pair<unsigned, bool> InstPageTable::lookup(const unsigned vpn) {
    if (vpn >= pageEntry) {
        ++miss;
        return std::make_pair(0, false);
    }
    if (data[vpn].valid) {
        ++hit;
    }
    else {
        ++miss;
    }
    return std::make_pair(data[vpn].ppn, data[vpn].valid);
}

unsigned InstPageTable::getHit() const {
    return this->hit;
}

unsigned InstPageTable::getMiss() const {
    return this->miss;
}

unsigned InstPageTable::size() const {
    return this->pageSize;
}

unsigned InstPageTable::entry() const {
    return this->pageEntry;
}

InstPageTable& InstPageTable::operator=(const InstPageTable& that) {
    if (this != &that) {
        delete[] this->data;
        if (that.data) {
            this->pageSize = that.pageSize;
            this->pageEntry = that.pageEntry;
            this->data = new PageTableData[this->pageEntry];
            for (unsigned i = 0; i < this->pageEntry; ++i) {
                this->data[i] = that.data[i];
            }
            this->hit = that.hit;
            this->miss = that.miss;
        }
        else {
            this->pageSize = 0;
            this->pageEntry = 0;
            this->data = nullptr;
            this->hit = 0;
            this->miss = 0;
        }
    }
    return *this;
}

InstPageTable& InstPageTable::operator=(InstPageTable&& that) {
    if (this != &that) {
        delete[] this->data;
        this->pageSize = that.pageSize;
        this->pageEntry = that.pageEntry;
        this->data = that.data;
        that.data = nullptr;
        this->hit = that.hit;
        this->miss = that.miss;
    }
    return *this;
}

} /* namespace inst */
