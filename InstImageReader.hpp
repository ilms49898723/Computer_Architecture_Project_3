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
 * A reader to read iimage.bin, dimage.bin using C I/O
 */
class InstImageReader {
public:
    /**
     * Read iimage.bin
     *
     * @param filePath path to iimage.bin
     * @param dst pointer to store data
     * @param pc initial pc
     */
    static unsigned readInstImage(const std::string& filePath, unsigned* dst, unsigned* pc);

    /**
     * Read iimage.bin
     *
     * @param iimage FILE* to iimage.bin
     * @param dst pointer to store data
     * @param pc initial pc
     */
    static unsigned readInstImage(FILE* iimage, unsigned* dst, unsigned* pc);

    /**
     * Read dimage.bin
     *
     * @param filePath path to dimage.bin
     * @param dst pointer to store data
     * @param sp initial sp
     */
    static unsigned readDataImage(const std::string& filePath, unsigned* dst, unsigned* sp);

    /**
     * Read dimage.bin
     *
     * @param dimage FILE* to dimage.bin
     * @param dst pointer to store data
     * @param sp initial sp
     */
    static unsigned readDataImage(FILE* dimage, unsigned* dst, unsigned* sp);

    /**
     * Read a word(4 byte) from FILE*, return as unsigned
     *
     * @param fin FILE* want to read
     */
    static unsigned readWordFromBin(FILE* fin);
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTIMAGEREADER_HPP_ */
