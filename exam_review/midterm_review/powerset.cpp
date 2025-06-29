#include <iostream>
#include <vector>

std::vector<std::vector<int>> powerSet(const std::vector<int>& input) {
    std::vector<std::vector<int>> result;
    
    if (input.size() != 3) {
        std::cerr << "Input must be a set of exactly 3 elements.\n";
        return result;
    }

    // Generate all subsets (2^3 = 8)
    int n = input.size();
    for (int mask = 0; mask < (1 << n); ++mask) {
        std::vector<int> subset;
        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                subset.push_back(input[i]);
            }
        }
        result.push_back(subset);
    }

    return result;
}

int main() {
    std::vector<int> mySet = {1, 2, 3};
    std::vector<std::vector<int>> subsets = powerSet(mySet);

    std::cout << "Power set:\n";
    for (const auto& subset : subsets) {
        std::cout << "{ ";
        for (int val : subset) {
            std::cout << val << " ";
        }
        std::cout << "}\n";
    }

    return 0;
}
