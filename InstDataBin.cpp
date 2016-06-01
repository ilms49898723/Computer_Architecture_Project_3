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
    this->instName = "";
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
        this->instName = that.instName;
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
        this->instName = std::move(that.instName);
        this->regRead = std::move(that.regRead);
        this->regWrite = std::move(that.regWrite);
    }
}

InstDataBin::~InstDataBin() {

}

InstType InstDataBin::getInstType() const {
    return this->instType;
}

unsigned InstDataBin::getOpcode() const {
    return this->opcode;
}

unsigned InstDataBin::getRs() const {
    return this->rs;
}

unsigned InstDataBin::getRt() const {
    return this->rt;
}

unsigned InstDataBin::getRd() const {
    return this->rd;
}

unsigned InstDataBin::getC() const {
    return this->c;
}

unsigned InstDataBin::getFunct() const {
    return this->funct;
}

unsigned InstDataBin::getInst() const {
    return this->inst;
}

const std::string& InstDataBin::getInstName() const {
    return this->instName;
}

const std::vector<InstElement>& InstDataBin::getRegRead() const {
    return this->regRead;
}

const std::vector<InstElement>& InstDataBin::getRegWrite() const {
    return this->regWrite;
}

void InstDataBin::setInstType(const InstType val) {
    this->instType = val;
}

void InstDataBin::setOpcode(const unsigned val) {
    this->opcode = val;
}

void InstDataBin::setRs(const unsigned val) {
    this->rs = val;
}

void InstDataBin::setRt(const unsigned val) {
    this->rt = val;
}

void InstDataBin::setRd(const unsigned val) {
    this->rd = val;
}

void InstDataBin::setC(const unsigned val) {
    this->c = val;
}

void InstDataBin::setFunct(const unsigned val) {
    this->funct = val;
}

void InstDataBin::setInst(const unsigned val) {
    this->inst = val;
}

void InstDataBin::setInstName(const unsigned val) {
    if (instType == InstType::UNDEF) {
        this->instName = "";
    }
    else if (instType == InstType::R) {
        if (inst == 0u) {
            this->instName = "NOP";
        }
        else if (rt == 0u && rd == 0u && c == 0u && funct == 0u) {
            this->instName = "NOP";
        }
        else {
            this->instName = toUpperString(InstLookUp::functLookUp(val));
        }
    }
    else {
        this->instName = toUpperString(InstLookUp::opCodeLookUp(val));
    }
}

void InstDataBin::addRegRead(const InstElement& element) {
    this->regRead.push_back(element);
}

void InstDataBin::addRegWrite(const InstElement& element) {
    this->regWrite.push_back(element);
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
        this->instName = that.instName;
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
        this->instName = std::move(that.instName);
        this->regRead = std::move(that.regRead);
        this->regWrite = std::move(that.regWrite);
    }
    return *this;
}

} /* namespace inst */
