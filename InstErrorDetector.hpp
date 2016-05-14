/*
 * InstErrorDetector.hpp
 *
 *  Created on: 2016/03/23
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTERRORDETECTOR_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTERRORDETECTOR_HPP_

#include "InstDataBin.hpp"
#include "InstDataStr.hpp"
#include "InstUtility.hpp"
#include "InstMemory.hpp"
#include "InstType.hpp"

namespace inst {

/**
 * detect error
 * write to $0
 * overflow
 * memory address overflow
 * data misaligned
 */
class InstErrorDetector {
public:
    /**
     * check whether the register is writable(i.e. not $0)
     * @param reg register to check
     */
    static bool isRegWritable(const unsigned& reg);

    /**
     * check number overflow,
     * src0 op src1
     * @param src0 left number
     * @param src1 right number
     * @param op operator
     */
    static bool isOverflowed(const int& src0, const int& src1, const InstOpType& op);

    /**
     * check memory address(0 to 1023)
     * @param addr memory address to check
     * @param type WORD, HALFWORD, BYTE
     */
    static bool isValidMemoryAddr(const unsigned& addr, const InstSize& type);

    /**
     * check misaligned address
     * @param addr memory address to check
     * @param type WORD, HALFWORD, BYTE
     */
    static bool isAlignedAddr(const unsigned& addr, const InstSize& type);
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTERRORDETECTOR_HPP_ */
