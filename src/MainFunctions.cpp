// Общая библиотека
#include "OpenGLSample.h"

// Указатель на 3D-объект
GLUquadricObj *QObj;

// Пусковая консольная функция
void main (void)
	{
	// Матрицы освещения (координаты: влево-вправо (x), вверх-вниз (y), вперёд-назад (z))
	GLfloat	Mat_AmDf[] = {0.0f, 0.0f, 0.0f, 1.0f},		// Матрица света и диффузии
			Mat_Spec[] = {1.0f, 1.0f, 1.0f, 1.0f},		// Матрица зеркальности
			Mat_Emis[] = {0.0f, 0.0f, 0.0f, 1.0f},		// Матрица внутреннего света
			Shin = 75.0;								// Блеск ([0; 128]; чем меньше, тем ярче
	GLfloat	Pos[4] = {5.0, 5.0, 5.0f},					// Позиции осветителей
			Dir[3] = {-1.0, -1.0, -1.0f},				// Их направление
			Amb_Color[4] = {1.0f, 1.0f, 1.0f, 1.0f},	// Цвет освещения
			Attn = 1.5f;								// Ослабление
	
	// Выдача справки по клавиатуре
	printf ("\n Keyboard usage:\n");
	printf ("  \x18\x19\x1A\x1B  - model roration;\n");
	printf ("  1 / 2 - model zoom in / out;\n");
	printf ("  4 / 5 - acceleration / deceleration of rings rotation\n");
	printf ("          (negative speed = rotation reverse);\n");
	printf ("  Mouse - model rotation");
	printf ("\n\n Press any key to continue...");
	_getch ();

	// Инициализация окна
	auxInitPosition			(WX0, WY0, WXM, WYM);				// Стартовая позиция окна
	auxInitDisplayMode		(AUX_RGB | AUX_DEPTH | AUX_DOUBLE);	// Формат окна
	auxInitWindow			(WTITLE);							// Заголовок окна

	// Функции отображения
	auxIdleFunc				(Display);							// Отображение
	auxReshapeFunc			(Resize);							// Изменение размеров окна

	// Главный осветитель и включение дополнительных прожекторов
	glEnable				(GL_LIGHTING);						// Включение режима освещения
	glEnable				(GL_LIGHT0);						// Номер осветителя
	glEnable				(GL_DEPTH_TEST);					// Включение света

	// Параметры материала
	glMaterialfv			(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, Mat_AmDf);
	glMaterialfv			(GL_FRONT_AND_BACK, GL_SPECULAR, Mat_Spec);
	glMaterialfv			(GL_FRONT_AND_BACK, GL_EMISSION, Mat_Emis);	// Внутренний свет
	glMaterialf				(GL_FRONT_AND_BACK, GL_SHININESS, Shin);
	glEnable				(GL_COLOR_MATERIAL);			// Включение цвета материала

	// Параметры осветителя
	glLightfv				(GL_LIGHT0, GL_POSITION, Pos);				// Позиция
	glLightfv				(GL_LIGHT0, GL_SPOT_DIRECTION, Dir);		// Направление
	glLightfv				(GL_LIGHT0, GL_AMBIENT, Amb_Color);			// Цвет осветителя
	glLightfv				(GL_LIGHT0, GL_SPECULAR, Amb_Color);		// Блеск
	glLightf				(GL_LIGHT0, GL_LINEAR_ATTENUATION, Attn);	// Ослабление

	// Функции обработки клавиш (описаны в BaseFunctions)
	auxKeyFunc			(AUX_LEFT, Key_LEFT);
	auxKeyFunc			(AUX_RIGHT, Key_RIGHT);
	auxKeyFunc			(AUX_UP, Key_UP);
	auxKeyFunc			(AUX_DOWN, Key_DOWN);
	auxKeyFunc			('1', Key_ZoomIn);
	auxKeyFunc			('2', Key_ZoomOut);
	auxKeyFunc			('4', Key_SpeedUp);
	auxKeyFunc			('5', Key_SpeedDown);

	// Функция обработки мыши
	auxMouseFunc		(AUX_LEFTBUTTON, AUX_MOUSELOC, MouseMove);

	// Функция рисования (цикл)
	auxMainLoop			(Display);
	}

// Главная функция отображения
void CALLBACK Display (void)
	{
	// Вращение
	Angle (Speed (0));

	// Очистка экрана
	glClear				(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor		(BACKGROUND_COLOR, 0.0f);		// Цвет фона
	glPushMatrix		();

	// Направления вращения и исходная позиция
	glRotated			(Alpha (0), 0, 1, 0);
	glRotated			(Beta (0), 0, 0, 1);
	glRotated			(45, 0, -1, 0);

	// Подключение и наложение цвета
	QObj = gluNewQuadric	(); 
	gluQuadricDrawStyle		(QObj, GLU_FILL); 

	////////////////////////////////
	// С-образные опоры
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

	// Держатели внешнего кольца
	glRotated			(45, 0, 0, 1);
	glTranslated		(0.0, (RADIUS1 + 1.5), 0.0);
	auxSolidBox			(1.0, 1.0, 2 * RING_HEIGHT);
	glTranslated		(0.0, -2 * (RADIUS1 + 1.5), 0.0);
	auxSolidBox			(1.0, 1.0, 2 * RING_HEIGHT);
	glTranslated		(0.0, (RADIUS1 + 1.5), 0.0);
	glRotated			(45, 0, 0, -1);

	// Площадка
	glTranslated		(0.0, -(RADIUS1 + 2.0), 0.0);
	auxSolidBox			(2.0, 2.0, 2 * RING_HEIGHT);

	glColor3d			(BASE_COLOR);
	glTranslated		(0.0, -1.0, 0.0);
	auxSolidBox			(4.0, RING_HEIGHT, 7.0);
	glTranslated		(0.0, (RADIUS1 + 3.0), 0.0);

	////////////////////////////////
	// Внешнее кольцо
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
	
	// Начало внешнего вращения
	glRotated			(RING1_ANGLE_OFFSET * Angle (0), 0, 1, 0);

	// Внешнее кольцо
	Ring				(QObj, RADIUS1, RING_WIDTH, RING_HEIGHT, RESOLUTION);

	// Возврат внешней опоры
	glRotated			(45, 0, 0, -1);

	////////////////////////////////
	// Средняя опора
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

	// Начало внутреннего вращения
	glRotated			(RING2_ANGLE_OFFSET * Angle (0), 0, 1, 0);
	// Какой-нибудь неточный коэффициент (для эффекта случайности)

	// Кольцо
	Ring				(QObj, RADIUS2, RING_WIDTH, RING_HEIGHT, RESOLUTION);

	// Возврат опоры
	glRotated			(-45, 0, 0, -1);

	////////////////////////////////
	// Внутренняя опора
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

	// Начало внутреннего вращения
	glRotated			(RING3_ANGLE_OFFSET * Angle (0), 0, 1, 0);

	// Внутреннее кольцо
	Ring				(QObj, RADIUS3, RING_WIDTH, RING_HEIGHT, RESOLUTION);

	// Возврат внутренней опоры
	glRotated			(45, 0, 0, -1);

	////////////////////////////////
	// Конец внутреннего вращения
	glRotated			(RING3_ANGLE_OFFSET * Angle (0), 0, -1, 0);

	////////////////////////////////
	// Конец среднего вращения
	glRotated			(RING2_ANGLE_OFFSET * Angle (0), 0, -1, 0);

	////////////////////////////////
	// Конец внешнего вращения
	glRotated			(RING1_ANGLE_OFFSET * Angle (0), 0, -1, 0);

	// Завершение
	glFlush				();
	gluDeleteQuadric	(QObj);
	glPopMatrix			();
	auxSwapBuffers		();
	}

// Функция изображения кольца
void Ring (GLUquadricObj *QO, double Radius, double Width, double Height, int Resolution)
	{
	// Верхняя крышка
	glTranslated		(0.0, 0.0, Height / 2);			// Задание точки отображения
	gluDisk				(QO, Radius - Width, Radius, Resolution, Resolution);

	// Нижняя крышка
	glTranslated		(0.0, 0.0, -Height);
	glRotated			(180, 1, 0, 0);
	gluDisk				(QO, Radius - Width, Radius, Resolution, Resolution);
	glRotated			(180, -1, 0, 0);
	glTranslated		(0.0, 0.0, Height / 2);

	// Цилиндры
	glTranslated		(0.0, 0.0, -Height / 2);
	gluCylinder			(QO, Radius, Radius, Height, Resolution, Resolution);
	gluCylinder			(QO, Radius - Width, Radius - Width, Height, Resolution, Resolution);
	glTranslated		(0.0, 0.0, Height / 2);
	}
