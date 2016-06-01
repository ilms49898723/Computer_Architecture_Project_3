/*
 * InstDataBin.cpp
 *
 *  Created on: 2016/03/13
 *      Author: LittleBird
 */

#include "InstDataBin.hpp"

namespace inst {

InstDataBin::InstDataBin() {
    this->instType = InstType::UNDEF;
    this->opcode = 0u;
    this->rs = 0u;
    this->rt = 0u;
    this->rd = 0u;
    this->c = 0u;
    this->funct = 0u;
    this->inst = 0u;
    this->regRead.clear();
    this->regWrite.clear();
}

InstDataBin::InstDataBin(const InstDataBin& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = that.opcode;
        this->rs = that.rs;
        this->rt = that.rt;
        this->rd = that.rd;
        this->c = that.c;
        this->funct = that.funct;
        this->inst = that.inst;
        this->regRead = that.regRead;
        this->regWrite = that.regWrite;
    }
}

InstDataBin::InstDataBin(InstDataBin&& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = that.opcode;
        this->rs = that.rs;
        this->rt = that.rt;
        this->rd = that.rd;
        this->c = that.c;
        this->funct = that.funct;
        this->inst = that.inst;
        this->regRead = std::move(that.regRead);
        this->regWrite = std::move(that.regWrite);
    }
}

InstDataBin::~InstDataBin() {

}

InstType InstDataBin::getInstType() const {
    return instType;
}

unsigned InstDataBin::getOpcode() const {
    return opcode;
}

unsigned InstDataBin::getRs() const {
    return rs;
}

unsigned InstDataBin::getRt() const {
    return rt;
}

unsigned InstDataBin::getRd() const {
    return rd;
}

unsigned InstDataBin::getC() const {
    return c;
}

unsigned InstDataBin::getFunct() const {
    return funct;
}

unsigned InstDataBin::getInst() const {
    return inst;
}

const std::string& InstDataBin::getInstName() const {
    return instName;
}

const std::vector<InstElement>& InstDataBin::getRegRead() const {
    return regRead;
}

const std::vector<InstElement>& InstDataBin::getRegWrite() const {
    return regWrite;
}

void InstDataBin::setInstType(const InstType val) {
    instType = val;
}

void InstDataBin::setOpcode(const unsigned val) {
    opcode = val;
}

void InstDataBin::setRs(const unsigned val) {
    rs = val;
}

void InstDataBin::setRt(const unsigned val) {
    rt = val;
}

void InstDataBin::setRd(const unsigned val) {
    rd = val;
}

void InstDataBin::setC(const unsigned val) {
    c = val;
}

void InstDataBin::setFunct(const unsigned val) {
    funct = val;
}

void InstDataBin::setInst(const unsigned val) {
    inst = val;
}

void InstDataBin::setInstName(const unsigned val) {
    if (instType == InstType::UNDEF) {
        instName = "";
    }
    else if (instType == InstType::R) {
        if (inst == 0u) {
            instName = "NOP";
        }
        else if (rt == 0u && rd == 0u && c == 0u && funct == 0u) {
            instName = "NOP";
        }
        else {
            instName = toUpperString(InstLookUp::functLookUp(val));
        }
    }
    else {
        instName = toUpperString(InstLookUp::opCodeLookUp(val));
    }
}

void InstDataBin::setRegRead(const InstElement& reg) {
    regRead.push_back(reg);
}

void InstDataBin::setRegWrite(const InstElement& reg) {
    regWrite.push_back(reg);
}

InstDataBin& InstDataBin::operator=(const InstDataBin& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = that.opcode;
        this->rs = that.rs;
        this->rt = that.rt;
        this->rd = that.rd;
        this->c = that.c;
        this->funct = that.funct;
        this->inst = that.inst;
        this->regRead = that.regRead;
        this->regWrite = that.regWrite;
    }
    return *this;
}

InstDataBin& InstDataBin::operator=(InstDataBin&& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = that.opcode;
        this->rs = that.rs;
        this->rt = that.rt;
        this->rd = that.rd;
        this->c = that.c;
        this->funct = that.funct;
        this->inst = that.inst;
        this->regRead = std::move(that.regRead);
        this->regWrite = std::move(that.regWrite);
    }
    return *this;
}

} /* namespace inst */
