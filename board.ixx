module;

#include <SFML/Graphics.hpp>
#include <array>
#include <span>

export module board;
import tetromino;

export class Board{
    public:
        static constexpr int WIDTH = 10;
        static constexpr int HEIGHT = 20;
        static constexpr float BLOCK_SIZE = 30.0f;

        inline static const std::array<sf::Color, 8> BLOCK_COLORS = {
            sf::Color::Black,
            sf::Color::Cyan,
            sf::Color::Yellow,
            sf::Color(128, 0, 128), //purple
            sf::Color::Green,
            sf::Color::Red,
            sf::Color::Blue,
            sf::Color(255, 165, 0) //orange
        };

        Board(){
            grid.fill({});
            locked_grid.fill({});
        }

        void initialize(){
            grid.fill({});
            locked_grid.fill({});
        }

        void clear_board(){
            grid.fill({});
            locked_grid.fill({});
        }

        void update_tetromino(const Tetromino& tetromino){

            for(int y=0; y < HEIGHT; ++y){
                for(int x=0; x < WIDTH; ++x){
                    if(!locked_grid[y][x]){
                        grid[y][x] = 0;
                    }
                }
            }

            auto shape = tetromino.get_shape();
            int type = static_cast<int>(tetromino.get_type());
            int pos_x = tetromino.get_pos_x();
            int pos_y = tetromino.get_pos_y();


            for(int y = 0; y < Tetromino::GRID_SIZE; ++y){
                for(int x = 0; x < Tetromino::GRID_SIZE; ++x){
                    if(shape[y][x]){
                        
                        int board_x = pos_x + x;
                        int board_y = pos_y + y;

                        if(board_x >= 0 && board_x < WIDTH && board_y >= 0 && board_y < HEIGHT){
                            grid[board_y][board_x] = type;
                        }
                    }
                }
            }
        }

        void lock_current_piece(const Tetromino& tetromino){
            auto shape = tetromino.get_shape();
            int type  = static_cast<int>(tetromino.get_type());
            int pos_x = tetromino.get_pos_x();
            int pos_y = tetromino.get_pos_y();

            for (int y = 0; y < Tetromino::GRID_SIZE; ++y) {
                for (int x = 0; x < Tetromino::GRID_SIZE; ++x) {
                    if (shape[y][x]) {
                        int board_x = pos_x + x;
                        int board_y = pos_y + y;

                    //Set locked state if not out of bounds
                        if (board_x >= 0 && board_x < WIDTH && board_y >= 0 && board_y < HEIGHT) {
                            locked_grid[board_y][board_x] = true;
                        }
                    }
                }
            }
        }

        bool is_collision(const Tetromino& tetromino) const {

            auto shape = tetromino.get_shape();
            int pos_x = tetromino.get_pos_x();
            int pos_y = tetromino.get_pos_y();

            for (int y = 0; y < Tetromino::GRID_SIZE; ++y) {
                for (int x = 0; x < Tetromino::GRID_SIZE; ++x) {
                    if (shape[y][x]) {
                        int board_x = pos_x + x;
                        int board_y = pos_y + y;
                        
                        if (board_x < 0 || board_x >= WIDTH || board_y >= HEIGHT) {
                            return true;
                        }
                        
                        // Check collision with locked pieces
                        if (board_y >= 0 && locked_grid[board_y][board_x]) {
                            return true;
                        }
                    }
                }
            }

            return false;
        }

        std::span<const std::array<int, WIDTH>> get_grid() const{
            return grid;
        }

        bool is_line_complete(int row) const{
            for(int x = 0; x < WIDTH; ++x){
                if(!locked_grid[row][x]) return false;
            }

            return true;
        }

        void clear_line(int row){
            for(int y=row; y > 0; --y){
                grid[y] = grid[y-1];
                locked_grid[y] = locked_grid[y-1];
            }

            grid[0].fill(0);
            locked_grid[0].fill(false);
        }

        int clear_complete_lines() {
            int lines_cleared = 0;
            for (int y = HEIGHT - 1; y >= 0; --y) {
                if (is_line_complete(y)) {
                    clear_line(y);
                    ++lines_cleared;
                    ++y; // Check the same row again as everything shifted down
                }
            }
            return lines_cleared;
        }

        bool is_game_over(const Tetromino& tetromino) const {
            // If a newly spawned piece immediately collides, game is over
            return is_collision(tetromino);
        }


        private:
            std::array<std::array<int, WIDTH>, HEIGHT> grid;
            std::array<std::array<bool,WIDTH>, HEIGHT> locked_grid{};


};