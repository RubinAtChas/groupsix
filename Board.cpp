#include <iostream>
#include <cstdlib>

class Board {
public:
    enum CellStatus { Water, Miss, Hit, Ship };

    Board() {
        // Creates the pacific ocean
        for (int i = 0; i < 15; ++i)
        {
            for (int j = 0; j < 15; ++j) 
            {
                grid[i][j] = Water;
            }
        }
    }

    // Simple ship placer for testing
    void placeShip(int x, int y) 
    {
        if (isValidPosition(x, y)) 
        {
            grid[x][y] = Ship;
        }
    }

    // Fire the cannons!
    bool fireCannon(int x, int y) {
        if (!isValidPosition(x, y)) return false;

        if (grid[x][y] == Ship) 
        {
            grid[x][y] = Hit;
            return true;  // Hit
        } 
        else if (grid[x][y] == Water) 
        {
            grid[x][y] = Miss;
            return false; // Miss
        }
        return false; // Already hit
    }

    // Metod för att visa spelplanen
    void displayPlayer() const {
        std::cout << "   ";
        for (int i = 0; i < 15; i++)
        {
            if ( i >= 8 ) std::cout << i + 1 << " ";
            else std::cout << i + 1 << "  ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 15; ++i) 
        {
            std::cout << (char)(i + 65) << "  ";
            for (int j = 0; j < 15; ++j) 
            {
                if (grid[i][j] == Water) std::cout << "~  ";
                else if (grid[i][j] == Miss) std::cout << "O  ";
                else if (grid[i][j] == Hit) std::cout << "X  ";
                else if (grid[i][j] == Ship) std::cout << "#  ";
            }
            std::cout << std::endl;
        }
    }

    void displayOpponent() const {
        std::cout << "   ";
        for (int i = 0; i < 15; i++)
        {
            if ( i >= 8 ) std::cout << i + 1 << " ";
            else std::cout << i + 1 << "  ";
        }
        std::cout << std::endl;

        for (int i = 0; i < 15; ++i) 
        {
            std::cout << (char)(i + 65) << "  ";
            for (int j = 0; j < 15; ++j) 
            {
                if (grid[i][j] == Water) std::cout << "~  ";
                else if (grid[i][j] == Miss) std::cout << "O  ";
                else if (grid[i][j] == Hit) std::cout << "X  ";
                else if (grid[i][j] == Ship) std::cout << "~  ";
            }
            std::cout << std::endl;
        }
    }

    // Controls if position is inside the pacific ocean
    bool isValidPosition(int x, int y) const {
        return x >= 0 && x < 15 && y >= 0 && y < 15;
    }
    CellStatus grid[15][15];  // 15x15 Pacific ocean

};

// My little playground to test to sink ships
int main() {
    Board board;

    char aimX;
    int aimY;

    // Place a 3 tile ship
    board.placeShip(5, 7);
    board.placeShip(5, 8);
    board.placeShip(5, 9);

    // Place a 5 tile ship
    board.placeShip( 9, 3);
    board.placeShip(10, 3);
    board.placeShip(11, 3);
    board.placeShip(12, 3);
    board.placeShip(13, 3);
    do
    {
        // Print game display
        std::cout << "-==============-Opponents side-==============-" << std::endl;
        board.displayOpponent();
        std::cout << "-===============-Players side-===============-" << std::endl;
        board.displayPlayer();

        // Enter coordinates and fire!
        std::cout << "Aim: ";
        std::cin >> aimX;
        std::cin >> aimY;
        board.fireCannon((int)(aimX - 65), aimY - 1);
        // Clear the console before next round
        system("CLS");
        if (board.grid[(int)(aimX - 65)][aimY - 1] == Board::Hit) std::cout << "Hit!" << std::endl;
        else std::cout << "Miss!" << std::endl;

    } while (1);

    return 0;
}
