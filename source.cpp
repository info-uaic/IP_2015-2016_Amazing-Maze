#include"Labirinth.h"
int main()
{
	system("color F5");
	int i, j, a[100][100] = { 9 },aux=0;
	int  width , length;
	int  maze_width , maze_length ;
	int  poz_i = 1, poz_j = 1,size=50;
	int random;
	int line_type[100][100];
	srand((unsigned)time(NULL));

	maze();
	menu();
	switch (_getch())
	{
	case '1':
	{width = 19; length = 19; }
	break;
	case '2':
	 {width = 19; length = 27; }
	 break;
	case '3':
	 {width = 27; length = 35; }
	}
	
	clear_screen();
	
	
	//maze_width = width, maze_length = length;
	//empty_matrice(line_type, width, length);
    //random_matrice(a, 1, maze_length,1,maze_width,line_type);
    empty_matrice(a, width, length);
	random_matrice_from_file(a, width, length);
	Movement(a, width, length, poz_i, poz_j,line_type);
	system("pause");
}
