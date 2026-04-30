#include "espresso_based.h"
#include "sub_ingredients.h"
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <chrono>
#include <random>
#include <queue>
#include <mutex>
#include <atomic>
#include <stack>

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

void EspressoBased::brew() {
    using namespace ftxui;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> cd(0, 255);
    std::mutex mtx;

    std::atomic<int> progress{0};

    auto make_layer = [&cd, &gen](std::string name, int height) {
        return text(name)
               | center                 // 文字在区块内居中
               | bgcolor(Color::RGB(cd(gen), cd(gen), cd(gen)))
               | color(Color::RGB(cd(gen), cd(gen), cd(gen)))
               | size(HEIGHT, EQUAL, height); // 强制设定区块高度
    };
    std::vector<Element> elements;
    float scalar = 100;
    size_t tmp = 0;
    std::queue<std::pair<Ingredient *, int>> que;
    for (const auto &i : ingredients) {
        tmp += i->get_units();
    }
    scalar /= tmp;
    float accumulated = 0;
    for (const auto &i : ingredients) {
        que.push({i, accumulated});
        accumulated += i->get_units() * scalar;
    }

    auto renderer = Renderer([&] {
        std::lock_guard<std::mutex> lock(mtx);
        return vbox({
            hbox({text("brewing:"), gauge((float)progress/100),
                  text(std::to_string(progress)+ "/100")}) | border,
            vbox(elements) | size(WIDTH, EQUAL, 30) | center
        });
    });

    auto screen = ScreenInteractive::TerminalOutput();

    std::thread update_thread([&]() {
        for (int i = 0; i <= 100; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            progress = i;
            if (!que.empty() && i > que.front().second) {
                auto [ing, _] = que.front(); que.pop();
                std::lock_guard<std::mutex> lock(mtx);
                elements.push_back(make_layer(ing->get_name(),
                                              ing->get_units()));
            }
            screen.PostEvent(Event::Custom);
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        screen.Exit();
    });

    screen.Loop(renderer);
    update_thread.join();
}


std::vector<Ingredient*> &EspressoBased::get_ingredients() {
    return ingredients;
}

EspressoBased::~EspressoBased() {
    for (const auto &i : ingredients) {
        delete i;
    }
    ingredients.clear();
}
