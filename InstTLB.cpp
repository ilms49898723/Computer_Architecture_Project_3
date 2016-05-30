/*
 * InstTLB.cpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#include "InstTLB.hpp"

namespace inst {

InstTLB::InstTLB() {
    this->size = 0u;
}

InstTLB::~InstTLB() {

}

void InstTLB::init(const unsigned size) {
    this->size = size;
}

} /* namespace inst */
