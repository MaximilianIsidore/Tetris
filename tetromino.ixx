module;

#include <array>

export module tetromino;

export class Tetromino{

    public:
        enum Type {I =1, O, T, S, Z, J, L};
        static constexpr int GRID_SIZE = 4;

        Tetromino(Type type)
            : curren_type(type)
            , current_rotation(0)
            , pos_x(3)
            , pos_y(0);
            , last_pos_x(3)
            , last_pos_y(0){

                intialize_shape(type);
                last_shape = current_shape;
        }

        void move_left() { --pos_x; }
        void move_right() { ++pos_x; }
        void move_down() { ++pos_y; }

        //When you rotate a 4×4 matrix clockwise, every element at position (i, j) moves to (j, 3 - i)
        void rotate() {
            std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> temp = current_shape;
            
            for (int i = 0; i < GRID_SIZE; ++i) {
                for (int j = 0; j < GRID_SIZE; ++j) {
                    current_shape[j][GRID_SIZE-1-i] = temp[i][j];
                }
            }
            current_rotation = (current_rotation + 1) % 4;
        }

        void undo_move() {
            pos_x = last_pos_x;
            pos_y = last_pos_y;
            current_shape = last_shape;
            current_rotation = last_rotation;
        }

        //Store the current state in case something goes wrong
        void backup_position() {
            last_pos_x = pos_x;
            last_pos_y = pos_y;
            last_shape = current_shape;
            last_rotation = current_rotation;
        }

        int get_pos_x() const { return pos_x; }
        int get_pos_y() const { return pos_y; }
        Type get_type() const { return current_type; }
        const auto& get_shape() const { return current_shape; }


        private:
            void initialize_shape(Type type) {
                current_shape.fill({});
                switch (type) {
                    case I:
                        current_shape[1] = {true, true, true, true};
                        break;
                    case O:
                        current_shape[1][1] = current_shape[1][2] = 
                        current_shape[2][1] = current_shape[2][2] = true;
                        break;
                    case T:
                        current_shape[1] = {true, true, true, false};
                        current_shape[2][1] = true;
                        break;
                    case S:
                        current_shape[1] = {false, true, true, false};
                        current_shape[2] = {true, true, false, false};
                        break;
                    case Z:
                        current_shape[1] = {true, true, false, false};
                        current_shape[2] = {false, true, true, false};
                        break;
                    case J:
                        current_shape[1] = {true, true, true, false};
                        current_shape[2][0] = true;
                        break;
                    case L:
                        current_shape[1] = {true, true, true, false};
                        current_shape[2][2] = true;
                        break;
                }
            }

        
        private: 

            Type current_type;
            int current_rotation;
            int last_rotation;
            int pos_x; // x position on the board with a size of (width = 10, height = 20) in our implementation
            int pos_y; // y position on the board with a size of (width = 10, height = 20) in our implementation
            int last_pos_x;
            int last_pos_y;
            std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> last_shape;
            std::array<std::array<bool, GRID_SIZE>, GRID_SIZE> current_shape;
                        

};