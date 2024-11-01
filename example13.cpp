#include <iostream>
#include <ctime>
#include <string>
#include <vector>
#include <cstdlib>
#include <limits>
#include <utility>
using namespace std;
string sysMessage;
class Matrix
{
public:
    string player;
    enum CellStatus { Water, Miss, Hit, Ship };
    CellStatus grid[15][15];
};
class Ship
{
public:
    string name;
    int shipId;
    int size;
    bool isSunk;
    vector<int> positionX;
    vector<int> positionY;
    int hits;
    Ship(const string& name, int id, int size, bool isSunk = false)
        : name(name), shipId(id), size(size), isSunk(isSunk),
          positionX(size), positionY(size){} // Initierar positionerna till storleken
};
void displayOceanOpponent(Matrix &matrix);
void displayOceanPlayer(Matrix &matrix);
void gameGraphics(Matrix &playerOcean, Matrix &opponentOcean);
bool isvalid(int x, int y);
void buildShip(vector<Ship>& ships, int size, int arrayIndex, Matrix &matrix);
void intOcean(Matrix &matrix);
void playerPlaceShips(vector<Ship>& ships,Matrix &playerOcean, Matrix &opponentOcean);
void attack(Matrix &playerOcean, Matrix &opponentOcean);
void switchPlayers();
void pressEnter();
void rapidFireCanon(Matrix& playerOcean, Matrix &opponentOcean, Ship &opponentShips);
void gameRound(Matrix &playerOcean, Matrix &opponentOcean, Ship &playerShips, Ship &opponentShips);
void firstAid(Matrix &playerOcean,Matrix &opponentOcean);
void missile(Matrix &playerOcean,Matrix &opponentOcean);
void sunkenShip(Ship &ship);
void checkWinCondition(const vector<Ship>& opponentShips, const string &playerName);

bool isvalid(int x, int y) // checks if an input is valid
{
    if (x >= 0 && x < 15 && y >= 0 && y < 15)
    {
        return true;
    }
    else
        return false;
}
void buildShip(vector<Ship>& ships, int size, int arrayIndex, Matrix &matrix) // used for placing ships onto the gridm, where ships are taken from the function Ships
{
    char placeShipX;
    int placeShipY;
    char direction;
    cin >> placeShipX;
    cin >> placeShipY;
    cin >> direction;
    int convertedX = (int)(placeShipX - 65);
    int convertedY = placeShipY - 1;
    if (direction == 'E' && isvalid(convertedX, convertedY + size - 1))
    {
        for (int i = 0; i < size; i++)
        {
            matrix.grid[convertedX][convertedY + i] = Matrix::Ship;
            ships[arrayIndex].positionX[i] = convertedX;
            ships[arrayIndex].positionY[i] = convertedY + i;
        }
    }
    else if (direction == 'S' && isvalid(convertedX + size - 1, convertedY))
    {
        for (int i = 0; i < size; i++)
        {
            matrix.grid[convertedX + i][convertedY] = Matrix::Ship;
            ships[arrayIndex].positionX[i] = convertedX + i;
            ships[arrayIndex].positionY[i] = convertedY;
        }
    }
}
void intOcean(Matrix &matrix) // initiliazes the grid that will be played on
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            matrix.grid[i][j] = Matrix::Water;
        }
    }
}
void displayOcean(Matrix &matrix, bool showShips) // displays the grid that is played on
{
    cout << "-================-" << matrix.player << "-================-" << endl;
    cout << " ";
    for (int i = 0; i < 15; i++) {
        if (i >= 9) cout << " " << i + 1;
        else cout << "  " << i + 1;
    }
    cout << endl;
    for (int i = 0; i < 15; i++) {
        cout << (char)(i + 65);
        for (int j = 0; j < 15; j++) {
            if (matrix.grid[i][j] == Matrix::Water) cout << "  ~"; // Water
            if (matrix.grid[i][j] == Matrix::Hit) cout << "  X";   // Hit
            if (matrix.grid[i][j] == Matrix::Miss) cout << "  0";  // Miss
            if (matrix.grid[i][j] == Matrix::Ship) {
                if (showShips) cout << "  #"; // Show own ships if true
                else cout << "  ~";           // Hide opponent's ships
            }
        }
        cout << endl; // Line break
    }
}
vector<Ship> initializeShips() // initiliazes a dynamic array that generates all the ships for the game
{
    vector<Ship> ships =
        {
            // Shipname, ShipID, Shipsize, IsSunk
            {"Destroyer", 0, 2, 0},
            {"Submarine", 1, 3, 0},
            {"Cruiser", 2, 3, 0},
            {"Battleship", 3, 4, 0},
            {"Titanic", 4, 5, 0},
        };
        return ships;
}
void attack(Matrix &playerOcean,Matrix &opponentOcean,vector<Ship>& opponentShips)
{
    sysMessage = "Enter coordinates to attack.";
    char inputX;
    int inputY;
    int failSafe = 0;
    do
    {
        failSafe = 0;
        gameGraphics(playerOcean, opponentOcean);
        cout << "Aim: ";
        cin >> inputX;
        cin >> inputY;
        int convertedX = (int)(inputX - 65);
        int convertedY = inputY - 1;
        if (isvalid(convertedX, convertedY))
        {
            if (opponentOcean.grid[convertedX][convertedY] == Matrix::Water)
            {
                opponentOcean.grid[convertedX][convertedY] = Matrix::Miss;
                sysMessage = "Your shot was a Miss!";
            }
            if (opponentOcean.grid[convertedX][convertedY] == Matrix::Ship)
            {
                opponentOcean.grid[convertedX][convertedY] = Matrix::Hit;
                // sysMessage = "You hit one of your opponents ships!";
                for (int i = 0; i < opponentShips.size(); i++)
                {
                    Ship& ship = opponentShips[i];
                    bool isHit = false;

                    // loops through position of ships
                    for(int x = 0; x < ship.positionX.size(); x++)
                    {
                        if(ship.positionX[x] == convertedX && ship.positionY[x] == convertedY)
                        {
                            ship.hits += 1;
                            isHit = true;
                            if (ship.hits >= ship.size){sysMessage = "The ship has been sunk!";} 
                            else {sysMessage = "You hit one of your opponents ships!";}
                            isHit = true;
                            break; // exits the innermost loop
                        }
                    }
                    if(isHit == true)
                    {
                        sunkenShip(ship);
                        break;
                    }
                }
            }
        }
        else
        {
            sysMessage = "Invalid coordinates, please try again.\n"
                "Enter coordinates to attack.";
            failSafe = 1;
        }
    } while (failSafe);
    gameGraphics(playerOcean, opponentOcean);
    pressEnter();
}
void gameGraphics(Matrix &playerOcean, Matrix &opponentOcean) // Calls on DisplayOcean to make the graphical part of the game
{
    system("CLS");
    displayOcean(opponentOcean, false); // Show opponent's ocean (hide ships)
    displayOcean(playerOcean, true);     // Show player's ocean (show ships)
    cout << sysMessage << endl;
}
void playerPlaceShips(vector<Ship>& ships,Matrix &playerOcean, Matrix &opponentOcean)
{
    sysMessage = "Enter coordinats and direction to place (E = East, S = South)";
    for (int i = 4; i >= 0; i--)
    {
        gameGraphics(playerOcean, opponentOcean);
        cout << "Place your " << ships[i].name << ": ";
        buildShip(ships, ships[i].size, ships[i].shipId ,playerOcean);
    }
    sysMessage = "All ships are placed.";
    gameGraphics(playerOcean, opponentOcean);
    pressEnter();
}
void switchPlayers()
{
    system("CLS");
    cout << "Next player coming up, previous player look away." << endl;
    pressEnter();
}
void pressEnter()
{
    cout << "Press ENTER to continue...";
    // Loopar tills användaren trycker exakt ENTER
    while (true) {
        cin.clear(); // Återställ inmatningsströmmen om det finns fel
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Rensa bufferten
        if (cin.get() == '\n') {
            break; // Om användaren trycker exakt ENTER, bryter vi loopen
        } else {
            cout << "Please press only ENTER to continue...\n"; // Uppmanar att bara trycka ENTER
        }
    }
}
void rapidFireCanon(Matrix& playerOcean, Matrix &opponentOcean) // Fires attacks that randomly target the Grid
{
    gameGraphics(playerOcean, opponentOcean);
    cout << "Rapid fire Canon Activated, shoots at random coordinates" << endl;
    srand(time(0));
    for (int i = 0; i < 4; i++)
    {
        int x = rand() % 14;
        int y = rand() % 14;
        if (opponentOcean.grid[x][y]==Matrix::Water)
        {
            opponentOcean.grid[x][y] = Matrix::Miss;
        }
        else if(opponentOcean.grid[x][y]== Matrix::Ship)
        {
            opponentOcean.grid[x][y] = Matrix::Hit;
            cout << "\a";                                         // Ljud tillägg
        }
    }
    gameGraphics(playerOcean, opponentOcean);
    pressEnter();
}
void gameRound(Matrix &playerOcean, Matrix &opponentOcean, vector<Ship>& opponentShips) {
    int action;
    sysMessage = "Choose your action.";
    do {
        gameGraphics(playerOcean, opponentOcean);
        cout << "1. Normal attack.\n"
             << "2. Rapid fire.\n"
             << "3. Missile\n"
             << "4. Repair kit.\n"
             << "Your choice: ";
        // Check if the input is valid
        while (!(cin >> action) || action < 1 || action > 4) {
            sysMessage = "Invalid input, plea1se try again.";
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            action = 0; // Reset action to prompt again
            gameGraphics(playerOcean, opponentOcean); // Refresh graphics after invalid input
            cout << "1. Normal attack.\n"
                 << "2. Rapid fire.\n"
                 << "3. Missile\n"
                 << "4. Repair kit.\n"
                 << "Your choice: ";
        }
        switch (action) {
            case 1:
                attack(playerOcean, opponentOcean, opponentShips );
                break;
            case 2:
                rapidFireCanon(playerOcean, opponentOcean);
                break;
            case 3:
                missile(playerOcean, opponentOcean);
                break;
            case 4:
                firstAid(playerOcean, opponentOcean);
                break;
        }
        checkWinCondition(opponentShips, playerOcean.player);
    } while (action < 1 || action > 4); // Loop until a valid action is chosen
    swap(playerOcean, opponentOcean);
    switchPlayers();
}
void firstAid(Matrix &playerOcean,Matrix &opponentOcean)
{
    gameGraphics(playerOcean, opponentOcean);
    char x;
    int y;
    cout << "Aim for the cordinate you want to aid: " << endl;
    cin >> x;
    cin >> y;
    int convertedX = (int(x - 'A'));
    int convertedY = y - 1;
    playerOcean.grid[convertedX][convertedY] = Matrix::Ship;
    gameGraphics(playerOcean, opponentOcean);
    cout << "Successfully healed the position!" << endl;
}
void missile(Matrix &playerOcean,Matrix &opponentOcean)
{
    sysMessage =+ "Enter a coordinate to attack with the missile.";
    char inputX;
    int inputY;
    int failSafe = 0;
    do
    {
        gameGraphics(playerOcean, opponentOcean);
        cout << "Aim: ";
        cin >> inputX;
        cin >> inputY;
        int convertedX = (int)(inputX - 65);
        int convertedY = inputY - 1;
        for (int i = 0; i < 3; i++)
        {
        for (int j = 0; j < 3; j++)
        {
            int targetX = convertedX + i;
            int targetY = convertedY + j;
            if (isvalid(targetX, targetY)) {
            if (opponentOcean.grid[targetX][targetY] == Matrix::Water)
            {
                opponentOcean.grid[targetX][targetY] = Matrix::Miss;
            } else if (opponentOcean.grid[targetX][targetY] == Matrix::Ship)
                    {
                        opponentOcean.grid[targetX][targetY] = Matrix::Hit;
                    }
                }
            }
        }
    } while (failSafe);
    gameGraphics(playerOcean, opponentOcean);
    pressEnter();
}
void MakeAname(Matrix ocean[]) // Makes a name for the players
{
    cout << "Enter player 1 name: ";
    cin >> ocean[0].player;
    cout << "Enter player 2 name: ";
    cin >> ocean[1].player;
}

void sunkenShip(Ship &ship)
{
    if (ship.hits >= ship.size)
    {
        sysMessage = "The ", ship.name, " has been sunk!";
        ship.isSunk = true;
    }
} 

void checkWinCondition(const vector<Ship>& opponentShips, const string &playerName) {
    // Check if all ships are sunk
    for (const Ship& ship : opponentShips) 
    {
        if (ship.isSunk == false) 
    	{
            return; // At least one ship is still afloat
    	}
    }
    
    // If we reach here, all ships are sunk
    printf("%s has won!\n", playerName.c_str());
}

int main()
{
    Matrix ocean[2];
    intOcean(ocean[0]);
    intOcean(ocean[1]);
    vector<Ship> playerShips = initializeShips(); // Initialize Player 1 ships
    vector<Ship> opponentShips = initializeShips(); // Initialize Player 2 ships
    MakeAname(ocean);
    switchPlayers();
    playerPlaceShips(playerShips, ocean[0], ocean[1]);
    switchPlayers();
    playerPlaceShips(opponentShips, ocean[1], ocean[0]);
    switchPlayers(); 
    do
    {
        gameRound(ocean[0], ocean[1], opponentShips);
    } while (1);
    return 0;
}
