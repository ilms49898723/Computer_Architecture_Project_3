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
    originalPc = 0;
    currentPc = 0;
    cycle = 0;
    snapshot = nullptr;
    report = nullptr;
    reg.init();
    iDisk.init();
    dDisk.init();
}

void InstSimulator::loadInstruction(const unsigned* src, const unsigned len, const unsigned pc) {
    this->originalPc = pc;
    for (unsigned i = 0; i < len; ++i) {
        iDisk.setData(pc + (i << 2), src[i]);
        iDisk.setInstruction(pc + (i << 2), InstDecoder::decodeInstBin(src[i]));
    }
}

void InstSimulator::loadData(const unsigned* src, const unsigned len, const unsigned sp) {
    reg.setRegister(29, sp);
    for (unsigned i = 0; i < len; ++i) {
        dDisk.setData(i << 2, src[i]);
    }
}

void InstSimulator::setProperty(const InstParameter& iParam, const InstParameter& dParam) {
    this->iParam = iParam;
    this->dParam = dParam;
    this->iTLB.init((1024u / iParam.pageSize) >> 2);
    this->dTLB.init((1024u / dParam.pageSize) >> 2);
    this->iPageTable.init(iParam.pageSize);
    this->dPageTable.init(dParam.pageSize);
    this->iMemory.init(iParam.memSize, iParam.pageSize);
    this->dMemory.init(dParam.memSize, dParam.pageSize);
    this->iCache.init(iParam.cacheSize, iParam.cacheBlockSize, iParam.cacheSetAssociativity);
    this->dCache.init(dParam.cacheSize, dParam.cacheBlockSize, dParam.cacheSetAssociativity);
}

void InstSimulator::setLogFile(const std::string& snapshotFilename, const std::string& reportFilename) {
    this->snapshot = fopen(snapshotFilename.c_str(), "w");
    if (!this->snapshot) {
        fprintf(stderr, "%s: %s\n", snapshotFilename.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
    this->report = fopen(reportFilename.c_str(), "w");
    if (!this->report) {
        fprintf(stderr, "%s: %s\n", reportFilename.c_str(), strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void InstSimulator::start() {
    if (!snapshot || !report) {
        fprintf(stderr, "Can\'t open output files\n");
        return;
    }
    currentPc = originalPc;
    cycle = 0u;
    dumpSnapshot(snapshot);
    InstDisk tddisk = dDisk;
    while (!isHalt(iDisk.getInstruction(currentPc))) {
        const InstDataBin& inst = iDisk.getInstruction(currentPc);
        bool pcUpdated = false;
        if (inst.getInstType() == InstType::R) {
            if (isBranchR(inst)) {
                currentPc = reg.getRegister(inst.getRs());
                pcUpdated = true;
            }
            else {
                reg.setRegister(inst.getRd(), instALUR(inst));
            }
        }
        else if (inst.getInstType() == InstType::I) {
            if (isBranchI(inst)) {
                unsigned result = instALUI(inst);
                if (result) {
                    int newPc = static_cast<int>(currentPc) + 4 + 4 * toSigned(inst.getC(), 16);
                    currentPc = static_cast<unsigned>(newPc);
                    pcUpdated = true;
                }
            }
            else if (isMemoryLoad(inst)) {
                unsigned addr = instALUI(inst);
                unsigned loadedData;
                switch (inst.getOpcode()) {
                    case 0x23u:
                        loadedData = tddisk.getData(addr);
                        break;
                    case 0x21u:
                        loadedData = toUnsigned(toSigned(tddisk.getData(addr, 2), InstSize::HALF));
                        break;
                    case 0x25u:
                        loadedData = tddisk.getData(addr, 2);
                        break;
                    case 0x20u:
                        loadedData = toUnsigned(toSigned(tddisk.getData(addr, 1), InstSize::BYTE));
                        break;
                    case 0x24u:
                        loadedData = tddisk.getData(addr, 1);
                        break;
                    default:
                        loadedData = 0;
                        break;
                }
                reg.setRegister(inst.getRt(), loadedData);
            }
            else if (isMemoryStore(inst)) {
                unsigned addr = instALUI(inst);
                unsigned savedData = reg.getRegister(inst.getRt());
                switch (inst.getOpcode()) {
                    case 0x2Bu:
                        tddisk.setData(addr, savedData, 4);
                        break;
                    case 0x29u:
                        tddisk.setData(addr, savedData, 2);
                        break;
                    case 0x28u:
                        tddisk.setData(addr, savedData, 1);
                        break;
                    default:
                        break;
                }
            }
            else {
                reg.setRegister(inst.getRt(), instALUI(inst));
            }
        }
        else {
            pcUpdated = true;
            switch (inst.getOpcode()) {
                case 0x02u:
                    currentPc = ((currentPc + 4) & 0xF0000000u) | (inst.getC() << 2);
                    break;
                case 0x03u:
                    reg.setRegister(31, currentPc + 4);
                    currentPc = ((currentPc + 4) & 0xF0000000u) | (inst.getC() << 2);
                    break;
                default:
                    break;
            }
        }
        if (!pcUpdated) {
            currentPc += 4;
        }
        ++cycle;
        printf("cycle %u: %s\n", cycle, InstDecoder::decodeInstStr(inst.getInst()).toString().c_str());
        dumpSnapshot(snapshot);
    }
    fclose(snapshot);
    fclose(report);
}

void InstSimulator::dumpSnapshot(FILE* fp) const {
    // TODO missing information
    fprintf(fp, "cycle %u\n", cycle);
    for (unsigned i = 0; i < 32; ++i) {
        fprintf(fp, "$%02d: 0x%08X\n", i, reg.getRegister(i));
    }
    fprintf(fp, "PC: 0x%08X\n", currentPc);
    fprintf(fp, "\n\n");
}

void InstSimulator::search(const unsigned virtualAddr, const InstRoute type) {
    const InstParameter& param = (type == InstRoute::INST) ? iParam : dParam;
    InstTLB& tlb = (type == InstRoute::INST) ? iTLB : dTLB;
    InstPageTable& pageTable = (type == InstRoute::INST) ? iPageTable : dPageTable;
    InstMemory& memory = (type == InstRoute::INST) ? iMemory : dMemory;
    InstCache& cache = (type == InstRoute::INST) ? iCache : dCache;
    InstDisk& disk = (type == InstRoute::INST) ? iDisk : dDisk;
    unsigned vpn = virtualAddr / param.pageSize;
    unsigned ppn = 0;
    auto tlbResult = tlb.lookup(vpn);
    if (tlbResult.second) {
        ppn = tlbResult.first;
        tlb.update(vpn, cycle);
    }
    else {
        auto ptResult = pageTable.find(vpn);
        if (ptResult.second) {
            ppn = ptResult.first;
            tlb.insert(vpn, ppn, cycle);
            memory.update(ppn, cycle);
        }
        else {
            // TODO recheck and complete it
        }
    }
    unsigned physicalAddr = ppn * param.pageSize + virtualAddr % param.pageSize;

}

unsigned InstSimulator::instALUR(const InstDataBin& inst) {
    const unsigned valRs = reg.getRegister(inst.getRs());
    const unsigned valRt = reg.getRegister(inst.getRt());
    const unsigned valC = inst.getC();
    switch (inst.getFunct()) {
        case 0x20u: // add
            return valRs + valRt;
        case 0x21u: // addu
            return valRs + valRt;
        case 0x22u: // sub
            return valRs - valRt;
        case 0x24u: // and
            return valRs & valRt;
        case 0x25u: // or
            return valRs | valRt;
        case 0x26u: // xor
            return valRs ^ valRt;
        case 0x27u: // nor
            return ~(valRs | valRt);
        case 0x28u: // nand
            return ~(valRs & valRt);
        case 0x2Au: // slt
            return static_cast<unsigned>(toSigned(valRs) < toSigned(valRt));
        case 0x00u: // sll
            return valRt << valC;
        case 0x02u: // srl
            return valRt >> valC;
        case 0x03u: // sra
            return static_cast<unsigned>(static_cast<int>(valRt) >> static_cast<int>(valC));
        default:
            return 0u;
    }
}

unsigned InstSimulator::instALUI(const InstDataBin& inst) {
    const unsigned valRs = reg.getRegister(inst.getRs());
    const unsigned valRt = reg.getRegister(inst.getRt());
    const unsigned valC = inst.getC();
    switch (inst.getOpcode()) {
        case 0x08u: // addi
            return toUnsigned(toSigned(valRs) + toSigned(valC, 16));
        case 0x09u: // addiu
            return valRs + toUnsigned(toSigned(valC, 16));
        case 0x23u: // lw
        case 0x21u: // lh
        case 0x25u: // lhu
        case 0x20u: // lb
        case 0x24u: // lbu
        case 0x2Bu: // sw
        case 0x29u: // sh
        case 0x28u: // sb
            return toUnsigned(toSigned(valRs) + toSigned(valC, 16));
        case 0x0Fu: // lui // special // maybe incorrect
            return valC << 16;
        case 0x0Cu: // andi
            return valRs & valC;
        case 0x0Du: // ori
            return valRs | valC;
        case 0x0Eu: // nori
            return ~(valRs | valC);
        case 0x0Au: // slti
            return static_cast<unsigned>(toSigned(valRs) < toSigned(valC, 16));
        case 0x04u: // beq
            return static_cast<unsigned>(valRs == valRt);
        case 0x05u: // bne
            return static_cast<unsigned>(valRs != valRt);
        case 0x07u: // bgtz
            return static_cast<unsigned>(toSigned(valRs) > 0);
        default:
            return 0u;
    }
}

bool InstSimulator::isNop(const InstDataBin& inst) const {
    return !inst.getOpcode() &&
           !inst.getRt() &&
           !inst.getRd() &&
           !inst.getC() &&
           !inst.getFunct();
}

bool InstSimulator::isHalt(const InstDataBin& inst) const {
    return inst.getOpcode() == 0x3Fu;
}

bool InstSimulator::isMemoryLoad(const InstDataBin& inst) const {
    switch (inst.getOpcode()) {
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

bool InstSimulator::isMemoryStore(const InstDataBin& inst) const {
    switch (inst.getOpcode()) {
        case 0x2Bu:
        case 0x29u:
        case 0x28u:
            return true;
        default:
            return false;
    }
}

bool InstSimulator::isBranch(const InstDataBin& inst) const {
    return isBranchR(inst) ||
           isBranchI(inst) ||
           isBranchJ(inst);
}

bool InstSimulator::isBranchR(const InstDataBin& inst) const {
    return inst.getInstType() == InstType::R && inst.getFunct() == 0x08u;
}

bool InstSimulator::isBranchI(const InstDataBin& inst) const {
    if (inst.getInstType() != InstType::I) {
        return false;
    }
    return inst.getOpcode() == 0x04u || inst.getOpcode() == 0x05u || inst.getOpcode() == 0x07u;
}

bool InstSimulator::isBranchJ(const InstDataBin& inst) const {
    if (inst.getInstType() != InstType::J) {
        return false;
    }
    return inst.getOpcode() == 0x02u || inst.getOpcode() == 0x03u;
}

} /* namespace inst */
