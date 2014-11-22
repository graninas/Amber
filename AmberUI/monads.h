#ifndef MONADS_H
#define MONADS_H

#include "monadicvalue.h"
#include "maybemonad.h"

namespace monad
{

// Maybe monad definitions

typedef MonadicValue<maybe::Maybe<bool>> MaybeBool;
typedef MonadicValue<maybe::Maybe<int>> MaybeInt;
typedef MonadicValue<maybe::Maybe<double>> MaybeDouble;

}

#endif // MONADS_H
