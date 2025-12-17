#include "array.hpp"
#include "figure.hpp"


const size_t six_angles = 6;


template<typename T>
class Hexagon: public Figure<T> {
  public:
    Hexagon();
    Hexagon(Array<std::pair<T, T>> lst);
    Hexagon(const Hexagon<T>& other);
    Hexagon(Hexagon<T>&& other) noexcept;

    Hexagon<T>& operator=(const Hexagon<T>& other);
    Hexagon<T>& operator=(Hexagon<T>&& other) noexcept;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& output, const Hexagon<U>& hexagon);
    
    template<typename U>
    friend std::istream& operator>>(std::istream& input, Hexagon<U>& square);

    virtual T square() const override;
    virtual std::pair<T, T> geom_center() const override;

    virtual ~Hexagon() = default;

    bool compare_hexagons(const Hexagon<T>& other) const;

  private:
    Array<std::pair<T, T>> coord_;
};

template<typename T>
bool operator==(const Hexagon<T>& left, const Hexagon<T>& right);

template<typename T>
Hexagon<T>::Hexagon() {
    for (int i = 0; i < six_angles; ++i) {
        coord_.Push(std::make_pair(T{}, T{}));
    }
}

template<typename T>
Hexagon<T>::Hexagon(Array<std::pair<T, T>> lst) {
    coord_ = std::move(lst);
}

template<typename T>
Hexagon<T>::Hexagon(const Hexagon& other) {
    coord_ = other.coord_;
}

template<typename T>
Hexagon<T>::Hexagon(Hexagon&& other) noexcept {
    std::swap(coord_, other.coord_);
}

template<typename T>
Hexagon<T>& Hexagon<T>::operator=(const Hexagon<T>& other) {
    coord_ =  other.coord_;
    return *this;
}

template<typename T>
Hexagon<T>& Hexagon<T>::operator=(Hexagon<T>&& other) noexcept {
    std::swap(coord_, other.coord_);
    return *this;
}

template<typename T>
std::istream& operator>>(std::istream& input, Hexagon<T>& hexagon) {
    for (int i = 0; i < six_angles; ++i) {
        std::cout << "Input " << i + 1 << "-th coordinate:\n";
        std::cout << "x: ";
        input >> hexagon.coord_[i].first;
        std::cout << "\ny: ";
        input >> hexagon.coord_[i].second;
    }
    return input;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, const Hexagon<T>& hexagon) {
    for (int i = 0; i < six_angles; ++i) {
        output << i + 1 << " coordinate\n";
        output << "x: " << hexagon.coord_[i].first << "; y: " << hexagon.coord_[i].second;
    }
    return output;
}

template<typename T>
T Hexagon<T>::square() const {
    T side_length = std::sqrt((coord_[0].first - coord_[1].first) * (coord_[0].first - coord_[1].first) + 
                    (coord_[0].second - coord_[1].second) * (coord_[0].second - coord_[1].second));

    return six_angles * side_length * side_length / 4 / std::tan(1.0 / six_angles);
}

template<typename T>
std::pair<T, T> Hexagon<T>::geom_center() const {
    T center_x = (coord_[0].first + coord_[1].first + coord_[2].first + coord_[3].first + coord_[4].first + coord_[5].first) / 6;
    T center_y = (coord_[0].second + coord_[1].second + coord_[2].second + coord_[3].second + coord_[4].second + coord_[5].second) / 6;
    return std::make_pair(center_x, center_y);
}

template<typename T>
bool Hexagon<T>::compare_hexagons(const Hexagon<T>& other) const {
    for (int i = 0; i < six_angles; ++i) {
        if (coord_[i] != other.coord_[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool operator==(const Hexagon<T>& left, const Hexagon<T>& right) {
  return left.compare_hexagons(right);
}
