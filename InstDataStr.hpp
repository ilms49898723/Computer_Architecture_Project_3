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
    /**
     * Default Constructor
     */
    InstDataStr();

    /**
     * Default Destructor
     */
    virtual ~InstDataStr();

    /**
     * Get InstType
     */
    InstType getInstType() const;

    /**
     * Get OpCode
     */
    std::string getOpCode() const;

    /**
     * Get Rs
     */
    std::string getRs() const;

    /**
     * Get Rt
     */
    std::string getRt() const;

    /**
     * Get Rd
     */
    std::string getRd() const;

    /**
     * Get C
     */
    std::string getC() const;

    /**
     * Get Funct
     */
    std::string getFunct() const;

    /**
     * Set InstType
     *
     * @param val InstType to set
     */
    void setInstType(const InstType& val);

    /**
     * Set OpCode
     *
     * @param val OpCode to set
     */
    void setOpCode(const std::string& val);

    /**
     * Set Rs
     *
     * @param val Rs to set
     */
    void setRs(const std::string& val);

    /**
     * Set Rt
     *
     * @param val Rt to set
     */
    void setRt(const std::string& val);

    /**
     * Set Rd
     *
     * @param val Rd to set
     */
    void setRd(const std::string& val);

    /**
     * Set C
     *
     * @param val C to set
     */
    void setC(const std::string& val);

    /**
     * Set Funct
     *
     * @param val Funct to set
     */
    void setFunct(const std::string& val);

    /**
     * Convert this to std::string
     */
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
