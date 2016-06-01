/*
 * InstPageTable.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstPageTable.hpp"

namespace inst {

InstPageTable::InstPageTable() {
    this->pageSize = 0u;
    this->pageEntry = 0u;
    this->data = nullptr;
}

InstPageTable::InstPageTable(const InstPageTable& that) {
    if (this != &that) {
        if (that.data) {
            this->pageSize = that.pageSize;
            this->pageEntry = that.pageEntry;
            this->data = new PageTableData[this->pageEntry];
            for (unsigned i = 0; i < this->pageEntry; ++i) {
                this->data[i] = that.data[i];
            }
        }
        else {
            this->pageSize = 0;
            this->pageEntry = 0;
            this->data = nullptr;
        }
    }
}

InstPageTable::InstPageTable(InstPageTable&& that) {
    if (this != &that) {
        this->pageSize = that.pageSize;
        this->pageEntry = that.pageEntry;
        this->data = that.data;
        that.data = nullptr;
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
}

void InstPageTable::push(const unsigned tag, const unsigned ppn) {
    data[tag] = PageTableData(ppn, true);
}

void InstPageTable::remove(const unsigned tag) {
    data[tag].valid = false;
}

std::pair<unsigned, bool> InstPageTable::lookup(const unsigned tag) {
    if (tag >= pageEntry) {
        return std::make_pair(0, false);
    }
    return std::make_pair(data[tag].ppn, data[tag].valid);
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
        }
        else {
            this->pageSize = 0;
            this->pageEntry = 0;
            this->data = nullptr;
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
    }
    return *this;
}

} /* namespace inst */
