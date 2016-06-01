/*
 * InstType.hpp
 *
 *  Created on: 2016/03/25
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTTYPE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTTYPE_HPP_

namespace inst {

/**
 * Enum for instruction elements
 * OPCODE, RS, RT, RD, C, FUNCT
 */
enum class InstElementType : unsigned {
    OPCODE, RS, RT, RD, C, FUNCT, UNDEF
};

/**
 * Enum for instruction type
 * R-type, I-type, J-type, Specialized, Undefined
 */
enum class InstType : unsigned {
    R, I, J, S, UNDEF
};

/**
 * Enum for memory size type
 * WORD: 4 bytes
 * HALFWORD: 2 bytes
 * BYTE: 1 byte
 */
enum class InstSize : unsigned {
    WORD, HALF, BYTE
};

/**
 * Enum for cache, tlb, pte... type
 * Instruction(i-image) or Data(d-image)
 */
enum class InstRoute : unsigned {
    INST, DATA
};

/**
 * Structure to store command-line arguments
 */
struct InstParameter {
    unsigned memSize;
    unsigned pageSize;
    unsigned cacheSize;
    unsigned cacheBlockSize;
    unsigned cacheSetAssociativity;

    InstParameter() {
        memSize = 0u;
        pageSize = 0u;
        cacheSize = 0u;
        cacheBlockSize = 0u;
        cacheSetAssociativity = 0u;
    }

    InstParameter(unsigned ms, unsigned ps, unsigned cs, unsigned cbs, unsigned csa) {
        memSize = ms;
        pageSize = ps;
        cacheSize = cs;
        cacheBlockSize = cbs;
        cacheSetAssociativity = csa;
    }
};

/**
 * Structure to store instruction elements
 * rs, rt, rd, etc.
 */
struct InstElement {
    unsigned val;
    InstElementType type;

    InstElement(unsigned val = 0, InstElementType type = InstElementType::UNDEF) :
            val(val), type(type) { }
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTTYPE_HPP_ */
