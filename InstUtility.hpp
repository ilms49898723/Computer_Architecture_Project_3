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
 * to std::string, if has number, use decimal
 */
template<typename Tp>
std::string toString(const Tp& val) {
    std::basic_stringstream<char> oss;
    oss << val;
    return oss.str();
}

/**
 * to std::string, if has number, use hex-decimal
 */
template<typename Tp>
std::string toHexString(const Tp& val) {
    std::basic_stringstream<char> oss;
    oss << std::showbase << std::hex << val;
    return oss.str();
}

/**
 * to upper string, "abc" -> "ABC"
 */
std::string toUpperString(std::string val);

/**
 * extend number from unsigned to 32 bits signed,
 * no sign-extended
 */
int toSigned(const unsigned& src);

/**
 * extend number from unsigned to 32 bits signed,
 * sign-extended
 */
int toSigned(const unsigned& src, const inst::InstSize& type);

/**
 * extend number from unsigned to 32 bits signed,
 * sign-extended
 */
int toSigned(const unsigned& src, const int& bits);

/**
 * change signed number to unsigned number
 */
unsigned toUnsigned(const int& src);

/**
 * get bits from range [l, r)
 * index starts from 0
 */
unsigned getBitsInRange(const unsigned& src, const int& l, const int& r);

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTUTILITY_HPP_ */
