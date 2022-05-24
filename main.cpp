#include <iostream>
#include <math.h>
#include <conio.h>
#include <fstream>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
#define roundf(x) floor(x + 0.5f)
#define P 3.14
using namespace std;

//Класс создания точек
class Linesp
{
public:
	float x; float y;
	void print(Linesp& point) { cout << point.x << point.y; }
};

//Функция окрашивания
void paint()
{
	float dx1, dx2, dx3, dx4;
	float q;
	dx1 = dx2 = dx3 = dx4 = 0;
	for (int i = 0; i < 1920; i++)
	{
		for (int j = 0; j < 1080; j++)
		{
			if (getpixel(i, j) == YELLOW)
			{
				if (dx1 == 0)  dx1 = j + 1;
				else
				{
					if (dx2 == 0) dx2 = j - 1;
					else if (dx3 == 0) dx3 = j + 1; else dx4 = j - 1;
				}
			}
		}
		setcolor(RED);
		if ((dx1 != 0 && dx2 != 0) || (dx3 != 0 && dx4 != 0)) { line(i, dx1, i, dx2); line(i, dx3, i, dx4); }
		dx1 = dx2 = dx3 = dx4 = 0;
	}
}
float moveline(float a, float d) { a += d; return a; } //Функция для перемещения линии.
float centx(float a, float b) { float cx = (b + a) / 2; return cx; } //Центр по x
float centy(float a, float b) { float cy = (b + a) / 2; return cy; } //Центр по y
float lenx(float a, float b) { float l = b - a; return l; } //Длина по x
float leny(float a, float b) { float l = b - a; return l; } //Длина по y
float mashtabs(float a, float b, float xe, float l, float e) //Функция для масштабирования.
{
	float sl, dl, al;
	if (a == b) return a;
	else { sl = l * e; dl = sl / 2; al = xe - dl; return al; }
}
float mashtabe(float a, float b, float xe, float l, float e) //Функция для масштабирования.
{
	float sl, dl, bl;
	if (a == b) return a;
	else { sl = l * e; dl = sl / 2; bl = xe + dl; return bl; }
}
float rmoves(float a, float b) { float m = a - b; return m; } 
float rmovee(float a, float b) { float m = a + b; return m; }
float rotatelinex(float a, float b, float u) // Функция для поворота точки относительно x.
{
	float d = cos(u * P / 180); float f = sin(u * P / 180);
	float rot = a * d - b * f; return rot;
}
float rotateliney(float a, float b, float u) // Функция для поворота точки относительно y.
{
	float d = cos(u * P / 180); float f = sin(u * P / 180);
	float rot = a * f + b * d; return rot;
}
void figure(int a, int b, int c, int d, int e, int f, int g, int h)
{
	setcolor(YELLOW);
	line(a, b, c, d);
	line(c, d, e, f);
	line(e, f, g, h);
	line(g, h, a, b);
}
int main()
{
	setlocale(LC_ALL, "Rus");
	//Ввод точек.
	Linesp A, B, C, D;
	ifstream fp("points.txt");
	fp >> A.x; fp >> A.y;
	fp >> B.x; fp >> B.y;
	fp >> C.x; fp >> C.y;
	fp >> D.x; fp >> D.y;

	//Все переменные для работы
	int g = 1, r = 1, k = 1;
	float mx, my, lx, ly;
	int p = 0;
	initwindow(1920, 1080); //Открытие графического интерфейса
	figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); //Создание фигуры
	cout << "Горячие клавиши программы." << endl << endl;
	cout << "Режимы работы:" << endl;
	cout << "m - перемещение." << endl;
	cout << "s - масштабирование." << endl;
	cout << "r - вращение." << endl ;
	cout << "p - закраска." << endl << endl;
 	cout << "Для взаимодействия используются следующие клавиши: w,a,s,d" << endl;
	cout << "0 - выход из любого режима." << endl;
	while (r != 0)
	{
		cout << endl << "Главный центр." << endl;
		switch (_getch())
		{
		case 'm': //Перемещение фигуры
			cout << endl << "Режим перемещения." << endl;
			while (k != 0)
			{
				switch (_getch())
				{
				case 'w': //Вверх
					A.y = moveline(A.y, -10); B.y = moveline(B.y, -10);
					C.y = moveline(C.y, -10); D.y = moveline(D.y, -10);
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); break;
				case 'a':  //Влево
					A.x = moveline(A.x, -10); B.x = moveline(B.x, -10);
					C.x = moveline(C.x, -10); D.x = moveline(D.x, -10);
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); break;
				case 's': //Вниз
					A.y = moveline(A.y, 10); B.y = moveline(B.y, 10);
					C.y = moveline(C.y, 10); D.y = moveline(D.y, 10);
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); break;
				case 'd': //Вправо
					A.x = moveline(A.x, 10); B.x = moveline(B.x, 10);
					C.x = moveline(C.x, 10); D.x = moveline(D.x, 10);
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); break;
				case '0': if (p == 1) paint(); k = 0; break;
				}
			}
			k = 1; break;
		case 's':
			cout << endl << "Режим масштабирования." << endl;
			while (k != 0)
			{
				switch (_getch())
				{
				case 'w': //Увеличение фигуры.
					if (A.y < C.y) { my = centy(A.y, C.y); ly = leny(A.y, C.y); A.y = mashtabs(A.y, C.y, my, ly, 1.1); C.y = mashtabe(A.y, C.y, my, ly, 1.1); }
					else { my = centy(C.y, A.y); ly = leny(C.y, A.y); C.y = mashtabs(C.y, A.y, my, ly, 1.1); A.y = mashtabe(C.y, A.y, my, ly, 1.1); }
					if (B.y < D.y) { my = centy(B.y, D.y); ly = leny(B.y, D.y); B.y = mashtabs(B.y, D.y, my, ly, 1.1); D.y = mashtabe(B.y, D.y, my, ly, 1.1); }
					else { my = centy(D.y, B.y); ly = leny(D.y, B.y); D.y = mashtabs(D.y, B.y, my, ly, 1.1); B.y = mashtabe(D.y, B.y, my, ly, 1.1); }
					if (A.x < C.x) { mx = centx(A.x, C.x); lx = lenx(A.x, C.x); A.x = mashtabs(A.x, C.x, mx, lx, 1.1); C.x = mashtabe(A.x, C.x, mx, lx, 1.1); }
					else { mx = centx(C.x, A.x); lx = lenx(C.x, A.x); C.x = mashtabs(C.x, A.x, mx, lx, 1.1); A.x = mashtabe(C.x, A.x, mx, lx, 1.1); }
					if (B.x < D.x) { mx = centx(B.x, D.x); lx = lenx(B.x, D.x); B.x = mashtabs(B.x, D.x, mx, lx, 1.1); D.x = mashtabe(B.x, D.x, mx, lx, 1.1); }
					else { mx = centx(D.x, B.x); lx = lenx(D.x, B.x); D.x = mashtabs(D.x, B.x, mx, lx, 1.1); B.x = mashtabe(D.x, B.x, mx, lx, 1.1); }
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); if (p == 1) paint(); break;
				case 's': //Уменьшение фигуры
					if (A.y < C.y) { my = centy(A.y, C.y); ly = leny(A.y, C.y); A.y = mashtabs(A.y, C.y, my, ly, 0.9); C.y = mashtabe(A.y, C.y, my, ly, 0.9); }
					else { my = centy(C.y, A.y); ly = leny(C.y, A.y); C.y = mashtabs(C.y, A.y, my, ly, 0.9); A.y = mashtabe(C.y, A.y, my, ly, 0.9); }
					if (B.y < D.y) { my = centy(B.y, D.y); ly = leny(B.y, D.y); B.y = mashtabs(B.y, D.y, my, ly, 0.9); D.y = mashtabe(B.y, D.y, my, ly, 0.9); }
					else { my = centy(D.y, B.y); ly = leny(D.y, B.y); D.y = mashtabs(D.y, B.y, my, ly, 0.9); B.y = mashtabe(D.y, B.y, my, ly, 0.9); }
					if (A.x < C.x) { mx = centx(A.x, C.x); lx = lenx(A.x, C.x); A.x = mashtabs(A.x, C.x, mx, lx, 0.9); C.x = mashtabe(A.x, C.x, mx, lx, 0.9); }
					else { mx = centx(C.x, A.x); lx = lenx(C.x, A.x); C.x = mashtabs(C.x, A.x, mx, lx, 0.9); A.x = mashtabe(C.x, A.x, mx, lx, 0.9); }
					if (B.x < D.x) { mx = centx(B.x, D.x); lx = lenx(B.x, D.x); B.x = mashtabs(B.x, D.x, mx, lx, 0.9); D.x = mashtabe(B.x, D.x, mx, lx, 0.9); }
					else { mx = centx(D.x, B.x); lx = lenx(D.x, B.x); D.x = mashtabs(D.x, B.x, mx, lx, 0.9); B.x = mashtabe(D.x, B.x, mx, lx, 0.9); }
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); break;
				case '0': k = 0; if (p == 1) paint(); break;
				}
			}
			k = 1; break;
		case 'r':
			cout << endl << "Режим вращения." << endl;
			while (k != 0)
			{
				switch (_getch())
				{
				case 'a': //Поворот налево
					mx = (A.x + C.x) / 2;
					my = (A.y + C.y) / 2;
					A.x = rmoves(A.x, mx); A.y = rmoves(A.y, my); B.x = rmoves(B.x, mx); B.y = rmoves(B.y, my);
					C.x = rmoves(C.x, mx); C.y = rmoves(C.y, my); D.x = rmoves(D.x, mx); D.y = rmoves(D.y, my);
					A.x = rotatelinex(A.x, A.y, 1); A.y = rotateliney(A.x, A.y, 1);
					B.x = rotatelinex(B.x, B.y, 1); B.y = rotateliney(B.x, B.y, 1);
					C.x = rotatelinex(C.x, C.y, 1); C.y = rotateliney(C.x, C.y, 1);
					D.x = rotatelinex(D.x, D.y, 1); D.y = rotateliney(D.x, D.y, 1);
					A.x = rmovee(A.x, mx); A.y = rmovee(A.y, my); B.x = rmovee(B.x, mx); B.y = rmovee(B.y, my);
					C.x = rmovee(C.x, mx); C.y = rmovee(C.y, my); D.x = rmovee(D.x, mx); D.y = rmovee(D.y, my);
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y);
					break;
				case 'd': //Поворот направо
					mx = (A.x + C.x) / 2;
					my = (A.y + C.y) / 2;
					A.x = rmoves(A.x, mx); A.y = rmoves(A.y, my); B.x = rmoves(B.x, mx); B.y = rmoves(B.y, my);
					C.x = rmoves(C.x, mx); C.y = rmoves(C.y, my); D.x = rmoves(D.x, mx); D.y = rmoves(D.y, my);
					A.x = rotatelinex(A.x, A.y, -1); A.y = rotateliney(A.x, A.y, -1);
					B.x = rotatelinex(B.x, B.y, -1); B.y = rotateliney(B.x, B.y, -1);
					C.x = rotatelinex(C.x, C.y, -1); C.y = rotateliney(C.x, C.y, -1);
					D.x = rotatelinex(D.x, D.y, -1); D.y = rotateliney(D.x, D.y, -1);
					A.x = rmovee(A.x, mx); A.y = rmovee(A.y, my); B.x = rmovee(B.x, mx); B.y = rmovee(B.y, my);
					C.x = rmovee(C.x, mx); C.y = rmovee(C.y, my); D.x = rmovee(D.x, mx); D.y = rmovee(D.y, my);
					cleardevice(); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y); if (p == 1) paint();
					break;
				case '0': if (p == 1) paint(); k = 0; break;
				}
			}
			k = 1; break;
		case 'p': //Окраска
			paint();
			setcolor(YELLOW); figure(A.x, A.y, B.x, B.y, C.x, C.y, D.x, D.y);
			p = 1;
			cout << endl << "Окрашено." << endl;
			break;
		case '0': r = 0; break;
		}
	}
	closegraph(); //Закрытие графического интерфейса.
	fp.close();
	return 0;
}
