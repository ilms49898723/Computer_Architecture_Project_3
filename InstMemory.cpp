/*
 * InstMemory.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstMemory.hpp"

namespace inst {

InstMemory::InstMemory() {
    memset(this->reg, 0, sizeof(unsigned) * 32);
    memset(this->mem, 0, sizeof(unsigned char) * 1024);
}

InstMemory::~InstMemory() {

}

void InstMemory::init() {
    memset(reg, 0, sizeof(unsigned) * 32);
    memset(mem, 0, sizeof(unsigned char) * 1024);
}

unsigned InstMemory::getMemory(const unsigned& addr, const unsigned& size) const {
    switch (size) {
        case 4u:
            return getMemory(addr, InstSize::WORD);
        case 2u:
            return getMemory(addr, InstSize::HALF);
        case 1u:
            return getMemory(addr, InstSize::BYTE);
        default:
            return 0u;
    }
}

unsigned InstMemory::getMemory(const unsigned& addr, const InstSize& size) const {
    if (size == InstSize::WORD) {
        return (mem[addr] << 24) | (mem[addr + 1] << 16) | (mem[addr + 2] << 8) | mem[addr + 3];
    }
    else if (size == InstSize::HALF) {
        return (mem[addr] << 8) | (mem[addr + 1]);
    }
    else {
        return mem[addr];
    }
}

void InstMemory::setMemory(const unsigned& addr, const unsigned& val, const unsigned& size) {
    switch (size) {
        case 4u:
            setMemory(addr, val, InstSize::WORD);
            return;
        case 2u:
            setMemory(addr, val, InstSize::HALF);
            return;
        case 1u:
            setMemory(addr, val, InstSize::BYTE);
            return;
        default:
            return;
    }
}

void InstMemory::setMemory(const unsigned& addr, const unsigned& val, const InstSize& size) {
    if (size == InstSize::WORD) {
        mem[addr] = static_cast<unsigned char>((val >> 24) & 0xFFu);
        mem[addr + 1] = static_cast<unsigned char>((val >> 16) & 0xFFu);
        mem[addr + 2] = static_cast<unsigned char>((val >> 8) & 0xFFu);
        mem[addr + 3] = static_cast<unsigned char>(val & 0xFFu);
    }
    else if (size == InstSize::HALF) {
        mem[addr] = static_cast<unsigned char>((val >> 8) & 0xFFu);
        mem[addr + 1] = static_cast<unsigned char>(val & 0xFFu);
    }
    else {
        mem[addr] = static_cast<unsigned char>(val & 0xFFu);
    }
}

} /* namespace inst */
