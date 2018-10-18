#pragma once

#include <vector>
#include "diyCMatrix.h"

typedef unsigned int UINT;

class NeuronNet_Base
{
protected:
	struct LayerPara   // ����ÿ���������Ĳ���
	{
		int LayerInputNum;   // �����������
		int LayerOutputNum;   // �����������
		LayerPara(int inputNum, int OutputNum) { LayerInputNum = inputNum; LayerOutputNum = OutputNum; }
	};

	int nn_iInputNum = 0;   // ���������
	int nn_iOutputNum = 0;   // ���������
	int nn_iLayerNum = 0;   // �������
	std::vector<diyCMatrix> nn_vecNeuronNetWeight;   // ��ԪȨ�ؾ���
	std::vector<LayerPara> nn_vecNeuronLayerPara;   // ÿ����Ԫ�����Ĳ���
	diyCMatrix nn_mtInputVector;   // ����������ɵ�����
	diyCMatrix nn_mtOutputVector;   // ���������ɵ�����
	bool nn_bIsContinus = true;   // �����Ƿ�Ϊ�����仯��

	// ��֤�����Ƿ���ȷ
	bool Validate();
	// ��ʼ�����磬������Ȩ�����������ʼ��
	virtual void Initialization();
	// ��ʼ����WeightID��Ȩ�ؾ���
	virtual void Initialization(const int WeightID);
	// ����������Ĭ��Ϊ��Ծ����
	virtual void ActivationFunction(diyCMatrix &Out);
public:
// ����
	// Ĭ�Ϲ��캯��
	NeuronNet_Base() = default;
	// ����ӵ��inputNum�������outputNum�������LayerNum��������
	NeuronNet_Base(const UINT inputNum, const UINT outputNum, const UINT layerNum);
	// ��������
	NeuronNet_Base(const NeuronNet_Base &) = delete;   

// ���ݲ�������
	// �Ƿ����
	bool IsAvaliable() {
		return !this->nn_vecNeuronNetWeight.empty();
	}
	// �½���inputNum�������outputNum�������layerNum��������
	void NewNeuronNet(const UINT inputNum, const UINT outputNum, const UINT layerNum);
	// ���������
	void ClearNeuronNet();
	// ��ȡ���������
	int GetInputNum() { return this->nn_iInputNum; }
	// ��ȡ���������
	int GetOutputNum() { return this->nn_iOutputNum; }
	// ��ȡ�������
	int GetLayerNum() { return this->nn_iLayerNum; }
	// ����������������˲����ᵼ�������ʼ��
	void SetInputNum(int InputNum);
	// ����������������˲����ᵼ�������ʼ����������������
	void SetOutputNum(int OutputNum);
	// ��������������˲����ᵼ�������ʼ��
	void SetLayerNum(int LayerNum);
	// �������������������������ά�Ȳ������򷵻�false
	bool SetInputVector(const std::vector<double> &inputVector);
	// �����������
	std::vector<double> GetOutputVector();
	// ��ȡ��LayerID����������������,ʹ��at���±�Խ��ʱ���׳��쳣
	int GetLayerOutputNum(UINT LayerID) {
		return this->nn_vecNeuronLayerPara.at(LayerID).LayerOutputNum;
	}
	// �õ�LayerID���������������ΪOutputNum���糢�Ըı����һ�������������᷵��false
	bool SetLayerOutputNum(UINT LayerID, int OutputNum);
	
// ����
	// �������
	void CalculateOutput();
	// Ȩ���ݻ������麯��
	virtual void EvaluateWeight() = 0; 

	// ����
	virtual ~NeuronNet_Base();
};

void InitRand();
double RandDouble(double rangeLow, double rangeHigh);

