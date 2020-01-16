cmake_minimum_required(VERSION 3.14)
project(Recipe_Manager C)

set(CMAKE_C_STANDARD 99)

add_executable(Recipe_Manager main.c Types/Ingredient.c Types/Ingredient.h Utilities.c Utilities.h Types/Recipe.c Types/Recipe.h FileManager.c FileManager.h)