#include "Recipe.h"
#include "../Utilities.h"
#include <string.h>

Recipe* insertRecipe(Recipe* start, const char* name, const char* instructions, Ingredient* ingredientList) {
    Recipe* new = (Recipe*)safe_malloc(sizeof(Recipe));

    new->index = 1;

    new->name = (char*)safe_malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new->name, name);

    new->instructions = (char*)safe_malloc(sizeof(char) * (strlen(instructions) + 1));
    strcpy(new->instructions, instructions);

    new->ingredients = ingredientList;
    new->next = NULL;

    if (start == NULL) return new;

    Recipe* temp = start;

    while (temp->next != NULL) temp = temp->next;

    new->index = temp->index + 1;
    temp->next = new;

    return start;
}

void displayRecipeNames(Recipe* start) {
    if (start == NULL) return;

    Recipe* temp = start;

    while (temp != NULL) {
        fprintf(stdout, "[%d] %s\n", temp->index, temp->name);
        temp = temp->next;
    }
}

void prettyPrintRecipe(Recipe* recipe) {
    if (recipe == NULL) {
        printf("Could not find recipe with given index.");
        return;
    }

    printf("==========================\n");
    printf("%s\n", recipe->name);
    printf("==========================\n");
    prettyPrintIngredients(recipe->ingredients);
    printf("Instructions:\n");
    printf("%s", recipe->instructions);
    printf("==========================\n");
}

void freeRecipe(Recipe* start) {
    if (start->next == NULL) return;

    freeRecipe(start->next);
    freeIngredient(start->ingredients);
    free(start->name);
    free(start->instructions);
    free(start);
}

Recipe* getRecipeByIndex(Recipe* start, unsigned int index) {
    Recipe* temp = start;

    while (temp != NULL) {
        if (temp->index == index) return temp;
        temp = temp->next;
    }

    return temp;
}

Recipe* readRecipe() {
    char buffer[2000];
    Ingredient* ingredients = NULL;
    Recipe* new = NULL;

    while (1) {
        fprintf(stdout, "Please enter the name of the recipe or (q) to quit:\n");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL || strcmp(buffer, "\n") == 0) {
            fprintf(stdout, "Please enter a valid and non-empty name.\n");
            continue;
        }

        if (strcmp(buffer, "q\n") == 0) break;

        int nameLength = (int)strlen(buffer);
        char name[nameLength];
        strncpy(name, buffer, nameLength - 1);
        name[nameLength - 1] = '\0';

        fprintf(stdout, "Enter the amount of ingredients:\n");

        int ingredientAmount = 0;

        if (fgets(buffer, sizeof(buffer), stdin) == NULL || strcmp(buffer, "\n") == 0 || strcmp(buffer, "0\n") == 0) {
            fprintf(stdout, "Must specify at least 1 ingredient.\n");
            continue;
        }

        ingredientAmount = (int)strtoul(buffer, NULL, 10);

        if (ingredientAmount <= 0) {
            fprintf(stdout, "Must specify an amount >= 0.\n");
            continue;
        }

        ingredients = readIngredients(ingredientAmount);

        if (ingredients == NULL) return NULL;

        fprintf(stdout, "Please enter the cooking instructions:\n");

        if (fgets(buffer, sizeof(buffer), stdin) == NULL || strcmp(buffer, "\n") == 0) {
            fprintf(stdout, "Please enter non-empty instructions.\n");
            freeIngredient(ingredients);
            continue;
        }

        int instructionSize = (int)strlen(buffer);
        char instructions[instructionSize + 1];
        strcpy(instructions, buffer);

        new = (Recipe*)safe_malloc(sizeof(Recipe));

        new->instructions = (char*)safe_malloc(sizeof(char) * instructionSize);
        strcpy(new->instructions, instructions);

        new->name = (char*)safe_malloc(sizeof(char) * nameLength);
        strcpy(new ->name, name);

        new->ingredients = ingredients;
        break;
    }

    return new;
}
