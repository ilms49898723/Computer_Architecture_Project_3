/*
 * InstPageTable.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_

#include <utility>

namespace inst {

class InstPageTable {
private:
    class PageTable {
    public:
        PageTable(const unsigned ppn = 0, const bool valid = false);

        ~PageTable();

    public:
        unsigned ppn;
        bool valid;
    };

public:
    /**
     * Default Constructor
     */
    InstPageTable();

    /**
     * Default Destructor
     */
    ~InstPageTable();

    /**
     * Initialize page table
     *
     * @param size page size(in bytes)
     */
    void init(const unsigned pageSize);

    void insert(const unsigned vpn, const unsigned ppn);

    void erase(const unsigned vpn);

    std::pair<unsigned, bool> find(const unsigned vpn);

    unsigned getHit() const;

    unsigned getMiss() const;

    unsigned getPageSize() const;

    unsigned getEntry() const;

private:
    unsigned pageSize;
    unsigned entry;
    PageTable* table;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_ */
