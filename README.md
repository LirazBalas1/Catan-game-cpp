# Catan Game in C++

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Game Rules](#game-rules)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

## Introduction
This project is a C++ implementation of the popular board game "Catan." The game involves players collecting and trading resources, building roads, settlements, and cities, and competing to earn the most victory points. This version supports both AI and human players.

## Features
- **Multiplayer Support:** Play against AI or other human players.
- **AI Players:** Different levels of AI difficulty (easy, medium, hard).
- **Resource Management:** Collect and trade resources to build and expand your settlements.
- **Robber Mechanic:** Implemented according to the official rules.
- **Development Cards:** Buy and use development cards to gain advantages.

## Game Rules
### Objective
The goal of Catan is to be the first player to reach 10 victory points.

### Setup
1. **Board Setup:** The board consists of hexagonal tiles representing different types of terrain, each producing a specific resource (wood, brick, sheep, grain, ore). The tiles are placed randomly.
2. **Initial Placement:** Each player places two settlements and two roads on the board. Each settlement must be at least two edges apart.

### Gameplay
Players take turns in a clockwise order. Each turn consists of the following phases:
1. **Rolling the Dice:** Players roll two six-sided dice to determine which tiles produce resources.
2. **Resource Production:** If a tile’s number matches the dice roll, players with settlements or cities adjacent to that tile collect the corresponding resources.
3. **Trading:** Players can trade resources with other players or with the bank.
4. **Building:** Players use resources to build roads, settlements, cities, or buy development cards.
5. **Using Development Cards:** Players can play development cards to gain special abilities or victory points.

### Robber
- When a player rolls a 7, the robber is activated. The player moves the robber to any tile, blocking its resource production.
- The player who moves the robber can steal a resource card from any player with a settlement or city adjacent to the tile where the robber is placed.
- Players with more than 7 resource cards must discard half (rounded down) of their cards.

### Building Costs
- **Road:** 1 wood, 1 brick
- **Settlement:** 1 wood, 1 brick, 1 sheep, 1 grain
- **City:** 3 ore, 2 grain (upgrades a settlement)
- **Development Card:** 1 ore, 1 sheep, 1 grain

### Winning the Game
The first player to reach 10 victory points wins the game. Points are earned through:
- Settlements (1 point each)
- Cities (2 points each)
- Development cards (varying points)
- Longest Road (2 points for the player with the longest continuous road)
- Largest Army (2 points for the player with the most knights from development cards)

## Requirements
- C++11 or higher
- `doctest` framework for testing

## Installation
1. **Clone the repository:**
   ```sh
   git clone https://github.com/LirazBalas1/Catan-game-cpp.git
   cd Catan-game-cpp
