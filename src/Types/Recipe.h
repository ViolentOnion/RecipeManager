#ifndef RECIPE_MANAGER_RECIPE_H
#define RECIPE_MANAGER_RECIPE_H

#include "Ingredient.h"

struct recipe_name {
    size_t length;
    char* name;
};

struct recipe_ingredient_list {
    size_t count;
    Ingredient* ingredients;
};

struct recipe_instructions {
    size_t length;
    char* instructions;
};

typedef struct recipe_struct {
    struct recipe_name name;
    struct recipe_ingredient_list ingredients;
    struct recipe_instructions instructions;
} Recipe;

int addRecipe(char* name, Ingredient* ingredient, char* instructions);

#endif //RECIPE_MANAGER_RECIPE_H
