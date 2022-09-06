#pragma once
#include "Graphics+.h"
#include "Sphere.h"

int main()
{
	setlocale(LC_CTYPE, "rus");
	srand((unsigned)time(NULL));
	::SetConsoleTitle(L"Graphics");
	::system("mode con cols=120 lines=70");

	hWnd = GetConsoleWindow();
	gr::InitGraphics(hWnd);
	int wid = gr::GetWid();
	int heg = gr::GetHeg();

	Sleep(50);
	std::vector<Sphere> spheres;
	//Создаем наши "планеты"
	Sphere mercury(0.1f, 0.0f, 5, 16, RGB(73, 73, 73));
	Sphere venus(0.2f, 0.0f, 7, 14, RGB(185, 122, 87));
	Sphere earth(0.3f, 0.0f, 6, 12, RGB(0, 255, 255));
	Sphere mars(0.4f, 0.0f, 5, 10, RGB(255, 0, 0));
	Sphere jupiter(0.5f, 0.0f, 15, 8, RGB(200, 100, 100));
	Sphere saturn(0.6f, 0, 12, 6, RGB(163, 73, 150));
	Sphere uran(0.7f, 0, 9, 4, RGB(0, 50, 255));
	Sphere neptun(0.8f, 0, 10, 2, RGB(0, 150, 255));

	spheres.push_back(mercury);
	spheres.push_back(venus);
	spheres.push_back(earth);
	spheres.push_back(mars);
	spheres.push_back(jupiter);
	spheres.push_back(saturn);
	spheres.push_back(uran);
	spheres.push_back(neptun);
	//Вызываем анимацию
	AnimSphere(gr::dcMem, spheres);

	cin.get();
	return 0;
}
