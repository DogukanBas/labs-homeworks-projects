#include <stdio.h>

#include <math.h>

#define MAX 50
#define EPSILON 0.000001


/*
EXTRAS
gauss seidal code works perfect even in matrixes such as:
1 5 3
2 2 4
3 6 8 
because it arranges the matrix in a way to get the max diagonal (heap algorithm used.)

matrix inverse code checks if the determinant is 0 so it prints NO INVERSE if there is no inverse..

Gauss elimination is implemented as gauss jordan. It also checks if determinant is 0 so it prints 3 cases 1)UNIQUE SOLUTION(prints the solution) 2) prints INFINITE AMOUNT OF SOLUTIONS 3) prints NO SOLUTION AVAILABLE



*/

typedef struct Polynomial {
    double coefficient;
    int degree;
}
polynomial;

int menu();

int getPolynomial(polynomial p1[]);
void sortPolynomial(polynomial p1[], int);
void printPolynomial(polynomial p1[], int);
double calculatePolynomial(polynomial p1[], double, int);
int calculateDerivative(polynomial p1[], polynomial p2[], int);

double regulaFalsi(polynomial p1[], int);
double bisectionMethod(polynomial p1[], int);
double newtonRaphsonMethod(polynomial p1[], polynomial p2[], int, int);
int inverseMatrixFunc(double matrix[MAX][MAX], double inverseMatrix[MAX][MAX], int n);
void gaussElemination(double matrix[MAX][MAX], double solution[]);
void gaussSeidel(double matrix[MAX][MAX]);
void heapPermutation(int a[], int size, int n, int * k, int permutationMatrix[MAX][MAX]);
int maxDiagonal(double mainMatrix[MAX][MAX]);
double numericalDifferentiation(polynomial p1[], int elementCount);
void simpsonMethod(polynomial p1[], int elementCount);
void trapezoidalMethod(polynomial p1[], int elementCount);
void gregoryNewton(double matrix[MAX][MAX]);

int main() {
    int method, elementCount, derivativeElementCount, n, i, j;
    double matrix[MAX][MAX], inverseMatrix[MAX][MAX] = {
        0
    }, solution[MAX];
    double answer;

    //p1 for polynomial and p2 for derivative of the polynomial
    polynomial p1[MAX], p2[MAX];

    method = menu();
    switch (method) {
    case 1:

        elementCount = getPolynomial(p1);
        sortPolynomial(p1, elementCount);
        printf("\nThe Function:");
        printPolynomial(p1, elementCount);
        answer = bisectionMethod(p1, elementCount);
        printf("\n\nEstimated root:%lf", answer);
        break;
    case 2:
        elementCount = getPolynomial(p1);
        sortPolynomial(p1, elementCount);
        printf("\nThe Function:");
        printPolynomial(p1, elementCount);
        answer = regulaFalsi(p1, elementCount);
        printf("\n\nEstimated root:%lf", answer);
        break;

    case 3:

        elementCount = getPolynomial(p1);
        sortPolynomial(p1, elementCount);
        printf("\nThe Function:");
        printPolynomial(p1, elementCount);
        derivativeElementCount = calculateDerivative(p1, p2, elementCount);
        printf("\nDerivative of the function:");
        printPolynomial(p2, derivativeElementCount);
        printf("\n");
        answer = newtonRaphsonMethod(p1, p2, elementCount, derivativeElementCount);
        printf("%lf", answer);
        break;
    case 4:
        printf("enter n:");
        scanf("%d", & n);
        answer = inverseMatrixFunc(matrix, inverseMatrix, n);
        if (answer == 0) {
            printf("The matrix is not invertable...");
        } else if (answer == 1) {
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                    printf("%lf ", inverseMatrix[i][j]);
                }
                printf("\n");
            }
        }
        break;

    case 5:
        gaussElemination(matrix, solution);
        break;
    case 6:
        gaussSeidel(matrix);
        break;

    case 7:
        elementCount = getPolynomial(p1);
        sortPolynomial(p1, elementCount);
        printf("\nThe function:");
        printPolynomial(p1, elementCount);

        printf("Estimated derivative= %lf", numericalDifferentiation(p1, elementCount));
        break;

    case 8:
        elementCount = getPolynomial(p1);
        sortPolynomial(p1, elementCount);
        printf("\nThe function:");
        printPolynomial(p1, elementCount);;

        simpsonMethod(p1, elementCount);
        break;

    case 9:
        elementCount = getPolynomial(p1);
        sortPolynomial(p1, elementCount);
        printf("\nThe function:");
        printPolynomial(p1, elementCount);

        trapezoidalMethod(p1, elementCount);
        break;

    case 10:
        gregoryNewton(matrix);
        break;

    default:
        printf("Invalid choice..");
    }

    return 0;
}
double bisectionMethod(polynomial p1[], int elementCount) {
    double error, realValue, a, b, c, expectedError;
    int n = 0, errorType = 0;

    printf("If you are going to give the real root to the programme enter 1, otherwise enter 0:");
    scanf("%d", & errorType);

    if (errorType == 1) {
        printf("Real root:");
        scanf("%lf", & realValue);

    }
    printf("Enter the expected error margin");
    scanf("%lf", & expectedError);
    printf("Beggining point of the interval(a):");
    scanf("%lf", & a);
    printf("Ending point of the interval(b)");
    scanf("%lf", & b);

    if ((calculatePolynomial(p1, a, elementCount) * calculatePolynomial(p1, b, elementCount)) > 0) {
        printf("Invalid range");

    } else {
        do {
            n = n + 1;

            c = (a + b) / 2;

            if ((calculatePolynomial(p1, a, elementCount) * calculatePolynomial(p1, c, elementCount)) < 0) {
                b = c;
            } else if ((calculatePolynomial(p1, b, elementCount) * calculatePolynomial(p1, c, elementCount)) < 0) {
                a = c;
            }
            if (errorType == 1) {
                error = fabs(realValue - c);
            } else if (errorType == 0) {
                error = (b - a) / (pow(2, n));
            }

        } while (error > expectedError);

        return c;

    }
}
double regulaFalsi(polynomial p1[], int elementCount) {
    double error, realValue, a, b, c, expectedError;
    int n = 0, errorType = 0;

    printf("If you are going to give the real root to the programme enter 1, otherwise enter 0:");
    scanf("%d", & errorType);

    if (errorType == 1) {
        printf("Real root:");
        scanf("%lf", & realValue);
    }
    printf("Enter the expected error margin");
    scanf("%lf", & expectedError);
    printf("Beggining point of the interval(a):");
    scanf("%lf", & a);
    printf("Ending point of the interval(b)");
    scanf("%lf", & b);

    if ((calculatePolynomial(p1, a, elementCount) * calculatePolynomial(p1, b, elementCount)) > 0) {
        printf("Invalid range.");

    } else {
        do {
            n = n + 1;

            c = (a * (calculatePolynomial(p1, b, elementCount)) - b * (calculatePolynomial(p1, a, elementCount))) / ((calculatePolynomial(p1, b, elementCount)) - (calculatePolynomial(p1, a, elementCount)));

            if ((calculatePolynomial(p1, a, elementCount) * calculatePolynomial(p1, c, elementCount)) < 0) {
                b = c;
            } else if ((calculatePolynomial(p1, b, elementCount) * calculatePolynomial(p1, c, elementCount)) < 0) {
                a = c;

            }
            if (errorType == 1) {
                error = fabs(realValue - c);
            } else if (errorType == 0) {
                error = (b - a) / (pow(2, n));
            }

        } while (error > expectedError);

        return c;

    }
}
double newtonRaphsonMethod(polynomial p1[], polynomial p2[], int elementCount, int derivativeElementCount) {

    double error, realValue, a, b, x, expectedError, temp;
    int n = 0, errorType, control;

    printf("If you are going to give the real root to the programme enter 1, otherwise enter 0:");
    scanf("%d", & errorType);

    if (errorType == 1) {
        printf("Real root:");
        scanf("%lf", & realValue);

    }
    printf("Error margin:");
    scanf("%lf", & expectedError);

    printf("Beggining point of the interval(a):");
    scanf("%lf", & a);
    x = a;
    printf("Ending point of the interval(b)");
    scanf("%lf", & b);

    if (calculatePolynomial(p1, a, elementCount) * calculatePolynomial(p1, b, elementCount) > 0) {
        printf("Invalid range.");
    } else {
        printf("If you are going to give the initial x press 1 otherwise press 0 (%lf will be considered as the initial x if you press 0):", a);
        scanf("%d", & control);
        if (control == 1) {
            printf("Initial x:");
            scanf("%lf", & x);
        }
        do {
            temp = x;
            x = x - (calculatePolynomial(p1, x, elementCount) / calculatePolynomial(p2, x, derivativeElementCount));
            if (errorType == 1) {
                error = fabs(x - realValue);

            } else {
                error = fabs(x - temp);
            }

        } while (error > expectedError);

        return x;
    }
}
int inverseMatrixFunc(double matrix[MAX][MAX], double inverseMatrix[MAX][MAX], int n) {
    double columnDivisionValue, rowDivisionValue, temp;
    int i, j, k, z, control, row, column;

    //setting diagonals of the idenity matrix to 1
    for (i = 0; i < n; i++) {
        inverseMatrix[i][i] = 1;
        for (j = 0; j < n; j++) {
            printf("Insert: %d th row and %dth column:", i + 1, j + 1);
            scanf("%lf", & matrix[i][j]);

        }
    }

    control = 1;
    i = 0;
    row = 0;
    while (control == 1 && i < n) {
        //if we have a 0 in the diagonal
        if (fabs(matrix[i][i]) < EPSILON) { // if its 0 but 1- 3*0.33333 is not 0 for computers =) we have an epsilon value
            row = i + 1;
            control = 0;
            while (row < n && control == 0) {
                if (fabs(matrix[row][i]) > EPSILON) {
                    //switch rows
                    for (column = 0; column < n; column++) {
                        temp = matrix[i][column];
                        matrix[i][column] = matrix[row][column];
                        matrix[row][column] = temp;

                        temp = inverseMatrix[i][column];
                        inverseMatrix[i][column] = inverseMatrix[row][column];
                        inverseMatrix[row][column] = temp;
                    }
                    control = 1;
                }
                row++;
            }
        }
        //this means we have gone through the entire matrix and couldnt find a suitable row where ith diagonal is not 0 that means we have at least 1 row full of 0.. 
        if (control == 0) {
            return 0;
        } else {

            //the pivot has to be 1, so we have to divide all by the pivot
            rowDivisionValue = matrix[i][i];

            for (j = 0; j < n; j++) {
                //getting the diagonnals 1 ,so dividing the entire row by the pivot
                matrix[i][j] = matrix[i][j] / rowDivisionValue;
                inverseMatrix[i][j] = inverseMatrix[i][j] / rowDivisionValue;
            }
            for (k = 0; k < n; k++) {
                if (k != i) {
                    //getting the entire column 0 except the i'th row.
                    columnDivisionValue = matrix[k][i];
                    for (z = 0; z < n; z++) {

                        matrix[k][z] = matrix[k][z] - (columnDivisionValue * matrix[i][z]);
                        inverseMatrix[k][z] = inverseMatrix[k][z] - (columnDivisionValue * inverseMatrix[i][z]);
                    }
                }
            }
        }
        i++;
    }
    return control;

}
void gaussElemination(double matrix[MAX][MAX], double solution[MAX]) {
    int i, j, z, k, n, row, column, control, rowOfZeroes;
    double rowDivisionValue, columnDivisionValue, temp;
    printf("n:");
    scanf("%d", & n);

    for (i = 0; i < n; i++) {
        printf("unknowns of the %dth equation...\n", i + 1);
        for (j = 0; j < n; j++) {
            printf("%dth unknown", j + 1);
            scanf("%lf", & matrix[i][j]);

        }
    }
    printf("Coefficient matrix\n");
    for (i = 0; i < n; i++) {
        printf("result of the %dth equation:", i + 1);
        scanf("%lf", & matrix[i][j]);
    }

    control = 1;
    i = 0;
    while (control == 1 && i < n) {
        if (fabs(matrix[i][i]) < EPSILON) {
            row = i + 1;
            control = 0;
            while (row < n && control == 0) {
                if (fabs(matrix[row][i]) > EPSILON) {
                    //switch rows
                    for (column = 0; column <= n; column++) {
                        temp = matrix[i][column];
                        matrix[i][column] = matrix[row][column];
                        matrix[row][column] = temp;

                    }
                    control = 1;
                }
                row++;
            }
        }

        if (control == 1) {
            rowDivisionValue = matrix[i][i];
            for (j = 0; j <= n; j++) {
                matrix[i][j] = matrix[i][j] / rowDivisionValue;
            }

            for (k = 0; k < n; k++) {
                if (k != i) {
                    //getting the entire column 0 except the i'th row.
                    columnDivisionValue = matrix[k][i];
                    for (z = 0; z <= n; z++) {
                        matrix[k][z] = matrix[k][z] - (columnDivisionValue * matrix[i][z]);

                    }
                }
            }

        }
        i++;

    }

    printf("\nThe augmented gauss-jordan matrix..\n");
    for (i = 0; i < n; i++) {
        printf("\n");
        for (j = 0; j <= n; j++) {
            printf("%6.2lf", matrix[i][j]);
        }
    }
    printf("\n");

    //this means we have gone throught the entire matrix and couldnt find a suitable row. where ith diagonal is not 0

    if (control == 0) {
        rowOfZeroes = 0;
        i = 0;
        while (i < n && control == 0) {
            rowOfZeroes = 0;
            for (j = 0; j < n; j++) {
                if (fabs(matrix[i][j]) < EPSILON) {
                    rowOfZeroes++;
                }
            }
            if ((rowOfZeroes == n) && (fabs(matrix[i][n]) > EPSILON)) {
                control = 1;
            }
            i++;
        }
        if (control == 1) {
            printf("NO SOLUTION AVALIABLE");
        } else if (control == 0) {
            printf("INFINITE AMOUNT OF SOLUTIONS");

        }
    } else {
        printf("\nTHE ROOTS:\n");
        for (i = 0; i < n; i++) {
            printf("%6.2lf", matrix[i][n]);
            printf("\n");
        }

    }
}
void gaussSeidel(double matrix[MAX][MAX]) {
    int i, j, k, n, control, maxIteration, iteration = 0;
    double solution[MAX], errorArray[MAX], expectedError, sum, newSolution;

    n = maxDiagonal(matrix);
    printf("error margin:");
    scanf("%lf", & expectedError);
    printf("maximum iterations:");
    scanf("%d", & maxIteration);
    //initializing the error array in a way that it would enter the loop
    for (i = 0; i < n; i++) {
        errorArray[i] = expectedError + 1;
    }
    for (i = 0; i < n; i++) {
        printf("initial value for the %dth unknown:", i + 1);
        scanf("%lf", & solution[i]);
    }
    control=1;

    while (control==1 && iteration < maxIteration) {
        printf("%d.iteration\n ------------\n", iteration + 1);
        for (k = 0; k < n; k++) {

            printf("%d. unknown:%lf\n\n", k + 1, solution[k]);
        }
        for (i = 0; i < n; i++) {
            if (errorArray[i] > expectedError) {
                sum = 0;
                for (j = 0; j < n; j++) {
                    if (j != i) {
                        sum = sum + solution[j] * matrix[i][j];

                    }
                }

                newSolution = (matrix[i][n] - sum) / matrix[i][i];
                errorArray[i] = fabs(newSolution - solution[i]);
                solution[i] = newSolution;
            } else {
                errorArray[i] = -1;
            }
        }
        control = 0;
        k = 0;
        while (control == 0 && k < n) {
            if (errorArray[k] != -1) {
                control = 1;
            }
            k++;
        }

        iteration++;
    }
    printf("THE MATRIX\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j <= n; j++) {
            printf("%6.2lf", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\nRESULT\n\n");
    for (k = 0; k < n; k++) {
        printf("%dth unknown:%lf\n", k + 1, solution[k]);
    }

}
void heapPermutation(int a[], int size, int n, int * k, int permutationMatrix[MAX][MAX]) {
    int temp, j, i;
    if (size == 1) {
        for (i = 0; i < n; i++) {
            permutationMatrix[ * k][i] = a[i];
        }
        * k = * k + 1;
        return;
    }

    for (i = 0; i < size; i++) {
        heapPermutation(a, size - 1, n, k, permutationMatrix);

        if (size % 2 == 1) {
            temp = a[0];
            a[0] = a[size - 1];
            a[size - 1] = temp;
        } else {
            temp = a[i];
            a[i] = a[size - 1];
            a[size - 1] = temp;
        }
    }
}

int maxDiagonal(double mainMatrix[MAX][MAX]) {
    double matrix[MAX][MAX], diagonalProduct, largestDiagonalProduct;
    int permutationMatrix[MAX][MAX], largestDiagonalIndexes[MAX], a[MAX], i, j, n, f, row, column, index;
    int * k;
    f = 0;
    k = & f;
    printf("n:");
    scanf("%d", & n);
    for (i = 0; i < n; i++) {
        printf("unknowns of the %dth equation...\n", i + 1);
        for (j = 0; j < n; j++) {
            printf("%dth unknown:", j + 1);
            scanf("%lf", & matrix[i][j]);
        }
    }
    printf("Coefficient matrix\n");
    for (i = 0; i < n; i++) {
        printf("result of the %dth equation:", i + 1);
        scanf("%lf", & matrix[i][j]);
    }
    for (i = 0; i < n; i++) {
        a[i] = i;
    }

    heapPermutation(a, n, n, k, permutationMatrix);

    //code to arrange the matrix in a way to get the largest diagonal.    
    for (i = 0; i < n; i++) {
        largestDiagonalIndexes[i] = i;
    }
    largestDiagonalProduct = 0;

    for (row = 0; row < f; row++) {
        diagonalProduct = 1;
        for (index = 0; index < n; index++) {
            diagonalProduct *= fabs(matrix[permutationMatrix[row][index]][index]);
        }
        if (diagonalProduct > largestDiagonalProduct) {
            largestDiagonalProduct = diagonalProduct;
            for (column = 0; column < n; column++) {
                largestDiagonalIndexes[column] = permutationMatrix[row][column];
            }
        }

    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n + 1; j++) {
            mainMatrix[i][j] = matrix[largestDiagonalIndexes[i]][j];
        }
    }

    return n;

}
double numericalDifferentiation(polynomial p1[], int elementCount) {
    int choice;
    double h, x, result;
    printf("\n\n");
    printf("Backward differentiation: 1\nCentral differentiation: 2\nForward Differentiation: 3\n");
    scanf("%d", & choice);
    printf("for which x value do you want to calculate the derivative:");
    scanf("%lf", & x);
    printf("\n");
    printf("h:");
    scanf("%lf", & h);
    printf("\n\n");

    if (choice == 1) {
        result = (calculatePolynomial(p1, x, elementCount) - calculatePolynomial(p1, x - h, elementCount)) / h;

    } else if (choice == 2) {
        result = (calculatePolynomial(p1, x + h, elementCount) - calculatePolynomial(p1, x - h, elementCount)) / (2 * h);

    } else if (choice == 3) {
        result = (calculatePolynomial(p1, x + h, elementCount) - calculatePolynomial(p1, x, elementCount)) / h;

    }

    return result;

}
void simpsonMethod(polynomial p1[], int elementCount) {
    double a, b, h, currentX, sum, counter, lastRoot, n;
    int i;
    printf("Starting point of the interval (a):");
    scanf("%lf", & a);
    printf("Ending point of the interval (b):");
    scanf("%lf", & b);
    printf("Enter the amount of subdivisions(n) (For both simpson 1/3 and 3/8 to converge, the amount of subdivisions has to be a factor of 6):");
    scanf("%lf", & n);

    //simpson 1/3
    sum = calculatePolynomial(p1, a, elementCount) + calculatePolynomial(p1, b, elementCount);
    lastRoot = a;
    h = (b - a) / n;
    for (i = 0; i < n - 1; i++) {
        currentX = lastRoot + h;
        if (i % 2 == 0) {
            sum = sum + 4 * (calculatePolynomial(p1, currentX, elementCount));
        } else {
            sum = sum + 2 * (calculatePolynomial(p1, currentX, elementCount));
        }
        lastRoot = currentX;
    }
    printf("Calculated integral for simpson 1/3:");
    printf("%lf", sum * h / 3);

    //simpson 3/8
    sum = calculatePolynomial(p1, a, elementCount) + calculatePolynomial(p1, b, elementCount);
    lastRoot = a;
    h = (b - a) / n;
    for (i = 0; i < n - 1; i++) {
        currentX = lastRoot + h;
        if (i % 3 == 2) {
            sum = sum + 2 * (calculatePolynomial(p1, currentX, elementCount));
        } else {
            sum = sum + 3 * (calculatePolynomial(p1, currentX, elementCount));
        }
        lastRoot = currentX;
    }
    printf("\nCalculated integral for simpson 3/8:");
    printf("%lf", sum * 3 * h / 8);

}
void trapezoidalMethod(polynomial p1[], int elementCount) {

    double a, b, h, sum, counter, lastRoot, n, currentX;
    int i;
    printf("Starting point of the interval (a):");
    scanf("%lf", & a);
    printf("Ending point of the interval (b):");
    scanf("%lf", & b);
    printf("Enter the amount of subdivisions(n):");
    scanf("%lf", & n);

    sum = (calculatePolynomial(p1, a, elementCount) + calculatePolynomial(p1, b, elementCount)) / 2;
    currentX = a;
    h = (b - a) / n;
    for (i = 0; i < n - 1; i++) {
        currentX += h;
        sum = sum + (calculatePolynomial(p1, currentX, elementCount));
    }
    printf("Calculated integral for trapezoidal method:");
    printf("%lf", sum * h);
}

void gregoryNewton(double matrix[MAX][MAX]) {
    int n, i, j;
    double factorialCounter, x, factor, result, x0, h, s;
    printf("Amount of values to be given:");
    scanf("%d", & n);
    printf("x0:");
    scanf("%lf", & x0);
    printf("h:");
    scanf("%lf", & h);
    for (i = 0; i < n; i++) {
        printf("value of f(%.2lf):", x0 + h * i);
        scanf("%lf", & matrix[i][0]);
    }

    for (i = 1; i < n; i++) {
        for (j = i; j < n; j++) {
            matrix[j][i] = matrix[j][i - 1] - matrix[j - 1][i - 1];
        }
    }

    printf("------------------\n");
    printf("DIFFERENCE TABLE\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("for which x value would you like to calculate the function:");
    scanf("%lf", & x);

    factorialCounter = 1;
    result = matrix[0][0];
    s = (x - x0) / (h);
    factor = s;
    printf("--------------------\n");
    printf("Function:\n");
    printf("%.2lf", matrix[0][0]);
    for (i = 1; i < n; i++) {
        printf(" + ");
        printf("%.2lf", matrix[i][i] / factorialCounter);
        for (j = 0; j < i; j++) {
            printf("*(((x-%.2lf)/%.2lf)-%d)", x0, h, j);
        }
        result = result + factor * matrix[i][i] / factorialCounter;
        factorialCounter = factorialCounter * (i + 1);
        factor = factor * (s - i);

    }
    printf("\n\nresult: %lf", result);

}
int calculateDerivative(polynomial p1[], polynomial p2[], int elementCount) {
    int i;
    int derivativeElementCount = elementCount;
    for (i = 0; i < elementCount; i++) {
        if (p1[i].degree != 0) {
            p2[i].coefficient = p1[i].coefficient * p1[i].degree;
            p2[i].degree = p1[i].degree - 1;
        } else {
            derivativeElementCount -= 1;
        }

    }
    return derivativeElementCount;
}
int getPolynomial(polynomial p1[]) {
    int elementCount, i;
    printf("Amount of elements:");
    scanf("%d", & elementCount);
    for (i = 0; i < elementCount; i++) {
        printf("coefficient of the %dth element:", i + 1);
        scanf("%lf", & p1[i].coefficient);
        printf("degree of the %dth element:", i + 1);
        scanf("%d", & p1[i].degree);

    }
    return elementCount;
}
double calculatePolynomial(polynomial p1[], double x, int elementCount) {
    int i, j;
    double value = 0, temp = 1;

    for (i = 0; i < elementCount; i++) {
        temp = 1;
        for (j = 0; j < p1[i].degree; j++) {
            temp = temp * x;
        }
        value = value + p1[i].coefficient * temp;
    }
    return value;
}
void sortPolynomial(polynomial p1[], int elementCount) {
    //bubble sort 
    int i = 0, j, control = 1;
    polynomial temp;
    while (control == 1 && i < elementCount - 1) {
        control = 0;

        for (j = 0; j < elementCount - i - 1; j++) {
            if (p1[j + 1].degree > p1[j].degree) {
                control = 1;
                temp = p1[j + 1];
                p1[j + 1] = p1[j];
                p1[j] = temp;
            }
        }
        i = i + 1;
    }
}
void printPolynomial(polynomial p1[], int elementCount) {
    int i;
    for (i = 0; i < elementCount - 1; i++) {
        printf("%2.2fx^%d + ", p1[i].coefficient, p1[i].degree);
    }
    printf("%2.2fx^%d\n", p1[i].coefficient, p1[i].degree);
}
int menu() {
    int method, elementCount;
    printf("Bisection Method:1\nRegula-Falsi Method:2 \nNewton-Raphson Method:3 \n"
        "Inverse of a matrix:4\nGauss-Jordan elimination:5\nGauss seidel Method:6\nNumerical Differentiation:7\nSimpson Method:8\n"
        "Trapezoidal Method:9\nGregory Newton Interpolation:10\nMethod of choice:");
    scanf("%d", & method);
    return method;
}
