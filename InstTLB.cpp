/*
 * InstTLB.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstTLB.hpp"

namespace inst {

InstTLB::TLBData::TLBData(const unsigned tag, const unsigned ppn, const unsigned cycle, const bool valid) {
    this->tag = tag;
    this->ppn = ppn;
    this->cycle = cycle;
    this->valid = valid;
}

InstTLB::TLBData::~TLBData() {

}

void InstTLB::TLBData::init(const unsigned tag, const unsigned ppn, const unsigned cycle) {
    this->tag = tag;
    this->ppn = ppn;
    this->cycle = cycle;
    this->valid = true;
}

InstTLB::InstTLB() {
    this->entry = 0;
    this->data = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstTLB::~InstTLB() {

}

void InstTLB::init(const unsigned entry) {
    delete[] this->data;
    this->entry = entry;
    this->data = new TLBData[entry];
    this->hit = 0;
    this->miss = 0;
}

void InstTLB::insert(const unsigned vpn, const unsigned ppn, const unsigned cycle) {
    unsigned index = 0;
    for (unsigned i = 0; i < entry; ++i) {
        if (!data[i].valid) {
            data[i].init(vpn, ppn, cycle);
            return;
        }
        else {
            if (data[i].cycle < data[index].cycle) {
                index = i;
            }
        }
    }
    data[index].init(vpn, ppn, cycle);
}

void InstTLB::erase(const unsigned vpn) {
    for (unsigned i = 0; i < entry; ++i) {
        if (data[i].valid && data[i].tag == vpn) {
            data[i].valid = false;
            break;
        }
    }
}

std::pair<unsigned, bool> InstTLB::search(const unsigned vpn, const unsigned cycle) {
    for (unsigned i = 0; i < entry; ++i) {
        if (data[i].valid && data[i].tag == vpn) {
            data[i].cycle = cycle;
            ++hit;
            return std::make_pair(data[i].ppn, data[i].valid);
        }
    }
    ++miss;
    return std::make_pair(0, false);
}

unsigned InstTLB::getHit() const {
    return this->hit;
}

unsigned InstTLB::getMiss() const {
    return this->miss;
}

} /* namespace inst */
