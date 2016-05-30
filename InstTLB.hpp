/*
 * InstTLB.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_

namespace inst {

class InstTLB {
public:
    InstTLB();

    virtual ~InstTLB();

    void init(const unsigned TLBSize);

private:
    unsigned size;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_ */
