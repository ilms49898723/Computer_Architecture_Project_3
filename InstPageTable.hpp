/*
 * InstPageTable.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_

#include <cstdio>
#include <string>
#include <utility>

namespace inst {

class InstPageTable {
private:
    class PageTable {
    public:
        PageTable(const unsigned ppn = 0, const bool valid = false);

        ~PageTable();

        void init(const unsigned ppn);

    public:
        unsigned ppn;
        bool valid;
    };

public:
    /**
     * Default constructor
     */
    InstPageTable();

    /**
     * Copy constructor
     */
    InstPageTable(const InstPageTable& that);

    /**
     * Move constructor
     */
    InstPageTable(InstPageTable&& that);

    /**
     * Default Destructor
     */
    ~InstPageTable();

    /**
     * Copy assignment
     */
    InstPageTable& operator=(const InstPageTable& that);

    /**
     * Move assignment
     */
    InstPageTable& operator=(InstPageTable&& that);

    /**
     * Initialize page table
     *
     * @param size page size(in bytes)
     */
    void init(const unsigned pageSize);

    /**
     * Add mapping vpn -> ppn to table
     *
     * @param vpn virtual page number
     * @param ppn physical page number
     */
    void insert(const unsigned vpn, const unsigned ppn);

    /**
     * Erase vpn in table
     *
     * @param vpn virtual page number to erase
     */
    void erase(const unsigned vpn);

    /**
     * Find vpn in table
     *
     * @param vpn virtual page number to find
     */
    std::pair<unsigned, bool> find(const unsigned vpn);

    /**
     * Get PageTable hit
     */
    unsigned getHit() const;

    /**
     * Get PageTable miss
     */
    unsigned getMiss() const;

    /**
     * Get string representation of current state
     */
    std::string toString() const;

private:
    unsigned entry;
    PageTable* table;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_ */
