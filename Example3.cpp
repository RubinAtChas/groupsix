#include <iostream>
#include <ctime>
#include <string>
using namespace std;
class Matrix{
    public:
    enum CellStatus { Water, Miss, Hit, Ship };
    static const int xRow = 15;
    static const int yRow = 15;
    int grid[xRow][yRow];
};
/* the & changes the array from a value type to a reference type.
this means instead of creating a copy we are referencing the original.
This is so that the value is consistent throughout the runtime of the program. */
void intOcean(Matrix& matrix)
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            matrix.grid[i][j] = Matrix::Water;
        }
    }
}
void displayOcean(Matrix& matrix)
{
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (matrix.grid[i][j] == Matrix::Water) cout << "  ~";  // DET ÄR BARA VATTEN!
            if (matrix.grid[i][j] == Matrix::Hit) cout << "  X";    // DET ÄR TRÄFF!
            if (matrix.grid[i][j] == Matrix::Miss) cout << "  0";   // DET ÄR MISS!
            if (matrix.grid[i][j] == Matrix::Ship) cout << "  #";   // DET ÄR ETT SKEPP!
        }
        cout << endl;                                               // DET ÄR RADBRYTNING!
    }

}
void buildShip()
{
    int placeShipX, placeShipY;
    int ships;
    int ship1, ship2, ship3, ship4, ship5;
    if(ship1 == 1)
    {
        for(int i = 0; i < 2; i++)
        {
            cout << "Place a" << i << "tile ship:";
            cin >> placeShipX, placeShipY;
        }
    }
}

bool isvalid(int x, int y)
{
    if(x >= 0 && x < 15 && y >= 0 && y < 15) { return true; }
    else return false;
}

void placeShip(int shipsize, Matrix& matrix)
{
    // need 5 ships;
    int placeShipX, placeShipY;
        for(int i = 0; i < shipsize; i++)
        {
            cout << "Place a " << i << "tile ship:";
            // cin >> placeShipX, placeShipY;
            cin >> placeShipX;
            cin >> placeShipY;
            isvalid(placeShipX, placeShipY);
            matrix.grid[placeShipX][placeShipY] = Matrix::Ship;
        }
}


int main()
{
    Matrix ocean;
    int tile;
    intOcean(ocean);
    displayOcean(ocean);
    placeShip(3, ocean);
    /* placeShip(3, ocean);
    placeShip(3, ocean);
    placeShip(4, ocean);
    placeShip(5, ocean); */
    displayOcean(ocean);
    return 0;
}