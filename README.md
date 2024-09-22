# Decision Making Criteria

A C++ implementation of decision-making criteria based on profit matrices.

This project includes methods for evaluating decisions using the **Minimax**, **Sevadge**, and **Hurwicz** criteria.

## Table of Contents

- [Decision Making Criteria](#decision-making-criteria)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Criteria](#criteria)
  - [Installation](#installation)
  - [Usage](#usage)
  - [License](#license)

## Introduction

This project aims to provide a clear and efficient way to evaluate different decision-making strategies based on given profit matrices.

The implemented criteria help in determining optimal solutions in scenarios with uncertain outcomes.

## Criteria

1. **Minimax (MM)**: Finds the maximum of the minimum profits, representing the best worst-case scenario.
2. **Sevadge (S)**: Adjusts profits by subtracting the maximum value of each column, then finds the minimum of the maximum adjusted profits.
3. **Hurwicz (HW)**: Computes a weighted average of the minimum and maximum outcomes based on a specified coefficient.

## Installation

To build and run this project, you need a C++ compiler that supports **C++23**.

You can clone the repository and compile it using the following commands:

```bash
git clone https://github.com/seigtm/decision_making_criteria.git
cd ./decision_making_criteria
# Compile the code (adjust command based on your setup)
clang++ -std=c++23 -o decision_criteria ./decision_criteria.cpp
```

## Usage

After compiling, you can run the executable:

```bash
./decision_criteria
```

The program will output the results for each decision-making criterion based on the predefined profit matrix.

## License

This project is licensed under the **MIT License** - see the [LICENSE](https://github.com/seigtm/decision_making_criteria/tree/main/LICENSE) file for details.

Feel free to modify the content to fit your specific needs and preferences!
