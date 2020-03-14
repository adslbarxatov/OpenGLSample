////////////////////////////////////////////
// Библиотека глобальных определений

////////////////////////////////////////////
// Подключение заголовочных файлов
#include <stdio.h>			// Главная библиотека IO
#include <conio.h>			// Для getch
#include <windows.h>		// Библиотека для создания окна
#include <math.h>			// Математические функции

#include <gl\gl.h>			// Procedure declarations, constant definitions and macros
							// for the OpenGL component
#include <gl\glu.h>			// ~ for the OpenGL Utility Library
#include "glaux\\glaux.h"	// ~ for the OpenGL Auxiliary (вспомогательной) Library

////////////////////////////////////////////
// Подключение статических библиотек
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glaux\\glaux.lib")
#pragma comment (lib, "glu32.lib")

////////////////////////////////////////////
// Параметры окна
#define	WX0		10					// Позиция и размеры окна
#define	WY0		10
#define	WXM		960
#define	WYM		540
#define WTITLE	" Time-turner"		// Заголовок

////////////////////////////////////////////
// Общие параметры модели
#define	MAXSPEED		0.5			// Максимальная скорость вращения
#define MAXDEEP			16.0		// Максимальное удаление от центра
#define STARTUP_DEEP	10.0
#define	STEP			0.02f		// Шаг смещения / приближения / изменения скорости

#define ROOM_DIM_A		1.77		// Размеры «комнаты» (от центра до края)
#define ROOM_DIM_B		1.0
#define ROOM_DEEP		24.0

#define ALPHABETA_INC_MULT	50		// Множитель инкремента для коллбэков клавиш-стрелок

////////////////////////////////////////////
// Общие параметры колец
#define RESOLUTION	48				// Разбиение краёв кольца (гладкость)

#define RADIUS1		4.0f			// Радиусы колец
#define RADIUS2		3.2f
#define RADIUS3		2.4f
#define	RING_HEIGHT	0.4f			// Толщина колец
#define	RING_WIDTH	0.6f			// Ширина колец

#define BACKGROUND_COLOR	0.10f,0.00f,0.20f
#define FRAMES_COLOR		0.35,0.35,0.35
#define BASE_COLOR			0.10,0.05,0.00
#define RING1_COLOR			0.20,0.20,0.25
#define RING2_COLOR			0.40,0.40,0.45
#define RING3_COLOR			0.30,0.30,0.35

#define RING1_ANGLE_OFFSET	1.00
#define RING2_ANGLE_OFFSET	1.37
#define RING3_ANGLE_OFFSET	1.67

////////////////////////////////////////////
// Общие прототипы
void BuildProjection ();				// Функция формирования комнаты
void CALLBACK MouseMove		(AUX_EVENTREC *event);	// Функция обработки мыши
void CALLBACK Key_LEFT		(void);					// Функции обработки клавиатуры
void CALLBACK Key_RIGHT		(void);
void CALLBACK Key_UP		(void);
void CALLBACK Key_DOWN		(void);
void CALLBACK Key_ZoomOut	(void);
void CALLBACK Key_ZoomIn	(void);
void CALLBACK Key_SpeedUp	(void);
void CALLBACK Key_SpeedDown	(void);

double Alpha (double Increment);		// Функции передачи поворотов
double Beta (double Increment);
double Deep (double Increment);			// Функция передачи глубины
double Speed (double Increment);		// Функция передачи скорости
double Angle (double Increment);		// Функция передачи текущего угла вращения

////////////////////////////////////////////
// Прототипы текущей реализации
void CALLBACK Resize (int width, int height);	// Функция пересчёта изображения при изменении размера окна
void CALLBACK Display (void);					// Главная функция формирования изображения
void ReLight (void);							// Функция пересчёта позиций осветителей
void Ring (GLUquadricObj *QO, double Radius,
	double Width, double Height, int Resolution);	// Функция изображения кольца
