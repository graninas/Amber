#ifndef MONADS_H
#define MONADS_H

#include "maybemonad.h"

namespace monad
{

// Maybe monad definitions

typedef maybe::Maybe<bool>   MaybeBool;
typedef maybe::Maybe<int>    MaybeInt;
typedef maybe::Maybe<double> MaybeDouble;

}

#endif // MONADS_H
