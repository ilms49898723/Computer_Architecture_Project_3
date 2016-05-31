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

/**
 * A data structure to store instruction with native value
 */
class InstDataBin {
public:
    /**
     * Default constructor
     */
    InstDataBin();

    /**
     * Copy constructor
     */
    InstDataBin(const InstDataBin& that);

    /**
     * Move constructor
     */
    InstDataBin(InstDataBin&& that);

    /**
     * Default destructor
     */
    ~InstDataBin();

public:
    /**
     * Get InstType
     */
    InstType getInstType() const;

    /**
     * Get OpCode
     */
    unsigned getOpCode() const;

    /**
     * Get Rs
     */
    unsigned getRs() const;

    /**
     * Get Rt
     */
    unsigned getRt() const;

    /**
     * Get Rd
     */
    unsigned getRd() const;

    /**
     * Get C
     */
    unsigned getC() const;

    /**
     * Get Funct
     */
    unsigned getFunct() const;

    /**
     * Get Inst
     */
    unsigned getInst() const;

    /**
     * Get RegRead
     */
    const std::vector<InstElement>& getRegRead() const;

    /**
     * Get RegWrite
     */
    const std::vector<InstElement>& getRegWrite() const;

    /**
     * Get InstName
     */
    std::string getInstName() const;

    /**
     * Set InstType
     *
     * @param val InstType to set
     */
    void setInstType(const InstType val);

    /**
     * Set OpCode
     *
     * @param val OpCode to set
     */
    void setOpCode(const unsigned val);

    /**
     * Set Rs
     *
     * @param val Rs to set
     */
    void setRs(const unsigned val);

    /**
     * Set Rt
     *
     * @param val Rt to set
     */
    void setRt(const unsigned val);

    /**
     * Set Rd
     *
     * @param val Rd to set
     */
    void setRd(const unsigned val);

    /**
     * Set C
     *
     * @param val C to set
     */
    void setC(const unsigned val);

    /**
     * Set Funct
     *
     * @param val Funct to set
     */
    void setFunct(const unsigned val);

    /**
     * Set Inst
     *
     * @param val Inst to set
     */
    void setInst(const unsigned val);

    /**
     * Set InstName
     *
     * @param val InstName to set
     */
    void setInstName(const unsigned val);

    /**
     * Set RegRead
     *
     * @param reg RegRead to set
     */
    void setRegRead(const InstElement& reg);

    /**
     * Set RegWrite
     *
     * @param reg RegWrite to set
     */
    void setRegWrite(const InstElement& reg);

    /**
     * Copy assignment
     */
    InstDataBin& operator=(const InstDataBin& that);

    /**
     * Move assignment
     */
    InstDataBin& operator=(InstDataBin&& that);

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
