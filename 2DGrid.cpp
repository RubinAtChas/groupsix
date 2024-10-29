#include <iostream>
#include <ctime>
#include <string>
using namespace std;

class Matrix{
    public:
    enum CellStatus { Water, Miss, Hit, Ship };
    CellStatus grid[15][15];
};

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

void displayOceanPlayer(Matrix& matrix)
{
    cout << "-==================-Player-==================-" << endl;
    cout << " ";
    for (int i = 0; i < 15; i++)
    {
        if ( i >= 9 ) cout << " " << i + 1;
        else cout << "  " << i + 1;
    }
    cout << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << (char)(i + 65);
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

void displayOceanOpponent(Matrix& matrix)
{
    cout << "-=================-Opponent-=================-" << endl;
    cout << " ";
    for (int i = 0; i < 15; i++)
    {
        if ( i >= 9 ) cout << " " << i + 1;
        else cout << "  " << i + 1;
    }
    cout << endl;
    for (int i = 0; i < 15; i++)
    {
        cout << (char)(i + 65);
        for (int j = 0; j < 15; j++)
        {
            matrix.grid[i][j] = Matrix::Water;
            if (matrix.grid[i][j] == Matrix::Water) cout << "  ~";  // DET ÄR BARA VATTEN!
            if (matrix.grid[i][j] == Matrix::Hit) cout << "  X";    // DET ÄR TRÄFF!
            if (matrix.grid[i][j] == Matrix::Miss) cout << "  0";   // DET ÄR MISS!
            if (matrix.grid[i][j] == Matrix::Ship) cout << "  ~";   // DET ÄR ETT SKEPP!
        }
        cout << endl;                                               // DET ÄR RADBRYTNING!
    }
}

int main()
{
    Matrix ocean;
    intOcean(ocean);
    displayOceanOpponent(ocean);
    displayOceanPlayer(ocean);
    return 0;
}