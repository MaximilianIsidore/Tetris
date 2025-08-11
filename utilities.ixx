module;

#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

export module utilities;
import board;
import tetromino;
import board_entity;

export Tetromino spawn_new_tetromino(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1,7);
    return Tetromino(static_cast<Tetromino::Type>(dis(gen)));
}

export void draw_next_piece(sf::RenderWindow& window, const Tetromino& next_piece) {
    // Draw preview box
    sf::RectangleShape preview_box;
    preview_box.setSize(sf::Vector2f(6 * Board::BLOCK_SIZE, 6 * Board::BLOCK_SIZE));
    preview_box.setPosition({(Board::WIDTH + 0.5f) * Board::BLOCK_SIZE, Board::BLOCK_SIZE});
    preview_box.setFillColor(sf::Color::Black);
    preview_box.setOutlineColor(sf::Color::White);
    preview_box.setOutlineThickness(2.0f);
    
    window.draw(preview_box);
    
    float preview_x = (Board::WIDTH + 1.5f) * Board::BLOCK_SIZE;
    float preview_y = 2 * Board::BLOCK_SIZE;
    
    sf::RectangleShape block(sf::Vector2f(Board::BLOCK_SIZE, Board::BLOCK_SIZE));
    block.setOutlineColor(sf::Color::White);
    block.setOutlineThickness(1.0f);
    
    auto next_shape = next_piece.get_shape();
    int type = static_cast<int>(next_piece.get_type());
    block.setFillColor(Board::BLOCK_COLORS[type]);
    
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if (next_shape[y][x]) {
                block.setPosition({preview_x + x * Board::BLOCK_SIZE, preview_y + y * Board::BLOCK_SIZE});
                window.draw(block);
            }
        }
    }
}

export void draw_score(sf::RenderWindow& window, int score, sf::Font& font, bool game_over) {
    sf::Text score_text(font);
    //score_text.setFont(font);
    score_text.setCharacterSize(24);
    score_text.setFillColor(sf::Color::White);
    
    // Position below the next piece preview
    float text_x = (Board::WIDTH + 0.5f) * Board::BLOCK_SIZE;
    float text_y = 8 * Board::BLOCK_SIZE;
    
    if (game_over) {
        score_text.setString("Game Over!\nScore: " + std::to_string(score) + "\nPress R to restart");
    } else {
        score_text.setString("Score: " + std::to_string(score));
    }
    
    score_text.setPosition({text_x, text_y});
    window.draw(score_text);
}