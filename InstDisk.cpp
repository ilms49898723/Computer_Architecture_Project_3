/*
 * InstDisk.cpp
 *
 *  Created on: 2016/05/31
 *      Author: LittleBird
 */

#include "InstDisk.hpp"

namespace inst {

InstDisk::InstDisk() {
    data = new unsigned[1024];
    instructionSet = new InstDataBin[1024];
}

InstDisk::InstDisk(const InstDisk& that) {
    if (this != &that) {
        this->data = new unsigned[1024];
        memcpy(this->data, that.data, sizeof(unsigned) * 1024);
        this->instructionSet = new InstDataBin[1024];
        for (int i = 0; i < 1024; ++i) {
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

InstDisk& InstDisk::operator=(const InstDisk& that) {
    if (this != &that) {
        this->data = new unsigned[1024];
        memcpy(this->data, that.data, sizeof(unsigned) * 1024);
        this->instructionSet = new InstDataBin[1024];
        for (int i = 0; i < 1024; ++i) {
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
