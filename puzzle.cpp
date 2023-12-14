// 20-Ball Pyramid Puzzle Solver in C++20

// Copyright (c) 2023 Yousuke Takada
// SPDX-License-Identifier: MIT

#include <array>
#include <compare>
#include <functional>
#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <utility>
#include <vector>

struct Coord
{
    int i{};
    int j{};

    friend constexpr auto operator<=>(const Coord&, const Coord&) = default;

    friend constexpr Coord operator+(const Coord& lhs, const Coord& rhs)
    {
        return {
            lhs.i + rhs.i,
            lhs.j + rhs.j,
        };
    }
};

class Puzzle
{
public:
    using Balls = std::array<char, 20>;
    using OnSolutionCallback = std::function<void(const Balls&)>;

    explicit Puzzle(OnSolutionCallback on_solution_callback) :
        on_solution_callback{std::move(on_solution_callback)}
    {}

    static std::string format_as_pyramid(const Balls& balls)
    {
        std::string str = R"(
         (0)
         / \
        /   \                   (1)
      (0)---(0)                 / \
      / \   / \                /   \             (2)
     /   \ /   \             (1)---(1)           / \
   (0)---(0)---(0)           / \   / \          /   \       (3)
   / \   / \   / \          /   \ /   \       (2)---(2)
  /   \ /   \ /   \       (1)---(1)---(1)
(0)---(0)---(0)---(0)
)";

        auto cur_ball = std::begin(balls);

        for (const auto c : {'0', '1', '2', '3'}) {
            for (std::size_t i = 0; (i = str.find(c, i)) != std::string::npos; ++i) {
                str[i] = *cur_ball++;
            }
        }

        return str;
    }

    void solve()
    {
        solve(std::begin(pieces));
    }

private:
    using Shape = std::vector<Coord>;

    struct Piece
    {
        char symbol{};
        std::vector<Shape> variants;
    };

    inline static const std::vector<Piece> pieces = {
        {
            .symbol = 'L',
            .variants = {
                // We shall fix the orientation of 'L'.
                {
                    { 0,  0},
                    { 1,  0},
                    { 2,  0}, { 2,  1},
                },
            },
        },
        {
            .symbol = 'T',
            .variants = {
                {
                    { 0,  0}, { 0,  1}, { 0,  2},
                              { 1,  1},
                },
                {
                    { 0,  0},
                    { 1,  0}, { 1,  1},
                    { 2,  0},
                },
                {
                              {-1,  1},
                    { 0,  0}, { 0,  1}, { 0,  2},
                },
                {
                              {-1,  1},
                    { 0,  0}, { 0,  1},
                              { 1,  1},
                },
            },
        },
        {
            .symbol = 'I',
            .variants = {
                {
                    { 0,  0},
                    { 1,  0},
                    { 2,  0},
                    { 3,  0},
                },
                {
                    { 0,  0}, { 0,  1}, { 0,  2}, { 0,  3}
                },
            },
        },
        {
            .symbol = 'v',
            .variants = {
                {
                    { 0,  0},
                    { 1,  0}, { 1,  1},
                },
                {
                              {-1,  1},
                    { 0,  0}, { 0,  1},
                },
                {
                    { 0,  0}, { 0,  1},
                              { 1,  1},
                },
                {
                    { 0,  0}, { 0,  1},
                    { 1,  0},
                },
            },
        },
        {
            .symbol = 'i',
            .variants = {
                {
                    { 0,  0},
                    { 1,  0},
                    { 2,  0},
                },
                {
                    { 0,  0}, { 0,  1}, { 0,  2},
                },
            },
        },
        {
            .symbol = 'd',
            .variants = {
                {
                    { 0,  0},
                    { 1,  0},
                },
                {
                    { 0,  0}, { 0,  1},
                },
            },
        },
    };

    using Layer = std::map<Coord, std::size_t>;

    inline static const std::vector<std::vector<Layer>> layers_sets = {
        // Square lattice layers parallel to 0-1-3-6 and 9-15-18-19
        {
            {
                {{0, 0},  0},
                {{1, 0},  1},
                {{2, 0},  3},
                {{3, 0},  6},
            },
            {
                {{0, 0},  2}, {{0, 1}, 10},
                {{1, 0},  4}, {{1, 1}, 11},
                {{2, 0},  7}, {{2, 1}, 13},
            },
            {
                {{0, 0},  5}, {{0, 1}, 12}, {{0, 2}, 16},
                {{1, 0},  8}, {{1, 1}, 14}, {{1, 2}, 17},
            },
            {
                {{0, 0},  9}, {{0, 1}, 15}, {{0, 2}, 18}, {{0, 3}, 19},
            },
        },
        // Square lattice layers parallel to 6-7-8-9 and 0-10-16-19
        {
            {
                {{0, 0},  6},
                {{1, 0},  7},
                {{2, 0},  8},
                {{3, 0},  9},
            },
            {
                {{0, 0},  3}, {{0, 1}, 13},
                {{1, 0},  4}, {{1, 1}, 14},
                {{2, 0},  5}, {{2, 1}, 15},
            },
            {
                {{0, 0},  1}, {{0, 1}, 11}, {{0, 2}, 17},
                {{1, 0},  2}, {{1, 1}, 12}, {{1, 2}, 18},
            },
            {
                {{0, 0},  0}, {{0, 1}, 10}, {{0, 2}, 16}, {{0, 3}, 19},
            },
        },
        // Square lattice layers parallel to 0-2-5-9 and 6-13-17-19
        {
            {
                {{0, 0},  0},
                {{1, 0},  2},
                {{2, 0},  5},
                {{3, 0},  9},
            },
            {
                {{0, 0},  1}, {{0, 1}, 10},
                {{1, 0},  4}, {{1, 1}, 12},
                {{2, 0},  8}, {{2, 1}, 15},
            },
            {
                {{0, 0},  3}, {{0, 1}, 11}, {{0, 2}, 16},
                {{1, 0},  7}, {{1, 1}, 14}, {{1, 2}, 18},
            },
            {
                {{0, 0},  6}, {{0, 1}, 13}, {{0, 2}, 17}, {{0, 3}, 19},
            },
        },
    };

    void solve(std::vector<Piece>::const_iterator cur_piece)
    {
        if (cur_piece == std::end(pieces)) {
            on_solution();
            return;
        }

        for (const auto& variant : cur_piece->variants) {
            // We shall place 'L' only in the first set of parallel layers.
            const std::size_t num_views = (cur_piece->symbol == 'L') ? 1 : 3;

            for (const auto& layers : layers_sets | std::views::take(num_views)) {
                for (const auto& layer : layers) {
                    for (const auto& pos : std::views::keys(layer)) {
                        if (can_put(variant, layer, pos)) {
                            put(cur_piece->symbol, variant, layer, pos);
                            solve(cur_piece + 1);
                            unput(variant, layer, pos);
                        }
                    }
                }
            }
        }
    }

    bool can_put(const Shape& shape, const Layer& layer, const Coord& pos) const
    {
        for (const auto& offset : shape) {
            const auto it = layer.find(pos + offset);

            if (it == std::end(layer) || balls[it->second] != '\0') {
                return false;
            }
        }

        return true;
    }

    void put(char symbol, const Shape& shape, const Layer& layer, const Coord& pos)
    {
        for (const auto& offset : shape) {
            const auto it = layer.find(pos + offset);

            balls[it->second] = symbol;
        }
    }

    void unput(const Shape& shape, const Layer& layer, const Coord& pos)
    {
        put('\0', shape, layer, pos);
    }

    void on_solution() const
    {
        on_solution_callback(balls);
    }

    Balls balls{};
    OnSolutionCallback on_solution_callback{};
};

int main()
{
    std::size_t num_solutions = 0;

    Puzzle puzzle{[&](const auto& balls)
    {
        std::cout << "Solution #" << num_solutions++ << ":\n"
                  << Puzzle::format_as_pyramid(balls) << "\n";
    }};

    puzzle.solve();

    std::cout << num_solutions << " solutions found.\n";
}
