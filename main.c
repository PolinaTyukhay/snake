
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int main()
{
	srand(time(NULL));
	
	
	char newGameChoice = 0;
	char Key;
    int CurrentDir = 0;
	int direction_snake = 0;
	int Dead = 0;
	int i, j, z ;
	int Speed;
	char* arr;
	int CheckFoodCoord = 0;
	char unused[30];
	int arraySizeX = 16;
	int arraySizeY = 16;
	int newFood = 1;
	int foodPos[2];
	int Avail = 0;
	int food_testX = 0;
	int food_testY = 0;
	int snakePos[100];
	int snakeSize = 3;
	int snakeDir = 1; 
	COORD pos = { 0, 0 };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	while (1)
	{
		printf("Game window size (16 - 25)\n");
		scanf_s("%d", &arraySizeX);
		if (!(arraySizeX < 16 || arraySizeX > 25)) break;

	}
	
	arraySizeY = arraySizeX;
	system("cls");

	arr = malloc(arraySizeX * arraySizeY * sizeof(char));
	

	while (1)
	{ // new game cycle
		
		Dead = 0;
		CurrentDir = 0;
		CheckFoodCoord = 0;
		Avail = 0;
		newFood = 1;
		snakeDir = 1;
		Key = 0;
		snakeSize = 3;
		
		z = 24; 
		while (1)
		{
			system("cls");
			printf("During the game- DIE to exit!\nSpeed level: (1-40)\n");
			scanf_s("%d", &Speed);
			if (!(Speed < 1 || Speed > 40)) break;
			
		}
		system("cls");
		
		for (i = 0; i < snakeSize; i++)
		{
			if (i == 0)
			{
				while (1)
				{
					snakePos[i] = 1 + rand() % (arraySizeX - 2);
					snakePos[2 * i + 1] = 1 + rand() % (arraySizeX - 2);
					if ((snakePos[i] - (snakeSize + 1)) > 0 && (snakePos[i] + (snakeSize + 1)) < arraySizeX && (snakePos[2 * i + 1] - (snakeSize + 1)) > 0 && (snakePos[2 * i + 1] + (snakeSize + 1)) < arraySizeX)
						break;
				}
			}
			else
			{
				if (i == 1)
				{
					direction_snake = 1 + rand() % 4;
					
					switch (direction_snake)
					{
					case 1: /*Right*/
						for (j = 2; j < 2 * snakeSize + 1;)
						{
							snakePos[j] = snakePos[j - 2] + 1;
							snakePos[j + 1] = snakePos[j - 1];
							j += 2;
						}
						snakeDir = 1;
						break;
					case 2:  /*up*/
						for (j = 2; j < 2 * snakeSize + 1;)
						{
							snakePos[j] = snakePos[j - 2];
							snakePos[j + 1] = snakePos[j - 1] - 1;
							j += 2;
						}
						snakeDir = 2;
						break;
					case 3: /* Left*/
						for (j = 2; j < 2 * snakeSize + 1;)
						{
							snakePos[j] = snakePos[j - 2] - 1;
							snakePos[j + 1] = snakePos[j - 1];
							j += 2;
						}
						snakeDir = 3;
						break;
					case 4: /*Down */
						for (j = 2; j < 2 * snakeSize + 1;)
						{
							snakePos[j] = snakePos[j - 2];
							snakePos[j + 1] = snakePos[j - 1] + 1;
							j += 2;
						}
						snakeDir = 4;
						break;

					}
				}
			}
		}
		
		while (1)
		{
			z--;
			if (z == 0) newFood = 1;
			

			Avail = 0;
			CurrentDir = snakeDir;

			/* рамки*/
			for (i = 0; i < arraySizeX * arraySizeY; i++)
			{

				if (i < arraySizeX) arr[i] = '-';
				else if (i % arraySizeX == 0) { arr[i] = '|'; }
				else if (i > arraySizeX* (arraySizeY - 1)) arr[i] = '-';
				else if (i % arraySizeX == arraySizeX - 1) arr[i] = '|';
				else arr[i] = ' ';
			}

			/* еда , но чтобы не на змее  */
			if (newFood)
			{
				CheckFoodCoord = 0;
				for (;;)
				{
					food_testX = 1 + rand() % (arraySizeX - 2);
					food_testY = 1 + rand() % (arraySizeY - 2);
					for (i = 0; i < snakeSize; i++)
					{
						if ((snakePos[2 * i] != food_testX) && (snakePos[2 * i + 1] != food_testY))
							CheckFoodCoord = 1;
					}
					if (CheckFoodCoord) break;
				}
				foodPos[0] = food_testX;
				foodPos[1] = food_testY;
				z = arraySizeX * 2;
				newFood = 0;
			}

			/* проветка на еду , стены  */
			for (i = 0; i < snakeSize; i++)
			{
				/* food check */
				if ((snakePos[2 * i] == foodPos[0]) && (snakePos[2 * i + 1] == foodPos[1]))
				{
					newFood = 1;
					/* есть еда. змея длиннее  */
					if (snakeSize < 50) snakeSize++;
					Avail = 1;
					
				}
				/* стена не стена  */
				if (!Avail)
				{
					if ((arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '-') || (arr[snakePos[2 * snakeSize - 1] * arraySizeX + snakePos[2 * snakeSize - 2]] == '|'))
					{
						Dead = 1;
					}
				}
				else
				{
					if ((arr[snakePos[2 * snakeSize - 3] * arraySizeX + snakePos[2 * snakeSize - 4]] == '-') || (arr[snakePos[2 * snakeSize - 3] * arraySizeX + snakePos[2 * snakeSize - 4]] == '|'))
					{
						Dead = 1;
					}
				}
				/* а вдруг себя съела */
				if (i != (snakeSize - 1))
				{
					if ((snakePos[2 * (snakeSize - 1)] == snakePos[2 * i]) && (snakePos[2 * (snakeSize - 1) + 1] == snakePos[2 * i + 1]))
					{
						Dead = 1;

					}
				}
			}

			/* подвинуть змею */
			if (Avail)
			{
				for (i = snakeSize; i > 1; i--)
				{
					snakePos[2 * i - 1] = snakePos[2 * i - 3];
					snakePos[2 * i - 2] = snakePos[2 * i - 4];
				}
				if (snakeDir == 1) { snakePos[0] = snakePos[2] - 1; snakePos[1] = snakePos[3]; } // move right
				if (snakeDir == 2) { snakePos[0] = snakePos[2];	   snakePos[1] = snakePos[3] + 1; } // move up
				if (snakeDir == 3) { snakePos[0] = snakePos[2] + 1; snakePos[1] = snakePos[3]; } // move left
				if (snakeDir == 4) { snakePos[0] = snakePos[2];	   snakePos[1] = snakePos[3] - 1; } // move down
			}
			
			for (i = 0; i < snakeSize - 1; i++)
			{
				snakePos[2 * i] = snakePos[2 * i + 2];
				snakePos[2 * i + 1] = snakePos[2 * i + 3];
			}

			if (snakeDir == 1) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] + 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move right
			if (snakeDir == 2) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];	   snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] - 1; } // move up
			if (snakeDir == 3) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4] - 1; snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3]; } // move left
			if (snakeDir == 4) { snakePos[2 * snakeSize - 2] = snakePos[2 * snakeSize - 4];	   snakePos[2 * snakeSize - 1] = snakePos[2 * snakeSize - 3] + 1; } // move down

			/* тело змейки */
			for (i = 0; i < snakeSize; i++)
			{
				arr[snakePos[2 * i + 1] * arraySizeX + snakePos[2 * i]] = '#';
			}

			/* место еды */
			arr[foodPos[1] * arraySizeX + foodPos[0]] = '+';
			//system("cls");
			pos.X = 0;
			pos.Y = 0;
			SetConsoleCursorPosition(output, pos);
			/* печать*/
			for (i = 0; i < arraySizeX; i++)
			{
				for (j = 0; j < arraySizeY; j++)
				{
					printf("%c", arr[i * arraySizeX + j]);
				}
				printf("\n");
			}

			/* if condition Dead is satisfied -> break */
			Key = 0;
			if (Dead) break;
			Sleep(1000 / Speed);
			if (_kbhit())
			{
				Key = _getch();
			}
			if (Key == -32)
			{
				switch (_getch())
				{
				case 72:
					snakeDir = 2; //up
					break;
				case 80:
					snakeDir = 4; //down
					break;
				case 75:
					snakeDir = 3; //left
					break;
				case 77:
					snakeDir = 1; // right
					break;
				}
				
			}
	
			if (snakeDir != CurrentDir)
			{
				/* if the current direction is left -> we cannot choose right ...*/
				if (snakeDir == 2 && CurrentDir == 4) snakeDir = 4;
				if (snakeDir == 1 && CurrentDir == 3) snakeDir = 3;
				if (snakeDir == 4 && CurrentDir == 2) snakeDir = 2;
				if (snakeDir == 3 && CurrentDir == 1) snakeDir = 1;
			}
			
			CurrentDir = snakeDir;
			i++;
		}

		if (Dead==1)
		{
			while (1)
			{
				printf("U R dead ! Game over\nStart new game? (Y/N and press ENTER)\n");
				scanf_s("%c", &newGameChoice);
				if (newGameChoice == 'n' || newGameChoice == 'N')
				{
					
					printf("Game over\n");
					exit(0);
				}
				if (newGameChoice == 'y' || newGameChoice == 'Y') break;
				system("cls");
			}
		}
	
		
	}
	
	return 0;
}