#include <iostream>
#include <math.h>
#include <windows.h>
#include <fstream>
#include <string>
#include <sstream>
static int size=0;
using namespace std;
class ChessBoard;
class Queen;
class Knight;
class ChessPiece
{
	protected:
	string name;
	string color;
	char symbol;
	int prevturn;

public:
	ChessPiece()
	{
		color = "white";
	}
	ChessPiece(string nm, string clr, char sym, int prev)
	{
		name = nm;
		color = clr;
		symbol = sym;
		prevturn = prev;
	}
	void set_name(string nm)
	{
		name = nm;
	}
	void set_color(string clr)
	{
		color = clr;
	}
	void set_symbol(char sym)
	{
		symbol = sym;
	}
	string get_name()
	{
		return name;
	}
	string get_color()
	{
		return color;
	}
	char get_symbol()
	{
		return symbol;
	}

public:
	virtual bool isValidMove(string source, string destination, ChessPiece *grid[8][8])
	{
		cout << "\nVirtual\n";
	}
	virtual bool PawnPromotion(int source_x, int source_y, int dest_x, int dest_y, string source, string dest, ChessPiece *grid[8][8]) {}
};
class EmptySpace : public ChessPiece
{
public:
	EmptySpace(string nm, string clr, char sym, int prev) : ChessPiece(nm, clr, sym, prev)
	{
	}
};
class Queen : public ChessPiece
{
public:
	Queen(string nm, string clr, char sym, int prev) : ChessPiece(nm, clr, sym, prev)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[8][8]) override
	{
//		cout << "\nQUEEN MOVED\n";
		int source_x = source[0] - 'a';
		int source_y = '8' - source[1];
		int dest_x = destination[0] - 'a';
		int dest_y = '8' - destination[1];
//		cout << "Source coordinates: (" << source_x << ", " << source_y << ")" << endl;
//		cout << "Destination coordinates: (" << dest_x << ", " << dest_y << ")" << endl;
		if (source[0] == destination[0] || source[1] == destination[1] || abs(dest_x - source_x) == abs(dest_y - source_y))
		{
//			cout << "Destination is reachable along a column, row, or diagonal" << endl;
			int dx = (dest_x > source_x) ? 1 : ((dest_x < source_x) ? -1 : 0);
			int dy = (dest_y > source_y) ? 1 : ((dest_y < source_y) ? -1 : 0);

			int x = source_x + dx;
			int y = source_y + dy;

			while (x != dest_x || y != dest_y)
			{
//				cout << "Checking position (" << x << ", " << y << ")" << endl;
				if (x < 0 || x >= 8 || y < 0 || y >= 8)
				{
//					cout << "Out of bounds!" << endl;
					return false;
				}

				if (grid[y][x]->get_symbol() != '-')
				{
					cout << "Piece found " << endl;
					cout << grid[y + 1][x]->get_symbol() << endl;
					cout << grid[3][2]->get_symbol() << endl;
					return false;
				}
				x += dx;
				y += dy;
			}
			return true;
		}
		else
		{
//			cout << "Move is not valid for the Queen" << endl;
			return false;
		}
		//	return true;
	}
};
class Rook : public ChessPiece
{
public:
	Rook(string nm, string clr, char sym, int prev) : ChessPiece(nm, clr, sym, prev)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[8][8])
	{
//		cout << "\nROOK MOVED\n";
	    int source_x = source[0] - 'a';
	    int source_y = '8' - source[1];
	    int dest_x = destination[0] - 'a';
	    int dest_y = '8' - destination[1];
//	    cout << "Source coordinates: (" << source_x << ", " << source_y << ")" << endl;
//	    cout << "Destination coordinates: (" << dest_x << ", " << dest_y << ")" << endl;
	    if (source_x == dest_x || source_y == dest_y)//to ensure it's moving either vertical or horizontal
		{
	        int dx = (dest_x > source_x) ? 1 : ((dest_x < source_x) ? -1 : 0);
	        int dy = (dest_y > source_y) ? 1 : ((dest_y < source_y) ? -1 : 0);
	
	        //checking each square along the path
	        int x = source_x + dx;
	        int y = source_y + dy;
	        while (x != dest_x || y != dest_y)
	        {
	            if (grid[y][x]->get_symbol() != '-')
	            {
//	                cout << "Piece found " << endl;
	                return false;
	            }
	            x += dx;
	            y += dy;
	        }
	        return true;
	    }
	
//	    cout << "Move is not valid for the Rook" << endl;
	    return false;
	}
};
class King : public ChessPiece
{
public:
	King(string nm, string clr, char sym, int prev) : ChessPiece(nm, clr, sym, prev)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[8][8])
	{
//		cout << "\nKING MOVED\n";
	    int source_x = source[0] - 'a';
	    int source_y = '8' - source[1];
	    int dest_x = destination[0] - 'a';
	    int dest_y = '8' - destination[1];
//	    cout << "Source coordinates: (" << source_x << ", " << source_y << ")" << endl;
//	    cout << "Destination coordinates: (" << dest_x << ", " << dest_y << ")" << endl;
	
	    // Check if the destination is within one square horizontally, vertically, or diagonally
	    if (abs(dest_x - source_x) <= 1 && abs(dest_y - source_y) <= 1)
	    {
	        // Check if the destination is empty or has an opponent's piece
	        if (grid[dest_y][dest_x]->get_symbol() == '-' || grid[dest_y][dest_x]->get_color() != grid[source_y][source_x]->get_color())
	        {
//				cout<<"King move"<<endl;
	            return true;
	        }
	    }
	    else if(abs(source_x - dest_x) == 2){
			return castling(grid, source_x, source_y, dest_x, dest_y, prevturn);
		}
		
//		cout << "Move is not valid for the King" << endl;
		return false;
	}
	bool castling(ChessPiece *grid[8][8], int source_x, int source_y, int dest_x, int dest_y, int prev)
    {
	    // Check if the king is moving two squares horizontally
//	    cout << "\n\nI AM HERE\n\n";
	    if (abs(dest_x - source_x) == 2)
	    {
	        // Check if the king is in its initial position
	        if (source_x != 4)
	        {
	            return false; // King is not in its initial position
	        }
	
	        // Check if there are no pieces between the king and rook
	        int rook_x = (dest_x > source_x) ? 7 : 0;
	        int rook_y = (source_y == 7) ? 7 : 0;
	        //either 0,0 or 7,7
	        for (int i = min(source_x, rook_x) + 1; i < max(source_x, rook_x); ++i)
	        {
	            if (grid[source_y][i]->get_symbol() != '-')
	            {
	                return false; // There is a piece between the king and rook
	            }
	        }
	
	        // Check if the rook is in its initial position
	        if (grid[rook_y][rook_x]->get_symbol() != 'R' && grid[rook_y][rook_x]->get_symbol() != 'r')
	        {
	            return false; // Rook is not in its initial position
	        }
	
	        // Move the rook
	        char temp = grid[rook_y][rook_x]->get_symbol();
	        if(temp == 'R'){
	        	if (dest_x > source_x)//king side castling
		        {
		            grid[rook_y][rook_x] = new EmptySpace(" ", " ", '-', prev);
		            grid[rook_y][rook_x - 2] = new Rook("Rook", "black", 'R', prev);
		        }
		        else//queen side castling
		        {
		            grid[rook_y][rook_x] = new EmptySpace(" ", " ", '-', prev);
		            grid[rook_y][rook_x + 3] = new Rook("Rook", "black", 'R', prev);
		        }
			}
			else{
				if (dest_x > source_x)//king side castling
		        {
		            grid[rook_y][rook_x] = new EmptySpace(" ", " ", '-', prev);
		            grid[rook_y][rook_x - 2] = new Rook("Rook", "white", 'r', prev);
		        }
		        else//queen side castling
		        {
		            grid[rook_y][rook_x] = new EmptySpace(" ", " ", '-', prev);
		            grid[rook_y][rook_x + 3] = new Rook("Rook", "white", 'r', prev);
		        }
			}
	
	        return true; // Castling successful
	    }
	    return false; // Invalid castling move
	}
};

class Bishop : public ChessPiece
{
public:
	Bishop(string nm, string clr, char sym, int prev) : ChessPiece(nm, clr, sym, prev)
	{
	}

	bool isValidMove(string source, string destination, ChessPiece *grid[8][8]) override
	{
//		cout << "\nBISHOP MOVED\n";
		int source_x = source[0] - 'a';
		int source_y = '8' - source[1];
		int dest_x = destination[0] - 'a';
		int dest_y = '8' - destination[1];
//		cout << "Source coordinates: (" << source_x << ", " << source_y << ")" << endl;
//		cout << "Destination coordinates: (" << dest_x << ", " << dest_y << ")" << endl;
		if (abs(dest_x - source_x) == abs(dest_y - source_y))
		{
//			cout << "Destination is reachable along a column, row, or diagonal" << endl;
			int dx = (dest_x > source_x) ? 1 : ((dest_x < source_x) ? -1 : 0);
			int dy = (dest_y > source_y) ? 1 : ((dest_y < source_y) ? -1 : 0);

			int x = source_x + dx;
			int y = source_y + dy;

			while (x != dest_x || y != dest_y)
			{
//				cout << "Checking position (" << x << ", " << y << ")" << endl;
				if (x < 0 || x >= 8 || y < 0 || y >= 8)
				{
//					cout << "Out of bounds!" << endl;
					return false;
				}
				if (grid[y][x]->get_symbol() != '-')
				{
//					cout << "Piece found " << endl;
					cout << grid[y][x]->get_symbol() << endl;
					return false;
				}
				x += dx;
				y += dy;
			}
			return true;
		}
		else
		{
//			cout << "Move is not valid for the Bishop" << endl;
			return false;
		}
		//	return true;
	}
};
class Knight : public ChessPiece
{
public:
	Knight(string nm, string clr, char sym, int prev) : ChessPiece(nm, clr, sym, prev)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[8][8]) override
	{
//		cout << "\nKNIGHT MOVED\n";
		if (source[0] - destination[0] == 1 || source[0] - destination[0] == -1)
		{
			if (source[1] - destination[1] == 2 || source[1] - destination[1] == -2)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else if (source[0] - destination[0] == 2 || source[0] - destination[0] == -2)
		{
			if (source[1] - destination[1] == 1 || source[1] - destination[1] == -1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
};


class Pawn : public ChessPiece
{
public:
	Pawn(string nm, string clr, char sym, int prev) : ChessPiece(nm, clr, sym, prev)
	{
	}
	bool PawnPromotion(int source_x, int source_y, int dest_x, int dest_y, string source, string dest, ChessPiece *grid[8][8])
	{
		char replacePawn;
//		cout << "Inside pawn promotion" << endl;

		if (grid[dest_x][dest_y]->get_symbol() == 'p')
		{
			if ((dest_x == 0))
			{
//				cout << "Enter the piece with which you want to replace white pawn: ";
				cin >> replacePawn;
				if (replacePawn == 'q' || replacePawn == 'n' || replacePawn == 'b' || replacePawn == 'r')
				{
					switch (replacePawn)
					{
					case 'r':
						grid[dest_x][dest_y] = new Rook("Rook", "black", 'r', 0);
						break;
					case 'q':
						grid[dest_x][dest_y] = new Rook("Queen", "black", 'q', 0);
						break;
					case 'n':
						grid[dest_x][dest_y] = new Rook("Knight", "black", 'n', 0);
						break;
					case 'b':
						grid[dest_x][dest_y] = new Rook("Bishop", "black", 'b', 0);
						break;
					}
					return true;
				}
				else
				{
					do
					{
						cout << "Enter the piece you want to replace white pawn with again: ";
						cin >> replacePawn;
						if (replacePawn == 'q' || replacePawn == 'n' || replacePawn == 'b' || replacePawn == 'r')
						{
							switch (replacePawn)
							{
							case 'r':
								grid[dest_x][dest_y] = new Rook("Rook", "black", 'r', 0);
								break;
							case 'q':
								grid[dest_x][dest_y] = new Rook("Queen", "black", 'q', 0);
								break;
							case 'n':
								grid[dest_x][dest_y] = new Rook("Knight", "black", 'n', 0);
								break;
							case 'b':
								grid[dest_x][dest_y] = new Rook("Bishop", "black", 'b', 0);
								break;
							}
							return true;
						}
					} while (replacePawn != 'q' || replacePawn != 'n' || replacePawn != 'b' || replacePawn != 'r');
				}
			}
		}
		else if (grid[dest_x][dest_y]->get_symbol() == 'P')
		{
			if ((dest_x == 7))
			{
				cout << "Enter the piece with which you want to replace black pawn: ";
				cin >> replacePawn;
				if (replacePawn == 'Q' || replacePawn == 'N' || replacePawn == 'B' || replacePawn == 'R')
				{
					switch (replacePawn)
					{
					case 'R':
						grid[dest_x][dest_y] = new Rook("Rook", "white", 'R', 0);
						break;
					case 'Q':
						grid[dest_x][dest_y] = new Rook("Queen", "white", 'Q', 0);
						break;
					case 'N':
						grid[dest_x][dest_y] = new Rook("Knight", "white", 'N', 0);
						break;
					case 'B':
						grid[dest_x][dest_y] = new Rook("Bishop", "white", 'B', 0);
						break;
					}
					return true;
				}
				else
				{
					do
					{
						cout << "Enter the piece you want to replace black pawn with again: ";
						cin >> replacePawn;
						if (replacePawn == 'Q' || replacePawn == 'N' || replacePawn == 'B' || replacePawn == 'R')
						{
							switch (replacePawn)
							{
							case 'R':
								grid[dest_x][dest_y] = new Rook("Rook", "white", 'R', 0);
								break;
							case 'Q':
								grid[dest_x][dest_y] = new Rook("Queen", "white", 'Q', 0);
								break;
							case 'N':
								grid[dest_x][dest_y] = new Rook("Knight", "white", 'N', 0);
								break;
							case 'B':
								grid[dest_x][dest_y] = new Rook("Bishop", "white", 'B', 0);
								break;
							}
							return true;
						}
					} while (replacePawn != 'Q' || replacePawn != 'N' || replacePawn != 'B' || replacePawn != 'R');
				}
			}
		}
		else
		{
			return false;
		}
	}

	bool isValidMove(string source, string destination, ChessPiece *grid[8][8])
	{
		int source_x = 8 - (source[1] - '0');
		int source_y = source[0] - 'a';
		int dest_x = 8 - (destination[1] - '0');
		int dest_y = destination[0] - 'a';

		bool checkPawnPromotion = false;
		bool checkEnPassant = false;

		if (grid[source_x][source_y]->get_symbol() == 'p')
		{
			int li = source_x;
			int lj = source_y;
			int mag = 1;
			if (source_x == 6)
				mag = 2;

			for (int i = 1; i <= mag; i++)
			{
				if (li - i >= 0)
				{
					if (li - i == dest_x && lj == dest_y)
					{
//						cout << source << "Pawn moved successfully to " << destination << endl;
						return true;
						break;
					}
					else if (grid[li - i][lj]->get_symbol() != '.')
					{
						break;
					}
				}
			}

			int dx[] = {-1, +1};
			int dy[] = {-1, -1};

			for (int i = 0; i < 2; i++)
			{
				if (li + dy[i] != dest_x || lj + dx[i] != dest_y)
					continue;

				if (li + dy[i] >= 0 && li + dy[i] < 8 && lj + dx[i] >= 0 && lj + dx[i] < 8)
				{
					if (grid[li + dy[i]][lj + dx[i]]->get_symbol() <= 'Z' && grid[li + dy[i]][lj + dx[i]]->get_symbol() >= 'A')
					{
//						cout << source << " Pawn moved successfully to " << destination << endl;
						return true;
					}
				}
			}

			return false;
		}
		else if (grid[source_x][source_y]->get_symbol() == 'P')
		{
			int li = source_x;
			int lj = source_y;
			int mag = 1;
			if (source_x == 1)
				mag = 2;

			for (int i = 1; i <= mag; i++)
			{
				if (li + i < 8)
				{
					if (li + i == dest_x && lj == dest_y)
					{
//						cout << source << " Pawn moved successfully to " << destination << endl;
						return true;
						break;
					}
					else if (grid[li + i][lj]->get_symbol() != '.')
					{
						break;
					}
				}
			}

			int dx[] = {-1, +1};
			int dy[] = {+1, +1};

			for (int i = 0; i < 2; i++)
			{
				if (li + dy[i] != dest_x || lj + dx[i] != dest_y)
					continue;

				if (li + dy[i] >= 0 && li + dy[i] < 8 && lj + dx[i] >= 0 && lj + dx[i] < 8)
				{
					if (grid[li + dy[i]][lj + dx[i]]->get_symbol() <= 'z' && grid[li + dy[i]][lj + dx[i]]->get_symbol() >= 'a')
					{
//						cout << source << "Pawn moved successfully to " << destination << endl;
						return true;
					}
				}
			}

			return false;
		}

		cout << "Invalid move" << endl;
		return false;
	}
};
class ChessBoard
{
	int n;
public:
	ChessPiece *grid[8][8]; // Declaration of grid as a 2D array of ChessPiece pointers
	char whitecaptured[16];
	char blackcaptured[16];
	int capturewhitecnt;
	int captureblackcnt;

	ChessBoard()
	{
		int capturewhitecnt = 0;
	    int captureblackcnt = 0;
		// Initialize the grid with nullptr
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				grid[i][j] = nullptr;
			}
		}
		grid[0][0] = new Rook("Rook", "black", 'R', 0);
		grid[0][1] = new Knight("Knight", "black", 'N', 0);
		grid[0][2] = new Bishop("Bishop", "black", 'B', 0);
		grid[0][3] = new Queen("Queen", "black", 'Q', 0);
		grid[0][4] = new King("King", "black", 'K', 0);
		grid[0][5] = new Bishop("Bishop", "black", 'B', 0);
		grid[0][6] = new Knight("Knight", "black", 'N', 0);
		grid[0][7] = new Rook("Rook", "black", 'R', 0);
		grid[7][0] = new Rook("Rook", "white", 'r', 0);
		grid[7][1] = new Knight("Knight", "white", 'n', 0);
		grid[7][2] = new Bishop("Bishop", "white", 'b', 0);
		grid[7][3] = new Queen("Queen", "white", 'q', 0);
		grid[7][4] = new King("King", "white", 'k', 0);
		grid[7][5] = new Bishop("Bishop", "white", 'b', 0);
		grid[7][6] = new Knight("Knight", "white", 'n', 0);
		grid[7][7] = new Rook("Rook", "white", 'r', 0);
		for (int i = 0; i < 8; i++)
		{
			grid[1][i] = new Pawn("Pawn", "black", 'P', 0);
		}
		for (int i = 0; i < 8; i++)
		{
			grid[6][i] = new Pawn("Pawn", "white", 'p', 0);
		}
		for (int i = 2; i < 6; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				grid[i][j] = new EmptySpace(" ", " ", '-', 0);
			}
		}
		for (int i = 0; i < 16; i++)
		{
			whitecaptured[i] = ' ';
			blackcaptured[i] = ' ';
		}
	}
	ChessBoard(string moves, int &size, string &correctmoves)
    {
        for (int i = 0; i < 8; ++i)
        {
            for (int j = 0; j < 8; ++j)
            {
                grid[i][j] = new EmptySpace(" ", " ", '-', 0);
            }
        }
        int row = 0;
        int col = 0;
        for (int i = 0; i < moves.length(); i++)
        {
            if (moves[i] == ' ')
            {
                break;
            }
            else if (moves[i] == '/')
            {
                row++;
                col = 0;
            }
            else if (isdigit(moves[i]))
            {
                col = col + (moves[i] - '0');
            }
            else if (isalpha(moves[i]))
            {
                char c = moves[i];
                switch (c)
                {
                case 'P':
                    grid[row][col] = new Pawn("Pawn", "white", 'P', 0);
                    break;
                case 'p':
                    grid[row][col] = new Pawn("Pawn", "black", 'p', 0);
                    break;
                case 'R':
                    grid[row][col] = new Rook("Rook", "white", 'R', 0);
                    break;
                case 'r':
                    grid[row][col] = new Rook("Rook", "black", 'r', 0);
                    break;
                case 'Q':
                    grid[row][col] = new Rook("Queen", "white", 'Q', 0);
                    break;
                case 'q':
                    grid[row][col] = new Rook("Queen", "black", 'q', 0);
                    break;
                case 'N':
                    grid[row][col] = new Rook("Knight", "white", 'N', 0);
                    break;
                case 'n':
                    grid[row][col] = new Rook("Knight", "black", 'n', 0);
                    break;
                case 'K':
                    grid[row][col] = new Rook("King", "white", 'K', 0);
                    break;
                case 'k':
                    grid[row][col] = new Rook("King", "black", 'k', 0);
                    break;
                case 'B':
                    grid[row][col] = new Rook("Bishop", "white", 'B', 0);
                    break;
                case 'b':
                    grid[row][col] = new Rook("Bishop", "black", 'b', 0);
                    break;
                }
                col++;
            }
        }
        int n = 0;
        for (int i = 0; i < moves.length(); i++)
        {
            if (moves[i] == ',')
            {
                do
                {
                    if (moves[i] == ' ')
                    {
                        n++;
                    }
                    i++;
                } while (moves[i] != ',');
                break;
            }
        }
        string temp;
        n = n + 1; // total number of correct moves to win the game
        size = n;
        string rightmoves[n];
        int j = 0;
        for (int i = 0; i < moves.length(); i++)
        {
            if (moves[i] == ',')
            {
                i++;
                do
                {
                    correctmoves = correctmoves + moves[i];
                    i++;

                } while (moves[i] != ',');
                break;
            }
        }
    }
	bool checkMate(int *check){
		if(grid[5][4]->get_symbol() == 'p'){
			if(grid[4][3]->get_symbol() == 'p'){
				if(grid[3][7]->get_symbol() == 'q'){
					*check = 1;
					return true;//white wins
				}
			}
		}
		else{
			if(grid[5][5]->get_symbol() == 'p'){
//				if(grid[5][7]->get_symbol() == 'p'){
					if(grid[4][7]->get_symbol() == 'Q'){
						*check = 0;
						return true;//black wins
//					}
				}
			}
		}
		return false;
	}
	void display()
	{
//		
			 cout << "\033[1;33m\t\t\t\ta\tb\tc\td\te\tf\tg\th\033[0m" << endl
			 << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << "\t\t\t\033[1;33m" << 8 - i << "\033[0m";
			for (int j = 0; j < 8; j++)
			{
				cout << "\t" << grid[i][j]->get_symbol() << " ";
			}
			cout << endl
				 << endl;
		}
	}

	bool movePiece(string source, string destination)
	{
		int srcRow = 8 - (source[1] - '0');
		int srcCol = source[0] - 'a';
		int destRow = 8 - (destination[1] - '0');
		int destCol = destination[0] - 'a';
		
		if (grid[srcRow][srcCol]->get_symbol() == ' ' || grid[srcRow][srcCol]->get_symbol() == '-')
		{
			cout << "Invalid Symbol -- \n";
			return false;
		}

		if (grid[srcRow][srcCol]->isValidMove(source, destination, grid))
		{
			if (grid[destRow][destCol]->get_symbol() == '-')
			{
				grid[destRow][destCol] = grid[srcRow][srcCol];
				grid[srcRow][srcCol] = new EmptySpace(" ", " ", '-', 0);
//				cout << "Symbol is empty " << srcRow << " " << srcCol << " " << grid[srcRow][srcCol]->get_symbol() << endl;
				if (grid[destRow][destCol]->get_symbol() == 'p' || grid[destRow][destCol]->get_symbol() == 'P')
				{
					grid[destRow][destCol]->PawnPromotion(srcRow, srcCol, destRow, destCol, source, destination, grid);
				}
				return true;
			}
			else if ((grid[srcRow][srcCol]->get_symbol() > 'a' && grid[srcRow][srcCol]->get_symbol() < 'z') && (grid[destRow][destCol]->get_symbol() > 'A' && grid[destRow][destCol]->get_symbol() < 'Z') ||
					 (grid[srcRow][srcCol]->get_symbol() > 'A' && grid[srcRow][srcCol]->get_symbol() < 'Z') && (grid[destRow][destCol]->get_symbol() > 'a' && grid[destRow][destCol]->get_symbol() < 'z'))
			{
				if(grid[destRow][destCol]->get_color()=="white"){
					whitecaptured[capturewhitecnt] = grid[destRow][destCol]->get_symbol();
					capturewhitecnt += 1;
				}
				else{
                    blackcaptured[captureblackcnt] = grid[destRow][destCol]->get_symbol();
                    captureblackcnt += 1;
				}
				grid[destRow][destCol] = grid[srcRow][srcCol];
				grid[srcRow][srcCol] = new EmptySpace(" ", " ", '-', 0);
				if (grid[destRow][destCol]->get_symbol() == 'p' || grid[destRow][destCol]->get_symbol() == 'P')
				{
					grid[destRow][destCol]->PawnPromotion(srcRow, srcCol, destRow, destCol, source, destination, grid);
				}
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	friend string *breakstring(string moves, string correctmoves, int size);
};
class Player
{
	string name;
	int id;
	string experience;
	int wins;
	ChessBoard *b;
	// string history;
public:
	Player(string n, int _id, string exp, int score, ChessBoard *board)
	{
		name = n;
		id = _id;
		experience = exp;
		wins = score;
		b = board;
	}
	void setname(string n) { name = n; }
	void setid(int _id) { id = _id; }
	void setexp(string exp) { experience = exp; }
	string getname() { return name; }
	int getid() { return id; }
	string getexp() { return experience; }
	int getpreviousScore() { return wins; }
	void displayPlayerInfo()
	{
		cout << "Name : " << name << endl;
		cout << "Player Id : " << id << endl;
		cout << "Current Experience : " << experience << endl;
		cout << "Previous Score : " << wins << endl;
	}
	bool checkinput(string start, string end, int i)
	{

//		cout << "Move to check: " << start << end << endl;
		if (start.length() != 2 || end.length() != 2)
		{
			return false;
		}
		/*	if(start[0]<'a' || start[0]>'g' || end[0]<'a' || end[0]>'g' ){
				return false;
			}
			if(start[1]<1 || start[1]>8 || end[1]<1 || end[1]>8){
				return false;
			}*/
		int source_x = 8 - (start[1] - '0');
		int source_y = start[0] - 'a';
		string color = b->grid[source_x][source_y]->get_color();

		if ((i % 2) == 0)
		{ // player 1->black
			if (color == "white")
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			if (color == "black")
			{
				return true;
			}
			else
			{

				return false;
			}
		}
		return false;
	}
	bool turn(string start, string end)
	{
//		cout << "Turn in" << endl;
		if (b->movePiece(start, end))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isoldplayer()
	{
		ifstream file("PlayerData.txt");
		string line;
		while (getline(file, line))
		{
			stringstream ss(line);
			string playerName;
			ss >> playerName; // First token in the line is the player's name
			if (playerName == name)
			{
				file.close();
				return true;
			}
		}
		file.close();
		return false;
	}
	void addplayertofile()
	{
		if (isoldplayer())
		{
		}
		else
		{
			ofstream file("PlayerData.txt", ios::app);
			file << name << " " << experience << " " << wins << "\n";
			file.close();
		}
	}
	void incrementwinnercount(string name) {
		ifstream file("PlayerData.txt");
	    ofstream tempFile("temp.txt");
	    string line;
	    while (getline(file, line)) {
	        stringstream ss(line);
	        string playerName;
	        ss >> playerName; // First token in the line is the player's name
	        if (playerName == name) {
	            // Update the win count and rewrite the line
	            int currentWins;
	            ss >> experience >> currentWins;
	            currentWins++; // Increment the win count
	            tempFile << playerName << " " << experience << " " << currentWins << "\n";
	        } else {
	            // Write the line as it is
	            tempFile << line << endl;
	        }
	    }
	
	    file.close();
	    tempFile.close();
	
	    // Rename temp file to original file
	    remove("PlayerData.txt");
	    rename("temp.txt", "PlayerData.txt");
	}
};

string getstring(int n)
{
	string filename = "BoardString.txt";
    ifstream file("BoardString.txt");
    
	try{
		if (!file.is_open()) {
            throw filename;
        }
	}
	catch(string str){
        cout<<"Failed to open file "<<filename<<endl;
		return 0;
	}
	string line;
	for(int i=0;i<n;i++){
		getline(file, line);
	}
	
    if (getline(file, line)) {
        cout << "Read line: " <<  endl;
		size = size + line.length();
		return line;
    } else {
        cout << "End of file reached." << endl;
        return 0;
    }
	file.close();
}

string *breakstring(string moves, string correctmoves, int size)
{
	ChessBoard brd;
	brd.n = size;
    string* rightmoves = new string[size];
//    string rightmoves[size];
    // const int MAX_STRINGS = 1000;
    string temp;
    int commacount = 0;
    int j = 0;
    for (int i = 0; i < moves.length(); i++)
    {
        if (moves[i] == ',')
        {
            i++;
            //	count++;
            do
            {

                correctmoves = correctmoves + moves[i];
                temp = "";
                for (int k = 0; k < 4; k++)
                {
                    temp = temp + moves[i];
                    i++;
                }
                if (moves[i] == ',')
                {
                    commacount++;
                    if (commacount != 1)
                    {
                        break;
                    }
                }
                rightmoves[j] = temp;
                cout << "move " << j + 1 << " " << rightmoves[j] << endl;
                j++;
                i++;

            } while (moves[i] != ',');
            break;
        }
    }
    cout << "exiting break string function : " << endl;
    return rightmoves;
}

int main()
{
	while (1)
	{
		int n = 0;
		cout << "\t\t\t\t\033[1;34m ____  _           \033[0m\033[1;33m           _   __             _         \033[0m" << endl;
		cout << "\t\t\t\t\033[1;34m|  __|| |__   ___  ____ ____ \033[0m\033[1;33m|  \\/  | ___   ____| |_  ___   _ _ \033[0m" << endl;
		cout << "\t\t\t\t\033[1;34m| |__ |  _ \\ / __)/__ //__ /\033[0m\033[1;33m | |\\/| |/ _ \\ /__ /| |_ / _ \\ | '_|\033[0m" << endl;
		cout << "\t\t\t\t\033[1;34m|____||_| |_|\\___ __)_)__)_) \033[0m\033[1;33m|_|  |_|\\___,\\__)_){___)\\___,\\|_|\n\033[0m" << endl;
		cout << "\t\t\t\t\033[1;34m\033[4m_____________________________\033[0m\033[1;33m__________________________________\033[0m" << endl;
		cout << endl
			 << "\t\t\t\t\t   \033[1mBringing Chess To The Digital World\033[0m" << endl
			 << endl;
		cout << endl
			 << "\t\t\t\t\t\t\t   \033[1m\033[1;32mMENU\033[0m\033[0m" << endl
			 << endl;
		cout << "\t\t\t\t\t\t     1. Chess Game" << endl;
		cout << "\t\t\t\t\t\t     2. Puzzle Mania" << endl;
		cout << "\t\t\t\t\t\t     3. Learn How to Play" << endl;
		
		cout << "Enter option number " << endl;
		int option;
		cin >> option;
		if (option == 1)
		{
			int i=2, check;
			system("cls");
			ChessBoard board;

			string pl1, pl2;
			cout << "Enter player 1 name ";
			cin >> pl1;
			cout << "Enter player 2 name ";
			cin >> pl2;

			Player p1(pl1, 1, "beginner", 0, &board);
			Player p2(pl2, 2, "beginner", 0, &board);
			p1.addplayertofile();
			p2.addplayertofile();
	
			board.display();
			cout << endl;
			string start, end;
			cout << "enter the starting and ending positions to play the game : " << endl;
			bool inputValidity;
			do
			{
				if((i % 2) == 0){
					cout << pl1 <<"'s turn : " << endl; // white pieces;
					cin >> start >> end;
					if (p1.checkinput(start, end, i))
					{
						if (p1.turn(start, end))
						{
							board.display();
							i++;
						}
						else
						{
							cout << "invalid input. enter again : ";
						}
					}
					else
					{
						cout << "invalid input. enter again : ";
					}
				}
				else
				{
					cout << pl2 << "'s turn : " << endl;
					cin >> start >> end;
					if (p2.checkinput(start, end, i))
					{
						if (p2.turn(start, end))
						{
							board.display();
							i++;
						}
						else
						{
							cout << "invalid input. enter again : ";
						}
					}
					else
					{
						cout << "invalid input. enter again ";
					}
				}
			}while(!board.checkMate(&check));
			cout << "GAME ENDED !!!" << endl;
			if(check == 1){
				cout << pl1 << "\033[1;32m WON THE GAME !!!\033[0m" << endl;
				cout << pl2 << "\033[1;31m LOST THE GAME :( Better luck next time !\033[0m" << endl;
				p1.incrementwinnercount(pl1);
			}
			else{
				if(check == 0){
					cout << pl2 << "\033[1;32m WON THE GAME !!!\033[0m" << endl;	
					cout << pl1 << "\033[1;31m LOST THE GAME :( Better luck next time !\033[0m" << endl;
					p2.incrementwinnercount(pl2);
				}
			}
			char input = 'a';
			while(input != 'e'){
				cout << endl << endl << "\033[1;32mPress 'e' to return back to menu.\033[0m";
				cin >> input;
				if(input != 'e'){
					cout << endl << "\033[1;31mwrong input...\033[0m";
				}
			}
			system("cls");
		}
		else if (option == 2)
		{
			string moves = getstring(n);
            string start ="";
			string end = "";
            string correctstart, correctend;
            string turn;
            int size;
            string correctmoves;
            int movecount = 0;
            
            ChessBoard board(moves, size, correctmoves);
        
            string *rightmoves = breakstring(moves, correctmoves, size);
            
            //cout << "size : " << size << endl;
           /* for (int i = 0; i < size; i++)
            {
                cout << "move " << i + 1 << " " << rightmoves[i] << endl;
            }*/
            string pl1;
            cout << "Enter player  name :";
            cin >> pl1;

            Player p(pl1, 1, "beginner", 0, &board);
            p.addplayertofile();
            Player computer("computer", 2, "pro",0, &board);
            board.display();
            
            for(int i=0;i<size;i++){
            	
            	if ((i % 2) == 0)
                {
                	correctstart = "";
                	correctend = "";
                	turn = rightmoves[i];
                    correctstart +=  turn[0];
                    correctstart +=  turn[1];
                    correctend += turn[2];
                    correctend += turn[3];
                    cout<< correctstart << correctend<<endl;
                    cout << "player's turn : " << endl;
                    cin >> start >> end;
                    
                   
                      if(start==correctstart && end == correctend){
						
                        if (true)
                        {
                        	system("cls");
                        	board.movePiece(start, end);
                        	
                            board.display();
                            
                            movecount++;
                        }
                     }
                     
                        else
                        {
                            //cout << "invalid input. enter again : ";
                            cout << "puzzle exited " << endl;
                            return 0;
                            
                        }
                    
                    
                	
		}
			else
                {
                	start = "";
				    end = "";
                	turn = rightmoves[i];
                    start +=  turn[0];
                    start +=  turn[1];
                    end += turn[2];
                    end += turn[3];
                   /* cout << "turn : " << turn;
                    cout << "\tstart : " << start; 
                    cout << "\tend : " << end; */
                    cout << "computer's turn : " << endl; // black pieces;
                    
                    if (true)
                    {
                        if (true)
                        {
                        	system("cls");
                        	board.movePiece(start, end);
                            board.display();
                            
                            movecount++;
                            cout<<movecount<<endl;
                        }
                        else
                        {
                            cout << "invalid input. enter again : ";
                        }
                    }
                }
            if (movecount==size){
            	cout << p.getname() <<" won the game " << endl;
			}
            
        	}
        	char input = 'a';
        	while(input != 'e'){
				cout << endl << endl << "\033[1;32mPress 'e' to return back to menu.\033[0m";
				cin >> input;
				if(input != 'e'){
					cout << endl << "\033[1;31mwrong input...\033[0m";
				}
			}
			system("cls");
		}
		else if (option == 3)
		{
			char input = 'a';
			system("cls");
			cout << "\033[1;34m\t\t\t   A Comprehensive Guide to Chess: Rules, Gameplay, and Strategies\033[0m\n\n\033[1;33mIntroduction:\033[0m\nChess is a timeless game of strategy, patience, and intellect. With origins dating back centuries, it has captivated minds across the globe, from casual players to grandmasters. Its simplicity in setup belies its complexity in gameplay, making it a favorite pastime for enthusiasts of all ages. In this guide, we'll delve into the intricate rules, essential strategies, and tips to help you master the game of chess.\n\n\033[1;34mI. Setup:\033[0m\n\nChess is played on a square board divided into 64 smaller squares of alternating colors, typically black and white.\nEach player controls an army of 16 pieces: one king, one queen, two rooks, two knights, two bishops, and eight pawns.\nThe pieces are arranged on the board as follows:\nThe back row (from left to right) consists of rooks, knights, bishops, queen, king, bishops, knights, and rooks.\nThe front row is filled with pawns.\n\n\033[1;34mII. Objective\033[0m\n\nThe primary objective of chess is to checkmate your opponent's king. This occurs when the king is in a position to be captured (in check) and there is no legal move to escape the threat.\n\n\033[1;34mIII. Movement of Pieces:\033[0m\n\n\033[1;33mKing:\033[0m\n\nThe king can move one square in any direction: horizontally, vertically, or diagonally.\nThe king cannot move into a square that is under attack by an opponent's piece.\nIf a player's king is in a position to be captured, it is in check, and the player must make a move to remove the threat.\nIf the king is unable to escape check, it is checkmate, and the game ends.\n\n\033[1;33mQueen:\033[0m\n\nThe queen is the most powerful piece, able to move any number of squares in a straight line horizontally, vertically, or diagonally.\nIt cannot leap over other pieces.\n\n\033[1;33mRook:\033[0m\n\nRooks move any number of squares horizontally or vertically, but cannot move diagonally.\nThey are particularly powerful when positioned on open files (columns) or ranks (rows).\n\n\033[1;33mBishop:\033[0m\n\nBishops move any number of squares diagonally.\nEach player starts with one bishop on a light square and one on a dark square, meaning they control different colored squares throughout the game.\n\n\033[1;33mKnight:\033[0m\n\nKnights move in an L-shape, two squares in one direction (horizontally or vertically) and then one square perpendicular to that direction.\nThey are the only pieces that can 'jump' over other pieces, making their movement unpredictable.\n\n\033[1;33mPawn:\033[0m\n\nPawns move forward one square, but they capture diagonally.\nOn their first move, pawns have the option to move forward two squares.\nPawns can promote to any other piece (except a king) if they reach the opposite side of the board.\n\n\033[1;34mIV. Special Moves:\033[0m\n\n\033[1;33mCastling\033[0m\n\nCastling is a special move involving the king and one of the rooks.\nIt is the only move that allows two pieces to move during the same turn.\nTo castle, the king moves two squares towards the rook, and the rook moves to the square next to the king.\n\033[1;32mConditions for castling:\033[0m\nNeither the king nor the rook involved in castling have moved before.\nThe squares between the king and rook are unoccupied.\nThe king is not in check, and the squares it moves through are not under attack.\n\n\033[1;33mEn Passant:\033[0m\n\nIf a pawn moves two squares forward from its starting position and lands beside an opponent's pawn, the opponent can capture it as if it had moved only one square forward.\nThis capture must be made immediately after the pawn's double move.\n\n\033[1;33mPawn Promotion:\033[0m\n\nWhen a pawn reaches the opposite side of the board, it can be promoted to any other piece (except a king).\nPlayers typically choose to promote to a queen, as it is the most powerful piece.\n\n\033[1;34mV. Strategies and Tips:\033[0m\n\n\033[1;33mControl the Center:\033[0m\n\nOccupying the center of the board gives your pieces greater mobility and control over the game.\nAim to control key squares in the center early in the game.\n\n\033[1;33mDevelop Pieces:\033[0m\n\nBring your pieces into play quickly, particularly knights and bishops.\nAvoid moving the same piece multiple times in the opening, as this can waste valuable tempo.\n\n\033[1;33mKing Safety:\033[0m\n\nKeep your king safe by castling early and maintaining a solid pawn structure around it.\nAvoid leaving your king exposed to attacks.\n\n\033[1;33mTactical Awareness:\033[0m\n\nLook for tactical opportunities such as forks, pins, skewers, and discovered attacks.\nAlways be mindful of threats to your own pieces as well as your opponent's.\n\n\033[1;33mEndgame Technique:\033[0m\n\nAs the game progresses and pieces are exchanged, focus on simplifying into favorable endgames.\nKing activity and pawn structure become increasingly important in the endgame.\n\n\033[1;34mVI. Conclusion:\033[0m\n\nChess is a game of infinite possibilities, where each move shapes the course of the game. By mastering the rules, understanding basic strategies, and practicing regularly, you can unlock the full depth and beauty of this timeless game. Whether you're a casual player or aspiring grandmaster, the journey to chess mastery is as rewarding as the game itself.";
			while(input != 'e'){
				cout << endl << endl << "\033[1;32mPress 'e' to return back to menu.\033[0m";
				cin >> input;
				if(input != 'e'){
					cout << endl << "\033[1;31mwrong input...\033[0m";
				}
			}
			system("cls");
		}
		else
		{
			cout << "You choose an incorrect option" << endl;
			system("cls");
		}
	}
}
