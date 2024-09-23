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
#include <ranges>

namespace setm {

/**
 * @brief Calculates the Minimax criterion.
 *
 * The Minimax criterion finds the maximum of the minimum profits for
 * each strategy. It represents the best worst-case scenario.
 *
 * @param profits A range of rows, where each row is a collection of profits.
 * @return The Minimax value, which is the maximum of the minimum profits.
 */
inline consteval auto minimax(const std::ranges::range auto& profits) {
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
inline consteval T savage(std::array<std::array<T, columns>, rows> profits) {
    for(auto col{ 0uz }; col < columns; ++col) {
        // Find the maximum value in the column.
        const auto max_value{
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
 * @param rng A range of rows, where each row is a collection of profits.
 * @param coefficient A weight value between 0 and 1 for the Hurwicz calculation.
 * @return The Hurwicz value, representing the best expected outcome
 *         based on the given coefficient.
 */
inline consteval auto hurwicz(const std::ranges::range auto& rng, std::floating_point auto coefficient) {
    return std::ranges::max(rng | std::views::transform([coefficient](const auto& row) {
                                const auto min_outcome{ *std::ranges::min_element(row) };
                                const auto max_outcome{ *std::ranges::max_element(row) };
                                return coefficient * min_outcome + (1 - coefficient) * max_outcome;
                            }));
}

}  // namespace setm


/**
 * @brief Main function to execute decision criterion calculations.
 *
 * This function initializes a profit matrix and calls the decision-making
 * criterion functions to compute and display their values.
 */
int main() {
    constexpr auto columns{ 5uz };
    constexpr auto rows{ 4uz };

    constexpr std::array<std::array<double, columns>, rows> profits{
        { { { 15, 10, 0, -6, 17 } },
          { { 3, 14, 8, 9, 2 } },
          { { 1, 5, 14, 20, -3 } },
          { { 7, 19, 10, 2, 0 } } }
    };

    constexpr auto minimax_value{ setm::minimax(profits) };
    constexpr auto savage_value{ setm::savage(profits) };
    constexpr auto coefficient{ 0.8 };
    constexpr auto hurwicz_value{ setm::hurwicz(profits, coefficient) };

    std::cout << "Minimax: " << minimax_value
              << "\nSavage: " << savage_value
              << "\nHurwicz: " << hurwicz_value << '\n';
}
