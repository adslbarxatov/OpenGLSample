// Общая библиотека
#include "OpenGLSample.h"

// Глобальные переменные
double alpha = 0, beta = 0,		// Углы поворота пространства
	deep = STARTUP_DEEP,		// Отдаление от центра
	currentAngle = 0,			// Текущий угол вращения
	angleIncrement = 2 * STEP;	// Смещение угла вращения

// Отображение проекции
void BuildProjection ()
	{
	glMatrixMode	(GL_PROJECTION);	// Режим проекции
	glLoadIdentity	();					// Очистка матрицы преобразования

	glFrustum		(-ROOM_DIM_A, ROOM_DIM_A, -ROOM_DIM_B, ROOM_DIM_B, 1.0, ROOM_DEEP);		// Инициализация комнаты
	gluLookAt							// Установка точки и направления наблюдения:
		(0.0, 0.0, deep,				// расположение глаз
		0.0, 0.0, 0.0,					// центр комнаты
		0.0, 1.0, 0.0);					// направление взгляда

	glMatrixMode	(GL_MODELVIEW);		// Режим модели
	}

// Изменение размера окна
void CALLBACK Resize (int Width, int Height)
	{
	glViewport		(0, 0, Width, Height);		// Размеры поля видимости окна

	BuildProjection ();
	}    

// Обработка мыши
void CALLBACK MouseMove (AUX_EVENTREC *event)
	{
	alpha = event->data[AUX_MOUSEX] - WXM / 2;
	beta = event->data[AUX_MOUSEY] - WYM / 2;
	}

// Обработка клавиатуры
void CALLBACK Key_LEFT (void)
	{
	Alpha (-ALPHABETA_INC_MULT * STEP);
	}

void CALLBACK Key_RIGHT (void)
	{
	Alpha (ALPHABETA_INC_MULT * STEP);
	}

void CALLBACK Key_UP (void)
	{
	Beta (-ALPHABETA_INC_MULT * STEP);
	}

void CALLBACK Key_DOWN (void)
	{
	Beta (ALPHABETA_INC_MULT * STEP);
	}

void CALLBACK Key_ZoomOut (void)
	{
	Deep (5 * STEP);

	BuildProjection ();
	}

void CALLBACK Key_ZoomIn (void)
	{
	Deep (-5 * STEP);

	BuildProjection ();
	}

void CALLBACK Key_SpeedUp (void)
	{
	Speed (STEP);
	}

void CALLBACK Key_SpeedDown (void)
	{
	Speed (-STEP);
	}

// Методы, изменяющие глобальные параметры модели
double Alpha (double Increment)
	{
	alpha += Increment;

	return alpha;
	}

double Beta (double Increment)
	{
	beta += Increment;

	return beta;
	}

double Deep (double Increment)
	{
	deep += Increment;

	// Зацикливание пространства
	if (deep > MAXDEEP)
		deep = 0.0;
	if (deep < 0.0)
		deep = MAXDEEP;

	return deep;
	}

double Speed (double Increment)
	{
	angleIncrement += Increment;

	if (angleIncrement < -MAXSPEED)
		angleIncrement = -MAXSPEED;
	if (angleIncrement > MAXSPEED)
		angleIncrement = MAXSPEED;

	return angleIncrement;
	}

double Angle (double Increment)
	{
	currentAngle += angleIncrement;

	return currentAngle;
	}
