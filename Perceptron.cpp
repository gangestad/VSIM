// Fill out your copyright notice in the Description page of Project Settings.

#include "Perceptron.h"

Perceptron::Perceptron()
{
	
}

Perceptron::Perceptron(TArray<TrainingSet> ts)
{
	this->ts = ts;
}

Perceptron::~Perceptron()
{
}

double Perceptron::DotProductBias(TArray<double> v1, TArray<double> v2)
{
	if (v1.Num() == 0 || v2.Num() == 0)
		return -1;

	if (v1.Num() != v2.Num())
		return -1;

	double d = 0;
	for (int x = 0; x < v1.Num(); x++)
	{
		d += v1[x] * v2[x];
	}

	d += bias;

	return d;
}

double Perceptron::CalcOutput(int i)
{
	double dp = DotProductBias(weights, ts[i].input);
	if (dp > 0) return(1);
	return (0);
}

double Perceptron::CalcOutput(double i1, double i2)
{
	TArray<double> inp;
	inp.Add(i1);
	inp.Add(i2);

	//int inp_count = 2;
	double dp = DotProductBias(weights, inp);
	if (dp > 0) return(1);
	return (0);
}

void Perceptron::InitialiseWeights()
{
	//srand(time(NULL));

	for (int i = 0; i < weights.Num(); i++)
	{
		weights[i] = ((float(rand()) / float(RAND_MAX)) * (1 - (-1))) + (-1);
	}
	bias = FMath::RandRange(-1, 1);
}

void Perceptron::UpdateWeights(int j)
{
	double error = ts[j].output - CalcOutput(j);
	totalError += fabs((float)error);
	for (int i = 0; i < weights.Num(); i++)
	{
		weights[i] = weights[i] + error * ts[j].input[i];
	}
	bias += error;
}

void Perceptron::Train()//int epochs)
{
	InitialiseWeights();

	totalError = 0;
	for (int t = 0; t < ts.Num(); t++)
	{
		UpdateWeights(t);
	}
}
