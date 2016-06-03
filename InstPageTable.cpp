/*
 * InstPageTable.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstPageTable.hpp"

namespace inst {

InstPageTable::PageTable::PageTable(const unsigned ppn, const bool valid) {
    this->ppn = ppn;
    this->valid = valid;
}

InstPageTable::PageTable::~PageTable() {

}

void InstPageTable::PageTable::init(const unsigned ppn) {
    this->ppn = ppn;
    this->valid = true;
}

InstPageTable::InstPageTable() {
    this->entry = 0;
    this->table = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstPageTable::InstPageTable(const InstPageTable& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        if (that.table) {
            this->table = new PageTable[this->entry];
            for (unsigned i = 0; i < this->entry; ++i) {
                this->table[i] = that.table[i];
            }
        }
        else {
            this->table = nullptr;
        }
    }
}

InstPageTable::InstPageTable(InstPageTable&& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        this->table = that.table;
        that.table = nullptr;
    }
}

InstPageTable::~InstPageTable() {
    delete[] this->table;
}

InstPageTable& InstPageTable::operator=(const InstPageTable& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        if (that.table) {
            this->table = new PageTable[this->entry];
            for (unsigned i = 0; i < this->entry; ++i) {
                this->table[i] = that.table[i];
            }
        }
        else {
            this->table = nullptr;
        }
    }
    return *this;
}

InstPageTable& InstPageTable::operator=(InstPageTable&& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        this->table = that.table;
        that.table = nullptr;
    }
    return *this;
}

void InstPageTable::init(const unsigned pageSize) {
    delete[] this->table;
    this->entry = 1024u / pageSize;
    this->table = new PageTable[this->entry];
    this->hit = 0;
    this->miss = 0;
}

void InstPageTable::insert(const unsigned vpn, const unsigned ppn) {
    table[vpn].init(ppn);
}

void InstPageTable::erase(const unsigned vpn) {
    table[vpn].valid = false;
}

std::pair<unsigned, bool> InstPageTable::find(const unsigned vpn) {
    (table[vpn].valid) ? ++hit : ++miss;
    return std::make_pair(table[vpn].ppn, table[vpn].valid);
}

unsigned InstPageTable::getHit() const {
    return this->hit;
}

unsigned InstPageTable::getMiss() const {
    return this->miss;
}

std::string InstPageTable::toString() const {
    std::string content = "PageTable\n";
    char temp[2048];
    for (unsigned i = 0; i < entry; ++i) {
        snprintf(temp, 2048, "vpn %u, ppn %u, valid %d\n", i, table[i].ppn, table[i].valid);
        content += temp;
    }
    return content;
}

} /* namespace inst */
