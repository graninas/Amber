#ifndef AMBER_H
#define AMBER_H

#include "amberstructure.h"

#include <functional>

namespace amber
{

typedef std::function<Amber (const Amber&)> AmberTask;

Amber defaultAmber();

} // namespace amber

#endif // AMBER_H
