#include "Recipe.h"
#include "../Utilities.h"
#include <string.h>

Recipe* insertRecipe(Recipe* start, unsigned int index, const char* name, const char* instructions, Ingredient* ingredientList) {
    Recipe* new = (Recipe*)safe_malloc(sizeof(Recipe));

    new->index = index;

    new->name = (char*)safe_malloc(sizeof(char) * strlen(name));
    strcpy(new->name, name);

    new->instructions = (char*)safe_malloc(sizeof(char) * strlen(instructions));
    strcpy(new->instructions, instructions);

    new->ingredients = ingredientList;
    new->next = NULL;

    if (start == NULL) return new;

    Recipe* temp = start;

    while (temp->next != NULL) temp = temp->next;

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
    printf("%s\n", recipe->instructions);
}

void freeRecipe(Recipe* start) {
    if (start->next == NULL) return;

    freeRecipe(start->next);
    freeIngredient(start->ingredients);
    free(start->name);
    free(start->instructions);
    free(start);
}
