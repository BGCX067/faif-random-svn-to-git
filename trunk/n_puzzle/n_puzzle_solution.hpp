#ifndef _N_PUZZLE_SOLUTION_H_
#define _N_PUZZLE_SOLUTION_H_

const int randomWalk=0;/**< Stala reprezentujaca algorytm random_walk*/
const int randomSampling=1;/**< Stala reprezentujaca algorytm random_sampling*/

const int UP=1;
const int DOWN=3;
const int LEFT=2;
const int RIGHT=4;

/**
*	@brief Klasa reprezentujaca metody rozwiazania problemu n_puzzli
*	Klasa puzzle_solution implementuje metody do rozwiazania problemu n_puzzli.
*	Obecnie rozwiazuje ten problem metoda przypadku, wykorzystujac algorytm random_walk
*	@see  puzzle_solution::solve_puzzle
*/
class puzzle_solution
{
private:
	/**
	* Struktura reprezentujaca punkt w przesterzni 2D
	* 
	*/
	struct point{
		int x;	/**<Skladowa x*/
		int y;	/**<Skladowa y*/
	};

public:
	/**
	*	Metoda klasy puzzle_solution
	*	Rozwiazuje ona problem n_puzzli metoda przypadkowego przechodzenia, wykorzystujacego algorytm random_walk.
	*   	@param n Rozmiar pola (pole ma wymiary n x n)
	*	@param puzzle Referencja na vektor z rozmieszczeniem poczatkowym puzzli.
	*	@param solution Referencja do obiektu vektora do kt�rego b�d� wrzucane kolejne ruch pustego elementu.
	*	@param algorithm Wybrany algorytm z k�rym mamy rozw�zac problem. Nalezy skorzystac z sta�ych : randomWalk, randomSampling.
	*	@param empty_element Prarametr zawierajacy numer pustego pola w vektorze puzzle.
	*	@see randomSampling
	*	@see ranodmWalk
	*/
	int solve_puzzle(int n,const std::vector<int> &puzzle, std::vector<int> &solution,int algorithm,int empty_element);
	/**
	*	Metoda klasy puzzle_solution
	*	Rozwiazuje ona problem n_puzzli metoda przypadkowego przechodzenia, wykorzystujacego algorytm random_walk.
	*	Ponadto autor doda� jeszcze jedno za�orzenie. W tej metodzie przy przechodzeniu miedzy elementami pola, nie mozna wr�ci� do pola z 		*	kt�rego sie przysz�o w poprzednim ruchu. Pozwoala to osiagn�c lepsz� wydajnosc.
	*   	@param n Rozmiar pola (pole ma wymiary n x n)
	*	@param puzzle Referencja na vektor z rozmieszczeniem poczatkowym puzzli.
	*	@param solution Referencja do obiektu vektora do kt�rego b�d� wrzucane kolejne ruch pustego elementu.
	*	@param algorithm Wybrany algorytm z k�rym mamy rozw�zac problem. Nalezy skorzystac z sta�ych : randomWalk, randomSampling.
	*	@param empty_element Prarametr zawierajacy numer pustego pola w vektorze puzzle.
	*	@see randomSampling
	*	@see ranodmWalk
	*/
	int solve_puzzle_progres(int n,const std::vector<int> &puzzle, std::vector<int> &solution,int algorithm,int empty_element);

};


#endif /*_N_PUZZLE_SOLUTION_H_*/
