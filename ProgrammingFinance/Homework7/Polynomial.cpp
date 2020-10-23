#include"Polynomial.h"

Polynomial::Polynomial()
{
	for (int i=0; i < 13; i++)
	{
		coefficient[i] = 0;
	}
	size = 0;
}

Polynomial::~Polynomial()
{
	for (int i = 0; i < 13; i++)
	{
		coefficient[i] = 0;
	}
	size = 0;
	//cout << "\nPolynomial destroyed" << endl;;
}

void Polynomial::auto_size()
{
	int tmp_size = 0;
	for (int i = 0;i < 13;i++)
	{
		if (this->coefficient[i] != 0)
			tmp_size++;
	}
	this->size = tmp_size;
	return;
}

void Polynomial::setCoe(int coef, int expo)
{
	coefficient[expo] = coef;
	return;
}

int Polynomial::getCoe(int expo)
{
	return coefficient[expo];
}

int Polynomial::getSize()
{
	return size;
}

void Polynomial::setSize(int size)
{
	this->size = size;
	return;
}

ostream& operator<<(ostream& oc, const Polynomial P)
{
	int count = 0;
	for (int i = 0;i < 13;i++)
	{
		if (P.coefficient[i] != 0)
		{
			oc << P.coefficient[i]<<"x^"<<i;
			count++;
			if (count < P.size)
			{
				oc << " + ";
			}
		}
	}
	return oc;
}

void Polynomial:: operator=(const Polynomial P)
{
	size = P.size;
	for (int i = 0;i < 7;i++)
	{
		coefficient[i] = P.coefficient[i];
	}
	return;
}

Polynomial Polynomial::operator+(Polynomial P)
{
	Polynomial temp;
	for (int i = 0;i < 7;i++)
	{
		temp.coefficient[i]=P.coefficient[i] + this->coefficient[i];
	}
	temp.auto_size();
	return temp;
}

void Polynomial::operator+=(Polynomial P)
{
	for (int i = 0;i < 7;i++)
	{
		this->coefficient[i] += P.coefficient[i];
		this->auto_size();
	}
	return;
}

Polynomial Polynomial::operator-(Polynomial P)
{
	Polynomial temp;
	for (int i = 0;i < 7;i++)
	{
		temp.coefficient[i] = this->coefficient[i]- P.coefficient[i];
	}
	temp.auto_size();
	return temp;
}

void Polynomial::operator-=(Polynomial P)
{
	for (int i = 0;i < 7;i++)
	{
		this->coefficient[i] -= P.coefficient[i];
		this->auto_size();
	}
	return;
}

Polynomial Polynomial::operator*(Polynomial P)
{
	Polynomial temp;
	for (int i = 0;i < 7;i++)
	{
		for (int j = 0;j < 7;j++)
		{
			temp.coefficient[i + j]+=this->coefficient[i] * P.coefficient[j];
		}
	}
	temp.auto_size();
	return temp;
}

void Polynomial::operator*=(Polynomial P)
{
	Polynomial temp;
	for (int i = 0;i < 7;i++)
	{
		for (int j = 0;j < 7;j++)
		{
			temp.coefficient[i + j] += this->coefficient[i] * P.coefficient[j];
		}
	}
	for (int i = 0;i < 13;i++)
	{
		this->coefficient[i] = temp.coefficient[i];
	}
	this->auto_size();
	return;
}