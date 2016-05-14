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

class InstLookUp {
public:
    /**
     * translate opCode -> readable string
     * @param src opCode to translate
     */
    static std::string opCodeLookUp(const unsigned& src);

    /**
     * translate funct -> readable string
     * @param src funct to translate
     */
    static std::string functLookUp(const unsigned& src);

    /**
     * translate register name -> numbers
     * @param src register name to translate
     */
    static std::string registerLookUpNumber(const unsigned& src);

private:
    const static std::string opCodeLookUpTable[];
    const static std::string functLookUpTable[];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTLOOKUP_HPP_ */
