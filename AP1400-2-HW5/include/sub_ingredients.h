#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H

#include "ingredient.h"

class SubIngredient : public Ingredient {
public:
    SubIngredient(double price_unit, size_t units, std::string name)
    : Ingredient(price_unit, units) {
        this->name = name;
    }

    virtual std::string get_name() { return name; }
};

class Cinnamon : public SubIngredient {
public:
    Cinnamon(size_t units) : SubIngredient(5, units, "Cinnamon") {}
};

class Chocolate : public SubIngredient {
public:
    Chocolate(size_t units) : SubIngredient(5, units, "Chocolate") {}
};

class Sugar : public SubIngredient {
public:
    Sugar(size_t units) : SubIngredient(1, units, "Sugar") {}
};

class Cookie : public SubIngredient {
public:
    Cookie(size_t units) : SubIngredient(10, units, "Cookie") {}
};

class Espresso : public SubIngredient {
public:
    Espresso(size_t units) : SubIngredient(15, units, "Espresso") {}
};

class Milk : public SubIngredient {
public:
    Milk(size_t units) : SubIngredient(10, units, "Milk") {}
};

class MilkFoam : public SubIngredient {
public:
    MilkFoam(size_t units) : SubIngredient(5, units, "MilkFoam") {}
};

class Water : public SubIngredient {
public:
    Water(size_t units) : SubIngredient(1, units, "Water") {}
};

#endif // SUB_SUBINGREDIENTS_H
