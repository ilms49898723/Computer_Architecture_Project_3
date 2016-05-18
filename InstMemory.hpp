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
 * Memory, 1024 bytes
 */
class InstMemory {
public:
    InstMemory();

    virtual ~InstMemory();

    void init();

    unsigned getMemory(const unsigned& addr, const unsigned& size) const;

    unsigned getMemory(const unsigned& addr, const InstSize& size) const;

    void setMemory(const unsigned& addr, const unsigned& val, const unsigned& size);

    void setMemory(const unsigned& addr, const unsigned& val, const InstSize& size);

private:
    unsigned char mem[1024];
    unsigned reg[32];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
