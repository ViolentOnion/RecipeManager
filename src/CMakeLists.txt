cmake_minimum_required(VERSION 3.14)
project(Recipe_Manager C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -pedantic -Wno-unused-parameter")
set(CMAKE_C_CLANG_TIDY clang-tidy -check=-*, readability=-*)

add_executable(Recipe_Manager main.c Types/Ingredient.c Types/Ingredient.h Utilities.c Utilities.h Types/Recipe.c Types/Recipe.h FileManager.c FileManager.h)