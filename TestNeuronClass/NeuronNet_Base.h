#pragma once

#include <vector>
#include "diyCMatrix.h"

typedef unsigned int UINT;

class NeuronNet_Base
{
protected:
	struct LayerPara   // 保存每个神经网络层的参数
	{
		int LayerInputNum;   // 层输入变量数
		int LayerOutputNum;   // 层输出变量数
		LayerPara(int inputNum, int OutputNum) { LayerInputNum = inputNum; LayerOutputNum = OutputNum; }
	};

	int nn_iInputNum = 0;   // 输入变量数
	int nn_iOutputNum = 0;   // 输出变量数
	int nn_iLayerNum = 0;   // 网络层数
	std::vector<diyCMatrix> nn_vecNeuronNetWeight;   // 神经元权重矩阵集
	std::vector<LayerPara> nn_vecNeuronLayerPara;   // 每个神经元网络层的参数
	diyCMatrix nn_mtInputVector;   // 输入数据组成的向量
	diyCMatrix nn_mtOutputVector;   // 输出数据组成的向量
	bool nn_bIsContinus = true;   // 数据是否为连续变化量

	// 验证矩阵是否正确
	bool Validate();
	// 初始化网络，将所有权重用随机数初始化
	virtual void Initialization();
	// 初始化第WeightID个权重矩阵
	virtual void Initialization(const int WeightID);
	// 激发函数，默认为阶跃函数
	virtual void ActivationFunction(diyCMatrix &Out);
public:
// 构造
	// 默认构造函数
	NeuronNet_Base() = default;
	// 构造拥有inputNum个输入和outputNum个输出的LayerNum层神经网络
	NeuronNet_Base(const UINT inputNum, const UINT outputNum, const UINT layerNum);
	// 不允许拷贝
	NeuronNet_Base(const NeuronNet_Base &) = delete;   

// 数据操作方法
	// 是否可用
	bool IsAvaliable() {
		return !this->nn_vecNeuronNetWeight.empty();
	}
	// 新建有inputNum个输入和outputNum个输出的layerNum层神经网络
	void NewNeuronNet(const UINT inputNum, const UINT outputNum, const UINT layerNum);
	// 清空神经网络
	void ClearNeuronNet();
	// 获取输入变量数
	int GetInputNum() { return this->nn_iInputNum; }
	// 获取输出变量数
	int GetOutputNum() { return this->nn_iOutputNum; }
	// 获取网络层数
	int GetLayerNum() { return this->nn_iLayerNum; }
	// 设置输入变量数，此操作会导致网络初始化
	void SetInputNum(int InputNum);
	// 设置输出变量数，此操作会导致网络初始化，并清空输出向量
	void SetOutputNum(int OutputNum);
	// 设置网络层数，此操作会导致网络初始化
	void SetLayerNum(int LayerNum);
	// 置输入向量，如果与输入数据维度不符，则返回false
	bool SetInputVector(const std::vector<double> &inputVector);
	// 返回输出向量
	std::vector<double> GetOutputVector();
	// 获取第LayerID层网络的输出变量数,使用at在下标越界时会抛出异常
	int GetLayerOutputNum(UINT LayerID) {
		return this->nn_vecNeuronLayerPara.at(LayerID).LayerOutputNum;
	}
	// 置第LayerID层网络输出变量数为OutputNum，如尝试改变最后一层的输出变量数会返回false
	bool SetLayerOutputNum(UINT LayerID, int OutputNum);
	
// 计算
	// 计算输出
	void CalculateOutput();
	// 权重演化，纯虚函数
	virtual void EvaluateWeight() = 0; 

	// 析构
	virtual ~NeuronNet_Base();
};

void InitRand();
double RandDouble(double rangeLow, double rangeHigh);

