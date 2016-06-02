/*
 * InstTLB.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_

#include <utility>

namespace inst {

/**
 * Translation Look-aside Buffer
 */
class InstTLB {
private:
    struct TLBData {
        unsigned tag;
        unsigned ppn;
        unsigned cycle;
        bool valid;
        TLBData(const unsigned tag = 0, const unsigned ppn = 0, const unsigned cycle = 0, const bool valid = false) :
                tag(tag), ppn(ppn), cycle(cycle), valid(valid) {}
    };

public:
    InstTLB();

    InstTLB(const InstTLB& that);

    InstTLB(InstTLB&& that);

    ~InstTLB();

    void init(const unsigned entry);

    void push(const unsigned vpn, const unsigned ppn, const unsigned cycle);

    void update(const unsigned vpn, const unsigned cycle);

    void remove(const unsigned vpn);

    std::pair<unsigned, bool> lookup(const unsigned vpn);

    unsigned getHit() const;

    unsigned getMiss() const;

    unsigned getEntry() const;

    InstTLB& operator=(const InstTLB& that);

    InstTLB& operator=(InstTLB&& that);

private:
    unsigned tlbEntry;
    TLBData* data;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_ */
