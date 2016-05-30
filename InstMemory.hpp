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
    /**
     * Default constructor
     */
    InstMemory();

    /**
     * Default destructor
     */
    virtual ~InstMemory();

    /**
     * Initialize
     */
    void init();

    /**
     * Get data value at specified address
     *
     * @param addr address to get
     * @param size size to get
     */
    unsigned getData(const unsigned& addr, const unsigned& size) const;

    /**
     * Get data value at specified address
     *
     * @param addr address to get
     * @param size size to get
     */
    unsigned getData(const unsigned& addr, const InstSize& size) const;

    /**
     * Set data value at specified address
     *
     * @param addr address to set
     * @param val value to set
     * @param size size to set
     */
    void setData(const unsigned& addr, const unsigned& val, const unsigned& size);

    /**
     * Set data value at specified address
     *
     * @param addr address to set
     * @param val value to set
     * @param size size to set
     */
    void setData(const unsigned& addr, const unsigned& val, const InstSize& size);

private:
    unsigned char data[1024];
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTMEMORY_HPP_ */
