/*
 * InstRegister.hpp
 *
 *  Created on: 2016/05/18
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTREGISTER_HPP
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTREGISTER_HPP

#include <cstring>
#include "InstType.hpp"

namespace inst {

/**
 * Register, 32 * 4 bytes
 */
class InstRegister {
public:
    InstRegister();

    virtual ~InstRegister();

    void init();

    unsigned getRegister(const unsigned& addr, const unsigned& size = 4u) const;

    unsigned getRegister(const unsigned& addr, const InstSize& type = InstSize::WORD) const;

    void setRegister(const unsigned& addr, const unsigned& val, const unsigned& size = 4u);

    void setRegister(const unsigned& addr, const unsigned& val, const InstSize& type = InstSize::WORD);

private:
    unsigned reg[32];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTREGISTER_HPP */
