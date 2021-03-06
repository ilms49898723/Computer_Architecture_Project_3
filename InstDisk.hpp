/*
 * InstDisk.hpp
 *
 *  Created on: 2016/05/31
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTDISK_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTDISK_HPP_

#include <cstdio>
#include <cstring>
#include "InstDataBin.hpp"
#include "InstDecoder.hpp"

namespace inst {

/**
 * Disk, 1024 bytes, fixed size
 */
class InstDisk {
public:
    /**
     * Default constructor
     */
    InstDisk();

    /**
     * Copy constructor
     */
    InstDisk(const InstDisk& that);

    /**
     * Move constructor
     */
    InstDisk(InstDisk&& that);

    /**
     * Default destructor
     */
    ~InstDisk();

    /**
     * Copy assignment
     */
    InstDisk& operator=(const InstDisk& that);

    /**
     * Move assignment
     */
    InstDisk& operator=(InstDisk&& that);

    /**
     * Initialize
     */
    void init();

    /**
     * Get data at specified address
     *
     * @param addr address to get
     * @param size size
     */
    unsigned getData(const unsigned addr, const unsigned size = 4) const;

    /**
     * Get instruction data at specified address(i-disk only)
     *
     * @param addr address to get
     */
    const InstDataBin& getInstruction(const unsigned addr) const;

    /**
     * Set data at specified address
     *
     * @param addr address to set
     * @param val data to set
     * @param size size
     */
    void setData(const unsigned addr, const unsigned val, const unsigned size = 4);

    /**
     * Set instruction data at specified address
     *
     * @param addr address to set
     * @param val instruction data to set
     */
    void setInstruction(const unsigned addr, const InstDataBin& val);

    /**
     * Set instruction data at specified address
     *
     * @param addr address to set
     * @param val instruction data to set
     */
    void setInstruction(const unsigned addr, InstDataBin&& val);

    /**
     * Get string representation of current state
     */
    std::string toString() const;

private:
    unsigned char* data;
    InstDataBin* instruction;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTDISK_HPP_ */
