/*
 * InstDataBin.hpp
 *
 *  Created on: 2016/03/13
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTDATABIN_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTDATABIN_HPP_

#include <string>
#include <vector>
#include "InstLookUp.hpp"
#include "InstUtility.hpp"
#include "InstType.hpp"

namespace inst {

class InstDataBin {
public:
    InstDataBin();

    virtual ~InstDataBin();

    InstType getInstType() const;

    unsigned getOpCode() const;

    unsigned getRs() const;

    unsigned getRt() const;

    unsigned getRd() const;

    unsigned getC() const;

    unsigned getFunct() const;

    unsigned getInst() const;

    const std::vector<InstElement>& getRegRead() const;

    const std::vector<InstElement>& getRegWrite() const;

    std::string getInstName() const;

    void setInstType(const InstType& val);

    void setOpCode(const unsigned& val);

    void setRs(const unsigned& val);

    void setRt(const unsigned& val);

    void setRd(const unsigned& val);

    void setC(const unsigned& val);

    void setFunct(const unsigned& val);

    void setInst(const unsigned& val);

    void setInstName(const unsigned& val);

    void setRegRead(const InstElement& reg);

    void setRegWrite(const InstElement& reg);

private:
    InstType instType;
    unsigned opCode;
    unsigned rs;
    unsigned rt;
    unsigned rd;
    unsigned c;
    unsigned funct;
    unsigned inst;
    std::string instName;
    std::vector<InstElement> regRead;
    std::vector<InstElement> regWrite;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTDATABIN_HPP_ */
