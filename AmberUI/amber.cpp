#include "amber.h"

namespace amber
{

void changeAmber(const AmberTask &task, Amber& amber)
{
    Amber newAmber = task(amber);
    amber = newAmber;
}

}
