/*
 * InstMemory.hpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_

#include <cstring>
#include <string>
#include "InstUtility.hpp"
#include "InstType.hpp"

namespace inst {

/**
 * memory, 1024 bytes and 32 registers
 */
class InstMemory {

public:
    InstMemory();

    virtual ~InstMemory();

    /**
     * initialize
     */
    void init();

    /**
     * get register value at addr
     * @param addr register number to get
     * @param type load type(WORD, HALF WORD, BYTE)
     */
    unsigned getRegister(const unsigned& addr, const InstSize& type = InstSize::WORD) const;

    /**
     * set register value at addr
     * @param addr register number to set
     * @param val value to set
     * @param type set type(WORD, HALF WORD, BYTE)
     */
    void setRegister(const unsigned& addr, const unsigned& val, const InstSize& type = InstSize::WORD);

    /**
     * get memory value at addr
     * @param addr memory address to get
     * @param type load type(WORD, HALF WORD, BYTE)
     */
    unsigned getMemory(const unsigned& addr, const InstSize& type) const;

    /**
     * set memory value at addr
     * @param addr memory address to set
     * @param val value to set
     * @param type set type(WORD, HALF WORD, BYTE)
     */
    void setMemory(const unsigned& addr, const unsigned& val, const InstSize& type);

private:
    unsigned char mem[1024];
    unsigned reg[32];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
