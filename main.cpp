#include "hexagon.hpp"
#include "pentagon.hpp"
#include "rhombus.hpp"
#include "array.hpp"
#include "figure.hpp"

#include <iostream>
#include <memory>
#include <cmath>

int main() {
    std::cout << "=== Demonstration with Array<std::shared_ptr<Figure<double>>> ===\n\n";

    Array<std::shared_ptr<Figure<double>>> figures;

    // ===== Создаем фигуры через Push =====

    Array<std::pair<double,double>> rdata;
    rdata.Push({0,0});
    rdata.Push({1,1});
    rdata.Push({2,0});
    rdata.Push({1,-1});

    Array<std::pair<double,double>> pdata;
    pdata.Push({0,0});
    pdata.Push({1,0});
    pdata.Push({2,1});
    pdata.Push({1,2});
    pdata.Push({0,1});

    Array<std::pair<double,double>> hdata;
    hdata.Push({0,0});
    hdata.Push({1,0});
    hdata.Push({1.5, std::sqrt(3)/2});
    hdata.Push({1, std::sqrt(3)});
    hdata.Push({0, std::sqrt(3)});
    hdata.Push({-0.5, std::sqrt(3)/2});

    // Добавляем shared_ptr фигур
    figures.Push(std::make_shared<Rhombus<double>>(rdata));
    figures.Push(std::make_shared<Pentagon<double>>(pdata));
    figures.Push(std::make_shared<Hexagon<double>>(hdata));

    // ===== Вывод =====
    for (size_t i = 0; i < figures.Size(); i++) {
        auto fig = figures[i];

        std::cout << "Figure #" << i + 1 << ":\n";
        std::cout << "  Square = " << fig->square() << "\n";

        auto c = fig->geom_center();
        std::cout << "  Center = (" << c.first << ", " << c.second << ")\n";
        std::cout << "  use_count = " << fig.use_count() << "\n\n";
    }

    // ===== Пример: копирование shared_ptr =====
    std::cout << "=== shared_ptr copy demo ===\n";
    std::shared_ptr<Figure<double>> cp = figures[0];
    std::cout << "use_count original: " << figures[0].use_count() << "\n";
    std::cout << "use_count copy:     " << cp.use_count() << "\n\n";

    // ===== Array конкретных фигур =====
    std::cout << "=== Array<std::shared_ptr<Rhombus<double>>> Example ===\n";

    Array<std::shared_ptr<Rhombus<double>>> rhombs;
    auto r1 = std::make_shared<Rhombus<double>>(rdata);
    auto r2 = r1;

    rhombs.Push(r1);
    rhombs.Push(r2);

    for (size_t i = 0; i < rhombs.Size(); i++) {
        std::cout << "Rhombus #" << i + 1
                  << " square = " << rhombs[i]->square()
                  << ", use_count = " << rhombs[i].use_count() << "\n";
    }

    std::cout << "\nAll shared_ptr objects will be deleted automatically.\n";

    // ===== Пример с unique_ptr =====
    std::cout << "\n=== Array<std::unique_ptr<Figure<double>>> Example ===\n";

    Array<std::unique_ptr<Figure<double>>> unique_figures;
    
    unique_figures.Push(std::make_unique<Rhombus<double>>(rdata));
    unique_figures.Push(std::make_unique<Pentagon<double>>(pdata));
    unique_figures.Push(std::make_unique<Hexagon<double>>(hdata));

    for (size_t i = 0; i < unique_figures.Size(); i++) {
        auto& fig = unique_figures[i];

        std::cout << "Figure #" << i + 1 << ":\n";
        std::cout << "  Square = " << fig->square() << "\n";

        auto c = fig->geom_center();
        std::cout << "  Center = (" << c.first << ", " << c.second << ")\n\n";
    }

    std::cout << "All unique_ptr objects will be deleted automatically.\n";
    return 0;
}
