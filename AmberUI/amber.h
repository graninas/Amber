#ifndef AMBER_H
#define AMBER_H

#include "common.h"
#include "amberstructure.h"

namespace amber
{

typedef std::function<Amber (const Amber&)> AmberTask;

Amber defaultAmber();

} // namespace amber

#endif // AMBER_H
