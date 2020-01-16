#include "FileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilities.h"

Recipe* parseRecipes(const char* path) {
    if (path == NULL) return NULL;

    FILE* fp = fopen(path, "r");
    char* lineBuff = (char*)safe_malloc(sizeof(char) * LINE_BUFFER_SIZE);
    int index = 0;
    Recipe* start = NULL;

    if (fp == NULL) {
        fprintf(stderr, "Could not open file at path %s", path);
        exit(EXIT_FAILURE);
    }

    while (fgets(lineBuff, LINE_BUFFER_SIZE, fp) != NULL) {
        // skip empty lines
        if (strcmp(lineBuff, "\n") == 0 || strcmp(lineBuff, "\r\n") == 0) {
            continue;
        }

        char* name = strtok(lineBuff, FILE_DELIMITER);
        char* ingredientString = strtok(NULL, FILE_DELIMITER);
        char* instructions = strtok(NULL, FILE_DELIMITER);

        if (name == NULL || ingredientString == NULL || instructions == NULL) {
            fprintf(stderr, "Invalid file structure.\n");
            exit(EXIT_FAILURE);
        }

        if (strtok(NULL, FILE_DELIMITER) != NULL) {
            fprintf(stderr, "Only three tokens allowed.\n");
        }

        Ingredient* ingredients = parseIngredients(ingredientString);
        start = insertRecipe(start, index++, name, instructions, ingredients);
    }

    return start;
}

Ingredient* parseIngredients(char* ingredients) {
    if (ingredients == NULL) return NULL;

    char* ptr = strdup(ingredients);
    char* token = strtok_r(ingredients, INGREDIENT_DELIMITER, &ptr);

    if (token == NULL) {
        fprintf(stderr, "Invalid ingredient structure");
        exit(EXIT_FAILURE);
    }

    Ingredient* start = NULL;

    do {
        char* dup = strdup(token);
        char* amountStr = strtok_r(token, INGREDIENT_COMP_DELIMITER, &dup);
        char* unit = strtok_r(NULL, INGREDIENT_COMP_DELIMITER, &dup);
        char* name = strtok_r(NULL, INGREDIENT_COMP_DELIMITER, &dup);
        char** ptr = NULL;

        if (amountStr == NULL || unit == NULL || name == NULL) {
            fprintf(stderr, "Error while parsing ingredients.\nPlease check the file structure.\n");
            exit(EXIT_FAILURE);
        }

        int amount = strtol(amountStr, ptr, 10);

        if (amount == 0 && strcmp(amountStr, " ") != 0) {
            fprintf(stderr, "Error while parsing ingredient amount\nPlease check the file structure.\n");
            exit(EXIT_FAILURE);
        }

        start = insertIngredient(start, amount, name, unit);
    } while ((token = strtok_r(NULL, INGREDIENT_DELIMITER, &ptr)) != NULL);

    return start;
}