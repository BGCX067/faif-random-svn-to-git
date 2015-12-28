/**
*	@file: RandomSampling.h
*	@autor: Kamil Zabielski
*	@description Plik naglowkowy implementuje algorytm random sampling
*	Dostepne zaimplementowane szablony klas:
*	- RandomSampling
*	- RandomSamplingSmPtr
*
**/


#ifndef _RANDOM_SAMPLING_H_
#define _RANDOM_SAMPLING_H_


#include <vector>
#include <cmath>
#include <ctime>
//#include <boost/random.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/shared_ptr.hpp>
//#include "boost/date_time/posix_time/posix_time.hpp" 


namespace random_lib
{

	/**
	* @brief Szablon klasy RandomSampling
	* Reprezentuje ona algorytm probkowania losowego(metoda sampling()).
	* Ta klasa nadaje sie do uzywania z typami wbudowanymi oraz wskaznikami.
	* Do obiektow klasy urzytkowanika polecam klase RandomSamplingSmPtr
	* @see RandomWalk
	* @see RandomSamplingSmPtr
	* @see RandomSampling::sampling()
	*/
	template <class T>
	class RandomSampling
	{
	private:
		/**
		* Obiekt generatora liczb pseldolosowych
		* Prywatna skladowa szablonu klasy RandomSampling.
		* 
		*/
		boost::mt19937 generator;
		/**
		* Operator kopiujacy
		* Niemozna publicznie kopiowac obiektu  klasy(szablonu) RandomSampling
		* @param a referencja na obiekt na bazie ktorego ma sie odbyc kopiowanie
		* 
		*/
		RandomSampling<T>& operator=(const RandomSampling<T>& a)
		{
			return a;
		};
		/**
		* Konstruktror kopiujacy
		* Niemozna publicznie torzyc kopii obiektu  klasy(szablonu) RandomSampling
		* @param a stala referencja na obiekt na bazie ktorego trzeba stworzyc kopie
		*/
		RandomSampling(const RandomSampling<T>& a){};
	public:
		/**
		* Konstruktor.
		* Inicjuje generator liczb pseldolosowych
		*/
		RandomSampling(void):generator(std::time(0)){};
		/**
		* Destruktor
		*/
		~RandomSampling(void){};
		/**
		* Metoda sampling(...)
		* Funkcja przeprowadza  'probkowanie losowe' wektora signal, gromadzac do n probek w wektorze samples.
		* Inaczej mowiac na kazdym kolejnym elemencie wektora signal jest przeprowadzany test, gdy test wypadnie pozytywnie ten element jest wkladany do wektora samples(nadal równiez znajduje sie w wektorze signal).
		* Ten cykl jest powtarzany do spelnienia jednego z 2 warunkow: a) do wektora samples zostanie dodane n probek, b)zostanie osiagniety koniec wektora signal.  
		* @param signal 	wektor wartosci do przetwrzenia
		* @param samples 	wektor do ktorego sa wkladane wyniki przetwarzania,  po przetwarzaniu jego dopuszczalna dlugosc moze wynosic do n
		* @param n 		maksymalna dlugosc wektora samples
		* Wartosc zwracana:
		* @return  		wartosc zwracana to ilosc wylosowanych elementow (dlugosc wektora samples)
		*/
		long long sampling(const std::vector<T> &signal,std::vector<T> &samples,const long n)
		{
			long long i=0;
			long long sampled=0;
			long long size=signal.size();
			for(unsigned int d=0;d<size;d++)
			{
				i=generator();
		//std::cout<<'\n'<< "Wylosowano liczbe"<<i;
				i=i%10;
				if(i<5)
				{
					samples.push_back(signal[d]);
					sampled++;
				}
				if(sampled>=n)
					break;
			}
			return sampled;
		};
	};
		
	/**
	* @brief Szablon klasy RandomSamplingSmPtr
	* Reprezentuje ona algorytm probkowania losowego(metoda sampling()).
	* Klasa korzysta z kolekcji sprytnych wskaznikow.
	* Ta klasa nadaje sie do uzywania z typami zdefiniowanymi przez uzytkownika.
	* Do typow wbudowanych polecam klase RandomSampling
	* @see RandomWalk
	* @see RandomSampling
	* @see RandomSampling::sampling()
	*/
	template <class T>
	class RandomSamplingSmPtr
	{
	private:
		/**
		* boost::mt19937 generator
		* Obiekt generatora liczb pseldo losowych
		* Prywatna skladowa szablonu klasy RandomSampling.
		* 
		*/
		boost::mt19937 generator;
		/**
		* Operator kopiujacy
		* Niemozna publicznie kopiowac obiektu  klasy(szablonu) RandomSamplingSmPtr
		* @param a referencja na obiekt na bazie ktorego ma sie odbyc kopiowanie
		* 
		*/
		RandomSamplingSmPtr<T>& operator=(const RandomSamplingSmPtr<T>& a){return this;};
		/**
		* Konstruktror kopiujacy
		* Niemozna publicznie torzyc kopii obiektu  klasy(szablonu) RandomSampling
		* @param a stala referencja na obiekt na bazie ktorego trzeba stworzyc kopie
		*/
		RandomSamplingSmPtr(const RandomSamplingSmPtr<T>& a){};
	public:
		/**
		* Konstruktor.
		* Inicjuje generator liczb pseldolosowych
		*/
		RandomSamplingSmPtr(void):generator(time(0)){};
		/**
		* Destruktor
		*/
		~RandomSamplingSmPtr(void){};
		/**
		* @brief Metoda sampling(...)
		* Funkcja przeprowadza  'probkowanie losowe' wektora signal, gromadzac do n probek w wektorze samples.
		* Inaczej mowiac na kazdym kolejnym elemencie wektora signal jest przeprowadzany test, gdy test wypadnie pozytywnie ten element jest wkladany do wektora samples(nadal równiez znajduje sie w wektorze signal).
		* Ten cykl jest powtarzany do spelnienia jednego z 2 warunkow: a) do wektora samples zostanie dodane n probek, b)zostanie osiagniety koniec wektora signal.  
		*
		* @param signal 	wektor wartosci do przetwrzenia
		* @param samples 	wektor do ktorego sa wkladane wyniki przetwarzania,  po przetwarzaniu jego dopuszczalna dlugosc moze wynosic do n
		* @param n 		maksymalna dlugosc wektora samples
		* Wartosc zwracana:
		* @return  		wartosc zwracana to ilosc wylosowanych elementow (równoznaczne z dlugoscia wektora samples tylko wtedy gdy wektor samples by³ pusty)
		*/
		long long sampling(const std::vector< boost::shared_ptr<T> > &signal,std::vector< boost::shared_ptr<T> > &samples,const long n)
		{
			long long i=0;
			long long sampled=0;
			unsigned long long size=signal.size();
			for(unsigned int d=0;d<size;d++)
			{
				i=generator();
		//std::cout<<'\n'<< "Wylosowano liczbe"<<i;
				i=i%10;
				if(i<5)
				{
					samples.push_back(signal[d]);
					sampled++;
				}
				if(sampled>=n)
					break;
			}
			return sampled;
		};

		


	};

typedef RandomSampling<int>		NumRandomSampling;/**< Przykladowa klasa operujaca na typie int */
typedef RandomSampling<long long>	NumRandomSampling64;/**< Przykladowa klasa operujaca na typie __int64 (czyli w praktyce long long) */

};//namespace random_lib



#endif// _RANDOM_SAMPLING_H_
