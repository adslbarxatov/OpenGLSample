////////////////////////////////////////////
// ���������� ���������� �����������

////////////////////////////////////////////
// ����������� ������������ ������
#include <stdio.h>			// ������� ���������� IO
#include <conio.h>			// ��� getch
#include <windows.h>		// ���������� ��� �������� ����
#include <math.h>			// �������������� �������

#include <gl\gl.h>			// Procedure declarations, constant definitions and macros
							// for the OpenGL component
#include <gl\glu.h>			// ~ for the OpenGL Utility Library
#include "glaux.h"			// ~ for the OpenGL Auxiliary (���������������) Library

////////////////////////////////////////////
// ����������� ����������� ���������
#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "glaux.lib")
#pragma comment (lib, "glu32.lib")

////////////////////////////////////////////
// ��������� ����
#define	WX0		10						// ������� � ������� ����
#define	WY0		10
#define	WXM		960
#define	WYM		540
#define WTITLE	" ��������� ��������"	// ���������

////////////////////////////////////////////
// ����� ��������� ������
#define	MAXSPEED		0.5			// ������������ �������� ��������
#define MAXDEEP			16.0		// ������������ �������� �� ������
#define STARTUP_DEEP	10.0
#define	STEP			0.02f		// ��� �������� / ����������� / ��������� ��������

#define ROOM_DIM_A		1.77		// ������� ��������� (�� ������ �� ����)
#define ROOM_DIM_B		1.0
#define ROOM_DEEP		24.0

#define ALPHABETA_INC_MULT	50		// ��������� ���������� ��� ��������� ������-�������

////////////////////////////////////////////
// ����� ��������� �����
#define RESOLUTION	48				// ��������� ���� ������ (���������)

#define RADIUS1		4.0f			// ������� �����
#define RADIUS2		3.2f
#define RADIUS3		2.4f
#define	RING_HEIGHT	0.4f			// ������� �����
#define	RING_WIDTH	0.6f			// ������ �����

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
// ����� ���������
void CALLBACK MouseMove		(AUX_EVENTREC *event);	// ������� ��������� ����
void CALLBACK Key_LEFT		(void);					// ������� ��������� ����������
void CALLBACK Key_RIGHT		(void);
void CALLBACK Key_UP		(void);
void CALLBACK Key_DOWN		(void);
void CALLBACK Key_ZoomOut	(void);
void CALLBACK Key_ZoomIn	(void);
void CALLBACK Key_SpeedUp	(void);
void CALLBACK Key_SpeedDown	(void);

double Alpha (double Increment);		// ������� �������� ���������
double Beta (double Increment);
double Deep (double Increment);			// ������� �������� �������
double Speed (double Increment);		// ������� �������� ��������
double Angle (double Increment);		// ������� �������� �������� ���� ��������

////////////////////////////////////////////
// ��������� ������� ����������
void CALLBACK Resize (int width, int height);	// ������� ��������� ����������� ��� ��������� ������� ����
void CALLBACK Display (void);					// ������� ������� �����������
void ReLight (void);							// ������� ��������� ������� �����������
void Ring (GLUquadricObj *QO, double Rd,
		   double Wdth, double Hgh, int Gr);	// ������� ����������� ������
