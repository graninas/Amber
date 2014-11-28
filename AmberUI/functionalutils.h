#ifndef FUNCTIONALUTILS_H
#define FUNCTIONALUTILS_H

#include "maybemonad.h"
#include "common.h"

namespace utils
{

// Lookup of maps
template <typename KeyType, typename MappedType>
    monad::maybe::Maybe<MappedType>
    lookupMap(const KeyType& key, const std::map<KeyType, MappedType>& dataMap)
{
    if (dataMap.find(key) != dataMap.end())
        return monad::maybe::just(dataMap.at(key));

    // Presentation tip: poor template types deducing for function nothing(). It is requres an explicit type.
    return monad::maybe::nothing<MappedType>();
}

} // namespace utils

#endif // FUNCTIONALUTILS_H
