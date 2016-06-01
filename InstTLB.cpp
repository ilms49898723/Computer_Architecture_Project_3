/*
 * InstTLB.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstTLB.hpp"

namespace inst {

InstTLB::InstTLB() {
    this->entry = 0;
    this->pageSize = 0;
    this->data = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstTLB::~InstTLB() {

}

void InstTLB::init(const unsigned entry, const unsigned pageSize) {
    delete[] this->data;
    this->entry = entry;
    this->pageSize = pageSize;
    this->data = new TLBData[entry];
    this->hit = 0;
    this->miss = 0;
}

void InstTLB::push(const unsigned tag, const unsigned ppn, const unsigned cycle) {
    unsigned index = 0;
    for (unsigned i = 0; i < entry; ++i) {
        if (!data[i].valid) {
            data[i] = TLBData(tag, ppn, cycle, true);
            return;
        }
        else {
            if (data[i].cycle < data[index].cycle) {
                index = i;
            }
        }
    }
    data[index] = TLBData(tag, ppn, cycle, true);
}

void InstTLB::update(const unsigned tag, const unsigned cycle) {
    for (unsigned i = 0; i < entry; ++i) {
        if (data[i].valid && data[i].tag == tag) {
            data[i].cycle = cycle;
            break;
        }
    }
}

void InstTLB::remove(const unsigned tag) {
    for (unsigned i = 0; i < entry; ++i) {
        if (data[i].valid && data[i].tag == tag) {
            data[i].valid = false;
            break;
        }
    }
}

std::pair<unsigned, bool> InstTLB::lookup(const unsigned tag, const unsigned cycle) {
    for (unsigned i = 0; i < entry; ++i) {
        if (data[i].valid && data[i].tag == tag) {
            data[i].cycle = cycle;
            ++hit;
            return std::make_pair(data[i].ppn, data[i].valid);
        }
    }
    ++miss;
    return std::make_pair(0, false);
}

} /* namespace inst */
