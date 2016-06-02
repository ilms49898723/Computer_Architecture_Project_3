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
    InstPageTable();

    InstPageTable(const InstPageTable& that);

    InstPageTable(InstPageTable&& that);

    ~InstPageTable();

    void init(const unsigned pageSize);

    void push(const unsigned vpn, const unsigned ppn);

    void remove(const unsigned vpn);

    std::pair<unsigned, bool> lookup(const unsigned vpn);

    unsigned getHit() const;

    unsigned getMiss() const;

    unsigned getSize() const;

    unsigned getEntry() const;

    InstPageTable& operator=(const InstPageTable& that);

    InstPageTable& operator=(InstPageTable&& that);

private:
    unsigned pageSize;
    unsigned pageEntry;
    PageTable* table;

private:
    unsigned hit;
    unsigned miss;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_ */
