/**
*	@file name: RandomWalk.h
*	@author  Kamil Zabielski
*	@description  Ten plik zawiera szablon clasy reprezentujacej algorytm  random walk
*	Dostêpne zaimplementowane szablony klas:
*	- RandomWalk
*	- RandomWalkSmPtr
*
*/

#ifndef _RANDOM_WALK_H_
#define _RANDOM_WALK_H_


#include <vector>
//#include <cmath>
#include <ctime>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/shared_ptr.hpp>
//#include "boost/date_time/posix_time/posix_time.hpp" 

#include "Clonable.hpp"


#if defined(_MSC_VER) && (_MSC_VER >= 1400)
#pragma warning(disable:4244)
#pragma warning(disable:4512)
#endif

namespace random_lib
{
	
/**
* @brief Szablon klasy algorytmu random walk.
* Uzycie: najpierw dodajemy wartosci do zbioru z ktorego losujemy poprzez metode InsertValue() otrzymujemy losowy obiekt z tego zbioru poprzez wywolanie metody NextStep()
*
* Ten szablon przechowuje elementy(albo wskazniki do nich) w kontenerze typu vector.
* trzeba  miec swiadomosc implikacji z tego wynikajacych. jesli utworzymy obiekt RandomWalk<foo> 
* podczas destrukcji tego obiektu zostana wywolane destruktory wszystkich obiektow klasy foo ktore zostaly wykorzystane jako argument metody InsertValue().
* Jesli utworzymy obiekt klasy RandomWalk<foo *> ten problem nie wystapi.
* 
*/
template <class T>
class RandomWalk
{
private:
	/**
	* Obiekt generatora liczb pseldolosowych.
	* @private 
	*/
	boost::mt19937  generator;
	/**
	* Wektor obiekow. Wektor zawiera obiekty wprowadzane metoda InsertValue(T& val) 
	* @see InsertValue()
	* @see NextStep()
	*/
	std::vector<T> vect;
	/**
	* Licznik wygenerowanych liczb pseldolosowych. Jest on konieczny gdyz generatory liczb pseldolosowych sa cykliczne.
	* Po 3mln wygenerowanych liczb generator liczb pseldolosowych jest inicjowany nowa wartoscia.
	*/
	unsigned long long counter;
	/**
	* Operator kopiujacy
	* Niemozna publicznie kopiowac obiektu  klasy(szablonu) RandomWalk
	* @param a referencja na obiekt na bazie ktorego ma sie odbyc kopiowanie
	* 
	*/
	RandomWalk<T>& operator=(const RandomWalk<T> &a){return NULL;};
	/**
	* Konstruktror kopiujacy
	* Niemozna publicznie torzyc kopii obiektu  klasy(szablonu) RandomWalk
	* @param a stala referencja na obiekt na bazie ktorego trzeba stworzyc kopie
	*/ 
	RandomWalk(const RandomWalk<T> &a):generator(){};
public: 
	/**
	* Konstruktor.
	* Inicjuje generator liczb pseldolosowych
	*/
	RandomWalk():generator(time(0)),counter(0)
	{
	//	boost::posix_time::ptime t=boost::posix_time::microsec_clock::local_time();
	};
	/**
	* Destruktor. 
	*/
	~RandomWalk(){};
	/**
	* void InsertValue( T& val)
	* Metoda za pomoca ktorej dodajemy obiekt danego typu do listy mozliwych do wylosowania elementow
	*/
	void InsertValue(const T& val)
	{
		
		vect.push_back(val);
	}

	/**
	* 
	* Metoda losuje obiekt i zwraca jego referencje. Obiekt jest brany z wektora vect.
	*/
	T& NextStep()
	{
		long long i=0;
		if(counter==3000000) //trzeba co jakis czas resetowac generator, bo jednak jest on okresowy :/
		{
			generator.seed(time(0));
			counter=0;
		}
		counter=0;
		i=generator();
		
		//std::cout<<'\n'<< "Wylosowano liczbe"<<i;
		i=(i%vect.size());
		//std::cout<<'	'<< "Po przeliczeniu"<<i;
		return (vect[static_cast<int>(i)]);
	}
	
};

/**
* @brief Szablon klasy algorytmu random walk.
* Uzycie: najpierw dodajemy wartosci do zbioru z ktorego losujemy poprzez metode InsertValue() otrzymujemy losowy obiekt z tego zbioru poprzez wywolanie metody NextStep()
*
* Ten szablon przechowuje elementy(albo wskazniki do nich) w kontenerze typu vector.
* Trzeba  miec swiadomosc implikacji z tego wynikajacych. jesli utworzymy obiekt RandomWalk< shared_ptr<foo> > 
* podczas destrukcji tego obiektu moga zostal wywolane destruktory obiektow klasy foo ktore zostaly wykorzystane jako argument metody InsertValue().
* Aby sie przed tym zabespieczyc nalezy przechowywac lokalne kopie obiektow typu shared_ptr<foo>.
* 
*/

template <class T>
class RandomWalkSmPtr
{
private:

	/**
	* Obiekt generatora liczb pseldolosowych.
	* @private 
	*/
	boost::mt19937  generator;
	/**
	* Wektor obiekow. Wektor zawiera obiekty wprowadzane metoda InsertValue(T& val) 
	* @see InsertValue()
	* @see NextStep()
	*/
	std::vector< boost::shared_ptr<T> > vect;
	/**
	* Licznik wygenerowanych liczb pseldolosowych. Jest on konieczny gdy¿ generatory liczb pseldolosowych s± cykliczne.
	* Po 3mln wygenerowanych liczb generator liczb pseldolosowych jest inicjowany nowa wartoscia.
	*/
	unsigned long long counter;
	/**
	* Operator kopiujacy
	* Niemozna publicznie kopiowac obiektu  klasy(szablonu) RandomWalk
	* @param a referencja na obiekt na bazie ktorego ma sie odbyc kopiowanie
	* 
	*/
	RandomWalkSmPtr<T>& operator=(const RandomWalkSmPtr<T>& a){return NULL;}; 
	/**
	* Konstruktror kopiujacy
	* Niemozna publicznie torzyc kopii obiektu  klasy(szablonu) RandomWalk
	* @param a stala referencja na obiekt na bazie ktorego trzeba stworzyc kopie
	*/ 
	RandomWalkSmPtr(const RandomWalkSmPtr<T>& a):generator(){};
public: 
	/**
	* Konstruktor.
	* Inicjuje generator liczb pseldolosowych
	*/
	RandomWalkSmPtr():generator(time(0)),counter(0){};
	/**
	* Destruktor. Przy wywolaniu destruktura w zaleznosci od ilosci referencji w liczniku obiektu shared_ptr<foo> moze zostaæ wywo³any destruktor obiektu foo.
	*/
	
	~RandomWalkSmPtr(){};
	/**
	* void InsertValue( T& val)
	* Metoda za pomoca której dodajemy obiekt danego typu do listy mo¿liwych do wylosowania elementów
	*/
	void InsertValue( T& val)
	{
		boost::shared_ptr<T> p(&val);
		vect.push_back(p);
	}

	/**
	* T& NextStep()
	* Metoda losuje i zwraca referencje na wylosowany obiekt
	*/
	T& NextStep()
	{
		long long i=0;
		if(counter==3000000) //trzeba co jakis czas resetowac generator, bo jednak jest on okresowy :/
		{
			generator.seed(time(0));
			counter=0;
		}
		counter++;
		i=generator();
		//std::cout<<'\n'<< "Wylosowano liczbe"<<i;
		i=(i%vect.size());
		//std::cout<<'	'<< "Po przeliczeniu"<<i;
		return (*vect[static_cast<int>(i)]);
	}
	
};


/*

template<>
class RandomWalk <class Clonable>
{
typedef boost::shared_ptr<Clonable> clonable_ptr;
private:
	//boost::mt19937 mt; // Idon't know if this is best random generator but it is fast and has big value range(and weight is less than 1K)
	//boost::normal_distribution<> dist;
	//boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > generator;
	boost::rand48 generator;
	unsigned long long counter;
	std::vector<clonable_ptr> vect;
	RandomWalk<Clonable>& operator=(const RandomWalk<Clonable>& a){return *this;}; // we don't want to copy this class
	RandomWalk(const RandomWalk<Clonable>& a):generator(){counter=0;};
public: 
	RandomWalk():generator(){};
	~RandomWalk(){};

	void InsertValue( Clonable &val)
	{
		clonable_ptr ptr((&val.Clone()));

		vect.push_back(ptr);
	};

	Clonable& NextStep()
	{
		long long i=0;
		
		if(counter==4000000) //trzeba co jakis czas resetowac generator, bo jednak jest on okresowy :/
		{
			generator.seed(time(0));
			counter=0;
		}
		counter++;
		i=generator();
		std::cout<<'\n'<< "Wylosowano liczbe"<<i;
		i=(i%vect.size());
		//std::cout<<'	'<< "Po przeliczeniu"<<i<<'\n';
		return (*vect[static_cast<int>(i)]);
	};
	
};

*/
/**
* typ reprezentujacy szablon klasy RandomWalk<int>.
*
*/
typedef RandomWalk<int>		NumRandomWalk;
/**
* Typ reprezentujacy szablon klasy RandomWalk<__int64>(RandomWalk<long long>)
*/
typedef RandomWalk<long long>	NumRandomWalk64;

//typedef RandomWalk<Clonable>			ClonRandomWalk;
};//namespace random_lib


#endif //_RANDOM_WALK_H_
