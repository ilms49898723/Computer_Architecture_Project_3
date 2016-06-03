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

InstTLB::InstTLB(const InstTLB& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        if (that.data) {
            this->data = new TLBData[this->entry];
            for (unsigned i = 0; i < this->entry; ++i) {
                this->data[i] = that.data[i];
            }
        }
        else {
            this->data = nullptr;
        }
    }
}

InstTLB::InstTLB(InstTLB&& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        this->data = that.data;
        that.data = nullptr;
    }
}

InstTLB::~InstTLB() {

}

InstTLB& InstTLB::operator=(const InstTLB& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        if (that.data) {
            this->data = new TLBData[this->entry];
            for (unsigned i = 0; i < this->entry; ++i) {
                this->data[i] = that.data[i];
            }
        }
        else {
            this->data = nullptr;
        }
    }
    return *this;
}

InstTLB& InstTLB::operator=(InstTLB&& that) {
    if (this != &that) {
        this->entry = that.entry;
        this->hit = that.hit;
        this->miss = that.miss;
        this->data = that.data;
        that.data = nullptr;
    }
    return *this;
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

std::string InstTLB::toString() const {
    std::string content = "TLB\n";
    char temp[2048];
    for (unsigned i = 0; i < entry; ++i) {
        snprintf(temp, 2048, "tag %u, ppn %u, valid %d\n", data[i].tag, data[i].ppn, data[i].valid);
        content += temp;
    }
    return content;
}

} /* namespace inst */
