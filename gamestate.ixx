module;

export module gamestate;

import board;
import tetromino;
import utilities;

export class GameState{
    public: 
        GameState() 
            : board()
            , current_piece(spawn_new_tetromino())
            , next_piece(spawn_new_tetromino())
            , game_over(false)
            , score(0) {
            board.initialize();
        }

        void update(float delta_time) {
            if (!game_over) {
                handle_falling(delta_time);
            }
        }

        void move_left() {
            if (game_over) return;
            current_piece.backup_position();
            current_piece.move_left();
            if (board.is_collision(current_piece)) {
                current_piece.undo_move();
            }
        }

        void move_right() {
            if (game_over) return;
            current_piece.backup_position();
            current_piece.move_right();
            if (board.is_collision(current_piece)) {
                current_piece.undo_move();
            }
        }

        void move_down() {
            if (game_over) return;
            current_piece.backup_position();
            current_piece.move_down();
            if (board.is_collision(current_piece)) {
                current_piece.undo_move();
            }
        }

        void rotate() {
            if (game_over) return;
            current_piece.backup_position();
            current_piece.rotate();
            if (board.is_collision(current_piece)) {
                current_piece.undo_move();
            }
        }

        void reset() {
            board.clear_board();
            current_piece = spawn_new_tetromino();
            next_piece = spawn_new_tetromino();
            game_over = false;
            score = 0;
        }

        // Getters
        const Board& get_board() const { return board; }
        const Tetromino& get_current_piece() const { return current_piece; }
        const Tetromino& get_next_piece() const { return next_piece; }
        bool is_game_over() const { return game_over; }
        int get_score() const { return score; }




    private: 

        void handle_falling(float delta_time) {
            falling_time += delta_time;
            if (falling_time >= fall_delay) {
                current_piece.backup_position();
                current_piece.move_down();
                
                if (board.is_collision(current_piece)) {
                    current_piece.undo_move();
                    board.lock_current_piece(current_piece);
                    
                    int lines = board.clear_complete_lines();
                    score += lines * 100;
                    
                    current_piece = next_piece;
                    next_piece = spawn_new_tetromino();
                    
                    if (board.is_game_over(current_piece)) {
                        game_over = true;
                    }
                }
                
                falling_time = 0;
            }
            board.update_tetromino(current_piece);
        }

        Board board;
        Tetromino current_piece;
        Tetromino next_piece;
        bool game_over;
        int score;
        float falling_time = 0;
        const float fall_delay = 0.5f;
};