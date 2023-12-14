#ifndef ITEMS_h_
#define ITEMS_h_

#include <string>

enum FoodItemType {
    butter,
    chocolate,
    eggs,
    honey,
    milk,
    straw,
    sugar,
    wheat,
};

static std::string foodItemTypeToString[] {
    "butter",
    "chocolate",
    "eggs",
    "honey",
    "milk",
    "straw",
    "sugar",
    "wheat",
};

enum RevenuesItemType {
    brigadeiro,
    cake,
    cheesebread,
    macarons,
    pudding,
};

static std::string RevenuesItemTypeToString[] {
    "brigadeiro",
    "cake",
    "cheesebread",
    "macarons",
    "pudding",
};

#endif