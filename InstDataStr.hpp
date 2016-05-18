/*
 * InstData.hpp
 *
 *  Created on: 2016/03/09
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTDATASTR_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTDATASTR_HPP_

#include <string>
#include "InstUtility.hpp"
#include "InstType.hpp"

namespace inst {

/**
 * A data structure to store instruction with readable string
 */
class InstDataStr {
public:
    InstDataStr();

    virtual ~InstDataStr();

    InstType getInstType() const;

    std::string getOpCode() const;

    std::string getRs() const;

    std::string getRt() const;

    std::string getRd() const;

    std::string getC() const;

    std::string getFunct() const;

    void setInstType(const InstType& val);

    void setOpCode(const std::string& val);

    void setRs(const std::string& val);

    void setRt(const std::string& val);

    void setRd(const std::string& val);

    void setC(const std::string& val);

    void setFunct(const std::string& val);

    std::string toString() const;

private:
    InstType instType;
    std::string opCode;
    std::string rs;
    std::string rt;
    std::string rd;
    std::string c;
    std::string funct;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTDATASTR_HPP_ */
