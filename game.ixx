module;

#include <SFML/Graphics.hpp>
#include <iostream>

export module game;

import board;
import tetromino;
import utilities;
import gamestate;
import board_entity;

export class Game{
    public:

        Game() : window(sf::VideoMode({static_cast<unsigned int>((Board::WIDTH + 7) * Board::BLOCK_SIZE)
                    , static_cast<unsigned int>(Board::HEIGHT * Board::BLOCK_SIZE)}), "Tetris"),
                    entity(state.get_board()), font("arial.ttf") {

            window.setFramerateLimit(60);
            // if (!font.loadFromFile("arial.ttf")) {
            //     std::cout << "Failed to load font\n";
            // }
        }

        void run() {
            while (window.isOpen()) {
                handle_events();
                update();
                render();
            }
        }


    private: 
        //Private member functions
        void handle_events() {

            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }
                if( state.is_game_over()){
                    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>() ) {
                        if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                            state.reset();
                        }
                    }
                }
            }
        }

        void update() {
            float delta_time = clock.restart().asSeconds();
            
            if (!state.is_game_over()) {
                handle_input();
                state.update(delta_time);
            }
        }

        void render() {
            window.clear(sf::Color::Black);
            entity.draw(window);
            draw_next_piece(window, state.get_next_piece());
            draw_score(window, state.get_score(), font, state.is_game_over());
            window.display();
        }

        void handle_input() {
            if (movement_clock.getElapsedTime().asSeconds() >= move_delay) {

                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
                    state.move_left();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
                    state.move_right();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
                    state.move_down();
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
                    state.rotate();
                }
                  
               
                movement_clock.restart();
            }
        }

    private: 
        sf::RenderWindow window;
        BoardEntity entity;
        GameState state;
        sf::Font font;
        sf::Clock clock;
        sf::Clock movement_clock;
        const float move_delay = 0.1f;
};