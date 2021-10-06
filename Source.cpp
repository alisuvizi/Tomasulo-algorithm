#include<iostream>
#include<conio.h>
#include<string>

using namespace std;

void Run(int **depend, int **depend_help, int  **&clockmatrix, int n, int iteration);
void dependency(int **n, int **&m, int **&q, int i);
void set_clock_ld(int **depend, int **depend_help, int  **&clockmatrix, int n, int &iteration, int i);
void set_clock_sd(int **depend, int **depend_help, int  **&clockmatrix, int n, int &iteration, int i);
void set_clock_addi(int **depend, int **depend_help, int  **&clockmatrix, int n, int iteration, int i);
void set_clock_bne(int **depend, int **depend_help, int  **&clockmatrix, int n, int iteration, int i);
void print(int **clockmatrix, int n, int iteration);
void clock_continue(int **&clockmatrix,int  n,int y);

void get_ld(int **&instruction, int i)
{
	cout << "\nfor example R 1 , 0 X 1	:	";
	char a[6];
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5];
	instruction[i][0] = 1;
	instruction[i][1] = int(a[1]) - 48;
	instruction[i][2] = int(a[3]) - 48;
	instruction[i][3] = int(a[5]) - 48;
}

void get_sd(int **&instruction, int i)
{
	cout << "\nfor example R 1 , 0 X 1	:	";
	char a[6];
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5];
	instruction[i][0] = 2;
	instruction[i][1] = int(a[1]) - 48;
	instruction[i][2] = int(a[3]) - 48;
	instruction[i][3] = int(a[5]) - 48;
}

void get_addi(int **&instruction, int i)
{
	cout << "\nfor example R 1 , R 2 , 3	:	";
	char a[7];
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6];
	instruction[i][0] = 7;
	instruction[i][1] = int(a[1]) - 48;
	instruction[i][2] = int(a[4]) - 48;
	instruction[i][3] = int(a[6]) - 48;
}

void get_bne(int **&instruction, int i)
{
	cout << "\nfor example X 1 , X 2 , L	:	";
	char a[7];
	cin >> a[0] >> a[1] >> a[2] >> a[3] >> a[4] >> a[5] >> a[6];
	instruction[i][0] = 8;
	instruction[i][1] = int(a[1]) - 48;
	instruction[i][2] = int(a[4]) - 48;
	instruction[i][3] =-200;
}

void ld_dep(int **instructions, int **&dependency, int **&dependency_help, int n, int i)
{
	bool flag = false;
	dependency[i][0] = 1;
	for (int j = i - 1;j >= 0;--j)
	{
		if (flag)
			break;
		else if (instructions[j][0] == 1)
		{
			dependency[j][0] = 1;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 6;
				flag = true;
			}
		}
		else if (instructions[j][0] == 2)
		{
			dependency[j][0] = 2;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 5;
				flag = true;
			}
		}
		else if (instructions[j][0] == 7)
		{
			if (instructions[i][3] == instructions[j][1])
			{
				dependency[i][3] = j;
				dependency_help[i][3] = 7;
				flag = true;
			}
			else if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 7;
				flag = true;
			}
		}
	}
}

void sd_dep(int **instructions, int **&dependency, int **&dependency_help, int n, int i)
{
	bool flag = false;
	dependency[i][0] = 2;
	for (int j = i - 1;j >= 0;--j)
	{
		if (flag)
			break;
		else if (instructions[j][0] == 1)
		{
			dependency[j][0] = 1;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 7;
				flag = true;
			}
			/*else if (instructions[i][3] == instructions[j][1])
			{
				dependency[i][1] = j;//shomare dastory ke be an vabastegi darad
				dependency_help[i][1] = 1;//shomare khonee ke be an vabastegi darad
				flag = true;
			}*/
		}
		/*else if(instructions[j][0]==2) // storhaye posht sar ham rabti be ham ndarand be goz dar dastresi be hafeze
		{
		dependency[j][0]=2;
		if(instructions[i][1]==instructions[j][1])
		{
		dependency[i][1]=j;
		dependency_help[i][1]=1;
		flag=true;
		}
		}*/
		else if (instructions[j][0] == 7)
		{
			if (instructions[i][3] == instructions[j][1])
			{
				dependency[i][3] = j;
				dependency_help[i][3] = 7;
				flag = true;
			}
			else if(instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 7;
				flag = true;
			}
		}
	}
}

void addi_dep(int **instructions, int **&dependency, int **&dependency_help, int n, int i)
{
	bool flag = false;
	dependency[i][0] = 7;
	for (int j = i - 1;j >= 0;--j)
	{
		if (flag)
			break;
		else if (instructions[j][0] == 1)
		{
			dependency[j][0] = 1;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 7;
				flag = true;
			}
			else if (instructions[i][1] == instructions[j][3])
			{
				dependency[i][3] = j;
				dependency_help[i][3] = 5;
				flag = true;
			}
		}
		else if (instructions[j][0] == 2)
		{
			dependency[j][0] = 2;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 5;
				flag = true;
			}
		}
		else if (instructions[j][0] == 7)
		{
			dependency[j][0] = 7;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 7;
				flag = true;
			}
		}
	}
}

void bne_dep(int **instructions, int **&dependency, int **&dependency_help, int n, int i)
{
	bool flag = false;
	dependency[i][0] = 8;
	for (int j = i - 1;j >= 0;--j)
	{
		if (flag)
			break;
		else if (instructions[j][0] == 1)//age dastor ghabli ld bashe
		{
			dependency[j][0] = 1;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 7;
				flag = true;
			}
			if (instructions[i][2] == instructions[j][1])
			{
				dependency[i][2] = j;
				dependency_help[i][2] = 7;
				flag = true;
			}
		}		
		
		else if (instructions[j][0] == 7)
		{
			dependency[j][0] = 7;
			if (instructions[i][1] == instructions[j][1])
			{
				dependency[i][1] = j;
				dependency_help[i][1] = 7;
				flag = true;
			}
			if (instructions[i][2] == instructions[j][1])
			{
				dependency[i][2] = j;
				dependency_help[i][2] = 7;
				flag = true;
			}
		}
	}
}

int main()
{
	int n;

	cout << "Enter number of instructions :\n";
	cin >> n;

	string name;

	int **instructions = new int*[n];
	for (int i = 0;i < n;++i)
		instructions[i] = new int[4];

									 
	for (int i = 0;i < n;++i)
	{
		cout << "\nPlease Enter (" << i + 1 << ") instruction name and press Enter key\n";
		cin >> name;
		if (name == "ld")
			get_ld(instructions, i);
		else if (name == "sd")
			get_sd(instructions, i);
		else if (name == "addi")
			get_addi(instructions, i);
		else if (name == "bne")
			get_bne(instructions, i);
	}


	int iteration = 1;
	cout << "\n\nEnter number of iteration: \n";
	cin >> iteration;

	int **clockmatrix = new int *[iteration*n];
	for (int i = 0;i < iteration*n;++i)
		clockmatrix[i] = new int[8];

	for (int i = 0;i < iteration*n;++i)
		for (int j = 0;j < 8;++j)
			clockmatrix[i][j] = 0;

	for (int i = 0, j = 0 ; i < iteration*n;i++, ++j)
		for (int k = 0;k < 4;++k)
		{
			if (j == n)
				j = 0;
			clockmatrix[i][k] = instructions[j][k];
		}
		

	int **depend = new int*[n];
	int **dep = new int*[n];
	for (int i = 0;i < n;++i)
		{
			depend[i] = new int[4];
			dep[i] = new int[4];
		}

	for (int i = 0;i <n;++i)
		for (int j = 0;j < 4;++j)
		{
			depend[i][j] = -1;
			dep[i][j] = -1;
		}

	dependency(instructions, depend, dep, n);


/*	for (int i = 1;i <n;++i, cout << "\n")
	{
		for (int j = 0;j < 4;++j)
			cout << depend[i][j] << " ";
		cout << "\n";
		for (int k = 0;k<4;++k)
			cout << dep[i][k] << " ";
	}
	_getch();*/

	Run(depend,dep, clockmatrix , n, iteration);
	clock_continue(clockmatrix, n, iteration);
	print(clockmatrix, n, iteration);

	_getch();
	return 0;
}

void dependency(int **instructions, int **&dependency, int **&dependency_help, int n)
{
	for (int i = 1;i < n;++i)
	{
		if (instructions[i][0] == 1)
			ld_dep(instructions, dependency, dependency_help, n, i);
		else if (instructions[i][0] == 2)
			sd_dep(instructions, dependency, dependency_help, n, i);
		else if (instructions[i][0] == 7)
			addi_dep(instructions, dependency, dependency_help, n, i);
		else if (instructions[i][0] == 8)
			bne_dep(instructions, dependency, dependency_help, n, i);
	}
}

void Run(int **depend,int **depend_help,int  **&clockmatrix,int n,int iteration)
{
	int mem=0;
	int counter = 1;
	for (int i = 0 , j=0 ; i < n*iteration ; i++)
	{
		if (clockmatrix[i][0] == 8&&j==2)
		{
			if (i != 0)
				++counter;
			clockmatrix[i][4] =counter++;
			j = 0;
			continue;
		}
		else
		{
			if (j == 2)
			{
				++counter;
				j = 0;
			}
			clockmatrix[i][4] = counter;
			++j;
		}
	}
	
			if (clockmatrix[0][0] == 1)
			{
				clockmatrix[0][5] = 2;
				clockmatrix[0][6] = 3;
				mem=clockmatrix[0][6];
				clockmatrix[0][7] = 4;
			}
			else if (clockmatrix[0][0] == 2)
			{
				clockmatrix[0][5] = 2;
				clockmatrix[0][6] = 3;
				mem=clockmatrix[0][6];
			}
			else if (clockmatrix[0][0] == 7)
			{
				clockmatrix[0][5] = 2;
				clockmatrix[0][7] = 3;
			}
			else if(clockmatrix[0][0] == 8)
				clockmatrix[0][5] = 2;
				
	
	for (int w = 1 ; w < n ; ++w)
	{
			cout<<"chap= "<<clockmatrix[w][0]<<"\n";
			if (clockmatrix[w][0] == 1)
			{
				int v = -1;
				for (int j = 1;j < 4;++j)
					if (depend[w][j] != -1)
						v = j;
				if (v == -1)
				{
					clockmatrix[w][5] = clockmatrix[w][4] + 1;
					if ((clockmatrix[w][5] + 1) <= mem)
						clockmatrix[w][6] = ++mem;
					else
					{
						clockmatrix[w][6] = clockmatrix[w][5] + 1;
						mem = clockmatrix[w][6];
					}
					clockmatrix[w][7] = clockmatrix[w][6] + 1;
				}
				else
				{
					clockmatrix[w][5] = clockmatrix[w][4]+1;
					if (mem > clockmatrix[w][5])
						clockmatrix[w][6] = ++mem;
					else
						mem = clockmatrix[w][6] = clockmatrix[depend[w][v]][depend_help[w][v]] + 1;;
					clockmatrix[w][7] = clockmatrix[w][6] + 1;
				}
			}

			else if (clockmatrix[w][0] == 2)
			{
				int v = -1;
				for (int j = 1;j < 4;++j)
					if (depend[w][j] != -1)
						v = j;
				if (v == -1)
				{
					clockmatrix[w][5] = clockmatrix[w][4] + 1;
					if ((clockmatrix[w][5] + 1) <= mem)
						clockmatrix[w][6] = ++mem;
					else
					{
						clockmatrix[w][6] = clockmatrix[w][5] + 1;
						mem = clockmatrix[w][6];
					}
					clockmatrix[w][7] = clockmatrix[w][6] + 1;
				}

				else
				{
					clockmatrix[w][5] =clockmatrix[w][4] + 1  ;
					if (mem > clockmatrix[w][5])
						clockmatrix[w][6] = ++mem;
					else
						mem = clockmatrix[w][6] = clockmatrix[depend[w][v]][depend_help[w][v]] + 1;
				}
			}

			else if (clockmatrix[w][0] == 7)
			{
				int v = -1;
				for (int j = 1;j < 4;++j)
					if (depend[w][j] != -1)
						v = j;
				if (v == -1)
				{
					clockmatrix[w][5] = clockmatrix[w][4] + 1;
					clockmatrix[w][7] = clockmatrix[w][5] + 1;
				}
				else
				{
					clockmatrix[w][5] = clockmatrix[depend[w][v]][depend_help[w][v]] + 1;
					clockmatrix[w][7] = clockmatrix[w][5] + 1;
				}
			}

			else if (clockmatrix[w][0] == 8)
			{
				int v = -1;
				for (int j = 1;j < 4;++j)
					if (depend[w][j] != -1)
						v = j;
				if (v == -1)
					clockmatrix[w][5] = clockmatrix[w][4] + 1;
				else
					clockmatrix[w][5] = clockmatrix[depend[w][v]][depend_help[w][v]] + 1;
			}
	}
}


void clock_continue(int **&clockmatrix,int n,int iteration)
{
	clockmatrix[n][5] = clockmatrix[n-1][5] + 1;
	int step = clockmatrix[n][5] - clockmatrix[0][5];
	for(int i=n,k=0;i<n*iteration;++i,++k)
		for (int j = 5;j < 8;++j)
		{
			if (clockmatrix[k][j] == 0)
			{
				clockmatrix[i][j] = 0;
				continue;
			}
			else
				clockmatrix[i][j] = clockmatrix[k][j] + step;
		}
}

void print(int **clockmatrix,int n,int iteration)
{
	
	cout << "\niter instructions  issue  exe  mem_acc  CDB\n\n";
	for(int i=0;i<n*iteration;++i)
		{
		if (clockmatrix[i][0] == 1)
			cout <<" "<<i/n+1<<"   "<<"ld " << "X" << clockmatrix[i][1] << "," << clockmatrix[i][2] << "(X" << clockmatrix[i][3] << ")     "<< clockmatrix[i][4]<<"     "<< clockmatrix[i][5]<<"      "<< clockmatrix[i][6]<<"      "<< cls, dependency, dependency_help, n, i);
		else if (instructions[i][0] == 8)
			bne_dep(instructions, dependency, dependency_help, n, i);
	}
}

void Run(int **depend,int **depend_help,int  **&clockmatrix,int n,int iteration)
{
	int mem=0;
	int counter = 1;
	for (int i = 0 , j=0 ; i < n*iteration ; i++)
	{
		if (clockmatrix[i][0] == 8&&j==2)
		{
			if (i != 0)
				++counter;
			clockmatrix[i][4] =counter++;
			j = 0;
			continue;
		}
		else
		{
			if (j == 2)
			{
				++counter;
				j = 0;
			}
			clockmatrix[i][4] = counter;
			++j;
		}
	}
	
			if (clockmatrix[0][0] == 1)
			{
				clockmatrix[0][5] = 2;
				clockmatrix[0][6] = 3;
				mem=clockmatrix[0][6];
				clockmatrix[0][7] = 4;
			}
			else if (clockmatrix[0][0] == 2)
			{
				clockmatrix[0][5] = 2;
				clockmatrix[0][6] = 3;
				mem=clockmatrix[0][6];