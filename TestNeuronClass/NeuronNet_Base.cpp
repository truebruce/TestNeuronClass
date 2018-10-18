#include "NeuronNet_Base.h"
#include <ctime>
#include <stdexcept>

NeuronNet_Base::~NeuronNet_Base()
{
}

NeuronNet_Base::NeuronNet_Base(const UINT inputNum, const UINT outputNum, const UINT layerNum)   // 构造拥有inputNum个输入和outputNum个输出的LayerNum层神经网络
{
	if (inputNum*outputNum*layerNum == 0)
		throw std::invalid_argument("Zero_Parameter_Exception");

	this->nn_iInputNum = inputNum;
	this->nn_iOutputNum = outputNum;
	this->nn_iLayerNum = layerNum;
	this->nn_mtInputVector.NewMatrix(nn_iInputNum, _Type::HVECTOR);

	this->nn_vecNeuronNetWeight.push_back(diyCMatrix(nn_iInputNum, nn_iOutputNum, 0));
	this->nn_vecNeuronLayerPara.push_back(LayerPara(nn_iInputNum, nn_iOutputNum));
	for (int i = 1; i < nn_iLayerNum; ++i)
	{
		this->nn_vecNeuronNetWeight.push_back(diyCMatrix(nn_iOutputNum, nn_iOutputNum, 0));
		this->nn_vecNeuronLayerPara.push_back(LayerPara(nn_iOutputNum, nn_iOutputNum));
	}

	this->Initialization();
}

bool NeuronNet_Base::Validate()   // 验证矩阵是否正确
{
	for (int i = 0; i < nn_iLayerNum; ++i)
	{
		if (nn_vecNeuronNetWeight[i].n != nn_vecNeuronLayerPara[i].LayerInputNum || 
			nn_vecNeuronNetWeight[i].m != nn_vecNeuronLayerPara[i].LayerOutputNum)
			return false;
	}

	if (nn_mtInputVector.m != nn_iInputNum)
		return false;

	if (nn_vecNeuronLayerPara.size() != nn_vecNeuronNetWeight.size())
		return false;

	return true;
}

void NeuronNet_Base::Initialization()   // 初始化网络，将所有权重用随机数初始化
{
	::InitRand();
	for (int a = 0; a < this->nn_iLayerNum; ++a)
		for (int i = 0; i < this->nn_vecNeuronLayerPara[a].LayerInputNum; ++i)
			for (int j = 0; j < this->nn_vecNeuronLayerPara[a].LayerOutputNum; ++j)
				this->nn_vecNeuronNetWeight[a].SetElement(i, j, ::RandDouble(-0.2, 0.2));
}

void NeuronNet_Base::Initialization(const int WeightID)   // 初始化第WeightID个权重矩阵
{
	::InitRand();
	for (int i = 0; i < this->nn_vecNeuronLayerPara[WeightID].LayerInputNum; ++i)
		for (int j = 0; j < this->nn_vecNeuronLayerPara[WeightID].LayerOutputNum; ++j)
			this->nn_vecNeuronNetWeight[WeightID].SetElement(i, j, ::RandDouble(-0.2, 0.2));
}

void NeuronNet_Base::ActivationFunction(diyCMatrix &Out)
{
	if (Out.n != 1)
		throw std::length_error("Vector_Type_Mismatch");

	for (int i = 0; i < Out.m; ++i)
		Out.SetElement(0, i, Out[0][i] > 0 ? 1 : 0);
}

void NeuronNet_Base::CalculateOutput()   // 计算输出
{
	if (!this->Validate())
		throw std::logic_error("Matrix_Size_Mismatch");

	diyCMatrix _tOut;
	diyCMatrix _tIn(this->nn_mtInputVector);

	for (auto c : this->nn_vecNeuronNetWeight)
	{
		_tOut = _tIn * c;
		ActivationFunction(_tOut);
		_tIn = _tOut;
	}

	this->nn_mtOutputVector = _tOut;
}

void NeuronNet_Base::NewNeuronNet(const UINT inputNum, const UINT outputNum, const UINT layerNum)   // 新建有inputNum个输入和outputNum个输出的LayerNum层神经网络
{
	if (inputNum*outputNum*layerNum == 0)
		throw std::invalid_argument("Zero_Parameter_Exception");

	if (this->IsAvaliable())
		this->ClearNeuronNet();

	this->nn_iInputNum = inputNum;
	this->nn_iOutputNum = outputNum;
	this->nn_iLayerNum = layerNum;
	this->nn_mtInputVector.NewMatrix(nn_iInputNum, _Type::HVECTOR);

	this->nn_vecNeuronNetWeight.push_back(diyCMatrix(nn_iInputNum, nn_iOutputNum, 0));
	this->nn_vecNeuronLayerPara.push_back(LayerPara(nn_iInputNum, nn_iOutputNum));
	for (int i = 1; i < nn_iLayerNum; ++i)
	{
		this->nn_vecNeuronNetWeight.push_back(diyCMatrix(nn_iOutputNum, nn_iOutputNum, 0));
		this->nn_vecNeuronLayerPara.push_back(LayerPara(nn_iOutputNum, nn_iOutputNum));
	}

	this->Initialization();
}

void NeuronNet_Base::ClearNeuronNet()   // 清空神经网络
{
	this->nn_vecNeuronNetWeight.clear();
	this->nn_vecNeuronNetWeight.clear();
	this->nn_mtInputVector.DeleteMatrix();
	this->nn_mtOutputVector.DeleteMatrix();
	this->nn_iInputNum = 0;
	this->nn_iOutputNum = 0;
	this->nn_iLayerNum = 0;
}

void NeuronNet_Base::SetInputNum(int InputNum)   // 设置输入变量数
{
	if (InputNum == this->nn_iInputNum)
		return;
	else 
	{
		this->nn_iInputNum = InputNum;
		this->nn_vecNeuronLayerPara[0].LayerInputNum = InputNum;
		this->nn_mtInputVector.DeleteMatrix();
		this->nn_mtInputVector.NewMatrix(nn_iInputNum, HVECTOR);
		this->nn_vecNeuronNetWeight[0].DeleteMatrix();
		this->nn_vecNeuronNetWeight[0].NewMatrix(nn_iInputNum, nn_vecNeuronLayerPara[0].LayerOutputNum);
		this->Initialization(0);
	}
}

void NeuronNet_Base::SetOutputNum(int OutputNum)   // 设置输出变量数
{
	if (OutputNum == this->nn_iOutputNum)
		return;
	else
	{
		int last = this->nn_iLayerNum - 1;
		this->nn_iOutputNum = OutputNum;
		this->nn_vecNeuronLayerPara[last].LayerOutputNum = OutputNum;
		this->nn_mtOutputVector.DeleteMatrix();
		this->nn_vecNeuronNetWeight[last].DeleteMatrix();
		this->nn_vecNeuronNetWeight[last].NewMatrix(nn_vecNeuronLayerPara[last].LayerInputNum, nn_iOutputNum);
		this->Initialization(last);
	}
}

void NeuronNet_Base::SetLayerNum(int LayerNum)   // 设置网络层数
{
	if (LayerNum == this->nn_iLayerNum)
		return;
	else if (LayerNum > this->nn_iLayerNum)
	{
		int in = this->nn_vecNeuronLayerPara[this->nn_iLayerNum - 1].LayerOutputNum;
		for (int i = nn_iLayerNum; i < LayerNum; ++i)
		{
			nn_vecNeuronLayerPara.push_back(LayerPara(in, nn_iOutputNum));
			nn_vecNeuronNetWeight.push_back(diyCMatrix(in, nn_iOutputNum, 0));
			in = nn_iOutputNum;
			this->Initialization(i);
		}
		this->nn_iLayerNum = LayerNum;
	}
	else
	{
		int in = this->nn_iInputNum;
		int out = this->nn_iOutputNum;
		int lay = LayerNum;
		this->ClearNeuronNet();
		this->NewNeuronNet(in, out, lay);
	}
}

bool NeuronNet_Base::SetInputVector(const std::vector<double> &inputVector)   // 置输入向量，如果与输入数据维度不符，则返回false
{
	if (inputVector.size() != this->nn_iInputNum)
		return false;
	else
	{
		for (int i = 0; i < nn_iInputNum; ++i)
		{
			if (!this->nn_mtInputVector.SetElement(0, i, inputVector[i]))
				return false;
		}
	}

	return true;
}

std::vector<double> NeuronNet_Base::GetOutputVector()   // 返回计算结果
{
	if (this->nn_mtOutputVector.n != 1)
		throw std::length_error("Vector_Type_Mismatch");

	std::vector<double> res(this->nn_iOutputNum);
	for (int i = 0; i < this->nn_iOutputNum; ++i)
		res[i] = this->nn_mtOutputVector[0][i];

	return res;
}

bool NeuronNet_Base::SetLayerOutputNum(const UINT LayerID, const int OutputNum)   // 置第LayerID层网络输出变量数为OutputNum，如尝试改变最后一层的输出变量数会返回false
{
	if (LayerID == nn_iLayerNum - 1)
		return false;
	else
	{
		this->nn_vecNeuronLayerPara[LayerID].LayerOutputNum = OutputNum;
		this->nn_vecNeuronLayerPara[LayerID + 1].LayerInputNum = OutputNum;
		this->nn_vecNeuronNetWeight[LayerID].DeleteMatrix();
		this->nn_vecNeuronNetWeight[LayerID].NewMatrix(nn_vecNeuronLayerPara[LayerID].LayerInputNum, nn_vecNeuronLayerPara[LayerID].LayerOutputNum);
		this->nn_vecNeuronNetWeight[LayerID+1].DeleteMatrix();
		this->nn_vecNeuronNetWeight[LayerID+1].NewMatrix(nn_vecNeuronLayerPara[LayerID+1].LayerInputNum, nn_vecNeuronLayerPara[LayerID+1].LayerOutputNum);
		this->Initialization(LayerID);
		this->Initialization(LayerID + 1);
	}

	return true;
}

void InitRand()
{
	srand((int)clock());
}

double RandDouble(double rangeLow, double rangeHigh)
{
	double rnd = ((double)rand() / RAND_MAX)*(rangeHigh - rangeLow);
	return rnd + rangeLow;
}