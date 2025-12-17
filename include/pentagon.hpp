#include "array.hpp"
#include "figure.hpp"


const size_t five_angles = 5;


template<typename T>
class Pentagon: public Figure<T> {
  public:
    Pentagon();
    Pentagon(Array<std::pair<T, T>> lst);
    Pentagon(const Pentagon<T>& other);
    Pentagon(Pentagon<T>&& other) noexcept;

    Pentagon<T>& operator=(const Pentagon<T>& other);
    Pentagon<T>& operator=(Pentagon<T>&& other) noexcept;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& output, const Pentagon<U>& square);
    
    template<typename U>
    friend std::istream& operator>>(std::istream& input, Pentagon<U>& square);

    virtual T square() const override;
    virtual std::pair<T, T> geom_center() const override;

    virtual ~Pentagon() = default;

    bool compare_pentagons(const Pentagon<T>& other) const;

  private:
    Array<std::pair<T, T>> coord_;
    
};

template<typename T>
bool operator==(const Pentagon<T>& left, const Pentagon<T>& right);

template<typename T>
Pentagon<T>::Pentagon() {
    for (int i = 0; i < five_angles; ++i) {
        coord_.Push(std::make_pair(T{}, T{}));
    }
}

template<typename T>
Pentagon<T>::Pentagon(Array<std::pair<T, T>> lst) {
    coord_ = std::move(lst);
}

template<typename T>
Pentagon<T>::Pentagon(const Pentagon<T>& other) {
    coord_ = other.coord_;
}

template<typename T>
Pentagon<T>::Pentagon(Pentagon<T>&& other) noexcept {
    std::swap(coord_, other.coord_);
}

template<typename T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T>& other) {
    coord_ =  other.coord_;
    return *this;
}

template<typename T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon<T>&& other) noexcept {
    std::swap(coord_, other.coord_);
    return *this;
}

template<typename T>
std::istream& operator>>(std::istream& input, Pentagon<T>& pentagon) {
    for (int i = 0; i < five_angles; ++i) {
        std::cout << "Input " << i + 1 << "-th coordinate:\n";
        std::cout << "x: ";
        input >> pentagon.coord_[i].first;
        std::cout << "\ny: ";
        input >> pentagon.coord_[i].second;
    }
    return input;
}

template<typename T>
std::ostream& operator<<(std::ostream& output, const Pentagon<T>& square) {
    for (int i = 0; i < five_angles; ++i) {
        output << i + 1 << " coordinate\n";
        output << "x: " << square.coord_[i].first << "; y: " << square.coord_[i].second;
    }
    return output;
}

template<typename T>
T Pentagon<T>::square() const {
    T side_length = std::sqrt((coord_[0].first - coord_[1].first) * (coord_[0].first - coord_[1].first) + 
                    (coord_[0].second - coord_[1].second) * (coord_[0].second - coord_[1].second));

    return five_angles * side_length * side_length / 4 / std::tan(1.0 / five_angles);
}

template<typename T>
std::pair<T, T> Pentagon<T>::geom_center() const {
    T center_x = (coord_[0].first + coord_[1].first + coord_[2].first + coord_[3].first + coord_[4].first) / 5;
    T center_y = (coord_[0].second + coord_[1].second + coord_[2].second + coord_[3].second + coord_[4].second) / 5;
    return std::make_pair(center_x, center_y);
}

template<typename T>
bool Pentagon<T>::compare_pentagons(const Pentagon<T>& other) const {
    for (int i = 0; i < five_angles; ++i) {
        if (coord_[i] != other.coord_[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool operator==(const Pentagon<T>& left, const Pentagon<T>& right) {
  return left.compare_pentagons(right);
}