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
    class TLBData {
    public:
        TLBData(const unsigned tag = 0, const unsigned ppn = 0, const unsigned cycle = 0, const bool valid = false);

        ~TLBData();

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
     * Default destructor
     */
    ~InstTLB();

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
     * Update vpn cycle recorded in table
     *
     * @param vpn virtual page number
     * @param cycle cycle to update
     */
    void update(const unsigned vpn, const unsigned cycle);

    /**
     * Erase mapping of vpn
     *
     * @param vpn virtual page number to erase
     */
    void erase(const unsigned vpn);

    /**
     * Find vpn in table
     *
     * @param vpn virtual page number
     */
    std::pair<unsigned, bool> lookup(const unsigned vpn);

    /**
     * Get TLB hit
     */
    unsigned getHit() const;

    /**
     * Get TLB miss
     */
    unsigned getMiss() const;

    /**
     * Get number of TLB entry
     */
    unsigned getEntry() const;

private:
    unsigned entry;
    TLBData* data;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTTLB_HPP_ */
