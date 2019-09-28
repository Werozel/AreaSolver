#include <stdio.h>
#include <string.h>

extern double f1(double);
extern double f2(double);
extern double f3(double);

int iterations = 0;

double fabs(double x)
{
    return x > 0 ? x : -x;
}

double f0(double x)
{
	return 0;
}

double f4(double x)
{
	return x*x*x - x*x + 12;
}

double f5(double x)
{
	return x*x*x - 12*x*x + 10 * x;
}

double f6(double x)
{
	return x*x - 12;
}

double root(double (*f)(double), double (*g)(double), double a, double b, double eps1)
{
    double c = 0;
    int flag = 1;
    do
    {
        double fa = f(a), fb = f(b), ga = g(a), gb = g(b);
        double Fa = (fa - ga), Fb = (fb - gb);
        if((Fa < 0 && (f((a + b)/2) - g((a + b)/2) < (Fa + Fb) / 2)) || (Fa > 0 && (f((a + b)/2) - g((a + b)/2) > (Fa + Fb) / 2)))
            flag = 1;
        else
            flag = 2;
        c = ((a * Fb - b * Fa)/(Fb - Fa));
        switch(flag){
            case 1:
                a = c;
                break;
            case 2:
                b = c;
                break;
        }
        iterations++;
		if(iterations > 1000000){
			printf("\nToo much iterations");
			return c;
		}
    } while(flag == 1 ? (f(c) - g(c))*(f(c + eps1) - g(c + eps1)) > 0 : (f(c) - g(c))*(f(c - eps1) - g(c - eps1)) > 0);
    return c;
}

double integral(double (*f)(double), double a, double b, double eps2)
{
    double olds = 0, s = 0;
    int n = 5;
    do {
        olds = s;
        n *= 2;
        s = (f(a) + f(b)) / 2;
        for(int i = 1; i < n; i++)
        {
            s += f(a + i * ((b - a) / n));
        }
        s *= (b - a)/n;
    } while(fabs(s - olds) > eps2);
    return s;
}

void testroot(int iterflag)
{
	int f, g;
	double a, b, eps1;
	printf("f = x^3 - x^2 + 12\n");
	printf("a = ");
	scanf("%lf", &a);
	printf("b = ");
	scanf("%lf", &b);
	printf("eps1 = ");
	scanf("%lf", &eps1);
	printf("root1 = %lf\n", root(f4, f0, a, b, eps1));
	if(iterflag) printf("Number of iterations = %d\n", iterations);
	iterations = 0;
	
	printf("g = x^3 - 12 * x^2 + 10*x\n");
	printf("a = ");
	scanf("%lf", &a);
	printf("b = ");
	scanf("%lf", &b);
	printf("eps1 = ");
	scanf("%lf", &eps1);
	printf("root2 = %lf\n", root(f5, f0, a, b, eps1));
	if(iterflag) printf("Number of iterations = %d\n", iterations);
}

void testintegral()
{
    int f;
    double a, b, eps2;
	printf("f = x^2 - 12\n");
    printf("a = ");
    scanf("%lf", &a);
    printf("b = ");
    scanf("%lf", &b);
    printf("eps2 = ");
    scanf("%lf", &eps2);
    printf("integral = %lf", integral(f6, a, b, eps2));
}

int main(int argvc, char **argv){
    int helpflag = 0, iterflag = 0, rootflag = 0;
    int testrootflag = 0, testintegralflag = 0; //Флаги ключей

    if(argvc > 1)	//обработка ключей
    {
        for(int i = 1; i < argvc; i++)
        {
            if(strcmp("-testroot", argv[i]) == 0) testrootflag = 1;
            else if(strcmp("-testintegral", argv[i]) == 0) testintegralflag = 1;
            else if(strcmp("-help", argv[i]) == 0) helpflag = 1;
            else if(strcmp("-iter", argv[i]) == 0) iterflag = 1;
            else if(strcmp("-root", argv[i]) == 0) rootflag = 1;
            else {
                printf("\"%s\" is unavaliable option, here are all avaliable options:\n");
                printf(" -iter	print number of iterations\n");
                printf(" -root	print the abscissas of intersection of functions\n");
                printf("  tests:\n");
                printf("    -testroot        returns the absciss of intersection of functions f and g\n");
                printf("    -testintegral    returns the area of function f from a to b\n");
                printf(" -help	print all avaliable options\n");
                return 0;
            }
        }
        if(helpflag)
        {
            printf(" -iter	print number of iterations\n");
            printf(" -root	print the abscissas of intersection of functions\n");
            printf("  tests:\n");
            printf("    -testroot        returns the absciss of intersection of functions f and g\n");
            printf("    -testintegral    returns the area of function f from a to b\n");
            printf(" -help	print all avaliable options\n");
            return 0;
        }
        if(testrootflag)
        {
            testroot(iterflag);
            return 0;
        }
        if(testintegralflag)
        {
            testintegral();
            return 0;
        }
    }
    double root12 = root(f1, f2, 2.5, 6, 0.00000001);
    if(iterflag)
    {
        printf("Number of iterations of the root search f1 = f2: %d\n", iterations);
        iterations = 0;
    }
    double root23 = root(f2, f3, 2, 4, 0.00000001);
    if(iterflag)
    {
        printf("Number of iterations of the root search f2 = f3: %d\n", iterations);
        iterations = 0;
    }
    double root13 = root(f1, f3, 0.5, 2, 0.00000001);
    if(iterflag)
    {
        printf("Number of iterations of the root search f1 = f3: %d\n", iterations);
        iterations = 0;
    }
    if(rootflag)
    {
        printf("Root of f1 = f2: %lf\n", root12);
        printf("Root of f2 = f3: %lf\n", root23);
        printf("Root of f1 = f3: %lf\n", root13);
    }
    double integral1 = integral(f1, root13, root12, 0.00000001);
    double integral2 = integral(f2, root23, root12, 0.00000001);
    double integral3 = integral(f3, root13, root23, 0.00000001);
    printf("Area = %lf\n", integral1 - integral2 - integral3);

    return 0;
}