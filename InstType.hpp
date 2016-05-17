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
 * enum class for instruction elements
 * OPCODE, RS, RT, RD, C, FUNCT
 */
enum class InstElementType : unsigned {
    OPCODE, RS, RT, RD, C, FUNCT, UNDEF
};

/**
 * enum class for basic operation type
 * add, sub
 */
enum class InstOpType : unsigned {
    ADD, SUB
};

/**
 * enum class for simulate operation
 * continue, halt
 */
enum class InstAction : unsigned {
    CONTINUE, HALT
};

/**
 * enum class for instruction type
 * R-type, I-type, J-type, Specialized, Undefined
 */
enum class InstType : unsigned {
    R, I, J, S, UNDEF
};

/**
 * enum class for memory size type
 * WORD: 4 bytes
 * HALFWORD: 2 bytes
 * BYTE: 1 byte
 */
enum class InstSize : unsigned {
    WORD, HALF, BYTE
};

/**
 * structure for record inst elements
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
