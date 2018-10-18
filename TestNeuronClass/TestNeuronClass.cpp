#include "NeuronNet_Base.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

class Base
{
public:
	virtual std::string Func() { return std::string("This is Base."); }
	void printInfo() { cout << Func() << endl; }
};

class A : public Base
{
public:
	std::string Func() { return Ff(); }
	std::string Ff() { return std::string("This is Derived"); }
};

class TestNeuronNet :public NeuronNet_Base
{
public:
	TestNeuronNet() = default;
	TestNeuronNet(const UINT inputNum, const UINT outputNum, const UINT layerNum) :
		NeuronNet_Base(inputNum, outputNum, layerNum)
	{}
	TestNeuronNet(const TestNeuronNet &) = delete;

	void EvaluateWeight() final;
};

void TestFun(Base *a)
{
	cout << a->Func() << endl;
}

void main()
{
	cout << "这是个测试程序，就酱！！ " << endl;

	NeuronNet_Base *p = new TestNeuronNet;
	cout << p->GetInputNum() << " " << p->GetOutputNum() << " " << p->GetLayerNum() << endl;
	cout << p->IsAvaliable() << endl;
	p->NewNeuronNet(6, 4, 5);
	cout << p->GetInputNum() << " " << p->GetOutputNum() << " " << p->GetLayerNum() << endl;
	std::vector<double> input = {0, 0, 1, 0, 1, 0};
	p->SetInputVector(input);
	if (p->IsAvaliable())
		cout << "NeuronNet Ready" << endl;
	else
		cout << "NotReady!!!" << endl;

	p->CalculateOutput();
	p->EvaluateWeight();
	auto out = p->GetOutputVector();
	for (auto c : out)
		cout << c << " ";
	cout << endl;

	p->SetLayerNum(8);
	p->CalculateOutput();
	out = p->GetOutputVector();
	for (auto c : out)
		cout << c << " ";
	cout << endl;

	p->SetInputNum(7);
	input = {1, 0, 1, 0, 0, 1, 0};
	p->SetInputVector(input);
	p->CalculateOutput();
	out = p->GetOutputVector();
	for (auto c : out)
		cout << c << " ";
	cout << endl;

	p->SetOutputNum(6);
	p->CalculateOutput();
	out = p->GetOutputVector();
	for (auto c : out)
		cout << c << " ";
	cout << endl;

	p->SetOutputNum(5);
	p->SetOutputNum(6);
	p->CalculateOutput();
	out = p->GetOutputVector();
	for (auto c : out)
		cout << c << " ";
	cout << endl;

	p->SetLayerOutputNum(p->GetLayerNum() / 2, 4);
	if (!p->IsAvaliable())
		cout << "Failed" << endl;
	else
	{
		p->CalculateOutput();
		out = p->GetOutputVector();
		for (auto c : out)
			cout << c << " ";
		cout << endl;
	}

	system("pause");
}

void TestNeuronNet::EvaluateWeight()
{
	cout << "Evaluated!!" << endl;
}

