#ifndef AMBERSHADOW_H
#define AMBERSHADOW_H

#include "amberstructure.h"

namespace amber
{

ShadowStructure amberShadowStructure();
ShadowStructure bergmaShadowStructure();
ShadowStructure kashfaShadowStructure();
ShadowStructure avalonShadowStructure();

ShadowVariator amberPoleVariator(int multiplier);
ShadowVariator bergmaShadowVariator();
ShadowVariator kashfaShadowVariator();
ShadowVariator avalonShadowVariator();

Shadows amberPoleShadows();
Area amberPoleArea();

} // namespace amber

#endif // AMBERSHADOW_H

