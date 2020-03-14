// ����� ����������
#include "OpenGLSample.h"

// ��������� �� �������� � �� � ������
GLUquadricObj *QObj;

// �������� ���������� �������
void main (void)
	{
	// ������� ��������� (����������: �����-������ (x), �����-���� (y), �����-����� (z))
	GLfloat	Mat_AmDf[] = {0.0f, 0.0f, 0.0f, 1.0f},	// ������� ����� � ��������
			Mat_Spec[] = {1.0f, 1.0f, 1.0f, 1.0f},	// ������� ������������
			Mat_Emis[] = {0.0f, 0.0f, 0.0f, 1.0f},	// ������� ����������� �����
			Shin = 75.0;							// ����� ([0; 128]; ��� ������, ��� ����

	// ������ ������� �� ����������
	printf ("\n Keyboard usage:\n");
	printf ("  \x18\x19\x1A\x1B  - model roration;\n");
	printf ("  1 / 2 - model zoom in / out;\n");
	printf ("  4 / 5 - acceleration / deceleration of rings rotation\n");
	printf ("          (negative speed = rotation reverse);\n");
	printf ("  Mouse - model rotation");
	printf ("\n\n Press any key to continue...");
	_getch ();

	// ������������� ����
	auxInitPosition			(WX0, WY0, WXM, WYM);				// ��������� ������� ����
	auxInitDisplayMode		(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);	// ������ ����
	auxInitWindow			(WTITLE);							// ��������� ����

	// ������� �����������
	auxIdleFunc				(Display);							// �����������
	auxReshapeFunc			(Resize);							// ��������� �������� ����

	// ������� ���������� � ��������� �������������� �����������
	glEnable				(GL_LIGHTING);						// ��������� ������ ���������
	glEnable				(GL_LIGHT0);						// ����� ����������
	glEnable				(GL_DEPTH_TEST);					// ��������� �����

	// ��������� ���������
	glMaterialfv			(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Mat_AmDf);
	glMaterialfv			(GL_FRONT_AND_BACK, GL_SPECULAR, Mat_Spec);
	glMaterialfv			(GL_FRONT_AND_BACK, GL_EMISSION, Mat_Emis);	// ���������� ����
	glMaterialf				(GL_FRONT_AND_BACK, GL_SHININESS, Shin);
	glEnable				(GL_COLOR_MATERIAL);			// ��������� ����� ���������

	// ������� ��������� ������ (������� � BaseFunctions)
	auxKeyFunc			(AUX_LEFT, Key_LEFT);
	auxKeyFunc			(AUX_RIGHT, Key_RIGHT);
	auxKeyFunc			(AUX_UP, Key_UP);
	auxKeyFunc			(AUX_DOWN, Key_DOWN);
	auxKeyFunc			('1', Key_ZoomIn);
	auxKeyFunc			('2', Key_ZoomOut);
	auxKeyFunc			('4', Key_SpeedUp);
	auxKeyFunc			('5', Key_SpeedDown);

	// ������� ��������� ����
	auxMouseFunc		(AUX_LEFTBUTTON, AUX_MOUSELOC, MouseMove);

	// ���������
	ReLight				();

	// ������� ��������� (����)
	auxMainLoop			(Display);
	}

// ������� ������� �����������
void CALLBACK Display (void)
	{
	// ��������
	Angle (Speed (0));

	// ������� ������
	glClear				(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor		(BACKGROUND_COLOR, 0.0f);		// ���� ����
	glPushMatrix		();

	// ����������� �������� � �������� �������
	glRotated			(Alpha (0), 0, 1, 0);
	glRotated			(Beta (0), 0, 0, 1);
	glRotated			(45, 0, -1, 0);

	// ����������� � ��������� �����
	QObj = gluNewQuadric	(); 
	gluQuadricDrawStyle		(QObj, GLU_FILL); 

	////////////////////////////////
	// �-�������� �����
	glColor3d			(FRAMES_COLOR);
	glTranslated		(0.0, 0.0, -RING_HEIGHT);
		glRotated			(180, 1, 0, 0);
		gluPartialDisk		(QObj, RADIUS1 + 1.0, RADIUS1 + 2.0, RESOLUTION, RESOLUTION, 225, 180);
		glRotated			(180, -1, 0, 0);
	glTranslated		(0.0, 0.0, RING_HEIGHT - 0.01);
		gluPartialDisk		(QObj, RADIUS1 + 1.0, RADIUS1 + 2.0, RESOLUTION, RESOLUTION, 135, 180);
	glTranslated		(0.0, 0.0, 0.02);
		glRotated			(180, 1, 0, 0);
		gluPartialDisk		(QObj, RADIUS1 + 1.0, RADIUS1 + 2.0, RESOLUTION, RESOLUTION, 225, 180);
		glRotated			(180, -1, 0, 0);
	glTranslated		(0.0, 0.0, RING_HEIGHT - 0.01);
		gluPartialDisk		(QObj, RADIUS1 + 1.0, RADIUS1 + 2.0, RESOLUTION, RESOLUTION, 135, 180);
	glTranslated		(0.0, 0.0, -RING_HEIGHT);

	// ��������� �������� ������
	glRotated			(45, 0, 0, 1);
	glTranslated		(0.0, (RADIUS1 + 1.5), 0.0);
	auxSolidBox			(1.0, 1.0, 2 * RING_HEIGHT);
	glTranslated		(0.0, -2 * (RADIUS1 + 1.5), 0.0);
	auxSolidBox			(1.0, 1.0, 2 * RING_HEIGHT);
	glTranslated		(0.0, (RADIUS1 + 1.5), 0.0);
	glRotated			(45, 0, 0, -1);

	// ��������
	glTranslated		(0.0, -(RADIUS1 + 2.0), 0.0);
	auxSolidBox			(2.0, 2.0, 2 * RING_HEIGHT);

	glColor3d			(BASE_COLOR);
	glTranslated		(0.0, -1.0, 0.0);
	auxSolidBox			(4.0, RING_HEIGHT, 7.0);
	glTranslated		(0.0, (RADIUS1 + 3.0), 0.0);

	////////////////////////////////
	// ������� ������
	glColor3d			(RING1_COLOR);

	glRotated			(45, 0, 0, 1);
	glTranslated		(0, RADIUS1, 0);
		glRotated			(90, -1, 0, 0);
		gluCylinder			(QObj, RING_HEIGHT / 2.0, RING_HEIGHT / 2.0, 1.0, RESOLUTION, RESOLUTION);
		glRotated			(90, 1, 0, 0);
	glTranslated		(0, -2 * RADIUS1, 0);
		glRotated			(90, 1, 0, 0);
		gluCylinder			(QObj, RING_HEIGHT / 2.0, RING_HEIGHT / 2.0, 1.0, RESOLUTION, RESOLUTION);
		glRotated			(90, -1, 0, 0);
	glTranslated		(0, RADIUS1, 0);
	
	// ������ �������� ��������
	glRotated			(RING1_ANGLE_OFFSET * Angle (0), 0, 1, 0);

	// ������� ������
	Ring				(QObj, RADIUS1, RING_WIDTH, RING_HEIGHT, RESOLUTION);

	// ������� ������� �����
	glRotated			(45, 0, 0, -1);

	////////////////////////////////
	// ������� �����
	glColor3d			(RING2_COLOR);

	glRotated			(-45, 0, 0, 1);
	glTranslated		(0, RADIUS2 - RING_WIDTH, 0);
		glRotated			(90, -1, 0, 0);
		gluCylinder			(QObj, RING_HEIGHT / 2.0, RING_HEIGHT / 2.0, RADIUS1 - RADIUS2, RESOLUTION, RESOLUTION);
		glRotated			(90, 1, 0, 0);
	glTranslated		(0, -2 * (RADIUS2 - RING_WIDTH), 0);
		glRotated			(90, 1, 0, 0);
		gluCylinder			(QObj, RING_HEIGHT / 2.0, RING_HEIGHT / 2.0, RADIUS1 - RADIUS2, RESOLUTION, RESOLUTION);
		glRotated			(90, -1, 0, 0);
	glTranslated		(0, RADIUS2 - RING_WIDTH, 0);

	// ������ ����������� ��������
	glRotated			(RING2_ANGLE_OFFSET * Angle (0), 0, 1, 0);
	// �����-������ �������� ����������� (��� ������� �����������)

	// ������
	Ring				(QObj, RADIUS2, RING_WIDTH, RING_HEIGHT, RESOLUTION);

	// ������� �����
	glRotated			(-45, 0, 0, -1);

	////////////////////////////////
	// ���������� �����
	glColor3d			(RING3_COLOR);

	glRotated			(45, 0, 0, 1);
	glTranslated		(0, RADIUS3 - RING_WIDTH, 0);
		glRotated			(90, -1, 0, 0);
		gluCylinder			(QObj, RING_HEIGHT / 2.0, RING_HEIGHT / 2.0, RADIUS2 - RADIUS3, RESOLUTION, RESOLUTION);
		glRotated			(90, 1, 0, 0);
	glTranslated		(0, -2 * (RADIUS3 - RING_WIDTH), 0);
		glRotated			(90, 1, 0, 0);
		gluCylinder			(QObj, RING_HEIGHT / 2.0, RING_HEIGHT / 2.0, RADIUS2 - RADIUS3, RESOLUTION, RESOLUTION);
		glRotated			(90, -1, 0, 0);
	glTranslated		(0, RADIUS3 - RING_WIDTH, 0);

	// ������ ����������� ��������
	glRotated			(RING3_ANGLE_OFFSET * Angle (0), 0, 1, 0);

	// ���������� ������
	Ring				(QObj, RADIUS3, RING_WIDTH, RING_HEIGHT, RESOLUTION);

	// ������� ���������� �����
	glRotated			(45, 0, 0, -1);

	////////////////////////////////
	// ����� ����������� ��������
	glRotated			(RING3_ANGLE_OFFSET * Angle (0), 0, -1, 0);

	////////////////////////////////
	// ����� �������� ��������
	glRotated			(RING2_ANGLE_OFFSET * Angle (0), 0, -1, 0);

	////////////////////////////////
	// ����� �������� ��������
	glRotated			(RING1_ANGLE_OFFSET * Angle (0), 0, -1, 0);

	// ����������
	glFlush				();
	gluDeleteQuadric	(QObj);
	glPopMatrix			();
	auxSwapBuffers		();
	}

// ������� ��������� ������� �����������
void ReLight (void)
	{
	// ������� ��������� (����������: �����-������ (x), �����-���� (y), �����-����� (z))
	// ������� �����������
	GLfloat	Pos[4] = {5.0, 5.0, 5.0f};

	// �� �����������
	GLfloat	Dir[3] = {-1.0, -1.0, -1.0f};

	// ������� ����� � �����
	GLfloat	Mat_Amb[4] = {1.0f, 1.0f, 1.0f, 1.0f};				// ����
	
	// ���� �����������
	GLfloat CArc = 30.0;

	glLightfv		(GL_LIGHT0, GL_POSITION, Pos);				// �������
	glLightfv		(GL_LIGHT0, GL_SPOT_DIRECTION, Dir);		// �����������
	glLightfv		(GL_LIGHT0, GL_AMBIENT, Mat_Amb);			// ���� ����������
	glLightfv		(GL_LIGHT0, GL_SPECULAR, Mat_Amb);			// �����
	glLightf		(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.5);	// ����������
	}

// ������� ����������� ������
void Ring (GLUquadricObj *QO, double Radius, double Width, double Height, int Resolution)
	{
	// ������� ������
	glTranslated		(0.0, 0.0, Height / 2);			// ������� ����� �����������
	gluDisk				(QO, Radius - Width, Radius, Resolution, Resolution);

	// ������ ������
	glTranslated		(0.0, 0.0, -Height);
	glRotated			(180, 1, 0, 0);
	gluDisk				(QO, Radius - Width, Radius, Resolution, Resolution);
	glRotated			(180, -1, 0, 0);
	glTranslated		(0.0, 0.0, Height / 2);

	// ��������
	glTranslated		(0.0, 0.0, -Height / 2);
	gluCylinder			(QO, Radius, Radius, Height, Resolution, Resolution);
	gluCylinder			(QO, Radius - Width, Radius - Width, Height, Resolution, Resolution);
	glTranslated		(0.0, 0.0, Height / 2);
	}
