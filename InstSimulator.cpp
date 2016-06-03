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

InstSimulator::InstSimulator(InstSimulator&& that) {
    if (this != &that) {
        this->originalPc = that.originalPc;
        this->currentPc = that.currentPc;
        this->cycle = that.cycle;
        this->snapshot = that.snapshot;
        this->report = that.report;
        this->reg = std::move(that.reg);
        this->iParam = std::move(that.iParam);
        this->dParam = std::move(that.dParam);
        this->iTLB = std::move(that.iTLB);
        this->dTLB = std::move(that.dTLB);
        this->iPageTable = std::move(that.iPageTable);
        this->dPageTable = std::move(that.dPageTable);
        this->iMemory = std::move(that.iMemory);
        this->dMemory = std::move(that.dMemory);
        this->iCache = std::move(that.iCache);
        this->dCache = std::move(that.dCache);
        this->iDisk = std::move(that.iDisk);
        this->dDisk = std::move(that.dDisk);
    }
}

InstSimulator::~InstSimulator() {

}

InstSimulator& InstSimulator::operator=(InstSimulator&& that) {
    if (this != &that) {
        this->originalPc = that.originalPc;
        this->currentPc = that.currentPc;
        this->cycle = that.cycle;
        this->snapshot = that.snapshot;
        this->report = that.report;
        this->reg = std::move(that.reg);
        this->iParam = std::move(that.iParam);
        this->dParam = std::move(that.dParam);
        this->iTLB = std::move(that.iTLB);
        this->dTLB = std::move(that.dTLB);
        this->iPageTable = std::move(that.iPageTable);
        this->dPageTable = std::move(that.dPageTable);
        this->iMemory = std::move(that.iMemory);
        this->dMemory = std::move(that.dMemory);
        this->iCache = std::move(that.iCache);
        this->dCache = std::move(that.dCache);
        this->iDisk = std::move(that.iDisk);
        this->dDisk = std::move(that.dDisk);
    }
    return *this;
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
    while (true) {
        ++cycle;
        search(currentPc, InstRoute::INST);
        if (isHalt(iDisk.getInstruction(currentPc))) {
            break;
        }
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
                if (instALUI(inst)) {
                    int newPc = static_cast<int>(currentPc) + 4 + 4 * toSigned(inst.getC(), 16);
                    currentPc = static_cast<unsigned>(newPc);
                    pcUpdated = true;
                }
            }
            else if (isMemoryLoad(inst)) {
                unsigned addr = instALUI(inst);
                search(addr, InstRoute::DATA);
                instMemoryLoad(inst, addr);
            }
            else if (isMemoryStore(inst)) {
                unsigned addr = instALUI(inst);
                search(addr, InstRoute::DATA);
                instMemoryStore(inst, addr);
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
        dumpSnapshot(snapshot);
    }
    dumpCMP(report);
    fclose(snapshot);
    fclose(report);
}

void InstSimulator::dumpSnapshot(FILE* fp) const {
    fprintf(fp, "cycle %u\n", cycle);
    for (unsigned i = 0; i < 32; ++i) {
        fprintf(fp, "$%02d: 0x%08X\n", i, reg.getRegister(i));
    }
    fprintf(fp, "PC: 0x%08X\n", currentPc);
    fprintf(fp, "\n\n");
}

void InstSimulator::dumpCMP(FILE* fp) const {
    fprintf(fp, "ICache :\n");
    fprintf(fp, "# hits: %u\n", iCache.getHit());
    fprintf(fp, "# misses: %u\n", iCache.getMiss());
    fprintf(fp, "\n");
    fprintf(fp, "DCache :\n");
    fprintf(fp, "# hits: %u\n", dCache.getHit());
    fprintf(fp, "# misses: %u\n", dCache.getMiss());
    fprintf(fp, "\n");
    fprintf(fp, "ITLB :\n");
    fprintf(fp, "# hits: %u\n", iTLB.getHit());
    fprintf(fp, "# misses: %u\n", iTLB.getMiss());
    fprintf(fp, "\n");
    fprintf(fp, "DTLB :\n");
    fprintf(fp, "# hits: %u\n", dTLB.getHit());
    fprintf(fp, "# misses: %u\n", dTLB.getMiss());
    fprintf(fp, "\n");
    fprintf(fp, "IPageTable :\n");
    fprintf(fp, "# hits: %u\n", iPageTable.getHit());
    fprintf(fp, "# misses: %u\n", iPageTable.getMiss());
    fprintf(fp, "\n");
    fprintf(fp, "DPageTable :\n");
    fprintf(fp, "# hits: %u\n", dPageTable.getHit());
    fprintf(fp, "# misses: %u\n", dPageTable.getMiss());
    fprintf(fp, "\n");
}

void InstSimulator::search(const unsigned virtualAddr, const InstRoute route) {
    const InstParameter& param = (route == InstRoute::INST) ? iParam : dParam;
    InstTLB& tlb = (route == InstRoute::INST) ? iTLB : dTLB;
    InstPageTable& pageTable = (route == InstRoute::INST) ? iPageTable : dPageTable;
    InstMemory& memory = (route == InstRoute::INST) ? iMemory : dMemory;
    InstCache& cache = (route == InstRoute::INST) ? iCache : dCache;
    unsigned vpn = virtualAddr / param.pageSize;
    unsigned ppn = 0;
    auto tlbResult = tlb.search(vpn, cycle);
    if (tlbResult.second) {
        ppn = tlbResult.first;
    }
    else {
        auto pageTableResult = pageTable.find(vpn);
        if (pageTableResult.second) {
            ppn = pageTableResult.first;
            tlb.insert(vpn, ppn, cycle);
            memory.update(ppn, cycle);
        }
        else {
            auto memoryResult = memory.requestPage(vpn, cycle);
            if (!memoryResult.second) {
                auto replacedAddr = memory.getLeastUsed();
                pageTable.erase(replacedAddr.first);
                tlb.erase(replacedAddr.first);
                for (unsigned i = 0; i < param.pageSize; ++i) {
                    cache.eraseSpecified(replacedAddr.second * param.pageSize + i);
                }
                memory.eraseLeastUsed();
                memoryResult = memory.requestPage(vpn, cycle);
            }
            ppn = memoryResult.first;
            memory.update(ppn, cycle);
            pageTable.insert(vpn, ppn);
            tlb.insert(vpn, ppn, cycle);
        }
    }
    unsigned physicalAddr = ppn * param.pageSize + virtualAddr % param.pageSize;
    bool cacheResult = cache.search(physicalAddr);
    if (!cacheResult) {
        if (!cache.requestBlock(physicalAddr)) {
            cache.eraseLeastUsed(physicalAddr);
            cache.requestBlock(physicalAddr);
        }
    }
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
        case 0x0Fu: // lui
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

void InstSimulator::instMemoryLoad(const InstDataBin& inst, unsigned addr) {
    unsigned loadedData;
    switch (inst.getOpcode()) {
        case 0x23u:
            loadedData = dDisk.getData(addr);
            break;
        case 0x21u:
            loadedData = toUnsigned(toSigned(dDisk.getData(addr, 2), InstSize::HALF));
            break;
        case 0x25u:
            loadedData = dDisk.getData(addr, 2);
            break;
        case 0x20u:
            loadedData = toUnsigned(toSigned(dDisk.getData(addr, 1), InstSize::BYTE));
            break;
        case 0x24u:
            loadedData = dDisk.getData(addr, 1);
            break;
        default:
            loadedData = 0;
            break;
    }
    reg.setRegister(inst.getRt(), loadedData);
}

void InstSimulator::instMemoryStore(const InstDataBin& inst, unsigned addr) {
    unsigned savedData = reg.getRegister(inst.getRt());
    switch (inst.getOpcode()) {
        case 0x2Bu:
            dDisk.setData(addr, savedData, 4);
            break;
        case 0x29u:
            dDisk.setData(addr, savedData, 2);
            break;
        case 0x28u:
            dDisk.setData(addr, savedData, 1);
            break;
        default:
            break;
    }
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

bool InstSimulator::isBranchR(const InstDataBin& inst) const {
    return inst.getInstType() == InstType::R && inst.getFunct() == 0x08u;
}

bool InstSimulator::isBranchI(const InstDataBin& inst) const {
    if (inst.getInstType() != InstType::I) {
        return false;
    }
    return inst.getOpcode() == 0x04u || inst.getOpcode() == 0x05u || inst.getOpcode() == 0x07u;
}

} /* namespace inst */
