/*
 * InstPageTable.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_

namespace inst {

class InstPageTable {
public:
    InstPageTable();

    ~InstPageTable();

public:
    void init(const unsigned pageSize);

    unsigned size() const;

    unsigned entry() const;

private:
    unsigned pageSize;
    unsigned pageEntry;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTPAGETABLE_HPP_ */
