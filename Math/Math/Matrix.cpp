#include "MathEngine.h"

namespace EngineSpace
{
	Matrix::Matrix()
		:_v0(Vect(0.0f, 0.0f, 0.0f, 0.0f)), _v1(Vect(0.0f, 0.0f, 0.0f, 0.0f)), _v2(Vect(0.0f, 0.0f, 0.0f, 0.0f)), _v3(Vect(0.0f, 0.0f, 0.0f, 0.0f))
	{

	}

	Matrix::Matrix(const Matrix& CopyVect)
		: _v0(CopyVect._v0), _v1(CopyVect._v1), _v2(CopyVect._v2), _v3(CopyVect._v3)
	{

	}

	Matrix::Matrix(Vect v0, Vect v1, Vect v2, Vect v3)
		: _v0(v0), _v1(v1), _v2(v2), _v3(v3)
	{

	}

	Matrix::Matrix(const Rot, Vect axis, const float angle)
	{
		const float angle_a = 0.5f * angle;
		float cos_a;
		float sin_a;

		cos_a = Trig::cos(angle_a);
		sin_a = Trig::sin(angle_a);

		Vect qV = axis.getNorm();

		qV *= sin_a;

		Vect Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];
		Q[w] = cos_a;

		// this function has been transposed
		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix::Matrix(Special Type)
		:_v0(Vect(0.0f, 0.0f, 0.0f, 0.0f)), _v1(Vect(0.0f, 0.0f, 0.0f, 0.0f)), _v2(Vect(0.0f, 0.0f, 0.0f, 0.0f)), _v3(Vect(0.0f, 0.0f, 0.0f, 0.0f))
	{
		if (Type == Matrix::Special::Identity)
		{
			this->_m0 = 1.0f;
			this->_m5 = 1.0f;
			this->_m10 = 1.0f;
			this->_m15 = 1.0f;
		}
	}

	Matrix::Matrix(Trans, float x, float y, float z)
		:_v0(Vect(1.0f, 0.0f, 0.0f, 0.0f)), _v1(Vect(0.0f, 1.0f, 0.0f, 0.0f)), _v2(Vect(0.0f, 0.0f, 1.0f, 0.0f)), _v3(Vect(x, y, z, 1.0f))
	{

	}

	Matrix::Matrix(Trans, Vect XYZ)
		: _v0(Vect(1.0f, 0.0f, 0.0f, 0.0f)), _v1(Vect(0.0f, 1.0f, 0.0f, 0.0f)), _v2(Vect(0.0f, 0.0f, 1.0f, 0.0f)), _v3(XYZ)
	{

	}

	Matrix::Matrix(Scale, float x, float y, float z)
		: _v0(Vect(x, 0.0f, 0.0f, 0.0f)), _v1(Vect(0.0f, y, 0.0f, 0.0f)), _v2(Vect(0.0f, 0.0f, z, 0.0f)), _v3(0.0f, 0.0f, 0.0f, 1.0f)
	{

	}

	Matrix::Matrix(Scale, Vect XYZ)
		: _v0(Vect(XYZ[x], 0.0f, 0.0f, 0.0f)), _v1(Vect(0.0f, XYZ[y], 0.0f, 0.0f)), _v2(Vect(0.0f, 0.0f, XYZ[z], 0.0f)), _v3(0.0f, 0.0f, 0.0f, 1.0f)
	{

	}

	Matrix::Matrix(Rot1 Axis, float angle)
	{
		const float angle_a = 0.5f * angle;
		float cos_a;
		float sin_a;

		cos_a = Trig::cos(angle_a);
		sin_a = Trig::sin(angle_a);
		Vect qV;

		if (Axis == Matrix::Rot1::X)
		{
			qV = Vect(1.0f, 0.0f, 0.0f);
		}
		else if (Axis == Matrix::Rot1::Y)
		{
			qV = Vect(0.0f, 1.0f, 0.0f);
		}
		else
		{
			qV = Vect(0.0f, 0.0f, 1.0f);
		}

		qV *= sin_a;

		Vect Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];
		Q[w] = cos_a;

		// this function has been transposed
		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	Matrix::Matrix(Orient Type, Vect Forward, Vect Up)
	{
		this->_v2 = Forward.getNorm();
		this->_m11 = 0.0f;
		this->_v0 = (Up.cross(Forward)).getNorm();
		this->_m3 = 0.0f;
		this->_v1 = this->_v2.cross(this->_v0);
		this->_m7 = 0.0f;
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);

		if (Type == Matrix::Orient::WorldToLocal)
		{
			this->T();
		}
	}

	Matrix::Matrix(Rot3, float xAngle, float yAngle, float zAngle)
	{
		Matrix Result = Matrix(Rot1::X, xAngle) * Matrix(Rot1::Y, yAngle) * Matrix(Rot1::Z, zAngle);
		this->_v0 = Result._v0;
		this->_v1 = Result._v1;
		this->_v2 = Result._v2;
		this->_v3 = Result._v3;
	}

	Matrix::Matrix(Quat temp)
	{
		this->_m0 = 1.0f - 2.0f * (temp.qy() * temp.qy() + temp.qz() * temp.qz());
		this->_m1 = 2.0f * (temp.qx() * temp.qy() + temp.real() * temp.qz());
		this->_m2 = 2.0f * (temp.qx() * temp.qz() - temp.real() * temp.qy());
		this->_m3 = 0;

		this->_m4 = 2.0f * (temp.qx() * temp.qy() - temp.real() * temp.qz());
		this->_m5 = 1.0f - 2.0f * (temp.qx() * temp.qx() + temp.qz() * temp.qz());
		this->_m6 = 2.0f * (temp.qy() * temp.qz() + temp.real() * temp.qx());
		this->_m7 = 0;

		this->_m8 = 2.0f * (temp.qx() * temp.qz() + temp.real() * temp.qy());
		this->_m9 = 2.0f * (temp.qy() * temp.qz() - temp.real() * temp.qx());
		this->_m10 = 1.0f - 2.0f * (temp.qx() * temp.qx() + temp.qy() * temp.qy());
		this->_m11 = 0;

		this->_m12 = 0;
		this->_m13 = 0;
		this->_m14 = 0;
		this->_m15 = 1;
	}

	Matrix Matrix::operator+()
	{
		return Matrix(this->_v0, this->_v1, this->_v2, this->_v3);
	}

	Matrix Matrix::operator-()
	{
		return Matrix(Vect(-this->_m0, -this->_m1, -this->_m2, -this->_m3), Vect(-this->_m4, -this->_m5, -this->_m6, -this->_m7), Vect(-this->_m8, -this->_m9, -this->_m10, -this->_m11), Vect(-this->_m12, -this->_m13, -this->_m14, -this->_m15));
	}

	Matrix Matrix::operator+(const Matrix AddM)
	{
		return Matrix(Vect(this->_m0 + AddM._m0, this->_m1 + AddM._m1, this->_m2 + AddM._m2, this->_m3 + AddM._m3),
			Vect(this->_m4 + AddM._m4, this->_m5 + AddM._m5, this->_m6 + AddM._m6, this->_m7 + AddM._m7),
			Vect(this->_m8 + AddM._m8, this->_m9 + AddM._m9, this->_m10 + AddM._m10, this->_m11 + AddM._m11),
			Vect(this->_m12 + AddM._m12, this->_m13 + AddM._m13, this->_m14 + AddM._m14, this->_m15 + AddM._m15));
	}

	Matrix Matrix::operator+=(const Matrix AddM)
	{
		this->_m0 += AddM._m0;
		this->_m1 += AddM._m1;
		this->_m2 += AddM._m2;
		this->_m3 += AddM._m3;
		this->_m4 += AddM._m4;
		this->_m5 += AddM._m5;
		this->_m6 += AddM._m6;
		this->_m7 += AddM._m7;
		this->_m8 += AddM._m8;
		this->_m9 += AddM._m9;
		this->_m10 += AddM._m10;
		this->_m11 += AddM._m11;
		this->_m12 += AddM._m12;
		this->_m13 += AddM._m13;
		this->_m14 += AddM._m14;
		this->_m15 += AddM._m15;

		return *this;
	}

	Matrix Matrix::operator-(const Matrix SubM)
	{
		return Matrix(Vect(this->_m0 - SubM._m0, this->_m1 - SubM._m1, this->_m2 - SubM._m2, this->_m3 - SubM._m3),
			Vect(this->_m4 - SubM._m4, this->_m5 - SubM._m5, this->_m6 - SubM._m6, this->_m7 - SubM._m7),
			Vect(this->_m8 - SubM._m8, this->_m9 - SubM._m9, this->_m10 - SubM._m10, this->_m11 - SubM._m11),
			Vect(this->_m12 - SubM._m12, this->_m13 - SubM._m13, this->_m14 - SubM._m14, this->_m15 - SubM._m15));
	}

	Matrix Matrix::operator-=(const Matrix SubM)
	{
		this->_m0 -= SubM._m0;
		this->_m1 -= SubM._m1;
		this->_m2 -= SubM._m2;
		this->_m3 -= SubM._m3;
		this->_m4 -= SubM._m4;
		this->_m5 -= SubM._m5;
		this->_m6 -= SubM._m6;
		this->_m7 -= SubM._m7;
		this->_m8 -= SubM._m8;
		this->_m9 -= SubM._m9;
		this->_m10 -= SubM._m10;
		this->_m11 -= SubM._m11;
		this->_m12 -= SubM._m12;
		this->_m13 -= SubM._m13;
		this->_m14 -= SubM._m14;
		this->_m15 -= SubM._m15;

		return *this;
	}

	Matrix Matrix::operator*=(const float scale)
	{
		this->_m0 *= scale;
		this->_m1 *= scale;
		this->_m2 *= scale;
		this->_m3 *= scale;
		this->_m4 *= scale;
		this->_m5 *= scale;
		this->_m6 *= scale;
		this->_m7 *= scale;
		this->_m8 *= scale;
		this->_m9 *= scale;
		this->_m10 *= scale;
		this->_m11 *= scale;
		this->_m12 *= scale;
		this->_m13 *= scale;
		this->_m14 *= scale;
		this->_m15 *= scale;
		return *this;
	}

	Matrix Matrix::operator*(const float scale)
	{
		return Matrix(Vect(this->_m0 * scale, this->_m1 * scale, this->_m2 * scale, this->_m3 * scale),
			Vect(this->_m4 * scale, this->_m5 * scale, this->_m6 * scale, this->_m7 * scale),
			Vect(this->_m8 * scale, this->_m9 * scale, this->_m10 * scale, this->_m11 * scale),
			Vect(this->_m12 * scale, this->_m13 * scale, this->_m14 * scale, this->_m15 * scale));
	}

	Matrix operator*(float scale, const Matrix& RHS)
	{
		return Matrix(Vect(RHS._m0 * scale, RHS._m1 * scale, RHS._m2 * scale, RHS._m3 * scale),
			Vect(RHS._m4 * scale, RHS._m5 * scale, RHS._m6 * scale, RHS._m7 * scale),
			Vect(RHS._m8 * scale, RHS._m9 * scale, RHS._m10 * scale, RHS._m11 * scale),
			Vect(RHS._m12 * scale, RHS._m13 * scale, RHS._m14 * scale, RHS._m15 * scale));
	}

	Matrix Matrix::operator*(const Matrix MMult)
	{
		return(Matrix(
			Vect(
				this->_m0 * MMult._m0 + this->_m1 * MMult._m4 + this->_m2 * MMult._m8 + this->_m3 * MMult._m12,
				this->_m0 * MMult._m1 + this->_m1 * MMult._m5 + this->_m2 * MMult._m9 + this->_m3 * MMult._m13,
				this->_m0 * MMult._m2 + this->_m1 * MMult._m6 + this->_m2 * MMult._m10 + this->_m3 * MMult._m14,
				this->_m0 * MMult._m3 + this->_m1 * MMult._m7 + this->_m2 * MMult._m11 + this->_m3 * MMult._m15),
			Vect(
				this->_m4 * MMult._m0 + this->_m5 * MMult._m4 + this->_m6 * MMult._m8 + this->_m7 * MMult._m12,
				this->_m4 * MMult._m1 + this->_m5 * MMult._m5 + this->_m6 * MMult._m9 + this->_m7 * MMult._m13,
				this->_m4 * MMult._m2 + this->_m5 * MMult._m6 + this->_m6 * MMult._m10 + this->_m7 * MMult._m14,
				this->_m4 * MMult._m3 + this->_m5 * MMult._m7 + this->_m6 * MMult._m11 + this->_m7 * MMult._m15),
			Vect(
				this->_m8 * MMult._m0 + this->_m9 * MMult._m4 + this->_m10 * MMult._m8 + this->_m11 * MMult._m12,
				this->_m8 * MMult._m1 + this->_m9 * MMult._m5 + this->_m10 * MMult._m9 + this->_m11 * MMult._m13,
				this->_m8 * MMult._m2 + this->_m9 * MMult._m6 + this->_m10 * MMult._m10 + this->_m11 * MMult._m14,
				this->_m8 * MMult._m3 + this->_m9 * MMult._m7 + this->_m10 * MMult._m11 + this->_m11 * MMult._m15),
			Vect(
				this->_m12 * MMult._m0 + this->_m13 * MMult._m4 + this->_m14 * MMult._m8 + this->_m15 * MMult._m12,
				this->_m12 * MMult._m1 + this->_m13 * MMult._m5 + this->_m14 * MMult._m9 + this->_m15 * MMult._m13,
				this->_m12 * MMult._m2 + this->_m13 * MMult._m6 + this->_m14 * MMult._m10 + this->_m15 * MMult._m14,
				this->_m12 * MMult._m3 + this->_m13 * MMult._m7 + this->_m14 * MMult._m11 + this->_m15 * MMult._m15)));
	}

	Matrix Matrix::operator*=(const Matrix MMult)
	{
		Vect v0 = Vect(
			this->_m0 * MMult._m0 + this->_m1 * MMult._m4 + this->_m2 * MMult._m8 + this->_m3 * MMult._m12,
			this->_m0 * MMult._m1 + this->_m1 * MMult._m5 + this->_m2 * MMult._m9 + this->_m3 * MMult._m13,
			this->_m0 * MMult._m2 + this->_m1 * MMult._m6 + this->_m2 * MMult._m10 + this->_m3 * MMult._m14,
			this->_m0 * MMult._m3 + this->_m1 * MMult._m7 + this->_m2 * MMult._m11 + this->_m3 * MMult._m15);
		Vect v1 = Vect(
			this->_m4 * MMult._m0 + this->_m5 * MMult._m4 + this->_m6 * MMult._m8 + this->_m7 * MMult._m12,
			this->_m4 * MMult._m1 + this->_m5 * MMult._m5 + this->_m6 * MMult._m9 + this->_m7 * MMult._m13,
			this->_m4 * MMult._m2 + this->_m5 * MMult._m6 + this->_m6 * MMult._m10 + this->_m7 * MMult._m14,
			this->_m4 * MMult._m3 + this->_m5 * MMult._m7 + this->_m6 * MMult._m11 + this->_m7 * MMult._m15);
		Vect v2 = Vect(
			this->_m8 * MMult._m0 + this->_m9 * MMult._m4 + this->_m10 * MMult._m8 + this->_m11 * MMult._m12,
			this->_m8 * MMult._m1 + this->_m9 * MMult._m5 + this->_m10 * MMult._m9 + this->_m11 * MMult._m13,
			this->_m8 * MMult._m2 + this->_m9 * MMult._m6 + this->_m10 * MMult._m10 + this->_m11 * MMult._m14,
			this->_m8 * MMult._m3 + this->_m9 * MMult._m7 + this->_m10 * MMult._m11 + this->_m11 * MMult._m15);
		Vect v3 = Vect(
			this->_m12 * MMult._m0 + this->_m13 * MMult._m4 + this->_m14 * MMult._m8 + this->_m15 * MMult._m12,
			this->_m12 * MMult._m1 + this->_m13 * MMult._m5 + this->_m14 * MMult._m9 + this->_m15 * MMult._m13,
			this->_m12 * MMult._m2 + this->_m13 * MMult._m6 + this->_m14 * MMult._m10 + this->_m15 * MMult._m14,
			this->_m12 * MMult._m3 + this->_m13 * MMult._m7 + this->_m14 * MMult._m11 + this->_m15 * MMult._m15);
		this->_v0 = v0;
		this->_v1 = v1;
		this->_v2 = v2;
		this->_v3 = v3;

		return *this;
	}

	Matrix Matrix::operator*(const Quat q)
	{
		Matrix temp = Matrix(q);
		return (*this * temp);
	}

	void Matrix::set(Special Type)
	{
		//Matrix is either Zero or Identity. These will always be zero
		this->_m1 = 0.0f;
		this->_m2 = 0.0f;
		this->_m3 = 0.0f;
		this->_m4 = 0.0f;
		this->_m6 = 0.0f;
		this->_m7 = 0.0f;
		this->_m8 = 0.0f;
		this->_m9 = 0.0f;
		this->_m11 = 0.0f;
		this->_m12 = 0.0f;
		this->_m13 = 0.0f;
		this->_m14 = 0.0f;

		//set the 1s if Identity, otherwise set as 0. 
		if (Type == Matrix::Special::Identity)
		{
			this->_m0 = 1.0f;
			this->_m5 = 1.0f;
			this->_m10 = 1.0f;
			this->_m15 = 1.0f;
		}
		else
		{
			this->_m0 = 0.0f;
			this->_m5 = 0.0f;
			this->_m10 = 0.0f;
			this->_m15 = 0.0f;
		}

	}

	void Matrix::set(Trans, float x, float y, float z)
	{
		this->set(Matrix::Special::Identity);
		this->_m12 = x;
		this->_m13 = y;
		this->_m14 = z;
	}

	void Matrix::set(Trans, Vect vTrans)
	{
		this->set(Matrix::Special::Identity);
		this->_v3.set(vTrans);
	}

	void Matrix::set(Scale, float x, float y, float z)
	{
		this->set(Matrix::Special::Identity);
		this->_m0 = x;
		this->_m5 = y;
		this->_m10 = z;
	}

	void Matrix::set(Scale, Vect vScale)
	{
		this->set(Matrix::Special::Identity);
		this->_m0 = vScale[x];
		this->_m5 = vScale[y];
		this->_m10 = vScale[z];
	}

	void Matrix::set(Rot1 Axis, float angle)
	{
		const float angle_a = 0.5f * angle;
		float cos_a;
		float sin_a;

		cos_a = Trig::cos(angle_a);
		sin_a = Trig::sin(angle_a);
		Vect qV;

		if (Axis == Matrix::Rot1::X)
		{
			qV = Vect(1.0f, 0.0f, 0.0f);
		}
		else if (Axis == Matrix::Rot1::Y)
		{
			qV = Vect(0.0f, 1.0f, 0.0f);
		}
		else
		{
			qV = Vect(0.0f, 0.0f, 1.0f);
		}

		qV *= sin_a;

		Vect Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];
		Q[w] = cos_a;

		// this function has been transposed
		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		// ADD test to make sure that quat is normalized

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Matrix::set(Row RowNum, const Vect newRow)
	{
		if (RowNum == Matrix::Row::i0)
		{
			this->_v0 = newRow;
		}
		else if (RowNum == Matrix::Row::i1)
		{
			this->_v1 = newRow;
		}
		else if (RowNum == Matrix::Row::i2)
		{
			this->_v2 = newRow;
		}
		else
		{
			this->_v3 = newRow;
		}
	}

	Vect Matrix::get(Row RowNum)
	{
		if (RowNum == Matrix::Row::i0)
		{
			return this->_v0;
		}
		else if (RowNum == Matrix::Row::i1)
		{
			return this->_v1;
		}
		else if (RowNum == Matrix::Row::i2)
		{
			return this->_v2;
		}
		else
		{
			return this->_v3;
		}
	}

	void Matrix::set(Rot, Vect Axis, float angle)
	{
		const float angle_a = 0.5f * angle;
		float cos_a;
		float sin_a;

		cos_a = Trig::cos(angle_a);
		sin_a = Trig::sin(angle_a);

		Vect qV = Axis.getNorm();

		qV *= sin_a;

		Vect Q;
		Q[x] = qV[x];
		Q[y] = qV[y];
		Q[z] = qV[z];
		Q[w] = cos_a;

		// this function has been transposed
		float x2, y2, z2;
		float xx, xy, xz;
		float yy, yz, zz;
		float wx, wy, wz;

		// ADD test to make sure that quat is normalized

		x2 = Q[x] + Q[x];
		y2 = Q[y] + Q[y];
		z2 = Q[z] + Q[z];

		xx = Q[x] * x2;
		xy = Q[x] * y2;
		xz = Q[x] * z2;

		yy = Q[y] * y2;
		yz = Q[y] * z2;
		zz = Q[z] * z2;

		wx = Q[w] * x2;
		wy = Q[w] * y2;
		wz = Q[w] * z2;

		this->_m0 = 1.0f - (yy + zz);
		this->_m1 = xy + wz;
		this->_m2 = xz - wy;
		this->_m3 = 0.0f;

		this->_m4 = xy - wz;
		this->_m5 = 1.0f - (xx + zz);
		this->_m6 = yz + wx;
		this->_m7 = 0.0f;

		this->_m8 = xz + wy;
		this->_m9 = yz - wx;
		this->_m10 = 1.0f - (xx + yy);
		this->_m11 = 0.0f;

		this->_v3.set(0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Matrix::set(Vect v0, Vect v1, Vect v2, Vect v3)
	{
		this->_v0 = v0;
		this->_v1 = v1;
		this->_v2 = v2;
		this->_v3 = v3;
	}

	void Matrix::set(Orient Type, Vect Forward, Vect Up)
	{
		this->_v2 = Forward.getNorm();
		this->_m11 = 0.0f;
		this->_v0 = (Up.cross(Forward)).getNorm();
		this->_m3 = 0.0f;
		this->_v1 = this->_v2.cross(this->_v0);
		this->_m7 = 0.0f;
		this->_v3 = Vect(0.0f, 0.0f, 0.0f, 1.0f);

		if (Type == Matrix::Orient::WorldToLocal)
		{
			this->T();
		}
	}

	void Matrix::set(Rot3, float xAngle, float yAngle, float zAngle)
	{
		Matrix Result = Matrix(Rot1::X, xAngle) * Matrix(Rot1::Y, yAngle) * Matrix(Rot1::Z, zAngle);
		this->_v0 = Result._v0;
		this->_v1 = Result._v1;
		this->_v2 = Result._v2;
		this->_v3 = Result._v3;
	}

	void Matrix::set(Quat temp)
	{
		this->_m0 = 1.0f - 2.0f * (temp.qy() * temp.qy() + temp.qz() * temp.qz());
		this->_m1 = 2.0f * (temp.qx() * temp.qy() + temp.real() * temp.qz());
		this->_m2 = 2.0f * (temp.qx() * temp.qz() - temp.real() * temp.qy());
		this->_m3 = 0;

		this->_m4 = 2.0f * (temp.qx() * temp.qy() - temp.real() * temp.qz());
		this->_m5 = 1.0f - 2.0f * (temp.qx() * temp.qx() + temp.qz() * temp.qz());
		this->_m6 = 2.0f * (temp.qy() * temp.qz() + temp.real() * temp.qx());
		this->_m7 = 0;

		this->_m8 = 2.0f * (temp.qx() * temp.qz() + temp.real() * temp.qy());
		this->_m9 = 2.0f * (temp.qy() * temp.qz() - temp.real() * temp.qx());
		this->_m10 = 1.0f - 2.0f * (temp.qx() * temp.qx() + temp.qy() * temp.qy());
		this->_m11 = 0;

		this->_m12 = 0;
		this->_m13 = 0;
		this->_m14 = 0;
		this->_m15 = 1;
	}

	bool Matrix::isEqual(Matrix RHS)
	{
		bool Equal = true;

		if (!this->_v0.isEqual(RHS._v0))
		{
			Equal = false;
		}

		if (!this->_v1.isEqual(RHS._v1))
		{
			Equal = false;
		}

		if (!this->_v2.isEqual(RHS._v2))
		{
			Equal = false;
		}

		if (!this->_v3.isEqual(RHS._v3))
		{
			Equal = false;
		}

		return Equal;
	}

	bool Matrix::isIdentity(float Tolerance)
	{
		bool Equal = true;

		if (!this->_v0.isEqual(Vect(1.0f, 0.0f, 0.0f, 0.0f), Tolerance))
		{
			Equal = false;
		}

		if (!this->_v1.isEqual(Vect(0.0f, 1.0f, 0.0f, 0.0f), Tolerance))
		{
			Equal = false;
		}

		if (!this->_v2.isEqual(Vect(0.0f, 0.0f, 1.0f, 0.0f), Tolerance))
		{
			Equal = false;
		}

		if (!this->_v3.isEqual(Vect(0.0f, 0.0f, 0.0f, 1.0f), Tolerance))
		{
			Equal = false;
		}

		return Equal;
	}

	bool Matrix::isRotation()
	{

		if ((this->det() > (1 - MATH_TOLERANCE)) && (this->det() < (1 + MATH_TOLERANCE)))
		{
			if ((this->getT() * *this).isIdentity(MATH_TOLERANCE))
			{
				return true;
			}
		}
		return false;
	}

	float Matrix::det()
	{
		return (this->_m0 * (this->_m5 * ((this->_m10 * this->_m15) - (this->_m11 * this->_m14)) - this->_m6 * ((this->_m9 * this->_m15) - (this->_m11 * this->_m13)) + this->_m7 * ((this->_m9 * this->_m14) - (this->_m10 * this->_m13)))
			-
			this->_m1 * (this->_m4 * ((this->_m10 * this->_m15) - (this->_m11 * this->_m14)) - this->_m6 * ((this->_m8 * this->_m15) - (this->_m11 * this->_m12)) + this->_m7 * ((this->_m8 * this->_m14) - (this->_m10 * this->_m12)))
			+
			this->_m2 * (this->_m4 * ((this->_m9 * this->_m15) - (this->_m11 * this->_m13)) - this->_m5 * ((this->_m8 * this->_m15) - (this->_m11 * this->_m12)) + this->_m7 * ((this->_m8 * this->_m13) - (this->_m9 * this->_m12)))
			-
			this->_m3 * (this->_m4 * ((this->_m9 * this->_m14) - (this->_m10 * this->_m13)) - this->_m5 * ((this->_m8 * this->_m14) - (this->_m10 * this->_m12)) + this->_m6 * ((this->_m8 * this->_m13) - (this->_m9 * this->_m12)))
			);
	}

	void Matrix::T()
	{
		Vect v0 = Vect(this->_m0, this->_m4, this->_m8, this->_m12);
		Vect v1 = Vect(this->_m1, this->_m5, this->_m9, this->_m13);
		Vect v2 = Vect(this->_m2, this->_m6, this->_m10, this->_m14);
		Vect v3 = Vect(this->_m3, this->_m7, this->_m11, this->_m15);

		this->_v0 = v0;
		this->_v1 = v1;
		this->_v2 = v2;
		this->_v3 = v3;
	}

	Matrix Matrix::getT()
	{
		return(Matrix(Vect(this->_m0, this->_m4, this->_m8, this->_m12), Vect(this->_m1, this->_m5, this->_m9, this->_m13), Vect(this->_m2, this->_m6, this->_m10, this->_m14), Vect(this->_m3, this->_m7, this->_m11, this->_m15)));
	}

	void Matrix::inv()
	{
		Matrix Holder = Matrix(*this);
		float det = 1 / Holder.det();
		this->_m0 = det * (Holder._m5 * (Holder._m10 * Holder._m15 - Holder._m11 * Holder._m14) - Holder._m9 * (Holder._m6 * Holder._m15 + Holder._m7 * Holder._m14) + Holder._m13 * (Holder._m6 * Holder._m11 - Holder._m7 * Holder._m10));
		this->_m4 = det * (Holder._m4 * (-Holder._m10 * Holder._m15 + Holder._m11 * Holder._m14) + Holder._m8 * (Holder._m6 * Holder._m15 - Holder._m7 * Holder._m14) - Holder._m12 * (Holder._m6 * Holder._m11 + Holder._m7 * Holder._m10));
		this->_m8 = det * (Holder._m4 * (Holder._m9 * Holder._m15 - Holder._m11 * Holder._m13) - Holder._m8 * (Holder._m5 * Holder._m15 + Holder._m7 * Holder._m13) + Holder._m12 * (Holder._m5 * Holder._m11 - Holder._m7 * Holder._m9));
		this->_m12 = det * (Holder._m4 * (-Holder._m9 * Holder._m14 + Holder._m10 * Holder._m13) + Holder._m8 * (Holder._m5 * Holder._m14 - Holder._m6 * Holder._m13) - Holder._m12 * (Holder._m5 * Holder._m10 - Holder._m6 * Holder._m9));

		this->_m1 = det * (Holder._m1 * (-Holder._m10 * Holder._m15 + Holder._m11 * Holder._m14) + Holder._m9 * (Holder._m2 * Holder._m15 - Holder._m3 * Holder._m14) - Holder._m13 * (Holder._m2 * Holder._m11 + Holder._m3 * Holder._m10));
		this->_m5 = det * (Holder._m0 * (Holder._m10 * Holder._m15 - Holder._m11 * Holder._m14) - Holder._m8 * (Holder._m2 * Holder._m15 + Holder._m3 * Holder._m14) + Holder._m12 * (Holder._m2 * Holder._m11 - Holder._m3 * Holder._m10));
		this->_m9 = det * (Holder._m0 * (-Holder._m9 * Holder._m15 + Holder._m11 * Holder._m13) + Holder._m8 * (Holder._m1 * Holder._m15 - Holder._m3 * Holder._m13) - Holder._m12 * (Holder._m1 * Holder._m11 + Holder._m3 * Holder._m9));
		this->_m13 = det * (Holder._m0 * (Holder._m9 * Holder._m14 - Holder._m10 * Holder._m13) + Holder._m8 * (Holder._m1 * Holder._m14 + Holder._m2 * Holder._m13) + Holder._m12 * (Holder._m1 * Holder._m10 - Holder._m2 * Holder._m9));

		this->_m2 = det * (Holder._m1 * (Holder._m6 * Holder._m15 - Holder._m7 * Holder._m14) - Holder._m5 * (Holder._m2 * Holder._m15 + Holder._m3 * Holder._m14) + Holder._m13 * (Holder._m2 * Holder._m7 - Holder._m3 * Holder._m6));
		this->_m6 = det * (Holder._m0 * (-Holder._m6 * Holder._m15 + Holder._m7 * Holder._m14) + Holder._m4 * (Holder._m2 * Holder._m15 - Holder._m3 * Holder._m14) - Holder._m12 * (Holder._m2 * Holder._m7 + Holder._m3 * Holder._m6));
		this->_m10 = det * (Holder._m0 * (Holder._m5 * Holder._m15 - Holder._m7 * Holder._m13) - Holder._m4 * (Holder._m1 * Holder._m15 + Holder._m3 * Holder._m13) + Holder._m12 * (Holder._m1 * Holder._m7 - Holder._m3 * Holder._m5));
		this->_m14 = det * (Holder._m0 * (-Holder._m5 * Holder._m14 + Holder._m6 * Holder._m13) + Holder._m4 * (Holder._m1 * Holder._m14 - Holder._m2 * Holder._m13) + Holder._m12 * (Holder._m1 * Holder._m6 + Holder._m2 * Holder._m5));

		this->_m3 = det * (Holder._m1 * (-Holder._m6 * Holder._m11 + Holder._m7 * Holder._m10) + Holder._m5 * (Holder._m2 * Holder._m11 - Holder._m3 * Holder._m10) - Holder._m9 * (Holder._m2 * Holder._m7 + Holder._m3 * Holder._m6));
		this->_m7 = det * (Holder._m0 * (Holder._m6 * Holder._m11 - Holder._m7 * Holder._m10) - Holder._m4 * (Holder._m2 * Holder._m11 + Holder._m3 * Holder._m10) + Holder._m8 * (Holder._m2 * Holder._m7 - Holder._m3 * Holder._m6));
		this->_m11 = det * (Holder._m0 * (-Holder._m5 * Holder._m11 + Holder._m7 * Holder._m9) + Holder._m4 * (Holder._m1 * Holder._m11 - Holder._m3 * Holder._m9) - Holder._m8 * (Holder._m1 * Holder._m7 + Holder._m3 * Holder._m5));
		this->_m15 = det * (Holder._m0 * (Holder._m5 * Holder._m10 - Holder._m6 * Holder._m9) + Holder._m4 * (Holder._m1 * Holder._m10 + Holder._m2 * Holder._m9) + Holder._m8 * (Holder._m1 * Holder._m6 - Holder._m2 * Holder._m5));

	}

	Matrix Matrix::getInv()
	{
		float det = 1 / this->det();
		return(Matrix(
			Vect(
				det * (this->_m5 * (this->_m10 * this->_m15 - this->_m11 * this->_m14) - this->_m9 * (this->_m6 * this->_m15 + this->_m7 * this->_m14) + this->_m13 * (this->_m6 * this->_m11 - this->_m7 * this->_m10)),
				det * (this->_m1 * (-this->_m10 * this->_m15 + this->_m11 * this->_m14) + this->_m9 * (this->_m2 * this->_m15 - this->_m3 * this->_m14) - this->_m13 * (this->_m2 * this->_m11 + this->_m3 * this->_m10)),
				det * (this->_m1 * (this->_m6 * this->_m15 - this->_m7 * this->_m14) - this->_m5 * (this->_m2 * this->_m15 + this->_m3 * this->_m14) + this->_m13 * (this->_m2 * this->_m7 - this->_m3 * this->_m6)),
				det * (this->_m1 * (-this->_m6 * this->_m11 + this->_m7 * this->_m10) + this->_m5 * (this->_m2 * this->_m11 - this->_m3 * this->_m10) - this->_m9 * (this->_m2 * this->_m7 + this->_m3 * this->_m6))),
			Vect(
				det * (this->_m4 * (-this->_m10 * this->_m15 + this->_m11 * this->_m14) + this->_m8 * (this->_m6 * this->_m15 - this->_m7 * this->_m14) - this->_m12 * (this->_m6 * this->_m11 + this->_m7 * this->_m10)),
				det * (this->_m0 * (this->_m10 * this->_m15 - this->_m11 * this->_m14) - this->_m8 * (this->_m2 * this->_m15 + this->_m3 * this->_m14) + this->_m12 * (this->_m2 * this->_m11 - this->_m3 * this->_m10)),
				det * (this->_m0 * (-this->_m6 * this->_m15 + this->_m7 * this->_m14) + this->_m4 * (this->_m2 * this->_m15 - this->_m3 * this->_m14) - this->_m12 * (this->_m2 * this->_m7 + this->_m3 * this->_m6)),
				det * (this->_m0 * (this->_m6 * this->_m11 - this->_m7 * this->_m10) - this->_m4 * (this->_m2 * this->_m11 + this->_m3 * this->_m10) + this->_m8 * (this->_m2 * this->_m7 - this->_m3 * this->_m6))),
			Vect(
				det * (this->_m4 * (this->_m9 * this->_m15 - this->_m11 * this->_m13) - this->_m8 * (this->_m5 * this->_m15 + this->_m7 * this->_m13) + this->_m12 * (this->_m5 * this->_m11 - this->_m7 * this->_m9)),
				det * (this->_m0 * (-this->_m9 * this->_m15 + this->_m11 * this->_m13) + this->_m8 * (this->_m1 * this->_m15 - this->_m3 * this->_m13) - this->_m12 * (this->_m1 * this->_m11 + this->_m3 * this->_m9)),
				det * (this->_m0 * (this->_m5 * this->_m15 - this->_m7 * this->_m13) - this->_m4 * (this->_m1 * this->_m15 + this->_m3 * this->_m13) + this->_m12 * (this->_m1 * this->_m7 - this->_m3 * this->_m5)),
				det * (this->_m0 * (-this->_m5 * this->_m11 + this->_m7 * this->_m9) + this->_m4 * (this->_m1 * this->_m11 - this->_m3 * this->_m9) - this->_m8 * (this->_m1 * this->_m7 + this->_m3 * this->_m5))),
			Vect(
				det * (this->_m4 * (-this->_m9 * this->_m14 + this->_m10 * this->_m13) + this->_m8 * (this->_m5 * this->_m14 - this->_m6 * this->_m13) - this->_m12 * (this->_m5 * this->_m10 - this->_m6 * this->_m9)),
				det * (this->_m0 * (this->_m9 * this->_m14 - this->_m10 * this->_m13) + this->_m8 * (this->_m1 * this->_m14 + this->_m2 * this->_m13) + this->_m12 * (this->_m1 * this->_m10 - this->_m2 * this->_m9)),
				det * (this->_m0 * (-this->_m5 * this->_m14 + this->_m6 * this->_m13) + this->_m4 * (this->_m1 * this->_m14 - this->_m2 * this->_m13) + this->_m12 * (this->_m1 * this->_m6 + this->_m2 * this->_m5)),
				det * (this->_m0 * (this->_m5 * this->_m10 - this->_m6 * this->_m9) + this->_m4 * (this->_m1 * this->_m10 + this->_m2 * this->_m9) + this->_m8 * (this->_m1 * this->_m6 - this->_m2 * this->_m5)))));
	}

	//Brackets & Accessors

	float& Matrix::operator[](const m0_enum)
	{
		return this->_m0;
	}
	float Matrix::operator[](const m0_enum) const
	{
		return this->_m0;
	}

	float& Matrix::operator[](const m1_enum)
	{
		return this->_m1;
	}
	float Matrix::operator[](const m1_enum) const
	{
		return this->_m1;
	}

	float& Matrix::operator[](const m2_enum)
	{
		return this->_m2;
	}
	float Matrix::operator[](const m2_enum) const
	{
		return this->_m2;
	}

	float& Matrix::operator[](const m3_enum)
	{
		return this->_m3;
	}
	float Matrix::operator[](const m3_enum) const
	{
		return this->_m3;
	}

	float& Matrix::operator[](const m4_enum)
	{
		return this->_m4;
	}
	float Matrix::operator[](const m4_enum) const
	{
		return this->_m4;
	}

	float& Matrix::operator[](const m5_enum)
	{
		return this->_m5;
	}
	float Matrix::operator[](const m5_enum) const
	{
		return this->_m5;
	}

	float& Matrix::operator[](const m6_enum)
	{
		return this->_m6;
	}
	float Matrix::operator[](const m6_enum) const
	{
		return this->_m6;
	}

	float& Matrix::operator[](const m7_enum)
	{
		return this->_m7;
	}
	float Matrix::operator[](const m7_enum) const
	{
		return this->_m7;
	}

	float& Matrix::operator[](const m8_enum)
	{
		return this->_m8;
	}
	float Matrix::operator[](const m8_enum) const
	{
		return this->_m8;
	}

	float& Matrix::operator[](const m9_enum)
	{
		return this->_m9;
	}
	float Matrix::operator[](const m9_enum) const
	{
		return this->_m9;
	}

	float& Matrix::operator[](const m10_enum)
	{
		return this->_m10;
	}
	float Matrix::operator[](const m10_enum) const
	{
		return this->_m10;
	}

	float& Matrix::operator[](const m11_enum)
	{
		return this->_m11;
	}
	float Matrix::operator[](const m11_enum) const
	{
		return this->_m11;
	}

	float& Matrix::operator[](const m12_enum)
	{
		return this->_m12;
	}
	float Matrix::operator[](const m12_enum) const
	{
		return this->_m12;
	}

	float& Matrix::operator[](const m13_enum)
	{
		return this->_m13;
	}
	float Matrix::operator[](const m13_enum) const
	{
		return this->_m13;
	}

	float& Matrix::operator[](const m14_enum)
	{
		return this->_m14;
	}
	float Matrix::operator[](const m14_enum) const
	{
		return this->_m14;
	}

	float& Matrix::operator[](const m15_enum)
	{
		return this->_m15;
	}
	float Matrix::operator[](const m15_enum) const
	{
		return this->_m15;
	}

	float& Matrix::m0()
	{
		return this->_m0;
	}
	float Matrix::m0() const
	{
		return this->_m0;
	}

	float& Matrix::m1()
	{
		return this->_m1;
	}
	float Matrix::m1() const
	{
		return this->_m1;
	}

	float& Matrix::m2()
	{
		return this->_m2;
	}
	float Matrix::m2() const
	{
		return this->_m2;
	}

	float& Matrix::m3()
	{
		return this->_m3;
	}
	float Matrix::m3() const
	{
		return this->_m3;
	}

	float& Matrix::m4()
	{
		return this->_m4;
	}
	float Matrix::m4() const
	{
		return this->_m4;
	}

	float& Matrix::m5()
	{
		return this->_m5;
	}
	float Matrix::m5() const
	{
		return this->_m5;
	}

	float& Matrix::m6()
	{
		return this->_m6;
	}
	float Matrix::m6() const
	{
		return this->_m6;
	}

	float& Matrix::m7()
	{
		return this->_m7;
	}
	float Matrix::m7() const
	{
		return this->_m7;
	}

	float& Matrix::m8()
	{
		return this->_m8;
	}
	float Matrix::m8() const
	{
		return this->_m8;
	}

	float& Matrix::m9()
	{
		return this->_m9;
	}
	float Matrix::m9() const
	{
		return this->_m9;
	}

	float& Matrix::m10()
	{
		return this->_m10;
	}
	float Matrix::m10() const
	{
		return this->_m10;
	}

	float& Matrix::m11()
	{
		return this->_m11;
	}
	float Matrix::m11() const
	{
		return this->_m11;
	}

	float& Matrix::m12()
	{
		return this->_m12;
	}
	float Matrix::m12() const
	{
		return this->_m12;
	}

	float& Matrix::m13()
	{
		return this->_m13;
	}
	float Matrix::m13() const
	{
		return this->_m13;
	}

	float& Matrix::m14()
	{
		return this->_m14;
	}
	float Matrix::m14() const
	{
		return this->_m14;
	}

	float& Matrix::m15()
	{
		return this->_m15;
	}
	float Matrix::m15() const
	{
		return this->_m15;
	}
}