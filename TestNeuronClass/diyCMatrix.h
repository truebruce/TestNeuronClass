#pragma once

enum _Type
{
	VVECTOR,        // 列向量，用0初始化
	HVECTOR,        // 行向量，用0初始化
	ZERO,        // 全0矩阵
	IDENTITY,        // 单位矩阵
};

class diyCMatrix
{
public:
	// 默认构造函数
	diyCMatrix(void);
	// 拷贝构造函数
	diyCMatrix(const diyCMatrix &_r);
	// 构造n行m列矩阵，用elem元素进行初始化
	diyCMatrix(int n, int m, double elem);
	// 构造_Ty类型的向量或方阵：VECTOR：用0初始化的向量，长度为n；ZERO：n×n维全0矩阵；IDENTITY：n×n维单位矩阵
	diyCMatrix(int n, _Type _Ty);    
	// 析构函数
	~diyCMatrix(void);

// 创建新矩阵
	// 创建n*m阶矩阵，用elem填充，失败返回false
	bool NewMatrix(int n, int m, double elem = 0);
	// 创建n维_Ty类型向量或方阵，失败返回false
	bool NewMatrix(int n, _Type _Ty);
	// 删除矩阵，失败返回false
	bool DeleteMatrix(void);     

// 元素操作
	// 添加行(_Ty = HVECTOR)或列(_Ty = VVECTOR)，类型不符返回false
	bool NewElements(double elem, _Type _Ty);
	// 写第i行第j列的元素
	bool SetElement(int i, int j, double elem);
	// 根据类型_Ty向第i行或第i列写入elem，类型不符返回false
	bool SetElement(int i, double elem, _Type _Ty, int a);
	// 返回第i行第j列的元素，下标越界抛出异常
	double GetElement(int i, int j);      
	
// 数据拷贝
	// 将数据拷贝到一维数组_d中（请使用未初始化的指针，如果使用已初始化的指针则可能导致内存泄露）
	bool MemoryCopy(double * _d);
	// 将_s中的数据拷贝到矩阵中，_n为行数，_m为列数（需要指定行数和列数，如果与矩阵的参数不符则报错）
	bool CopyData(double * _s, int _n, int _m);
	// 返回从x0,y0到x1,y1的元素构成的新矩阵
	diyCMatrix ExportSection(int x0, int y0, int x1, int y1);
	// 返回第n行/列的元素作为_Ty类型的向量
	diyCMatrix ExportVector(int n, _Type _Ty);

// 重载运算符
	// 常数与矩阵相乘
	friend diyCMatrix operator *(const double &a, const diyCMatrix &b);
	// 矩阵相加，参数不符抛出异常
	friend diyCMatrix operator +(const diyCMatrix &a, const diyCMatrix &b);
	// 矩阵相减，参数不符抛出异常
	friend diyCMatrix operator -(const diyCMatrix &a, const diyCMatrix &b);
	// 矩阵相乘，参数不符抛出异常
	friend diyCMatrix operator *(const diyCMatrix &a, const diyCMatrix &b);
	// 赋值操作符
	diyCMatrix& operator =(const diyCMatrix &_r);
	// 下标运算符，下标越界返回空指针
	const double * operator [](const int row);      

// 初等变换操作
	// 交换is和id行，失败则无变化
	void SwapLines(int is, int id);
	// 交换js和jd列，失败则无变化
	void SwapRows(int js, int jd);
	// 将k*l1行与l2行相加
	void AddTwoLines(double k, int l1, int l2);
	// 将k*r1列与r2列相加
	void AddTwoRows(double k, int r1, int r2);
	// l行所有元素乘以k
	void MultipleLine(double k, int l);
	// r列所有元素乘以k
	void MultipleRow(double k, int r);      
	
// 矩阵计算
	// 求矩阵的行列式，条件不符时抛出异常
	double Determinant(void);
	// 求转置矩阵
	void Transform();
	// 求第i行第j列的代数余子式，失败返回空矩阵
	diyCMatrix Cafactor(int i, int j);
	// 求矩阵的逆矩阵，失败返回空矩阵
	diyCMatrix Inverse(void);
	// 求矩阵的伴随矩阵，失败返回空矩阵
	diyCMatrix Adjoint(void);      
	
// 其他功能
	// 将矩阵中小于1.0e-12的值改为0
	diyCMatrix EliminateMinimum(void);
	// 寻找矩阵中最大的，返回所在行号line和列号row
	void FindMax(int & line, int & row);
	// 寻找矩阵中绝对值最大的，返回所在行号line和列号row
	void FindAbsMax(int & line, int & row);
	// 将矩阵用单位矩阵中的对应元素补齐成方阵，返回补齐方阵使用的
	int Squarelize(void);      

	int n;       // 行数
	int m;       // 列数
protected:
	double **Data;      // 矩阵数据
private:
	bool isInited;      // 标志矩阵是否已经初始化	
public:
	
};

