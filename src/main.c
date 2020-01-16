#include <stdio.h>
#include "FileManager.h"

int main(int argc, char* argv[]) {

    Recipe* recipes = parseRecipes("/Users/srole/Git/Recipe-Manager/src/database.txt");

    if (recipes == NULL) {
        fprintf(stderr, "Error while parsing file.\nPlease check if the provided path is correct.");
    }

    displayRecipeNames(recipes);

    prettyPrintRecipe(recipes);

    return 0;
}