#include "mocha.h"
#include "sub_ingredients.h"

Mocha::Mocha()
: EspressoBased(), side_items(std::vector<Ingredient *>(0)) {
    ingredients.push_back(new Espresso(2));
    ingredients.push_back(new Milk(2));
    ingredients.push_back(new MilkFoam(1));
    ingredients.push_back(new Chocolate(1));
    this->name = "Mocha";
}
Mocha::Mocha(const Mocha &cap)
: EspressoBased(cap) {
    for (const auto &s : cap.side_items) {
        this->side_items.push_back((Ingredient *)new SubIngredient(*s));
    }
    this->name = cap.name;
}
Mocha::~Mocha() {
    for (const auto &s : side_items) {
        delete s;
    }
    side_items.clear();
}
void Mocha::operator=(const Mocha &cap) {
    if (this == &cap) return ;

    this->ingredients.clear();
    for (const auto &i : cap.ingredients) {
        this->ingredients.push_back((Ingredient *)new SubIngredient(*i));
    }
    this->side_items.clear();
    for (const auto &s : cap.side_items) {
        this->side_items.push_back((Ingredient *)new SubIngredient(*s));
    }
    this->name = cap.name;
}

std::string Mocha::get_name() {
    return this->name;
}
double Mocha::price() {
    double res = EspressoBased::price();
    for (const auto &s : side_items) {
        res += s->price();
    }
    return res;
}

void Mocha::add_side_item(Ingredient *side) {
    side_items.push_back(side);
}
std::vector<Ingredient *> &Mocha::get_side_items() {
    return side_items;
}
