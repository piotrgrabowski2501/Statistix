//Piotr Grabowski
bool expectedValue(unsigned int n, const double* x, const double* p, double (*f)(double), double &r);
bool median(unsigned int n, const int* t, int (*f)(int), bool (*p)(int), double &r);
unsigned int gcd(unsigned int n, const int* t, int* r);
unsigned int count(unsigned int n, const int* t, bool (*p)(int, int));
