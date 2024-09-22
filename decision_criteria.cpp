/**
 * @file decision_criterion.cpp
 * @brief Implements decision-making criterion for profit matrices.
 *
 * This module contains functions that evaluate decision-making strategies
 * based on a matrix of profits using the Minimax, Savage, and Hurwicz
 * criterion. Each function processes the input matrix to determine the optimal
 * solution based on specified decision-making rules.
 */

#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <ranges>

namespace setm {

/**
 * @brief Calculates the Minimax criterion.
 *
 * The Minimax criterion finds the maximum of the minimum profits for
 * each strategy. It represents the best worst-case scenario.
 *
 * @tparam T Type of the matrix elements.
 * @tparam rows Number of rows in the profit matrix.
 * @tparam columns Number of columns in the profit matrix.
 * @param profits A 2D array representing the profit matrix.
 * @return The Minimax value, which is the maximum of the minimum profits.
 */
template<class T, size_t rows, size_t columns>
static constexpr T minimax(const std::array<std::array<T, columns>, rows>& profits) {
    return std::ranges::max(profits | std::views::transform([](const auto& row) {
                                return *std::ranges::min_element(row);
                            }));
}

/**
 * @brief Calculates the Savage criterion.
 *
 * The Savage criterion evaluates the profit matrix by subtracting
 * the maximum value of each column from the values in that column,
 * and then finds the minimum of the maximum profits from the resulting
 * adjusted matrix.
 *
 * @tparam T Type of the matrix elements.
 * @tparam rows Number of rows in the profit matrix.
 * @tparam columns Number of columns in the profit matrix.
 * @param profits A 2D array representing the profit matrix.
 * @return The Savage value, which is the minimum of the maximum adjusted profits.
 */
template<class T, size_t rows, size_t columns>
static constexpr T savage(std::array<std::array<T, columns>, rows> profits) {
    for(auto col{ 0uz }; col < columns; ++col) {
        // Find the maximum value in the column.
        const T max_value{
            std::ranges::max(profits | std::views::transform([col](const auto& row) {
                                 return row[col];
                             }))
        };

        // Subtract the maximum value from each element in the column.
        for(auto row{ 0uz }; row < rows; ++row)
            profits[row][col] = max_value - profits[row][col];
    }

    // Find the minimum of the maximum values of each row.
    return std::ranges::min(profits | std::views::transform([](const auto& row) {
                                return *std::ranges::max_element(row);
                            }));
}

/**
 * @brief Calculates the Hurwicz criterion.
 *
 * The Hurwicz criterion computes a weighted average of the minimum
 * and maximum outcomes for each strategy, where the weight is determined
 * by a specified coefficient.
 *
 * @tparam T Type of the matrix elements.
 * @tparam rows Number of rows in the profit matrix.
 * @tparam columns Number of columns in the profit matrix.
 * @param profits A 2D array representing the profit matrix.
 * @param coefficient A weight value between 0 and 1 for the Hurwicz calculation.
 * @return The Hurwicz value, representing the best expected outcome
 *         based on the given coefficient.
 */
template<class T, size_t rows, size_t columns>
static constexpr T hurwicz(const std::array<std::array<T, columns>, rows>& profits, T coefficient) {
    auto max_value{ std::numeric_limits<T>::lowest() };
    for(const auto& row : profits) {
        const auto min_outcome{ *std::ranges::min_element(row) };
        const auto max_outcome{ *std::ranges::max_element(row) };
        const auto hurwicz_value{ coefficient * min_outcome + (1 - coefficient) * max_outcome };

        max_value = std::max(max_value, hurwicz_value);
    }

    return max_value;
}

}  // namespace setm


/**
 * @brief Main function to execute decision criterion calculations.
 *
 * This function initializes a profit matrix and calls the decision-making
 * criterion functions to compute and display their values.
 */
int main() {
    constexpr static auto columns{ 5uz };
    constexpr static auto rows{ 4uz };

    constexpr static std::array<std::array<double, columns>, rows> profits{
        { { { 15, 10, 0, -6, 17 } },
          { { 3, 14, 8, 9, 2 } },
          { { 1, 5, 14, 20, -3 } },
          { { 7, 19, 10, 2, 0 } } }
    };

    constexpr static auto minimax_value{ setm::minimax(profits) };
    constexpr static auto savage_value{ setm::savage(profits) };
    constexpr static auto coefficient{ 0.8 };
    constexpr static auto hurwicz_value{ setm::hurwicz(profits, coefficient) };

    std::cout << "Minimax: " << minimax_value
              << "\nSavage: " << savage_value
              << "\nHurwicz: " << hurwicz_value << '\n';
}
