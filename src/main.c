#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include "FileManager.h"
#include "Types/Recipe.h"

#define BUFF_SIZE 2000
#define EDIT "e\n"
#define ADD "a\n"
#define QUIT "q\n"

int main(int argc, char* argv[]) {

    int ch;

    while ((ch = getopt(argc, argv, "f")) != -1)
    {
        if (ch != 'f') {
            fprintf(stderr, "Invalid options defined.\n");
            return EXIT_FAILURE;
        }
    }

    if (optind != argc-1) {
        printf("Invalid parameter count.\n");
        return EXIT_FAILURE;
    }

    Recipe* recipes = parseRecipes(argv[optind]);

    if (recipes == NULL) {
        fprintf(stderr, "Error while parsing file.\nPlease check if the provided path is correct.\n");
        return EXIT_FAILURE;
    }

    char buffer[BUFF_SIZE];
    int recipeIndex = 0;

    displayRecipeNames(recipes);

    while (1) {
        fprintf(stdout, "Please select the number of the recipe to display, (e) to edit, (a) to add or (q) to quit:\n");

        if (fgets(buffer, BUFF_SIZE, stdin) != NULL) {
            if (strcmp(buffer, ADD) == 0) {
                Recipe* new = readRecipe();

                if (new == NULL) return EXIT_SUCCESS;

                Recipe* temp = recipes;
                while (temp->next != NULL) temp = temp->next;

                new->index = temp->index + 1;
                temp->next = new;

                writeToFile(recipes, argv[optind]);
                displayRecipeNames(recipes);
            } else if (strcmp(buffer, EDIT) == 0) {
                int recipeIndex = 0;

                fprintf(stdout, "Please the index of the recipe to edit:\n");
                if (fgets(buffer, BUFF_SIZE, stdin) == NULL || strcmp(buffer, "\n") == 0) {
                    fprintf(stderr, "Invalid input.");
                    continue;
                }

                recipeIndex = (int)strtol(buffer, NULL, 10);

                if (recipeIndex <= 0) {
                    fprintf(stderr, "Invalid input.");
                    continue;
                }

                Recipe* previous = getRecipeByIndex(recipes, recipeIndex == 1 ? recipeIndex : recipeIndex - 1);

                if (previous == NULL) {
                    fprintf(stdout, "Recipe at given index could not be found.\n");
                    continue;
                }

                Recipe* new = readRecipe();

                if (new == NULL) return EXIT_SUCCESS;

                if (previous->next == NULL) {
                    previous->next = new;
                    new->index = previous->index + 1;
                }
                else {
                    Recipe* old = previous->next;
                    previous->next = new;
                    new->next = old->next == NULL ? NULL : old->next;
                    new->index = old->index;
                    free(old);
                }

                writeToFile(recipes, argv[optind]);
                displayRecipeNames(recipes);
            } else if (strcmp(buffer, QUIT) == 0) {
                break;
            } else if ((recipeIndex = (int)strtol(buffer, NULL, 10)) > 0) {
                Recipe* recipe = getRecipeByIndex(recipes, recipeIndex);

                if (recipe == NULL) {
                    fprintf(stdout, "Recipe with index %d not found.\n", recipeIndex);
                    continue;
                }

                prettyPrintRecipe(recipe);
                displayRecipeNames(recipes);
            } else {
                fprintf(stderr, "Unknown command.\n");
            }
        }
    }

    freeRecipe(recipes);

    return EXIT_SUCCESS;
}
