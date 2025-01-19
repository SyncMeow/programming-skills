#include <iostream>
#include <vector>
using namespace std;

const int MaxTerms = 1000;

class term {
    friend Polynomial;
    private:
        float coef;
        int exp;    
};

class Polynomial {
    private:
        static term termArray[MaxTerms];
        static int free;
        int Start, Finish;

    public:
        Polynomial(); //return the polynomial

        int operator!(); //if *this is the zero polynomial, return 1, else return 0
        
        float Eval(float f); //evaluate the polynomial *this at f and return the result

        void NewTerm(float c, int e);
};

term Polynomial::termArray[MaxTerms];
int Polynomial::free = 0;

void Polynomial::NewTerm(float c, int e) {
    if (free >= MaxTerms) {
        cerr << "Too many terms in polynomials" << endl;
        exit(1);
    }
    termArray[free].coef = c;
    termArray[free].exp = e;
    free++;
}

int main() {
    
}