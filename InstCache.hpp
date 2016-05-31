/*
 * InstCache.hpp
 *
 *  Created on: 2016/05/30
 *      Author: LittleBird
 */

#ifndef COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_
#define COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_

namespace inst {

class InstCache {
public:
    InstCache();

    ~InstCache();

public:
    void init(const unsigned cacheSize, const unsigned blockSize, const unsigned setAssociativity);

private:
    unsigned cacheSize;
    unsigned blockSize;
    unsigned setAssociativity;
};

} /* namespace inst */

#endif /* COMPUTER_ARCHITECTURE_PROJECT_3_INSTCACHE_HPP_ */
