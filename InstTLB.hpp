/*
 * InstTLB.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_

#include <queue>
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

    ~InstTLB();

    void init(const unsigned entry, const unsigned pageSize);

    void push(const unsigned tag, const unsigned ppn, const unsigned cycle);

    void update(const unsigned tag, const unsigned cycle);

    void remove(const unsigned tag);

    std::pair<unsigned, bool> lookup(const unsigned tag, const unsigned cycle);

private:
    unsigned entry;
    unsigned pageSize;
    TLBData* data;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_ */
