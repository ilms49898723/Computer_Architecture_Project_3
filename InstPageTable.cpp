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

InstPageTable::InstPageTable() {
    this->entry = 0;
    this->table = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstPageTable::~InstPageTable() {
    delete[] this->table;
}

void InstPageTable::init(const unsigned pageSize) {
    delete[] this->table;
    this->entry = 1024u / pageSize;
    this->table = new PageTable[this->entry];
    this->hit = 0;
    this->miss = 0;
    printf("#Pagetable entry %u\n", entry);
}

void InstPageTable::insert(const unsigned vpn, const unsigned ppn) {
    table[vpn] = PageTable(ppn, true);
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

} /* namespace inst */
