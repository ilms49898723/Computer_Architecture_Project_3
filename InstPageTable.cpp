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
}

InstPageTable::~InstPageTable() {

}

void InstPageTable::init(const unsigned pageSize) {
    this->pageSize = pageSize;
    this->pageEntry = 1024u / pageSize;
}

unsigned InstPageTable::size() const {
    return pageSize;
}

unsigned InstPageTable::entry() const {
    return pageEntry;
}

} /* namespace inst */
