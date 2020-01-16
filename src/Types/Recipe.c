#include "Recipe.h"
#include "../Utilities.h"
#include <string.h>

Recipe* insertRecipe(Recipe* start, unsigned int index, char* name, char* instructions, Ingredient* ingredientList) {
    Recipe* new = (Recipe*)safe_malloc(sizeof(Recipe));

    new->index = index;

    new->name = (char*)safe_malloc(sizeof(char) * strlen(name));
    new->name = name;

    new->instructions = (char*)safe_malloc(sizeof(char) * strlen(instructions));
    new->instructions = instructions;

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
