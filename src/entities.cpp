#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

// Base class for entities in the game
class Entity {
public:
    int row;
    int col;

    Entity(int row, int col) : row(row), col(col) {}

    virtual char getSymbol() const {
        return '.';
    }
};

// Inanimate entities like stones
class InanimateEntity : public Entity {
public:
    InanimateEntity(int row, int col) : Entity(row, col) {}

    char getSymbol() const override {
        return '.';
    }
};

// Special type of inanimate entity: Stone
class Stone : public InanimateEntity {
public:
    Stone(int row, int col) : InanimateEntity(row, col) {}

    char getSymbol() const override {
        return 'S';
    }
};

// Another special inanimate entity: Hole
class Hole : public InanimateEntity {
public:
    int depth;

    Hole(int row, int col, int depth) : InanimateEntity(row, col), depth(depth) {}

    char getSymbol() const override {
        return 'O';
    }
};

// Base class for animated entities (those that can move)
class AnimateEntity : public Entity {
public:
    int health;

    AnimateEntity(int row, int col) : Entity(row, col), health(100) {}

    virtual void move(vector<vector<Entity*>>& board) = 0;
    virtual char getSymbol() const = 0;
    virtual void displayProperties() = 0;
};

// Player-controlled entity: Human
class Human : public AnimateEntity {
public:
    string name;

    Human(int row, int col, const string& name) : AnimateEntity(row, col), name(name) {
        health = 100;
    }

    void move(vector<vector<Entity*>>& board) override {
        if (health <= 0) {
            board[row][col] = nullptr;
            return;
        }

        if (col + 1 < 10 && board[row][col + 1] == nullptr) {
            board[row][col] = nullptr;
            col++;
            board[row][col] = this;
        } else {
            int direction = rand() % 4;
            if (direction == 0 && row - 1 >= 0 && board[row - 1][col] == nullptr) {
                board[row][col] = nullptr;
                row--;
                board[row][col] = this;
            } else if (direction == 1 && row + 1 < 10 && board[row + 1][col] == nullptr) {
                board[row][col] = nullptr;
                row++;
                board[row][col] = this;
            } else if (direction == 2 && col - 1 >= 0 && board[row][col - 1] == nullptr) {
                board[row][col] = nullptr;
                col--;
                board[row][col] = this;
            } else if (direction == 3 && col + 1 < 10 && board[row][col + 1] == nullptr) {
                board[row][col] = nullptr;
                col++;
                board[row][col] = this;
            }
        }

        health--;

        if (health < 0) {
            health = 0;
        }
    }

    char getSymbol() const override {
        return '@';
    }

    void displayProperties() override {
        cout << "Type: Human\n";
        cout << "Name: " << name << "\n";
        cout << "Health: " << health << "\n";
    }
};

// Non-player-controlled entity: Dragon
class Dragon : public AnimateEntity {
public:
    Dragon(int row, int col) : AnimateEntity(row, col) {}

    void move(vector<vector<Entity*>>& board) override {
        int direction = rand() % 4;
        if (direction == 0 && row - 1 >= 0 && board[row - 1][col] == nullptr) {
            board[row][col] = nullptr;
            row--;
            board[row][col] = this;
        } else if (direction == 1 && row + 1 < 12 && board[row + 1][col] == nullptr) {
            board[row][col] = nullptr;
            row++;
            board[row][col] = this;
        } else if (direction == 2 && col - 1 >= 0 && board[row][col - 1] == nullptr) {
            board[row][col] = nullptr;
            col--;
            board[row][col] = this;
        } else if (direction == 3 && col + 1 < 12 && board[row][col + 1] == nullptr) {
            board[row][col] = nullptr;
            col++;
            board[row][col] = this;
        }

        health -= rand() % 6;

        if (health <= 0) {
            board[row][col] = nullptr;
        }
    }

    char getSymbol() const override {
        return '#';
    }

    void displayProperties() override {
        cout << "Type: Dragon\n";
        cout << "Health: " << health << "\n";
    }
};

// Another non-player-controlled entity: Monster
class Monster : public AnimateEntity {
public:
    int strength;

    Monster(int row, int col, int strength) : AnimateEntity(row, col), strength(strength) {}

    void move(vector<vector<Entity*>>& board) override {
        int direction = rand() % 4;
        int steps = rand() % (strength + 1);
        for (int i = 0; i < steps; ++i) {
            if (health <= 0) {
                board[row][col] = nullptr;
                return;
            }

            if (direction == 0 && row - 1 >= 0 && board[row - 1][col] == nullptr) {
                board[row][col] = nullptr;
                row--;
                board[row][col] = this;
            } else if (direction == 1 && row + 1 < 12 && board[row + 1][col] == nullptr) {
                board[row][col] = nullptr;
                row++;
                board[row][col] = this;
            } else if (direction == 2 && col - 1 >= 0 && board[row][col - 1] == nullptr) {
                board[row][col] = nullptr;
                col--;
                board[row][col] = this;
            } else if (direction == 3 && col + 1 < 12 && board[row][col + 1] == nullptr) {
                board[row][col] = nullptr;
                col++;
                board[row][col] = this;
            } else {
                int randDirection = rand() % 4;
                if (randDirection == 0 && row - 1 >= 0 && board[row - 1][col] == nullptr) {
                    board[row][col] = nullptr;
                    row--;
                    board[row][col] = this;
                } else if (randDirection == 1 && row + 1 < 12 && board[row + 1][col] == nullptr) {
                    board[row][col] = nullptr;
                    row++;
                    board[row][col] = this;
                } else if (randDirection == 2 && col - 1 >= 0 && board[row][col - 1] == nullptr) {
                    board[row][col] = nullptr;
                    col--;
                    board[row][col] = this;
                } else if (randDirection == 3 && col + 1 < 12 && board[row][col + 1] == nullptr) {
                    board[row][col] = nullptr;
                    col++;
                    board[row][col] = this;
                }
            }
        }
        health -= strength;

        if (health <= 0) {
            board[row][col] = nullptr;
        }
    }

    char getSymbol() const override {
        return '*';
    }

    void displayProperties() override {
        cout << "Type: Monster\n";
        cout << "Strength: " << strength << "\n";
        cout << "Health: " << health << "\n";
    }
};

// Represents the game environment: the room
class Room {
public:
    vector<vector<Entity*>> board;

    Room() : board(12, vector<Entity*>(12, nullptr)) {
        srand(static_cast<unsigned>(time(nullptr)));
        for (int i = 0; i < 2; ++i) {
            addEntity(new Stone(rand() % 12, rand() % 12));
        }
        for (int i = 0; i < 2; ++i){
            addEntity(new Hole(rand() % 12, rand() % 12, rand() % 21));
        }

        for (int i = 0; i < 3; ++i) {
            addEntity(new Human(rand() % 12, rand() % 12, "Human" + to_string(i + 1)));
        }

        for (int i = 0; i < 3; ++i) {
            addEntity(new Monster(rand() % 12, rand() % 12, rand() % 6));
        }

        for (int i = 0; i < 3; ++i) {
            addEntity(new Dragon(rand() % 12, rand() % 12));
        }
    }

    void addEntity(Entity* entity) {
        board[entity->row][entity->col] = entity;
    }

    void displayRoom() {
        for (auto& row : board) {
            for (auto& cell : row) {
                if (cell) {
                    cout << cell->getSymbol() << " ";
                } else {
                    cout << ". ";
                }
            }
            cout << endl;
        }
    }
};
