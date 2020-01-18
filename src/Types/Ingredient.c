#include "Ingredient.h"
#include "../Utilities.h"
#include <stdio.h>
#include <string.h>

Ingredient* insertIngredient(Ingredient* start, unsigned int amount, const char* name, const char* unit) {
    Ingredient* new = (Ingredient*)safe_malloc(sizeof(Ingredient));

    new->name = (char*)safe_malloc(sizeof(char) * (strlen(name) + 1));
    strcpy(new->name, name);

    new->unit = (char*)safe_malloc(sizeof(char) * (strlen(unit) + 1));
    strcpy(new->unit, unit);

    new->amount = amount;
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

    printf("\n");
}

void prettyPrintIngredient(Ingredient* ingredient) {
    if (ingredient == NULL) return;

    if (ingredient->amount == 0) {
        printf("%s\n", ingredient->name);
        return;
    }

    printf("%-4d  %-10s  %s\n", ingredient->amount, ingredient->unit, ingredient->name);
}

void freeIngredient(Ingredient* ingredient) {
    if (ingredient == NULL || ingredient->next == NULL) return;

    freeIngredient(ingredient->next);
    free(ingredient->name);
    free(ingredient->unit);
    free(ingredient);
}

Ingredient* readIngredients(unsigned int amount) {
    char buff[20];
    char name[20];
    char unit[20];
    unsigned int ingrCount = 0;
    Ingredient* new = NULL;

    while (ingrCount < amount) {
        fprintf(stdout, "Please enter the name of the ingredient or type (q) to quit:\n");

        if (fgets(buff, sizeof(buff), stdin) == NULL || strcmp(buff, "\n") == 0) {
            fprintf(stdout, "Please enter a non-empty name.\n");
            continue;
        }

        if (strcmp(buff, "q\n") == 0) return NULL;

        buff[strcspn(buff, "\n")] = '\0';
        strcpy(name, buff);

        fprintf(stdout, "Please enter an amount (leave blank for nothing): \n");
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            fprintf(stderr, "Error while reading input.\n");
            continue;
        }

        int ingrAmount = (int)strtoul(buff, NULL , 10);

        fprintf(stdout, "Please enter a unit (leave blank for nothing): \n");
        if (fgets(buff, sizeof(buff), stdin) == NULL) {
            fprintf(stderr, "Error while reading input.\n");
            continue;
        }

        buff[strcspn(buff, "\n")] = '\0';
        strcpy(unit, buff);

        new = insertIngredient(new, ingrAmount, name, unit);
        ingrCount++;
    }

    return new;
}
