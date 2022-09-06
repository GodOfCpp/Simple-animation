#pragma once
#include "Graphics+.h"

void VisStar(HDC);

class Sphere
{
private:
	//��������������� ����������
	//�������� ����������
	//������ ����� �������� � ��������
	float R; //������ �����
	COLORREF col{ 0 }; //���� �����
	bool Hit(int, int, float*); // ����� ���������� ����������� ����������� �����
	float xn, yn; //���������� ������ � ��������������� ����
	float k; //����������, ������� ����� ����� ��� ��������
	float speed; //�������� ��������� �����
	int gr; // �� ������� �������� ������ ��������� ����� (���������� �� 0)
	POINT ctr; // ���������� ������ ����� � �������� ����
public:
	//������������� ���������� � ������������
	Sphere(float xn_, float yn_, float R_, float speed_, COLORREF col_)
		: xn(xn_), yn(yn_), R(R_), col(col_), speed(speed_), gr(0) {
		gr::WinCoor(ctr, xn, yn); k = xn;
	}
	void VisSphere(HDC); //����� ��� ������������ �����
	//�������
	void setXN(float xn)   { this->xn = xn; }
	void setYN(float yn)   { this->yn = yn; }
	void setGR(int gr)     { this->gr = gr; }
	//�������
	float getXN() const    { return xn;     }
	float getYN() const    { return yn;     }
	float getSpeed() const { return speed;  }
	float getK() const	   { return k;      }
	int getGR() const      { return gr;     }
	POINT* getCenter()     { return &ctr;   }
	COLORREF getCol()      { return col;    }
};

bool Sphere::Hit(int wx, int wy, float* n)
{
	//�� �������������� �������� ��������� ������
	// ����������� ��� ���������� ������ �����
	// ��� �������� ������
	float dx = float(wx - ctr.x);
	float dy = float(wy - ctr.y);
	float dz;
	if ((dx * dx + dy * dy) < R * R)
	{
		dz = sqrt(R * R - dx * dx - dy * dy);
		*n = dz / R;
		return true;
	}
	return false;
}

void Sphere::VisSphere(HDC dc)
{
	int y, x;
	float n; //����������� ����������
	BYTE r, g, b;

	int wid = gr::GetWid();
	int heg = gr::GetHeg();

	for (y = 0; y < heg; y++)
	{
		for (x = 0; x < wid; x++)
		{
// ��� �� � ���������� ���� �����������, ����������� ������
// ����� ����� ��������
			if (Hit(x, y, &n) == true) 
			{
				r = (BYTE)(GetRValue(col) * n);
				g = (BYTE)(GetGValue(col) * n);
				b = (BYTE)(GetBValue(col) * n);
				gr::Point(dc, x, y, RGB(r, g, b));
			}
		}
	}
}


//������� ��� �������� ���� ����
void AnimSphere(HDC dc, std::vector<Sphere> spheres)
{
	float rad = 0.0174533f;
	float alfa;
	int wid = gr::GetWid();
	int heg = gr::GetHeg();

	Sphere sp(0.0f, 0.0f, 40, 0, RGB(249, 215, 28));

	gr::Set_brush(dc, RGB(0, 0, 0), true);
	gr::Set_pen(dc, RGB(0, 0, 0), 1);
	int counter = 1;
	while (!_kbhit())
	{
		Rectangle(dc, 0, 0, wid - 1, heg - 1);
		sp.VisSphere(dc);

		for (int i = 0; i < spheres.size(); i++) { spheres[i].VisSphere(dc); }

		for (int i = 0; i < spheres.size(); i++) {
			spheres[i].getGR() > 0 ? spheres[i].setGR(spheres[i].getGR() - spheres[i].getSpeed()) : spheres[i].setGR(360);
			alfa = spheres[i].getGR() * rad;
			spheres[i].setXN(spheres[i].getK() * cos(alfa));
			spheres[i].setYN(spheres[i].getK() * sin(alfa));
			gr::WinCoor(*(spheres[i].getCenter()), spheres[i].getXN(), spheres[i].getYN());
			Sleep(5);
		}
		if (counter%3 == 0) VisStar(dc);
			counter++;
		// BitBlt ������������ ��� ��������� �������� ��� ��������� ����
		// ����������� ������� ����������� � ������, � �����
		// ��������������� � �������
		BitBlt(gr::dc, 0, 0, wid, heg, gr::dcMem, 0, 0, SRCCOPY);
	}
}

//=======================================================================

struct Star
{
public:
	COLORREF col;
	int x, y;
	Star();
};

Star::Star()
{
	int wid = gr::GetWid();
	int heg = gr::GetHeg();
	x = rand() % wid;
	y = rand() % heg;

	BYTE r, g, b;
	r = 255;
	g = 255;
	b = 255;
	col = RGB(r, g, b);
}
// ������������ �����
void VisStar(HDC dc)
{
	Star star[25];
	int x, y, x1, y1, x2, y2;
	for (int i = 0; i < 25; i++)
	{
		gr::Set_pen(dc, star[i].col, 1);
		x = star[i].x;
		y = star[i].y;

		x1 = x - 3;	y1 = y;
		x2 = x + 3; y2 = y;
		gr::Line(dc, x1, y1, x2, y2);

		x1 = x;	y1 = y - 3;
		x2 = x; y2 = y + 3;
		gr::Line(dc, x1, y1, x2, y2);

		x1 = x - 3;	y1 = y - 3;
		x2 = x + 3; y2 = y + 3;
		gr::Line(dc, x1, y1, x2, y2);

		x1 = x + 3;	y1 = y - 3;
		x2 = x - 3; y2 = y + 3;
		gr::Line(dc, x1, y1, x2, y2);
	}
}

