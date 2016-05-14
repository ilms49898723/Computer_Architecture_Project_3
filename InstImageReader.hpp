/*
 * InstImageReader.hpp
 *
 *  Created on: 2016/03/24
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTIMAGEREADER_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTIMAGEREADER_HPP_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <string>

namespace inst {

/**
 * A reader to read iimage.bin, dimage.bin by using C I/O
 */
class InstImageReader {
public:
    static unsigned readImageI(const std::string& filePath, unsigned* dst, unsigned* pc);

    static unsigned readImageI(FILE* iimage, unsigned* dst, unsigned* pc);

    static unsigned readImageD(const std::string& filePath, unsigned* dst, unsigned* sp);

    static unsigned readImageD(FILE* dimage, unsigned* dst, unsigned* sp);

public:
    static unsigned readWordFromBin(FILE* fin);
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTIMAGEREADER_HPP_ */
