#include <iostream>
#include <print>

inline static size_t max(size_t a, size_t b) {
    return a > b ? a : b;
}

class string {
    constexpr static const int MIN_CAPACITY = int(1e2 + 5);
    char *container;
    size_t _capacity, _size;

    void _allocate_memory(size_t _capacity) {
        this->container = (char *) malloc(_capacity * sizeof(char));
        this->_capacity = _capacity;
        memset(this->container, 0, this->_capacity);
    }

    void _increase_capacity() {
        this->container = (char *) realloc(this->container, 2 * _capacity * sizeof(char));
        memset(this->container + this->_capacity, 0, this->_capacity);
        this->_capacity = 2 * this->_capacity;
    }

public:

    string(const string &other) {
        _allocate_memory(other.capacity());
        this->_size = other.size();
        memcpy(this->container, other.container, other.size());
    }

    string(size_t capacity = string::MIN_CAPACITY) {
        _allocate_memory(max(capacity, string::MIN_CAPACITY));
    }

    string(const char *other) {
        const int N = strlen(other);
        _allocate_memory(max(string::MIN_CAPACITY, N));
        memcpy(this->container, other, N);
        this->_size = N;
    }

    [[nodiscard]]
    size_t capacity() const {
        return this->_capacity;
    }

    [[nodiscard]]
    size_t size() const {
        return this->_size;
    }
    
    [[nodiscard]]
    int length() const {
        return int(this->_size);
    }

    [[nodiscard]]
    string operator+(const string &other) const {
        string new_string(*this);

        for (int i = 0; i < other.size(); i++)
            new_string.append(other);

        return new_string;
    }

    void append(const string &other) {
        while (this->capacity() + other.size() <= this->_capacity)
            this->_increase_capacity();

        for (int i = 0; i < other.size(); i++)
            this->container[this->_size++] = other[i];
    }

    void append(const char *other) noexcept {
        const int N = strlen(other);

        while (this->capacity() - this->size() <= N)
            this->_increase_capacity();

        for (int i = 0; i < N; i++)
            this->container[this->_size++] = other[i];
    }

    void push_back(const char character) {
        if (this->_size + 1 == this->_capacity)
            this->_increase_capacity();

        this->container[this->_size++] = character;
    }

    bool operator<(const string &other) const {
        return strcmp(this->container, other.container) < 0;
    }

    bool operator>(const string &other) const {
        return strcmp(this->container, other.container) > 0;
    }

    char& operator[](size_t index) {
        return this->container[index];
    }

    const char& operator[](const size_t index) const {
        return this->container[index];
    }

    [[nodiscard]]
    const char * c_str() const {
        return this->container;
    }

    [[nodiscard]]
    bool operator==(const string &other) const {
        if (this->size() != other.size())
            return false;

        return strcmp(this->container, other.container) == 0;
    }

    ~string() {
        free(container);
    }

    friend std::ostream& operator<<(std::ostream &os, const string &other) {
        return os << other.container;
    }
};

int main() {
    string line = "sourav auddy";

    for (int i = 0; i < line.size(); i++)
        std::cout << line[i];
    std::cout << '\n';
}
