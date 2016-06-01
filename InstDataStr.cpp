/*
 * InstData.cpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#include "InstDataStr.hpp"

namespace inst {

InstDataStr::InstDataStr() {
    this->instType = InstType::UNDEF;
    this->opcode = "";
    this->rs = "";
    this->rt = "";
    this->rd = "";
    this->c = "";
    this->funct = "";
}

InstDataStr::InstDataStr(const InstDataStr& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = that.opcode;
        this->rs = that.rs;
        this->rt = that.rt;
        this->rd = that.rd;
        this->c = that.c;
        this->funct = that.funct;
    }
}

InstDataStr::InstDataStr(InstDataStr&& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = std::move(that.opcode);
        this->rs = std::move(that.rs);
        this->rt = std::move(that.rt);
        this->rd = std::move(that.rd);
        this->c = std::move(that.c);
        this->funct = std::move(that.funct);
    }
}

InstDataStr::~InstDataStr() {

}

InstType InstDataStr::getInstType() const {
    return this->instType;
}

std::string InstDataStr::getOpcode() const {
    return this->opcode;
}

std::string InstDataStr::getRs() const {
    if (instType == InstType::J || instType == InstType::S) {
        return "";
    }
    return this->rs;
}

std::string InstDataStr::getRt() const {
    if (instType == InstType::J || instType == InstType::S) {
        return "";
    }
    return this->rt;
}

std::string InstDataStr::getRd() const {
    if (instType != InstType::R) {
        return "";
    }
    return this->rd;
}

std::string InstDataStr::getC() const {
    return this->c;
}

std::string InstDataStr::getFunct() const {
    if (instType != InstType::R) {
        return "";
    }
    return this->funct;
}

void InstDataStr::setInstType(const InstType val) {
    this->instType = val;
}

void InstDataStr::setOpcode(const std::string& val) {
    this->opcode = val;
}

void InstDataStr::setRs(const std::string& val) {
    this->rs = val;
}

void InstDataStr::setRt(const std::string& val) {
    this->rt = val;
}

void InstDataStr::setRd(const std::string& val) {
    this->rd = val;
}

void InstDataStr::setC(const std::string& val) {
    this->c = val;
}

void InstDataStr::setFunct(const std::string& val) {
    this->funct = val;
}

std::string InstDataStr::toString() const {
    if (instType == InstType::R) {
        if (funct == "jr") {
            return funct + " $" + rs;
        }
        else if (funct == "sll" || funct == "srl" || funct == "sra") {
            return funct + " $" + rd + ", $" + rt + ", " + c;
        }
        else {
            return funct + " $" + rd + ", $" + rs + ", $" + rt;
        }
    }
    else if (instType == InstType::I) {
        if (opcode == "lui") {
            return opcode + " $" + rt + ", " + c;
        }
        else if (opcode == "bgtz") {
            return opcode + " $" + rs + ", " + c;
        }
        else if (opcode == "addi" || opcode == "addiu" || opcode == "lui" ||
                 opcode == "andi" || opcode == "ori" || opcode == "nori" ||
                 opcode == "slti") {
            return opcode + " $" + rt + ", $" + rs + ", " + c;
        }
        else if (opcode == "beq" || opcode == "bne") {
            return opcode + " $" + rs + ", $" + rt + ", " + c;
        }
        else {
            return opcode + " $" + rt + ", " + c + "($" + rs + ")";
        }
    }
    else if (instType == InstType::J) {
        return opcode + " " + c;
    }
    else if (instType == InstType::S) {
        return opcode;
    }
    else {
        return "undef";
    }
}

InstDataStr& InstDataStr::operator=(const InstDataStr& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = that.opcode;
        this->rs = that.rs;
        this->rt = that.rt;
        this->rd = that.rd;
        this->c = that.c;
        this->funct = that.funct;
    }
    return *this;
}

InstDataStr& InstDataStr::operator=(InstDataStr&& that) {
    if (this != &that) {
        this->instType = that.instType;
        this->opcode = std::move(that.opcode);
        this->rs = std::move(that.rs);
        this->rt = std::move(that.rt);
        this->rd = std::move(that.rd);
        this->c = std::move(that.c);
        this->funct = std::move(that.funct);
    }
    return *this;
}

} /* namespace inst */
