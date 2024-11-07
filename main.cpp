#include <GL/glut.h>
#include <vector>
#include <cmath>
#include <string>

// Дані точок для інтерполяції (6 точок)
std::vector<float> x_nodes = {-1.0f, -0.6f, -0.2f, 0.2f, 0.6f, 1.0f};
std::vector<float> y_nodes = {0.2f, -0.5f, 0.8f, -0.4f, 0.5f, -0.1f};

// Функція для обчислення базисної функції Лагранжа L_i(x)
float lagrangeBasis(int i, float x) {
    float result = 1.0f;
    for (int j = 0; j < x_nodes.size(); ++j) {
        if (j != i) {
            result *= (x - x_nodes[j]) / (x_nodes[i] - x_nodes[j]);
        }
    }
    return result;
}

// Функція для обчислення значення полінома Лагранжа в точці x
float lagrangePolynomial(float x) {
    float result = 0.0f;
    for (int i = 0; i < x_nodes.size(); ++i) {
        result += y_nodes[i] * lagrangeBasis(i, x);
    }
    return result;
}

// Функція для відображення осей координат
void drawAxes() {
    glColor3f(1.0f, 1.0f, 1.0f); // Білий колір для осей
    glBegin(GL_LINES);
    // Вісь X
    glVertex2f(-1.5f, 0.0f);
    glVertex2f(1.5f, 0.0f);
    // Вісь Y
    glVertex2f(0.0f, -1.5f);
    glVertex2f(0.0f, 1.5f);
    glEnd();

    // Підписи на осях
    glRasterPos2f(1.4f, -0.1f); // Підпис для осі X
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');
    glRasterPos2f(-0.1f, 1.4f); // Підпис для осі Y
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');
}

// Функція для відображення графіка
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes(); // Малюємо осі

    // Ламана лінія (синя) через задані точки
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < x_nodes.size(); ++i) {
        glVertex2f(x_nodes[i], y_nodes[i]);
    }
    glEnd();

    // Згладжений поліном Лагранжа (червоний)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_STRIP);
    for (float x = -1.0f; x <= 1.0f; x += 0.01f) {
        float y = lagrangePolynomial(x);
        glVertex2f(x, y);
    }
    glEnd();

    // Відображення точок даних
    glPointSize(8.0f);
    glColor3f(0.0f, 0.8f, 1.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < x_nodes.size(); ++i) {
        glVertex2f(x_nodes[i], y_nodes[i]);
    }
    glEnd();

    // Відображення підпису "Поліном степеня 5" внизу
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-1.2f, -1.4f);
    std::string text = "Поліном степеня 5";
    for (char c : text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glFlush();
}

// Ініціалізація OpenGL
void initOpenGL() {
    glClearColor(0.2f, 0.2f, 0.5f, 1.0f); // Темно-синій фон
    glColor3f(1.0f, 1.0f, 1.0f);           // Білий колір для тексту
    glPointSize(8.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.5, 1.5, -1.5, 1.5, -1.0, 1.0);
}

// Основна функція
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Polynomial Interpolation - Degree 5");
    initOpenGL();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
