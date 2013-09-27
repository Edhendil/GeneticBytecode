/*
 * Fitness.cpp
 *
 *  Created on: 05-02-2011
 *      Author: edhendil
 *
 *  To separe fitness function from test cases
 */

#include "Fitness.h"
#include <algorithm>
#include <math.h>
#include <string>
#include <stdio.h>

int LD(unsigned char* x, unsigned int m, unsigned char* y, unsigned int n);
double normalizedLogKrugDistance(unsigned char* x, unsigned int m,
		unsigned char* y, unsigned int n);
double normalizedStringsEqual(unsigned char* x, unsigned int m,
		unsigned char* y, unsigned int n);

/**
 * compares two strings, the result varies from 0 (every character is different)
 * to length of the longer string
 * Levenshtein distance
 */
double evaluateStringFitness(unsigned char* output, unsigned int outLength,
		unsigned char* expected, unsigned int expLength) {

	//	if (outLength > expLength)
	//		return 0.0;

	return (double) normalizedStringsEqual(output, outLength, expected,
			expLength) * 100.0;

	return (double) (std::max(outLength, expLength) - LD(output, outLength,
			expected, expLength)) / (double) std::max(outLength, expLength)
			* 100;

	return (double) normalizedLogKrugDistance(output, outLength, expected,
			expLength) * 100.0;

}

double evaluateIntegerFitness(unsigned char* output, unsigned int outLength,
		unsigned char* expected, unsigned int expLength) {

	//	if (outLength > expLength)
	//		return 0.0;

	//	return (double) (std::max(outLength, expLength) - LD(output, outLength,
	//			expected, expLength)) / (double) std::max(outLength, expLength)
	//			* 100;

	for (unsigned int i = 0; i < outLength; i++) {
		if (output[i] > 57 || output[i] < 48)
			return 0.0;
	}

	if (outLength>7)
		return 0.0;

	int out = 0;
	unsigned int multi = 1;

	for (unsigned int j = 0; j < outLength; j++) {
		out += (output[outLength-j-1] - 48) * multi;
		multi *= 10;
	}

	int exp = 0;
	multi = 1;

	for (unsigned int k = 0; k < expLength; k++) {
		exp += (expected[expLength-k-1] - 48) * multi;
		multi *= 10;
	}

//	printf("%i %i\n", out, exp);

	//	return (double) normalizedLogKrugDistance(output, outLength, expected,
	//			expLength) * 100.0;
//	printf("%f\n", ((double)(exp - (abs(exp - out))) / (double)exp)*100.0);
	return ((double)(exp - (abs(exp - out))) / (double)exp)*100.0;

}

#define min(a, b) (((a) < (b)) ? (a) : (b))

// finds the minimum of tree integers
int _min(int a, int b, int c) {
	return min(min(a, b), c);
}

// allocates a 2D array of integers
int **create_matrix(int Row, int Col) {
	int **array = new int*[Row];
	for (int i = 0; i < Row; ++i) {
		array[i] = new int[Col];
	}
	return array;
}

// deallocates memory
int **delete_matrix(int **array, int Row, int Col) {
	for (int i = 0; i < Row; ++i) {
		delete array[i];
	}
	delete[] array;
	return array;
}

// computes the Levenshtein distance between two strings
// "x" represent the pattern and "y" represent the text
// "m" is the pattern length and "n" is the text length
int LD(unsigned char* x, unsigned int m, unsigned char* y, unsigned int n) {
	// if the length of the second string is zero
	// then the distance between the two strings will
	// be equal to the length of the first string
	// and vis-versa
	// if the length of both strings is equal to zero
	// then the distance between this two strings will
	// simply be zero
	if (n == 0) {
		return m;
	} else if (m == 0) {
		return n;
	}

	// creating a matrix of m+1 rows and n+1 columns
	int **matrix = create_matrix(m + 1, n + 1);

	// initialising the first row of the matrix
	for (unsigned int i = 0; i <= n; ++i) {
		matrix[0][i] = i;
	}

	// initialising the first column of the matrix
	for (unsigned int i = 0; i <= m; ++i) {
		matrix[i][0] = i;
	}

	// complementary variables for computing the "Levenshtein distance"
	unsigned int above_cell, left_cell, diagonal_cell, cost;

	// starting the main process for computing
	// the distance between the two strings "x" and "y"
	for (unsigned int i = 1; i <= m; ++i) {
		for (unsigned int j = 1; j <= n; ++j) {
			// if the current two characters
			// of both strings are the same
			// then, the corresponding cost value
			// will be zero,otherwise it will be 1
			if (x[i - 1] == y[j - 1]) {
				cost = 0;
			} else {
				cost = 1;
			}
			// current cell of the matrix: matrix[i][j]

			// finds the above cell to the current cell
			above_cell = matrix[i - 1][j];

			// finds the left cell to the current cell
			left_cell = matrix[i][j - 1];

			// finds the diagonally above cell to the current cell
			diagonal_cell = matrix[i - 1][j - 1];

			// computes the current value of the "edit distance" and place
			// the result into the current matrix cell
			matrix[i][j] = _min(above_cell + 1, left_cell + 1, diagonal_cell
					+ cost);
		}
	}
	// placing the final result into a variable
	unsigned int result = matrix[m][n];
	// freeing memory that has been used
	// for the "matrix variable"
	delete_matrix(matrix, m + 1, n + 1);
	// returning result of the search
	return result;
}

// returns infinity when strings are equal
double normalizedLogKrugDistance(unsigned char* x, unsigned int m,
		unsigned char* y, unsigned int n) {
	int dist, mini;
	mini = min(m,n);
	if (m > n)
		dist = m - n;
	else
		dist = n - m;
	dist = dist * 256;
	for (int i = 0; i < mini; i++) {
		if (x[i] > y[i])
			dist += x[i] - y[i];
		else
			dist += y[i] - x[i];
	}
	// log po to by koncowka byla wiecej warta, tzn. kazda zmiana
	// sens tylko gdy procentowa szansa na krzyzowanie
	// inaczej i tak ostatecznie dyskretne stopnie
	return ((double) log((std::max(m, n) * 256)) - log(dist)) / (double) log(
			(std::max(m, n) * 256));
}

double normalizedStringsEqual(unsigned char* x, unsigned int m,
		unsigned char* y, unsigned int n) {

	unsigned int good, mini;
	mini = min(m,n);
	good = 0;

	for (unsigned int i = 0; i < mini; i++) {
		if (x[i] == y[i])
			good++;
	}

	return ((double) good) / (double) std::max(m, n);

}
