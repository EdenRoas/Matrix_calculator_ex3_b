// Author -> Eden Roas

#include <iostream>
#include <string>
#include <ctype.h>
#include "Matrix.hpp"

void check_shapes(int rows_a, int cols_a, int rows_b, int cols_b) // return if the 2 Matrices are the same size -> true ? false
{

    if (rows_a != rows_b || cols_a != cols_b)
    {
        __throw_length_error("Two Matrices are not same size!!");
    }
}
void check_shapes_for_mult(int rows_a, int cols_a, int rows_b, int cols_b) // check if the colums of the first mat are equals to the row's mat_b
{
    if (cols_a != rows_b)
    {
        __throw_length_error("cannot mult this Matrices with diffrenet size!!");
    }
}

zich::Matrix::Matrix()
{ // defult constructor -> matrix 2x2
    row = 2;
    cols = 2;
    int mat_lentgh = row * cols;
    my_mat.resize((unsigned long)mat_lentgh);
}

zich::Matrix::Matrix(vector<double> mat, int rows, int columns)
{ // main construcor

    if (rows < 0 || columns < 0)
    { // first check -> negative
        __throw_invalid_argument("martix size cannot be negative!!!");
    }
    if (rows * columns != mat.size())
    { // second check -> equal
        __throw_out_of_range("matrix size not equal to rows*cols inputs!!!");
    }
    row = rows;
    cols = columns;
    int mat_size = row * cols;
    my_mat.resize((unsigned long)mat_size);
    string::size_type i = 0;
    string Vec_check;
    for (i = 0; i < mat_size; ++i)
    { 
        my_mat.at(i) = mat.at(i);
    }
}
// Add
zich::Matrix zich::Matrix::operator+(const zich::Matrix &mat_b)
{ // mat += mat_b -> return new mat

    check_shapes(row, cols, mat_b.row, mat_b.cols);
    int mat_size = row * cols;
    string::size_type i = 0;
    Matrix ans_mat(my_mat, row, cols);
    for (i = 0; i < mat_size; ++i)
    {
        ans_mat.my_mat.at(i) += mat_b.my_mat.at(i);
    }
    return ans_mat;
}

zich::Matrix zich::Matrix::operator+=(const zich::Matrix &mat_b)
{ // mat += mat_b -> return curr mat

    check_shapes(row, cols, mat_b.row, mat_b.cols);
    int mat_size = row * cols;
    string::size_type i = 0;
    for (i = 0; i < mat_size; ++i)
    {
        my_mat.at(i) += mat_b.my_mat.at(i);
    }
    return *this;
}

zich::Matrix zich::Matrix::operator+() // unari -> return the cureent mat without changes
{
    return Matrix(my_mat, row, cols);
}

// Sub
zich::Matrix zich::Matrix::operator-(const zich::Matrix &mat_b)
{ // mat -= mat_b -> return new mat

    check_shapes(row, cols, mat_b.row, mat_b.cols);

    int mat_size = row * cols;
    string::size_type i = 0;

    Matrix ans_mat(my_mat, row, cols);

    for (i = 0; i < mat_size; ++i)
    {
        ans_mat.my_mat.at(i) -= mat_b.my_mat.at(i);
    }

    return ans_mat;
}

zich::Matrix zich::Matrix::operator-=(const zich::Matrix &mat_b)
{ // mat -= mat_b -> return curr mat

    check_shapes(row, cols, mat_b.row, mat_b.cols);

    int mat_size = row * cols;
    string::size_type i = 0;

    for (i = 0; i < mat_size; ++i)
    {
        my_mat.at(i) -= mat_b.my_mat.at(i);
    }

    return *this;
}

zich::Matrix zich::Matrix::operator-()
{ // unari -> return new mat = mat* (-1)

    int mat_size = row * cols;
    string::size_type i = 0;

    Matrix ans_mat(my_mat, row, cols);

    for (i = 0; i < mat_size; ++i)
    {
        ans_mat.my_mat.at(i) = -(ans_mat.my_mat.at(i));
    }
    return ans_mat;
}
// Mult
zich::Matrix zich::Matrix::operator*(double scalar)
{ // return new mat -> curr mat * scalar
    int mat_size = row * cols;
    string::size_type i = 0;
    Matrix ans_mat(my_mat, row, cols);
    for (i = 0; i < mat_size; ++i)
    {
        ans_mat.my_mat.at(i) *= scalar;
    }
    return ans_mat;
}

zich::Matrix zich::Matrix::operator*=(double scalar)
{ // return curr mat *= scalar
    int mat_size = row * cols;
    string::size_type i = 0;
    for (i = 0; i < mat_size; ++i)
    {
        my_mat.at(i) *= scalar;
    }
    return *this;
}
zich::Matrix zich::operator*(double scalar, zich::Matrix &mat)
{ // return new mat -> scalar * curr mat

    int mat_size = mat.row * mat.cols;
    string::size_type i = 0;

    Matrix ans_mat(mat.my_mat, mat.row, mat.cols);

    for (i = 0; i < mat_size; ++i)
    {
        ans_mat.my_mat.at(i) *= scalar;
    }
    return ans_mat;
}

double zich::Matrix::multi(const Matrix &mat, const int row, const int col) // mult eeach cell by this func
{
    double sum = 0;
    for (int i = 0; i < this->cols; i++)
    {
        sum += this->my_mat[(unsigned int)(this->cols * row + i)] * mat.my_mat[(unsigned int)(mat.cols * i + col)];
    }
    return sum;
}
zich::Matrix zich::Matrix::operator*(const Matrix &mat) // mat*mat -> return new mat
{
    check_shapes_for_mult(row, cols, mat.row, mat.cols);
    vector<double> sol_mat;
    sol_mat.resize((unsigned int)(this->row * mat.cols));
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            sol_mat[(unsigned int)(i * mat.cols + j)] = multi(mat, i, j);
        }
    }
    Matrix ans_mat(sol_mat, this->row, mat.cols);
    return ans_mat;
}
zich::Matrix zich::Matrix::operator*=(const Matrix &mat) // mat * mat ->  return curr mat
{
    check_shapes_for_mult(row, cols, mat.row, mat.cols);

    vector<double> ans_mat;
    ans_mat.resize((unsigned int)(this->row * mat.cols));
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < mat.cols; j++)
        {
            ans_mat[(unsigned int)(i * mat.cols + j)] = multi(mat, i, j);
        }
    }
    this->cols = mat.cols;
    this->my_mat = ans_mat;
    return *this;
}
// Operators
double zich::Matrix::sumMat()
{ //return the sum of all cells
    double sum = 0;
    for (int i = 0; i < this->row; i++)
    {
        for (int j = 0; j < this->cols; j++)
        {
            sum += this->my_mat[(unsigned int)(i * cols + j)];
        }
    }
    return sum;
}

bool zich::Matrix::operator>(zich::Matrix &mat_b) // check mat>mat_b ->true ? false
{
    check_shapes(row, cols, mat_b.row, mat_b.cols);
    return this->sumMat() > mat_b.sumMat();
}

bool zich::Matrix::operator>=(zich::Matrix &mat_b)
{ // check mat>=mat_b ->true ? false
    check_shapes(row, cols, mat_b.row, mat_b.cols);
    return this->sumMat() >= mat_b.sumMat();
}

bool zich::Matrix::operator<(zich::Matrix &mat_b)
{ // check mat<mat_b ->true ? false
    check_shapes(row, cols, mat_b.row, mat_b.cols);
    return this->sumMat() < mat_b.sumMat();
}

bool zich::Matrix::operator<=(zich::Matrix &mat_b)
{ // check mat <= mat_b ->true ? false
    check_shapes(row, cols, mat_b.row, mat_b.cols);
    return this->sumMat() <= mat_b.sumMat();
}

bool zich::Matrix::operator==(const zich::Matrix &mat_b) const
{ // check if mat == mat_b -> true ? false
    check_shapes(row, cols, mat_b.row, mat_b.cols);
    int mat_size = row * cols;
    string::size_type i = 0;
    for (i = 0; i < mat_size; ++i)
    {
        if (my_mat.at(i) != mat_b.my_mat.at(i))
        { // check each cell
            return false;
        }
    }
    return true;
}

bool zich::Matrix::operator!=(zich::Matrix &mat_b)
{ // check if mat != mat_b ->true ? false

    check_shapes(row, cols, mat_b.row, mat_b.cols);

    int mat_size = row * cols;
    string::size_type i = 0;

    for (i = 0; i < mat_size; ++i)
    {
        if (my_mat.at(i) != mat_b.my_mat.at(i))
        { // check cell,cell if equals ->true ? false
            return true;
        }
    }
    return false;
}

zich::Matrix &zich::Matrix::operator++()
{ // return the curr (increment by 1)mat
    int mat_size = row * cols;
    string::size_type i = 0;
    for (i = 0; i < mat_size; i++)
    {
        ++(my_mat.at(i));
    }
    return *this;
}

zich::Matrix zich::Matrix::operator++(int)
{ // return new mat ->increment by 1 the mat
    int mat_size = row * cols;
    string::size_type i = 0;
    Matrix ans_mat = *this;
    for (i = 0; i < mat_size; i++)
    {
        (my_mat.at(i))++;
    }
    return ans_mat;
}

zich::Matrix &zich::Matrix::operator--()
{ // return curr mat ->increment by -1 the mat
    int mat_size = row * cols;
    string::size_type i = 0;
    for (i = 0; i < mat_size; i++)
    {
        --(my_mat.at(i));
    }
    return *this;
}

zich::Matrix zich::Matrix::operator--(int)
{ // return new mat ->increment by -1 the mat

    int mat_size = row * cols;
    string::size_type i = 0;
    Matrix ans_mat = *this;

    for (i = 0; i < mat_size; i++)
    {
        (my_mat.at(i))--;
    }
    return ans_mat;
}

ostream &zich::operator<<(ostream &output, const zich::Matrix &mat)
{
    string::size_type i = 0;
    for ( i = 0; i < mat.row; i++)
    {
        output << "["; // new row of mat
        string::size_type j = 0;
        for (j = 0; j < mat.cols; j++){
            output << mat.my_mat[i *(unsigned long)mat.cols + j];
            if (j + 1 < mat.cols){ // add space after value
                output << " ";
            }
        }
        output << "]";  // end row of mat
        if (i + 1 < mat.row){ // new line
            output << endl;
        }
    }
    return output;
}

istream &zich::operator>>(istream &is, zich::Matrix &mat)
{
    string input;
    getline(is, input);
    size_t i = 0;
    int rows = 0;
    int columns = 0;
    int cols = 0;
    int tops = 0;
    size_t k = 0;
    if (input[0] != '[')
    {
        __throw_invalid_argument("index 0 must be  [ ");
    }
    for (i = 0; i < input.length(); ++i)
    {
        if (input[i] == '[')
        {
            tops++;
            cols = 0;
            k = 0;
            while (input[k] != ']')
            {
                cols++;
                k++;
            }
            cols /= 2;
            if (cols != columns && columns != 0)
            {
                __throw_invalid_argument("Columns does not equals");
            }
            else
            {
                columns = cols;
            }
        }
        if (input[i] == ']')
        {
            tops--;
            if (i == input.length() - 1)
            {
                rows++;
            }
            else if (input[i + 1] == ',' && input[i + 2] == ' ')
            {
                ++rows;
            }
            else
            {
                __throw_invalid_argument("wrong input");
            }
        }
    }
    if (tops != 0)
    {
        __throw_invalid_argument("wrong input,tops are not equal");
    }

    int const two = 2;

    vector<double> new_mat((unsigned int)(rows * columns));
    k = 0;
    size_t x = 0;
    double strTo = 0;
    for (i = 0; i < input.length(); ++i)
    {
        if (isdigit(input[i]) != 0)
        {
            strTo = input[i] - '0';
            x = i + 1;
            while ((input[x] != ' ' && input[x] != ']') && x < input.length())
            {
                strTo *= (two);
                strTo += input[x] - '0';
                ++x;
            }
            i = x; 
            cout << strTo << ", ";
            new_mat.at(k) = strTo;
            ++k;
        }
        else
        {
            continue;
        }
    }
    cout << endl;
    mat.my_mat = new_mat;
    mat.row = rows;
    mat.cols = columns;

    return is;
}