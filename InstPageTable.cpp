/*
 * InstPageTable.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstPageTable.hpp"

namespace inst {

InstPageTable::PageTable::PageTable(const unsigned int ppn, const bool valid) {
    this->ppn = ppn;
    this->valid = valid;
}

InstPageTable::PageTable::~PageTable() {

}

InstPageTable::InstPageTable() {
    this->pageSize = 0;
    this->pageEntry = 0;
    this->table = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstPageTable::InstPageTable(const InstPageTable& that) {
    if (this != &that) {
        if (that.table) {
            this->pageSize = that.pageSize;
            this->pageEntry = that.pageEntry;
            this->table = new PageTable[this->pageEntry];
            this->hit = that.hit;
            this->miss = that.miss;
            for (unsigned i = 0; i < this->pageEntry; ++i) {
                this->table[i] = that.table[i];
            }
        }
        else {
            this->pageSize = 0;
            this->pageEntry = 0;
            this->table = nullptr;
            this->hit = 0;
            this->miss = 0;
        }
    }
}

InstPageTable::InstPageTable(InstPageTable&& that) {
    if (this != &that) {
        this->pageSize = that.pageSize;
        this->pageEntry = that.pageEntry;
        this->table = that.table;
        that.table = nullptr;
        this->hit = that.hit;
        this->miss = that.miss;
    }
}

InstPageTable::~InstPageTable() {
    delete[] this->table;
}

void InstPageTable::init(const unsigned pageSize) {
    delete[] this->table;
    this->pageSize = pageSize;
    this->pageEntry = 1024u / pageSize;
    this->table = new PageTable[this->pageEntry];
    this->hit = 0;
    this->miss = 0;
}

void InstPageTable::push(const unsigned vpn, const unsigned ppn) {
    table[vpn] = PageTable(ppn, true);
}

void InstPageTable::remove(const unsigned vpn) {
    table[vpn].valid = false;
}

std::pair<unsigned, bool> InstPageTable::lookup(const unsigned vpn) {
    if (vpn >= pageEntry) {
        ++miss;
        return std::make_pair(0, false);
    }
    (table[vpn].valid) ? ++hit : ++miss;
    return std::make_pair(table[vpn].ppn, table[vpn].valid);
}

unsigned InstPageTable::getHit() const {
    return this->hit;
}

unsigned InstPageTable::getMiss() const {
    return this->miss;
}

unsigned InstPageTable::getSize() const {
    return this->pageSize;
}

unsigned InstPageTable::getEntry() const {
    return this->pageEntry;
}

InstPageTable& InstPageTable::operator=(const InstPageTable& that) {
    if (this != &that) {
        delete[] this->table;
        if (that.table) {
            this->pageSize = that.pageSize;
            this->pageEntry = that.pageEntry;
            this->table = new PageTable[this->pageEntry];
            for (unsigned i = 0; i < this->pageEntry; ++i) {
                this->table[i] = that.table[i];
            }
            this->hit = that.hit;
            this->miss = that.miss;
        }
        else {
            this->pageSize = 0;
            this->pageEntry = 0;
            this->table = nullptr;
            this->hit = 0;
            this->miss = 0;
        }
    }
    return *this;
}

InstPageTable& InstPageTable::operator=(InstPageTable&& that) {
    if (this != &that) {
        delete[] this->table;
        this->pageSize = that.pageSize;
        this->pageEntry = that.pageEntry;
        this->table = that.table;
        that.table = nullptr;
        this->hit = that.hit;
        this->miss = that.miss;
    }
    return *this;
}

} /* namespace inst */
