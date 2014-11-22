#ifndef MONADS_H
#define MONADS_H

#include "monadicvalue.h"
#include "maybemonad.h"
#include "common.h"

namespace monad
{

// Maybe monad definitions

typedef MonadicValue<Maybe<bool>> MaybeBool;


// Lookup of maps
template <typename KeyType, typename MappedType>
    monad::MonadicValue<monad::Maybe<MappedType>>
    lookupMap(const KeyType& key, const std::map<KeyType, MappedType>& dataMap)
{
    if (dataMap.find(key) != dataMap.end())
        return monad::just(dataMap.at(key));

    // Presentation tip: poor template types deducing for function nothing(). It is requres an explicit type.
    return monad::nothing<MappedType>();
}

}

#endif // MONADS_H
