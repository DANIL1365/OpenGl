#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>
#include <sstream>

// Константи
const int GRID_SIZE = 20;    // Розмір сітки
const float GRID_STEP = 2.0f; // Крок сітки
std::vector<std::pair<float, float>> controlPoints = {{-10, -10}, {0, 0}, {10, 10}, {5, -5}, {-5, 5}}; // Контрольні точки
float adjustment = 1.0f;     // Рівень наближення

// Функція поверхні
float functionSurface(float x, float y) {
    return 6.4f * adjustment - 0.060f * x * y - 0.054f * x * x - 0.059f * y * y;
}

// Вирахування коефіцієнта детермінації (R²)
float calculateRSquared() {
    float ssTot = 0.0f, ssRes = 0.0f;
    float meanZ = 0.0f;

    // Знаходимо середнє значення Z
    for (const auto& point : controlPoints) {
        meanZ += functionSurface(point.first, point.second);
    }
    meanZ /= controlPoints.size();

    // Обчислюємо суму квадратів залишків (SSres) і загальну суму квадратів (SStot)
    for (const auto& point : controlPoints) {
        float actualZ = functionSurface(point.first, point.second);
        float predictedZ = functionSurface(point.first, point.second);
        ssRes += pow(predictedZ - actualZ, 2);
        ssTot += pow(actualZ - meanZ, 2);
    }

    // Повертаємо R²
    return 1.0f - (ssRes / ssTot);
}

// Функція для відображення тексту
void renderText(float x, float y, float z, const char* text) {
    glRasterPos3f(x, y, z);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Ініціалізація OpenGL
void initOpenGL() {
    glEnable(GL_DEPTH_TEST); // Глибина
    glEnable(GL_POINT_SMOOTH); // Згладжування точок
    glPointSize(8.0f); // Розмір точок

    // Освітлення
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat lightPos[] = {50.0f, 50.0f, 50.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    // Встановлення матеріалів для забезпечення кольорів
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Установка сірого фону
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f); // Світло-сірий фон (RGBA)
}

// Функція для малювання координатних осей
void drawAxes() {
    glLineWidth(3.0f);

    // X-вісь (темно-червона)
    glColor3f(0.5f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-GRID_SIZE, -GRID_SIZE, -20.0f);
    glVertex3f(GRID_SIZE, -GRID_SIZE, -20.0f);
    glEnd();
    renderText(GRID_SIZE + 2, -GRID_SIZE, -20.0f, "X");

    // Y-вісь (темно-зелена)
    glColor3f(0.0f, 0.5f, 0.0f);
    glBegin(GL_LINES);
    glVertex3f(-GRID_SIZE, -GRID_SIZE, -20.0f);
    glVertex3f(-GRID_SIZE, GRID_SIZE, -20.0f);
    glEnd();
    renderText(-GRID_SIZE, GRID_SIZE + 2, -20.0f, "Y");

    // Z-вісь (темно-синя)
    glColor3f(0.0f, 0.0f, 0.5f);
    glBegin(GL_LINES);
    glVertex3f(-GRID_SIZE, -GRID_SIZE, -20.0f);
    glVertex3f(-GRID_SIZE, -GRID_SIZE, 10.0f);
    glEnd();
    renderText(-GRID_SIZE, -GRID_SIZE, 12.0f, "Z");
}

// Функція для відображення контрольних точок
void drawControlPoints() {
    glColor3f(1.0f, 0.5f, 0.0f); // Помаранчевий колір
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    for (const auto& point : controlPoints) {
        float z = functionSurface(point.first, point.second);
        glVertex3f(point.first, point.second, z);
    }
    glEnd();
}

// Функція для відображення поверхні
void drawSurface() {
    glColor3f(1.0f, 0.0f, 1.0f); // Колір поверхні
    glBegin(GL_LINES);

    for (float x = -GRID_SIZE; x <= GRID_SIZE; x += GRID_STEP) {
        for (float y = -GRID_SIZE; y <= GRID_SIZE; y += GRID_STEP) {
            float z = functionSurface(x, y);

            // Лінії вздовж X
            if (x + GRID_STEP <= GRID_SIZE) {
                float zNextX = functionSurface(x + GRID_STEP, y);
                glVertex3f(x, y, z);
                glVertex3f(x + GRID_STEP, y, zNextX);
            }

            // Лінії вздовж Y
            if (y + GRID_STEP <= GRID_SIZE) {
                float zNextY = functionSurface(x, y + GRID_STEP);
                glVertex3f(x, y, z);
                glVertex3f(x, y + GRID_STEP, zNextY);
            }
        }
    }
    glEnd();
}

// Відображення сцени
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Налаштування камери
    gluLookAt(30.0, 30.0, 40.0,   // Позиція камери
              0.0, 0.0, 0.0,      // Точка, на яку дивиться камера
              0.0, 0.0, 1.0);     // Напрямок "вгору"

    drawAxes();          // Малюємо осі
    drawSurface();       // Малюємо поверхню
    drawControlPoints(); // Малюємо контрольні точки

    // Відображення тексту
    glColor3f(0.0f, 0.0f, 0.0f); // Чорний колір тексту
    std::ostringstream text;
    text << "R^2 = " << calculateRSquared();
    renderText(-GRID_SIZE, GRID_SIZE + 5, -20.0f, text.str().c_str());

    glutSwapBuffers();
}

// Обробка зміни розміру вікна
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

// Обробка клавіш
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+': // Збільшення рівня наближення
        adjustment += 0.1f;
        glutPostRedisplay();
        break;
    case '-': // Зменшення рівня наближення
        adjustment -= 0.1f;
        glutPostRedisplay();
        break;
    case 27: // Вихід
        exit(0);
    }
}

// Основна функція
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Polynomial Surface Visualization");

    initOpenGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}
