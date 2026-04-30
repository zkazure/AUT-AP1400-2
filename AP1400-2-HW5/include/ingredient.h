#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

class Ingredient {
public:
    double get_price_unit() { return price_unit; }
    size_t get_units() { return units; }
    virtual std::string get_name() = 0;

    double price() { return units * price_unit; }

    virtual ~Ingredient() = default;

protected:
    Ingredient(double price_unit, size_t units)
    : price_unit(price_unit), units(units) {}
    Ingredient(const Ingredient &other)
    : price_unit(other.price_unit), units(other.units), name(other.name) {}

    double price_unit;
    size_t units;
    std::string name;
};

#endif // INGREDIENT_H
