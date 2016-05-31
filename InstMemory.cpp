/*
 * InstMemory.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstMemory.hpp"

namespace inst {

InstMemory::InstMemory() {
    this->data = new unsigned char[1024];
}

InstMemory::InstMemory(const InstMemory& that) {
    if (this != &that) {
        this->lruSet = that.lruSet;
        this->data = new unsigned char[1024];
        memcpy(this->data, that.data, sizeof(unsigned char) * 1024);
    }
}

InstMemory::InstMemory(InstMemory&& that) {
    if (this != &that) {
        this->lruSet = std::move(that.lruSet);
        this->data = that.data;
        that.data = nullptr;
    }
}

InstMemory::~InstMemory() {
    delete[] data;
}

void InstMemory::init() {
    memset(data, 0, sizeof(unsigned char) * 1024);
}

unsigned InstMemory::getData(const unsigned addr, const unsigned size) const {
    switch (size) {
        case 4u:
            return getData(addr, InstSize::WORD);
        case 2u:
            return getData(addr, InstSize::HALF);
        case 1u:
            return getData(addr, InstSize::BYTE);
        default:
            return 0u;
    }
}

unsigned InstMemory::getData(const unsigned addr, const InstSize& size) const {
    if (size == InstSize::WORD) {
        return (data[addr] << 24) | (data[addr + 1] << 16) | (data[addr + 2] << 8) | data[addr + 3];
    }
    else if (size == InstSize::HALF) {
        return (data[addr] << 8) | (data[addr + 1]);
    }
    else {
        return data[addr];
    }
}

void InstMemory::setData(const unsigned addr, const unsigned val, const unsigned size) {
    switch (size) {
        case 4u:
            setData(addr, val, InstSize::WORD);
            return;
        case 2u:
            setData(addr, val, InstSize::HALF);
            return;
        case 1u:
            setData(addr, val, InstSize::BYTE);
            return;
        default:
            return;
    }
}

void InstMemory::setData(const unsigned addr, const unsigned val, const InstSize& size) {
    if (size == InstSize::WORD) {
        data[addr] = static_cast<unsigned char>((val >> 24) & 0xFFu);
        data[addr + 1] = static_cast<unsigned char>((val >> 16) & 0xFFu);
        data[addr + 2] = static_cast<unsigned char>((val >> 8) & 0xFFu);
        data[addr + 3] = static_cast<unsigned char>(val & 0xFFu);
    }
    else if (size == InstSize::HALF) {
        data[addr] = static_cast<unsigned char>((val >> 8) & 0xFFu);
        data[addr + 1] = static_cast<unsigned char>(val & 0xFFu);
    }
    else {
        data[addr] = static_cast<unsigned char>(val & 0xFFu);
    }
}

InstMemory& InstMemory::operator=(const InstMemory& that) {
    if (this != &that) {
        this->lruSet = that.lruSet;
        this->data = new unsigned char[1024];
        memcpy(this->data, that.data, sizeof(unsigned char) * 1024);
    }
    return *this;
}

InstMemory& InstMemory::operator=(InstMemory&& that) {
    if (this != &that) {
        this->lruSet = std::move(that.lruSet);
        this->data = that.data;
        that.data = nullptr;
    }
    return *this;
}

} /* namespace inst */
