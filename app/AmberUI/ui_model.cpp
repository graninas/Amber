#include "ui_model.h"

using namespace amber::model;

addComponent(ComponentsTVar tvar,
             QString itemName,
             int itemType,
             int itemSubtype)
{
    switch (static_cast<ComponentType>(itemType))
    {
        case ComponentType::Scalar:
            auto res = addScalar(itemName, itemSubtype);
            return;
        case ComponentType::Composite:
            auto res = addComposite(itemName);
            return;
    }
}
