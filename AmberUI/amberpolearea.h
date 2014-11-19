#ifndef AMBERSHADOW_H
#define AMBERSHADOW_H

#include "shadowstructure.h"

namespace amber
{

ShadowStructure amberShadowStructure();
ShadowStructure trueAmberStructure();
ShadowStructure bergmaShadowStructure();
ShadowStructure trueBergmaStructure();

ShadowVariator amberVariator();
ShadowVariator bergmaVariator();

Shadows amberPoleShadows();
Area amberPoleArea();

} // namespace amber

#endif // AMBERSHADOW_H
