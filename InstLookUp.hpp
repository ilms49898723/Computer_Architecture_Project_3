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
 * Translate opcode, funct, register
 */
class InstLookUp {
public:
    /**
     * Translate opcode to readable string
     *
     * @param src opcode to translate
     */
    static std::string opCodeLookUp(const unsigned src);

    /**
     * Translate funct to readable string
     *
     * @param src funct to translate
     */
    static std::string functLookUp(const unsigned src);

    /**
     * Translate register to readable string
     *
     * @param src register to translate
     */
    static std::string registerLookUpNumber(const unsigned src);

private:
    const static std::string opCodeLookUpTable[];
    const static std::string functLookUpTable[];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTLOOKUP_HPP_ */
