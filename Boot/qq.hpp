namespace qq {
    template <typename TT>
TT&& move(TT& arg) noexcept {
    return static_cast<TT&&>(arg);
}

    #define nullptr_ 0
    template<typename T, int Capacity>
    class vector {
    private:
        T elements[Capacity];
        int sizee;

    public:
        vector() : sizee(0) {}

        void push_back(const T& value) {
    if (sizee < Capacity) {
        elements[sizee] = value;
        ++sizee;
    } else {
        // Handle vector full error
        // You can define custom behavior here
        // For example, return an error code or do nothing
    }
}




        void pop_back() {
            if (sizee > 0)
                --sizee;
        }

        size_t size() const {
            return sizee;
        }

        bool empty() const {
            return sizee == 0;
        }

        const T& operator[](size_t index) const {
            if (index >= sizee) {
                // Handle index out of range error
                // You can define custom behavior here
                // For example, return a default value or throw an exception
                // Avoiding std::out_of_range as requested
                return elements[0]; // Default behavior: return the first element
            }
            return elements[index];
        }

        T& operator[](size_t index) {
            if (index >= sizee) {
                // Handle index out of range error
                // You can define custom behavior here
                // For example, return a default value or throw an exception
                // Avoiding std::out_of_range as requested
                return elements[0]; // Default behavior: return the first element
            }
            return elements[index];
        }

        T& at(size_t index) {
            if (index >= sizee) {
                // Handle index out of range error
                // You can define custom behavior here
                // For example, return a default value or throw an exception
                // Avoiding std::out_of_range as requested
                return elements[0]; // Default behavior: return the first element
            }
            return elements[index];
        }

        const T& at(size_t index) const {
            if (index >= sizee) {
                // Handle index out of range error
                // You can define custom behavior here
                // For example, return a default value or throw an exception
                // Avoiding std::out_of_range as requested
                return elements[0]; // Default behavior: return the first element
            }
            return elements[index];
        }

        T* begin() {
            return elements;
        }

        T* end() {
            return elements + sizee;
        }
        T& back() {
        if (sizee > 0) {
            return elements[sizee - 1];
        }
        // Throw an exception or handle the error case when the vector is empty
        // ...
        return elements[0];
    }
    };
    template <typename KeyType, typename ValueType, int Capacity>
class map {
private:
    struct Pair {
        KeyType first;
        ValueType second;
    };

    vector<Pair, Capacity> pairs;

public:
    void insert(const KeyType& key, const ValueType& value) {
        for (const auto& pair : pairs) {
            if (pair.first == key) {
                return;
            }
        }

        Pair newPair;
        newPair.first = key;
        newPair.second = value;
        pairs.push_back(newPair);
    }
    void insert_or_assign(const KeyType& key, const ValueType& value) {
        for (auto& pair : pairs) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        Pair newPair;
        newPair.first = key;
        newPair.second = value;
        pairs.push_back(newPair);
    }

    bool contains(const KeyType& key) const {
        for (const auto& pair : pairs) {
            if (pair.first == key) {
                return true;
            }
        }
        return false;
    }

    ValueType& operator[](const KeyType& key) {
        for (auto& pair : pairs) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        Pair newPair;
        newPair.first = key;
        pairs.push_back(newPair);
        return pairs.back().second;
    }
    auto begin() {
        return pairs.begin();
    }

    auto end() {
        return pairs.end();
    }
    Pair* find(const KeyType& key) {
    for (auto& pair : pairs) {
        if (strcmp(pair.first, key) == 0) {
            return &pair;
        }
    }
    
    return nullptr_; // Return nullptr if the key is not found
}

void erase(const KeyType& key) {
    size_t eraseCount = 0;
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (strcmp(pairs[i].first, key) == 0) {
            ++eraseCount;
        } else if (eraseCount > 0) {
            pairs[i - eraseCount] = move(pairs[i]);
        }
    }

    for (size_t i = 0; i < eraseCount; ++i) {
        pairs.pop_back();
    }
}








};
}
