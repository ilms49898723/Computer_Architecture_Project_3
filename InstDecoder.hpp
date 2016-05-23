/*
 * InstDecoder.hpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTDECODER_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTDECODER_HPP_

#include <string>
#include "InstDataBin.hpp"
#include "InstDataStr.hpp"
#include "InstLookUp.hpp"
#include "InstUtility.hpp"
#include "InstType.hpp"

namespace inst {

/**
 * A decoder to decode instruction set to readable string
 */
class InstDecoder {
public:
    /**
     * Decode Instruction. Store with InstDataStr
     *
     * @param src Instruction to decode
     */
    static InstDataStr decodeInstStr(const unsigned& src);

    /**
     * Decode Instruction. Store with InstDataBin
     *
     * @param src Instruction to decode
     */
    static InstDataBin decodeInstBin(const unsigned& src);
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTDECODER_HPP_ */
