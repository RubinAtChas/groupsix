#include <iostream>
#include <ctime>
#include <string>
#include <vector>
using namespace std;
class Matrix
{
public:
    enum CellStatus
    {
        Water,
        Miss,
        Hit,
        Ship
    };
    static const int xRow = 15;
    static const int yRow = 15;
    int grid[xRow][yRow];
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
    else
    {
        buildShip(ships, size, arrayIndex, matrix);
    }
}
void intOcean(Matrix &matrix) // VATTEN GRID
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            matrix.grid[i][j] = Matrix::Water;
        }
    }
}
// bool isplayer is unused but is for implementation of name and who is the player
void displayOceanPlayer(Matrix &matrix, bool isPlayer) // SPELARENS SPELPLAN
{
    cout << "-==================-Player-==================-" << endl;
    cout << " ";
    for (int i = 0; i < 15; i++)
    {
        if (i >= 9)
            cout << " " << i + 1;
        else
            cout << "  " << i + 1;
    }
    cout << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << (char)(i + 65);
        for (int j = 0; j < 15; j++)
        {
            if (matrix.grid[i][j] == Matrix::Water)
                cout << "  ~"; // DET ÄR BARA VATTEN!
            if (matrix.grid[i][j] == Matrix::Hit)
                cout << "  X"; // DET ÄR TRÄFF!
            if (matrix.grid[i][j] == Matrix::Miss)
                cout << "  0"; // DET ÄR MISS!
            if (matrix.grid[i][j] == Matrix::Ship)
                cout << "  #"; // DET ÄR ETT SKEPP!
        }
        cout << endl; // DET ÄR RADBRYTNING!
    }
}
vector<Ship> initializeShips()
{
    vector<Ship> ships =
        {
            // Name : ID : Size : IsSinked
            {"Ship1", 0, 2, 0},
            {"Ship2", 1, 3, 0},
            {"Ship3", 2, 3, 0},
            {"Ship4", 3, 4, 0},
            {"Ship5", 4, 5, 0},
        };
        return ships;
}



void playerPlaceShips(vector<Ship>& ships, Matrix &playerOcean)
{
    string sysMessage;
    sysMessage = "Enter coordinats and direction to place (E = East, S = South)";
    for (int i = 4; i >= 0; i--)
    {
        cout << "Place your " << ships[i].name << ": ";
        buildShip(ships, ships[i].size, ships[i].shipId ,playerOcean);
    }
}

void SwitchTurn(int &playerTurn, Matrix(&oceans)[2])
{
    playerTurn = !playerTurn; 

    int currentPlayerIndex;
    if (playerTurn) {
        currentPlayerIndex = 1; // Player 1's turn
    } else {
        currentPlayerIndex = 0; // Player 0's turn
    }
    displayOceanPlayer(oceans[currentPlayerIndex], false);
    displayOceanPlayer(oceans[1 - currentPlayerIndex], true);
}

int main()
{
    Matrix ocean[2]; // Keeps track of oceans for two players
    // Initiliazes oceans
    intOcean(ocean[0]);
    intOcean(ocean[1]);

    int playerTurn; // switches between player 0 and player 1
    SwitchTurn(playerTurn, ocean);

    // initiliazes ship size and their IDS
    vector<Ship> ships[2];
    ships[0] = initializeShips(); 
    ships[1] = initializeShips();

    // Lets players place their ships and build their ships
    playerPlaceShips(ships[0], ocean[0]);
    playerPlaceShips(ships[1], ocean[1]);


    return 0;
}
