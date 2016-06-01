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
    struct PageTableData {
        unsigned ppn;
        bool valid;
        PageTableData(const unsigned ppn = 0, const bool valid = false) :
                ppn(ppn), valid(valid) {}
    };

public:
    InstPageTable();

    InstPageTable(const InstPageTable& that);

    InstPageTable(InstPageTable&& that);

    ~InstPageTable();

    void push(const unsigned tag, const unsigned ppn);

    void remove(const unsigned tag);

    std::pair<unsigned, bool> lookup(const unsigned tag);

    InstPageTable& operator=(const InstPageTable& that);

    InstPageTable& operator=(InstPageTable&& that);

public:
    void init(const unsigned pageSize);

    unsigned size() const;

    unsigned entry() const;

private:
    unsigned pageSize;
    unsigned pageEntry;
    PageTableData* data;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_ */
