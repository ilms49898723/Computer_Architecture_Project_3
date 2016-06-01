/*
 * InstDisk.cpp
 *
 *  Created on: 2016/05/31
 *      Author: LittleBird
 */

#include "InstDisk.hpp"

namespace inst {

InstDisk::InstDisk() {
    data = new unsigned[1024 >> 2];
    instructionSet = new InstDataBin[1024 >> 2];
}

InstDisk::InstDisk(const InstDisk& that) {
    if (this != &that) {
        this->data = new unsigned[1024 >> 2];
        memcpy(this->data, that.data, sizeof(unsigned) * (1024 >> 2));
        this->instructionSet = new InstDataBin[1024 >> 2];
        for (int i = 0; i < (1024 >> 2); ++i) {
            this->instructionSet[i] = that.instructionSet[i];
        }
    }
}

InstDisk::InstDisk(InstDisk&& that) {
    if (this != &that) {
        this->data = that.data;
        that.data = nullptr;
        this->instructionSet = that.instructionSet;
        that.instructionSet = nullptr;
    }
}

InstDisk::~InstDisk() {
    delete[] data;
    delete[] instructionSet;
}

unsigned InstDisk::getData(const unsigned addr) const {
    return data[addr >> 2];
}

const InstDataBin& InstDisk::getInstruction(const unsigned addr) const {
    return instructionSet[addr >> 2];
}

void InstDisk::setData(const unsigned addr, const unsigned val) {
    data[addr >> 2] = val;
}

void InstDisk::setInstruction(const unsigned addr, const InstDataBin& val) {
    instructionSet[addr >> 2] = val;
}

void InstDisk::setInstruction(const unsigned addr, InstDataBin&& val) {
    instructionSet[addr >> 2] = std::move(val);
}

InstDisk& InstDisk::operator=(const InstDisk& that) {
    if (this != &that) {
        delete[] this->data;
        this->data = new unsigned[1024 >> 2];
        memcpy(this->data, that.data, sizeof(unsigned) * (1024 >> 2));
        delete[] this->instructionSet;
        this->instructionSet = new InstDataBin[1024 >> 2];
        for (int i = 0; i < (1024 >> 2); ++i) {
            this->instructionSet[i] = that.instructionSet[i];
        }
    }
    return *this;
}

InstDisk& InstDisk::operator=(InstDisk&& that) {
    if (this != &that) {
        this->data = that.data;
        that.data = nullptr;
        this->instructionSet = that.instructionSet;
        that.instructionSet = nullptr;
    }
    return *this;
}

}
