#ifndef NEURALNET_H
#define NEURALNET_H

#include <iostream>
#include <cmath>
#include <cstdlib>

#define LEARNING_RATE 0.2

using namespace std;

class NeuralNet
{
private:
    double m_xin;
    double m_yout;
    double m_zop;
    double m_delta;
    double m_eta;
    double m_w;
    double m_e;

    double  transferFunction(const double&);
    double  transferFunctionDerivative(const double&);
    void    feedForward();
    void    backPropagation();
    double  invLogisticFunction(const double&);
    double  normalWeight(const double&);

public:
	NeuralNet();
	~NeuralNet();
    double train(const double& weight, const int& value);
};

#endif
