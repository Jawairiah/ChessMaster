#include<iostream>
#include<math.h>
using namespace std;
class ChessBoard;
class Queen;
class Knight;
class ChessPiece
{
	string name;
	string color;
	char symbol;

public:
	ChessPiece()
	{
		color = "white";
	}
	ChessPiece(string nm, string clr, char sym)
	{
		name = nm;
		color = clr;
		symbol = sym;
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
	virtual bool isValidMove(string source, string destination, ChessPiece *grid[])
	{
		cout << "\nVirtual\n";
	}
	//	virtual bool isValidMove(string source, string destination, ChessPiece *grid[]) = 0;
};
class Queen : public ChessPiece
{
public:
	Queen(string nm, string clr, char sym) : ChessPiece(nm, clr, sym)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[]) override
	{
		cout << "\nQUEEN MOVED\n";
		int source_x = source[0] - 'a';
		int source_y = '8' - source[1];
		int dest_x = destination[0] - 'a';
		int dest_y = '8' - destination[1];
		if (source[0] == destination[0] || source[1] == destination[1] || abs(dest_x - source_x) == abs(dest_y - source_y))
		{
			int dx = (dest_x > source_x) ? 1 : ((dest_x < source_x) ? -1 : 0);
			int dy = (dest_y > source_y) ? 1 : ((dest_y < source_y) ? -1 : 0);

			int x = source_x + dx;
			int y = source_y + dy;

			while (x != dest_x || y != dest_y)
			{
				if (grid[y][x].get_symbol() != ' ')
				{
					// There is a piece in the way
					return false;
				}
				x += dx;
				y += dy;
			}
		}
		else
		{
			return false;
		}
		return true;
	}
};
class King : public ChessPiece
{
public:
	King(string nm, string clr, char sym) : ChessPiece(nm, clr, sym)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[])
	{
		cout << "\nKING MOVED\n";
		return true;
	}
};
class Pawn : public ChessPiece
{
public:
	Pawn(string nm, string clr, char sym) : ChessPiece(nm, clr, sym)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[])
	{
		cout << "\nPAWN MOVED\n";
		return true;
	}
};
class Bishop : public ChessPiece
{
public:
	Bishop(string nm, string clr, char sym) : ChessPiece(nm, clr, sym)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[])
	{
		cout << "\nBISHOP MOVED\n";
		return true;
	}
};
class Knight : public ChessPiece
{
public:
	Knight(string nm, string clr, char sym) : ChessPiece(nm, clr, sym)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[]) override
	{
		cout << "\nKNIGHT MOVED\n";
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
class Rook : public ChessPiece
{
public:
	Rook(string nm, string clr, char sym) : ChessPiece(nm, clr, sym)
	{
	}
	bool isValidMove(string source, string destination, ChessPiece *grid[])
	{
		cout << "\nROOK MOVED\n";
		return true;
	}
};
class ChessBoard
{
public:
	ChessPiece *grid[8][8]; // Declaration of grid as a 2D array of ChessPiece pointers
	//Player *p1;
	//Player *p2;

	ChessBoard()
	{
		// Initialize the grid with nullptr
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				//	grid[i][j] = nullptr;
			}
		}
		grid[0][0] = new Rook("Rook", "black", 'R');
		grid[0][1] = new Knight("Knight", "black", 'N');
		grid[0][2] = new Bishop("Bishop", "black", 'B');
		grid[0][3] = new Queen("Queen", "black", 'Q');
		grid[0][4] = new King("King", "black", 'K');
		grid[0][5] = new Bishop("Bishop", "black", 'B');
		grid[0][6] = new Knight("Knight", "black", 'N');
		grid[0][7] = new Rook("Rook", "black", 'R');
		grid[7][0] = new Rook("Rook", "white", 'r');
		grid[7][1] = new Knight("Knight", "white", 'n');
		grid[7][2] = new Bishop("Bishop", "white", 'b');
		grid[7][3] = new Queen("Queen", "white", 'q');
		grid[7][4] = new King("King", "white", 'k');
		grid[7][5] = new Bishop("Bishop", "white", 'b');
		grid[7][6] = new Knight("Knight", "white", 'n');
		grid[7][7] = new Rook("Rook", "white", 'r');
		for (int i = 0; i < 8; i++)
		{
			grid[1][i] = new Pawn("Pawn", "black", 'P');
		}
		for (int i = 0; i < 8; i++)
		{
			grid[6][i] = new Pawn("Pawn", "white", 'p');
		}
		for (int i = 2; i < 6; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				grid[i][j] = new Pawn(" ", " ", ' ');
			}
		}
		//p1=player1;
		//p2=player2;
	}

	void display()
	{
		cout << "  a   b   c   d   e   f   g   h\n";
		for (int i = 0; i < 8; i++)
		{
			cout << 8 - i << " ";
			for (int j = 0; j < 8; j++)
			{
				cout << grid[i][j]->get_symbol() << "   ";
			}
			cout << 8 - i << endl;
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
			return false;
		}
		
		if (grid[srcRow][srcCol]->isValidMove(source, destination, *grid))
		{
			if (grid[destRow][destCol]->get_symbol() == ' ')
			{
				grid[destRow][destCol] = grid[srcRow][srcCol];
				grid[srcRow][srcCol] = new Pawn(" ", " ", '-');
				return true;
			}
			else if ((grid[srcRow][srcCol]->get_color()!= grid[destRow][destCol]->get_color()))
			{

				delete grid[destRow][destCol];
				grid[destRow][destCol] = grid[srcRow][srcCol];
				grid[srcRow][srcCol] = new Pawn(" ", " ", '-');
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
};
class Player
{
	string name;
	int id;
	string experience;
	int previousscore;
	ChessBoard *b;
	//string history;
public:
	Player(string n, int _id, string exp, int score, ChessBoard *board)
	{
		name = n;
		id = _id;
		experience = exp;
		previousscore = score;
		b = board;
	}
	void setname(string n) { name = n; }
	void setid(int _id) { id = _id; }
	void setexp(string exp) { experience = exp; }
	string getname() { return name; }
	int getid() { return id; }
	string getexp() { return experience; }
	int getpreviousScore() { return previousscore; }
	void displayPlayerInfo()
	{
		cout << "Name : " << name << endl;
		cout << "Player Id : " << id << endl;
		cout << "Current Experience : " << experience << endl;
		cout << "Previous Score : " << previousscore << endl;
	}
	bool checkinput(string start, string end, int i)
	{
		if (start.length() != 2 || end.length() != 2 )
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
		
		if ((i % 2) == 0 )
		{ //player 1->black
			if (color =="white")
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
	};
	bool turn(string start, string end)
	{
		if(b->movePiece(start, end)){
			return true;
		}
		else{
			return false;
		}
	}
};

int main()
{
	ChessBoard board;
	board.display();
	Player p1("sara", 1, "beginner", 0, &board);
	Player p2("asad", 2, "beginner", 0, &board);
	cout << endl;
	string start, end;
	cout << "enter the starting and ending positions to play the game : " << endl;
	bool inputValidity;
	for (int i = 2; i < 4;)
	{
		if ((i % 2) == 0 )
		{
			cout << "player one's turn : " << endl; //black pieces;
			cin >> start>> end;
			if (p1.checkinput(start, end, i))
			{
				if(p1.turn(start, end)){
                    board.display();
				    i++;
				}
				else{
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
			cout << "player two's turn : " << endl;
			cin >> start >> end;
			if (p2.checkinput(start, end, i))
			{
				if(p2.turn(start, end)){
                    board.display();
				    i++;
				}
				else{
					cout << "invalid input. enter again : ";
				};
			}
			else
			{
				cout << "invalid input. enter again ";
			}
		}
	}
}
