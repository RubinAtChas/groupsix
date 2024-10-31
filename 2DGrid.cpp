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

    Ship(const string& name, int id, int size, bool isSunk = false)
        : name(name), shipId(id), size(size), isSunk(isSunk),
          positionX(size), positionY(size) {} // Initierar positionerna till storleken
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

bool isvalid(int x, int y)
{
    if (x >= 0 && x < 15 && y >= 0 && y < 15)
    {
        return true;
    }
    else
        return false;
}
void buildShip(vector<Ship>& ships, int size, int arrayIndex, Matrix &matrix)
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
void intOcean(Matrix &matrix)
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            matrix.grid[i][j] = Matrix::Water;
        }
    }
}
void displayOceanPlayer(Matrix &matrix)
{
    cout << "-================-" << matrix.player << "-================-" << endl;
    cout << " ";
    for (int i = 0; i < 15; i++)
    {
        if (i >= 9) cout << " " << i + 1;
        else cout << "  " << i + 1;
    }
    cout << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << (char)(i + 65);
        for (int j = 0; j < 15; j++)
        {
            if (matrix.grid[i][j] == Matrix::Water) cout << "  ~"; // DET ÄR BARA VATTEN!
            if (matrix.grid[i][j] == Matrix::Hit) cout << "  X"; // DET ÄR TRÄFF!
            if (matrix.grid[i][j] == Matrix::Miss) cout << "  0"; // DET ÄR MISS!
            if (matrix.grid[i][j] == Matrix::Ship) cout << "  #"; // DET ÄR ETT SKEPP!
        }
        cout << endl; // DET ÄR RADBRYTNING!
    }
}
void displayOceanOpponent(Matrix &matrix)
{
    cout << "-================-" << matrix.player << "-================-" << endl;
    cout << " ";
    for (int i = 0; i < 15; i++)
    {
        if (i >= 9) cout << " " << i + 1;
        else cout << "  " << i + 1;
    }
    cout << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << (char)(i + 65);
        for (int j = 0; j < 15; j++)
        {
            if (matrix.grid[i][j] == Matrix::Water) cout << "  ~"; // DET ÄR BARA VATTEN!
            if (matrix.grid[i][j] == Matrix::Hit) cout << "  X"; // DET ÄR TRÄFF!
            if (matrix.grid[i][j] == Matrix::Miss) cout << "  0"; // DET ÄR MISS!
            if (matrix.grid[i][j] == Matrix::Ship) cout << "  ~"; // DET ÄR ETT SKEPP!
        }
        cout << endl; // DET ÄR RADBRYTNING!
    }
}
vector<Ship> initializeShips()
{
    vector<Ship> ships =
        {
            {"Destroyer", 0, 2, 0},
            {"Submarine", 1, 3, 0},
            {"Cruiser", 2, 3, 0},
            {"Battleship", 3, 4, 0},
            {"Carrier", 4, 5, 0},
        };
        return ships;
}

void attack(Matrix &playerOcean,Matrix &opponentOcean)
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
                sysMessage = "You hit one of your opponents ships!";
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

void gameGraphics(Matrix &playerOcean, Matrix &opponentOcean)
{
    system("CLS");
    displayOceanOpponent(opponentOcean);
    displayOceanPlayer(playerOcean);
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

void rapidFireCanon(Matrix& playerOcean, Matrix &opponentOcean)
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

void gameRound(Matrix &playerOcean, Matrix &opponentOcean)
{
    int action;
    sysMessage = "Choose your action.";
    do
    {
        gameGraphics(playerOcean, opponentOcean);
        cout << "1. Normal attack.\n"
            "2. Rapid fire.\n"
            "3. Missile\n"
            "4. Repaird kit.\n"
            "Your choice: ";
        cin >> action;
        switch (action)
        {
        case 1:
            attack(playerOcean, opponentOcean);
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
        default:
            sysMessage = "Invalid input, please try again.";
            break;
        }
    } while (action < 1 || action > 4);
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

int main()
{
    Matrix ocean[2];
    intOcean(ocean[0]);
    intOcean(ocean[1]);
    vector<Ship> playerShips = initializeShips(); // Initialize Player 1 ships
    vector<Ship> opponentShips = initializeShips(); // Initialize Player 2 ships
    cout << "Enter player 1 name: ";
    cin >> ocean[0].player;
    cout << "Enter player 2 name: ";
    cin >> ocean[1].player;

    //switchPlayers();
    //playerPlaceShips(playerShips, ocean[0], ocean[1]);
    //switchPlayers();
    //playerPlaceShips(opponentShips, ocean[1], ocean[0]);
    //switchPlayers();
    do
    {
        gameRound(ocean[0], ocean[1]);
    } while (1);

    return 0;
}
