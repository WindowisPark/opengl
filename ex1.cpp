#include <GL/glut.h>

float angleZ = 0.0;  // ȸ�� ����
float transX = 0.0, transY = 0.0;  // �̵� �Ÿ�
float zoom = 1.0;  // Ȯ��/���
int lastX, lastY;  // ������ ���콺 ��ġ
int activeButton = -1;  // ���� Ȱ��ȭ�� ���콺 ��ư
int windowWidth = 800, windowHeight = 600;
bool rotateRight = false;  // ȸ�� ���� ���� �÷���

void initGL() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(1.0 * zoom, 1.0 * zoom, 1.0 * zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glTranslatef(transX, transY, 0.0);
    glRotatef(angleZ, 0.0, 0.0, 1.0);

    glColor3f(1.0, 0.0, 0.0); 
    glPushMatrix();
    glTranslatef(-0.75, 0.0, 0.0);
    glutSolidCube(0.5);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0); 
    glPushMatrix();
    glTranslatef(1.5, 0.0, 0.0);
    glutSolidCube(0.3);
    glPopMatrix();

    glColor3f(1.0, 1.0, 0.0); 
    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0);
    glutSolidSphere(0.3, 20, 16);
    glPopMatrix();

    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0);
    glutSolidSphere(0.2, 20, 16);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    windowWidth = w;
    windowHeight = h;
    glViewport(0, 0, w, h);
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y) {
    lastX = x;
    lastY = y;
    if (state == GLUT_DOWN) {
        activeButton = button;
        if (button == GLUT_LEFT_BUTTON) {
            rotateRight = (x > windowWidth / 2);  // ���콺 Ŭ�� ��ġ�� ���� ȸ�� ����
        }
    }
    else if (state == GLUT_UP) {
        activeButton = -1;  // ���콺 ��ư�� �������� �� ���¸� ����
    }
    glutPostRedisplay();
}

void mouseMove(int x, int y) {
    if (activeButton == GLUT_LEFT_BUTTON) {
        if (rotateRight) {
            angleZ -= 0.5; // ����ؼ� �ݽð� �������� ȸ��
        }
        else {
            angleZ += 0.5; // ����ؼ� �ð� �������� ȸ��
        }
    }
    else if (activeButton == GLUT_MIDDLE_BUTTON) {
        transX += (x - lastX) * 0.01f;
        transY -= (y - lastY) * 0.01f;
    }
    else if (activeButton == GLUT_RIGHT_BUTTON) {
        if ((x - lastX > 0 && y - lastY > 0)) {
            zoom *= 1.05;  // Ȯ��
        }
        else if ((x - lastX < 0 || y - lastY < 0)) {
            zoom /= 1.05;  // ���
        }
    }
    lastX = x;
    lastY = y;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("22011946_����3");
    initGL();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);
    glutMainLoop();
    return 0;
}
