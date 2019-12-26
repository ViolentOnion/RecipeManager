#ifndef RECIPE_MANAGER_INGREDIENT_H
#define RECIPE_MANAGER_INGREDIENT_H

#include <stdlib.h>
#include "MeasurementUnits.h"

struct recipe_ingredient_name {
    size_t nameLength;
    char* name;
} IngredientName;

typedef struct ingredient {
    uint16_t amount;
    struct recipe_ingredient_name name;
    MeasureUnit unit;
} Ingredient;

Ingredient* createIngredient(char* name, uint16_t amount, MeasureUnit unit);
struct recipe_ingredient_name* createIngredientName(char* name);

#endif //RECIPE_MANAGER_INGREDIENT_H
