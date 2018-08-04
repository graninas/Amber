#ifndef UI_MODEL_H
#define UI_MODEL_H

#include <QTreeWidgetItem>

#include <amber.h>
#include <stm/stm.h>


addComponent(amber::model::ComponentsTVar tvar,
             QString itemName,
             int itemType,
             int itemSubtype);

#endif // UI_MODEL_H
