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
#include "InstType.hpp"
#include "InstUtility.hpp"

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
     * Get Opcode
     */
    unsigned getOpcode() const;

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
    const std::string& getInstName() const;

    /**
     * Set InstType
     *
     * @param val InstType to set
     */
    void setInstType(const InstType val);

    /**
     * Set Opcode
     *
     * @param val OpCode to set
     */
    void setOpcode(const unsigned val);

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
     * @param val opcode or funct to translate to string
     */
    void setInstName(const unsigned val);

    /**
     * Add an instruction element to RegRead
     *
     * @param element instruction element to add
     */
    void addRegRead(const InstElement& element);

    /**
     * Add an instruction element to RegWrite
     *
     * @param element instruction element to add
     */
    void addRegWrite(const InstElement& element);

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
    unsigned opcode;
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
