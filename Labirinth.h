#include<iostream>
#include<string>
#include<fstream>
#include<windows.h>
#include<conio.h>
#include<time.h>
using namespace std;
ifstream f1("easy.txt");
ifstream f2("medium.txt");
ifstream f3("hard.txt");
int line_type[100][100];
int x ;
#define key_up 72
#define key_down 80
#define key_left 75
#define key_rigth 77
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

//finds if there is an vertical line at the poz a[i][j]
bool ver_line(int a[100][100], int i, int j, int line_type[100][100])
{//if (line_type[i][j] == 2)return false;
	if (i % 2 == 0 && j % 2 == 0)
		if (a[i][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j] == 1 && a[i + 1][j + 1] == 1)
			if (a[i - 1][j] == 1 && a[i - 1][j + 1] == 1 && a[i + 2][j] == 1 && a[i + 2][j + 1] == 1) return true;
			else return false;
			
			if (j % 2 == 0)
			//	if (line_type[i][j] == 1 || line_type[i][j] == 3)
					if (a[i][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j] == 1 && a[i + 1][j + 1] == 1) return true;
			return false;
}

//find if there is an orizontal line at the poz a[i][j]
bool or_line(int a[100][100], int i, int j, int line_type[100][100])
{//if (line_type[i][j] == 1)return false;
	if (i % 2 == 0 && j % 2 == 0)
		if (a[i][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j] == 1 && a[i + 1][j + 1] == 1)
			if (a[i][j - 1] == 1 && a[i + 1][j - 1] == 1 && a[i][j + 2] == 1 && a[i + 1][j + 2] == 1) return false;
	if (i % 2 == 0 && j % 2 == 0)
		if (ver_line(a, i, j, line_type))return false;
	
	if (i % 2 == 0)
	//	if (line_type[i][j] == 2 || line_type[i][j] == 3)
			if (a[i][j] == 1 && a[i][j + 1] == 1 && a[i + 1][j] == 1 && a[i + 1][j + 1] == 1) return true;
	return false;
}

//find if there is a T shape
bool up_T(int a[100][100], int i, int j, int line_type[100][100])
{
	if (or_line(a, i, j - 1, line_type) && or_line(a, i, j + 1, line_type) && ver_line(a, i + 1, j, line_type)) return true;
	return false;
}

//find if there is an upside down T shape
bool down_T(int a[100][100], int i, int j, int line_type[100][100])
{
	if (or_line(a, i, j - 1, line_type) && or_line(a, i, j + 1, line_type) && ver_line(a, i - 1, j, line_type)) return true;
	return false;
}

//find if there is an left T shape
bool left_T(int a[100][100], int i, int j, int line_type[100][100])
{
	if (ver_line(a, i, j, line_type))
		if (ver_line(a, i - 1, j, line_type) && ver_line(a, i + 1, j, line_type) && or_line(a, i, j - 1, line_type)) return true;
	return false;

}

//find if there is a right T shape
bool right_T(int a[100][100], int i, int j, int line_type[100][100])
{
	if (ver_line(a, i, j, line_type))
		if (ver_line(a, i - 1, j, line_type) && ver_line(a, i + 1, j, line_type) && or_line(a, i, j + 1, line_type)) return true;
	return false;

}

//find if there is a + shape
bool plus_shape(int a[100][100], int i, int j, int line_type[100][100])
{
	if (or_line(a, i, j - 1, line_type) && or_line(a, i, j + 1, line_type) && ver_line(a, i - 1, j, line_type) && ver_line(a, i + 1, j, line_type))return true;
	return false;
}

//corner down-left
bool l_down(int a[100][100], int i, int j, int line_type[100][100])
{
	if (a[i][j] == 1 && a[i + 1][j] == 0 && or_line(a, i, j + 1, line_type) && ver_line(a, i - 1, j, line_type)) return true;
	return false;
}

//corner up-right
bool r_up(int a[100][100], int i, int j, int line_type[100][100])
{
	if (a[i][j] == 0 && or_line(a, i, j - 2, line_type) && ver_line(a, i + 1, j - 1, line_type)) return true;
	return false;
}

//corner down-right
bool r_down(int a[100][100], int i, int j, int line_type[100][100])
{
	if (a[i][j] == 1 && a[i + 1][j] == 0 && or_line(a, i, j - 2, line_type) && ver_line(a, i - 1, j - 1, line_type)) return true;
	return false;
}

//corner up-left
bool l_up(int a[100][100], int i, int j, int line_type[100][100])
{
	if (a[i][j] == 0 && or_line(a, i, j + 1, line_type) && ver_line(a, i + 1, j, line_type)) return true;
	return false;
}

void Labirinth_generator(int a[100][100], int width, int length, int poz_i, int poz_j, int line_type[100][100])
{
	int i, j;
	for (i = 0; i <= width; i++)
		for (j = 0; j <= length; j++)
		{   //corners
			if (i == 0 && j == 0)cout << "\xC9";
			if (i == 0 && j == length)cout << "\xBB" << endl;
			if (i == width&&j == 0)cout << "\xC8";
			if (i == width&&j == length)cout << "\xBC" << endl;

			//border up
			if (i == 0 && j != 0 && j != length && a[1][j] == 1 && a[1][j + 1] == 1 && j % 2 == 0) cout << "\xCD\xCB";
			else if (i == 0 && j == length - 1)cout << "\xCD";
			else if (i == 0 && j != 0 && j != length)cout << "\xCD\xCD";

			//border down
			if (i == width && j != 0 && j != length&&a[width - 1][j] == 1 && a[width - 1][j + 1] == 1 && j % 2 == 0)cout << "\xCD\xCA";
			else if (i == width && j == length - 1)cout << " ";
			else if (i == width && j == length - 2)cout << "  ";
			else if (i == width && j == length - 3)cout << "\xCD ";
			else if (i == width && j != 0 && j != length)cout << "\xCD\xCD";

			//border left
			if (j == 0 && i != 0 && i != width&&i != width - 1 && a[i][1] == 1 && a[i + 1][1] == 1 && i % 2 == 0)cout << "\xCC";
			else  if (j == 0 && i != 0 && i != width &&i != width - 1)cout << "\xBA";

			//border right
			if (j == length && i != 0 && i != width &&i != width - 1 && a[i][length - 1] == 1 && a[i + 1][length - 1] == 1 && i % 2 == 0)cout << "\xB9" << endl;
			else if (j == length &&i != 0 && i != width && i != width - 1)cout << "\xBA" << endl;

			//inside corners
			if (l_down(a, i, j, line_type)) cout << "\xC8";
			if (r_up(a, i, j, line_type))cout << "\xBB";
			if (r_down(a, i, j, line_type))cout << "\xBC";
			if (l_up(a, i, j, line_type))cout << "\xC9";

			//spaces
			if (j % 2 == 1 && i != 0 && i != width - 1 && i != width - 1)
			{
				if (a[i][j] == 0 && ver_line(a, i - 1, j + 1, line_type) && a[i + 1][j + 1] == 0 && l_down(a, i, j + 1, line_type) == 0 && a[i][j + 3] != 0 && i == poz_i&&j == poz_j) cout << " \x99  ";//4
				else if (a[i][j] == 0 && ver_line(a, i - 1, j + 1, line_type) && l_down(a, i, j + 1, line_type) == 0 && a[i + 1][j + 1] == 0 && a[i][j + 3] != 0)cout << "    ";//4

				else if (a[i][j] == 0 && ver_line(a, i - 1, j + 1, line_type) && a[i + 1][j + 1] == 0 && l_down(a, i, j + 1, line_type) == 0 && i == poz_i&&j == poz_j) cout << " \x99  ";//4
				else if (a[i][j] == 0 && ver_line(a, i - 1, j + 1, line_type) && a[i + 1][j + 1] == 0 && l_down(a, i, j + 1, line_type) == 0 && l_up(a, i, j + 3, line_type) == 0)cout << "    ";//4

				else if (a[i][j] == 0 && ver_line(a, i - 1, j + 1, line_type) && i == poz_i&&j == poz_j) cout << " \x99 ";//3
				else if (a[i][j] == 0 && ver_line(a, i - 1, j + 1, line_type))cout << "   ";//3

				else if (a[i][j] == 0 && ver_line(a, i, j + 1, line_type) && i == poz_i&&j == poz_j) cout << " \x99 ";//3
				else if (a[i][j] == 0 && ver_line(a, i, j + 1, line_type))cout << "   ";//3

				else if (a[i][j] == 0 && l_down(a, i, j + 1, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 0 && l_down(a, i, j + 1, line_type))cout << "   ";//3

				else if (a[i][j] == 0 && l_up(a, i, j + 1, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 0 && l_up(a, i, j + 1, line_type))cout << "   ";//3

																					//	else if (or_line(a,i,j-2)&&or_line(a,i,j+2)&&a[i][j] == 0 && a[i][j + 1] == 0 && j != length - 2 && i == poz_i&&j == poz_j)cout << "  \x99  ";//5
																					//	else if (or_line(a, i, j - 2) && or_line(a, i, j + 2) && a[i][j] == 0 && a[i][j + 1] == 0 && j != length - 2)cout << "     ";//5

				else if (a[i][j] == 0 && a[i][j + 1] == 0 && j != length - 2 && i == poz_i&&j == poz_j)cout << " \x99  ";//4
				else if (a[i][j] == 0 && a[i][j + 1] == 0 && j != length - 2)cout << "    ";//4

				else if (a[i][j] == 0 && a[i][j + 1] == 0 && j == length - 2 && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 0 && a[i][j + 1] == 0 && j == length - 2)cout << "   ";//3

				else if (a[i][j] == 0 && ver_line(a, i, j + 1, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 0 && ver_line(a, i, j + 1, line_type))cout << "   ";//3



				if (a[i][j] == 1 && ver_line(a, i, j - 1, line_type) && or_line(a, i, j, line_type) == 0 && j != length - 2 && ver_line(a, i, j + 1, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 1 && ver_line(a, i, j - 1, line_type) && or_line(a, i, j, line_type) == 0 && j != length - 2 && ver_line(a, i, j + 1, line_type))cout << "   ";//3

				else if (a[i][j] == 1 && r_down(a, i, j, line_type) && a[i][j + 1] == 0 && a[i][j + 2] == 0 && i == poz_i&&j == poz_j) cout << " \x99  ";//4
				else if (a[i][j] == 1 && r_down(a, i, j, line_type) && a[i][j + 1] == 0 && a[i][j + 2] == 0) cout << "    ";//4

				else if (a[i][j] == 1 && r_down(a, i, j, line_type) && a[i][j + 1] == 0 && or_line(a, i, j + 2, line_type) && l_up(a, i, j + 1, line_type) == 0 && i == poz_i&&j == poz_j) cout << " \x99  ";//4
				else if (a[i][j] == 1 && r_down(a, i, j, line_type) && a[i][j + 1] == 0 && l_up(a, i, j + 1, line_type) == 0 && or_line(a, i, j + 2, line_type)) cout << "    ";//4

				else if (a[i][j] == 1 && l_down(a, i, j + 1, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 1 && l_down(a, i, j + 1, line_type))cout << "   ";//3

				else if (a[i][j] == 1 && l_up(a, i, j + 1, line_type) && ver_line(a, i, j - 1, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 1 && l_up(a, i, j + 1, line_type) && ver_line(a, i, j - 1, line_type))cout << "   ";//3

				else if (a[i][j] == 1 && ver_line(a, i, j - 1, line_type) && or_line(a, i, j, line_type) == 0 && j != length - 2 && i == poz_i&&j == poz_j) cout << " \x99  ";//4
				else if (a[i][j] == 1 && ver_line(a, i, j - 1, line_type) && or_line(a, i, j, line_type) == 0 && j != length - 2) cout << "    ";//4

				else if (a[i][j] == 1 && ver_line(a, i, j - 1, line_type) && or_line(a, i, j, line_type) == 0 && j == length - 2 && i == poz_i&&j == poz_j)cout << " \x99 "; //3
				else if (a[i][j] == 1 && ver_line(a, i, j - 1, line_type) && or_line(a, i, j, line_type) == 0 && j == length - 2)cout << "   "; //3

				else if (a[i][j] == 1 && or_line(a, i - 1, j, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 1 && or_line(a, i - 1, j, line_type))cout << "   ";//3

				else if (a[i][j] == 1 && r_down(a, i, j, line_type) && ver_line(a, i, j + 2, line_type) == 0 && ver_line(a, i - 1, j + 1, line_type) && a[i + 1][j + 2] == 0 && i == poz_i&&j == poz_j)cout << " \x99  ";//4
				else if (a[i][j] == 1 && r_down(a, i, j, line_type) && ver_line(a, i, j + 2, line_type) == 0 && ver_line(a, i - 1, j + 1, line_type) && a[i + 1][j + 2] == 0)cout << "    ";//4

				else if (a[i][j] == 1 && r_down(a, i, j, line_type) && i == poz_i&&j == poz_j)cout << " \x99 ";//3
				else if (a[i][j] == 1 && r_down(a, i, j, line_type))cout << "   ";//3
																	   //limit left
				else if (a[i][j] == 1 && a[i][j + 1] == 0 && ver_line(a, i - 1, j - 1, line_type) && j == length - 2 && i == poz_i&&j == poz_j)cout << " \x99";//3
				else if (a[i][j] == 1 && a[i][j + 1] == 0 && ver_line(a, i - 1, j - 1, line_type) && j == length - 2 && ver_line(a, i, j + 2, line_type) == 0)cout << "   ";//3

				else if (a[i][j] == 1 && a[i][j + 1] == 0 && ver_line(a, i - 1, j - 1, line_type) && j != length - 2 && l_up(a, i, j + 1, line_type) && i == poz_i&&j == poz_j)cout << "  \x99  ";//4
				else if (a[i][j] == 1 && a[i][j + 1] == 0 && ver_line(a, i - 1, j - 1, line_type) && j != length - 2 && l_up(a, i, j + 1, line_type)) cout << "    ";//4

				else if (a[i][j] == 1 && a[i][j + 1] == 0 && ver_line(a, i - 1, j - 1, line_type) && j != length - 2 && i == poz_i&&j == poz_j)cout << " \x99  ";//4
				else if (a[i][j] == 1 && a[i][j + 1] == 0 && ver_line(a, i - 1, j - 1, line_type) && j != length - 2) cout << "    ";//4
			}



			//inside lines
			if (or_line(a, i, j, line_type))cout << "\xCD\xCD\xCD";
			if (plus_shape(a, i, j, line_type))cout << "\xCE";
			else if (left_T(a, i, j, line_type))cout << "\xB9";
			else if (right_T(a, i, j, line_type))cout << "\xCC";
			else if (ver_line(a, i, j, line_type))cout << "\xBA";
			else if (down_T(a, i, j, line_type))cout << "\xCA";
			else if (up_T(a, i, j, line_type))cout << "\xCB";
			else if (or_line(a, i, j - 1, line_type) && or_line(a, i, j + 1, line_type))cout << "\xCD";



			//spaces #2
			if (j % 2 == 1 && i != 0 && i != width - 1 && i != width - 1)
			{
				//if (a[i][j] == 0 && or_line(a, i, j - 2) && ver_line(a, i, j + 1) == 0&&ver_line(a,i-1,j+1)&&j-2==1)cout << " ";
				if (a[i][j] == 1 && or_line(a, i, j, line_type) && a[i][j + 2] == 0 && r_up(a, i, j + 2, line_type) == 0) cout << " ";
				if (a[i][j] == 1 && or_line(a, i - 1, j, line_type) && ver_line(a, i, j + 1, line_type) == 0 && ver_line(a, i, j - 1, line_type) == 0 && j != length - 2) cout << " ";
				if (a[i][j] == 1 && ver_line(a, i - 1, j - 1, line_type) && ver_line(a, i - 1, j + 1, line_type) && or_line(a, i, j, line_type) == 0 && a[i + 1][j - 1] == 0 && l_down(a, i, j + 1, line_type) == 0)cout << "   ";//3
			}
		}

}

void Movement(int a[100][100], int width, int length, int poz_i, int poz_j,int line_type[100][100])
{
	int i = 0;
	CursorPosition.X = 0;
	CursorPosition.Y = 0;
	SetConsoleCursorPosition(console, CursorPosition);
	Labirinth_generator(a, width, length, poz_i, poz_j, line_type);
	cout << "Moves: " << i<<endl;
	while (poz_i != width - 2 || poz_j != length - 2)
	{
		CursorPosition.X = 0;
		CursorPosition.Y = 0;
		SetConsoleCursorPosition(console, CursorPosition);
		switch (_getch())
		{
		case key_down:
		{	if (or_line(a, poz_i + 1, poz_j, line_type) == 0 && poz_i != width - 2)
		{
			i++;
			poz_i = poz_i + 2;
			Labirinth_generator(a, width, length, poz_i, poz_j, line_type);
			cout << "Moves: " << i << endl;
		}}
		break;
		case key_up:
		{	if (or_line(a, poz_i - 1, poz_j, line_type) == 0 && poz_i != 1)
		{
			i++;
			poz_i = poz_i - 2;
		Labirinth_generator(a, width, length, poz_i, poz_j, line_type);
		cout << "Moves: " << i << endl;
		}
	}
		break;
		case key_left:
		{	if (ver_line(a, poz_i, poz_j - 1, line_type) == 0 && poz_j != 1)
		{
			i++;
			poz_j = poz_j - 2;
			Labirinth_generator(a, width, length, poz_i, poz_j, line_type);
			cout << "Moves: " << i << endl;
		}}
		break;
		case key_rigth:
		{if (ver_line(a, poz_i, poz_j + 1, line_type) == 0 && poz_j != length - 2)
		{
			i++;
			poz_j = poz_j + 2;
			Labirinth_generator(a, width, length, poz_i, poz_j, line_type);
			cout << "Moves: " << i << endl;
		}}
		break; 
		}

	}

	cout << "                       YOU WON!      " << endl;

}

int random_number(int size)
{
	int random;
    random = rand() % size + 1;
	return random;
}

void empty_matrice(int a[100][100], int width, int length)
{
	int i, j;
	for (i = 0; i <= width; i++)
		for (j = 0; j <= length; j++)

			if (i == 0 || j == 0 || i == width || j == length)
				a[i][j] = 9;
			else a[i][j] = 0;


}

void show_mat(int a[100][100], int width, int length)
{
	int i, j;
	for (i = 0; i <= width; i++)
	{
		for (j = 0; j <= length; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
}

void read_mat(int a[100][100], int width, int length)
{
	int i, j;
	for (i = 1; i < width; i++)
		for (j = 1; j < length; j++)
			f1 >> a[i][j];
}

//recursive division that doesn't work
void random_matrice(int a[100][100], int left_start, int right_up_corner, int up_start, int left_down_corner, int line_type[100][100])
{
	int i, j, v_wal, o_wal,gap0, gap1, gap2, gap3, aux;
	v_wal = random_number(right_up_corner / 2 - 1);
	o_wal = random_number(left_down_corner / 2 - 1);
	aux = left_down_corner / 2 - o_wal;
	gap0= random_number(left_down_corner / 2 - aux);
	gap1 = random_number(left_down_corner / 2 - o_wal);
	aux = right_up_corner / 2 - v_wal;
	gap2 = random_number(right_up_corner / 2 - aux);
	gap3 = random_number(right_up_corner / 2 - v_wal);

	for (j = up_start; j < left_down_corner; j++)
	{
		if (j != (o_wal + gap1) * 2 && j != (o_wal + gap1) * 2 - 1 && j != gap0 * 2 && j != gap0 * 2 - 1)
		{
			a[j][v_wal * 2] = 1;
			a[j][v_wal * 2 + 1] = 1;
			if (line_type[j][v_wal * 2] == 2) line_type[j][v_wal * 2] = 3;
			else line_type[j][v_wal * 2] = 1;

		}
	}
		
		if (a[left_down_corner][v_wal * 2] == 1 && a[left_down_corner][v_wal * 2 + 1] == 0)
	if (a[left_down_corner-1][v_wal * 2] == 1 && a[left_down_corner-1][v_wal * 2 + 1] == 1)
		a[left_down_corner][v_wal * 2 + 1] = 1;
	if (a[left_down_corner][v_wal * 2] == 0 && a[left_down_corner][v_wal * 2 + 1] == 1)
		if (a[left_down_corner - 1][v_wal * 2] == 1 && a[left_down_corner - 1][v_wal * 2 + 1] == 1)
			a[left_down_corner][v_wal * 2 ] = 1;
	

	for (j = left_start; j < right_up_corner; j++)
	{
		if (j != gap2 * 2 && j != gap2 * 2 - 1 && j != (gap3 + v_wal) * 2 && j != (gap3 + v_wal) * 2 - 1)
		{
			a[o_wal * 2][j] = 1;
			a[o_wal * 2 + 1][j] = 1;
			if (line_type[o_wal * 2][j] == 1) line_type[o_wal * 2][j] = 3;
			else line_type[o_wal * 2][j] = 2;
}
	
	}

	// left up square
	if (v_wal >=3 && o_wal >= 3)
		random_matrice(a,left_start, v_wal * 2+1 , up_start, o_wal * 2+1, line_type);
	
	// right up square
	if (right_up_corner / 2 - v_wal >= 3 && o_wal >= 3)
		random_matrice(a, v_wal * 2 + 1, right_up_corner,up_start, o_wal * 2+1, line_type);

	//left_down square
	if (v_wal >= 3&& left_down_corner / 2 - o_wal >=3)
    	random_matrice(a,left_start, v_wal * 2+1, o_wal * 2 + 1,left_down_corner, line_type);

	//right down square
	if (right_up_corner / 2 - v_wal >= 3 && left_down_corner / 2 - o_wal >= 3)
		random_matrice(a, v_wal * 2 + 1, right_up_corner, o_wal * 2 + 1, left_down_corner, line_type);
} 

 void clear_screen()
 {
	 CursorPosition.X = 0;
	 CursorPosition.Y = 0;
	 SetConsoleCursorPosition(console, CursorPosition);
	 int i, j;
	 for (i = 1; i <= 100; i++)
	 {
		 for (j = 1; j <= 110; j++)
			 cout << " ";
		 cout << endl;

	 }
 }

 void menu()
{
	cout << endl << endl << endl << endl;
	cout << "                                          Press the key for the desired difficulty"<<endl<<endl<<endl<<endl;
		cout << "                                                           1.EASY"<<endl<<endl;
		cout << "                                                           2.MEDIUM"<<endl<<endl;
		cout << "                                                           3.HARD"<<endl<<endl;
}

void random_matrice_from_file(int a[100][100], int width, int length)
{
	int i, j,x;
	int a1[100][100], a2[100][100], a3[100][100], a4[100][100], a5[100][100];
	if (width == 19 && length == 27)
	{  
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f2 >> a1[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f2 >> a2[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f2 >> a3[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f2 >> a4[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f2 >> a5[i][j];
		
			x = random_number(5);
			if (x == 1)
				for (i = 1; i < width; i++)
					for (j = 1; j < length; j++)
						a[i][j] = a1[i][j];
			if (x == 2)
				for (i = 1; i < width; i++)
					for (j = 1; j < length; j++)
						a[i][j] = a2[i][j];
			if (x == 3)
				for (i = 1; i < width; i++)
					for (j = 1; j < length; j++)
						a[i][j] = a3[i][j];
			if (x == 4)
				for (i = 1; i < width; i++)
					for (j = 1; j < length; j++)
						a[i][j] = a4[i][j];
			if (x == 5)
				for (i = 1; i < width; i++)
					for (j = 1; j < length; j++)
						a[i][j] = a5[i][j];

	}

	if (width == 19 && length == 19)
	{
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f1 >> a1[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f1 >> a2[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f1 >> a3[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f1 >> a4[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f1 >> a5[i][j];

		x = random_number(5);
		if (x == 1)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a1[i][j];
		if (x == 2)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a2[i][j];
		if (x == 3)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a3[i][j];
		if (x == 4)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a4[i][j];
		if (x == 5)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a5[i][j];

	}

	if (width == 27 && length == 35)
	{
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f3 >> a1[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f3 >> a2[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f3 >> a3[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f3 >> a4[i][j];
		for (i = 1; i < width; i++)
			for (j = 1; j < length; j++)
				f3 >> a5[i][j];

		x = random_number(5);
		if (x == 1)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a1[i][j];
		if (x == 2)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a2[i][j];
		if (x == 3)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a3[i][j];
		if (x == 4)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a4[i][j];
		if (x == 5)
			for (i = 1; i < width; i++)
				for (j = 1; j < length; j++)
					a[i][j] = a5[i][j];

	}
}

void maze()
{
	cout << "             \xC9\xCD\xCD\xBB             \xC9\xCD\xCD\xBB       \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB       \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB       \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB"<<endl;
	cout << "             \xBA\xB2\xB2\xBA             \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xBA       \xBA\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xBA       \xBA\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xBA" << endl;
	cout << "             \xBA\xB2\xB2\xBA             \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\xB2\xB2\xBA       \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC       \xBA\xB2\xB2\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC" << endl;
	cout << "             \xBA\xB2\xB2\xBA\xB2           \xB2\xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA                     \xB2\xB2          \xBA\xB2\xB2\xBA" << endl;
	cout << "             \xBA\xB2\xB2\xBA \xB2         \xB2 \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA                   \xB2\xB2            \xBA\xB2\xB2\xBA" << endl;
	cout << "             \xBA\xB2\xB2\xBA  \xB2       \xB2  \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\xB2\xB2\xBA                 \xB2\xB2              \xBA\xB2\xB2\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB" << endl;
	cout << "             \xBA\xB2\xB2\xBA   \xB2     \xB2   \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xBA               \xB2\xB2                \xBA\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xBA " << endl;
	cout << "             \xBA\xB2\xB2\xBA    \xB2\xB2\xB2\xB2\xB2    \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\xB2\xB2\xBA             \xB2\xB2                  \xBA\xB2\xB2\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC" << endl;
	cout << "             \xBA\xB2\xB2\xBA             \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA           \xB2\xB2                    \xBA\xB2\xB2\xBA" << endl;
	cout << "             \xBA\xB2\xB2\xBA             \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA       \xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB       \xBA\xB2\xB2\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB" << endl;
	cout << "             \xBA\xB2\xB2\xBA             \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xBA       \xBA\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xBA       \xBA\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xBA" << endl;
	cout << "             \xC8\xCD\xCD\xBC             \xC8\xCD\xCD\xBC       \xC8\xCD\xCD\xBC       \xC8\xCD\xCD\xBC       \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC       \xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC" << endl;
}