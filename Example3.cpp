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
            matrix.grid[i][j] = Matrix::Water;
            if (matrix.grid[i][j] == Matrix::Water) cout << "  ~";  // DET ÄR BARA VATTEN!
            if (matrix.grid[i][j] == Matrix::Hit) cout << "  X";    // DET ÄR TRÄFF!
            if (matrix.grid[i][j] == Matrix::Miss) cout << "  0";   // DET ÄR MISS!
            if (matrix.grid[i][j] == Matrix::Ship) cout << "  #";   // DET ÄR ETT SKEPP!
        }
        cout << endl;                                               // DET ÄR RADBRYTNING!
    }

}
void placeShip()
{
    
}


int main()
{
    Matrix ocean;
    intOcean(ocean);
    displayOcean(ocean);
    return 0;
}