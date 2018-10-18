#pragma once

enum _Type
{
	VVECTOR,        // ����������0��ʼ��
	HVECTOR,        // ����������0��ʼ��
	ZERO,        // ȫ0����
	IDENTITY,        // ��λ����
};

class diyCMatrix
{
public:
	// Ĭ�Ϲ��캯��
	diyCMatrix(void);
	// �������캯��
	diyCMatrix(const diyCMatrix &_r);
	// ����n��m�о�����elemԪ�ؽ��г�ʼ��
	diyCMatrix(int n, int m, double elem);
	// ����_Ty���͵���������VECTOR����0��ʼ��������������Ϊn��ZERO��n��nάȫ0����IDENTITY��n��nά��λ����
	diyCMatrix(int n, _Type _Ty);    
	// ��������
	~diyCMatrix(void);

// �����¾���
	// ����n*m�׾�����elem��䣬ʧ�ܷ���false
	bool NewMatrix(int n, int m, double elem = 0);
	// ����nά_Ty������������ʧ�ܷ���false
	bool NewMatrix(int n, _Type _Ty);
	// ɾ������ʧ�ܷ���false
	bool DeleteMatrix(void);     

// Ԫ�ز���
	// �����(_Ty = HVECTOR)����(_Ty = VVECTOR)�����Ͳ�������false
	bool NewElements(double elem, _Type _Ty);
	// д��i�е�j�е�Ԫ��
	bool SetElement(int i, int j, double elem);
	// ��������_Ty���i�л��i��д��elem�����Ͳ�������false
	bool SetElement(int i, double elem, _Type _Ty, int a);
	// ���ص�i�е�j�е�Ԫ�أ��±�Խ���׳��쳣
	double GetElement(int i, int j);      
	
// ���ݿ���
	// �����ݿ�����һά����_d�У���ʹ��δ��ʼ����ָ�룬���ʹ���ѳ�ʼ����ָ������ܵ����ڴ�й¶��
	bool MemoryCopy(double * _d);
	// ��_s�е����ݿ����������У�_nΪ������_mΪ��������Ҫָ����������������������Ĳ��������򱨴�
	bool CopyData(double * _s, int _n, int _m);
	// ���ش�x0,y0��x1,y1��Ԫ�ع��ɵ��¾���
	diyCMatrix ExportSection(int x0, int y0, int x1, int y1);
	// ���ص�n��/�е�Ԫ����Ϊ_Ty���͵�����
	diyCMatrix ExportVector(int n, _Type _Ty);

// ���������
	// ������������
	friend diyCMatrix operator *(const double &a, const diyCMatrix &b);
	// ������ӣ����������׳��쳣
	friend diyCMatrix operator +(const diyCMatrix &a, const diyCMatrix &b);
	// ������������������׳��쳣
	friend diyCMatrix operator -(const diyCMatrix &a, const diyCMatrix &b);
	// ������ˣ����������׳��쳣
	friend diyCMatrix operator *(const diyCMatrix &a, const diyCMatrix &b);
	// ��ֵ������
	diyCMatrix& operator =(const diyCMatrix &_r);
	// �±���������±�Խ�緵�ؿ�ָ��
	const double * operator [](const int row);      

// ���ȱ任����
	// ����is��id�У�ʧ�����ޱ仯
	void SwapLines(int is, int id);
	// ����js��jd�У�ʧ�����ޱ仯
	void SwapRows(int js, int jd);
	// ��k*l1����l2�����
	void AddTwoLines(double k, int l1, int l2);
	// ��k*r1����r2�����
	void AddTwoRows(double k, int r1, int r2);
	// l������Ԫ�س���k
	void MultipleLine(double k, int l);
	// r������Ԫ�س���k
	void MultipleRow(double k, int r);      
	
// �������
	// ����������ʽ����������ʱ�׳��쳣
	double Determinant(void);
	// ��ת�þ���
	void Transform();
	// ���i�е�j�еĴ�������ʽ��ʧ�ܷ��ؿվ���
	diyCMatrix Cafactor(int i, int j);
	// �����������ʧ�ܷ��ؿվ���
	diyCMatrix Inverse(void);
	// �����İ������ʧ�ܷ��ؿվ���
	diyCMatrix Adjoint(void);      
	
// ��������
	// ��������С��1.0e-12��ֵ��Ϊ0
	diyCMatrix EliminateMinimum(void);
	// Ѱ�Ҿ��������ģ����������к�line���к�row
	void FindMax(int & line, int & row);
	// Ѱ�Ҿ����о���ֵ���ģ����������к�line���к�row
	void FindAbsMax(int & line, int & row);
	// �������õ�λ�����еĶ�ӦԪ�ز���ɷ��󣬷��ز��뷽��ʹ�õ�
	int Squarelize(void);      

	int n;       // ����
	int m;       // ����
protected:
	double **Data;      // ��������
private:
	bool isInited;      // ��־�����Ƿ��Ѿ���ʼ��	
public:
	
};

