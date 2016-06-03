/*
 * InstTLB.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_

#include <cstdio>
#include <string>
#include <utility>

namespace inst {

/**
 * Translation Look-aside Buffer
 */
class InstTLB {
private:
    class TLBData {
    public:
        TLBData(const unsigned tag = 0, const unsigned ppn = 0, const unsigned cycle = 0, const bool valid = false);

        ~TLBData();

        void init(const unsigned tag, const unsigned ppn, const unsigned cycle);

    public:
        unsigned tag;
        unsigned ppn;
        unsigned cycle;
        bool valid;
    };

public:
    /**
     * Default constructor
     */
    InstTLB();

    /**
     * Copy constructor
     */
    InstTLB(const InstTLB& that);

    /**
     * Move constructor
     */
    InstTLB(InstTLB&& that);

    /**
     * Default destructor
     */
    ~InstTLB();

    /**
     * Copy assignment
     */
    InstTLB& operator=(const InstTLB& that);

    /**
     * Move assignment
     */
    InstTLB& operator=(InstTLB&& that);

    /**
     * Initialize
     *
     * @param entry number of TLB entry
     */
    void init(const unsigned entry);

    /**
     * Add mapping vpn -> ppn to table
     *
     * @param vpn virtual page number
     * @param ppn physical page number
     * @param cycle cycle
     */
    void insert(const unsigned vpn, const unsigned ppn, const unsigned cycle);

    /**
     * Erase mapping of vpn
     *
     * @param vpn virtual page number to erase
     */
    void erase(const unsigned vpn);

    /**
     * Find vpn in table, if found, update cycle
     *
     * @param vpn virtual page number
     * @param cycle cycle
     */
    std::pair<unsigned, bool> search(const unsigned vpn, const unsigned cycle);

    /**
     * Get TLB hit
     */
    unsigned getHit() const;

    /**
     * Get TLB miss
     */
    unsigned getMiss() const;

    /**
     * Get string representation of current state
     */
    std::string toString() const;

private:
    unsigned entry;
    TLBData* data;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_ */
