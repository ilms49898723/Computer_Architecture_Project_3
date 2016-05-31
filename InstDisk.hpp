/*
 * InstDisk.hpp
 *
 *  Created on: 2016/05/31
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTDISK_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTDISK_HPP_

#include "InstDataBin.hpp"

namespace inst {

class InstDisk {
public:
    InstDisk();

    InstDisk(const InstDisk& that);

    InstDisk(InstDisk&& that);

    ~InstDisk();

    InstDisk& operator=(const InstDisk& that);

    InstDisk& operator=(InstDisk&& that);

private:
    unsigned* data;
    InstDataBin* instructionSet;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTDISK_HPP_ */
