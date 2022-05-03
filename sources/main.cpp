#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <stdexcept>
#include "Matrix.hpp"


using namespace std;
using namespace zich;

int main(){

   vector<double> v_a = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}; // 4X4
   vector<double> v_b = {1,1,1,1,1,1,1,1}; //4X2
   vector<double> x = {1,2,3,4,5,6};
   Matrix mat_x (x,2,3);
   Matrix mat_y (x,3,2);
   Matrix mat_a(v_a,4,4);
   cout << mat_a << " --good--" << endl;
   try{
       Matrix mat_b(v_b,0,2);
   }
   catch (exception& ex){
       cout << "caught exception: " << ex.what() << endl;
   }
   Matrix mat_b(v_b,4,2);
   cout << mat_b << " --good--" << endl;
   try{
       Matrix m = mat_b * mat_a; //not good
   }
   catch (exception& ex){
       cout << "caught exception: " << ex.what() << endl;
   }
   Matrix mul = mat_a * mat_b; // 4X2 ->new mat
   mat_a *= mat_b; // to the curr mat
   
    cout   << mat_x * mat_y << endl; 
    cout   << mat_y * mat_x << endl; 

   try{
       bool t = true;
       t = mat_a >= mat_b;
       cout << t << " --> big and equal <--" << endl;
       t = mat_a <= mat_b;
       cout << t << " --> equal and smaller <--" << endl;
       t = mat_a > mat_b;
       cout << t << " --> bigger <--" << endl;
       t = mat_a < mat_b;
       cout << t << " --> smaller <--" << endl;
   }
   catch (exception& ex){
       cout << "caught exception: " << ex.what() << endl;
   }

   try{
       Matrix add = mat_b + mat_a;
       cout << add << " --good--" << endl;
   }
   catch (exception& ex){
       cout << "caught exception: " << ex.what() << endl;
   }



   return 0;
}