/// @file FileManager.c/// Parses recipe from given file at path.
/// @param path
/// @return First node of recipe list
/// @return NULL if path is null or file is empty

#include "FileManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Utilities.h"

/// Parses recipe from given file at path.
/// @param path
/// @return First node of recipe list
/// @return NULL if path is null or file is empty
Recipe* parseRecipes(const char* path) {
    if (path == NULL) return NULL;

    FILE* fp = fopen(path, "r");
    char* lineBuff = (char*)safe_malloc(sizeof(char) * LINE_BUFFER_SIZE);
    Recipe* start = NULL;

    if (fp == NULL) {
        fprintf(stderr, "Could not open file at path %s\n", path);
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
        start = insertRecipe(start, name, instructions, ingredients);
    }

    free(lineBuff);
    fclose(fp);

    return start;
}

/// Parses the ingredients from the given Ingredient string.
/// @param ingredients
/// @return First node of ingredient list
/// @return NULL if ingredient string is NULL or ingredient list is empty.
Ingredient* parseIngredients(char* ingredients) {
    if (ingredients == NULL) return NULL;

    char* ptr;
    char* token = strtok_r(ingredients, INGREDIENT_DELIMITER, &ptr);

    if (token == NULL) {
        fprintf(stderr, "Invalid ingredient structure.\n");
        exit(EXIT_FAILURE);
    }

    Ingredient* start = NULL;

    do {
        char* ingrPtr;
        char* amountStr = strtok_r(token, INGREDIENT_COMP_DELIMITER, &ingrPtr);
        char* unit = strtok_r(NULL, INGREDIENT_COMP_DELIMITER, &ingrPtr);
        char* name = strtok_r(NULL, INGREDIENT_COMP_DELIMITER, &ingrPtr);

        if (amountStr == NULL || unit == NULL || name == NULL) {
            fprintf(stderr, "Error while parsing ingredients.\nPlease check the file structure.\n");
            exit(EXIT_FAILURE);
        }

        int amount = (int)strtol(amountStr, NULL, 10);

        if (amount == 0 && strcmp(amountStr, " ") != 0) {
            fprintf(stderr, "Error while parsing ingredient amount\nPlease check the file structure.\n");
            exit(EXIT_FAILURE);
        }

        start = insertIngredient(start, amount, name, unit);
    } while ((token = strtok_r(NULL, INGREDIENT_DELIMITER, &ptr)) != NULL);

    return start;
}

/// Writes the recipes and their ingredients to the file at given path.
/// @param start
/// @param path
/// @return Number of rows written to the file
/// @return Negative integer value in case of failure
int writeToFile(Recipe* start, const char* path) {
    if (start == NULL || path == NULL) return -1;

    int rowsWritten = 0;
    Recipe* recipe = start;
    FILE* fp = fopen(path, "w");

    if (fp == NULL) return -1;

    while (recipe != NULL) {
        if (fprintf(fp, "%s;", recipe->name) <= 0) {
            return -1;
        }

        Ingredient* curr = recipe->ingredients;

        while (curr != NULL) {
            if (curr->amount == 0) {
                if (fprintf(fp, " |") <= 0) return -1;
            }
            else {
                if (fprintf(fp, "%d|", curr->amount) <= 0) return -1;
            }

            if (strcmp(curr->unit, "\0") == 0) {
                if (fprintf(fp, " |") <= 0) return -1;
            }
            else {
                if (fprintf(fp, "%s|", curr->unit) <= 0) return -1;
            }

            if (fprintf(fp, "%s#", curr->name) <= 0) {
                return -1;
            }

            curr = curr->next;
        }

        if (fprintf(fp, ";%s", recipe->instructions) <= 0) return -1;

        recipe = recipe->next;
        rowsWritten++;
    }

    fclose(fp);

    return rowsWritten;
}
