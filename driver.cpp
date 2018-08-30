#include <stdio.h> // pre-processor directives
#include <string>      // insert the header files
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <sstream>
double learning_rate = 0.1;

using namespace std;

int learn(double* p, double x1, double x2) {
	int temp_result = (x1 * p[0]) + (x2 * p[1]) - p[2];
	int target = 0;

	if (temp_result > 0) {
		target = 1;
	}

	return target;
}

void train(double* p, double x1, double x2, int output) {
	int temp_result = (x1 * p[0]) + (x2 * p[1]) - p[2];
	int target = 0;

	if (temp_result > 0) {
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

	for (int i = 0; i < training_data.size(); i++) {
		train(p, (training_data.at(i))[0], (training_data.at(i))[1], (training_data.at(i))[2]);
	}
}

int main(int argc, char* argv[]) {

	int iterations = 1000;

	double perceptron1[3] = {1.0, 1.0, 1.0};
	double perceptron2[3] = {1.0, 1.0, 1.0};
	double perceptron3[3] = {1.0, 1.0, 1.0};

	readData(perceptron1, "or");
	readData(perceptron2, "nand");
	readData(perceptron3, "and");

	vector<vector<double>> data;

	vector<double> first;
	first.push_back(1.0); first.push_back(1.0); first.push_back(0.0);

	vector<double> second;
	second.push_back(1.0); second.push_back(0.0); second.push_back(1.0);

	vector<double> third;
	third.push_back(0.0); third.push_back(1.0); third.push_back(1.0);

	vector<double> fourth;
	fourth.push_back(0.0); fourth.push_back(0.0); fourth.push_back(0.0);

	data.push_back(first);
	data.push_back(second);
	data.push_back(third);
	data.push_back(fourth);

	for (int i = 0; i < data.size(); i++) {
		int or_result = learn(perceptron1, (data.at(i))[0], (data.at(i))[1]);

		int nand_result = learn(perceptron2, (data.at(i))[0], (data.at(i))[1]);

		int xor_result = learn(perceptron3, or_result, nand_result);

		if (xor_result == 0.0) {
			cout << "Learned correctly" << endl;
		}

		else {
			cout << "Incorrect" << endl;
		}
	}

	return 0;
}
