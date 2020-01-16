#ifndef RECIPE_MANAGER_INGREDIENT_H
#define RECIPE_MANAGER_INGREDIENT_H

#include <stdlib.h>

typedef struct ingredient {
    unsigned int amount;
    char* name;
    char* unit;
    struct ingredient* next;
} Ingredient;

Ingredient* insertIngredient(Ingredient* start, unsigned int amount, char* name, char* unit);
void prettyPrintIngredient(Ingredient* ingredient);
void prettyPrintIngredients(Ingredient* ingredients);

#endif //RECIPE_MANAGER_INGREDIENT_H
