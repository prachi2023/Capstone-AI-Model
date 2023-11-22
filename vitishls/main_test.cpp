using namespace std;
#include "test_values_15nov_3.h"
#include "definitions.h"
#include "ap_int.h"
#include "main.h"
#include <math.h>

int main()
{
	int num_correct = 0;
	int num_tests = 100;

      for (int test = 0; test < num_tests; test ++){
	  hls::stream<ap_axis<32,2,5,6> > A, B;
	  ap_axis<32,2,5,6> tmp1, tmp2;

	  for(int j=0;j<NUM_READINGS;j++){
		 for (int i = 0; i < NUM_SAMPLES; i++){
			  ap_int<32> value =  test_values[test][j][i]*(pow(2,20));
			  tmp1.data = value;
			  A.write(tmp1);
		 }
	  }
	  model(A,B);
	  B.read(tmp2);
	  if (test_results[test] == tmp2.data){
		  num_correct += 1;
	  }
      cout << test << "| " << test_results[test] << ":" << tmp2.data << endl;
  }
  float accuracy = float(num_correct) *100 / num_tests;
  cout << "Test Accuracy: " << accuracy;
  return 0;

}
