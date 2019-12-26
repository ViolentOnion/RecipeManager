#include "Ingredient.h"
#include "MeasurementUnits.h"
#include <string.h>

Ingredient* createIngredient(char* name, uint16_t amount, MeasureUnit unit) {
    if (name == NULL) return NULL;

    Ingredient* newIngredient = (Ingredient*)malloc(sizeof(Ingredient));

    // no memory
    if (newIngredient == NULL) return NULL;

    newIngredient->amount = amount;
    newIngredient->unit = unit;

    struct recipe_ingredient_name* ingredientName = createIngredientName(name);

    if (ingredientName == NULL) return NULL;

    newIngredient->name = *ingredientName;

    return newIngredient;
}

struct recipe_ingredient_name* createIngredientName(char* name) {
    size_t length = strlen(name);
    struct recipe_ingredient_name* ingredientName = (struct recipe_ingredient_name*)malloc(sizeof(struct recipe_ingredient_name));

    if (ingredientName == NULL) return NULL;

    ingredientName->nameLength = length;
    strcpy(ingredientName->name, name);

    return ingredientName;
}