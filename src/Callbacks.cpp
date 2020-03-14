// ����� ����������
#include "OpenGLSample.h"

// ���������� ����������
int mouseX0, mouseY0 = -10000;	// ��������� �������� ����
double alpha = 0, beta = 0,		// ���� �������� ������������
	deep = STARTUP_DEEP,		// ��������� �� ������
	currentAngle = 0,			// ������� ���� ��������
	angleIncrement = 2 * STEP;	// �������� ���� ��������

// ��������� ������� ����
void CALLBACK Resize (int Width, int Height)
	{
	glViewport		(0, 0, Width, Height);		// ������� ���� ��������� ����
	glMatrixMode	(GL_PROJECTION);
	glLoadIdentity	();							// ������� ������� ��������������

	glFrustum		(-ROOM_DIM_A, ROOM_DIM_A, -ROOM_DIM_B, ROOM_DIM_B, 1.0, ROOM_DEEP);

	gluLookAt		(0.0, 0.0, deep,			// ������� ���������� (���� ������)
					 0.0, 0.0, 0.0,				// �����������
					 0.0, 1.0, 0.0);			// 1 = ����������� �����
	glMatrixMode	(GL_MODELVIEW);
	}    

// ��������� ����
void CALLBACK MouseMove (AUX_EVENTREC *event)
	{
	mouseX0 = event->data[AUX_MOUSEX];
	mouseY0 = event->data[AUX_MOUSEY];

//	Alpha (mouseY0);
//	Beta (mouseY0);
	}

// ��������� ����������
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
	glMatrixMode	(GL_PROJECTION);
	glLoadIdentity	();

	glFrustum		(-ROOM_DIM_A, ROOM_DIM_A, -ROOM_DIM_B, ROOM_DIM_B, 1.0, ROOM_DEEP);

	gluLookAt		(0.0, 0.0, Deep (0),
					 0.0, 0.0, 0.0,
					 0.0, 1.0, 0.0);
	glMatrixMode	(GL_MODELVIEW);
	}

void CALLBACK Key_ZoomIn (void)
	{
	Deep (-5 * STEP);
	glMatrixMode	(GL_PROJECTION);
	glLoadIdentity	();

	glFrustum		(-ROOM_DIM_A, ROOM_DIM_A, -ROOM_DIM_B, ROOM_DIM_B, 1.0, ROOM_DEEP);

	gluLookAt		(0.0, 0.0, Deep (0),
					 0.0, 0.0, 0.0,
					 0.0, 1.0, 0.0);
	glMatrixMode	(GL_MODELVIEW);
	}

void CALLBACK Key_SpeedUp (void)
	{
	Speed (STEP);
	}

void CALLBACK Key_SpeedDown (void)
	{
	Speed (-STEP);
	}

// ������, ���������� ���������� ��������� ������
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

	// ������������ ������������
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
