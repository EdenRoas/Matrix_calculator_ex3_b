// @author  hpp


#include <iostream>
#include <vector>
using namespace std;
namespace zich
{

    class Matrix
    {

    private:
        int row;
        int cols;
        vector<double> my_mat;        
        


    public:
        Matrix();                                               // Default constructor
        Matrix(vector<double> mat, int rows, int columns); //  another constructor        
        // Addion
        Matrix operator+(const Matrix &mat_b); // mat += mat_b -> return new mat
        Matrix operator+=(const Matrix &mat_b);  // mat += mat_b -> return curr mat
        Matrix operator+(); //unari -> return the cureent mat without changes
          // Subtraction
        Matrix operator-(const Matrix &mat_b);  // mat -= mat_b -> return new mat
        Matrix operator-=(const Matrix &mat_b); // mat -= mat_b -> return curr mat
        Matrix operator-();// unari -> return new mat = mat* (-1)
        double sumMat();//return the sum of all cells
        // Multipliction
        Matrix operator*(double scalar);                     //return new mat -> curr mat * scalar
        Matrix operator*=(double scalar);                    //return curr mat * scalar
        friend Matrix operator*(double scalar, Matrix &mat); // return new mat -> scalar * curr mat 
        double multi(const Matrix &mat, const int row, const int col);//mult each cell
        Matrix operator* (const Matrix &mat);// mat*mat -> return new mat
        Matrix operator*= (const Matrix &mat);// mat * mat ->  return curr mat
        // Boolean opperators
        bool operator>(Matrix &mat_b); //check mat>mat_b ->true ? false
        bool operator>=(Matrix &mat_b);//check mat>=mat_b ->true ? false
        bool operator<(Matrix &mat_b);//check mat<mat_b ->true ? false
        bool operator<=(Matrix &mat_b);//check mat<=mat_b ->true ? false
        bool operator==(const Matrix &mat_b)const;// check if mat == mat_b -> true ? false
        bool operator!=(Matrix &mat_b); // check if mat != mat_b ->true ? false
        // pre & suf
        Matrix &operator++();   // increased by 1 -> cur mat
        Matrix operator++(int); // increased by 1 ->new mat
        Matrix &operator--(); // increased by -1 -> cur mat
        Matrix operator--(int); //increased by -1 -> new mat
        
        friend ostream& operator<< (ostream& output, const Matrix& mat);
        friend istream& operator>> (istream& is, Matrix& mat);
    };
}