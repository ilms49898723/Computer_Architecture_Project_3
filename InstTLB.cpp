/*
 * InstTLB.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstTLB.hpp"

namespace inst {

InstTLB::InstTLB() {
    this->tlbEntry = 0;
    this->data = nullptr;
    this->hit = 0;
    this->miss = 0;
}

InstTLB::InstTLB(const InstTLB& that) {
    if (this != &that) {
        if (that.data) {
            this->tlbEntry = that.tlbEntry;
            this->data = new TLBData[this->tlbEntry];
            for (unsigned i = 0; i < this->tlbEntry; ++i) {
                this->data[i] = that.data[i];
            }
            this->hit = that.hit;
            this->miss = that.miss;
        }
        else {
            this->tlbEntry = 0;
            this->data = nullptr;
            this->hit = 0;
            this->miss = 0;
        }
    }
}

InstTLB::InstTLB(InstTLB&& that) {
    if (this != &that) {
        this->tlbEntry = that.tlbEntry;
        this->data = that.data;
        that.data = nullptr;
        this->hit = that.hit;
        this->miss = that.miss;
    }
}

InstTLB::~InstTLB() {

}

void InstTLB::init(const unsigned entry) {
    delete[] this->data;
    this->tlbEntry = entry;
    this->data = new TLBData[entry];
    this->hit = 0;
    this->miss = 0;
}

void InstTLB::push(const unsigned vpn, const unsigned ppn, const unsigned cycle) {
    unsigned index = 0;
    for (unsigned i = 0; i < tlbEntry; ++i) {
        if (!data[i].valid) {
            data[i] = TLBData(vpn, ppn, cycle, true);
            return;
        }
        else {
            if (data[i].cycle < data[index].cycle) {
                index = i;
            }
        }
    }
    data[index] = TLBData(vpn, ppn, cycle, true);
}

void InstTLB::update(const unsigned vpn, const unsigned cycle) {
    for (unsigned i = 0; i < tlbEntry; ++i) {
        if (data[i].valid && data[i].tag == vpn) {
            data[i].cycle = cycle;
            break;
        }
    }
}

void InstTLB::remove(const unsigned vpn) {
    for (unsigned i = 0; i < tlbEntry; ++i) {
        if (data[i].valid && data[i].tag == vpn) {
            data[i].valid = false;
            break;
        }
    }
}

std::pair<unsigned, bool> InstTLB::lookup(const unsigned vpn) {
    for (unsigned i = 0; i < tlbEntry; ++i) {
        if (data[i].valid && data[i].tag == vpn) {
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

unsigned InstTLB::entry() const {
    return this->tlbEntry;
}

InstTLB& InstTLB::operator=(const InstTLB& that) {
    if (this != &that) {
        delete[] this->data;
        if (that.data) {
            this->tlbEntry = that.tlbEntry;
            this->data = new TLBData[this->tlbEntry];
            for (unsigned i = 0; i < this->tlbEntry; ++i) {
                this->data[i] = that.data[i];
            }
            this->hit = that.hit;
            this->miss = that.miss;
        }
        else {
            this->tlbEntry = 0;
            this->data = nullptr;
            this->hit = 0;
            this->miss = 0;
        }
    }
    return *this;
}

InstTLB& InstTLB::operator=(InstTLB&& that) {
    if (this != &that) {
        delete[] this->data;
        this->tlbEntry = that.tlbEntry;
        this->data = that.data;
        that.data = nullptr;
        this->hit = that.hit;
        this->miss = that.miss;
    }
    return *this;
}

} /* namespace inst */
