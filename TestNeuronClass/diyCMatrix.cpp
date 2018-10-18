#include "diyCMatrix.h"
#include <cstdlib>
#include <cmath>
#include <stdexcept>

diyCMatrix::diyCMatrix(void)
	: n(0)
	, m(0)
	, Data(NULL)
	, isInited(false)
{
}


diyCMatrix::~diyCMatrix(void)
{
	this->DeleteMatrix();
}


diyCMatrix::diyCMatrix(int n, int m, double elem)
{
	this->n = n;
	this->m = m;
	this->Data = new double * [this->n];
	for(int i=0;i<this->n;i++)
		this->Data[i] = new double [this->m];

	for(int i=0;i<this->n;i++)
		for(int j=0;j<this->m;j++)
			this->Data[i][j] = elem;

	this->isInited = true;
}


diyCMatrix::diyCMatrix(int n, _Type _Ty)
{
	this->n = this->m = n;

	switch(_Ty)
	{
	case VVECTOR:
		this->m = 1;
		this->n = n;
		this->Data = new double * [this->n];
		for(int i=0;i<this->n;i++)
			this->Data[i] = new double [m];
		for(int i=0;i<this->n;i++)
			this->Data[i][0] = 0;
		this->isInited = true;
		break;
	case HVECTOR:
		this->n = 1;
		this->m = n;
		this->Data = new double * [this->n];
		this->Data[0] = new double [this->m];
		for(int i=0;i<this->m;i++)
			this->Data[0][i] = 0;
		this->isInited = true;
		break;
	case ZERO:
		this->n = this->m = n;
		this->Data = new double * [this->n];
		for(int i=0;i<this->n;i++)
			this->Data[i] = new double [this->m];
		for(int i=0;i<this->n;i++)
			for(int j=0;j<this->m;j++)
				this->Data[i][j] = 0;
		break;
	case IDENTITY:
		this->n = this->m = n;
		this->Data = new double * [this->n];
		for(int i=0;i<this->n;i++)
			this->Data[i] = new double [this->m];
		for(int i=0;i<this->n;i++)
			for(int j=0;j<this->m;j++)
				this->Data[i][j] = 0;
		for(int i=0;i<n;i++)
			this->Data[i][i] = 1;
		break;
	}

	this->isInited = true;
}


diyCMatrix::diyCMatrix(const diyCMatrix &_r)
{
	this->n = _r.n;
	this->m = _r.m;

	this->Data = new double *[this->n];
	for(int i=0;i<this->n;i++)
		this->Data[i] = new double [this->m];

	for(int i=0;i<this->n;i++)
		for(int j=0;j<this->m;j++)
			this->Data[i][j] = _r.Data[i][j];

	this->isInited = _r.isInited;
}


bool diyCMatrix::NewMatrix(int n, int m, double elem)
{
	if(!this->isInited)
	{
		this->n = n;
		this->m = m;
		this->Data = new double * [this->n];
		for(int i=0;i<this->n;i++)
			this->Data[i] = new double [this->m];

		for(int i=0;i<this->n;i++)
			for(int j=0;j<this->m;j++)
				this->Data[i][j] = elem;

		this->isInited = true;
	}
	else
		return false;

	return true;
}



bool diyCMatrix::NewMatrix(int n, _Type _Ty)
{
	if(!this->isInited)
	{
		switch(_Ty)
		{
		case VVECTOR:
			this->m = 1;
			this->n = n;
			this->Data = new double * [this->n];
			for(int i=0;i<this->n;i++)
				this->Data[i] = new double [m];
			for(int i=0;i<this->n;i++)
				this->Data[i][0] = 0;
			this->isInited = true;
			break;
		case HVECTOR:
			this->n = 1;
			this->m = n;
			this->Data = new double * [this->n];
			this->Data[0] = new double [this->m];
			for(int i=0;i<this->m;i++)
				this->Data[0][i] = 0;
			this->isInited = true;
			break;
		case ZERO:
			this->n = this->m = n;
			this->Data = new double * [this->n];
			for(int i=0;i<this->n;i++)
				this->Data[i] = new double [this->m];
			for(int i=0;i<this->n;i++)
				for(int j=0;j<this->m;j++)
					this->Data[i][j] = 0;
			this->isInited = true;
			break;
		case IDENTITY:
			this->n = this->m = n;
			this->Data = new double * [this->n];
			for(int i=0;i<this->n;i++)
				this->Data[i] = new double [this->m];
			for(int i=0;i<this->n;i++)
				for(int j=0;j<this->m;j++)
					this->Data[i][j] = 0;
			for(int i=0;i<n;i++)
				this->Data[i][i] = 1;
			this->isInited = true;
			break;
		}
	}
	else
		return false;

	return true;
}


bool diyCMatrix::DeleteMatrix(void)
{
	if(this->Data == NULL)
		return false;
	else
	{
		for(int i=0;i<this->n;i++)
			delete this->Data[i];
		delete this->Data;
		this->n = this->m = 0;
		this->isInited = false;
		this->Data = NULL;
		return true;
	}
}


diyCMatrix& diyCMatrix::operator =(const diyCMatrix &_r)
{
	if(this->isInited)
	{
		this->DeleteMatrix();
	}

	this->n = _r.n;
	this->m = _r.m;
	this->Data = new double * [this->n];
	for(int i=0;i<this->n;i++)
		this->Data[i] = new double [this->m];

	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			this->Data[i][j] = _r.Data[i][j];

	this->isInited = true;

	return *this;
}


const double * diyCMatrix::operator [](const int row)
{
	if(this->isInited)
	{
		if(row<this->n)
			return this->Data[row];
	}

	return NULL;
}


bool diyCMatrix::SetElement(int i, int j, double elem)
{
	if(this->isInited)
	{
		if(i<this->n&&j<this->m)
		{
			this->Data[i][j] = elem;
			return true;
		}
	}

	return false;
}


bool diyCMatrix::SetElement(int i, double elem, _Type _Ty, int a)
{
	if(this->isInited)
	{
		switch(_Ty)
		{
		case VVECTOR:
			if(i<this->m)
			{
				for(int j=0;j<this->n;j++)
					this->Data[j][i] = elem;
				
				return true;
			}
			break;
		case HVECTOR:
			if(i<this->n)
			{
				for(int j=0;j<this->m;j++)
					this->Data[i][j] = elem;

				return true;
			}
			break;
		}
	}

	return false;
}


double diyCMatrix::GetElement(int i, int j)
{
	if (i >= this->n)
		throw std::out_of_range("Rows_over_range");
	if (j >= this->m)
		throw std::out_of_range("Columns_over_Range");

	if (this->isInited)
	{
		if (i < this->n&&j < this->m)
		{
			return this->Data[i][j];
		}
	}
	else
		throw std::logic_error("Matrix_not_Ready");

	return -1;
}


diyCMatrix operator *(const double &a, const diyCMatrix &b)
{
	diyCMatrix _mt(b.n, b.m, 0);

	for(int i=0;i<_mt.n;i++)
		for(int j=0;j<_mt.m;j++)
			_mt.Data[i][j] = b.Data[i][j] * a;

	return _mt;
}


diyCMatrix operator +(const diyCMatrix &a, const diyCMatrix &b)
{
	if(a.n != b.n || a.m != b.m)
		throw std::logic_error("Matrix_Mismatch");

	diyCMatrix _mt(a.n, a.m, 0);

	for(int i=0;i<_mt.n;i++)
		for(int j=0;j<_mt.m;j++)
			_mt.Data[i][j] = a.Data[i][j] + b.Data[i][j];

	return _mt;
}


diyCMatrix operator -(const diyCMatrix &a, const diyCMatrix &b)
{
	if(a.n != b.n || a.m != b.m)
		throw std::logic_error("Matrix_Mismatch");

	diyCMatrix _mt(a.n, a.m, 0);

	for(int i=0;i<_mt.n;i++)
		for(int j=0;j<_mt.m;j++)
			_mt.Data[i][j] = a.Data[i][j] - b.Data[i][j];

	return _mt;
}


diyCMatrix operator *(const diyCMatrix &a, const diyCMatrix &b)
{
	if(a.m != b.n)
		throw std::logic_error("Matrix_Mismatch");

	diyCMatrix _mt(a.n, b.m, 0);

	for(int i=0;i<_mt.n;i++)
	{
		for(int j=0;j<_mt.m;j++)
		{
			_mt.Data[i][j] = a.Data[i][0] * b.Data[0][j];
			for(int k=1;k<a.m;k++)
				_mt.Data[i][j] += a.Data[i][k] * b.Data[k][j];
		}
	}

	return _mt;
}

void diyCMatrix::Transform()
{
	diyCMatrix _mt(this->m, this->n, 0);

	for(int i=0;i<this->n;i++)
	{
		for(int j=0;j<this->m;j++)
			_mt.Data[j][i] = this->Data[i][j];
	}

	this->DeleteMatrix();
	this->NewMatrix(_mt.n, _mt.m, 0);
	for(int i=0;i<this->n;i++)
		for(int j=0;j<this->m;j++)
			this->Data[i][j] = _mt.Data[i][j];
}


bool diyCMatrix::NewElements(double elem, _Type _Ty)
{
	double **temp = this->Data;

	switch(_Ty)
	{
	case VVECTOR:
		this->m++;
		this->Data = new double *[this->n];
		for(int i=0;i<this->n;i++)
			this->Data[i] = new double [this->m];

		for(int i=0;i<this->n;i++)
			for(int j=0;j<this->m-1;j++)
				this->Data[i][j] = temp[i][j];

		for(int i=0;i<this->n;i++)
			this->Data[i][this->m-1] = elem;

		for(int i=0;i<this->n-1;i++)
			delete temp[i];
		delete temp;

		return true;
		break;
	case HVECTOR:
		this->n++;
		this->Data = new double *[this->n];
		for(int i=0;i<this->n;i++)
			this->Data[i] = new double [this->m];

		for(int i=0;i<this->n-1;i++)
			for(int j=0;j<this->m;j++)
				this->Data[i][j] = temp[i][j];

		for(int i=0;i<this->m;i++)
			this->Data[this->n-1][i] = elem;

		for(int i=0;i<this->n-1;i++)
			delete temp[i];
		delete temp;

		return true;
		break;
	}

	return false;
}


double diyCMatrix::Determinant(void)
{
	if(this->n != this->m)
		throw std::logic_error("Wrong_Type_of_Matrix");

	diyCMatrix _t = *this;

	double _r = 0;
	
	// 如果阶数大于5，则使用行变换法，小于5则使用行展开递归法
	if(this->n<=5)
	{
		if(this->n == 1&&this->m == 1)
			_r = this->Data[0][0];
		else
		{
			for(int i=0;i<this->m;i++)
			{
				double s = pow(-1.0,i);
				_r += s * this->Data[0][i] * this->Cafactor(0,i).Determinant();
			}
		}
	}
	else
	{
		_r = 1;
		double s = 1;

		for(int i=0;i<_t.m;i++)
		{
			// 从第一列开始，每一列进行一次操作
			if(_t[i][i] == 0)
			{
				bool q = false;
				for(int j=i;j<_t.n;j++)
				{
					if(_t[j][i] != 0)
					{
						_t.SwapLines(j,i);
						s *= -1;
						q = false;
						break;
					}
					else
						q = true;
				}
	
				if(q)
				{
					return 0;
					break;
				}	
			}
	
			for(int j=i;j<_t.n;j++)
			{
				if(j==i)
					continue;
				double rr = _t[j][i]/_t[i][i];
				_t.AddTwoLines(-rr,i,j);
			}
		}

		for(int i=0;i<_t.n;i++)
			_r *= _t[i][i];
		
		_r = s*_r;
	}

	return _r;
}


diyCMatrix diyCMatrix::Cafactor(int i, int j)
{
	diyCMatrix _mt;

	if(i<this->n&&j<this->m)
	{
		_mt.NewMatrix(this->n-1,this->m-1);
		for(int x=0;x<_mt.n;x++)
		{
			int mx = x;
			if(x>=i)
				mx++;
			for(int y=0;y<_mt.m;y++)
			{
				int my = y;
				if(y>=j)
					my++;
				_mt.SetElement(x,y,this->Data[mx][my]);
			}
		}
	}

	return _mt;
}


diyCMatrix diyCMatrix::Inverse(void)
{
	diyCMatrix _mt;

	if(this->n == this->m)
	{
		_mt = *this;

		diyCMatrix _e(this->n,IDENTITY);

		for(int i=0;i<_mt.m;i++)
		{
			// 从第一列开始，每一列进行一次操作
			if(_mt[i][i] == 0)
			{
				bool q = false;
				for(int j=i;j<_mt.n;j++)
				{
					if(_mt[j][i] != 0)
					{
						_mt.SwapLines(j,i);
						_e.SwapLines(j,i);
						q = false;
						break;
					}
					else
						q = true;
				}
	
				if(q)
				{
					return _mt;
					break;
				}
			}
	
			double r = 1/_mt[i][i];
			_mt.MultipleLine(r,i);
			_e.MultipleLine(r,i);      // 对角线元素变1
			for(int j=0;j<_mt.n;j++)
			{
				if(j==i)	
					continue;
				double rr = _mt[j][i]/_mt[i][i];
				_mt.AddTwoLines(-rr,i,j);
				_e.AddTwoLines(-rr,i,j);
			}
		}

		_mt = _e;
	}

	return _mt;
}


diyCMatrix diyCMatrix::Adjoint(void)
{
	diyCMatrix _mt;

	if(this->n == this->m)
	{
		_mt.NewMatrix(this->n,this->m);
		for(int i=0;i<_mt.n;i++)
		{
			for(int j=0;j<_mt.m;j++)
			{
				double _s = pow(-1.0,i+j);
				_mt.SetElement(i,j,_s * this->Cafactor(i,j).Determinant());
			}
		}

		_mt.Transform();
	}

	return _mt;
}


bool diyCMatrix::MemoryCopy(double * _d)
{
	int size = this->n*this->m;

	_d = new double [size];
	for(int i=0;i<this->n;i++)
		for(int j=0;j<this->m;j++)
			_d[i*this->n+j] = this->Data[i][j];

	return true;
}


bool diyCMatrix::CopyData(double * _s, int _n, int _m)
{
	if(this->isInited)
	{
		if(this->n == _n&&this->m == _m)
		{
			for(int i=0;i<_n;i++)
				for(int j=0;j<_m;j++)
					this->Data[i][j] = _s[i*_n+j];
		}
		else
			return false;
	}
	else
		return false;

	return true;
}


diyCMatrix diyCMatrix::ExportSection(int x0, int y0, int x1, int y1)
{
	diyCMatrix _mt;

	if(x0>=this->m)
		x0 = this->m;
	if(x1>=this->m)
		x1 = this->m;
	if(y0>=this->n)
		y0 = this->n;
	if(y1>=this->n)
		y1 = this->n;

	int _n(0),_m(0),offx(0),offy(0);
	if(x0>x1)
	{
		_m = x0 - x1 + 1;
		offx = x1;
	}
	else
	{
		_m = x1 - x0 + 1;
		offx = x0;
	}

	if(y0>y1)
	{
		_n = y0 - y1 + 1;
		offy = y1;
	}
	else
	{
		_n = y1 - y0 + 1;
		offy = y0;
	}

	_mt.NewMatrix(_n,_m,0);
	for(int i=0;i<_mt.n;i++)
	{
		for(int j=0;j<_mt.m;j++)
		{
			_mt.SetElement(i,j,this->Data[i+offx][j+offy]);
		}
	}

	return _mt;
}


void diyCMatrix::SwapLines(int is, int id)
{
	if(is<this->n&&id<this->n)
	{
		double tmp(0);
		for(int i=0;i<this->m;i++)
		{
			tmp = this->Data[id][i];
			this->Data[id][i] = this->Data[is][i];
			this->Data[is][i] = tmp;
		}
	}
}


void diyCMatrix::SwapRows(int js, int jd)
{
	if(js<this->m&&jd<this->m)
	{
		double tmp(0);
		for(int i=0;i<this->n;i++)
		{
			tmp = this->Data[i][jd];
			this->Data[i][jd] = this->Data[i][js];
			this->Data[i][js] = tmp;
		}
	}
}


void diyCMatrix::AddTwoLines(double k, int l1, int l2)
{
	if(l1<this->n&&l2<this->n)
	{
		for(int i=0;i<this->m;i++)
			this->Data[l2][i] = this->Data[l2][i] + k * this->Data[l1][i];
	}
}


void diyCMatrix::AddTwoRows(double k, int r1, int r2)
{
	if(r1<this->m&&r2<this->m)
	{
		for(int i=0;i<this->n;i++)
			this->Data[i][r2] = this->Data[i][r2] + k * this->Data[i][r1];
	}
}


void diyCMatrix::MultipleLine(double k, int l)
{
	if(l<this->n)
	{
		for(int i=0;i<this->m;i++)
			this->Data[l][i] = this->Data[l][i] * k;
	}
}


void diyCMatrix::MultipleRow(double k, int r)
{
	if(r<this->m)
	{
		for(int i=0;i<this->n;i++)
			this->Data[i][r] = this->Data[i][r] * k;
	}
}


void diyCMatrix::FindMax(int & line, int & row)
{
	double _m = 0;
	int l(0),r(0);
	for(int i=0;i<this->n;i++)
	{
		for(int j=0;j<this->m;j++)
		{
			if(this->Data[i][j]>_m)
			{
				_m = this->Data[i][j];
				l = i;
				r = j;
			}
		}
	}

	line = l;
	row = r;
}


void diyCMatrix::FindAbsMax(int & line, int & row)
{
	double _m = 0;
	int l(0),r(0);
	for(int i=0;i<this->n;i++)
	{
		for(int j=0;j<this->m;j++)
		{
			if(abs(this->Data[i][j])>_m)
			{
				_m = abs(this->Data[i][j]);
				l = i;
				r = j;
			}
		}
	}

	line = l;
	row = r;
}


diyCMatrix diyCMatrix::EliminateMinimum(void)
{
	diyCMatrix _mt(this->n,this->m,0);

	for(int i=0;i<_mt.n;i++)
	{
		for(int j=0;j<_mt.m;j++)
		{
			if(this->Data[i][j]<1.0e-12)
				_mt.Data[i][j] = 0;
			else
				_mt.Data[i][j] = this->Data[i][j];
		}
	}

	return _mt;
}


int diyCMatrix::Squarelize(void)
{
	diyCMatrix _mt;

	int size(0);

	if(this->n>this->m)
		size = this->n;
	else if(this->m>this->n)
		size = this->m;
	else
		return 0;

	_mt.NewMatrix(size,IDENTITY);

	for(int i=0;i<this->n;i++)
	{
		for(int j=0;j<this->m;j++)
		{
			_mt.SetElement(i,j,this->Data[i][j]);
		}
	}

	this->operator=(_mt);

	return size;
}


diyCMatrix diyCMatrix::ExportVector(int n, _Type _Ty)
{
	diyCMatrix _v;

	switch(_Ty)
	{
	case HVECTOR:
		if(n<this->n)
		{
			_v.NewMatrix(this->m,_Ty);
			for(int i=0;i<_v.m;i++)
				_v.SetElement(0,i,this->Data[n][i]);
		}
		break;
	case VVECTOR:
		if(n<this->m)
		{
			_v.NewMatrix(this->n,_Ty);
			for(int i=0;i<_v.n;i++)
				_v.SetElement(i,0,this->Data[i][n]);
		}
		break;
	}

	return _v;
}
