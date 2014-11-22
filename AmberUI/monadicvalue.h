#ifndef MONADICVALUE_H
#define MONADICVALUE_H

namespace monad
{

template <typename M> struct MonadicValue
{
    M genericData;
};


}

#endif // MONADICVALUE_H
