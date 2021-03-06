/// @file Recipe.h

#ifndef RECIPE_MANAGER_RECIPE_H
#define RECIPE_MANAGER_RECIPE_H

#include "Ingredient.h"
#include <stdio.h>

typedef struct recipe {
    unsigned int index;
    char* name;
    char* instructions;
    Ingredient* ingredients;
    struct recipe* next;
} Recipe;

Recipe* insertRecipe(Recipe* start, const char* name, const char* instructions, Ingredient* ingredientList);
void displayRecipeNames(Recipe* start);
void prettyPrintRecipe(Recipe* recipe);
void freeRecipe(Recipe* start);
Recipe* getRecipeByIndex(Recipe* start, unsigned int index);
Recipe* readRecipe();

#endif //RECIPE_MANAGER_RECIPE_H
