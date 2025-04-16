# Pac-Man Game

Welcome to the Pac-Man Game repository! This project is a console-based implementation of the classic Pac-Man game developed in C++ using the Simple and Fast Multimedia Library (SFML). It features multiple difficulty levels, dynamic enemy movements, and a scoring system.

## Overview


In this game, you control Pac-Man, navigating through a maze to collect all the dots while avoiding colored ghosts. The game features three difficulty levels, each with different enemy behavior, and allows players to view and save high scores.

## Features

- **Game World Map**: Dynamic maze with obstacles and food points.
- **Difficulty Levels**:
  - **Easy**: Random enemy movements.
  - **Medium**: Faster enemy movements.
  - **Hard**: Enemies use Breadth-First Search (BFS) algorithm.
- **Score Counter**: Tracks collected food points.
- **Collision Detection**: Handles collisions with enemies and game outcomes.
- **High Scores**: Save and display top scores (up to three).

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., g++, clang).
- **SFML**: Install the SFML library. Follow the [SFML installation guide](https://www.sfml-dev.org/download.php) for your platform.

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/pacman-game.git
   cd pacman-game
