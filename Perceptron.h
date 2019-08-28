// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class TrainingSet
{
public:
	TArray<double> input;
	int input_count;
	double output;
};

class DOGBALL_PERCEPTRON_1_API Perceptron
{
public:
	TArray<TrainingSet> ts;
	TArray<double> weights = { 0, 0 };

	double bias = 0;
	double totalError = 0;

	Perceptron();
	Perceptron(TArray<TrainingSet> ts);
	~Perceptron();

	double DotProductBias(TArray<double> v, TArray<double> v2);

	double CalcOutput(int i);
	double CalcOutput(double i1, double i2);

	void InitialiseWeights();
	void UpdateWeights(int j);

	void Train();
};

