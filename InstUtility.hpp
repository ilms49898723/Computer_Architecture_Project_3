/*
 * InstUtility.hpp
 *
 *  Created on: 2016/03/10
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTUTILITY_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTUTILITY_HPP_

#include <cctype>
#include <sstream>
#include <string>
#include "InstType.hpp"

namespace inst {

/**
 * Convert val to std::string
 * If has number, use decimal
 *
 * @param val value to convert
 */
template<typename Tp>
std::string toString(const Tp& val) {
    std::basic_stringstream<char> oss;
    oss << val;
    return oss.str();
}

/**
 * Convert val to std::string
 * If has number, use hex-decimal
 *
 * @param val value to convert
 */
template<typename Tp>
std::string toHexString(const Tp& val) {
    std::basic_stringstream<char> oss;
    oss << std::showbase << std::hex << val;
    return oss.str();
}

/**
 * Parse command-line arguments
 *
 * @param iMemArgs i-Memory Parameter to set
 * @param dMemArgs d-Memory Parameter to set
 * @param argc argc in main function
 * @param argv argv in main function
 */
void parseArgument(InstParameter& iMemArgs, InstParameter& dMemArgs, const int argc, const char** argv);

/**
 * Convert val to upper string
 *
 * @param val string to convert
 */
std::string toUpperString(std::string val);

/**
 * Extend number from unsigned to 32 bits signed, no sign-extended
 *
 * @param src source to convert
 */
int toSigned(const unsigned src);

/**
 * Extend number from unsigned to 32 bits signed, sign-extended
 *
 * @param src source to convert
 * @param type source type(size)
 */
int toSigned(const unsigned src, const inst::InstSize& type);

/**
 * Extend number from unsigned to 32 bits signed, sign-extended
 *
 * @param src source to convert
 * @param bits source bits length
 */
int toSigned(const unsigned src, const unsigned bits);

/**
 * Convert signed number to unsigned number
 *
 * @param src source to convert
 */
unsigned toUnsigned(const int src);

/**
 * Get bits from range [l, r), index starts from 0
 *
 * @param src source number
 * @param l lower loundary
 * @param r upper boundary
 */
unsigned getBitsInRange(const unsigned src, const unsigned l, const unsigned r);

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTUTILITY_HPP_ */
