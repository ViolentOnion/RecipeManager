#ifndef RECIPE_MANAGER_FILEMANAGER_H
#define RECIPE_MANAGER_FILEMANAGER_H

#include "Types/Recipe.h"

#define LINE_BUFFER_SIZE 4000
#define FILE_DELIMITER ";"
#define INGREDIENT_DELIMITER "#"
#define INGREDIENT_COMP_DELIMITER "|"

Recipe* parseRecipes(const char* path);
Ingredient* parseIngredients(char* ingredients);

#endif //RECIPE_MANAGER_FILEMANAGER_H
