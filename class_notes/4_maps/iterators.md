# Iterators in C++ (with Vectors and Maps)

## What Is an Iterator?

An iterator is an object that behaves like a pointer and allows traversal of elements in a container (like `vector`, `map`, `set`, etc.).

- `*it` — dereferences to the value
- `++it` — moves to the next element
- `it != container.end()` — checks if the end has been reached

---

## Iterators with `std::vector`

A vector stores elements contiguously, so its iterator behaves like a raw pointer.

### Example:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> nums = {10, 20, 30, 40};

    std::vector<int>::iterator it;
    for (it = nums.begin(); it != nums.end(); ++it) {
        std::cout << *it << " ";
    }
}
```

**Output:**
```
10 20 30 40
```

### Modern Range-Based Version:

```cpp
for (int value : nums) {
    std::cout << value << " ";
}
```

---

## Iterators with `std::map`

A `std::map<Key, Value>` stores sorted key-value pairs using a binary search tree.

### Example:

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> ages = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 28}
    };

    std::map<std::string, int>::iterator it;
    for (it = ages.begin(); it != ages.end(); ++it) {
        std::cout << it->first << " is " << it->second << " years old.\n";
    }
}
```

**Output:**
```
Alice is 30 years old.
Bob is 25 years old.
Charlie is 28 years old.
```

### Notes:

- `it->first`: key
- `it->second`: value
- Iteration is in ascending order of keys

---

## Types of Iterators

| Type              | Description                  | Use Case            |
|-------------------|------------------------------|---------------------|
| `iterator`        | Read/write access             | Modifying elements  |
| `const_iterator`  | Read-only access              | Read-only iteration |
| `reverse_iterator`| Reverse direction traversal   | Backward iteration  |
| `auto`            | Type deduction (C++11+)       | Cleaner code        |

### Example Using `auto`:

```cpp
for (auto it = ages.begin(); it != ages.end(); ++it) {
    std::cout << it->first << ": " << it->second << '\n';
}
```

---

## Modify Values in Vector

```cpp
for (auto it = nums.begin(); it != nums.end(); ++it) {
    *it += 5; // increment each number
}
```

---

## Modifying Map Elements

You can modify values but not keys:

```cpp
it->second = 99; // OK
it->first = "NewKey"; // ❌ Error: keys are read-only
```

---

## Summary

| Feature           | `std::vector`                  | `std::map`                             |
|------------------|-------------------------------|----------------------------------------|
| Access pattern   | Linear (insertion order)       | Sorted by key                          |
| Dereference      | `*it`                          | `it->first`, `it->second`              |
| Modifiability    | Full (`*it = ...`)             | Only value (`it->second = ...`)        |
| Traversal Order  | In insertion order             | Sorted ascending by key                |

