#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
const ll inf = 100000000000000;
const int MAX = 200000;
const int mod = 10;
class Matrix
{
public:
    vector<vector<int>> mat;
    Matrix(int sz)
    {
        mat.resize(sz+1, vector<int>(sz+1, 0));
    }
    Matrix operator + (const Matrix &b)
    {
        Matrix tmp(mat.size()-1);
        for(int i=1;i<mat.size();i++)
        {
            for(int j=1;j<mat.size();j++)
            {
                tmp.mat[i][j] = (mat[i][j] + b.mat[i][j])%mod;
            }
        }
        return tmp;
    }
    Matrix operator * (const Matrix &b)
    {
        Matrix tmp(mat.size()-1);
        for(int i=0;i<mat.size();i++)
        {
            for(int j=0;j<mat.size();j++)
            {
                int sum = 0;
                for(int k=0;k<mat.size();k++)
                {
                    sum += (mat[i][k] * b.mat[k][j])%mod;
                }
                tmp.mat[i][j] = sum;
            }
        }
        return tmp;
    }
    Matrix operator ^ (int power)
    {
        Matrix res(mat.size()-1);
        res.make_identity();
        Matrix A = *this;
        while(power)
        {
            if(power&1)
            {
                res = res * A;
            }
            A = A * A;
            power >>= 1;
        }
        return res;
    }
    void take_input()
    {
        for(int i=1;i<mat.size();i++)
        {
            for(int j=1;j<mat.size();j++)
            {
                cin >> mat[i][j];
            }
        } 
    }
    void make_identity()
    {
        for(int i=1;i<mat.size();i++)
        {
            for(int j=1;j<mat.size();j++)
            {
                mat[i][j] = (i == j);
            }
        }
    }
    void print()
    {
        for(int i=1;i<mat.size();i++)
        {
            for(int j=1;j<mat.size();j++)
            {
                cout << mat[i][j];
            }
            cout << "\n";
        }
    }
};
int main() {
    int N;
    cin >> N;
    Matrix mat(N);
    mat.take_input();
    mat.print();
    return 0;
}