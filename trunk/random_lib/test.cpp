#include <iostream>
#include "RandomSampling.hpp"
#include "RandomWalk.hpp"
#include "test.hpp"
#include <fstream>
#include "../n_puzzle/n_puzzle_solution.hpp"



int test_random_lib() ;

int test_puzzle_solution(int n);
//int randomSamplingTest3();


int test_puzzle_solution_progr(int n);
int main()
{

	//test();
	//test_puzzle_solution(2);
	//system("date");
	//system("time");
	//test_puzzle_solution(3);
	//system("date");
	//system("time");
	//system("pause");
	test_puzzle_solution_progr(3);
	//system("date");
	//system("time");
	//system("pause");
	//test_puzzle_solution(3);
	//system("pause");
	//test_puzzle_solution_progr(3);
	//system("pause");
	//system("date /T");
	//system("time /T");
	//test_puzzle_solution_progr(4);
	//system("date /T");
	//system("time /T");
	system("pause");
	return 0;
}

int test_puzzle_solution(int n)
{
	puzzle_solution puzzle; //obiekt klasy ktory rozwiaze problem
	std::vector<int> vect;	//wektor z problemem
	std::vector<int>  solution; //wektor zawierajacy sekwencje ruchow aby roziwazac problem
	//int n=3;	// rozmiar boku kwadratu ktory obrazuje pole puzzli
	for(int i=n*n-1;i>=0;i--)
	{
		vect.push_back(i);
	}
	
	puzzle.solve_puzzle(n,vect,solution,randomWalk,0);


	return 0;
}

int test_puzzle_solution_progr(int n)
{
	int signal=0;

  	std::ofstream filestr;

	puzzle_solution puzzle; //obiekt klasy ktory rozwiaze problem
	std::vector<int> vect;	//wektor z problemem
	std::vector<int>  solution; //wektor zawierajacy sekwencje ruchow aby roziwazac problem
	//int n=3;	// rozmiar boku kwadratu ktory obrazuje pole puzzli
	for(int i=n*n-1;i>=0;i--)
	{
		vect.push_back(i);
	}
	do{
		puzzle.solve_puzzle_progres(n,vect,solution,randomWalk,0);
		std::cout<<"\nZnaleziono rozwiazanie od dlugosci:  "<<solution.size()<<"\n\n";
		if(solution.size()>5000)
			solution.clear();
		else
			signal=1;
	}while(signal==0);
	filestr.open ("out",std::ios::trunc);

	for(unsigned int i=0;i<solution.size();i++)
	{
		filestr<<" "<<solution[i];
	}	
	filestr.flush();
 	filestr.close();
	return 0;
}

int randomWalkTest();
int randomSamplingTest1();
int randomSamplingTest2();

int test_random_lib()
{


	randomWalkTest();
	//system("pause");
	randomSamplingTest1();
	//system("pause");
	randomSamplingTest2();
	//system("pause");
//	randomSamplingTest3();
//	system("pause");

	return 0;
}


int randomWalkTest()
{
	std::cout<<"\n\n		RANDOM WALK TEST 1\n\n";
	//random_lib::ClonRandomWalk blle;
	random_lib::NumRandomWalk num;
	random_lib::RandomWalkSmPtr<D> num2;
	//random_lib::RandomWalk<>
	D* t=NULL;
	num.InsertValue(1);
	num.InsertValue(2);
	num.InsertValue(3);
	num.InsertValue(4);
	num.InsertValue(5);
	num.InsertValue(6);
	num.InsertValue(10); 
	num.InsertValue(11);
	num.InsertValue(12);
	num.InsertValue(13);

	num2.InsertValue(*(t=new D));
	num2.InsertValue(*(t=new D));
	num2.InsertValue(*(t=new D));
	num2.InsertValue(*(t=new D));
	num2.InsertValue(*(t=new D));
	num2.InsertValue(*(t=new D));
	num2.InsertValue(*(t=new D));
	num2.InsertValue(*(t=new D));

	//for(int i=0;i<50;i++)
	//{
	//	std::cout<<"Wylosowano: "<<num.NextStep()<<"\n";
	//}
	std::cout<<"Wylosowano: ";
	for(int i=0;i<50;i++)
	{
		std::cout<<"  "<<num2.NextStep().command();
	}
	std::cout<<"\n";
	return 0;
}

int randomSamplingTest1()
{
	std::cout<<"\n\n		RANDOM SAMPLING TEST 1\n\n";
	random_lib::NumRandomSampling sampler;
	int i=0;
	std::vector<int> sample;
	std::vector<int> out;

	for(int d=0;d<20;d++)
	{
		sample.push_back(d*2);
	}

	for(int d=0;d<15;d++)
	{
		sample.push_back(d*3);
	}

	for(int d=0;d<10;d++)
	{
		i=sampler.sampling(sample,out,sample.size()); 
		std::cout<<"Testing random_lib::RandomSampling, sample size:"<< sample.size()<<"number of got samples: "<<i <<out <<"\n";
		out.clear();
	}
	return 0;
}

int randomSamplingTest2()
{
	int i;
	std::cout<<"\n\n		RANDOM SAMPLING TEST 2\n\n";
	random_lib::RandomSamplingSmPtr<E> sampler;
	std::vector< boost::shared_ptr<E> > sample;
	std::vector< boost::shared_ptr<E> > out;
	//E *temp=NULL;
	for(i=0;i<20;i++)
	{
		boost::shared_ptr<E> ptr(new E());
		sample.push_back(ptr);
	}

	for(int d=0;d<10;d++)
	{
		i=sampler.sampling(sample,out,sample.size()); 
		std::cout<<"Testing random_lib::RandomSamplingSmPtr, sample size:"<< sample.size()<<"number of got samples: "<<i <<out <<"\n";
		out.clear();
	}
	
	return 0;
}
