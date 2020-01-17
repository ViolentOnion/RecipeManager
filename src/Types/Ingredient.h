#ifndef RECIPE_MANAGER_INGREDIENT_H
#define RECIPE_MANAGER_INGREDIENT_H

#include <stdlib.h>

typedef struct ingredient {
    unsigned int amount;
    char* name;
    char* unit;
    struct ingredient* next;
} Ingredient;

Ingredient* insertIngredient(Ingredient* start, unsigned int amount, const char* name, const char* unit);
Ingredient* readIngredients(unsigned int amount);
void prettyPrintIngredient(Ingredient* ingredient);
void prettyPrintIngredients(Ingredient* ingredients);
void freeIngredient(Ingredient* ingredient);

#endif //RECIPE_MANAGER_INGREDIENT_H
