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
 * Decode hex-decimal format instruction set to readable string
 * All static functions
 * return type InstData defined in "InstData.h"
 */
class InstDecoder {
public:

    /**
     * decode instruction set, saved by string
     * @param src instruction to decode
     */
    static InstDataStr decodeInstStr(const unsigned& src);

    /**
     * decode instruction set, save by unsigned
     * @param src instruction to decode
     */
    static InstDataBin decodeInstBin(const unsigned& src);
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTDECODER_HPP_ */
