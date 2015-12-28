#include <iostream>
#include <fstream>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <string>
#include <vector>
#include "n_puzzle_solution.hpp"

using namespace boost::python;
using namespace std;

typedef vector<int> vector_int;
enum solution_alg {random_walk = 0, random_sampling = 1};
/**
* @brief Klasa-wrapper do pythona. To przez nią interfejs HTTP wywołuje kod z c++ 
*/
class n_puzzle{

public:
   n_puzzle(){}
   //   n_puzzle(int n_size, solution_alg algorithm):d_size(n_size), d_algorithm(algorithm){}
//   void compute(int n_size, solution_alg algorithm, const vector_int & puzzle_order){
   int compute(int n_size, const vector_int & puzzle_order, const string & filename){
      //n_size to dlugosc boku kwadratowej układanki
      //puzzle order to wektor intow uporzadkowany w taki sposob:
      //dla ustawienia ukladanki:
      //  -- -- -- --
      // |2 |3 |1 |4 |
      //  -- -- -- --
      // |8 |7 |6 |5 |
      //  -- -- -- --
      // |9 |10|11|12|
      //  -- -- -- --
      // |15|14|13|XX|
      //  -- -- -- --
      // puzzle_order={2,3,1,4,8,7,6,5,9,10,11,12,15,14,13,(16)};
      // najwyzszy numer w ukladance n_size*n_size (tutaj n_size*n_size=16) reprezentuje wolne miejsce
      vector_int::const_iterator iter;
//      cout << algorithm << endl;
//      for(iter = puzzle_order.begin(); iter != puzzle_order.end(); iter++){
//         cout << (*iter) << " ";
//      }
//      cout <<  endl;
      ofstream out_file;
      string result_file = "results/" + filename;
      out_file.open (result_file.c_str());

      puzzle_solution p;
      vector_int result;
      p.solve_puzzle_progres(n_size, puzzle_order, result, random_walk, n_size*n_size);


      int row_len = 0;
      map<int,string> num_to_arrow;
      num_to_arrow[UP] = "&uarr;";
      num_to_arrow[DOWN] = "&darr;";
      num_to_arrow[LEFT] = "&larr;";
      num_to_arrow[RIGHT] = "&rarr;";
      out_file  << "<html><body>";
      
      iter = result.begin();
      while(iter != result.end()){
         out_file  << num_to_arrow[(*iter)];
         row_len++;
         ++iter;
         if(iter != result.end()){
             out_file  << ", ";
             if(row_len > 20){
               out_file  <<"\n";
               row_len = 0;   
             }
         }
      }
     out_file  << "<body></html>";
      out_file.close();
      return result.size();
   }
};

BOOST_PYTHON_MODULE(n_puzzle){
   class_<n_puzzle>("n_puzzle")
        .def("compute",&n_puzzle::compute)
        ;
   class_<vector_int >("vector_int")
        .def(vector_indexing_suite<vector_int >())
        ;
    enum_<solution_alg>("solution_alg")
        .value("random_walk", random_walk)
        .value("random_sampling", random_sampling)
        ;
}


