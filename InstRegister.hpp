/*
 * InstRegister.hpp
 *
 *  Created on: 2016/05/18
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTREGISTER_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTREGISTER_HPP_

#include <cstring>
#include "InstType.hpp"

namespace inst {

/**
 * Register, 32 * 4 bytes
 */
class InstRegister {
public:
    /**
     * Default constructor
     */
    InstRegister();

    /**
     * Default destructor
     */
    virtual ~InstRegister();

    /**
     * Initialize
     */
    void init();

    /**
     * Get register value at specified address
     *
     * @param addr address to get
     * @param size size to get
     */
    unsigned getRegister(const unsigned addr, const unsigned size = 4u) const;

    /**
     * Get register value at specified address
     *
     * @param addr address to get
     * @param size size to get
     */
    unsigned getRegister(const unsigned addr, const InstSize& type) const;

    /**
     * Set register value at specified address
     *
     * @param addr address to set
     * @param val value to set
     * @param size size to set
     */
    void setRegister(const unsigned addr, const unsigned val, const unsigned size = 4u);

    /**
     * Set register value at specified address
     *
     * @param addr address to set
     * @param val value to set
     * @param size size to set
     */
    void setRegister(const unsigned addr, const unsigned val, const InstSize& type);

private:
    unsigned reg[32];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTREGISTER_HPP_ */
