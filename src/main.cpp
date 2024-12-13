#include "entities.cpp"  // Include the entities class file

int main() {
    Room room;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Display Room\n";
        cout << "2. Move all animated entities\n";
        cout << "3. Display entity state by coordinates\n";
        cout << "4. Reset the room\n";
        cout << "5. Finish\n";

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                room.displayRoom();
                break;
            case 2:
                // Move all animated entities
                for (auto& row : room.board) {
                    for (auto& cell : row) {
                        if (cell != nullptr && dynamic_cast<AnimateEntity*>(cell) != nullptr)
                            dynamic_cast<AnimateEntity*>(cell)->move(room.board);
                    }
                }
                room.displayRoom();  // Display the updated grid after moving
                break;
            case 3: {
                // Display properties of an entity based on user-specified coordinates
                int row, col;
                cout << "Enter row and column: ";
                cin >> row >> col;

                if (row >= 0 && row < 12 && col >= 0 && col < 12 && room.board[row][col] != nullptr) {
                    cout << "\nEntity properties:\n";
                    cout << "Type: " << room.board[row][col]->getSymbol() << "\n";
                    if (auto* animateEntity = dynamic_cast<AnimateEntity*>(room.board[row][col]))
                        animateEntity->displayProperties();
                } else {
                    cout << "\nNo entity at the specified coordinates.\n";
                }
                break;
            }
            case 4:
                room = Room(); // Reset the room
                cout << "\nRoom reset.\n";
                break;
            case 5:
                return 0; // Finish the program
            default:
                cout << "\nInvalid choice. Try again.\n";
        }
    }

    return 0;
}
