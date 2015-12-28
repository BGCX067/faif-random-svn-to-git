#ifndef _TEST_H_
#define _TEST_H_

/**
* Metoda przeladowujaca operator strumienia wyjsciowego dla kontenera vector
*
*/
template<class T>
std::ostream & operator<< (std::ostream &wyjscie, const std::vector<T> &s)         
{
	wyjscie <<"\nZawartosc vectora\n" ;
	for(unsigned int i=0;i<s.size();i++)
	{
		wyjscie <<s[i]<<"  " ;
	}
	wyjscie << "\n\n";
	return wyjscie;
}
/**
* Metoda przeladowujaca operator strumienia wyjsciowego dla kontenera vector przechowujacego sprytne wskazniki
*
*/
template<class T>
std::ostream & operator<< (std::ostream &wyjscie, const std::vector< boost::shared_ptr<T> > &s)         
{
	wyjscie <<"\nZawartosc vectora\n" ;
	for(unsigned int i=0;i<s.size();i++)
	{
		wyjscie <<*s[i]<<"  " ;
	}
	wyjscie << "\n\n";
	return wyjscie;
}

/**
*
* @brief Klasa D. Przyladowa klasa do testowania i analizowania dzialania szablonow RandomWalk i RandomSampling
*
*/
class D{
	static int licznik;
	int mNumber;
	D(const D& d){};
	D& operator=(D& d){D*temp;return *(temp=new D());};
public:
	D(){mNumber=licznik++;};
	~D(){std::cout<<"Niszcze obiekt klasy D num: "<<mNumber <<"\n";};
	int command(){return mNumber;};
	
};
/**
* Metoda przeladowujaca operator strumienia wyjsciowego dla referencji na obiekt klasy D
*
*/
std::ostream & operator<< (std::ostream &wyjscie, D &d)
	{
		wyjscie<<d.command();
		return wyjscie;
	};
int D::licznik=0;

/**
* @brief Klasa E. Przyladowa klasa do testowania i analizowania dzialania szablonow RandomWalk i RandomSampling
*
*/
class E{
	static int licznik;
	int mNumber;
public:
	E(){mNumber=licznik++;};
	E(const E &e)
	{
		// std::cout<<"\nKonstruktor kopiujacy klasy E\n";
		mNumber=licznik++;
	};
	E& operator=(const E &e)
	{
		E *t=NULL;
		//std::cout<<"\noperator kopiujacy klasy5 E\n";
		return *(t=new E());
	};
   	~E(){std::cout<<"Destruktor klasy E\n";};
	int command(){return mNumber;};
	
};
/**
* Metoda przeladowujaca operator strumienia wyjsciowego dla referencji na obiekt klasy E
*
*/
std::ostream & operator<< (std::ostream &wyjscie,  E &d)
	{
		wyjscie<<d.command();
		return wyjscie;
	};
int E::licznik=0;





#endif
