/*
 * InstDisk.cpp
 *
 *  Created on: 2016/05/31
 *      Author: LittleBird
 */

#include "InstDisk.hpp"

namespace inst {

InstDisk::InstDisk() {
    this->data = new unsigned char[1024];
    this->instruction = new InstDataBin[1024 >> 2];
}

InstDisk::InstDisk(const InstDisk& that) {
    if (this != &that) {
        this->data = new unsigned char[1024];
        memcpy(this->data, that.data, sizeof(unsigned char) * 1024);
        this->instruction = new InstDataBin[1024 >> 2];
        for (int i = 0; i < (1024 >> 2); ++i) {
            this->instruction[i] = that.instruction[i];
        }
    }
}

InstDisk::InstDisk(InstDisk&& that) {
    if (this != &that) {
        this->data = that.data;
        that.data = nullptr;
        this->instruction = that.instruction;
        that.instruction = nullptr;
    }
}

InstDisk::~InstDisk() {
    delete[] this->data;
    delete[] this->instruction;
}

void InstDisk::init() {
    memset(this->data, 0, sizeof(unsigned char) * 1024);
    for (int i = 0; i < (1024 >> 2); ++i) {
        this->instruction[i] = InstDecoder::decodeInstBin(0);
    }
}

unsigned InstDisk::getData(const unsigned addr, const unsigned size) const {
    if (size == 4) {;
        return (this->data[addr] << 24) |
               (this->data[addr + 1] << 16) |
               (this->data[addr + 2] << 8) |
               (this->data[addr + 3]);
    }
    else if (size == 2) {
        return (this->data[addr] << 8) |
               (this->data[addr + 1]);
    }
    else {
        return this->data[addr];
    }
}

const InstDataBin& InstDisk::getInstruction(const unsigned addr) const {
    return this->instruction[addr >> 2];
}

void InstDisk::setData(const unsigned addr, const unsigned val, const unsigned size) {
    if (size == 4) {
        this->data[addr] = static_cast<unsigned char>((val >> 24) & 0xFFu);
        this->data[addr + 1] = static_cast<unsigned char>((val >> 16) & 0xFFu);
        this->data[addr + 2] = static_cast<unsigned char>((val >> 8) & 0xFFu);
        this->data[addr + 3] = static_cast<unsigned char>(val & 0xFFu);
    }
    else if (size == 2) {
        this->data[addr] = static_cast<unsigned char>((val >> 8) & 0xFFu);
        this->data[addr + 1] = static_cast<unsigned char>(val & 0xFFu);
    }
    else {
        this->data[addr] = static_cast<unsigned char>(val & 0xFFu);
    }
}

void InstDisk::setInstruction(const unsigned addr, const InstDataBin& val) {
    this->instruction[addr >> 2] = val;
}

void InstDisk::setInstruction(const unsigned addr, InstDataBin&& val) {
    this->instruction[addr >> 2] = std::move(val);
}

InstDisk& InstDisk::operator=(const InstDisk& that) {
    if (this != &that) {
        delete[] this->data;
        delete[] this->instruction;
        this->data = new unsigned char[1024];
        memcpy(this->data, that.data, sizeof(unsigned char) * 1024);
        this->instruction = new InstDataBin[1024 >> 2];
        for (int i = 0; i < (1024 >> 2); ++i) {
            this->instruction[i] = that.instruction[i];
        }
    }
    return *this;
}

InstDisk& InstDisk::operator=(InstDisk&& that) {
    if (this != &that) {
        delete[] this->data;
        delete[] this->instruction;
        this->data = that.data;
        that.data = nullptr;
        this->instruction = that.instruction;
        that.instruction = nullptr;
    }
    return *this;
}

}
