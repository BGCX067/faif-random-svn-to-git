
#include <boost/multi_array.hpp>
#include <vector>
#include <iostream>
#include "../random_lib/RandomSampling.hpp"
#include "../random_lib/RandomWalk.hpp"
#include "n_puzzle_solution.hpp"

int print_tab(int **ar,int n)
{
	
	for(int i=0;i<n;i++)
	{
		std::cout<<'\n';
		for(int j=0;j<n;j++)
		{
			std::cout<<ar[i][j]<<' ';
		}
	}
	
	std::cout<<" \n";
	return 0;
};

int puzzle_solution::solve_puzzle(int n,const std::vector<int> &puzzle, std::vector<int> &solution,int algorithm,int empty_element)
{
	if(n<=2)
	{
		std::cout<<"Blad zbyt male n";
			return -1;
	}
	// Stworz tablice 2D, n x n
	//boost::multi_array<int, 2, std::allocator<int> > ar(boost::extents[n][n]);
	
	int **ar=new int*[n]; //szybsze niz obiekt multi_array
	for(int i=0;i<n;i++)
		ar[i]=new int[n];
	//Przepisz zawartosc wektora puzzle do tablicy;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			ar[i][j]=puzzle[i*n+j];
		}


	std::cout<<"Stan poczatkowy tablicy "<<'\n';
	print_tab(ar,n);
	
	// solving problem
	/*
	*	W rozwiazywaniu problemu przyjmuje nastepujace zalozenia:
	*	0 albo liczba ujemna w wektorze puzzle oznacza pusta komorke puzzli ,
	*	obiekt RandomWalk/RandomSampling bedzie zwracac liczby z zakresu 1-4 (inne sany sa niedozwolone, 0 to stan poczatkowy)
	*	Oznaczaja one:
	*		
	*		UP	- przesuniecie na miejsce pustej komorki obiektu z gory (przystajacego do gornej krawedzi pustej komorki, pozostale operacje beda rozumiane analogicznie)
	*		RIGHT	- przesuniecie na miejsce pustej komorki obiektu z prawej strony
	*		DOWN	- przesuniecie na miejsce pustej komorki obiektu z dolu
	*		LEFT	- przesuniecie na miejsce pustej komorki obiektu z lewej strony
	*
	*/
	int last_state=0;//poprzedni wylosowany stan
	int state=0;	//wylosowany stan
	int temp_state=0;
	struct point p; //pozycja pustej komorki
	p.x=-1;
	p.y=-1;
	//inicjowanie klasy random walk
	random_lib::NumRandomWalk rWalk;
	random_lib::NumRandomSampling rSampling;
	//int vect_length=0;
	std::vector<int> sampled_vector;
	std::vector<int> temp_vect;
	

	rWalk.InsertValue(UP);
	rWalk.InsertValue(RIGHT);
	rWalk.InsertValue(DOWN);
	rWalk.InsertValue(LEFT);
	unsigned long long licznik=0;
	//znajdz pusta komórkê
    for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(ar[i][j]==empty_element)
			{
				p.y=i;
				p.x=j;
			}
		}
	}
	//zacznij wytyczanie sciezki
	for(;;)
	{

		int signal=1;
		//losuj stan przejscia

		state=rWalk.NextStep();
		//sprawdz czy to nie jest brzeg tablicy
		switch(state)
		{
		case UP:
			
			if(p.y==0) //gorna granica
				continue;
			
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y-1][p.x];
			ar[p.y-1][p.x]=temp_state;
			p.y--;
			break;
			
		case RIGHT:
			
			if(p.x==n-1) //prawa granica
				continue;
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y][p.x+1];
			ar[p.y][p.x+1]=temp_state;
			p.x++;
			break;
		case DOWN:
		
			if(p.y==n-1) //dolna granica
				continue;
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y+1][p.x];
			ar[p.y+1][p.x]=temp_state;
			p.y++;
			break;
		case LEFT:
			
			if(p.x==0) //prawa granica
				continue;
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y][p.x-1];
			ar[p.y][p.x-1]=temp_state;
			p.x--;
			break;
		default:
			//b³¹d
			continue;
		}
	
	
/*		if(ar[n-1][n-1]==0 && ar[0][0]==1 && ar[0][1]==2 &&  ar[0][2]==3 && ar[n-1][n-2]==n*n-1 && ar[n-1][0]==(n-1)*n+1 &&  ar[0][n-1]==n)
		{
 			std::cout<<"\nWykonano "<<licznik <<" cykli \n";
			print_tab(ar,n);
		}*/

		//sprawdz czy tablica jest uporzadkowana
		temp_state=-1;
		if( ar[n-1][n-1]==empty_element && ar[0][0]==1 && ar[n-1][0]==((n-1)*n+1) && ar[0][n-1]==n)
		{
			signal=0;
			for(int i=0;i<n;i++) 
			{
				for(int j=0;j<n;j++)
				{
					if((i==n-1)&&(j==n-1))
						continue;
					
					if(ar[i][j]<temp_state)
						signal=1;
					
					temp_state=ar[i][j];
				}
				if(signal==1)
					break;
			}
		}
		licznik++;
		last_state=state;
		solution.push_back(state);
		if(signal==0)
		{
			std::cout<<"\nWykonano "<<licznik <<" cykli \n";
			print_tab(ar,n);
		}
		if(signal==0)
		 break;
	}



	//end of the problem
		for(int i=0;i<n-1;i++)
			delete[] ar[i];
	delete[] ar;
	return 0;
};


int puzzle_solution::solve_puzzle_progres(int n,const std::vector<int> &puzzle, std::vector<int> &solution,int algorithm,int empty_element)
{
	
	// Stwórz tablice 2D, n x n
	//boost::multi_array<int, 2, std::allocator<int> > ar(boost::extents[n][n]);
	
	int **ar=new int*[n]; //szybsze ni¿ obiekt multi_array
	for(int i=0;i<n;i++)
		ar[i]=new int[n];
	//Przepisz zawartosc wektora puzzle do tablicy;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			ar[i][j]=puzzle[i*n+j];
		}


	std::cout<<"Stan poczatkowy tablicy "<<'\n';
	for(int i=0;i<n;i++)
	{
		std::cout<<'\n';
	for(int j=0;j<n;j++)
	{
		std::cout << ar[i][j] <<' ';
	}
	}
	std::cout<<'\n';
	
	// solving problem
	/*
	*	W rozwiazywaniu problemu przyjmuje nastepujace zalozenia:
	*	0 albo liczba ujemna w wektorze puzzle oznacza pusta komorke puzzli ,
	*	obiekt RandomWalk/RandomSampling bedzie zwracac liczby z zakresu 1-4 (inne sany sa niedozwolone, 0 to stan poczatkowy)
	*	Oznaczaja one:
	*		
	*		1- przesuniecie na miejsce pustej komorki obiektu z gory (przystajacego do gornej krawedzi pustej komorki, pozostale operacje beda rozumiane analogicznie)
	*		2- przesuniecie na miejsce pustej komorki obiektu z prawej strony
	*		3- przesuniecie na miejsce pustej komorki obiektu z dolu
	*		4- przesuniecie na miejsce pustej komorki obiektu z lewej strony
	*
	*/
	int last_state=0;//poprzedni wylosowany stan
	int state=0;	//wylosowany stan
	int temp_state=0;
	struct point p; //pozycja pustej komórki
	p.x=-1;
	p.y=-1;
	//inicjowanie klasy random walk
	random_lib::NumRandomWalk rWalk;
	random_lib::NumRandomSampling rSampling;
	//int vect_length=0;
	std::vector<int> sampled_vector;
	std::vector<int> temp_vect;
	

	rWalk.InsertValue(UP);
	rWalk.InsertValue(RIGHT);
	rWalk.InsertValue(DOWN);
	rWalk.InsertValue(LEFT);
	unsigned long long licznik=0;
	//znajdz pust¹ komórkê
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(ar[i][j]==empty_element)
			{
				p.y=i;
				p.x=j;
			}
		}
	}
	//zacznij wytyczanie sciezki
	for(;;)
	{

		int signal=1;
		//losuj stan przejscia

		state=rWalk.NextStep();
		//sprawdz czy to nie jest brzeg tablicy
		switch(state)
		{
		case UP:
			if(last_state==DOWN)//nie ma cofania sie :)
				continue;
			if(p.y==0) //gorna granica
				continue;
			
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y-1][p.x];
			ar[p.y-1][p.x]=temp_state;
			p.y--;
			break;
			
		case RIGHT:
			if(last_state==LEFT) //nie ma cofania sie :)
				continue;
			if(p.x==n-1) //prawa granica
				continue;
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y][p.x+1];
			ar[p.y][p.x+1]=temp_state;
			p.x++;
			break;
		case DOWN:
			if(last_state==UP)//nie ma cofania sie :)
				continue;
			if(p.y==n-1) //dolna granica
				continue;
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y+1][p.x];
			ar[p.y+1][p.x]=temp_state;
			p.y++;
			break;
		case LEFT:
			if(last_state==RIGHT)//nie ma cofania sie :)
				continue;
			if(p.x==0) //prawa granica
				continue;
			temp_state=ar[p.y][p.x];
			ar[p.y][p.x]=ar[p.y][p.x-1];
			ar[p.y][p.x-1]=temp_state;
			p.x--;
			break;
		default:
			//b³¹d
			continue;
		}
	
	
		//if(ar[n-1][n-1]==0 && ar[0][0]==1 && ar[0][1]==2 &&  ar[0][2]==3 && ar[n-1][n-2]==n*n-1 && ar[n-1][0]==(n-1)*n+1 &&  ar[0][n-1]==n)
		//{
 	//		std::cout<<"\nWykonano "<<licznik <<" cykli \n";
		//	print_tab(ar,n);
		//}

		//sprawdz czy tablica jest uporzadkowana
		temp_state=-1;
		if( ar[n-1][n-1]==empty_element && ar[0][0]==1 && ar[n-1][0]==((n-1)*n+1) && ar[0][n-1]==n && ar[0][1]==2 && ar[n-1][n-2]==n*n-1)
		{
			std::cout<<"\nWykonano "<<licznik <<" cykli \n";
			print_tab(ar,n);

			signal=0;
			for(int i=0;i<n;i++) 
			{
				for(int j=0;j<n;j++)
				{
					if((i==n-1)&&(j==n-1))
						continue;
					
					if(ar[i][j]<temp_state)
						signal=1;
					
					temp_state=ar[i][j];
				}
				if(signal==1)
					break;
			}
		}
		licznik++;
		last_state=state;
		solution.push_back(state);
		if(signal==0)
		{
			std::cout<<"\nWykonano "<<licznik <<" cykli \n";
			for(int i=0;i<n;i++)
			{
				std::cout<<'\n';
				for(int j=0;j<n;j++)
				{
					std::cout<<ar[i][j]<<' ';
				}
			}
		}
		if(signal==0)
		 break;
	}



	//end of the problem
		for(int i=0;i<n-1;i++)
			delete[] ar[i];
	delete[] ar;
	return 0;
};

