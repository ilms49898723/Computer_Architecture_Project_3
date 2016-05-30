/*
 * InstRegister.cpp
 *
 *  Created on: 2016/05/18
 *      Author: LittleBird
 */

#include "InstRegister.hpp"

namespace inst {

InstRegister::InstRegister() {
    init();
}

InstRegister::~InstRegister() {

}

void InstRegister::init() {
    memset(reg, 0, sizeof(unsigned) * 32);
}

unsigned InstRegister::getRegister(const unsigned addr, const unsigned size) const {
    switch (size) {
        case 4u:
            return getRegister(addr, InstSize::WORD);
        case 2u:
            return getRegister(addr, InstSize::HALF);
        case 1u:
            return getRegister(addr, InstSize::BYTE);
        default:
            return 0u;
    }
}

unsigned InstRegister::getRegister(const unsigned addr, const InstSize& type) const {
    if (type == InstSize::WORD) {
        return reg[addr];
    }
    else if (type == InstSize::HALF) {
        return reg[addr] & 0x0000FFFFu;
    }
    else {
        return reg[addr] & 0x000000FFu;
    }
}

void InstRegister::setRegister(const unsigned addr, const unsigned val, const unsigned size) {
    switch (size) {
        case 4u:
            setRegister(addr, val, InstSize::WORD);
            return;
        case 2u:
            setRegister(addr, val, InstSize::HALF);
            return;
        case 1u:
            setRegister(addr, val, InstSize::BYTE);
            return;
        default:
            return;
    }
}

void InstRegister::setRegister(const unsigned addr, const unsigned val, const InstSize& type) {
    if (addr == 0u) {
        return;
    }
    if (type == InstSize::WORD) {
        reg[addr] = val;
    }
    else if (type == InstSize::HALF) {
        reg[addr] = val & 0x0000FFFFu;
    }
    else {
        reg[addr] = val & 0x000000FFu;
    }
}

} /* namespace inst */
