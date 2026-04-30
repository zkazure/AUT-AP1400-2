#include "espresso_based.h"
#include "sub_ingredients.h"

EspressoBased::EspressoBased() {
    ingredients = std::vector<Ingredient *>(0);
}
EspressoBased::EspressoBased(const EspressoBased &esp) {
    this->name = esp.name;
    this->ingredients.clear();
    for (const auto &i : esp.ingredients) {
        this->ingredients.push_back((Ingredient *)new SubIngredient(*i));
    }
}
void EspressoBased::operator=(const EspressoBased &esp) {
    if (this == &esp) return ;

    this->name = esp.name;
    this->ingredients.clear();
    for (const auto &i : esp.ingredients) {
        this->ingredients.push_back(i);
    }
}

std::string EspressoBased::get_name() { return name; }
double EspressoBased::price() {
    double res = 0;
    for (const auto &i : ingredients) {
        res += i->price();
    }
    return res;
}

void EspressoBased::brew() {return;}
std::vector<Ingredient*> &EspressoBased::get_ingredients() {
    return ingredients;
}

EspressoBased::~EspressoBased() {
    for (const auto &i : ingredients) {
        delete i;
    }
    ingredients.clear();
}
