/* File:     exercise_test.c
 *
 * Purpose:  Unit tests for functions defined in exercise.c 
 *
 * Compile:  gcc -g -Wall -o exercise exercise.c exercise_test.c
 * Run:      ./exercise
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minunit.h"
#include "exercise.h"


/*-------------------------------------------------------------------
 * Test exchange() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *exchange_test(void){
 	int a = 1;
	int b = 7;

	//Should fail on bad input
	if(exchange(NULL, &a)) return "should fail with NULL arguments";

	//Should not fail on good input
	if(!exchange(&a, &b)) return "exchange function should execute without failiure";
	mu_assert("1st param should be value of 2nd param", a == 7);
	mu_assert("2nd param should be value of 1st param", b == 1);

	//Test passed
	return NULL;
}  

/*-------------------------------------------------------------------
 * Test reverse_array() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *reverse_array_test(void){
	int length = 7;
 	int arry[] = {1, 2, 3, 4, 5, 6, 7};
	int copy[] = {1, 2, 3, 4, 5, 6, 7};
	int *bad;
	bad = NULL;

	//Should fail on bad input
	if(reverse_array(bad, 1)) return "reverse_array should have failed with NULL array";
	if(reverse_array(arry, 0)) return "reverse_array should have failed with length of zero";

	//Function should execute with valid arguments
	if(!reverse_array(arry, length)) return "reverse_array function failed";
	
	//Should be reversed
	for (int i = 0; i < length; i++) {
		if(arry[i] != copy[length - i - 1]) return "array was not reversed correctly";
	}
	
	//Test passed
	return NULL;
}  
/*-------------------------------------------------------------------
 * Test match_add() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *match_add_test(void){
 	char *bad;
	bad = NULL;

	//Should ignore bad commands
	mu_assert("Should ignore null cmd strings", match_add(bad, 2) == 2);
	mu_assert("Should ignore bad commands", match_add("add5", 3) == 3);

	//Should compute correct addition
	mu_assert("Should add2 to 3 and result in 5", match_add("add2", 3) == 5);

	//Passed Test
	return NULL;
}  


/*-------------------------------------------------------------------
 * Test set_key_action() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
int del1(int x){
        return x-1;
}
int del2(int x){
        return x-2;
}

char * set_key_action_test(void){
	struct key_action *rec= (struct key_action *) malloc(sizeof(struct key_action));
	char *key="del1";
	int ret = set_key_action(rec, key, del1);
	mu_assert("Error in set_key_action with del1 key", strcmp(key, rec->cmd) == 0);
	mu_assert("Error in set_key_action with del1 value", rec->func == del1);
	mu_assert("Error in set_key_action with del1 value", ret == SUCC);
	ret = set_key_action(NULL, key, del1);
	mu_assert("Error in set_key_action with NULL value", ret == FAIL);

	/*All comparisons/tests are valid*/
	return NULL;
}

/*-------------------------------------------------------------------
 * Test match_action() 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */

struct key_action map[] = {
    { "del1", del1 },
    { "del2", del2 },
    { 0, 0 }
 };

char *match_action_test(void){

	//Test function
 	mu_assert("Should return 9 when cmd is NULL", match_action(map, NULL, 9) == 9);
 	mu_assert("Should return 9 when map is NULL", match_action(NULL, "del1", 9) == 9);
 	mu_assert("Should return 8 when cmd is del1", match_action(map, "del1", 9) == 8);
 	mu_assert("Should return 7 when cmd is del2", match_action(map, "del2", 9) == 7);

	//Passed tests
	return NULL;
}  
/*-------------------------------------------------------------------
 * Test if the  matrix-vector multiplicatioon result is expected.
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 * m is number of rows and n is the number of columns
 */
char*  test_vect(double y[], int m, int n){
	int i;
	double expected= n*(n-1)/2;
   	for (i = 0; i < m; i++){
#ifdef DEBUG1
		printf("Expected %f actual %f in mat_vect_mult\n", expected, y[i]); 
#endif
		mu_assert("Error in mat_vect_mult, one mismatch", y[i] ==expected); 
	}
	return NULL;
}
/*-------------------------------------------------------------------
 * Test matrix vector multiplciation 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char* mat_vect_mult_test1(int m, int n) {
	int i,j;
	char *msg;
	double *A = malloc(m*n*sizeof(double));
	double *x = malloc(n*sizeof(double));
   	double *y = malloc(m*sizeof(double));
   	for (j = 0; j < n; j++){
      		x[j]=j;
	}
   	for (i = 0; i < m; i++){
      		y[i]=0;
	}
	for (i = 0; i < m; i++){
   		for (j = 0; j < n; j++)
      			A[i*n+j]=1;
	}

   	int ret=mat_vect_mult(A, x, y, m, n);
	msg=test_vect(y, m, n);	
   	free(A);
   	free(x);
   	free(y);
	if(msg !=NULL)
		return msg;
	if(ret!=SUCC)
		return "Error in mat_vect_mult return value";
	return NULL;
}  

/*-------------------------------------------------------------------
 * Test matrix vector multiplication.
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *mat_vect_mult_test(void){
	return  mat_vect_mult_test1(2,4);
}  

char *mat_vect_mult_test_null(void){
 	double A=1; 
	int n=1;	
	int ret=mat_vect_mult(NULL, NULL, NULL, n, n);
        mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
        ret=mat_vect_mult(&A, &A, &A, 0, n);
        mu_assert("Error in mat_mat_mult, NULL input", ret ==FAIL);
	return  NULL;
}  



/*-------------------------------------------------------------------
 * Test matrix matrix multiplication 
 * If failed, return a message string showing the failed point
 * If successful, return NULL 
 */
char *mat_mat_mult_test(void){
 	int matrix_rows = 2;
	double A[] = {1,1,1,1};
	double B[] = {2,2,2,2};
	double C[] = {0,0,0,0};
	double expected[] = {4,4,4,4};

	//Should fail on NULL inputs
	mu_assert("Should fail when one or more matrix is NULL", mat_mat_mult(NULL, B, C, matrix_rows) == FAIL);
	mu_assert("Should fail when one or more matrix is NULL", mat_mat_mult(A, NULL, C, matrix_rows) == FAIL);
	mu_assert("Should fail when one or more matrix is NULL", mat_mat_mult(A, B, NULL, matrix_rows) == FAIL);

	//Should fail when matrix size is zero
	mu_assert("Should fail when matrix size is less than one", mat_mat_mult(A, B, C, 0) == FAIL);

	//Should be successful on good input
	mu_assert("Failed to successfully return for valid input", mat_mat_mult(A, B, C, matrix_rows) == SUCC);

  	for (int i = 0; i < matrix_rows * matrix_rows; ++i) {
		  mu_assert("Failed to correctly implement algorithm", (C[i] - expected[i]) == 0);
	  }
	





	return NULL;
}  
/*-------------------------------------------------------------------
 * Run all tests.  Ignore returned messages.
 */
void run_all_tests(void){
 	/* Call all tests.  You can add more tests*/
	mu_run_test(exchange_test);
	mu_run_test(reverse_array_test);
	mu_run_test(match_add_test);
	mu_run_test(set_key_action_test);
	mu_run_test(match_action_test);
	mu_run_test(mat_vect_mult_test);
	mu_run_test(mat_vect_mult_test_null);
	mu_run_test(mat_mat_mult_test);
}

/*-------------------------------------------------------------------
 * The main entrance to run all tests.  
 * If failed, return a message string showing the first failed point
 * Print the test stats
 */
int main(int argc, char* argv[]){
	run_all_tests();
	
	mu_print_test_summary("Summary:");  
	return 0;
}
