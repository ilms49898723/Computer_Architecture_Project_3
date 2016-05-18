/*
 * InstLookUp.hpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTLOOKUP_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTLOOKUP_HPP_

#include <string>
#include "InstUtility.hpp"

namespace inst {

/**
 * Look-up table for opcode, register, funct
 */
class InstLookUp {
public:
    static std::string opCodeLookUp(const unsigned& src);

    static std::string functLookUp(const unsigned& src);

    static std::string registerLookUpNumber(const unsigned& src);

private:
    const static std::string opCodeLookUpTable[];
    const static std::string functLookUpTable[];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTLOOKUP_HPP_ */
