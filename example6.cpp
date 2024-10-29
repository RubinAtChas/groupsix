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
void buildShip(int size, Matrix &matrix)
{
    // need 5 ships;
    char placeShipX;
    int placeShipY;
    char direction;
    cin >> placeShipX;
    cin >> placeShipY;
    cin >> direction;
    if (direction == 'E')
    {
        for (int i = placeShipY; i < placeShipY + size; i++)
        {
            matrix.grid[placeShipX - 65][i - 1] = Matrix::Ship;
        }
    }
    else if (direction == 'S')
    {
        for (int i = placeShipX; i < placeShipX + size; i++)
        {
            matrix.grid[i - 65][placeShipY - 1] = Matrix::Ship;
        }
    }
    isvalid(placeShipX, placeShipY);
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
void displayOceanOpponent(Matrix &matrix)
{
    cout << "-=================-Opponent-=================-" << endl;
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
                cout << "  ~"; // DET ÄR ETT SKEPP!
        }
        cout << endl; // DET ÄR RADBRYTNING!
    }
}
vector<Ship> initializeShips()
{
    vector<Ship> ships =
        {
            {"Ship1", 1, 2, 0},
            {"Ship2", 2, 3, 0},
            {"Ship3", 3, 3, 0},
            {"Ship4", 4, 4, 0},
            {"Ship5", 5, 5, 0},
        };
        return ships;
}
int main()
{
    Matrix ocean;
    intOcean(ocean);
    displayOceanOpponent(ocean);
    displayOceanPlayer(ocean);
    displayOceanOpponent(ocean);
    displayOceanPlayer(ocean);
    vector<Ship> ships = initializeShips(); // check if this logic is correct 
    return 0;
}