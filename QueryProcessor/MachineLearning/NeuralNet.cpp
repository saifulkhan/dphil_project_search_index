#include "NeuralNet.h"

NeuralNet::NeuralNet()
{
    m_xin   = 1.0;
    m_eta   = LEARNING_RATE;
    m_yout  = 0.0;
    m_zop   = 0.0;
    m_delta = 0.0;
    m_w     = 0.0;
    m_e     = 0.0;
}


NeuralNet::~NeuralNet()
{
}


double NeuralNet::train(const double& weight, const int& value)
{
    cout << endl; cout << __PRETTY_FUNCTION__ << endl;
    m_w   = this->invLogisticFunction(weight);
    m_zop = (value > 0) ? 1.0 : 0.0;

    for (unsigned i = 0; i < abs(value); ++i)
    {
        this->feedForward();
        this->backPropagation();
    }
    cout << " Trained." << endl;
    return this->normalWeight(m_w);
}


void NeuralNet::feedForward()
{
    m_xin   = 1.0;
    m_e     = m_xin * m_w;
    m_yout  = this->transferFunction(m_e);
}


void NeuralNet::backPropagation()
{
    m_delta = m_zop - m_yout;
    m_w     = m_w + (m_eta * m_delta * this->transferFunctionDerivative(m_e) * m_xin);
    cout << m_w << ", ";
}

double NeuralNet::transferFunctionDerivative(const double& x)
{
    // tanh derivative
    // return 1.0 - x * x;

    double sx = this->transferFunction(x);
    return  sx * (1 - sx);
}


double NeuralNet::transferFunction(const double& x)
{
    //tanh - output range [-1.0..1.0]
    //return tanh(x);

    // Sigmoid op range [0.0 - 1.0]
    return 1.0 / (1.0 + exp(-x));
}


double NeuralNet::invLogisticFunction(const double& x)
{
    return -log(1 / x - 1);
}

double NeuralNet::normalWeight(const double &w)
{
    return this->transferFunction(w);
}
