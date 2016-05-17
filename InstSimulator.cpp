/*
 * InstSimulator.cpp
 *
 *  Created on: 2016/03/11
 *      Author: LittleBird
 */

#include "InstSimulator.hpp"

namespace inst {

InstSimulator::InstSimulator() {
    init();
}

InstSimulator::~InstSimulator() {

}

void InstSimulator::init() {
    memory.init();
    originalPc = 0u;
    snapshot = nullptr;
    errorDump = nullptr;
    for (int i = 0; i < InstSimulator::MAXN; ++i) {
        instList[i] = InstDecoder::decodeInstBin(0u);
    }
}

void InstSimulator::loadImageI(const unsigned* src, const unsigned& len, const unsigned& pc) {
    this->originalPc = pc;
    unsigned instSetIdx = pc >> 2;
    for (unsigned i = 0; i < len; ++i) {
        instList[instSetIdx] = InstDecoder::decodeInstBin(src[i]);
        ++instSetIdx;
    }
}

void InstSimulator::loadImageD(const unsigned* src, const unsigned& len, const unsigned& sp) {
    memory.setRegister(29, sp, InstSize::WORD);
    for (unsigned i = 0; i < len; ++i) {
        memory.setMemory(i * 4, src[i], InstSize::WORD);
    }
}

void InstSimulator::setLogFile(FILE* snapshot, FILE* errorDump) {
    this->snapshot = snapshot;
    this->errorDump = errorDump;
}

void InstSimulator::simulate() {
    if (!snapshot || !errorDump) {
        fprintf(stderr, "Can\'t open output files\n");
        return;
    }
    currentPc = originalPc;
    cycle = 0u;
    alive = true;
    while (!isHalt(instList[currentPc >> 2])) {
        if (!alive) {
            break;
        }
        dumpSnapshot(snapshot);
        ++cycle;
        currentPc += 4;
    }
}

void InstSimulator::dumpSnapshot(FILE* fp) {
    fprintf(fp, "cycle %u\n", cycle);
    for (unsigned i = 0; i < 32; ++i) {
        fprintf(fp, "$%02d: 0x%08X\n", i, memory.getRegister(i));
    }
    fprintf(fp, "PC: 0x%08X\n", currentPc);
}

unsigned InstSimulator::instMemLoad(const unsigned& addr, const InstDataBin& inst) {
    switch (inst.getOpCode()) {
        case 0x23u:
            return memory.getMemory(addr, InstSize::WORD);
        case 0x21u:
            return toUnsigned(toSigned(memory.getMemory(addr, InstSize::HALF), InstSize::HALF));
        case 0x25u:
            return memory.getMemory(addr, InstSize::HALF);
        case 0x20u:
            return toUnsigned(toSigned(memory.getMemory(addr, InstSize::BYTE), InstSize::BYTE));
        case 0x24u:
            return memory.getMemory(addr, InstSize::BYTE);
        default:
            return 0u;
    }
}

void InstSimulator::instMemStore(const unsigned& addr, const unsigned& val, const InstDataBin& inst) {
    switch (inst.getOpCode()) {
        case 0x2Bu:
            memory.setMemory(addr, val, InstSize::WORD);
            return;
        case 0x29u:
            memory.setMemory(addr, val, InstSize::HALF);
            return;
        case 0x28u:
            memory.setMemory(addr, val, InstSize::BYTE);
            return;
        default:
            return;
    }
}

bool InstSimulator::isNOP(const InstDataBin& inst) {
    return !inst.getOpCode() &&
           !inst.getRt() &&
           !inst.getRd() &&
           !inst.getC() &&
           !inst.getFunct();
}

bool InstSimulator::isHalt(const InstDataBin& inst) {
    return inst.getOpCode() == 0x3Fu;
}

bool InstSimulator::isMemoryLoad(const InstDataBin& inst) {
    switch (inst.getOpCode()) {
        case 0x23u:
        case 0x21u:
        case 0x25u:
        case 0x20u:
        case 0x24u:
            return true;
        default:
            return false;
    }
}

bool InstSimulator::isMemoryStore(const InstDataBin& inst) {
    switch (inst.getOpCode()) {
        case 0x2Bu:
        case 0x29u:
        case 0x28u:
            return true;
        default:
            return false;
    }
}

bool InstSimulator::isBranch(const InstDataBin& inst) {
    return isBranchR(inst) ||
           isBranchI(inst) ||
           isBranchJ(inst);
}

bool InstSimulator::isBranchR(const InstDataBin& inst) {
    return inst.getInstType() == InstType::R && inst.getFunct() == 0x08u;
}

bool InstSimulator::isBranchI(const InstDataBin& inst) {
    if (inst.getInstType() != InstType::I) {
        return false;
    }
    return inst.getOpCode() == 0x04u || inst.getOpCode() == 0x05u || inst.getOpCode() == 0x07u;
}

bool InstSimulator::isBranchJ(const InstDataBin& inst) {
    if (inst.getInstType() != InstType::J) {
        return false;
    }
    return inst.getOpCode() == 0x02u || inst.getOpCode() == 0x03u;
}

} /* namespace inst */
