#include "Ingredient.h"
#include <stdio.h>
#include <string.h>

Ingredient* insertIngredient(Ingredient* start, unsigned int amount, char* name, char* unit) {
    Ingredient* new = (Ingredient*)malloc(sizeof(Ingredient));

    if (new == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(EXIT_SUCCESS);
    }

    new->amount = amount;
    new->name = name;
    new->unit = unit;
    new->next = NULL;

    if (start == NULL) return new;

    Ingredient* temp = start;

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = new;

    return start;
}


void prettyPrintIngredients(Ingredient* ingredients) {
    if (ingredients == NULL) return;

    printf("Ingredients:\n");

    Ingredient* current = ingredients;

    while(current != NULL) {
        prettyPrintIngredient(current);
        current = current->next;
    }

    printf("\n\n");
}

void prettyPrintIngredient(Ingredient* ingredient) {
    if (ingredient == NULL) return;

    if (ingredient->amount == 0 && strcmp(ingredient->unit, " ") == 0) {
        printf("%s", ingredient->name);
        return;
    }

    printf("%-4d  %-10s  %s\n", ingredient->amount, ingredient->unit, ingredient->name);
}