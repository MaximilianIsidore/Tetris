module;

#include <SFML/Graphics.hpp>

export module board_entity;

import board;

export class BoardEntity {
public:
    explicit BoardEntity(const Board& board) : board_(board) {}

    void draw(sf::RenderWindow& window) const {
        sf::RectangleShape block(sf::Vector2f(Board::BLOCK_SIZE, Board::BLOCK_SIZE));
        block.setOutlineColor(sf::Color::White);
        block.setOutlineThickness(1.0f);

        auto grid = board_.get_grid();
        for (int y = 0; y < Board::HEIGHT; ++y) {
            for (int x = 0; x < Board::WIDTH; ++x) {
                block.setPosition(x * Board::BLOCK_SIZE, y * Board::BLOCK_SIZE);
                block.setFillColor(Board::BLOCK_COLORS[grid[y][x]]);
                window.draw(block);
            }
        }
    }

private:
    const Board& board_;
};