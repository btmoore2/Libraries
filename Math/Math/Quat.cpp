
#include "MathEngine.h"

namespace EngineSpace
{
    Quat::Quat()
        :_qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(1.0f)
    {

    }

    Quat::Quat(const float nx, const float ny, const float nz, const float nw)
        : _qx(nx), _qy(ny), _qz(nz), _qw(nw)
    {

    }

    Quat::Quat(Vect temp, float nw)
        : _qx(temp.x()), _qy(temp.y()), _qz(temp.z()), _qw(nw)
    {

    }

    Quat::Quat(Rot1 type, float angle)
        : _qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(Trig::cos(angle / 2))
    {
        if (type == Rot1::X)
        {
            this->_qx = Trig::sin(angle / 2);
        }
        else if (type == Rot1::Y)
        {
            this->_qy = Trig::sin(angle / 2);
        }
        else
        {
            this->_qz = Trig::sin(angle / 2);
        }
    }

    Quat::Quat(Rot3 type, float x, float y, float z)
    {
        //Better way to do this?
        if (type == Rot3::XYZ)
        {
            Quat temp = Quat(Rot1::X, x) * Quat(Rot1::Y, y) * Quat(Rot1::Z, z);
            this->_mq = temp._mq;
        }
    }

    Quat::Quat(Rot type, Vect v, float angle)
    {
        if (type == Rot::AxisAngle)
        {
            const float angle_a = 0.5f * angle;
            float sin_a = Trig::sin(angle_a);

            Vect qV = v.getNorm();

            qV *= sin_a;

            this->_qx = qV[x];
            this->_qy = qV[y];
            this->_qz = qV[z];
            this->_qw = Trig::cos(angle_a);
        }
    }

    Quat::Quat(Matrix temp)
    {
        float tr = temp.m0() + temp.m5() + temp.m10();
        float S;

        if (tr > 0.0f)
        {
            //Check this again
            S = 2 * Trig::sqrt(tr + 1.0f);
            this->_qw = 0.25f * S;
            this->_qx = -(temp.m9() - temp.m6()) / S;
            this->_qy = -(temp.m2() - temp.m8()) / S;
            this->_qz = -(temp.m4() - temp.m1()) / S;
        }
        else if ((temp.m0() > temp.m5()) && (temp.m0() > temp.m10()))
        {
            S = 2 * Trig::sqrt(1.0f + temp.m0() - temp.m5() - temp.m10());
            this->_qw = -(temp.m9() - temp.m6()) / S;
            this->_qx = 0.25f * S;
            this->_qy = (temp.m1() + temp.m4()) / S;
            this->_qz = (temp.m2() + temp.m8()) / S;
        }
        else if (temp.m5() > temp.m10())
        {
            S = 2 * Trig::sqrt(1.0f + temp.m5() - temp.m0() - temp.m10());
            this->_qw = -(temp.m2() - temp.m8()) / S;
            this->_qx = (temp.m1() + temp.m4()) / S;
            this->_qy = 0.25f * S;
            this->_qz = (temp.m6() + temp.m9()) / S;
        }
        else
        {
            S = 2 * Trig::sqrt(1.0f + temp.m10() - temp.m0() - temp.m5());
            this->_qw = -(temp.m4() - temp.m1()) / S;
            this->_qx = (temp.m2() + temp.m8()) / S;
            this->_qy = (temp.m6() + temp.m9()) / S;
            this->_qz = 0.25f * S;
        }
    }

    Quat::Quat(Special type)
        :_qx(0.0f), _qy(0.0f), _qz(0.0f), _qw(1.0f)
    {
        if (type == Quat::Special::Identity)
        {
            _qw = 1.0f;
        }
    }

    Quat::Quat(Orient type, Vect Forward, Vect Up)
    {
        if (type == Quat::Orient::LocalToWorld)
        {
            Matrix M = Matrix(EngineSpace::Matrix::Orient::LocalToWorld, Forward, Up);
            *this = Quat(M);
        }

        else if (type == Quat::Orient::WorldToLocal)
        {
            Matrix M = Matrix(EngineSpace::Matrix::Orient::WorldToLocal, Forward, Up);
            *this = Quat(M);
        }
    }

    void Quat::set(const float nx, const float ny, const float nz, const float nw)
    {
        this->_mq = _mm_set_ps(nw, nz, ny, nx);
    }

    void Quat::set(const Quat newQuat)
    {
        this->_mq = newQuat._mq;
    }

    void Quat::set(Rot3, float x, float y, float z)
    {
        //Better way to do this?
        Quat temp = Quat(Rot1::X, x) * Quat(Rot1::Y, y) * Quat(Rot1::Z, z);
        this->_mq = temp._mq;
    }

    void Quat::set(Rot1 type, float angle)
    {
        this->_qw = Trig::cos(angle / 2);
        if (type == Rot1::X)
        {
            this->_qx = Trig::sin(angle / 2);
            this->_qy = 0;
            this->_qz = 0;
        }
        else if (type == Rot1::Y)
        {
            this->_qx = 0;
            this->_qy = Trig::sin(angle / 2);
            this->_qz = 0;
        }
        else
        {
            this->_qx = 0;
            this->_qy = 0;
            this->_qz = Trig::sin(angle / 2);
        }
    }

    void Quat::set(Rot type, Vect v, float angle)
    {
        if (type == Rot::AxisAngle)
        {
            const float angle_a = 0.5f * angle;
            float sin_a = Trig::sin(angle_a);

            Vect qV = v.getNorm();

            qV *= sin_a;

            this->_qx = qV[x];
            this->_qy = qV[y];
            this->_qz = qV[z];
            this->_qw = Trig::cos(angle_a);
        }
    }

    void Quat::set(Vect temp, float nw)
    {
        this->_qx = temp.x();
        this->_qy = temp.y();
        this->_qz = temp.z();
        this->_qw = nw;
    }

    void Quat::set(Quat::Special type)
    {
        this->_qx = 0.0f;
        this->_qy = 0.0f;
        this->_qz = 0.0f;
        if (type == Quat::Special::Identity)
        {
            this->_qw = 1.0f;
        }
        else
        {
            this->_qw = 0.0f;
        }

    }

    void Quat::set(Orient type, Vect Forward, Vect Up)
    {
        if (type == Quat::Orient::LocalToWorld)
        {
            Matrix M = Matrix(EngineSpace::Matrix::Orient::LocalToWorld, Forward, Up);
            *this = Quat(M);
        }

        else if (type == Quat::Orient::WorldToLocal)
        {
            Matrix M = Matrix(EngineSpace::Matrix::Orient::WorldToLocal, Forward, Up);
            *this = Quat(M);
        }
    }

    Quat Quat::operator+()
    {
        return Quat(this->_qx, this->_qy, this->_qz, this->_qw);
    }

    Quat Quat::operator-()
    {
        return Quat(-this->_qx, -this->_qy, -this->_qz, -this->_qw);
    }


    float& Quat::qx()
    {
        return this->_qx;
    }

    float Quat::qx() const
    {
        return this->_qx;
    }

    float& Quat::qy()
    {
        return this->_qy;
    }

    float Quat::qy() const
    {
        return this->_qy;
    }

    float& Quat::qz()
    {
        return this->_qz;
    }

    float Quat::qz() const
    {
        return this->_qz;
    }

    float& Quat::real()
    {
        return this->_qw;
    }

    float Quat::real() const
    {
        return this->_qw;
    }

    float& Quat::operator[](const x_enum)
    {
        return this->_qx;
    }

    float Quat::operator[](const x_enum) const
    {
        return this->_qx;
    }

    float& Quat::operator[](const y_enum)
    {
        return this->_qy;
    }

    float Quat::operator[](const y_enum) const
    {
        return this->_qy;
    }

    float& Quat::operator[](const z_enum)
    {
        return this->_qz;
    }

    float Quat::operator[](const z_enum) const
    {
        return this->_qz;
    }

    float& Quat::operator[](const w_enum)
    {
        return this->_qw;
    }

    float Quat::operator[](const w_enum) const
    {
        return this->_qw;
    }

    Quat Quat::operator+(const Quat AddQuat)
    {
        return(Quat(this->_qx + AddQuat._qx, this->_qy + AddQuat._qy, this->_qz + AddQuat._qz, this->_qw + AddQuat._qw));
    }

    Quat Quat::operator+=(const Quat AddQuat)
    {
        this->_qx += AddQuat._qx;
        this->_qy += AddQuat._qy;
        this->_qz += AddQuat._qz;
        this->_qw += AddQuat._qw;

        return *this;
    }

    Quat Quat::operator-(const Quat SubQuat)
    {
        return(Quat(this->_qx - SubQuat._qx, this->_qy - SubQuat._qy, this->_qz - SubQuat._qz, this->_qw - SubQuat._qw));
    }

    Quat Quat::operator-=(const Quat SubQuat)
    {
        this->_qx -= SubQuat._qx;
        this->_qy -= SubQuat._qy;
        this->_qz -= SubQuat._qz;
        this->_qw -= SubQuat._qw;

        return *this;
    }

    Quat Quat::operator+(const float Adder)
    {
        return (Quat(this->_qx + Adder, this->_qy + Adder, this->_qz + Adder, this->_qw + Adder));
    }

    Quat operator + (const float Adder, const Quat& newQuat)
    {
        return (Quat(newQuat._qx + Adder, newQuat._qy + Adder, newQuat._qz + Adder, newQuat._qw + Adder));
    }

    Quat Quat::operator+=(const float Adder)
    {
        this->_qx += Adder;
        this->_qy += Adder;
        this->_qz += Adder;
        this->_qw += Adder;

        return *this;
    }

    Quat Quat::operator-(const float Sub)
    {
        return (Quat(this->_qx - Sub, this->_qy - Sub, this->_qz - Sub, this->_qw - Sub));
    }

    Quat operator - (const float Sub, const Quat& newQuat)
    {
        return (Quat(Sub - newQuat._qx, Sub - newQuat._qy, Sub - newQuat._qz, Sub - newQuat._qw));
    }

    Quat Quat::operator-=(const float Sub)
    {
        this->_qx -= Sub;
        this->_qy -= Sub;
        this->_qz -= Sub;
        this->_qw -= Sub;

        return *this;
    }

    Quat Quat::operator*(const Quat MultiQuat)
    {
        Vect LHS(*this);
        Vect RHS(MultiQuat);

        return (Quat(RHS.cross(LHS) + MultiQuat._qw * LHS + this->_qw * RHS, ((this->_qw * MultiQuat._qw) - LHS.dot(RHS))));
    }

    Quat Quat::operator*=(const Quat MultiQuat)
    {
        Vect LHS(*this);
        Vect RHS(MultiQuat);

        this->_mq = Quat(RHS.cross(LHS) + MultiQuat._qw * LHS + this->_qw * RHS, ((this->_qw * MultiQuat._qw) - LHS.dot(RHS)))._mq;
        return *this;
    }

    Matrix Quat::operator*(const Matrix m)
    {
        Matrix temp = Matrix(*this);
        return (temp * m);
    }

    Matrix Quat::operator *= (const Matrix m)
    {
        Matrix temp = Matrix(*this);
        *this = Quat(temp * m);
        return *this;

    }

    Quat Quat::operator/(const Quat DivQuat)
    {
        return (Quat(this->_qx / DivQuat._qx, this->_qy / DivQuat._qy, this->_qz / DivQuat._qz, this->_qw / DivQuat._qw));
    }

    Quat Quat::operator/=(const Quat DivQuat)
    {
        this->_qx /= DivQuat._qx;
        this->_qy /= DivQuat._qy;
        this->_qz /= DivQuat._qz;
        this->_qw /= DivQuat._qw;
        return *this;
    }

    Quat Quat::operator/(const float div)
    {
        return(Quat(this->_qx / div, this->_qy / div, this->_qz / div, this->_qw / div));
    }

    Quat Quat::operator/= (const float div)
    {
        this->_qx /= div;
        this->_qy /= div;
        this->_qz /= div;
        this->_qw /= div;
        return *this;
    }

    Quat operator / (const float div, const Quat& newQuat)
    {
        return(Quat(div / newQuat._qx, div / newQuat._qy, div / newQuat._qz, div / newQuat._qw));
    }

    Quat Quat::operator*(const float Scale)
    {
        return (Quat(this->_qx * Scale, this->_qy * Scale, this->_qz * Scale, this->_qw * Scale));
    }

    Quat operator * (const float Scale, const Quat& newQuat)
    {
        return (Quat(newQuat._qx * Scale, newQuat._qy * Scale, newQuat._qz * Scale, newQuat._qw * Scale));
    }

    Quat Quat::operator*=(const float Scale)
    {
        this->_qx *= Scale;
        this->_qy *= Scale;
        this->_qz *= Scale;
        this->_qw *= Scale;
        return (*this);
    }

    Quat Quat::norm()
    {
        //Returns the normalized Quat.
        float norm = 1 / this->mag();
        this->_qx *= norm;
        this->_qy *= norm;
        this->_qz *= norm;
        this->_qw *= norm;
        return *this;
    }

    Quat Quat::getNorm()
    {
        float norm = 1 / this->mag();
        return(Quat(this->_qx * norm, this->_qy * norm, this->_qz * norm, this->_qw * norm));
    }

    float Quat::mag()
    {
        return(Trig::sqrt((this->_qx * this->_qx) + (this->_qy * this->_qy) + (this->_qz * this->_qz) + (this->_qw * this->_qw)));
    }

    float Quat::magSquared()
    {
        return((this->_qx * this->_qx) + (this->_qy * this->_qy) + (this->_qz * this->_qz) + (this->_qw * this->_qw));
    }

    float Quat::invMag()
    {
        return(1 / this->mag());
    }

    bool Quat::isNormalized(const float dev)
    {
        bool Norm = true;
        if (this->magSquared() > 1 + dev)
        {
            Norm = false;
        }
        if (this->magSquared() < 1 - dev)
        {
            Norm = false;
        }

        return(Norm);
    }

    void Quat::T()
    {
        this->_qx = -this->_qx;
        this->_qy = -this->_qy;
        this->_qz = -this->_qz;
    }

    Quat Quat::getT()
    {
        return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
    }

    void Quat::conj()
    {
        this->_qx = -this->_qx;
        this->_qy = -this->_qy;
        this->_qz = -this->_qz;
    }

    Quat Quat::getConj()
    {
        return Quat(-this->_qx, -this->_qy, -this->_qz, this->_qw);
    }

    void Quat::inv()
    {
        float nSquare = this->magSquared();

        this->_qx /= -nSquare;
        this->_qy /= -nSquare;
        this->_qz /= -nSquare;
        this->_qw /= nSquare;
    }

    Quat Quat::getInv()
    {
        float nSquare = this->magSquared();

        return(Quat(-this->_qx / nSquare, -this->_qy / nSquare, -this->_qz / nSquare, this->_qw / nSquare));
    }

    Quat Quat::multByElement(const Quat temp)
    {
        return(Quat(this->_qx * temp._qx, this->_qy * temp._qy, this->_qz * temp._qz, this->_qw * temp._qw));
    }

    bool Quat::isEqual(const Quat temp, const float dev)
    {
        Quat test = *this - temp;

        if (test._qx < dev && test._qx > -dev)
        {
            if (test._qy < dev && test._qy > -dev)
            {
                if (test._qz < dev && test._qz > -dev)
                {
                    if (test._qw < dev && test._qw > -dev)
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool Quat::isNegEqual(const Quat temp, const float dev)
    {
        return(this->isEqual(0 - temp, dev));
    }

    bool Quat::isEquivalent(const Quat temp, const float dev)
    {
        if (this->isEqual(temp, dev))
        {
            return true;
        }
        else if (this->isNegEqual(temp, dev))
        {
            return true;
        }

        return false;
    }

    bool Quat::isConjugateEqual(const Quat temp, const float dev)
    {
        return(this->isEqual(Quat(-temp._qx, -temp._qy, -temp._qz, temp._qw), dev));
    }

    bool Quat::isIdentity(const float dev)
    {
        return (this->isEqual(Quat(0.0f, 0.0f, 0.0f, 1.0f), dev));
    }

    bool Quat::isZero(const float dev)
    {
        return (this->isEqual(Quat(0.0f, 0.0f, 0.0f, 0.0f), dev));
    }

    float Quat::dot(const Quat temp)
    {
        return(this->_qx * temp._qx + this->_qy * temp._qy + this->_qz * temp._qz + this->_qw * temp._qw);
    }

    void Quat::Lqcvq(Vect in, Vect& out)
    {
        Vect qV(*this);

        out = 2 * this->_qw * (qV.cross(in)) + in * (this->_qw * this->_qw - qV.dot(qV)) + 2 * (qV.dot(in)) * qV;
    }

    void Quat::Lqvqc(Vect in, Vect& out)
    {
        Vect qV(*this);

        out = 2 * this->_qw * (in.cross(qV)) + in * (this->_qw * this->_qw - qV.dot(qV)) + 2 * (qV.dot(in)) * qV;

    }

    float Quat::getAngle()
    {
        return (2.0f * (Trig::acos(this->_qw)));
    }

    void Quat::getAxis(Vect& out)
    {
        out = Vect(*this);
        out.norm();
    }

    void Quat::getVect(Vect& out)
    {
        out = Vect(*this);
    }

    void Quat::setVect(Vect temp)
    {
        this->_qx = temp.x();
        this->_qy = temp.y();
        this->_qz = temp.z();
    }
}