/*
 * InstUtility.cpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#include "InstUtility.hpp"

namespace inst {

void parseArgument(InstParameter& iMemArgs, InstParameter& dMemArgs, const int argc, const char** argv) {
    if (argc == 1) {
        iMemArgs = InstParameter(64, 8, 16, 4, 4);
        dMemArgs = InstParameter(32, 16, 16, 4, 1);
        return;
    }
    if (argc != 10) {
        iMemArgs = InstParameter();
        dMemArgs = InstParameter();
        return;
    }
    iMemArgs = InstParameter(static_cast<unsigned>(atoi(argv[1])),
                             static_cast<unsigned>(atoi(argv[3])),
                             static_cast<unsigned>(atoi(argv[5])),
                             static_cast<unsigned>(atoi(argv[6])),
                             static_cast<unsigned>(atoi(argv[7])));
    dMemArgs = InstParameter(static_cast<unsigned>(atoi(argv[2])),
                             static_cast<unsigned>(atoi(argv[4])),
                             static_cast<unsigned>(atoi(argv[8])),
                             static_cast<unsigned>(atoi(argv[9])),
                             static_cast<unsigned>(atoi(argv[10])));
}

std::string toUpperString(std::string val) {
    for (unsigned long long i = 0; i < val.length(); ++i) {
        val[i] = static_cast<char>(toupper(static_cast<int>(val[i])));
    }
    return val;
}

int toSigned(const unsigned src) {
    return static_cast<int>(src);
}

int toSigned(const unsigned src, const InstSize& type) {
    if (type == InstSize::WORD) {
        return static_cast<int>(src);
    }
    else if (type == InstSize::HALF) {
        int var = static_cast<int>(src << 16);
        int ret = var >> 16;
        return ret;
    }
    else {
        int var = static_cast<int>(src << 24);
        int ret = var >> 24;
        return ret;
    }
}

int toSigned(const unsigned src, const unsigned bits) {
    int var = static_cast<int>(src << (32 - bits));
    int ret = var >> (32 - bits);
    return ret;
}

unsigned toUnsigned(const int src) {
    return static_cast<unsigned>(src);
}

unsigned getBitsInRange(const unsigned src, const unsigned l, const unsigned r) {
    return (src << (32 - r)) >> (l + (32 - r));
}

} /* namespace inst */
