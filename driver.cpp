#include <stdio.h> // pre-processor directives
#include <string>      // insert the header files
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
double learning_rate = 0.01;

using namespace std;

void train(double* p, double x1, double x2, int output) {
	int temp = (x1 * p[0]) + (x2 * p[1]) - p[2];
	int target = 0;

	if (temp > 0) {
		target = 1;
	}

	p[0] += (learning_rate * (target - output) * x1);
	p[1] += (learning_rate * (target - output) * x2);
	p[2] += (learning_rate * (target - output));
}

void readData(double* p, string filename) {
	ifstream input_file(filename.c_str());

	vector<vector<double>> training_data;

	double in1, in2;
	int output;

	if (input_file.is_open()) {
		string line;
		while (getline(input_file, line)) {
			stringstream example(line);
			
			vector<double> data;

			for (int i = 0; i < 3; i++) {
				double input;
				example >> input;
				data.push_back(input);
			}

			training_data.push_back(data);
		}
	}

	else {
		cout << "Couldn't open file." << endl;
	}
	input_file.close();

	int iterations = 100;
	while (iterations >= 0) {

		for (int i = 0; i < training_data.size(); i++) {
			train(p, (training_data.at(i))[0], (training_data.at(i))[1], (training_data.at(i))[2]);
		}
		iterations--;
	}
}

int main(int argc, char* argv[]) {

	int iterations = 1000;

	double perceptron1[3] = {1.0, 1.0, 1.0};
	double perceptron2[3] = {1.0, 1.0, 1.0};
	double perceptron3[3] = {1.0, 1.0, 1.0};

	readData(perceptron1, "or");

	for (int i = 0; i < 3; i++) {
		cout << perceptron1[i] << endl;
	}

	//train(perceptron2, "nand");
	//train(perceptron3, "and");

	return 0;
}
