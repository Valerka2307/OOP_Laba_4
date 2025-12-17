#include "array.hpp"
#include "figure.hpp"


const size_t four_angles = 4;


template<typename T>
class Rhombus: public Figure<T> {
  public:
    Rhombus();
    Rhombus(Array<std::pair<T, T>> lst);
    Rhombus(const Rhombus<T>& other);
    Rhombus(Rhombus<T>&& other) noexcept;

    Rhombus<T>& operator=(const Rhombus<T>& other);
    Rhombus<T>& operator=(Rhombus<T>&& other) noexcept;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& output, const Rhombus<U>& rhombus);
    
    template<typename U>
    friend std::istream& operator>>(std::istream& input, Rhombus<U>& rhombus);

    virtual T square() const override;
    virtual std::pair<T, T> geom_center() const override;

    virtual ~Rhombus() = default;

    bool compare_rhombuses(const Rhombus<T>& other) const;

  private:
    Array<std::pair<T, T>> coord_;
};

template<typename T>
bool operator==(const Rhombus<T>& left, const Rhombus<T>& right);

template<typename T>
Rhombus<T>::Rhombus() {
    for (int i = 0; i < four_angles; ++i) {
        coord_.Push(std::make_pair(T{}, T{}));
    }
}

template<typename T>
Rhombus<T>::Rhombus(Array<std::pair<T, T>> lst) {
    coord_ = std::move(lst);
}

template<typename T>
Rhombus<T>::Rhombus(const Rhombus<T>& other) {
    coord_ = other.coord_;
}

template<typename T>
Rhombus<T>::Rhombus(Rhombus<T>&& other) noexcept {
    std::swap(coord_, other.coord_);
}

template<typename T>
Rhombus<T>& Rhombus<T>::operator=(const Rhombus<T>& other) {
    coord_ =  other.coord_;
    return *this;
}

template<typename T>
Rhombus<T>& Rhombus<T>::operator=(Rhombus<T>&& other) noexcept {
    std::swap(coord_, other.coord_);
    return *this;
}

template<typename T>
std::istream& operator>>(std::istream& input, Rhombus<T>& rhombus) {
    for (int i = 0; i < four_angles; ++i) {
        std::cout << "Input " << i + 1 << "-th coordinate:\n";
        std::cout << "x: ";
        input >> rhombus.coord_[i].first;
        std::cout << "\ny: ";
        input >> rhombus.coord_[i].second;
    }
    return input;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, const Rhombus<T>& rhombus) {
    for (int i = 0; i < four_angles; ++i) {
        output << i + 1 << " coordinate\n";
        output << "x: " << rhombus.coord_[i].first << "; y: " << rhombus.coord_[i].second;
    }
    return output;
}

template<typename T>
T Rhombus<T>::square() const {
    T diag_1 = std::sqrt((coord_[0].first - coord_[2].first) * (coord_[0].first - coord_[2].first) + 
                    (coord_[0].second - coord_[2].second) * (coord_[0].second - coord_[2].second));
    T diag_2 = std::sqrt((coord_[1].first - coord_[3].first) * (coord_[1].first - coord_[3].first) + 
                    (coord_[1].second - coord_[3].second) * (coord_[1].second - coord_[3].second));
    return diag_1 * diag_2 / 2;
}

template<typename T>
std::pair<T, T> Rhombus<T>::geom_center() const {
    T center_x = (coord_[0].first + coord_[2].first) / 2;
    T center_y = (coord_[0].second + coord_[2].second) / 2;
    return std::make_pair(center_x, center_y);
}

template<typename T>
bool Rhombus<T>::compare_rhombuses(const Rhombus<T>& other) const {
    for (int i = 0; i < four_angles; ++i) {
        if (coord_[i] != other.coord_[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool operator==(const Rhombus<T>& left, const Rhombus<T>& right) {
  return left.compare_rhombuses(right);
}