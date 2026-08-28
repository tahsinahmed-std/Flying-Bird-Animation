#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

// Bird positions
float birdX1 = -0.8f, birdX2 = -0.8f, birdX3 = -0.8f;
float birdY1 = -0.2f, birdY2 = -0.2f, birdY3 = -0.2f;

// Bird status (1 = flying)
int bird1Flying = 1;
int bird2Flying = 0;
int bird3Flying = 0;

int wingState = 0;
float birdSpeed = 0.012f;      // Birds fly speed
float cloudShift = 0.0f;       // Cloud movement only
float riverShift = 0.0f;       // River water flow

int releaseTimer = 0;

// Draw circle
void drawCircle(float cx, float cy, float r) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.1416f / 180;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();
}

// Draw beautiful flower
void drawFlower(float x, float y) {
    // Stem
    glColor3f(0.0f, 0.7f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
        glVertex2f(x, y);
        glVertex2f(x, y + 0.12f);
    glEnd();

    // Leaves on stem
    glColor3f(0.0f, 0.6f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y + 0.05f);
        glVertex2f(x - 0.04f, y + 0.02f);
        glVertex2f(x, y + 0.03f);

        glVertex2f(x, y + 0.08f);
        glVertex2f(x + 0.04f, y + 0.05f);
        glVertex2f(x, y + 0.06f);
    glEnd();

    // 5 Petals
    glColor3f(1.0f, 0.4f, 0.7f);
    for(int i = 0; i < 5; i++) {
        float angle = i * 72 * 3.1416f / 180;
        float px = x + 0.04f * cos(angle);
        float py = y + 0.12f + 0.04f * sin(angle);
        drawCircle(px, py, 0.025f);
    }

    // Flower center
    glColor3f(1.0f, 0.8f, 0.0f);
    drawCircle(x, y + 0.12f, 0.018f);
}

// Draw mountain (sits directly on ground, no black line)
void drawMountain(float x, float peakY, float width) {
    // Mountain body - green color
    glColor3f(0.25f, 0.5f, 0.25f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x - width/2, -0.35f);
        glVertex2f(x, peakY);
        glVertex2f(x + width/2, -0.35f);
    glEnd();

    // Lighter side for depth
    glColor3f(0.35f, 0.6f, 0.35f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, peakY);
        glVertex2f(x + width/2, -0.35f);
        glVertex2f(x, -0.35f);
    glEnd();
}

// Draw bird
void drawBird(float x, float y) {
    // Body
    glColor3f(1.0f, 0.8f, 0.2f);
    drawCircle(x, y, 0.07f);

    // Head
    drawCircle(x + 0.07f, y + 0.03f, 0.05f);

    // Eye
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x + 0.09f, y + 0.05f, 0.008f);

    // Beak
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x + 0.12f, y + 0.04f);
        glVertex2f(x + 0.15f, y + 0.05f);
        glVertex2f(x + 0.12f, y + 0.07f);
    glEnd();

    // Wings (flapping)
    glColor3f(0.9f, 0.6f, 0.1f);

    if(wingState == 0) {  // Wing UP
        glBegin(GL_TRIANGLES);
            glVertex2f(x - 0.03f, y + 0.02f);
            glVertex2f(x - 0.14f, y + 0.12f);
            glVertex2f(x - 0.10f, y + 0.02f);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(x - 0.01f, y - 0.03f);
            glVertex2f(x - 0.12f, y + 0.02f);
            glVertex2f(x - 0.08f, y - 0.03f);
        glEnd();
    } else {  // Wing DOWN
        glBegin(GL_TRIANGLES);
            glVertex2f(x - 0.03f, y + 0.02f);
            glVertex2f(x - 0.14f, y - 0.03f);
            glVertex2f(x - 0.10f, y + 0.02f);
        glEnd();
        glBegin(GL_TRIANGLES);
            glVertex2f(x - 0.01f, y - 0.03f);
            glVertex2f(x - 0.12f, y - 0.10f);
            glVertex2f(x - 0.08f, y - 0.03f);
        glEnd();
    }
}

// Draw river at bottom
void drawRiver() {
    // River water
    glColor3f(0.2f, 0.5f, 0.8f);  // Blue water
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.65f);
        glVertex2f(-1.0f, -0.65f);
    glEnd();

    // River banks (edges)
    glColor3f(0.5f, 0.35f, 0.2f);  // Brown bank
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.65f);
        glVertex2f(1.0f, -0.65f);
        glVertex2f(1.0f, -0.62f);
        glVertex2f(-1.0f, -0.62f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.98f);
        glVertex2f(-1.0f, -0.98f);
    glEnd();

    // Water flow lines (moving)
    glColor3f(0.6f, 0.8f, 1.0f);  // Light blue/white
    for(float i = -1.0f; i <= 1.0f; i += 0.15f) {
        float lineX = i + riverShift;
        if(lineX > 1.0f) lineX = -1.0f;
        if(lineX < -1.0f) lineX = 1.0f;
        glBegin(GL_LINES);
            glVertex2f(lineX, -0.9f);
            glVertex2f(lineX + 0.08f, -0.85f);
            glVertex2f(lineX - 0.03f, -0.8f);
            glVertex2f(lineX + 0.05f, -0.75f);
        glEnd();
    }
}

// Draw grass ground (above river)
void drawGround() {
    glColor3f(0.2f, 0.55f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.62f);
        glVertex2f(1.0f, -0.62f);
        glVertex2f(1.0f, -0.35f);
        glVertex2f(-1.0f, -0.35f);
    glEnd();
}

// Draw cloud (moves)
void drawCloud(float baseX, float y) {
    float x = baseX + cloudShift;
    if(x > 1.3f) x = -1.3f;
    if(x < -1.3f) x = 1.3f;

    glColor3f(1.0f, 0.95f, 0.85f);
    drawCircle(x, y, 0.09f);
    drawCircle(x + 0.08f, y - 0.02f, 0.08f);
    drawCircle(x - 0.08f, y - 0.02f, 0.08f);
    drawCircle(x + 0.03f, y - 0.07f, 0.07f);
    drawCircle(x - 0.03f, y - 0.07f, 0.07f);
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky gradient (top to bottom) - covers everything behind mountains
    glBegin(GL_QUADS);
        glColor3f(0.3f, 0.6f, 0.95f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3f(0.7f, 0.85f, 1.0f);
        glVertex2f(1.0f, -0.35f);
        glVertex2f(-1.0f, -0.35f);
    glEnd();

    // Sun
    glColor3f(1.0f, 0.85f, 0.3f);
    drawCircle(0.75f, 0.75f, 0.1f);

    // Sun rays
    glColor3f(1.0f, 0.9f, 0.5f);
    glLineWidth(1.5f);
    for(int i = 0; i < 12; i++) {
        float angle = i * 30 * 3.1416f / 180;
        glBegin(GL_LINES);
            glVertex2f(0.75f + 0.13f * cos(angle), 0.75f + 0.13f * sin(angle));
            glVertex2f(0.75f + 0.2f * cos(angle), 0.75f + 0.2f * sin(angle));
        glEnd();
    }

    // Clouds
    drawCloud(-0.6f, 0.68f);
    drawCloud(0.3f, 0.72f);
    drawCloud(0.7f, 0.6f);
    drawCloud(-0.2f, 0.55f);

    // Mountains (sit on ground, sky is behind them - no black line)
    drawMountain(-0.85f, 0.28f, 0.5f);
    drawMountain(-0.35f, 0.32f, 0.55f);
    drawMountain(0.15f, 0.30f, 0.52f);
    drawMountain(0.65f, 0.25f, 0.48f);
    drawMountain(-0.05f, 0.22f, 0.42f);

    // Ground (grass between mountains and river)
    drawGround();

    // Flowers on ground
    drawFlower(-0.85f, -0.48f);
    drawFlower(-0.65f, -0.52f);
    drawFlower(-0.45f, -0.46f);
    drawFlower(-0.25f, -0.50f);
    drawFlower(-0.05f, -0.47f);
    drawFlower(0.15f, -0.51f);
    drawFlower(0.35f, -0.45f);
    drawFlower(0.55f, -0.49f);
    drawFlower(0.75f, -0.47f);
    drawFlower(0.90f, -0.50f);
    drawFlower(-0.75f, -0.55f);
    drawFlower(0.05f, -0.54f);
    drawFlower(0.65f, -0.53f);

    // River at bottom
    drawRiver();

    // Birds
    if(bird1Flying) drawBird(birdX1, birdY1);
    if(bird2Flying) drawBird(birdX2, birdY2);
    if(bird3Flying) drawBird(birdX3, birdY3);

    glFlush();
}

// Wing flap animation
void flapWings(int v) {
    wingState = !wingState;
    glutPostRedisplay();
    glutTimerFunc(120, flapWings, 0);
}

// Scene movement (birds, clouds, and river flow)
void moveScene(int v) {
    // Birds fly RIGHT
    if(bird1Flying) {
        birdX1 += birdSpeed;
        birdY1 = -0.15f + 0.12f * sin(birdX1 * 6.0f);
        if(birdX1 > 1.5f) birdX1 = -1.3f;
    }

    if(bird2Flying) {
        birdX2 += birdSpeed + 0.002f;
        birdY2 = -0.12f + 0.1f * sin(birdX2 * 5.5f + 1.5f);
        if(birdX2 > 1.5f) birdX2 = -1.3f;
    }

    if(bird3Flying) {
        birdX3 += birdSpeed + 0.004f;
        birdY3 = -0.18f + 0.14f * sin(birdX3 * 6.5f + 3.0f);
        if(birdX3 > 1.5f) birdX3 = -1.3f;
    }

    // Release birds one by one
    releaseTimer++;
    if(releaseTimer == 70 && bird2Flying == 0) {
        bird2Flying = 1;
        birdX2 = -0.82f;
        birdY2 = -0.18f;
    }
    if(releaseTimer == 140 && bird3Flying == 0) {
        bird3Flying = 1;
        birdX3 = -0.84f;
        birdY3 = -0.15f;
    }

    // Clouds move RIGHT
    cloudShift += 0.0018f;
    if(cloudShift > 2.0f) cloudShift = -2.0f;

    // River water flows (waves move)
    riverShift += 0.008f;
    if(riverShift > 0.3f) riverShift = -0.3f;

    glutPostRedisplay();
    glutTimerFunc(16, moveScene, 0);
}

// Keyboard controls
void keyboard(unsigned char key, int x, int y) {
    if(key == 'f') birdSpeed += 0.002f;
    if(key == 's') birdSpeed -= 0.002f;
    if(birdSpeed < 0.005f) birdSpeed = 0.005f;
    if(key == 'r') {
        birdX1 = -0.8f; birdX2 = -0.8f; birdX3 = -0.8f;
        bird1Flying = 1; bird2Flying = 0; bird3Flying = 0;
        releaseTimer = 0;
        birdSpeed = 0.012f;
    }
    if(key == 27) exit(0);
}

// Initialize OpenGL
void init() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(900, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Flying Birds with River | OpenGL Project");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, moveScene, 0);
    glutTimerFunc(0, flapWings, 0);

    glutMainLoop();
    return 0;
}
