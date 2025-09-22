#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#define CTRL_COUNT 100
#define MAX_RAINDROPS 600
#define MAX_SPLASHES 200
#define PI 3.1416
#ifndef MOUSE_HANDLER_H
#define MOUSE_HANDLER_H
#endif

bool Fuad = true;
bool Azim = false;
bool Mahfuzur = false;
bool Ishrak = false;

//for day night effect
bool isNight = false; // Start with night view (set to 0 for day view)

//for rain
bool isRaining = false;
float rainTargetYMin = 0.0f;
float rainTargetYMax = 50.0f;
//truck
int triangleAmount = 20;
GLfloat twicePi = 2.0f * PI;

//for Lightning effect
bool lightningActive = false;
bool lightningActive2 = false;
float boltX = 50.0f, boltY = 90.0f;

//for cloud
float cloudX1 = 0.0f;
float cloudX2 = 30.0f;
float cloudX3 = 60.0f;
float cloudSpeed = 0.04f;
float minCloudSpeed = 0.05f;
float maxCloudSpeed = 0.5f;
float normalCloudSpeed = 0.1f;

//for plane
float planeX = -20.0f;
float planeSpeed = 0.2f;

float planeX2 = 120.0f;
float planeSpeed2 = 0.4f;

//for my boat
float boatX = 25.0f;
float boatSpeed = 0.3f;

//Bus & Car
float carX1 = -30.0f;    // First car start X
float carSpeed1 = 0.5f; // First car speed

float carX2 = 120.0f;    // Second car start X (from right side)
float carSpeed2 = -0.4f; // Second car speed (move left)

float carX3 = -40.0f;
float carSpeed3 = 0.6f;

float carX4 = 150.0f;
float carSpeed4 = -0.5f;

bool nightLight = false;

// Draw circle for tree leafs
void drawCircle(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = r * cosf(angle);
        float y = r * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

// Draw triangle for tree leafs
void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3) {
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

// Draw rectangle given two opposite corners
void drawRectangle(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

// Object ID: OBJ1
void drawRiver(float R, float G, float B) {

    glColor3f(R, G, B);  // RGB(65, 105, 225) - Royal Blue
    glBegin(GL_QUADS);             //River
    glVertex2f(0.0, 0.0);
    glVertex2f(100.0, 0.0);
    glVertex2f(100.0, 20.0);
    glVertex2f(0.0, 20.0);
    glEnd();

}

// Object ID: OBJ2
void drawSky(float R, float G, float B) {

    glColor3f(R, G, B);  // RGB(135, 206, 235) - Sky Blue
    glBegin(GL_QUADS);             //River
    glVertex2f(0.0, 50.0);
    glVertex2f(100.0, 50.0);
    glVertex2f(100.0, 90.0);
    glVertex2f(0.0, 90.0);
    glEnd();
}

// Object ID: OBJ4
void drawBorder() {

    int index = 0;
    for (float x = 0.0f; x < 100.0f; x += 3.0f, index++) {

        if (index % 2 == 0) {
            glColor3f(1.0f, 1.0f, 1.0f); // white
        }
        else {
            glColor3f(0.0f, 0.0f, 0.0f); // black
        }

        glBegin(GL_QUADS);
        glVertex2f(x, 20.0f);
        glVertex2f(x + 3.0f, 20.0f);
        glVertex2f(x + 3.0f, 22.0f);
        glVertex2f(x, 22.0f);
        glEnd();
    }


    glColor3f(0.45f, 0.36f, 0.22f);  // mud/soil color for rail border
    glBegin(GL_QUADS);              //rail border base (44-50)
    glVertex2f(0.0, 44.0);
    glVertex2f(100.0, 44.0);
    glVertex2f(100.0, 50.0);
    glVertex2f(0.0, 50.0);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);     // White border for road divider
    glBegin(GL_QUADS);              //road divider
    glVertex2f(0.0, 32.0);
    glVertex2f(100.0, 32.0);
    glVertex2f(100.0, 34.0);
    glVertex2f(0.0, 34.0);
    glEnd();

    for (float x = 5.0f; x < 100.0f; x += 10.0f) {

        // Road signalLine base

        glColor3f(1.0f, 1.0f, 1.0f); // white color
        glBegin(GL_QUADS);
        glVertex2f(x, 38.0f);
        glVertex2f(x + 5.0f, 38.0f);
        glVertex2f(x + 5.0f, 40.0f);
        glVertex2f(x, 40.0f);
        glEnd();

        // optional outline (thin black line)
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, 38.0f);
        glVertex2f(x + 5.0f, 38.0f);
        glVertex2f(x + 5.0f, 40.0f);
        glVertex2f(x, 40.0f);
        glEnd();
    }

    for (float x = 0.0f; x < 100.0f; x += 10.0f) {

        // Road signalLine base

        glColor3f(1.0f, 1.0f, 1.0f); // white color
        glBegin(GL_QUADS);
        glVertex2f(x, 26.0f);
        glVertex2f(x + 5.0f, 26.0f);
        glVertex2f(x + 5.0f, 28.0f);
        glVertex2f(x, 28.0f);
        glEnd();

        // optional outline (thin black line)
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, 26.0f);
        glVertex2f(x + 5.0f, 26.0f);
        glVertex2f(x + 5.0f, 28.0f);
        glVertex2f(x, 28.0f);
        glEnd();
    }

}

// Object ID: OBJ4
void drawRailPath() {

    for (float x = 0.0f; x < 100.0f; x += 2.0f) {

        // optional outline (thin black line)
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.3f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, 46.0f);
        glVertex2f(x + 2.0f, 46.0f);
        glVertex2f(x + 2.0f, 48.0f);
        glVertex2f(x, 48.0f);
        glEnd();

    }
}

// Object ID: OBJ5
void drawTree(float trunkX, float trunkY, float X1, float Y1) {

    // Draw trunk
    glColor3f(0.55f, 0.27f, 0.07f); // Brown
    glBegin(GL_POLYGON);
    glVertex2f(trunkX, trunkY);
    glVertex2f(trunkX + 3.0f, trunkY);
    glVertex2f(X1 + 1.0f, Y1);
    glVertex2f(X1, Y1);
    glEnd();

    // Draw leaves as 3 circles
    glColor3f(0.0f, 0.6f, 0.0f); // Green
    drawCircle(X1 - 4.0f, Y1, 4.0f, 100);         // Left leaf
    drawCircle(X1 + 5.0f, Y1, 4.0f, 100);         // Right leaf
    drawCircle(X1 + 0.5f, Y1 + 3.0f, 4.0f, 100);    // Top leaf
}

// trunkX, trunkY are the bottom-left of the trunk at (45, 50)
void drawTree(float trunkX, float trunkY) {
    // Trunk: width = 1, height = 6 (from 50 to 56)
    glColor3f(0.55f, 0.27f, 0.07f); // Brown
    glBegin(GL_QUADS);
    glVertex2f(trunkX, trunkY);
    glVertex2f(trunkX + 1.0f, trunkY);
    glVertex2f(trunkX + 1.0f, trunkY + 6.0f);
    glVertex2f(trunkX, trunkY + 6.0f);
    glEnd();

    // Draw leaf triangles
    glColor3f(0.6f, 1.0f, 0.6f);     // Light green
    glColor3f(0.6f, 0.9f, 0.2f);    //Yellow-Green
    glColor3f(0.0f, 1.0f, 0.5f);    //Spring Green
    glColor3f(0.75f, 1.0f, 0.0f);   //Lime


    // Triangle 1: relative to trunk
    drawTriangle(trunkX - 1.0f, trunkY + 3.0f,
        trunkX + 2.0f, trunkY + 3.0f,
        trunkX + 0.5f, trunkY + 15.0f);

    // Triangle 2
    drawTriangle(trunkX - 2.0f, trunkY + 4.0f,
        trunkX + 3.0f, trunkY + 4.0f,
        trunkX + 0.5f, trunkY + 12.0f);

    // Triangle 3
    drawTriangle(trunkX - 3.0f, trunkY + 5.0f,
        trunkX + 4.0f, trunkY + 5.0f,
        trunkX + 0.5f, trunkY + 9.0f);
}

// Object ID: OBJ6
void drawBuildingTop(float x1, float y1, float x2, float y2, float R, float G, float B, float BR, float BG, float BB) {

    glColor3f(R, G, B); // Building color
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    // Draw Building border
    glColor3f(BR, BG, BB); // Building border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    glLineWidth(1.5f);

}

void drawBuilding(float x1, float y1, float x2, float y2, float R, float G, float B, float BR, float BG, float BB) {

    glColor3f(R, G, B); // Building color
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    // Draw Building border
    glColor3f(BR, BG, BB); // Building border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    glLineWidth(1.5f);

}

void drawSideBuildingTop(float x1, float y1, float x2, float y2, float y3, float R, float G, float B, float BR, float BG, float BB) {

    glColor3f(R, G, B); // Building color
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y3);
    glEnd();

    // Draw Building border
    glColor3f(BR, BG, BB); // Building border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2f(x1, y3);
    glEnd();

    glLineWidth(1.5f);

}

void drawBuildingSide(float x1, float y1, float x2, float y2, float y3, float R, float G, float B, float BR, float BG, float BB) {

    glColor3f(R, G, B); // Building color
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y3);
    glEnd();

    // Draw Building border
    glColor3f(BR, BG, BB); // Building border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2f(x1, y3);
    glEnd();

    glLineWidth(1.5f);

}

void drawWindow(int x, int y, float R, float G, float B, float BR, float BG, float BB) {
    int x1 = x;
    int y1 = y;
    int x2 = x + 2;
    int y2 = y + 2;

    glColor3f(R, G, B); // Window color
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    // Draw Building border
    glColor3f(BR, BG, BB); // Building border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    glLineWidth(1.5f);
}

void drawWindowGrid(int startX, int startY, int rows, int cols, int xSpacing, int ySpacing, float R, float G, float B, float BR, float BG, float BB) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int x = startX + col * (2 + xSpacing); // 2 = window width
            int y = startY + row * (2 + ySpacing); // 2 = window height
            drawWindow(x, y, R, G, B, BR, BG, BB);
        }
    }
}

void drawSideWindow(int x, int y, float R, float G, float B, float BR, float BG, float BB) {
    int x1 = x;
    int y1 = y;
    int x2 = x + 2;
    int y2 = y + 2;

    glColor3f(R, G, B); // Window color
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1 + 1);
    glVertex2i(x2, y2 + 1);
    glVertex2i(x1, y2);
    glEnd();

    // Draw Building border
    glColor3f(BR, BG, BB); // Building border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1 + 1);
    glVertex2i(x2, y2 + 1);
    glVertex2i(x1, y2);
    glEnd();

    glLineWidth(1.5f);

}

void drawSideWindowGrid(int startX, int startY, int rows, int cols, int xSpacing, int ySpacing, float R, float G, float B, float BR, float BG, float BB) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int x = startX + col * (2 + xSpacing); // 2 = window width
            int y = startY + row * (2 + ySpacing); // 2 = window height
            drawSideWindow(x, y, R, G, B, BR, BG, BB);
        }
    }
}

void drawDoor1(int x, int y, float R, float G, float B, float BR, float BG, float BB) {
    // Window size is 2 units wide and 2 units tall (from your coords)
    int x1 = x;
    int y1 = y;
    int x2 = x + 2;
    int y2 = y + 3;

    // Draw filled DOOR
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    // Draw Building border
    glColor3f(BR, BG, BB); // Building border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    glLineWidth(1.5f);

}

void drawDoorGrid(int startX, int startY, int rows, int cols, int xGap, int yGap, float R, float G, float B, float BR, float BG, float BB) {
    int doorWidth = 2;
    int doorHeight = 3;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int x = startX + col * (doorWidth + xGap);
            int y = startY + row * (doorHeight + yGap);
            drawDoor1(x, y, R, G, B, BR, BG, BB);
        }
    }
}

// Object ID: OBJ7
//all about sky elements
void drawStars() {
    glColor3f(1.0f, 1.0f, 1.0f); // White stars
    srand(42); // Fixed seed for consistent star positions

    for (int i = 0; i < 100; i++) {
        float x = rand() % 100;
        float y = 60 + rand() % 40;
        drawCircle(x, y, 0.2, 100);
    }
}

// Object ID: OBJ8
void drawSun(float x, float y, float radius) {
    // Main sun body
    glColor3f(1.0f, 0.843f, 0.0f); // Gold color
    drawCircle(x, y, radius, 100);

    // Sun glow effect (optional)
    glColor4f(1.0f, 0.843f, 0.0f, 0.3f); // Semi-transparent gold
    drawCircle(x, y, radius * 1.5f, 100);
}

void drawCrescentMoon(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(1.0f, 1.0f, 0.8f);  // pale yellow
    drawCircle(x, y, radius, 100);

    // Overlapping circle to form crescent
    glColor3f(0.05f, 0.05f, 0.2f); // night sky color (to "cut" moon)
    drawCircle(x + radius * 0.2f, y + radius * 0.1f, radius * 0.85f, 100);
}

// Object ID: OBJ9
//Animation Function ID: ANM1
void updateClouds(int value) {
    cloudX1 += cloudSpeed;  // Update cloud position based on speed
    cloudX2 -= cloudSpeed;
    cloudX3 += cloudSpeed;

    // Reset cloud positions to create a looping effect
    if (cloudX1 > 110.0f) cloudX1 = -30.0f;
    if (cloudX2 < -20.0f) cloudX2 = 120.0f;
    if (cloudX3 > 110.0f) cloudX3 = -35.0f;

    glutPostRedisplay();  // Request a redraw
    glutTimerFunc(30, updateClouds, 0);  // Recursive call to keep the animation going
}

// Object ID: OBJ11
void drawPlane2(float axis_y) {
    glPushMatrix();
    // Plane will move with planeX2 horizontally, at axis_y vertically
    glTranslatef(planeX2, axis_y, 0.0f);

    // Positive scale so it's not mirrored, Z scale = 1
    glScalef(-16.0f, 30.0f, 1.0f);

    // ================= Plane Body =================
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.4214f, 0.2920f);
    glVertex2f(-0.8376f, 0.2912f);
    glVertex2f(-0.9320f, 0.2881f);
    glVertex2f(-0.9289f, 0.2556f);
    glVertex2f(-0.9041f, 0.2378f);
    glVertex2f(-0.8732f, 0.2278f);
    glVertex2f(-0.8453f, 0.2193f);
    glVertex2f(-0.8144f, 0.2108f);
    glVertex2f(-0.7842f, 0.2069f);
    glVertex2f(-0.7440f, 0.2077f);
    glVertex2f(-0.3897f, 0.2092f);
    glVertex2f(-0.3603f, 0.2131f);
    glEnd();

    // ================= Plane Head =================
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.4214f, 0.2920f);
    glVertex2f(-0.4044f, 0.2893f);
    glVertex2f(-0.3832f, 0.2803f);
    glVertex2f(-0.3546f, 0.2671f);
    glVertex2f(-0.3381f, 0.2622f);
    glVertex2f(-0.3238f, 0.2573f);
    glVertex2f(-0.3177f, 0.2518f);
    glVertex2f(-0.3122f, 0.2463f);
    glVertex2f(-0.3100f, 0.2400f);
    glVertex2f(-0.3098f, 0.2357f);
    glVertex2f(-0.3100f, 0.2300f);
    glVertex2f(-0.3138f, 0.2259f);
    glVertex2f(-0.3204f, 0.2228f);
    glVertex2f(-0.3281f, 0.2191f);
    glVertex2f(-0.3379f, 0.2157f);
    glVertex2f(-0.3500f, 0.2128f);
    glVertex2f(-0.3603f, 0.2131f);
    glEnd();

    // ================= Head Windows =================
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.3819f, 0.2759f);
    glVertex2f(-0.3881f, 0.2729f);
    glVertex2f(-0.3772f, 0.2609f);
    glVertex2f(-0.3705f, 0.2634f);
    glVertex2f(-0.3661f, 0.2658f);
    glVertex2f(-0.3609f, 0.2696f);
    glVertex2f(-0.3787f, 0.2782f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.3989f, 0.2687f);
    glVertex2f(-0.4099f, 0.2680f);
    glVertex2f(-0.4085f, 0.2627f);
    glVertex2f(-0.4031f, 0.2556f);
    glVertex2f(-0.3926f, 0.2562f);
    glVertex2f(-0.3805f, 0.2589f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.4128f, 0.2603f);
    glVertex2f(-0.4148f, 0.2668f);
    glVertex2f(-0.4318f, 0.2669f);
    glVertex2f(-0.4323f, 0.2604f);
    glVertex2f(-0.4296f, 0.2515f);
    glVertex2f(-0.4078f, 0.2526f);
    glEnd();

    // ================= Front Door =================
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.4540f, 0.2650f);
    glVertex2f(-0.4772f, 0.2641f);
    glVertex2f(-0.4757f, 0.2159f);
    glVertex2f(-0.4517f, 0.2157f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.4540f, 0.2650f);
    glVertex2f(-0.4772f, 0.2641f);
    glVertex2f(-0.4757f, 0.2159f);
    glVertex2f(-0.4517f, 0.2157f);
    glEnd();

    // Door Handle
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.4696f, 0.2426f);
    glVertex2f(-0.4728f, 0.2424f);
    glVertex2f(-0.4726f, 0.2379f);
    glVertex2f(-0.4693f, 0.2381f);
    glEnd();

    // ================= Wings =================
    // Upper Wing
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.5498f, 0.2873f);
    glVertex2f(-0.6218f, 0.3771f);
    glVertex2f(-0.6566f, 0.3778f);
    glVertex2f(-0.6489f, 0.2916f);
    glEnd();

    // Lower Wing
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.8513f, 0.1241f);
    glVertex2f(-0.8653f, 0.1246f);
    glVertex2f(-0.8522f, 0.1102f);
    glVertex2f(-0.8291f, 0.1111f);
    glVertex2f(-0.5056f, 0.2087f);
    glVertex2f(-0.7115f, 0.2078f);
    glEnd();

    // Lower Wing Back
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.8479f, 0.2812f);
    glVertex2f(-0.9293f, 0.2448f);
    glVertex2f(-0.9793f, 0.2453f);
    glVertex2f(-0.9320f, 0.2881f);
    glEnd();

    // Upper Wing Back
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.8229f, 0.3036f);
    glVertex2f(-0.8415f, 0.3121f);
    glVertex2f(-0.8562f, 0.3283f);
    glVertex2f(-0.9057f, 0.3910f);
    glVertex2f(-0.9428f, 0.3894f);
    glVertex2f(-0.9320f, 0.2881f);
    glVertex2f(-0.7618f, 0.2914f);
    glVertex2f(-0.7935f, 0.2959f);
    glVertex2f(-0.8097f, 0.2989f);
    glEnd();

    // ================= Back Door =================
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.7514f, 0.2701f);
    glVertex2f(-0.7756f, 0.2687f);
    glVertex2f(-0.7743f, 0.2286f);
    glVertex2f(-0.7496f, 0.2281f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.7514f, 0.2701f);
    glVertex2f(-0.7756f, 0.2687f);
    glVertex2f(-0.7743f, 0.2286f);
    glVertex2f(-0.7496f, 0.2281f);
    glEnd();

    // Back Door Handle
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.7679f, 0.2511f);
    glVertex2f(-0.7709f, 0.2509f);
    glVertex2f(-0.7708f, 0.2474f);
    glVertex2f(-0.7677f, 0.2477f);
    glEnd();

    // ================= Windows =================
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);

    // Window 1
    glVertex2f(-0.7151f, 0.2669f);
    glVertex2f(-0.7145f, 0.2435f);
    glVertex2f(-0.6963f, 0.2435f);
    glVertex2f(-0.6976f, 0.2669f);

    // Window 2
    glVertex2f(-0.6820f, 0.2682f);
    glVertex2f(-0.6813f, 0.2441f);
    glVertex2f(-0.6638f, 0.2445f);
    glVertex2f(-0.6641f, 0.2678f);

    // Window 3
    glVertex2f(-0.6501f, 0.2669f);
    glVertex2f(-0.6492f, 0.2448f);
    glVertex2f(-0.6316f, 0.2445f);
    glVertex2f(-0.6329f, 0.2672f);

    // Window 4
    glVertex2f(-0.6196f, 0.2672f);
    glVertex2f(-0.6183f, 0.2451f);
    glVertex2f(-0.6014f, 0.2448f);
    glVertex2f(-0.6030f, 0.2669f);

    // Window 5
    glVertex2f(-0.5858f, 0.2662f);
    glVertex2f(-0.5852f, 0.2458f);
    glVertex2f(-0.5702f, 0.2454f);
    glVertex2f(-0.5712f, 0.2669f);

    // Window 6
    glVertex2f(-0.5533f, 0.2669f);
    glVertex2f(-0.5520f, 0.2454f);
    glVertex2f(-0.5371f, 0.2448f);
    glVertex2f(-0.5394f, 0.2669f);

    // Window 7
    glVertex2f(-0.5228f, 0.2665f);
    glVertex2f(-0.5208f, 0.2432f);
    glVertex2f(-0.5040f, 0.2435f);
    glVertex2f(-0.5056f, 0.2669f);

    glEnd();

    glPopMatrix();
}

//Animation Function ID: ANM2
void updatePlane(int value) {
    planeX += planeSpeed;
    if (planeX > 120.0f) planeX = -30.0f; // Reset if it goes off right side

    planeX2 -= planeSpeed2;
    if (planeX2 < -20.0f) planeX2 = 120.0f; // Reset if it goes off right side

    glutPostRedisplay();
    glutTimerFunc(30, updatePlane, 0);

}

void drawCloud(float x, float y, float scale, float r, float g, float b) {
    glColor3f(r, g, b); // Set cloud color

    drawCircle(x, y, 4.0f * scale, 100);
    drawCircle(x + 3.0f * scale, y + 1.0f * scale, 4.5f * scale, 100);
    drawCircle(x + 6.0f * scale, y, 4.0f * scale, 100);
    drawCircle(x + 3.0f * scale, y - 1.5f * scale, 4.0f * scale, 100);
}

// Object ID: OBJ12

// Train position variables
float trainX = -100.0f;  // Starting x-position
float trainSpeed = 1.0f;  // Speed of movement

// Draw circle function (for wheels)
void circle(float cx, float cy, float r) {
    int num_segments = 50;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for(int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);
        glVertex2f(cx + r * cos(theta), cy + r * sin(theta));
    }
    glEnd();
}

// Draw full train
void drawTrain(float xOffset) {
    float scale = 0.08f;
    float yOffset = 30.0f;

    // ===== Car 1 =====
    glColor3f(0.0, 0.2, 0.7);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 0*scale, 200*scale + yOffset);
    glVertex2f(xOffset + 200*scale, 200*scale + yOffset);
    glVertex2f(xOffset + 200*scale, 300*scale + yOffset);
    glVertex2f(xOffset + 0*scale, 300*scale + yOffset);
    glEnd();

    glColor3f(1.0, 0.6, 0.2); // stripe
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 0*scale, 210*scale + yOffset);
    glVertex2f(xOffset + 200*scale, 210*scale + yOffset);
    glVertex2f(xOffset + 200*scale, 220*scale + yOffset);
    glVertex2f(xOffset + 0*scale, 220*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.0,0.1); // roof
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 0*scale,300*scale + yOffset);
    glVertex2f(xOffset + 200*scale,300*scale + yOffset);
    glVertex2f(xOffset + 220*scale,320*scale + yOffset);
    glVertex2f(xOffset + 30*scale,320*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.0,0.2); // slope
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 200*scale,300*scale + yOffset);
    glVertex2f(xOffset + 220*scale,320*scale + yOffset);
    glVertex2f(xOffset + 220*scale,230*scale + yOffset);
    glVertex2f(xOffset + 200*scale,200*scale + yOffset);
    glEnd();

    // windows + door
    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS); glVertex2f(xOffset + 10*scale,250*scale + yOffset); glVertex2f(xOffset + 40*scale,250*scale + yOffset); glVertex2f(xOffset + 40*scale,280*scale + yOffset); glVertex2f(xOffset + 10*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 50*scale,250*scale + yOffset); glVertex2f(xOffset + 80*scale,250*scale + yOffset); glVertex2f(xOffset + 80*scale,280*scale + yOffset); glVertex2f(xOffset + 50*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 90*scale,250*scale + yOffset); glVertex2f(xOffset + 120*scale,250*scale + yOffset); glVertex2f(xOffset + 120*scale,280*scale + yOffset); glVertex2f(xOffset + 90*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 130*scale,220*scale + yOffset); glVertex2f(xOffset + 165*scale,220*scale + yOffset); glVertex2f(xOffset + 165*scale,280*scale + yOffset); glVertex2f(xOffset + 130*scale,280*scale + yOffset); glEnd();

    // ===== Car 2 =====
    glColor3f(0.0,0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 220*scale,200*scale + yOffset);
    glVertex2f(xOffset + 420*scale,200*scale + yOffset);
    glVertex2f(xOffset + 420*scale,300*scale + yOffset);
    glVertex2f(xOffset + 220*scale,300*scale + yOffset);
    glEnd();

    glColor3f(1.0,0.6,0.2);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 220*scale,210*scale + yOffset);
    glVertex2f(xOffset + 420*scale,210*scale + yOffset);
    glVertex2f(xOffset + 420*scale,220*scale + yOffset);
    glVertex2f(xOffset + 220*scale,220*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 220*scale,300*scale + yOffset);
    glVertex2f(xOffset + 420*scale,300*scale + yOffset);
    glVertex2f(xOffset + 440*scale,320*scale + yOffset);
    glVertex2f(xOffset + 250*scale,320*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 420*scale,300*scale + yOffset);
    glVertex2f(xOffset + 440*scale,320*scale + yOffset);
    glVertex2f(xOffset + 440*scale,230*scale + yOffset);
    glVertex2f(xOffset + 420*scale,200*scale + yOffset);
    glEnd();

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS); glVertex2f(xOffset + 230*scale,250*scale + yOffset); glVertex2f(xOffset + 260*scale,250*scale + yOffset); glVertex2f(xOffset + 260*scale,280*scale + yOffset); glVertex2f(xOffset + 230*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 270*scale,250*scale + yOffset); glVertex2f(xOffset + 300*scale,250*scale + yOffset); glVertex2f(xOffset + 300*scale,280*scale + yOffset); glVertex2f(xOffset + 270*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 310*scale,250*scale + yOffset); glVertex2f(xOffset + 340*scale,250*scale + yOffset); glVertex2f(xOffset + 340*scale,280*scale + yOffset); glVertex2f(xOffset + 310*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 355*scale,220*scale + yOffset); glVertex2f(xOffset + 390*scale,220*scale + yOffset); glVertex2f(xOffset + 390*scale,280*scale + yOffset); glVertex2f(xOffset + 355*scale,280*scale + yOffset); glEnd();

    // ===== Car 3 =====
    glColor3f(0.0,0.2,0.7);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 440*scale,200*scale + yOffset);
    glVertex2f(xOffset + 640*scale,200*scale + yOffset);
    glVertex2f(xOffset + 640*scale,300*scale + yOffset);
    glVertex2f(xOffset + 440*scale,300*scale + yOffset);
    glEnd();

    glColor3f(1.0,0.6,0.2);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 440*scale,210*scale + yOffset);
    glVertex2f(xOffset + 640*scale,210*scale + yOffset);
    glVertex2f(xOffset + 640*scale,220*scale + yOffset);
    glVertex2f(xOffset + 440*scale,220*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 440*scale,300*scale + yOffset);
    glVertex2f(xOffset + 640*scale,300*scale + yOffset);
    glVertex2f(xOffset + 660*scale,320*scale + yOffset);
    glVertex2f(xOffset + 470*scale,320*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.0,0.2);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 640*scale,300*scale + yOffset);
    glVertex2f(xOffset + 660*scale,320*scale + yOffset);
    glVertex2f(xOffset + 660*scale,230*scale + yOffset);
    glVertex2f(xOffset + 640*scale,200*scale + yOffset);
    glEnd();

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS); glVertex2f(xOffset + 450*scale,250*scale + yOffset); glVertex2f(xOffset + 480*scale,250*scale + yOffset); glVertex2f(xOffset + 480*scale,280*scale + yOffset); glVertex2f(xOffset + 450*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 490*scale,250*scale + yOffset); glVertex2f(xOffset + 520*scale,250*scale + yOffset); glVertex2f(xOffset + 520*scale,280*scale + yOffset); glVertex2f(xOffset + 490*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 530*scale,250*scale + yOffset); glVertex2f(xOffset + 560*scale,250*scale + yOffset); glVertex2f(xOffset + 560*scale,280*scale + yOffset); glVertex2f(xOffset + 530*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 580*scale,220*scale + yOffset); glVertex2f(xOffset + 615*scale,220*scale + yOffset); glVertex2f(xOffset + 615*scale,280*scale + yOffset); glVertex2f(xOffset + 580*scale,280*scale + yOffset); glEnd();

    // ===== Engine =====
    glColor3f(0.0,0.2,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(xOffset + 660*scale,200*scale + yOffset); glVertex2f(xOffset + 860*scale,200*scale + yOffset);
    glVertex2f(xOffset + 860*scale,250*scale + yOffset); glVertex2f(xOffset + 760*scale,300*scale + yOffset); glVertex2f(xOffset + 660*scale,300*scale + yOffset);
    glEnd();

    glColor3f(1.0,0.6,0.2);
    glBegin(GL_QUADS);
    glVertex2f(xOffset + 660*scale,210*scale + yOffset); glVertex2f(xOffset + 860*scale,210*scale + yOffset);
    glVertex2f(xOffset + 860*scale,220*scale + yOffset); glVertex2f(xOffset + 660*scale,220*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.0,0.1);
    glBegin(GL_POLYGON);
    glVertex2f(xOffset + 660*scale,300*scale + yOffset); glVertex2f(xOffset + 760*scale,300*scale + yOffset);
    glVertex2f(xOffset + 790*scale,320*scale + yOffset); glVertex2f(xOffset + 690*scale,320*scale + yOffset);
    glEnd();

    glColor3f(0.0,0.6,0.7);
    glBegin(GL_POLYGON);
    glVertex2f(xOffset + 760*scale,300*scale + yOffset); glVertex2f(xOffset + 790*scale,320*scale + yOffset);
    glVertex2f(xOffset + 880*scale,270*scale + yOffset); glVertex2f(xOffset + 860*scale,250*scale + yOffset);
    glEnd();

    glColor3f(0.7,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(xOffset + 860*scale,200*scale + yOffset); glVertex2f(xOffset + 860*scale,250*scale + yOffset);
    glVertex2f(xOffset + 880*scale,270*scale + yOffset); glVertex2f(xOffset + 880*scale,225*scale + yOffset);
    glEnd();

    glColor3f(1.0f,1.0f,1.0f);
    glBegin(GL_QUADS); glVertex2f(xOffset + 680*scale,220*scale + yOffset); glVertex2f(xOffset + 720*scale,220*scale + yOffset); glVertex2f(xOffset + 720*scale,280*scale + yOffset); glVertex2f(xOffset + 680*scale,280*scale + yOffset); glEnd();
    glBegin(GL_QUADS); glVertex2f(xOffset + 730*scale,250*scale + yOffset); glVertex2f(xOffset + 760*scale,250*scale + yOffset); glVertex2f(xOffset + 760*scale,280*scale + yOffset); glVertex2f(xOffset + 730*scale,280*scale + yOffset); glEnd();

    // ===== Wheels =====
    glColor3f(0.0,0.0,0.0);
    int wheelX[] = {10,60,110,170, 250,300,350,400, 460,510,560,620, 680,730,780,830};
    for(int i=0;i<16;i++) circle(xOffset + wheelX[i]*scale, 200*scale + yOffset, 10*scale);
}

// Timer function to update train position
void updateTrain(int value) {
    trainX += trainSpeed;
    if(trainX > 240.0f) trainX = -200.0f; // Reset to left

    glutPostRedisplay();
    glutTimerFunc(30, updateTrain, 0);
}

// Object ID: OBJ14
void drawTaxi() {
    glPushMatrix();
    glTranslatef(carX1, 26.0f, 0.0f);
    glScalef(1.8f, 1.8f, 1.0f);

    // --- Body ---
    glColor3f(1.0f, 0.5f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-8.0f, -2.0f);
    glVertex2f(-1.0f, -2.0f);
    glVertex2f(-1.0f, 1.0f);
    glVertex2f(-8.0f, 1.0f);
    glEnd();

    // --- Taxi's roof---
    glBegin(GL_QUADS);
    glVertex2f(-6.5f, 1.0f);
    glVertex2f(-2.5f, 1.0f);
    glVertex2f(-3.0f, 3.0f);
    glVertex2f(-6.0f, 3.0f);
    glEnd();

    // --- (Roof light) ---
    glColor3f(1.0f, 0.2f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(-4.6f, 3.0f);
    glVertex2f(-4.2f, 3.0f);
    glVertex2f(-4.4f, 3.8f);
    glEnd();

    // ---(Windows) ---
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(-6.0f, 1.0f);
    glVertex2f(-4.5f, 1.0f);
    glVertex2f(-4.8f, 2.7f);
    glVertex2f(-6.0f, 2.7f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-4.5f, 1.0f);
    glVertex2f(-3.0f, 1.0f);
    glVertex2f(-3.2f, 2.7f);
    glVertex2f(-4.8f, 2.7f);
    glEnd();

    // --- Write Down Taxi ---
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(-7.5f, 0.0f);
    const char* text = "TAXI";
    for (int i = 0; text[i] != '\0'; i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }

    // --- Divided Door---
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(-4.8f, -2.0f);
    glVertex2f(-4.8f, 1.0f);
    glEnd();

    // --- Handle ---
    glBegin(GL_QUADS);
    glVertex2f(-5.5f, 0.0f);
    glVertex2f(-5.1f, 0.0f);
    glVertex2f(-5.1f, -0.3f);
    glVertex2f(-5.5f, -0.3f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(-3.9f, 0.0f);
    glVertex2f(-3.5f, 0.0f);
    glVertex2f(-3.5f, -0.3f);
    glVertex2f(-3.9f, -0.3f);
    glEnd();

    // --- Wheel ---
    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(-2.0f, -2.0f, 1.0f, 100);
    drawCircle(-7.0f, -2.0f, 1.0f, 100);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(-2.0f, -2.0f, 0.5f, 100);
    drawCircle(-7.0f, -2.0f, 0.5f, 100);

    // ================= Optional: Night light beam =================
if (nightLight == true) {

    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 200);
    glVertex2f(0.3f, -0.45f);
    glVertex2f(1.0f, -0.7f);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(0.3f, -0.3f);
    glEnd();

}

    glPopMatrix();
}

void drawMiniCar() {
    glPushMatrix();
    glTranslatef(carX2, 40.0f, 0.0f);  // Move car onto road
    glScalef(-7.5, 7.5, 1);           // Maintain flipping

    // ================= Wheels =================
    drawCircle(0.1f, -0.52f, 0.1f, 100);     // Rear wheel
    drawCircle(-0.4f, -0.52f, 0.1f, 100);    // Front wheel

    // ================= Car Body =================
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);  // Bright red
    glVertex2f(0.3f, -0.2f);
    glVertex2f(0.3f, -0.5f);
    glVertex2f(-0.6f, -0.5f);
    glVertex2f(-0.6f, -0.2f);
    glEnd();

    // ================= Roof and Windshield =================
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.8f, 1.0f);  // Light blue for windshield
    glVertex2f(0.15f, -0.2f);
    glVertex2f(0.05f, 0.02f);
    glVertex2f(-0.3f, 0.02f);
    glVertex2f(-0.4f, -0.2f);
    glEnd();

    // Roof outline
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.15f, -0.2f);
    glVertex2f(0.05f, 0.02f);
    glVertex2f(-0.3f, 0.02f);
    glVertex2f(-0.4f, -0.2f);
    glEnd();

    // ================= Headlights =================
    glColor3f(1.0f, 1.0f, 1.0f);  // White lights
    drawCircle(0.25f, -0.33f, 0.05f, 100);
    drawCircle(-0.55f, -0.33f, 0.05f, 100);

    // ================= Front Grille =================
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.1f, 0.1f);  // Dark grey grille
    glVertex2f(-0.55f, -0.4f);
    glVertex2f(-0.45f, -0.5f);
    glVertex2f(0.2f, -0.5f);
    glVertex2f(0.3f, -0.4f);
    glEnd();

    // ================= Hood Stripes =================
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(0.15f, -0.2f);
    glVertex2f(0.15f, -0.45f);
    glVertex2f(0.05f, -0.2f);
    glVertex2f(0.05f, -0.45f);
    glEnd();

    // ================= Door Outline =================
    glBegin(GL_LINE_LOOP);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(-0.05f, -0.2f);
    glVertex2f(-0.05f, -0.45f);
    glVertex2f(-0.45f, -0.45f);
    glVertex2f(-0.45f, -0.2f);
    glEnd();

    // ================= Seat =================
    glBegin(GL_QUADS);
    glColor3f(0.1f, 0.1f, 0.1f);  // Black seat
    glVertex2f(-0.3f, -0.2f);
    glVertex2f(-0.3f, -0.05f);
    glVertex2f(-0.1f, -0.05f);
    glVertex2f(-0.1f, -0.2f);
    glEnd();

    // ================= Side Mirror =================
    drawCircle(0.28f, -0.22f, 0.025f, 20); // Right mirror

    // ================= Optional: Night light beam =================
    if (nightLight == true) {
        glBegin(GL_POLYGON);
        glColor3ub(192, 192, 192);
        glVertex2f(0.3f, -0.45f);
        glVertex2f(0.8f, -0.6f);
        glVertex2f(0.8f, -0.1f);
        glVertex2f(0.3f, -0.3f);
        glEnd();
    }

    glPopMatrix();
}

// Object ID: OBJ15
void drawMegendaBus() {
    glPushMatrix();
glTranslatef(carX2, 65.0f, 0.0f);  // Truck position shifted up by 10
glScalef(-28.0f, 28.0f, 1.0f);

    // === Truck Body with 3D gradient ===
    glBegin(GL_QUADS);
    glColor3f(0.55f, 0.0f, 0.55f);  // Dark left
    glVertex2f(0.0f, -0.85f);
    glVertex2f(0.45f, -0.85f);
    glColor3f(0.75f, 0.0f, 0.75f);  // Light right
    glVertex2f(0.45f, -0.65f);
    glVertex2f(0.0f, -0.65f);
    glEnd();

    // === Cabin / Front with curved 3D hood ===
    glBegin(GL_POLYGON);
    glColor3f(0.25f, 0.25f, 0.25f);  // Shadow
    glVertex2f(0.45f, -0.85f);
    glVertex2f(0.55f, -0.85f);
    glColor3f(0.5f, 0.5f, 0.5f);     // Highlight
    glVertex2f(0.55f, -0.65f);
    glVertex2f(0.465f, -0.65f);
    glVertex2f(0.45f, -0.70f);       // Hood curve
    glEnd();

    // === Windshield with gradient for 3D reflection ===
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.5f, 0.9f);  // bottom
    glVertex2f(0.465f, -0.72f);
    glVertex2f(0.545f, -0.72f);
    glColor3f(0.6f, 0.8f, 1.0f);  // top
    glVertex2f(0.545f, -0.665f);
    glVertex2f(0.47f, -0.665f);
    glEnd();

    // === Side Window 3D ===
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.4f, 0.9f);  // bottom
    glVertex2f(0.47f, -0.78f);
    glVertex2f(0.535f, -0.78f);
    glColor3f(0.5f, 0.7f, 0.95f); // top
    glVertex2f(0.535f, -0.72f);
    glVertex2f(0.47f, -0.72f);
    glEnd();

    // === Door outline + handle ===
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.465f, -0.85f);
    glVertex2f(0.535f, -0.85f);
    glVertex2f(0.535f, -0.72f);
    glVertex2f(0.465f, -0.72f);
    glEnd();

    glBegin(GL_QUADS);  // Handle
    glVertex2f(0.485f, -0.80f);
    glVertex2f(0.495f, -0.80f);
    glVertex2f(0.495f, -0.81f);
    glVertex2f(0.485f, -0.81f);
    glEnd();

    // === Front Grille (vertical lines) ===
    for (float y = -0.80f; y > -0.85f; y -= 0.012f) {
        glBegin(GL_LINES);
        glVertex2f(0.54f, y);
        glVertex2f(0.55f, y);
        glEnd();
    }

    // === Headlights 3D ===
    float lightY[] = {-0.77f, -0.83f};
    for (int i = 0; i < 2; i++) {
        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 0.0f); // Outer yellow
        glVertex2f(0.545f, lightY[i]);
        glVertex2f(0.555f, lightY[i]);
        glVertex2f(0.555f, lightY[i]-0.02f);
        glVertex2f(0.545f, lightY[i]-0.02f);
        glEnd();

        glBegin(GL_QUADS);
        glColor3f(1.0f, 1.0f, 1.0f); // Inner white
        glVertex2f(0.548f, lightY[i]-0.008f);
        glVertex2f(0.555f, lightY[i]-0.008f);
        glVertex2f(0.555f, lightY[i]-0.016f);
        glVertex2f(0.548f, lightY[i]-0.016f);
        glEnd();
    }

    // === Roof Light Bar ===
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.3f, 0.0f);
    glVertex2f(0.46f, -0.645f);
    glVertex2f(0.545f, -0.645f);
    glVertex2f(0.545f, -0.66f);
    glVertex2f(0.46f, -0.66f);
    glEnd();

    // === Side Mirrors 3D ===
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(0.455f, -0.735f);
    glVertex2f(0.44f, -0.735f);
    glVertex2f(0.44f, -0.755f);
    glVertex2f(0.455f, -0.755f);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.545f, -0.735f);
    glVertex2f(0.56f, -0.735f);
    glVertex2f(0.56f, -0.755f);
    glVertex2f(0.545f, -0.755f);
    glEnd();

    // === Wheels with 3D shading ===
    float wheelX[] = {0.12f, 0.32f, 0.52f};
    float wheelY = -0.87f;
    float radiusOuter = 0.04f, radiusInner = 0.02f;
    int triangleAmount = 40;
    float twicePi = 2.0f * 3.1415926f;

    for (int w = 0; w < 3; w++) {
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.05f, 0.05f, 0.05f);
        glVertex2f(wheelX[w], wheelY);
        for (int i = 0; i <= triangleAmount; i++) {
            float angle = i * twicePi / triangleAmount;
            glColor3f(0.05f + 0.05f*cos(angle), 0.05f + 0.05f*sin(angle), 0.05f);
            glVertex2f(wheelX[w] + radiusOuter * cos(angle),
                       wheelY + radiusOuter * sin(angle));
        }
        glEnd();

        glColor3f(0.8f, 0.8f, 0.8f);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(wheelX[w], wheelY);
        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(wheelX[w] + radiusInner * cos(i * twicePi / triangleAmount),
                       wheelY + radiusInner * sin(i * twicePi / triangleAmount));
        }
        glEnd();
    }

    // === Night Mode Headlight Beam ===
 // === Night Mode Headlight Beam (Smaller Area) ===
if (nightLight) {
    // Inner bright cone (smaller)
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 180);
    glVertex2f(0.55f, -0.75f); // front right headlight
    glVertex2f(0.9f, -0.82f);
    glVertex2f(0.9f, -0.68f);
    glVertex2f(0.55f, -0.73f);
    glEnd();

    // Outer faint cone (smaller)
    glBegin(GL_POLYGON);
    glColor3ub(230, 230, 180);
    glVertex2f(0.55f, -0.75f);
    glVertex2f(1.0f, -0.85f);
    glVertex2f(1.0f, -0.65f);
    glVertex2f(0.55f, -0.73f);
    glEnd();
}

    glPopMatrix();
}


void drawTruck() {
   glPushMatrix();
  glTranslatef(carX1, 34.0f, 0.0f);
    glScalef(-1.0f, 1.0f, 1.0f);

    glPushMatrix();
    glTranslatef(-25.0f, 5.0f, 0.0f);

    // ========== Body ==========
   glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(21.0f, 0.875f);
    glVertex2f(21.0f, -1.0f);
    glVertex2f(16.0f, -1.0f);
    glVertex2f(16.5f, 0.875f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.0f, 0.5f, 0.0f);
    glVertex2f(21.0f, -1.0f);
    glVertex2f(21.0f, -3.35f);
    glVertex2f(15.0f, -3.35f);
    glVertex2f(15.0f, -1.0f);
    glEnd();

    // ========== Front Light ==========
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.038f, 0.27f);
    glVertex2f(15.3f, -1.0f);
    glVertex2f(15.45f, -1.6f);
    glVertex2f(15.0f, -1.6f);
    glVertex2f(15.0f, -1.0f);
    glEnd();

    // ========== Night Beam ==========
    if (nightLight == true) {
        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.6f, 0.2f);
        glVertex2f(15.0f, -1.25f);
        glVertex2f(15.0f, -1.6f);
        glColor3f(1.0f, 1.0f, 0.79f);
        glVertex2f(14.0f, -3.35f);
        glVertex2f(12.5f, -3.35f);
        glEnd();
    }

    // ========== Back Light ==========
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.38f, 0.27f);
    glVertex2f(21.0f, -2.0f);
    glVertex2f(20.65f, -2.0f);
    glVertex2f(20.65f, -2.7f);
    glVertex2f(21.0f, -2.7f);
    glEnd();

    // ========== Wheel Box ==========
    glBegin(GL_QUADS);
    glColor3f(0.8f, 1.0f, 1.0f);
    glVertex2f(21.0f, -0.9f);
    glVertex2f(21.25f, -0.9f);
    glVertex2f(21.25f, -2.5f);
    glVertex2f(21.0f, -2.65f);
    glEnd();

    // ========== Windows ==========
    glColor3f(0.8f, 1.0f, 1.0f);
    glBegin(GL_QUADS); // Window 1
    glVertex2f(17.6f, 0.75f);
    glVertex2f(17.6f, -1.0f);
    glVertex2f(16.25f, -1.0f);
    glVertex2f(16.7f, 0.75f);
    glEnd();

    glBegin(GL_QUADS); // Window 2
    glVertex2f(17.7f, 0.75f);
    glVertex2f(17.7f, -1.0f);
    glVertex2f(18.7f, -1.0f);
    glVertex2f(18.7f, 0.75f);
    glEnd();

    glBegin(GL_QUADS); // Window 3
    glVertex2f(20.5f, 0.75f);
    glVertex2f(20.5f, -1.0f);
    glVertex2f(18.8f, -1.0f);
    glVertex2f(18.8f, 0.75f);
    glEnd();

    // ========== Doors ==========
    glBegin(GL_QUADS); // Door 1
    glVertex2f(17.6f, -1.15f);
    glVertex2f(17.6f, -1.35f);
    glVertex2f(17.2f, -1.35f);
    glVertex2f(17.2f, -1.15f);
    glEnd();

    glBegin(GL_QUADS); // Door 2
    glVertex2f(18.65f, -1.15f);
    glVertex2f(18.65f, -1.35f);
    glVertex2f(18.35f, -1.35f);
    glVertex2f(18.35f, -1.15f);
    glEnd();

    // ========== Wheels ==========
    int triangleAmount = 40;
    float twicePi = 2.0f * M_PI;

    // Wheel 1
    float xc1 = 16.5f, yc1 = -3.35f, r1 = 0.75f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc1, yc1);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            xc1 + (r1 * cos(i * twicePi / triangleAmount)),
            yc1 + (r1 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    // Rim
    float r1_inner = 0.4f;
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc1, yc1);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            xc1 + (r1_inner * cos(i * twicePi / triangleAmount)),
            yc1 + (r1_inner * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    // Wheel 2
    float xc2 = 19.5f, yc2 = -3.35f;
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc2, yc2);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            xc2 + (r1 * cos(i * twicePi / triangleAmount)),
            yc2 + (r1 * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    // Rim 2
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(xc2, yc2);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            xc2 + (r1_inner * cos(i * twicePi / triangleAmount)),
            yc2 + (r1_inner * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();

    glPopMatrix();
    glPopMatrix();
}

//Animation Function ID: ANM4
void updateCars(int value) {
    // Move first car right
    carX1 += carSpeed1;
    if (carX1 > 120.0f) carX1 = -30.0f; // Loop left to right

    // Move second car left
    carX2 += carSpeed2;
    if (carX2 < -30.0f) carX2 = 120.0f; // Loop right to left

    carX3 += carSpeed3;
    if (carX3 > 160.0f) carX3 = -40.0f; // Loop left to right

    carX4 += carSpeed4;
    if (carX4 < -50.0f) carX4 = 150.0f;

    glutPostRedisplay();
    glutTimerFunc(30, updateCars, 0);
glColor3f(1.0f, 1.0f, 1.0f);
drawCircle(-0.14f, -0.3f, 0.03f, 30);

// ===== Optional: Night Mode Headlight Beam =====
if (nightLight == true) {
    // Inner bright cone
    glBegin(GL_POLYGON);
    glColor3ub(255, 255, 180);
    glVertex2f(-0.14f, -0.3f);
    glVertex2f(1.0f, -0.7f);
    glVertex2f(1.0f, -0.1f);
    glVertex2f(-0.14f, -0.25f);
    glEnd();

    // Outer faint cone
    glBegin(GL_POLYGON);
    glColor3ub(230, 230, 180);
    glVertex2f(-0.14f, -0.3f);
    glVertex2f(1.5f, -0.8f);
    glVertex2f(1.5f, 0.15f);
    glVertex2f(-0.14f, -0.25f);
    glEnd();
}

}

// Object ID: OBJ16
//all about River elements

// Object ID: OBJ17
void drawBoat(float x, float y) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);  // Move boat to desired position
    glScalef(1.4f, 0.8f, 1.0f); // Adjust scale to better fit scene (you can tweak this)

    // Top red body
    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(3.5, 5.5);
    glVertex2f(3.5, 8.5);
    glVertex2f(19.5, 8.5);
    glVertex2f(19.5, 5.5);
    glEnd();

    // Bottom blue hull
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex2f(1, 5.5);
    glVertex2f(4, 1);
    glVertex2f(19, 1);
    glVertex2f(21.5, 5.5);
    glEnd();

    // Mast
    glColor3f(0.7, 0.4, 0.2);
    glBegin(GL_POLYGON);
    glVertex2f(4, 5.5);
    glVertex2f(4, 8);
    glVertex2f(5, 8);
    glVertex2f(5, 5.5);
    glEnd();

    // Windows
    glColor3f(0.9, 0.9, 0.9);
    float wx[][4] = { {7,7.5,10,8}, {11.5,7.5,15,8}, {16,7.5,19,8} };
    for (auto& w : wx) {
        glBegin(GL_POLYGON);
        glVertex2f(w[0], w[1]);
        glVertex2f(w[0], w[3]);
        glVertex2f(w[2], w[3]);
        glVertex2f(w[2], w[1]);
        glEnd();
    }

    // Top Deck
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(4.5, 8.5);
    glVertex2f(4.5, 10);
    glVertex2f(18.5, 10);
    glVertex2f(18.5, 8.5);
    glEnd();

    // Chimneys
    float chimneyX[] = { 5.5, 8.5, 11.5, 14.5 };
    for (int i = 0; i < 4; ++i) {
        float cx = chimneyX[i];

        // Base
        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        glVertex2f(cx, 10);
        glVertex2f(cx, 12.9);
        glVertex2f(cx + 1.5, 12.9);
        glVertex2f(cx + 1.5, 10);
        glEnd();

        // Cap
        glColor3f(0.9, 0.5, 0.2);
        glBegin(GL_POLYGON);
        glVertex2f(cx, 12.9);
        glVertex2f(cx, 13.5);
        glVertex2f(cx + 1.5, 13.5);
        glVertex2f(cx + 1.5, 12.9);
        glEnd();
    }

    glPopMatrix();
}

//Animation Function ID: ANM6
void updateBoat(int value) {
    boatX += boatSpeed;
    if (boatX > 130.0f) boatX = -30.0f; // Reset once off screen right
    glutPostRedisplay();
    glutTimerFunc(30, updateBoat, 0);
}

//all about Rain
typedef struct {
    float x, y;
    float targetY;
} RainDrop;

typedef struct {
    float x, y;
    float radius;
    int active;
    float alpha;
} Splash;

RainDrop rain[MAX_RAINDROPS];
Splash splashes[MAX_SPLASHES];
float rainSpeed = 0.6f;

float randomRange(float min, float max) {
    return min + ((float)rand() / RAND_MAX) * (max - min);
}

void initRain() {
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        rain[i].x = rand() % 100;
        rain[i].y = 100 + rand() % 50;
        rain[i].targetY = randomRange(rainTargetYMin, rainTargetYMax);
    }
    for (int i = 0; i < MAX_SPLASHES; i++) {
        splashes[i].active = 0;
    }
}

void addSplash(float x, float y) {
    for (int i = 0; i < MAX_SPLASHES; i++) {
        if (!splashes[i].active) {
            splashes[i].x = x;
            splashes[i].y = y;
            splashes[i].radius = 0.01f;
            splashes[i].alpha = 1.0f;
            splashes[i].active = 1;
            break;
        }
    }
}

// Object ID: OBJ18
void drawRain() {
    glColor3f(0.7f, 0.8f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        glVertex2f(rain[i].x, rain[i].y);
        glVertex2f(rain[i].x, rain[i].y - 2.0f);
    }
    glEnd();
}

// Object ID: OBJ19
void drawSplashes() {
    for (int i = 0; i < MAX_SPLASHES; i++) {
        if (splashes[i].active) {
            glColor4f(1.0f, 1.0f, 1.0f, splashes[i].alpha);
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < 12; j++) {
                float angle = 2 * PI * j / 12;
                float dx = splashes[i].radius * cos(angle);
                float dy = splashes[i].radius * sin(angle);
                glVertex2f(splashes[i].x + dx, splashes[i].y + dy);
            }
            glEnd();
        }
    }
}

//Animation Function ID: ANM7
void updateRain(int value) {
    for (int i = 0; i < MAX_RAINDROPS; i++) {
        rain[i].y -= rainSpeed;

        // Check if it has reached the target splash point
        if (rain[i].y <= rain[i].targetY) {
            addSplash(rain[i].x, rain[i].targetY);

            // Reset raindrop
            rain[i].x = rand() % 100;
            rain[i].y = 100 + rand() % 50;
            rain[i].targetY = randomRange(rainTargetYMin, rainTargetYMax);
        }
    }

    // Update splashes
    for (int i = 0; i < MAX_SPLASHES; i++) {
        if (splashes[i].active) {
            splashes[i].radius += 0.03f;
            splashes[i].alpha -= 0.03f;
            if (splashes[i].alpha <= 0.0f) {
                splashes[i].active = 0;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateRain, 0);
}

// Object ID: OBJ20
void drawLightningBolt(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); // Bright white bolt
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x + 2, y - 8);
    glVertex2f(x - 2, y - 16);
    glVertex2f(x + 1, y - 24);
    glEnd();
}

void drawLightningFlash() {
    if (lightningActive) {
        // White semi-transparent screen flash
        glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 60.0f);
        glVertex2f(100.0f, 60.0f);
        glVertex2f(100.0f, 100.0f);
        glVertex2f(0.0f, 100.0f);
        glEnd();
        drawBorder();
        drawRiver(0.682f, 0.863f, 0.949f);
        drawSky(0.529f, 0.808f, 0.922f);
        drawRailPath();
        drawCloud(cloudX1, 85.0f, 1.0f, 1.0f, 1.0f, 1.0f);
        drawCloud(cloudX2, 90.0f, 1.2f, 0.95f, 0.95f, 0.95f);
        drawCloud(cloudX3, 88.0f, 0.8f, 0.9f, 0.9f, 0.9f);
        drawBuildingSide(94.0f, 50.0f, 96.0f, 71.0f, 70.0f, 0.463f, 0.286f, 0.216f, 0.506f, 0.322f, 0.235f);
        drawBuilding(90.0f, 50.0f, 94.0f, 70.0f, 0.737f, 0.435f, 0.294f, 0.506f, 0.322f, 0.235f);
        drawWindowGrid(91, 55, 4, 1, 0, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
        drawDoorGrid(91, 50, 1, 1, 1, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);

        drawBuilding(96.0f, 50.0f, 100.0f, 75.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
        drawWindowGrid(97, 55, 5, 1, 0, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
        drawDoorGrid(97, 50, 1, 1, 1, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);

        drawSideBuildingTop(31.0f, 80.0f, 35.0f, 83.0f, 82.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
        drawBuildingSide(32.0f, 50.0f, 36.0f, 81.0f, 80.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
        drawBuildingTop(20.0f, 80.0f, 31.0f, 82.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
        drawBuilding(18.0f, 50.0f, 32.0f, 80.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
        drawWindowGrid(20, 54, 6, 3, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
        drawSideWindowGrid(33, 54, 6, 1, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
        drawDoorGrid(22, 50, 1, 3, 0, 0, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);


        drawSideBuildingTop(59.0f, 70.0f, 65.0f, 74.0f, 73.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
        drawBuildingSide(60.0f, 50.0f, 66.0f, 71.0f, 70.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
        drawBuildingTop(51.0f, 70.0f, 59.0f, 73.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
        drawBuilding(50.0f, 50.0f, 60.0f, 70.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
        drawWindowGrid(52, 58, 3, 2, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
        drawSideWindowGrid(62, 54, 4, 1, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
        drawDoorGrid(53, 50, 2, 2, 0, 0, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);



        drawBuildingSide(75.0f, 50.0f, 80.0f, 70.0f, 67.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
        drawBuilding(67.0f, 50.0f, 75.0f, 67.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
        drawWindowGrid(69, 54, 3, 2, 1.5, 2, 0.506f, 0.322f, 0.235, 0.506f, 0.322f, 0.235f);
        glColor3f(0.506f, 0.322f, 0.235f); // Window color
        glBegin(GL_POLYGON);
        glVertex2i(67, 67);
        glVertex2i(75, 67);
        glVertex2i(80, 70);
        glVertex2i(72, 70);
        glEnd();

        // Draw bolt using current random coordinates
        drawLightningBolt(boltX, boltY);
        drawLightningBolt(boltX + 10, boltY - 20);
        drawLightningBolt(boltX - 10, boltY - 20);
    }
}

//Animation Function ID: ANM8
void updateLightning(int value) {
    if (isRaining) {
        lightningActive = true;

        // Randomize bolt position
        boltX = rand() % 80 + 10;
        boltY = rand() % 10 + 80;

        // Turn off lightning after 2 seconds
        glutTimerFunc(30, [](int) {
            lightningActive = false;
            glutPostRedisplay();
            }, 0);
    }

    glutPostRedisplay();
    glutTimerFunc(5000, updateLightning, 0); // Repeat every 5 seconds
}

void drawLightningBolt2(float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); // Bright white bolt
    glLineWidth(2.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(x, y);
    glVertex2f(x + 2, y - 8);
    glVertex2f(x - 2, y - 16);
    glVertex2f(x + 1, y - 24);
    glEnd();
}

void drawLightningFlash2() {
    if (lightningActive2) {
        // Draw bolt using current random coordinates
        drawLightningBolt2(boltX, boltY);
        drawLightningBolt2(boltX + 5, boltY + 20);
        drawLightningBolt2(boltX - 10, boltY + 20);
    }
}

void updateLightning2(int value) {
    if (isRaining) {
        lightningActive2 = true;

        // Randomize bolt position
        boltX = rand() % 80 + 10;
        boltY = rand() % 10 + 80;

        // Turn off lightning after 2 seconds
        glutTimerFunc(800, [](int) {
            lightningActive2 = false;
            glutPostRedisplay();
            }, 0);
    }

    glutPostRedisplay();
    glutTimerFunc(7000, updateLightning2, 0); // Repeat every 5 seconds
}

//all Scene

//Animation Function ID: ANM9
void drawDayScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    drawBorder();
    drawRiver(0.682f, 0.863f, 0.949f);
    drawSky(0.529f, 0.808f, 0.922f);
    drawRailPath();
    drawSun(85.0f, 85.0f, 4.0f);
    drawCloud(cloudX1, 85.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    drawCloud(cloudX2, 90.0f, 1.2f, 0.95f, 0.95f, 0.95f);
    drawCloud(cloudX3, 88.0f, 0.8f, 0.9f, 0.9f, 0.9f);

        // --------------------  Building3 --------------------

    drawSideBuildingTop(91.0f, 80.0f, 95.0f, 83.0f, 82.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingSide(92.0f, 50.0f, 96.0f, 81.0f, 80.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingTop(80.0f, 80.0f, 91.0f, 82.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawBuilding(78.0f, 50.0f, 92.0f, 80.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawWindowGrid(80, 54, 6, 3, 2, 2, 0.2f, 0.3f, 0.4f, 0.2f, 0.3f, 0.4f);
    drawSideWindowGrid(93, 54, 6, 1, 2, 2, 0.2f, 0.3f, 0.4f, 0.2f, 0.3f, 0.4f);
    drawDoorGrid(82, 50, 1, 3, 0, 0, 0.2f, 0.3f, 0.4f, 0.2f, 0.3f, 0.4f);

    // --------------------  Building1 --------------------
    drawBuildingSide(94.0f, 50.0f, 96.0f, 71.0f, 70.0f, 0.463f, 0.286f, 0.216f, 0.506f, 0.322f, 0.235f);
    drawBuilding(90.0f, 50.0f, 94.0f, 70.0f, 0.737f, 0.435f, 0.294f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(91, 55, 4, 1, 0, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(91, 50, 1, 1, 1, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);

    // --------------------  Building2 --------------------

    drawBuilding(96.0f, 50.0f, 100.0f, 75.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(97, 55, 5, 1, 0, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(97, 50, 1, 1, 1, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);



    // -------------------- Hotel Building4 --------------------

    drawBuilding(65.0f, 50.0f, 81.0f, 85.0f, 0.75f, 0.65f, 0.55f, 0.45f, 0.35f, 0.25f);
    drawWindowGrid(66 + 0, 58, 6, 5, 1, 2, 0.45f, 0.35f, 0.25f, 0.55f, 0.45f, 0.35f);  // Added one more column (5 windows wide)
    drawDoorGrid(74, 50, 2, 1, 0, 1, 0.3f, 0.25f, 0.2f, 0.4f, 0.35f, 0.3f);  // Shifted door 4 units right from 70 to 74

    // -------------------- Skyscraper Building9 --------------------

    drawSideBuildingTop(16.0f, 140.0f, 20.0f, 144.0f, 143.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingSide(17.0f, 50.0f, 21.0f, 142.0f, 140.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingTop(0.0f, 140.0f, 16.0f, 143.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawBuilding(-2.0f, 50.0f, 17.0f, 140.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawWindowGrid(1, 55, 11, 4, 2, 3, 0.75f, 0.9f, 1.0f, 0.15f, 0.15f, 0.15f);
    drawSideWindowGrid(18, 55, 11, 1, 2, 3, 0.75f, 0.9f, 1.0f, 0.15f, 0.15f, 0.15f);
    drawDoorGrid(5, 50, 1, 2, 3, 0, 0.25f, 0.2f, 0.15f, 0.1f, 0.1f, 0.1f);

    // --------------------  Building7 --------------------

    drawSideBuildingTop(51.0f, 80.0f, 55.0f, 83.0f, 82.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(52.0f, 50.0f, 56.0f, 81.0f, 80.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(40.0f, 80.0f, 51.0f, 82.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawBuilding(38.0f, 50.0f, 52.0f, 80.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(40, 54, 6, 3, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawSideWindowGrid(53, 54, 6, 1, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(42, 50, 1, 3, 0, 0, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);


    // --------------------  Building8 --------------------
    drawSideBuildingTop(31.0f, 80.0f, 35.0f, 83.0f, 82.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingSide(32.0f, 50.0f, 36.0f, 81.0f, 80.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingTop(20.0f, 80.0f, 31.0f, 82.0f, 0.4f, 0.6f, 0.8f, 0.2f, 0.2f, 0.2f);
    drawBuilding(18.0f, 50.0f, 32.0f, 80.0f, 0.3f, 0.5f, 0.7f, 0.2f, 0.2f, 0.2f);
    drawWindowGrid(20, 54, 6, 3, 2, 2, 0.75f, 0.9f, 1.0f, 0.1f, 0.1f, 0.1f);
    drawSideWindowGrid(33, 54, 6, 1, 2, 2, 0.75f, 0.9f, 1.0f, 0.1f, 0.1f, 0.1f);
    drawDoorGrid(22, 50, 1, 3, 0, 0, 0.25f, 0.2f, 0.15f, 0.1f, 0.1f, 0.1f);

    // --------------------  Building6 --------------------

    drawSideBuildingTop(59.0f, 70.0f, 65.0f, 74.0f, 73.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(60.0f, 50.0f, 66.0f, 71.0f, 70.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(51.0f, 70.0f, 59.0f, 73.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawBuilding(50.0f, 50.0f, 60.0f, 70.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(52, 58, 3, 2, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawSideWindowGrid(62, 54, 4, 1, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(53, 50, 2, 2, 0, 0, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);


    // --------------------  Building5 --------------------

    drawBuildingSide(75.0f, 50.0f, 80.0f, 70.0f, 67.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuilding(67.0f, 50.0f, 75.0f, 67.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(69, 54, 3, 2, 1.5, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    glColor3f(0.506f, 0.322f, 0.235f); // Window color
    glBegin(GL_POLYGON);
    glVertex2i(67, 67);
    glVertex2i(75, 67);
    glVertex2i(80, 70);
    glVertex2i(72, 70);
    glEnd();

    drawTree(10.0f, 50.0f, 11.0f, 63.0f); // Original tree
    drawTree(38.0f, 50.0f, 39.0f, 60.0f); // 2nd tree
    drawTree(45.0f, 50.0f);               // 3rd tree
    drawTree(83.0f, 50.0f);               // 4th tree
    drawTree(89.0f, 50.0f);               // 4th tree

    drawTrain(trainX);   // Right-to-left ট্রেন
//    drawTrain2(trainX2); // Left-to-right ট্রেন
    drawBoat(boatX, 5.0f);
    drawMiniCar();
    drawTruck();
    drawTaxi();
    drawMegendaBus();
//    drawPlane();
    drawPlane2(75.0f);

    glutSwapBuffers();
}

//Animation Function ID: ANM10
void drawNightScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    drawBorder();
    drawRiver(0.376f, 0.553f, 0.769f);
    drawSky(0.05f, 0.05f, 0.2f);
    drawRailPath();
    drawStars();
    drawCrescentMoon(80.0f, 85.0f, 3.0f);
    // Dark grayish-blue clouds
    drawCloud(cloudX1, 80.0f, 1.0f, 0.3f, 0.3f, 0.4f);
    drawCloud(cloudX2, 85.0f, 1.2f, 0.35f, 0.35f, 0.45f);
    drawCloud(cloudX3, 78.0f, 0.9f, 0.25f, 0.25f, 0.35f);

     // --------------------  Building3 --------------------

    drawSideBuildingTop(91.0f, 80.0f, 95.0f, 83.0f, 82.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingSide(92.0f, 50.0f, 96.0f, 81.0f, 80.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingTop(80.0f, 80.0f, 91.0f, 82.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawBuilding(78.0f, 50.0f, 92.0f, 80.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawWindowGrid(80, 54, 6, 3, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(93, 54, 6, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(82, 50, 1, 3, 0, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);


    // --------------------  Building1 --------------------
    drawBuildingSide(94.0f, 50.0f, 96.0f, 71.0f, 70.0f, 0.463f, 0.286f, 0.216f, 0.506f, 0.322f, 0.235f);
    drawBuilding(90.0f, 50.0f, 94.0f, 70.0f, 0.737f, 0.435f, 0.294f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(91, 55, 4, 1, 0, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(91, 50, 1, 1, 1, 2, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // --------------------  Building2 --------------------

    drawBuilding(96.0f, 50.0f, 100.0f, 75.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(97, 55, 5, 1, 0, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(97, 50, 1, 1, 1, 2, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);



    // -------------------- Hotel Building4 --------------------

    drawBuilding(65.0f, 50.0f, 81.0f, 85.0f, 0.75f, 0.65f, 0.55f, 0.45f, 0.35f, 0.25f);
    drawWindowGrid(66, 58, 6, 5, 1, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(74, 50, 2, 1, 0, 1, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // -------------------- Skyscraper Building9 --------------------

    drawSideBuildingTop(16.0f, 140.0f, 20.0f, 144.0f, 143.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingSide(17.0f, 50.0f, 21.0f, 142.0f, 140.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingTop(0.0f, 140.0f, 16.0f, 143.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawBuilding(-2.0f, 50.0f, 17.0f, 140.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawWindowGrid(1, 55, 11, 4, 2, 3, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(18, 55, 11, 1, 2, 3, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(5, 50, 1, 2, 3, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // --------------------  Building7 --------------------

    drawSideBuildingTop(51.0f, 80.0f, 55.0f, 83.0f, 82.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(52.0f, 50.0f, 56.0f, 81.0f, 80.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(40.0f, 80.0f, 51.0f, 82.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawBuilding(38.0f, 50.0f, 52.0f, 80.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(40, 54, 6, 3, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(53, 54, 6, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(42, 50, 1, 3, 0, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);


    // --------------------  Building8 --------------------
    drawSideBuildingTop(31.0f, 80.0f, 35.0f, 83.0f, 82.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingSide(32.0f, 50.0f, 36.0f, 81.0f, 80.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingTop(20.0f, 80.0f, 31.0f, 82.0f, 0.4f, 0.6f, 0.8f, 0.2f, 0.2f, 0.2f);
    drawBuilding(18.0f, 50.0f, 32.0f, 80.0f, 0.3f, 0.5f, 0.7f, 0.2f, 0.2f, 0.2f);
    drawWindowGrid(20, 54, 6, 3, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(33, 54, 6, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(22, 50, 1, 3, 0, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // --------------------  Building6 --------------------

    drawSideBuildingTop(59.0f, 70.0f, 65.0f, 74.0f, 73.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(60.0f, 50.0f, 66.0f, 71.0f, 70.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(51.0f, 70.0f, 59.0f, 73.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawBuilding(50.0f, 50.0f, 60.0f, 70.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(52, 58, 3, 2, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(62, 54, 4, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(53, 50, 2, 2, 0, 0, 1.0f, 0.9f, 0.6f, 1.0f, 0.9f, 0.6f);

    // --------------------  Building5 --------------------

    drawBuildingSide(75.0f, 50.0f, 80.0f, 70.0f, 67.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuilding(67.0f, 50.0f, 75.0f, 67.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(69, 54, 3, 2, 1.5f, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);

    glColor3f(0.506f, 0.322f, 0.235f); // Window color
    glBegin(GL_POLYGON);
    glVertex2i(67, 67);
    glVertex2i(75, 67);
    glVertex2i(80, 70);
    glVertex2i(72, 70);
    glEnd();

    drawTree(10.0f, 50.0f, 11.0f, 63.0f); // Original tree
    drawTree(38.0f, 50.0f, 39.0f, 60.0f); // 2nd tree
    drawTree(45.0f, 50.0f);               // 3rd tree
    drawTree(83.0f, 50.0f);               // 4th tree
    drawTree(89.0f, 50.0f);               // 4th tree

    drawTrain(trainX);
//    drawTrain2(trainX2);
    drawBoat(boatX, 5.0f);
    drawMiniCar();
    drawTruck();
    drawTaxi();
    drawMegendaBus();
    drawPlane2(75.0f);

    glutSwapBuffers();
}

//Animation Function ID: ANM11
void drawDayRainScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    drawBorder();
    drawRiver(0.682f, 0.863f, 0.949f);
    drawSky(0.6f, 0.7f, 0.75f);
    drawRailPath();
    drawCloud(cloudX1, 85.0f, 1.0f, 0.4f, 0.4f, 0.4f);
    drawCloud(cloudX2, 90.0f, 1.2f, 0.65f, 0.65f, 0.65);
    drawCloud(cloudX3, 88.0f, 0.8f, 0.2f, 0.2f, 0.2f);
    drawCloud(10, 77.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    drawCloud(70, 75.0f, 0.9f, 0.25f, 0.25f, 0.35f);

        // --------------------  Building3 --------------------

    drawSideBuildingTop(91.0f, 80.0f, 95.0f, 83.0f, 82.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingSide(92.0f, 50.0f, 96.0f, 81.0f, 80.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingTop(80.0f, 80.0f, 91.0f, 82.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawBuilding(78.0f, 50.0f, 92.0f, 80.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawWindowGrid(80, 54, 6, 3, 2, 2, 0.2f, 0.3f, 0.4f, 0.2f, 0.3f, 0.4f);
    drawSideWindowGrid(93, 54, 6, 1, 2, 2, 0.2f, 0.3f, 0.4f, 0.2f, 0.3f, 0.4f);
    drawDoorGrid(82, 50, 1, 3, 0, 0, 0.2f, 0.3f, 0.4f, 0.2f, 0.3f, 0.4f);

    // --------------------  Building1 --------------------
    drawBuildingSide(94.0f, 50.0f, 96.0f, 71.0f, 70.0f, 0.463f, 0.286f, 0.216f, 0.506f, 0.322f, 0.235f);
    drawBuilding(90.0f, 50.0f, 94.0f, 70.0f, 0.737f, 0.435f, 0.294f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(91, 55, 4, 1, 0, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(91, 50, 1, 1, 1, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);

    // --------------------  Building2 --------------------

    drawBuilding(96.0f, 50.0f, 100.0f, 75.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(97, 55, 5, 1, 0, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(97, 50, 1, 1, 1, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);

    // -------------------- Hotel Building4 --------------------

    drawBuilding(65.0f, 50.0f, 81.0f, 85.0f, 0.75f, 0.65f, 0.55f, 0.45f, 0.35f, 0.25f);
    drawWindowGrid(66 + 0, 58, 6, 5, 1, 2, 0.45f, 0.35f, 0.25f, 0.55f, 0.45f, 0.35f);  // Added one more column (5 windows wide)
    drawDoorGrid(74, 50, 2, 1, 0, 1, 0.3f, 0.25f, 0.2f, 0.4f, 0.35f, 0.3f);  // Shifted door 4 units right from 70 to 74

    // -------------------- Skyscraper Building9 --------------------

    drawSideBuildingTop(16.0f, 140.0f, 20.0f, 144.0f, 143.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingSide(17.0f, 50.0f, 21.0f, 142.0f, 140.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingTop(0.0f, 140.0f, 16.0f, 143.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawBuilding(-2.0f, 50.0f, 17.0f, 140.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawWindowGrid(1, 55, 11, 4, 2, 3, 0.75f, 0.9f, 1.0f, 0.15f, 0.15f, 0.15f);
    drawSideWindowGrid(18, 55, 11, 1, 2, 3, 0.75f, 0.9f, 1.0f, 0.15f, 0.15f, 0.15f);
    drawDoorGrid(5, 50, 1, 2, 3, 0, 0.25f, 0.2f, 0.15f, 0.1f, 0.1f, 0.1f);

    // --------------------  Building7 --------------------

    drawSideBuildingTop(51.0f, 80.0f, 55.0f, 83.0f, 82.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(52.0f, 50.0f, 56.0f, 81.0f, 80.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(40.0f, 80.0f, 51.0f, 82.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawBuilding(38.0f, 50.0f, 52.0f, 80.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(40, 54, 6, 3, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawSideWindowGrid(53, 54, 6, 1, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(42, 50, 1, 3, 0, 0, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);


    // --------------------  Building8 --------------------
    drawSideBuildingTop(31.0f, 80.0f, 35.0f, 83.0f, 82.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingSide(32.0f, 50.0f, 36.0f, 81.0f, 80.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingTop(20.0f, 80.0f, 31.0f, 82.0f, 0.4f, 0.6f, 0.8f, 0.2f, 0.2f, 0.2f);
    drawBuilding(18.0f, 50.0f, 32.0f, 80.0f, 0.3f, 0.5f, 0.7f, 0.2f, 0.2f, 0.2f);
    drawWindowGrid(20, 54, 6, 3, 2, 2, 0.75f, 0.9f, 1.0f, 0.1f, 0.1f, 0.1f);
    drawSideWindowGrid(33, 54, 6, 1, 2, 2, 0.75f, 0.9f, 1.0f, 0.1f, 0.1f, 0.1f);
    drawDoorGrid(22, 50, 1, 3, 0, 0, 0.25f, 0.2f, 0.15f, 0.1f, 0.1f, 0.1f);

    // --------------------  Building6 --------------------

    drawSideBuildingTop(59.0f, 70.0f, 65.0f, 74.0f, 73.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(60.0f, 50.0f, 66.0f, 71.0f, 70.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(51.0f, 70.0f, 59.0f, 73.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawBuilding(50.0f, 50.0f, 60.0f, 70.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(52, 58, 3, 2, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawSideWindowGrid(62, 54, 4, 1, 2, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);
    drawDoorGrid(53, 50, 2, 2, 0, 0, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);


    // --------------------  Building5 --------------------

    drawBuildingSide(75.0f, 50.0f, 80.0f, 70.0f, 67.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuilding(67.0f, 50.0f, 75.0f, 67.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(69, 54, 3, 2, 1.5, 2, 0.506f, 0.322f, 0.235f, 0.506f, 0.322f, 0.235f);

    glColor3f(0.506f, 0.322f, 0.235f); // Window color
    glBegin(GL_POLYGON);
    glVertex2i(67, 67);
    glVertex2i(75, 67);
    glVertex2i(80, 70);
    glVertex2i(72, 70);
    glEnd();

    drawTree(10.0f, 50.0f, 11.0f, 63.0f); // Original tree
    drawTree(38.0f, 50.0f, 39.0f, 60.0f); // 2nd tree
    drawTree(45.0f, 50.0f);               // 3rd tree
    drawTree(83.0f, 50.0f);               // 4th tree
    drawTree(89.0f, 50.0f);               // 4th tree


    drawRain();
    drawSplashes();
    drawLightningFlash();
    drawLightningFlash2();

    drawTrain(trainX);
    drawMiniCar();
    drawTruck();
    drawTaxi();
    drawMegendaBus();
    drawBoat(boatX, 5.0f);


    glutSwapBuffers();
}

//Animation Function ID: ANM12
void drawNightRainScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    drawBorder();
    drawRiver(0.376f, 0.553f, 0.769f);
    drawSky(0.05f, 0.05f, 0.2f);
    drawRailPath();
    // Dark grayish-blue clouds
    drawCloud(cloudX1, 80.0f, 1.0f, 0.3f, 0.3f, 0.4f);
    drawCloud(cloudX2, 85.0f, 1.2f, 0.35f, 0.35f, 0.45f);
    drawCloud(cloudX3, 78.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    drawCloud(60, 70.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    drawCloud(20, 80.0f, 0.9f, 0.25f, 0.25f, 0.35f);

     // --------------------  Building3 --------------------

    drawSideBuildingTop(91.0f, 80.0f, 95.0f, 83.0f, 82.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingSide(92.0f, 50.0f, 96.0f, 81.0f, 80.0f, 0.4f, 0.5f, 0.6f, 0.2f, 0.3f, 0.4f);
    drawBuildingTop(80.0f, 80.0f, 91.0f, 82.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawBuilding(78.0f, 50.0f, 92.0f, 80.0f, 0.5f, 0.6f, 0.7f, 0.2f, 0.3f, 0.4f);
    drawWindowGrid(80, 54, 6, 3, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(93, 54, 6, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(82, 50, 1, 3, 0, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);


    // --------------------  Building1 --------------------
    drawBuildingSide(94.0f, 50.0f, 96.0f, 71.0f, 70.0f, 0.463f, 0.286f, 0.216f, 0.506f, 0.322f, 0.235f);
    drawBuilding(90.0f, 50.0f, 94.0f, 70.0f, 0.737f, 0.435f, 0.294f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(91, 55, 4, 1, 0, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(91, 50, 1, 1, 1, 2, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // --------------------  Building2 --------------------

    drawBuilding(96.0f, 50.0f, 100.0f, 75.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(97, 55, 5, 1, 0, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(97, 50, 1, 1, 1, 2, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // -------------------- Hotel Building4 --------------------

    drawBuilding(65.0f, 50.0f, 81.0f, 85.0f, 0.75f, 0.65f, 0.55f, 0.45f, 0.35f, 0.25f);
    drawWindowGrid(66, 58, 6, 5, 1, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(74, 50, 2, 1, 0, 1, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // -------------------- Skyscraper Building9 --------------------

    drawSideBuildingTop(16.0f, 140.0f, 20.0f, 144.0f, 143.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingSide(17.0f, 50.0f, 21.0f, 142.0f, 140.0f, 0.18f, 0.3f, 0.45f, 0.1f, 0.1f, 0.1f);
    drawBuildingTop(0.0f, 140.0f, 16.0f, 143.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawBuilding(-2.0f, 50.0f, 17.0f, 140.0f, 0.22f, 0.4f, 0.6f, 0.1f, 0.1f, 0.1f);
    drawWindowGrid(1, 55, 11, 4, 2, 3, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(18, 55, 11, 1, 2, 3, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(5, 50, 1, 2, 3, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // --------------------  Building7 --------------------

    drawSideBuildingTop(51.0f, 80.0f, 55.0f, 83.0f, 82.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(52.0f, 50.0f, 56.0f, 81.0f, 80.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(40.0f, 80.0f, 51.0f, 82.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawBuilding(38.0f, 50.0f, 52.0f, 80.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(40, 54, 6, 3, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(53, 54, 6, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(42, 50, 1, 3, 0, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);


    // --------------------  Building8 --------------------
    drawSideBuildingTop(31.0f, 80.0f, 35.0f, 83.0f, 82.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingSide(32.0f, 50.0f, 36.0f, 81.0f, 80.0f, 0.2f, 0.4f, 0.6f, 0.2f, 0.2f, 0.2f);
    drawBuildingTop(20.0f, 80.0f, 31.0f, 82.0f, 0.4f, 0.6f, 0.8f, 0.2f, 0.2f, 0.2f);
    drawBuilding(18.0f, 50.0f, 32.0f, 80.0f, 0.3f, 0.5f, 0.7f, 0.2f, 0.2f, 0.2f);
    drawWindowGrid(20, 54, 6, 3, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(33, 54, 6, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(22, 50, 1, 3, 0, 0, 1.0f, 0.9f, 0.6f, 0.8f, 0.7f, 0.2f);

    // --------------------  Building6 --------------------

    drawSideBuildingTop(59.0f, 70.0f, 65.0f, 74.0f, 73.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingSide(60.0f, 50.0f, 66.0f, 71.0f, 70.0f, 0.361f, 0.275f, 0.224f, 0.506f, 0.322f, 0.235f);
    drawBuildingTop(51.0f, 70.0f, 59.0f, 73.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawBuilding(50.0f, 50.0f, 60.0f, 70.0f, 0.596f, 0.388f, 0.275f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(52, 58, 3, 2, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawSideWindowGrid(62, 54, 4, 1, 2, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);
    drawDoorGrid(53, 50, 2, 2, 0, 0, 1.0f, 0.9f, 0.6f, 1.0f, 0.9f, 0.6f);

    // --------------------  Building5 --------------------

    drawBuildingSide(75.0f, 50.0f, 80.0f, 70.0f, 67.0f, 0.624f, 0.439f, 0.302f, 0.506f, 0.322f, 0.235f);
    drawBuilding(67.0f, 50.0f, 75.0f, 67.0f, 0.839f, 0.600f, 0.388f, 0.506f, 0.322f, 0.235f);
    drawWindowGrid(69, 54, 3, 2, 1.5f, 2, 1.0f, 1.0f, 0.6f, 0.8f, 0.8f, 0.2f);

    glColor3f(0.506f, 0.322f, 0.235f); // Window color
    glBegin(GL_POLYGON);
    glVertex2i(67, 67);
    glVertex2i(75, 67);
    glVertex2i(80, 70);
    glVertex2i(72, 70);
    glEnd();

    drawTree(10.0f, 50.0f, 11.0f, 63.0f); // Original tree
    drawTree(38.0f, 50.0f, 39.0f, 60.0f); // 2nd tree
    drawTree(45.0f, 50.0f);               // 3rd tree
    drawTree(83.0f, 50.0f);               // 4th tree
    drawTree(89.0f, 50.0f);               // 4th tree

    drawRain();
    drawSplashes();
    drawLightningFlash();
    drawLightningFlash2();

    drawBoat(boatX, 5.0f);
    drawTrain(trainX);

    drawMiniCar();
    drawTruck();
    drawTaxi();
    drawMegendaBus();
    drawPlane2(65);

    glutSwapBuffers();
}


// ================= Start Mahfuzur =================

//for boat
float boatX_A = 0.0f;
bool movingRight_A = true; // Direction flag
bool boatMoving = true;

float tree1_X_A = 0.0;
float treeSpeed1_A = 0.01f; // First car speed
bool moveTreeRight_A = true;




void DownGround() {
    glColor3f(0.12f, 0.55f, 0.43f); //backgren
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(0.0f, 55.0f);
    glEnd();
}

void UpperSky(float r, float g, float b) {
    glColor3f(r, g, b);

    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 80.0f);
    glVertex2f(0.0f, 80.0f);
    glEnd();
}

void LTree1() {

    // Draw tree trunk (brown rectangle)
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(3.0f, 0.0f);
    glVertex2f(5.0f, 0.0f);
    glVertex2f(5.0f, 40.0f);
    glVertex2f(3.0f, 40.0f);
    glEnd();
    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(4.0f, 0.0f);
    glVertex2f(5.0f, 0.0f);
    glVertex2f(5.0f, 40.0f);
    glVertex2f(4.0f, 40.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(tree1_X_A, 0.0f, 0.0f); // Move car onto road (Y=26.0f is road level)

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 40.0f);
    glVertex2f(4.0f, 38.0f);
    glVertex2f(19.0f, 40.0f);
    glVertex2f(14.0f, 50.0f);
    glVertex2f(0.0f, 50.0f);
    glVertex2f(-3.0f, 45.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 50.0f);
    glVertex2f(4.0f, 48.0f);
    glVertex2f(14.5f, 50.0f);
    glVertex2f(10.0f, 60.0f);
    glVertex2f(1.5f, 60.0f);
    glVertex2f(0.0f, 57.0f);
    glVertex2f(-2.0f, 53.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);// lldGreen
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 60.0f);
    glVertex2f(4.0f, 58.0f);
    glVertex2f(10.5f, 60.0f);
    glVertex2f(4.0f, 70.0f);
    glVertex2f(0.0f, 60.0f);
    glEnd();

    glPopMatrix();

}

void LTree2() {

    // Draw tree trunk (brown rectangle)
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(15.0f, 30.0f);
    glVertex2f(17.0f, 30.0f);
    glVertex2f(17.0f, 55.0f);
    glVertex2f(15.0f, 55.0f);
    glEnd();
    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(16.0f, 30.0f);
    glVertex2f(17.0f, 30.0f);
    glVertex2f(17.0f, 55.0f);
    glVertex2f(16.0f, 55.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(tree1_X_A, 0.0f, 0.0f); // Move car onto road (Y=26.0f is road level)

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(8.0f, 55.0f);
    glVertex2f(16.0f, 50.0f);
    glVertex2f(27.0f, 55.0f);
    glVertex2f(23.0f, 64.0f);
    glVertex2f(11.0f, 64.0f);
    glVertex2f(8.0f, 55.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(10.0f, 64.0f);
    glVertex2f(16.0f, 62.0f);
    glVertex2f(24.5f, 64.0f);
    glVertex2f(20.0f, 70.0f);
    glVertex2f(14.0f, 70.0f);
    glVertex2f(10.0f, 64.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);// lldGreen
    glBegin(GL_POLYGON);
    glVertex2f(12.0f, 70.0f);
    glVertex2f(16.0f, 68.0f);
    glVertex2f(21.0f, 70.0f);
    glVertex2f(16.0f, 75.0f);
    glVertex2f(12.0f, 70.0f);
    glEnd();

    glPopMatrix();

}

void LTree3() {

    // Draw tree trunk (brown rectangle)
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(25.0f, 43.0f);
    glVertex2f(25.0f, 60.0f);
    glVertex2f(24.0f, 60.0f);
    glEnd();
    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(24.5f, 43.0f);
    glVertex2f(25.0f, 43.0f);
    glVertex2f(25.0f, 60.0f);
    glVertex2f(24.5f, 60.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(tree1_X_A, 0.0f, 0.0f); // Move car onto road (Y=26.0f is road level)
    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 60.0f);
    glVertex2f(24.5f, 58.0f);
    glVertex2f(32.0f, 60.0f);
    glVertex2f(29.0f, 65.0f);
    glVertex2f(20.0f, 65.0f);
    glVertex2f(18.0f, 60.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(19.0f, 65.0f);
    glVertex2f(24.5f, 63.0f);
    glVertex2f(30.0f, 65.0f);
    glVertex2f(27.0f, 70.0f);
    glVertex2f(22.0f, 70.0f);
    glVertex2f(19.0f, 65.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);// lldGreen
    glBegin(GL_POLYGON);
    glVertex2f(21.0f, 70.0f);
    glVertex2f(24.5f, 68.0f);
    glVertex2f(28.0f, 70.0f);
    glVertex2f(24.5f, 75.0f);
    glVertex2f(21.0f, 70.0f);
    glEnd();

    glPopMatrix();
    //TRUNKS1
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(20.0f, 42.0f);
    glVertex2f(21.0f, 42.0f);
    glVertex2f(21.0f, 55.0f);
    glVertex2f(20.0f, 55.0f);
    glEnd();
    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(20.5f, 42.0f);
    glVertex2f(21.0f, 42.0f);
    glVertex2f(21.0f, 55.0f);
    glVertex2f(20.5f, 55.0f);
    glEnd();
    //backtree

    glPushMatrix();
    glTranslatef(tree1_X_A, 0.0f, 0.0f); // Move car onto road (Y=26.0f is road level)
    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(3.0f, 65.0f);
    glVertex2f(9.0f, 60.0f);
    glVertex2f(15.0f, 65.0f);
    glVertex2f(12.0f, 67.0f);
    glVertex2f(5.0f, 67.0f);
    glVertex2f(3.0f, 65.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(4.0f, 67.0f);
    glVertex2f(9.0f, 66.0f);
    glVertex2f(13.0f, 67.0f);
    glVertex2f(11.0f, 71.0f);
    glVertex2f(6.0f, 71.0f);
    glVertex2f(4.0f, 67.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);// lldGreen
    glBegin(GL_POLYGON);
    glVertex2f(5.0f, 71.0f);
    glVertex2f(9.0f, 70.0f);
    glVertex2f(12.5f, 71.0f);
    glVertex2f(9.0f, 75.0f);
    glVertex2f(5.0f, 71.0f);
    glEnd();

    glPopMatrix();

}

//bush_A
void Bush_A() {
    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(11.0f, 0.0f);
    glVertex2f(17.0f, 7.0f);
    glVertex2f(13.0f, 5.0f);
    glVertex2f(15.0f, 10.0f);
    glVertex2f(9.0f, 8.0f);
    glVertex2f(12.0f, 13.0f);
    glVertex2f(8.0f, 11.0f);
    glVertex2f(6.0f, 18.0f);
    glVertex2f(2.0f, 10.0f);
    glVertex2f(0.0f, 13.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();
    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(11.0f, 0.0f);
    glVertex2f(15.0f, 5.0f);
    glVertex2f(10.0f, 3.0f);
    glVertex2f(11.0f, 8.0f);
    glVertex2f(7.0f, 5.0f);
    glVertex2f(6.0f, 16.0f);
    glVertex2f(2.0f, 5.0f);
    glVertex2f(1.0f, 10.0f);
    glVertex2f(0.0f, 8.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    //bush_A2
    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(12.0f, 30.0f);
    glVertex2f(20.0f, 30.0f);
    glVertex2f(21.0f, 35.0f);
    glVertex2f(19.0f, 33.0f);
    glVertex2f(19.0f, 38.0f);
    glVertex2f(16.0f, 33.0f);
    glVertex2f(14.0f, 37.0f);
    glVertex2f(13.0f, 33.0f);
    glVertex2f(11.0f, 36.0f);
    glVertex2f(12.0f, 30.0f);

    glEnd();
    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(12.0f, 30.0f);
    glVertex2f(20.0f, 30.0f);
    glVertex2f(21.0f, 33.0f);
    glVertex2f(19.0f, 32.0f);
    glVertex2f(20.0f, 35.0f);
    glVertex2f(17.0f, 32.0f);
    glVertex2f(16.0f, 37.0f);
    glVertex2f(15.0f, 33.0f);
    glVertex2f(12.0f, 36.0f);
    glVertex2f(13.0f, 32.0f);
    glVertex2f(10.0f, 34.0f);
    glVertex2f(12.0f, 30.0f);
    glEnd();
    //bush_A3
    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(20.0f, 42.0f);
    glVertex2f(21.0f, 42.0f);
    glVertex2f(23.0f, 45.0f);
    glVertex2f(21.0f, 44.0f);
    glVertex2f(20.5f, 47.0f);
    glVertex2f(20.0f, 44.0f);
    glVertex2f(18.0f, 45.0f);
    glVertex2f(20.0f, 42.0f);
    glEnd();

    //bush_A4r
    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(90.0f, 50.0f);
    glVertex2f(93.0f, 50.0f);
    glVertex2f(94.0f, 52.0f);
    glVertex2f(92.0f, 51.0f);
    glVertex2f(91.5f, 53.0f);
    glVertex2f(91.0f, 51.0f);
    glVertex2f(89.0f, 52.0f);
    glVertex2f(90.0f, 50.0f);
    glEnd();

    //bush_A5r
    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 40.0f);
    glVertex2f(90.0f, 40.0f);
    glVertex2f(90.0f, 44.0f);
    glVertex2f(87.0f, 40.0f);
    glVertex2f(86.5f, 44.0f);
    glVertex2f(85.0f, 40.0f);
    glEnd();

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 40.0f);
    glVertex2f(90.0f, 40.0f);
    glVertex2f(92.0f, 44.0f);
    glVertex2f(89.0f, 42.0f);
    glVertex2f(88.0f, 45.0f);
    glVertex2f(87.0f, 42.0f);
    glVertex2f(83.0f, 44.0f);
    glVertex2f(85.0f, 40.0f);
    glEnd();

    //bush_A6r
    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(88.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(100.0f, 10.0f);
    glVertex2f(99.0f, 11.0f);
    glVertex2f(96.0f, 8.0f);
    glVertex2f(94.0f, 12.0f);
    glVertex2f(90.0f, 5.0f);
    glVertex2f(86.0f, 6.0f);
    glVertex2f(88.0f, 0.0f);
    glEnd();

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(90.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(100.0f, 5.0f);
    glVertex2f(98.0f, 8.0f);
    glVertex2f(95.0f, 4.0f);
    glVertex2f(93.0f, 10.0f);
    glVertex2f(90.0f, 4.0f);
    glVertex2f(85.0f, 5.0f);
    glVertex2f(90.0f, 0.0f);
    glEnd();
}

//Mountain
void Mountain() {
    glColor3f(0.18f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(30.0f, 55.0f);
    glVertex2f(30.0f, 60.0f);
    glVertex2f(0.0f, 60.0f);
    glEnd();
    glColor3f(0.09f, 0.14f, 0.20f);
    glBegin(GL_POLYGON);
    glVertex2f(22.0f, 55.0f);
    glVertex2f(44.0f, 55.0f);
    glVertex2f(33.5f, 65.0f);
    glVertex2f(22.0f, 55.0f);
    glEnd();
    glColor3f(0.18f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(30.0f, 55.0f);
    glVertex2f(50.0f, 55.0f);
    glVertex2f(40.0f, 63.0f);
    glVertex2f(30.0f, 55.0f);
    glEnd();

    glColor3f(0.18f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(80.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 60.0f);
    glVertex2f(80.0f, 60.0f);
    glEnd();
    glColor3f(0.18f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(65.0f, 55.0f);
    glVertex2f(85.0f, 55.0f);
    glVertex2f(75.0f, 66.0f);

    glEnd();
    glColor3f(0.09f, 0.14f, 0.20f);
    glBegin(GL_POLYGON);
    glVertex2f(59.0f, 55.0f);
    glVertex2f(81.0f, 55.0f);
    glVertex2f(70.0f, 65.0f);
    glVertex2f(59.0f, 55.0f);
    glEnd();
    glColor3f(0.18f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(45.0f, 55.0f);
    glVertex2f(68.0f, 55.0f);
    glVertex2f(55.0f, 69.0f);
    glVertex2f(45.0f, 55.0f);
    glEnd();

    glColor3f(0.32f, 0.44f, 0.52f);
    glBegin(GL_POLYGON);
    glVertex2f(35.0f, 55.0f);
    glVertex2f(65.0f, 55.0f);
    glVertex2f(50.0f, 70.0f);
    glVertex2f(35.0f, 55.0f);
    glEnd();

}

void RTree3() {

    // Draw tree trunk (brown rectangle)
    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(81.0f, 49.0f);
    glVertex2f(82.0f, 49.0f);
    glVertex2f(82.0f, 60.0f);
    glVertex2f(81.0f, 60.0f);
    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(81.5f, 49.0f);
    glVertex2f(82.0f, 49.0f);
    glVertex2f(82.0f, 60.0f);
    glVertex2f(81.5f, 60.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(tree1_X_A, 0.0f, 0.0f); //

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(75.0f, 59.0f);
    glVertex2f(81.5f, 56.0f);
    glVertex2f(86.0f, 59.0f);
    glVertex2f(84.0f, 65.0f);
    glVertex2f(79.0f, 65.0f);
    glVertex2f(75.0f, 59.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(77.0f, 65.0f);
    glVertex2f(81.5f, 63.0f);
    glVertex2f(86.0f, 65.0f);
    glVertex2f(84.0f, 69.0f);
    glVertex2f(80.0f, 69.0f);
    glVertex2f(77.0f, 65.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);// lldGreen
    glBegin(GL_POLYGON);
    glVertex2f(78.0f, 69.0f);
    glVertex2f(81.5f, 68.0f);
    glVertex2f(85.0f, 69.0f);
    glVertex2f(81.5f, 73.0f);
    glVertex2f(78.0f, 69.0f);
    glEnd();

    glPopMatrix();

    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(84.0f, 48.0f);
    glVertex2f(85.0f, 48.0f);
    glVertex2f(85.0f, 60.0f);
    glVertex2f(84.0f, 60.0f);
    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(84.5f, 48.0f);
    glVertex2f(85.0f, 48.0f);
    glVertex2f(85.0f, 60.0f);
    glVertex2f(84.5f, 60.0f);
    glEnd();

    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(91.0f, 50.0f);
    glVertex2f(92.0f, 50.0f);
    glVertex2f(92.0f, 60.0f);
    glVertex2f(91.0f, 60.0f);
    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(91.5f, 50.0f);
    glVertex2f(92.0f, 50.0f);
    glVertex2f(92.0f, 60.0f);
    glVertex2f(91.5f, 60.0f);
    glEnd();

}

void RTree2() {

    // Draw tree trunk (brown rectangle)
    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(87.0f, 42.0f);
    glVertex2f(89.0f, 42.0f);
    glVertex2f(89.0f, 60.0f);
    glVertex2f(87.0f, 60.0f);
    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(88.0f, 42.0f);
    glVertex2f(89.0f, 42.0f);
    glVertex2f(89.0f, 60.0f);
    glVertex2f(88.0f, 60.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(tree1_X_A, 0.0f, 0.0f); // Move car onto road (Y=26.0f is road level)

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(79.0f, 59.0f);
    glVertex2f(88.0f, 56.0f);
    glVertex2f(95.0f, 59.0f);
    glVertex2f(92.0f, 66.0f);
    glVertex2f(85.0f, 66.0f);
    glVertex2f(79.0f, 59.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(81.0f, 65.0f);
    glVertex2f(88.0f, 64.0f);
    glVertex2f(93.0f, 66.0f);
    glVertex2f(90.0f, 70.0f);
    glVertex2f(85.0f, 70.0f);
    glVertex2f(81.0f, 65.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);// lldGreen
    glBegin(GL_POLYGON);
    glVertex2f(84.0f, 70.0f);
    glVertex2f(88.0f, 69.0f);
    glVertex2f(92.0f, 70.0f);
    glVertex2f(88.0f, 75.0f);
    glVertex2f(84.0f, 70.0f);
    glEnd();

    glPopMatrix();

}

void RTree1() {

    // Draw tree trunk (brown rectangle)
    glColor3f(0.5137f, 0.3059f, 0.3059f); // lBrown
    glBegin(GL_QUADS);
    glVertex2f(95.0f, 36.0f);
    glVertex2f(97.0f, 36.0f);
    glVertex2f(97.0f, 60.0f);
    glVertex2f(95.0f, 60.0f);
    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(96.0f, 36.0f);
    glVertex2f(97.0f, 36.0f);
    glVertex2f(97.0f, 60.0f);
    glVertex2f(96.0f, 60.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(tree1_X_A, 0.0f, 0.0f); // Move car onto road (Y=26.0f is road level)

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 59.0f);
    glVertex2f(96.0f, 55.0f);
    glVertex2f(100.0f, 57.0f);
    glVertex2f(103.0f, 60.0f);
    glVertex2f(100.0f, 63.0f);
    glVertex2f(90.0f, 63.0f);
    glVertex2f(85.0f, 59.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);// ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(88.0f, 64.0f);
    glVertex2f(96.0f, 62.0f);
    glVertex2f(100.0f, 63.0f);
    glVertex2f(102.0f, 66.0f);
    glVertex2f(100.0f, 68.0f);
    glVertex2f(98.0f, 70.0f);
    glVertex2f(93.0f, 70.0f);
    glVertex2f(88.0f, 64.0f);

    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);// lldGreen
    glBegin(GL_POLYGON);
    glVertex2f(92.0f, 70.0f);
    glVertex2f(96.0f, 68.0f);
    glVertex2f(100.0f, 70.0f);
    glVertex2f(96.0f, 75.0f);
    glVertex2f(92.0f, 70.0f);
    glEnd();

    glPopMatrix();

}

void updatetree_A(int value) {
    // Update tree position based on direction
    if (moveTreeRight_A) {
        tree1_X_A += treeSpeed1_A;
        if (tree1_X_A >= 1.0) {
            moveTreeRight_A = false; // Change direction to left
        }
    }
    else {
        tree1_X_A -= treeSpeed1_A;
        if (tree1_X_A <= -1.0) {
            moveTreeRight_A = true; // Change direction to right
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updatetree_A, 0);
}

void Tent1_A(float r, float g, float b) {
    glColor3f(0.59f, 0.37f, 0.61f); // Tent body
    glBegin(GL_POLYGON);
        glVertex2f(18.0f, 12.5f);
        glVertex2f(19.0f, 14.5f);
        glVertex2f(20.0f, 16.5f);
        glVertex2f(21.0f, 18.5f);
        glVertex2f(22.0f, 20.5f);
        glVertex2f(23.0f, 22.5f);
        glVertex2f(24.0f, 24.5f);
        glVertex2f(25.0f, 26.5f);
        glVertex2f(26.0f, 27.5f);
        glVertex2f(27.0f, 28.0f);
        glVertex2f(28.0f, 28.5f); // top-center
        glVertex2f(29.0f, 28.0f);
        glVertex2f(30.0f, 27.5f);
        glVertex2f(31.0f, 26.5f);
        glVertex2f(32.0f, 24.5f);
        glVertex2f(33.0f, 22.5f);
        glVertex2f(34.0f, 20.5f);
        glVertex2f(35.0f, 18.5f);
        glVertex2f(36.0f, 16.5f);
        glVertex2f(37.0f, 14.5f);
        glVertex2f(38.0f, 12.5f);
    glEnd();

    // Door
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(28.0f, 23.0f); // top of door
        glVertex2f(25.0f, 12.5f); // bottom-left
        glVertex2f(31.0f, 12.5f); // bottom-right
    glEnd();

    // Ropes
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
        glVertex2f(18.0f, 12.5f);
        glVertex2f(15.0f, 9.5f);

        glVertex2f(38.0f, 12.5f);
        glVertex2f(41.0f, 9.5f);
    glEnd();

    // Stakes
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(15.0f, 9.5f);
        glVertex2f(41.0f, 9.5f);
    glEnd();
}

void Tent2_A(float r, float g, float b) {
    glColor3f(0.72f, 0.33f, 0.28f);
    glBegin(GL_TRIANGLES);
        glVertex2f(24.5f, 33.5f);
        glVertex2f(38.5f, 33.5f);
        glVertex2f(31.5f, 51.5f);
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(28.5f, 33.5f);
        glVertex2f(34.5f, 33.5f);
        glVertex2f(31.5f, 45.5f);
    glEnd();

    glColor3f(0.99f, 0.78f, 0.55f);
    glBegin(GL_TRIANGLES);
        glVertex2f(28.5f, 33.5f);
        glVertex2f(31.5f, 45.5f);
        glVertex2f(31.5f, 33.5f);
    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
        glVertex2f(24.5f, 33.5f);
        glVertex2f(22.5f, 31.5f);
        glVertex2f(38.5f, 33.5f);
        glVertex2f(40.5f, 31.5f);
    glEnd();

    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(22.5f, 31.5f);
        glVertex2f(40.5f, 31.5f);
    glEnd();
}

void Tent3_A(float r, float g, float b) {
    // Tent body (smaller A-frame)
    glColor3f(0.36f, 0.24f, 0.46f);
    glBegin(GL_TRIANGLES);
        glVertex2f(78.0f, 29.0f);  // top peak
        glVertex2f(70.0f, 14.0f);  // bottom-left
        glVertex2f(86.0f, 14.0f);  // bottom-right
    glEnd();

    // Tent back panel (depth)
    glColor3f(0.59f, 0.37f, 0.61f);
    glBegin(GL_TRIANGLES);
        glVertex2f(78.0f, 29.0f);  // top peak
        glVertex2f(86.0f, 14.0f);  // front bottom-right
        glVertex2f(90.0f, 17.0f);  // back-bottom-right
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(78.0f, 29.0f);  // top peak
        glVertex2f(70.0f, 14.0f);  // front bottom-left
        glVertex2f(66.0f, 17.0f);  // back-bottom-left
    glEnd();

    // Door (front)
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(78.0f, 24.0f);  // top of door
        glVertex2f(73.0f, 14.0f);  // bottom-left
        glVertex2f(83.0f, 14.0f);  // bottom-right
    glEnd();

    // Ropes
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
        // Left back rope
        glVertex2f(66.0f, 17.0f);
        glVertex2f(63.0f, 12.0f);  // left back stake

        // Right back rope
        glVertex2f(90.0f, 17.0f);
        glVertex2f(93.0f, 12.0f);  // right back stake

        // Left front rope
        glVertex2f(70.0f, 14.0f);
        glVertex2f(67.0f, 9.0f);  // left front stake

        // Right front rope
        glVertex2f(86.0f, 14.0f);
        glVertex2f(89.0f, 9.0f);  // right front stake
    glEnd();

    // Stakes
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(63.0f, 12.0f);  // left back stake
        glVertex2f(93.0f, 12.0f);  // right back stake
        glVertex2f(67.0f, 9.0f);   // left front stake
        glVertex2f(89.0f, 9.0f);   // right front stake
    glEnd();
}

void Tent4_A(float r, float g, float b) {
    glColor3f(0.2f, 0.5f, 0.8f);
    glBegin(GL_POLYGON);
        glVertex2f(72.0f, 32.0f); // bottom-left
        glVertex2f(80.0f, 44.0f); // top peak
        glVertex2f(88.0f, 32.0f); // bottom-right
    glEnd();

    glColor3f(0.6f, 0.8f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(80.0f, 44.0f); // top peak
        glVertex2f(88.0f, 32.0f); // front bottom-right
        glVertex2f(91.0f, 34.0f); // back bottom-right
        glVertex2f(83.0f, 46.0f); // back top
    glEnd();

    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
        glVertex2f(80.0f, 39.0f); // top of door
        glVertex2f(76.0f, 32.0f); // bottom-left
        glVertex2f(84.0f, 32.0f); // bottom-right
    glEnd();

    // Ropes
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
        // Left rope
        glVertex2f(72.0f, 32.0f);
        glVertex2f(69.0f, 29.0f);
        // Right rope
        glVertex2f(88.0f, 32.0f);
        glVertex2f(91.0f, 29.0f);
        // Side flap rope
        glVertex2f(91.0f, 34.0f);
        glVertex2f(93.0f, 32.0f);
    glEnd();

    // Stakes
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2f(69.0f, 29.0f); // left front stake
        glVertex2f(91.0f, 29.0f); // right front stake
        glVertex2f(93.0f, 32.0f); // back stake for flap
    glEnd();
}

void drawRiver_A() {
    glColor3f(0.20f, 0.41f, 0.64f);
    glBegin(GL_TRIANGLES);
    glVertex2f(35.0f, 55.0f);
    glVertex2f(60.0f, 53.0f);
    glVertex2f(65.0f, 55.0f);
    glEnd();

    glColor3f(0.20f, 0.41f, 0.64f);
    glBegin(GL_QUADS);
    glVertex2f(35.0f, 55.0f);
    glVertex2f(50.0f, 50.0f);
    glVertex2f(70.0f, 48.0f);
    glVertex2f(60.0f, 53.0f);
    glEnd();

    glColor3f(0.20f, 0.41f, 0.64f);
    glBegin(GL_QUADS);
    glVertex2f(50.0f, 50.0f);
    glVertex2f(35.0f, 45.0f);
    glVertex2f(55.0f, 44.0f);
    glVertex2f(70.0f, 48.0f);
    glEnd();

    glColor3f(0.20f, 0.41f, 0.64f);
    glBegin(GL_QUADS);
    glVertex2f(35.0f, 45.0f);
    glVertex2f(45.0f, 40.0f);
    glVertex2f(65.0f, 40.0f);
    glVertex2f(55.0f, 44.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);
    glBegin(GL_QUADS);
    glVertex2f(50.0f, 50.0f);
    glVertex2f(35.0f, 45.0f);
    glVertex2f(36.2f, 44.5f);
    glVertex2f(50.0f, 49.0f);

    glEnd();


    glColor3f(0.09f, 0.38f, 0.33f);
    glBegin(GL_QUADS);
    glVertex2f(60.0f, 53.0f);
    glVertex2f(60.0f, 52.0f);
    glVertex2f(68.6f, 47.5f);
    glVertex2f(70.0f, 48.0f);
    glEnd();

    glColor3f(0.09f, 0.38f, 0.33f);
    glBegin(GL_QUADS);
    glVertex2f(55.0f, 44.0f);
    glVertex2f(55.0f, 43.0f);
    glVertex2f(63.f, 40.0f);
    glVertex2f(65.0f, 40.0f);

    glEnd();

}

void river() {
    glColor3f(0.20f, 0.41f, 0.64f);
    glBegin(GL_QUADS);
    glVertex2f(45.0f, 0.0f);
    glVertex2f(70.0f, 0.0f);
    glVertex2f(50.0f, 15.0f);
    glVertex2f(40.0f, 5.0f);

    glEnd();
    glColor3f(0.09f, 0.38f, 0.33f);
    glBegin(GL_QUADS);
    glVertex2f(41.0f, 4.0f);
    glVertex2f(50.0f, 14.0f);
    glVertex2f(50.0f, 15.0f);
    glVertex2f(40.0f, 5.0f);

    glEnd();
    glColor3f(0.09f, 0.38f, 0.33f);
    glBegin(GL_QUADS);
    glVertex2f(50.0f, 14.0f);
    glVertex2f(69.0f, 0.0f);
    glVertex2f(70.0f, 0.0f);
    glVertex2f(50.0f, 15.0f);

    glEnd();

}

void Stone_A() {
    glColor3f(0.18f, 0.25f, 0.35f);

    glBegin(GL_POLYGON);
    glVertex2f(23.0f, 6.0f); // Center point
    glVertex2f(27.0f, 6.0f);
    glVertex2f(27.0f, 7.0f);
    glVertex2f(25.0f, 8.0f);
    glVertex2f(24.0f, 9.0f);
    glVertex2f(22.0f, 7.0f);

    glEnd();

    glColor3f(0.18f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(70.0f, 6.0f); // Center point
    glVertex2f(74.0f, 6.0f);
    glVertex2f(75.0f, 5.0f);
    glVertex2f(77.0f, 3.0f);
    glVertex2f(80.0f, 5.0f);
    glVertex2f(78.0f, 10.0f);
    glVertex2f(76.0f, 11.0f);
    glVertex2f(75.0f, 10.0f);
    glVertex2f(71.0f, 10.0f);
    glVertex2f(68.0f, 8.0f);
    glEnd();

    glColor3f(0.18f, 0.25f, 0.35f);
    glBegin(GL_POLYGON);
    glVertex2f(73.0f, 44.0f); // Center point
    glVertex2f(79.0f, 44.0f);
    glVertex2f(78.0f, 45.0f);
    glVertex2f(78.0f, 46.0f);
    glVertex2f(76.0f, 46.0f);
    glVertex2f(75.0f, 47.0f);
    glVertex2f(73.0f, 46.0f);

    glEnd();

}

void fire_Astick_A() {
    glColor3f(0.33f, 0.20f, 0.22f);

    glBegin(GL_POLYGON);
    glVertex2f(50.0f, 23.0f); // Center point
    glVertex2f(51.0f, 22.0f);
    glVertex2f(55.0f, 26.0f);
    glVertex2f(54.0f, 27.0f);

    glEnd();

    glColor3f(0.33f, 0.20f, 0.22f);

    glBegin(GL_POLYGON);
    glVertex2f(55.0f, 21.0f); // Center point
    glVertex2f(57.0f, 21.0f);
    glVertex2f(57.0f, 26.0f);
    glVertex2f(55.0f, 26.0f);

    glEnd();

    glColor3f(0.33f, 0.20f, 0.22f);

    glBegin(GL_POLYGON);
    glVertex2f(57.0f, 26.0f); // Center point
    glVertex2f(61.0f, 22.0f);
    glVertex2f(62.0f, 23.0f);
    glVertex2f(58.0f, 27.0f);

    glEnd();
}

void fire_A() {
    glColor3f(0.95f, 0.50f, 0.39f);

    glBegin(GL_POLYGON);
    glVertex2f(53.0f, 29.0f);
    glVertex2f(59.0f, 29.0f);
    glVertex2f(59.0f, 33.0f);
    glVertex2f(58.0f, 32.0f);
    glVertex2f(56.0f, 35.0f);
    glVertex2f(54.0f, 32.0f);
    glVertex2f(53.0f, 33.0f);

    glEnd();

    // Time-based left-right wobble using sine wave

    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // seconds
    float offsetX = sin(time * 5.0f) * 0.3f; // Adjust speed and distance

    glColor3f(0.97f, 0.73f, 0.43f);
    glBegin(GL_POLYGON);
    glVertex2f(54.0f + offsetX, 29.0f);
    glVertex2f(58.0f + offsetX, 29.0f);
    glVertex2f(58.0f + offsetX, 32.0f);
    glVertex2f(57.0f + offsetX, 30.0f);
    glVertex2f(56.0f + offsetX, 33.0f);
    glVertex2f(55.0f + offsetX, 30.0f);
    glVertex2f(54.0f + offsetX, 31.0f);
    glEnd();
}

void meat() {
    glColor3f(0.42f, 0.13f, 0.01f);

    glBegin(GL_QUADS);
    glVertex2f(53.0f, 36.0f);
    glVertex2f(60.0f, 36.0f);
    glVertex2f(60.0f, 38.0f);
    glVertex2f(53.0f, 38.0f);

    glEnd();

    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown

    glBegin(GL_QUADS);
    glVertex2f(47.0f, 22.0f);
    glVertex2f(48.0f, 22.0f);
    glVertex2f(48.0f, 38.0f);
    glVertex2f(47.0f, 38.0f);

    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown

    glBegin(GL_QUADS);
    glVertex2f(64.0f, 22.0f);
    glVertex2f(65.0f, 22.0f);
    glVertex2f(65.0f, 38.0f);
    glVertex2f(64.0f, 38.0f);
    glEnd();

}

void meatrope() {
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown

    glBegin(GL_QUADS);
    glVertex2f(48.0f, 36.75f);
    glVertex2f(53.0f, 36.75f);
    glVertex2f(53.0f, 37.0f);
    glVertex2f(48.0f, 37.0f);

    glEnd();

    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown

    glBegin(GL_QUADS);
    glVertex2f(61.0f, 36.75f);
    glVertex2f(64.0f, 36.75f);
    glVertex2f(64.0f, 37.0f);
    glVertex2f(61.0f, 37.0f);

    glEnd();

}

void boat() {

    glPushMatrix(); // Save current transformation state
    glTranslatef(boatX_A, 0.0f, 0.0f); // Move the boat along X-axis
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown

    glBegin(GL_QUADS);
    glVertex2f(53.0f, 49.0f);
    glVertex2f(57.0f, 49.0f);
    glVertex2f(57.0f, 50.0f);
    glVertex2f(53.0f, 50.0f);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);
    glVertex2f(53.0f, 50.0f);
    glVertex2f(57.0f, 50.0f);
    glVertex2f(55.0f, 54.0f);

    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown

    glBegin(GL_TRIANGLES);
    glVertex2f(53.0f, 49.0f);
    glVertex2f(53.0f, 50.0f);
    glVertex2f(51.0f, 51.0f);

    glEnd();
    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown

    glBegin(GL_TRIANGLES);
    glVertex2f(57.0f, 49.0f);
    glVertex2f(59.0f, 51.0f);
    glVertex2f(57.0f, 50.0f);

    glEnd();
    glPopMatrix(); // Restore previous state

}

float boatspeed_A = 0.02f;

void update(int value) {
    if (boatMoving) {
        if (movingRight_A) {
            boatX_A += boatspeed_A;
            if (boatX_A >= 8.0f) {
                movingRight_A = false;
            }
        }
        else {
            boatX_A -= boatspeed_A;
            if (boatX_A <= -4.0f) {
                movingRight_A = true;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void flowercut() {
    glColor3f(0.20f, 0.41f, 0.64f);
    glBegin(GL_TRIANGLES);
    glVertex2f(47.0f, 3.0f);
    glVertex2f(49.0f, 5.0f);
    glVertex2f(47.0f, 6.0f);

    glEnd();
    glColor3f(0.20f, 0.41f, 0.64f);
    glBegin(GL_TRIANGLES);
    glVertex2f(55.0f, 2.0f); // Center point
    glVertex2f(57.0f, 3.0f);
    glVertex2f(55.0f, 4.0f);

    glEnd();
}

void flower1(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(0.55f, 0.69f, 0.38f);


    drawCircle(x, y, radius, 100);
}

void flower2(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(0.55f, 0.69f, 0.38f);


    drawCircle(x, y, radius, 100);
}

void drawCrescentMoon_A(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(1.0f, 0.92f, 0.50f);

    drawCircle(x, y, radius, 100);
}


void drawCrescentMoon_A1(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(1.0f, 1.0f, 1.0f);


    drawCircle(x, y, radius, 100);
}

void fire_A1(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(0.95f, 0.50f, 0.39f);

    drawCircle(x, y, radius, 100);
}

void fire_A2(float x, float y, float radius) {
    // Animate wobble using sine wave
    float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f; // Time in seconds
    float offsetX = sin(time * 2.5f) * 0.3f; // Slower speed, small distance

    // Set color for fire_A glow
    glColor3f(0.97f, 0.73f, 0.43f);

    // Draw the moving circle
    drawCircle(x + offsetX, y, radius, 100);
}

void meat1(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(0.64f, 0.27f, 0.0f);

    drawCircle(x, y, radius, 100);
}

void meat2(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(0.42f, 0.13f, 0.01f);


    drawCircle(x, y, radius, 100);
}

void fire_Aflies() {
    glColor3f(0.98f, 0.87f, 0.27f);
    srand(10); // Fixed seed for consistent star positions

    for (int i = 0; i < 100; i++) {
        float x = rand() % 21;
        float y = 0 + rand() % 21;
        drawCircle(x, y, 0.1, 100);
    }
}

void drawScene_A() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    UpperSky(0.53f, 0.81f, 0.92f);

    DownGround();
    drawCrescentMoon_A(40.0f, 70.0f, 4.0f);
    drawCloud(cloudX1, 66.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    drawCloud(cloudX2, 70.0f, 1.2f, 0.95f, 0.95f, 0.95f);
    drawCloud(cloudX3, 68.0f, 0.8f, 0.9f, 0.9f, 0.9f);
    drawPlane2(65.0f);
    Mountain();
    RTree3();
    RTree2();
    RTree1();
    LTree3();
    LTree2();
    LTree1();
    Bush_A();
    Tent1_A(0.20f, 0.15f, 0.31f);
    Tent2_A(0.37f, 0.22f, 0.23f);
    Tent3_A(0.37f, 0.22f, 0.23f);
    Tent4_A(0.37f, 0.22f, 0.23f);

    drawRiver_A();
    river();
    boat();
    fire_Astick_A();
    fire_A1(56.0f, 29.0f, 3.0f);
    fire_A();
    fire_A2(56.0f, 28.0f, 2.0f);
    Stone_A();
    flower1(49.0f, 5.0f, 2.0f);
    flower2(57.0f, 3.0f, 2.0f);
    flowercut();
    meat();
    meat1(53.0f, 37.0f, 1.0f);
    meat2(60.0f, 37.0f, 1.0f);
    meatrope();
    // fire_Aflies();

    glutSwapBuffers();
}

void drawScene1_A() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    UpperSky(0.15f, 0.20f, 0.34f);
    drawStars();
    DownGround();
    drawCrescentMoon_A(40.0f, 70.0f, 4.0f);
    drawCrescentMoon_A1(40.0f, 70.0f, 3.5f);
    drawCloud(cloudX1, 66.0f, 1.0f, 0.3f, 0.3f, 0.4f);
    drawPlane2(65.0f);
    drawCloud(cloudX2, 70.0f, 1.2f, 0.35f, 0.35f, 0.45f);
    drawCloud(cloudX3, 75.0f, 0.9f, 0.25f, 0.25f, 0.35f);

    Mountain();
    RTree3();
    RTree2();
    RTree1();
    LTree3();
    LTree2();
    LTree1();
    Bush_A();
    Tent1_A(1.0f, 0.843f, 0.0f);
    Tent2_A(1.0f, 0.843f, 0.0f);
    Tent3_A(1.0f, 0.843f, 0.0f);
    Tent4_A(1.0f, 0.843f, 0.0f);

    drawRiver_A();
    river();
    boat();
    fire_Astick_A();
    fire_A1(56.0f, 29.0f, 3.0f);
    fire_A();
    fire_A2(56.0f, 28.0f, 2.0f);
    Stone_A();
    flower1(49.0f, 5.0f, 2.0f);
    flower2(57.0f, 3.0f, 2.0f);
    flowercut();
    meat();
    meat1(53.0f, 37.0f, 1.0f);
    meat2(60.0f, 37.0f, 1.0f);
    meatrope();
    fire_Aflies();
    glutSwapBuffers();

    drawRain();
    drawSplashes();

}

void drawDayRainScene_A() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    UpperSky(0.5f, 0.6f, 0.7f);

    //drawStars();
    DownGround();

    drawCloud(cloudX1, 66.0f, 1.0f, 0.3f, 0.3f, 0.4f);
    drawCloud(cloudX2, 70.0f, 1.2f, 0.35f, 0.35f, 0.45f);
    drawCloud(cloudX3, 75.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    Mountain();
    RTree3();
    RTree2();
    RTree1();
    LTree3();
    LTree2();
    LTree1();
    Bush_A();
    Tent1_A(0.20f, 0.15f, 0.31f);
    Tent2_A(0.37f, 0.22f, 0.23f);
    Tent3_A(0.37f, 0.22f, 0.23f);
    Tent4_A(0.37f, 0.22f, 0.23f);

    drawRiver_A();
    river();
    boat();
    fire_Astick_A();
    Stone_A();
    flower1(49.0f, 5.0f, 2.0f);
    flower2(57.0f, 3.0f, 2.0f);
    flowercut();
    drawRain();
    drawSplashes();

    glutSwapBuffers();
}

void drawNightRainScene_A() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    UpperSky(0.1f, 0.12f, 0.18f);

    DownGround();
    drawCloud(cloudX1, 66.0f, 1.0f, 0.3f, 0.3f, 0.4f);
    drawCloud(cloudX2, 70.0f, 1.2f, 0.35f, 0.35f, 0.45f);
    drawCloud(cloudX3, 75.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    Mountain();
    RTree3();
    RTree2();
    RTree1();
    LTree3();
    LTree2();
    LTree1();
    Bush_A();
    Tent1_A(1.0f, 0.843f, 0.0f);
    Tent2_A(1.0f, 0.843f, 0.0f);
    Tent3_A(1.0f, 0.843f, 0.0f);
    Tent4_A(1.0f, 0.843f, 0.0f);
    drawRiver_A();
    river();
    boat();
    fire_Astick_A();

    Stone_A();
    flower1(49.0f, 5.0f, 2.0f);
    flower2(57.0f, 3.0f, 2.0f);
    flowercut();
    drawRain();
    drawSplashes();

    glutSwapBuffers();
}

void sound_a()
{

    //PlaySound("a.wav", NULL, SND_ASYNC|SND_FILENAME);
    PlaySound("Azim.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

}
void sound_f()
{

    //PlaySound("a.wav", NULL, SND_ASYNC|SND_FILENAME);
    PlaySound("antor.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

}
void sound_i()
{

    //PlaySound("a.wav", NULL, SND_ASYNC|SND_FILENAME);
    PlaySound("ishrak.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

}
void sound_m()
{

    //PlaySound("a.wav", NULL, SND_ASYNC|SND_FILENAME);
    PlaySound("mahfuz.wav", NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);

}

// ================= Start Azim =================

bool isRaining_J = false;
bool isNight_J = false;

//for plane
float planeX_J = -20.0f;
float planeSpeed_J = 0.2f * 2;

//for cloud
float cloudX1_J = 0.0f;
float cloudX2_J = 30.0f;
float cloudX3_J = 60.0f;
float cloudSpeed_J = 0.05f;
float minCloudSpeed_J = 0.05f;
float maxCloudSpeed_J = 0.5f;
float normalCloudSpeed_J = 0.1f;

void drawCircle_J(float cx, float cy, float r, int segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= segments; ++i) {
        float angle = 2.0f * PI * i / segments;
        float x = r * cosf(angle);
        float y = r * sinf(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

void drawOcean_J(float R, float G, float B) {
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex2f(0, 25);
    glVertex2f(4, 24);
    glVertex2f(5, 25);
    glVertex2f(35, 21);
    glVertex2f(40, 22);
    glVertex2f(60, 22);
    glVertex2f(69, 23);
    glVertex2f(65, 25);
    glVertex2f(93, 28);
    glVertex2f(94, 31);
    glVertex2f(97, 33);
    glVertex2f(94, 38);
    glVertex2f(80, 45);
    glVertex2f(0, 45);
    glEnd();
}
//Draw Rock

void drawRocks() {
    glColor3f(0.58f, 0.56f, 0.50f); // Light gray-brown rock
    drawCircle_J(84.0f, 5.8f, 7.0f, 100);

    glColor3f(0.45f, 0.43f, 0.40f);
    drawCircle_J(97.7f, 3.5f, 4.5f, 100);

    glColor3f(0.45f, 0.43f, 0.40f); // Darker gray rock
    drawCircle_J(78.0f, 1.0f, 2.5f, 100);

    glColor3f(0.45f, 0.43f, 0.40f);
    drawCircle_J(91.0f, 2.0f, 5.0f, 100);
}

void drawSand() {

    glColor3f(0.698f, 0.631f, 0.710f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 25);
    glVertex2f(4, 24);
    glVertex2f(5, 25);
    glVertex2f(35, 21);
    glVertex2f(40, 22);
    glVertex2f(60, 22);
    glVertex2f(69, 23);
    glVertex2f(65, 25);
    glVertex2f(93, 28);
    glVertex2f(94, 31);
    glVertex2f(97, 33);
    glVertex2f(94, 38);
    glVertex2f(80, 45);
    glVertex2f(100, 45);
    glVertex2f(100, 0);
    glVertex2f(0, 0);
    glEnd();

}

void drawMountain1_J(float R, float G, float B) {

    glBegin(GL_POLYGON);
    glColor3f(0.663f, 0.302f, 0.275f);
    glVertex2f(55, 45);
    glVertex2f(58, 49);
    glVertex2f(59, 48);
    glVertex2f(63, 54);
    glVertex2f(64, 54);
    glColor3f(0.490f, 0.263f, 0.294f);
    glColor3f(0.329f, 0.255f, 0.353f);
    glVertex2f(72, 48);
    glVertex2f(70, 45);
    glEnd();


    glColor3f(0.506f, 0.322f, 0.235f); // Black border
    glBegin(GL_LINE_LOOP);
    glVertex2f(55, 45);
    glVertex2f(58, 49);
    glVertex2f(59, 48);
    glVertex2f(63, 54);
    glVertex2f(64, 54);
    glVertex2f(72, 48);
    glVertex2f(70, 45);
    glEnd();

    glLineWidth(1.5f);
}

void drawSideMountain1_J(float R, float G, float B) {
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex2f(64, 54);
    glVertex2f(62, 45);
    glVertex2f(70, 45);
    glVertex2f(72, 48);


    glEnd();
}

void drawMountain2_J(float R, float G, float B) {
    //glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glColor3f(0.663f, 0.302f, 0.275f);
    glVertex2f(70, 45);
    glVertex2f(72, 48);
    glVertex2f(74, 48);
    glColor3f(0.490f, 0.263f, 0.294f);
    glVertex2f(76, 50);
    glVertex2f(77, 50);

    glColor3f(0.329f, 0.255f, 0.353f);
    glVertex2f(82, 45);
    glEnd();
}


void drawMountain3_J(float R, float G, float B) {
    //glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glColor3f(0.663f, 0.302f, 0.275f);
    glVertex2f(62, 45);
    glVertex2f(73, 57);
    glVertex2f(74, 57);
    glColor3f(0.490f, 0.263f, 0.294f);
    glVertex2f(76, 60);
    glVertex2f(77, 60);
    glVertex2f(81, 57);
    glColor3f(0.329f, 0.255f, 0.353f);
    glVertex2f(83, 55);
    glVertex2f(84, 55);
    glVertex2f(85, 54);
    glVertex2f(93, 45);

    glEnd();
}

void drawSideMountain3_J(float R, float G, float B) {
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    glVertex2f(77, 60);
    glVertex2f(81, 57);
    glVertex2f(83, 55);
    glVertex2f(84, 55);
    glVertex2f(85, 54);
    glVertex2f(85, 45);
    glVertex2f(82, 45);
    glVertex2f(77, 50);
    glVertex2f(76, 50);
    glVertex2f(75, 49);


    glEnd();
}
// all about sky
void drawSky_J() {
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.6f, 0.2f); // sunset orange
    glVertex2f(100, 80);
    glVertex2f(0, 80);
    glColor3f(1.0f, 0.8f, 0.4f); // near horizon
    glVertex2f(0, 45);
    glVertex2f(100, 45);
    glEnd();
}

void drawSky2_J() {

    glBegin(GL_QUADS);
    // Top sky - dark muted orange
    glColor3f(0.4f, 0.2f, 0.1f);
    glVertex2f(100, 80);
    glVertex2f(0, 80);

    // Horizon - slightly lighter muted orange
    glColor3f(0.6f, 0.35f, 0.15f);
    glVertex2f(0, 45);
    glVertex2f(100, 45);

    glEnd();

}

void drawNightSky_J(float R, float G, float B) {

    glColor3f(R, G, B);
    glBegin(GL_QUADS);
    glVertex2f(100, 80);
    glVertex2f(0, 80);
    glVertex2f(0, 45);
    glVertex2f(100, 45);
    glEnd();
}

void drawStars_J() {
    glColor3f(1.0f, 1.0f, 1.0f); // White stars
    srand(42); // Fixed seed for consistent star positions

    for (int i = 0; i < 100; i++) {
        float x = rand() % 100;
        float y = 45 + rand() % 40;
        drawCircle_J(x, y, 0.2, 100);
    }
}

void drawCrescentMoon_J(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(1.0f, 1.0f, 0.8f);  // pale yellow
    drawCircle_J(x, y, radius, 100);

    // Overlapping circle to form crescent
    glColor3f(0.05f, 0.05f, 0.2f); // night sky color (to "cut" moon)
    drawCircle_J(x + radius * 0.2f, y + radius * 0.1f, radius * 0.85f, 100);
}

void drawCloud_J(float x, float y, float scale, float r, float g, float b) {
    glColor3f(r, g, b); // Set cloud color

    drawCircle_J(x, y, 4.0f * scale, 100);
    drawCircle_J(x + 3.0f * scale, y + 1.0f * scale, 4.5f * scale, 100);
    drawCircle_J(x + 6.0f * scale, y, 4.0f * scale, 100);
    drawCircle_J(x + 3.0f * scale, y - 1.5f * scale, 4.0f * scale, 100);
}

void updateClouds_J(int value) {
    cloudX1_J += cloudSpeed_J;
    cloudX2_J -= cloudSpeed_J;
    cloudX3_J += cloudSpeed_J;

    // Reset positions further left so clouds enter smoothly
    if (cloudX1_J > 110.0f) cloudX1_J = -30.0f;
    if (cloudX2_J < -20.0f) cloudX2_J = +120.0f;
    if (cloudX3_J > 110.0f) cloudX3_J = -35.0f;

    glutPostRedisplay();
    glutTimerFunc(30, updateClouds_J, 0);
}

void drawBuilding_J(float x1, float y1, float x2, float y2, float R, float G, float B) {

    glColor3f(R, G, B); // Building color
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    // Draw Building border
    glColor3f(0.506f, 0.322f, 0.235f); // Black border
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

}

void drawWindow_J(float j, float x1, float y1, float x2, float y2, float R, float G, float B) {

    glColor3f(R, G, B); // window color
    for (float i = 0; i < j + 1; i += j) {
        glBegin(GL_POLYGON);
        glVertex2f(x1 + i, y1);
        glVertex2f(x2 + i, y1);
        glVertex2f(x2 + i, y2);
        glVertex2f(x1 + i, y2);
        glEnd();
    }

    // Draw window border
    glColor3f(0.506f, 0.322f, 0.235f); // Black border
    for (float i = 0; i < j + 1; i += j) {
        glBegin(GL_LINE_LOOP);
        glVertex2i(x1 + i, y1);
        glVertex2i(x2 + i, y1);
        glVertex2i(x2 + i, y2);
        glVertex2i(x1 + i, y2);
        glEnd();
    }

}

void drawDoor_J(float x1, float y1, float x2, float y2, float R, float G, float B) {

    glColor3f(R, G, B); // door color
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();

    // Draw door border
    glColor3f(0.65f, 0.6f, 0.55f); // Ash with warm brown undertone
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();

    glColor3f(0.65f, 0.6f, 0.55f); // Ash with warm brown undertone
    glBegin(GL_LINE_LOOP);
    glVertex2i((x1 + x2) / 2, y1);
    glVertex2i((x1 + x2) / 2, y2);
    glEnd();

}

void drawBalcony_J(float x1, float y1, float x2, float y2, float R, float G, float B) {

    glColor3f(R, G, B); // Building color
    glBegin(GL_POLYGON);
    glVertex2f(x1, y1);
    glVertex2f(x2, y1);
    glVertex2f(x2, y2);
    glVertex2f(x1, y2);
    glEnd();
}

void drawCastle() {

    glPushMatrix();
    glScalef(0.6, 0.6, 1);
    glTranslatef(60, 10, 0);

    glColor3f(0.965f, 0.663f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(84.0f, 20.0f);
    glVertex2f(84.0f, 26.0f);
    glVertex2f(87.0f, 26.0f);
    glVertex2f(87.0f, 20.0f);
    glEnd();

    glColor3f(0.965f, 0.663f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(94.0f, 20.0f);
    glVertex2f(94.0f, 26.0f);
    glVertex2f(97.0f, 26.0f);
    glVertex2f(97.0f, 20.0f);
    glEnd();

    glColor3f(0.965f, 0.663f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(83.0f, 26.0f);
    glVertex2f(85.5f, 29.0f);
    glVertex2f(88.0f, 26.0f);
    glEnd();

    glColor3f(0.965f, 0.663f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(93.0f, 26.0f);
    glVertex2f(95.5f, 29.0f);
    glVertex2f(98.0f, 26.0f);
    glEnd();

    glColor3f(0.965f, 0.663f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 23.0f);
    glVertex2f(89.0f, 27.0f);
    glVertex2f(92.0f, 27.0f);
    glVertex2f(92.0f, 23.0f);
    glEnd();

    glColor3f(0.965f, 0.663f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(88.0f, 27.0f);
    glVertex2f(90.5f, 30.0f);
    glVertex2f(93.0f, 27.0f);
    glEnd();

    glColor3f(0.965f, 0.663f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(87.0f, 20.0f);
    glVertex2f(87.0f, 23.0f);
    glVertex2f(94.0f, 23.0f);
    glVertex2f(94.0f, 20.0f);
    glEnd();

    glColor3f(0.965f, 0.663f, 0.235f);
    for (float i = 0; i < 5; i += 2) {
        glBegin(GL_POLYGON);
        glVertex2f(88 + i, 23);
        glVertex2f(88 + i, 24);
        glVertex2f(89 + i, 24);
        glVertex2f(89 + i, 23);
        glEnd();
    }

    glColor3f(0.506f, 0.322f, 0.235f);
    for (float i = 0; i < 11; i += 10) {
        glBegin(GL_POLYGON);
        glVertex2f(85 + i, 22);
        glVertex2f(85 + i, 24);
        glVertex2f(86 + i, 24);
        glVertex2f(86 + i, 22);
        glEnd();
    }

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(90.0f, 25.0f);
    glVertex2f(90.0f, 26.0f);
    glVertex2f(91.0f, 26.0f);
    glVertex2f(91.0f, 25.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 20.0f);
    glVertex2f(89.0f, 22.0f);
    glVertex2f(92.0f, 22.0f);
    glVertex2f(92.0f, 20.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(84.0f, 20.0f);
    glVertex2f(84.0f, 26.0f);
    glVertex2f(87.0f, 26.0f);
    glVertex2f(87.0f, 20.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(94.0f, 20.0f);
    glVertex2f(94.0f, 26.0f);
    glVertex2f(97.0f, 26.0f);
    glVertex2f(97.0f, 20.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(83.0f, 26.0f);
    glVertex2f(85.5f, 29.0f);
    glVertex2f(88.0f, 26.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(93.0f, 26.0f);
    glVertex2f(95.5f, 29.0f);
    glVertex2f(98.0f, 26.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(89.0f, 23.0f);
    glVertex2f(89.0f, 27.0f);
    glVertex2f(92.0f, 27.0f);
    glVertex2f(92.0f, 23.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(88.0f, 27.0f);
    glVertex2f(90.5f, 30.0f);
    glVertex2f(93.0f, 27.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(87.0f, 20.0f);
    glVertex2f(87.0f, 23.0f);
    glVertex2f(94.0f, 23.0f);
    glVertex2f(94.0f, 20.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    for (float i = 0; i < 5; i += 2) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(88 + i, 23);
        glVertex2f(88 + i, 24);
        glVertex2f(89 + i, 24);
        glVertex2f(89 + i, 23);
        glEnd();
    }

    glColor3f(0.506f, 0.322f, 0.235f);
    for (float i = 0; i < 11; i += 10) {
        glBegin(GL_LINE_LOOP);
        glVertex2f(85 + i, 22);
        glVertex2f(85 + i, 24);
        glVertex2f(86 + i, 24);
        glVertex2f(86 + i, 22);
        glEnd();
    }

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(90.0f, 25.0f);
    glVertex2f(90.0f, 26.0f);
    glVertex2f(91.0f, 26.0f);
    glVertex2f(91.0f, 25.0f);
    glEnd();

    glColor3f(0.506f, 0.322f, 0.235f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(89.0f, 20.0f);
    glVertex2f(89.0f, 22.0f);
    glVertex2f(92.0f, 22.0f);
    glVertex2f(92.0f, 20.0f);
    glEnd();

    glPopMatrix();

}
void drawSun_J(float x, float y, float radius) {
    // Full moon base (bright)
    glColor3f(1.0f, 0.92f, 0.50f);

    drawCircle_J(x, y, radius, 100);
}

float treeX_J = 0;
float treeSpeed_J = 0.05;
bool moveTreeRight_J = true;

void drawTree_J() {

    glColor3f(0.2706f, 0.1765f, 0.1882f); // dBrown
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(2.0f, 0.0f);
    glVertex2f(2.0f, 25.0f);
    glVertex2f(0.0f, 25.0f);
    glEnd();

    glPushMatrix();
    glTranslatef(treeX_J, 0, 0);   // Position on screen

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(-10.0f, 40.0f);
    glVertex2f(8.0f, 25.0f);
    glVertex2f(-10.0f, 25.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);
    glBegin(GL_POLYGON);
    glVertex2f(-10.0f, 25.0f);
    glVertex2f(4.0f, 25.0f);
    glVertex2f(10.0f, 18.0f);
    glVertex2f(-10.0f, 18.0f);
    glEnd();

    glColor3f(0.07f, 0.32f, 0.27f);//
    glBegin(GL_POLYGON);
    glVertex2f(-10.0f, 45.0f);
    glVertex2f(5.0f, 30.0f);
    glVertex2f(-10.0f, 30.0f);
    glEnd();

    glPopMatrix();
}


void updatetree_J(int value) {
    if (!isRaining_J) {
        return; // Stop updating if not raining
    }

    // Update tree position based on direction
    if (moveTreeRight_J) {
        treeX_J += treeSpeed_J;
        if (treeX_J >= 1.0f) {
            treeX_J = 1.0f; // Clamp to boundary
            moveTreeRight_J = false; // Change direction to left
        }
    }
    else {
        treeX_J -= treeSpeed_J;
        if (treeX_J <= -1.0f) {
            treeX_J = -1.0f; // Clamp to boundary
            moveTreeRight_J = true; // Change direction to right
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updatetree_J, 0); // Continue updating
}

void drawBush_J() {
    glColor3f(0.07f, 0.32f, 0.27f); // ldGreen
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(7.0f, 0.0f);
    glVertex2f(11.0f, 5.0f);
    glVertex2f(9.0f, 3.0f);
    glVertex2f(10.0f, 7.0f);
    glVertex2f(6.0f, 5.0f);
    glVertex2f(8.0f, 9.0f);
    glVertex2f(5.0f, 7.0f);
    glVertex2f(4.0f, 12.0f);
    glVertex2f(1.0f, 7.0f);
    glVertex2f(0.0f, 9.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

    glColor3f(0.07f, 0.24f, 0.22f); // dGreen
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(7.0f, 0.0f);
    glVertex2f(10.0f, 3.0f);
    glVertex2f(7.0f, 2.0f);
    glVertex2f(7.0f, 5.0f);
    glVertex2f(5.0f, 3.0f);
    glVertex2f(4.0f, 11.0f);
    glVertex2f(1.0f, 3.0f);
    glVertex2f(1.0f, 7.0f);
    glVertex2f(0.0f, 5.0f);
    glVertex2f(0.0f, 0.0f);
    glEnd();

}

//Azim ship

float ShipX_J = -30.0f;
float ShipSpeed_J = 0.5f;
bool moveShipRight_J = true;

void drawShip_J() {

 glPushMatrix();
    glTranslatef(ShipX_J, 0.0f, 0.0f); // Move ship

    glColor3f(0.0f, 0.0f, 0.28f); // dark blue body

    glBegin(GL_QUADS);
        glVertex2f(0.0f, 42.6f);
        glVertex2f(3.1f, 36.3f);
        glVertex2f(9.0f, 36.3f);
        glVertex2f(9.0f, 42.6f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(9.0f, 42.6f);
        glVertex2f(9.0f, 36.3f);
        glVertex2f(11.0f, 36.3f);
        glVertex2f(11.0f, 41.5f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(31.0f, 36.3f);
        glVertex2f(31.0f, 41.5f);
        glVertex2f(33.0f, 42.6f);
        glVertex2f(33.0f, 36.3f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(11.0f, 41.5f);
        glVertex2f(11.0f, 36.3f);
        glVertex2f(31.0f, 36.3f);
        glVertex2f(31.0f, 41.5f);
    glEnd();

    glBegin(GL_TRIANGLES);
        glVertex2f(36.4f, 42.6f);
        glVertex2f(33.0f, 42.6f);
        glVertex2f(33.0f, 36.3f);
    glEnd();

    // ==================== Boxes on Ship ====================
    // box-1 (red)
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(3.9f, 50.0f);
        glVertex2f(8.4f, 50.0f);
        glVertex2f(8.4f, 47.1f);
        glVertex2f(3.9f, 47.1f);
    glEnd();

    // box-2 (blue)
    glColor3f(0.0f, 0.0f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(1.6f, 47.1f);
        glVertex2f(6.1f, 47.1f);
        glVertex2f(6.1f, 44.3f);
        glVertex2f(1.6f, 44.3f);
    glEnd();

    // box-3 (yello)
    glColor3f(0.949f, 0.612f, 0.243f);
    glBegin(GL_QUADS);
        glVertex2f(1.6f, 44.3f);
        glVertex2f(1.6f, 42.6f);
        glVertex2f(6.1f, 42.6f);
        glVertex2f(6.1f, 44.3f);
    glEnd();

    // box-4 (yellow)
    glColor3f(0.949f, 0.612f, 0.243f);
    glBegin(GL_QUADS);
        glVertex2f(6.1f, 47.1f);
        glVertex2f(6.1f, 44.3f);
        glVertex2f(10.7f, 44.3f);
        glVertex2f(10.7f, 47.1f);
    glEnd();

    // box-5 (red)
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(6.1f, 44.3f);
        glVertex2f(6.1f, 42.6f);
        glVertex2f(10.7f, 42.6f);
        glVertex2f(10.7f, 44.3f);
    glEnd();

    // small triangle (red)
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(10.7f, 42.6f);
        glVertex2f(9.0f, 42.6f);
        glVertex2f(10.7f, 41.7f);
    glEnd();

    // box-6 (green)
    glColor3f(0.6f, 0.55f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(10.7f, 50.0f);
        glVertex2f(10.7f, 47.1f);
        glVertex2f(15.2f, 47.1f);
        glVertex2f(15.2f, 50.0f);
    glEnd();

    // box-7 (blue)
    glColor3f(0.0f, 0.0f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(10.7f, 47.1f);
        glVertex2f(10.7f, 44.3f);
        glVertex2f(19.8f, 44.3f);
        glVertex2f(19.8f, 47.1f);
    glEnd();

    // box-8 (gray)
    glColor3f(0.812f, 0.812f, 0.812f);
    glBegin(GL_QUADS);
        glVertex2f(10.7f, 44.3f);
        glVertex2f(19.8f, 44.3f);
        glVertex2f(19.8f, 41.5f);
        glVertex2f(10.7f, 41.5f);
    glEnd();

    // box-9 (red)
    glColor3f(0.8f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(19.8f, 44.3f);
        glVertex2f(24.4f, 44.3f);
        glVertex2f(24.4f, 41.5f);
        glVertex2f(19.8f, 41.5f);
    glEnd();

  // box-10 (yello)
    glColor3f(0.6f, 0.55f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(22.5f, 47.3f);
        glVertex2f(26.8f, 47.3f);
        glVertex2f(26.8f, 44.6f);
        glVertex2f(22.5f, 44.6f);
    glEnd();

    // Vertical lines on ship
    glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(5.0f);
    glBegin(GL_LINES);
        glVertex2f(27.0f, 52.4f);
        glVertex2f(27.0f, 41.5f);

        glVertex2f(27.6f, 52.4f);
        glVertex2f(27.6f, 41.5f);

        glVertex2f(18.3f, 52.0f);
        glVertex2f(18.3f, 51.4f);

        glVertex2f(18.3f, 51.4f);
        glVertex2f(32.6f, 51.4f);

        glVertex2f(32.6f, 51.4f);
        glVertex2f(32.6f, 52.0f);

        glVertex2f(32.6f, 52.0f);
        glVertex2f(18.3f, 52.0f);

        glVertex2f(27.0f, 52.4f);
        glVertex2f(27.4f, 53.8f);

        glVertex2f(27.4f, 53.8f);
        glVertex2f(27.6f, 52.4f);
        glEnd();

   glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(1.8f);
    glBegin(GL_LINES);
        glVertex2f(24.75f, 50.4f);
        glVertex2f(24.75f, 47.4f);
        glEnd();

    // Unfilled triangle
 glColor3f(1.0f, 1.0f, 0.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(24.75f, 47.4f);
        glVertex2f(22.4f, 44.4f);
        glVertex2f(26.9f, 44.4f);
    glEnd();

    // Small yellow quad
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(24.5f, 51.4f);
        glVertex2f(25.0f, 51.4f);
        glVertex2f(25.0f, 50.4f);
        glVertex2f(24.5f, 50.4f);
    glEnd();
glPopMatrix();
    glFlush();
}

void updateShip_J(int value) {
    // Update tree position based on direction
    if (moveShipRight_J) {
        ShipX_J += ShipSpeed_J;
        if (ShipX_J >= 40.0f) {
            ShipX_J = 40.0f; // Clamp to boundary
            moveShipRight_J = false; // Change direction to left
        }
    }
    else {
        ShipX_J -= ShipSpeed_J;
        if (ShipX_J <= -65.0f) {
            ShipX_J = -65.0f; // Clamp to boundary
            moveShipRight_J = true; // Change direction to right
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updateShip_J, 0);
}
//Draw mat
void drawmat() {
   glColor3f(0.65f, 0.0f, 0.0f);

    glBegin(GL_POLYGON);
        glVertex2f(50.64f, 14.4f);
        glVertex2f(53.75f, 8.16f);
        glVertex2f(60.22f, 8.65f);
        glVertex2f(56.98f, 13.25f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(56.98f, 13.25f);
        glVertex2f(61.96f, 13.13f);
        glVertex2f(66.69f, 13.87f);
        glVertex2f(67.68f, 8.65f);
        glVertex2f(60.22f, 8.65f);
    glEnd();

     glBegin(GL_POLYGON);
        glVertex2f(66.69f, 13.87f);
        glVertex2f(69.67f, 14.0f);
        glVertex2f(74.28f, 8.77f);
        glVertex2f(67.68f, 8.65f);
    glEnd();
}

//draw Ball
void drawball() {

    glColor3f(0.529f, 0.808f, 0.922f); // 20% darker turquoise
    drawCircle_J(74.06f, 18.0f, 2.0f, 200); // filled circle

    glColor3f(0.0f, 0.0f, 0.0f); // black cross lines
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    glVertex2f(72.06f, 18.0f); // left edge
    glVertex2f(76.06f, 18.0f); // right edge

    glVertex2f(74.06f, 16.0f); // bottom edge
    glVertex2f(74.06f, 20.0f); // top edge

 glEnd();
}

//all about sky element
void drawPlane_J() {
    glPushMatrix();
    glTranslatef(planeX_J, 73.0f, 0.0f); // Bottom Y = 73
    glScalef(0.4, 0.4, 1);

    // Body
    glColor3f(0.94f, 0.94f, 0.86f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(10.0f, 0.0f);
    glVertex2f(10.0f, 2.0f);
    glVertex2f(0.0f, 2.0f);
    glEnd();

    // Tail
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 2.0f);
    glVertex2f(2.0f, 2.0f);
    glVertex2f(1.0f, 4.0f);
    glVertex2f(0.0f, 4.0f);
    glEnd();

    // Nose
    glBegin(GL_TRIANGLES);
    glVertex2f(10.0f, 0.0f);
    glVertex2f(12.0f, 1.0f);
    glVertex2f(10.0f, 2.0f);
    glEnd();

    // Bottom Wing
    glBegin(GL_QUADS);
    glVertex2f(5.0f, 0.0f);
    glVertex2f(4.0f, -3.0f);
    glVertex2f(5.0f, -3.0f);
    glVertex2f(7.0f, 0.0f);
    glEnd();

    // Top Wing
    glBegin(GL_QUADS);
    glVertex2f(5.0f, 2.0f);
    glVertex2f(3.0f, 4.0f);
    glVertex2f(4.0f, 4.0f);
    glVertex2f(6.0f, 2.0f);
    glEnd();

    // Windows (3 rectangular windows)
    glColor3f(0.3f, 0.6f, 0.9f); // Blue windows

    // Window 1
    glBegin(GL_POLYGON);
    glVertex2f(2.0f, 0.5f);
    glVertex2f(3.0f, 0.5f);
    glVertex2f(3.0f, 1.5f);
    glVertex2f(2.0f, 1.5f);
    glEnd();

    // Window 2
    glBegin(GL_POLYGON);
    glVertex2f(4.5f, 0.5f);
    glVertex2f(5.5f, 0.5f);
    glVertex2f(5.5f, 1.5f);
    glVertex2f(4.5f, 1.5f);
    glEnd();

    // Window 3
    glBegin(GL_POLYGON);
    glVertex2f(7.0f, 0.5f);
    glVertex2f(8.0f, 0.5f);
    glVertex2f(8.0f, 1.5f);
    glVertex2f(7.0f, 1.5f);
    glEnd();

    glPopMatrix();
}

void updatePlane_J(int value) {
    planeX_J += planeSpeed_J;
    if (planeX_J > 120.0f) planeX_J = -30.0f; // Reset if it goes off right side
    glutPostRedisplay();
    glutTimerFunc(30, updatePlane_J, 0);
}

void drawSeat1_J() {

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_POLYGON);
    glVertex2f(24.0f, 10.0f);
    glVertex2f(20.0f, 14.0f);
    glVertex2f(16.0f, 14.0f);
    glVertex2f(20.0f, 10.0f);
    glEnd();

    glColor3f(0.741f, 0.243f, 0.031f);
    glBegin(GL_POLYGON);
    glVertex2f(17.0f, 15.5f);
    glVertex2f(21.0f, 15.0f);
    glVertex2f(20.0f, 14.0f);
    glVertex2f(16.0f, 14.0f);
    glEnd();

    glColor3f(0.741f, 0.243f, 0.031f);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 10.0f);
    glVertex2f(24.0f, 10.0f);
    glVertex2f(20.0f, 14.0f);
    glVertex2f(21.0f, 15.0f);
    glEnd();

    glColor3f(0.765f, 0.204f, 0.039f);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 10.0f);
    glVertex2f(31.0f, 14.0f);
    glVertex2f(25.0f, 14.0f);
    glVertex2f(23.0f, 12.0f);

    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 10.0f);
    glVertex2f(31.0f, 14.0f);
    glVertex2f(31.0f, 13.0f);
    glVertex2f(25.0f, 9.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 10.0f);
    glVertex2f(20.0f, 10.0f);
    glVertex2f(20.0f, 9.0f);
    glVertex2f(25.0f, 9.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(24.0f, 10.0f);
    glVertex2f(23.0f, 11.0f);
    glVertex2f(22.0f, 6.0f);
    glVertex2f(23.0f, 6.0f);

    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(20.0f, 10.0f);
    glVertex2f(19.0f, 11.0f);
    glVertex2f(18.0f, 6.0f);
    glVertex2f(19.0f, 6.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(30.0f, 13.0f);
    glVertex2f(33.0f, 9.0f);
    glVertex2f(32.0f, 9.0f);
    glVertex2f(29.0f, 12.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 11.0f);
    glVertex2f(29.0f, 9.0f);
    glVertex2f(28.0f, 9.0f);
    glVertex2f(27.0f, 11.0f);
    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(17.0f, 15.5f);
    glVertex2f(21.0f, 15.0f);
    glVertex2f(20.0f, 14.0f);
    glVertex2f(16.0f, 14.0f);
    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(25.0f, 10.0f);
    glVertex2f(24.0f, 10.0f);
    glVertex2f(20.0f, 14.0f);
    glVertex2f(21.0f, 15.0f);
    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(24.0f, 13.0f);
    glVertex2f(29.5f, 13.0f);

    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(23.5f, 12.0f);
    glVertex2f(27.5f, 12.0f);

    glEnd();

}

void drawSeat2_J() {

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_POLYGON);
    glVertex2f(39.0f, 10.0f);
    glVertex2f(35.0f, 14.0f);
    glVertex2f(31.0f, 14.0f);
    glVertex2f(35.0f, 10.0f);
    glEnd();

    glColor3f(0.741f, 0.243f, 0.031f);
    glBegin(GL_POLYGON);
    glVertex2f(32.0f, 15.5f);
    glVertex2f(36.0f, 15.0f);
    glVertex2f(35.0f, 14.0f);
    glVertex2f(31.0f, 14.0f);
    glEnd();

    glColor3f(0.741f, 0.243f, 0.031f);
    glBegin(GL_POLYGON);
    glVertex2f(40.0f, 10.0f);
    glVertex2f(39.0f, 10.0f);
    glVertex2f(35.0f, 14.0f);
    glVertex2f(36.0f, 15.0f);
    glEnd();

    glColor4ub(195, 52, 10, 255);
    glBegin(GL_POLYGON);
    glVertex2f(40.0f, 10.0f);
    glVertex2f(46.0f, 14.0f);
    glVertex2f(40.0f, 14.0f);
    glVertex2f(38.0f, 12.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(40.0f, 10.0f);
    glVertex2f(46.0f, 14.0f);
    glVertex2f(46.0f, 13.0f);
    glVertex2f(40.0f, 9.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(40.0f, 10.0f);
    glVertex2f(35.0f, 10.0f);
    glVertex2f(35.0f, 9.0f);
    glVertex2f(40.0f, 9.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(39.0f, 10.0f);
    glVertex2f(38.0f, 11.0f);
    glVertex2f(37.0f, 6.0f);
    glVertex2f(38.0f, 6.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(35.0f, 10.0f);
    glVertex2f(34.0f, 11.0f);
    glVertex2f(33.0f, 6.0f);
    glVertex2f(34.0f, 6.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(45.0f, 13.0f);
    glVertex2f(48.0f, 9.0f);
    glVertex2f(47.0f, 9.0f);
    glVertex2f(44.0f, 12.0f);
    glEnd();

    glColor3f(0.278f, 0.149f, 0.074f);
    glBegin(GL_POLYGON);
    glVertex2f(43.0f, 11.0f);
    glVertex2f(44.0f, 9.0f);
    glVertex2f(43.0f, 9.0f);
    glVertex2f(42.0f, 11.0f);
    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(32.0f, 15.5f);
    glVertex2f(36.0f, 15.0f);
    glVertex2f(35.0f, 14.0f);
    glVertex2f(31.0f, 14.0f);
    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(40.0f, 10.0f);
    glVertex2f(39.0f, 10.0f);
    glVertex2f(35.0f, 14.0f);
    glVertex2f(36.0f, 15.0f);
    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(39.0f, 13.0f);
    glVertex2f(44.5f, 13.0f);

    glEnd();

    glColor3f(0.129f, 0.102f, 0.094f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(38.5f, 12.0f);
    glVertex2f(42.5f, 12.0f);

    glEnd();
}

void drawshadow_J() {

    glColor3f(0.2941f, 0.2353f, 0.2431f);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 9.0f);
    glVertex2f(33.0f, 9.0f);
    glVertex2f(20.0f, 1.0f);
    glVertex2f(10.0f, 1.0f);
    glVertex2f(18.0f, 6.0f);
    glEnd();

    glColor3f(0.2941f, 0.2353f, 0.2431f);
    glBegin(GL_POLYGON);
    glVertex2f(43.0f, 9.0f);
    glVertex2f(48.0f, 9.0f);
    glVertex2f(35.0f, 1.0f);
    glVertex2f(25.0f, 1.0f);
    glVertex2f(33.0f, 6.0f);
    glEnd();

}

void drawUmbrella_J() {
    glColor3f(0.133f, 0.122f, 0.086f);
    glBegin(GL_POLYGON);
    glVertex2f(27.0f, 7.0f);
    glVertex2f(28.0f, 7.0f);
    glVertex2f(28.0f, 21.0f);
    glVertex2f(27.0f, 21.0f);

    glEnd();

    glColor3f(0.396f, 0.102f, 0.063f);
    glBegin(GL_POLYGON);

    glVertex2f(28.0f, 27.0f);
    glVertex2f(20.0f, 20.0f);
    glVertex2f(23.0f, 21.0f);
    glVertex2f(25.0f, 20.0f);
    glEnd();

    glColor3f(0.624f, 0.141f, 0.043f);
    glBegin(GL_POLYGON);

    glVertex2f(28.0f, 27.0f);
    glVertex2f(30.0f, 20.0f);
    glVertex2f(28.0f, 21.0f);
    glVertex2f(25.0f, 20.0f);
    glEnd();

    glColor3f(0.902f, 0.196f, 0.008f);
    glBegin(GL_POLYGON);

    glVertex2f(28.0f, 27.0f);
    glVertex2f(36.0f, 20.0f);
    glVertex2f(33.0f, 21.0f);
    glVertex2f(30.0f, 20.0f);
    glEnd();

}

void drawUmbrella1_J() {

    glColor3f(0.133f, 0.122f, 0.086f);
    glBegin(GL_POLYGON);
    glVertex2f(27.0f, 7.0f);
    glVertex2f(28.0f, 7.0f);
    glVertex2f(28.0f, 21.0f);
    glVertex2f(27.0f, 21.0f);

    glEnd();

    glColor3f(0.624f, 0.141f, 0.043f);
    glBegin(GL_POLYGON);

    glVertex2f(28.0f, 27.0f);
    glVertex2f(32.0f, 15.0f);
    glVertex2f(30.0f, 17.0f);
    glVertex2f(28.0f, 15.0f);
    glVertex2f(26.0f, 17.0f);

    glVertex2f(23.0f, 15.0f);
    glEnd();

}

void drawDayScene_J() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawOcean_J(0.0f, 0.4f, 0.8f);  // A shade of blue
    drawSky_J();
    drawCloud_J(cloudX1_J, 68.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    drawCloud_J(cloudX2_J, 74.0f, 1.2f, 0.95f, 0.95f, 0.95f);
    drawCloud_J(cloudX3_J, 65.0f, 0.8f, 0.9f, 0.9f, 0.9f);
    drawMountain3_J(1.0f, 0.87f, 0.432f);
    drawMountain1_J(0.490f, 0.263f, 0.294f);
    drawMountain2_J(1.0f, 0.0f, 0.432f);
    drawBuilding_J(85.0f, 45.0f, 90.0f, 55.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(2.0f, 86.0f, 52.0f, 87.0f, 53.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(2.0f, 86.0f, 50.0f, 87.0f, 51.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(2.0f, 86.0f, 48.0f, 87.0f, 49.0f, 0.506f, 0.322f, 0.235f);
    drawDoor_J(86.0f, 45.0f, 88.0f, 47.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(92.0f, 45.0f, 100.0f, 65.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(4.0f, 93.0f, 60.0f, 95.0f, 62.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(4.0f, 93.0f, 56.0f, 95.0f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(4.0f, 93.0f, 52.0f, 95.0f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawDoor_J(94.0f, 45.0f, 98.0f, 50.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(91.0f, 45.0f, 95.0f, 60.0f, 0.839f, 0.600f, 0.388f);
    drawBuilding_J(92.5f, 55.0f, 93.8f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(92.5f, 51.0f, 93.8f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawDoor_J(92.0f, 45.0f, 94.0f, 49.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 57.0f, 91.0f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 55.0f, 91.0f, 56.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 53.0f, 91.0f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 51.0f, 91.0f, 52.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 49.0f, 91.0f, 50.0f, 0.506f, 0.322f, 0.235f);
    drawSun_J(45.0f, 50.0f, 5.0f);
    drawTree_J();
    drawBush_J();
    drawShip_J();
    drawRocks();

    drawshadow_J();
    drawSeat1_J();
    drawSeat2_J();
    drawUmbrella_J();
    drawmat();
    drawCastle();
    drawPlane2(65);
    drawball();
    glutSwapBuffers();
}

void drawNightScene_J() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawSand();
    drawOcean_J(0.0f, 0.4f, 0.8f);  // A shade of blue

    drawNightSky_J(0.05f, 0.05f, 0.2f);
    drawStars_J();
    drawCrescentMoon_J(80.0f, 75.0f, 3.0f);

    drawCloud_J(cloudX1_J, 68.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    drawCloud_J(cloudX2_J, 74.0f, 1.2f, 0.95f, 0.95f, 0.95f);
    drawCloud_J(cloudX3_J, 65.0f, 0.8f, 0.9f, 0.9f, 0.9f);
    drawMountain3_J(1.0f, 0.87f, 0.432f);
    drawMountain1_J(0.490f, 0.263f, 0.294f);

    drawMountain2_J(1.0f, 0.0f, 0.432f);

    drawBuilding_J(85.0f, 45.0f, 90.0f, 55.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(2.0f, 86.0f, 52.0f, 87.0f, 53.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(2.0f, 86.0f, 50.0f, 87.0f, 51.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(2.0f, 86.0f, 48.0f, 87.0f, 49.0f, 1.0f, 0.843f, 0.0f);
    drawDoor_J(86.0f, 45.0f, 88.0f, 47.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(92.0f, 45.0f, 100.0f, 65.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(4.0f, 93.0f, 60.0f, 95.0f, 62.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(4.0f, 93.0f, 56.0f, 95.0f, 58.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(4.0f, 93.0f, 52.0f, 95.0f, 54.0f, 1.0f, 0.843f, 0.0f);
    drawDoor_J(94.0f, 45.0f, 98.0f, 50.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(91.0f, 45.0f, 95.0f, 60.0f, 0.839f, 0.600f, 0.388f);
    drawBuilding_J(92.5f, 55.0f, 93.8f, 58.0f, 1.0f, 0.843f, 0.0f);
    drawBuilding_J(92.5f, 51.0f, 93.8f, 54.0f, 1.0f, 0.843f, 0.0f);
    drawDoor_J(92.0f, 45.0f, 94.0f, 49.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 57.0f, 91.0f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 55.0f, 91.0f, 56.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 53.0f, 91.0f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 51.0f, 91.0f, 52.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 49.0f, 91.0f, 50.0f, 0.506f, 0.322f, 0.235f);

    drawTree_J();
    drawBush_J();
    drawShip_J();
    drawRocks();

    drawshadow_J();
    drawSeat1_J();
    drawSeat2_J();
    drawUmbrella1_J();
    drawmat();
    drawPlane2(65);
    glutSwapBuffers();
}

void drawRainDayScene_J() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawOcean_J(0.0f, 0.4f, 0.8f);  // A shade of blue
    drawSky2_J();
    drawCloud_J(cloudX1_J, 68.0f, 1.0f, 0.4f, 0.4f, 0.4f);
    drawCloud_J(cloudX2_J, 74.0f, 1.2f, 0.65f, 0.65f, 0.65);
    drawCloud_J(cloudX3_J, 65.0f, 0.8f, 0.2f, 0.2f, 0.2f);
    drawCloud_J(10, 66.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    drawCloud_J(70, 70.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    drawMountain3_J(1.0f, 0.87f, 0.432f);
    drawMountain1_J(0.490f, 0.263f, 0.294f);
    drawMountain2_J(1.0f, 0.0f, 0.432f);

    drawBuilding_J(85.0f, 45.0f, 90.0f, 55.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(2.0f, 86.0f, 52.0f, 87.0f, 53.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(2.0f, 86.0f, 50.0f, 87.0f, 51.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(2.0f, 86.0f, 48.0f, 87.0f, 49.0f, 0.506f, 0.322f, 0.235f);
    drawDoor_J(86.0f, 45.0f, 88.0f, 47.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(92.0f, 45.0f, 100.0f, 65.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(4.0f, 93.0f, 60.0f, 95.0f, 62.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(4.0f, 93.0f, 56.0f, 95.0f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawWindow_J(4.0f, 93.0f, 52.0f, 95.0f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawDoor_J(94.0f, 45.0f, 98.0f, 50.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(91.0f, 45.0f, 95.0f, 60.0f, 0.839f, 0.600f, 0.388f);
    drawBuilding_J(92.5f, 55.0f, 93.8f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(92.5f, 51.0f, 93.8f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawDoor_J(92.0f, 45.0f, 94.0f, 49.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 57.0f, 91.0f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 55.0f, 91.0f, 56.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 53.0f, 91.0f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 51.0f, 91.0f, 52.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 49.0f, 91.0f, 50.0f, 0.506f, 0.322f, 0.235f);

    drawTree_J();
    drawBush_J();
    drawShip_J();
    drawRocks();

    drawSeat1_J();
    drawSeat2_J();
    drawUmbrella_J();

    drawPlane2(65);
    drawRain();
    drawSplashes();

    glutSwapBuffers();
}

void drawRainNightScene_J() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    drawSand();
    drawOcean_J(0.0f, 0.4f, 0.8f);  // A shade of blue

    drawNightSky_J(0.05f, 0.05f, 0.2f);
    drawCloud_J(cloudX1_J, 68.0f, 1.0f, 0.4f, 0.4f, 0.4f);
    drawCloud_J(cloudX2_J, 74.0f, 1.2f, 0.65f, 0.65f, 0.65);
    drawCloud_J(cloudX3_J, 65.0f, 0.8f, 0.2f, 0.2f, 0.2f);
    drawCloud_J(10, 66.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    drawCloud_J(70, 70.0f, 0.9f, 0.25f, 0.25f, 0.35f);
    drawMountain3_J(1.0f, 0.87f, 0.432f);
    drawMountain1_J(0.490f, 0.263f, 0.294f);
    drawMountain2_J(1.0f, 0.0f, 0.432f);

    drawBuilding_J(85.0f, 45.0f, 90.0f, 55.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(2.0f, 86.0f, 52.0f, 87.0f, 53.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(2.0f, 86.0f, 50.0f, 87.0f, 51.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(2.0f, 86.0f, 48.0f, 87.0f, 49.0f, 1.0f, 0.843f, 0.0f);
    drawDoor_J(86.0f, 45.0f, 88.0f, 47.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(92.0f, 45.0f, 100.0f, 65.0f, 0.839f, 0.600f, 0.388f);
    drawWindow_J(4.0f, 93.0f, 60.0f, 95.0f, 62.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(4.0f, 93.0f, 56.0f, 95.0f, 58.0f, 1.0f, 0.843f, 0.0f);
    drawWindow_J(4.0f, 93.0f, 52.0f, 95.0f, 54.0f, 1.0f, 0.843f, 0.0f);
    drawDoor_J(94.0f, 45.0f, 98.0f, 50.0f, 0.506f, 0.322f, 0.235f);
    drawBuilding_J(91.0f, 45.0f, 95.0f, 60.0f, 0.839f, 0.600f, 0.388f);
    drawBuilding_J(92.5f, 55.0f, 93.8f, 58.0f, 1.0f, 0.843f, 0.0f);
    drawBuilding_J(92.5f, 51.0f, 93.8f, 54.0f, 1.0f, 0.843f, 0.0f);
    drawDoor_J(92.0f, 45.0f, 94.0f, 49.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 57.0f, 91.0f, 58.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 55.0f, 91.0f, 56.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 53.0f, 91.0f, 54.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 51.0f, 91.0f, 52.0f, 0.506f, 0.322f, 0.235f);
    drawBalcony_J(90.5f, 49.0f, 91.0f, 50.0f, 0.506f, 0.322f, 0.235f);

    drawTree_J();
    drawBush_J();
    drawShip_J();
    drawRocks();

    drawSeat1_J();
    drawSeat2_J();
    drawUmbrella1_J();
    drawPlane2(65);
    drawRain();
    drawSplashes();

    glutSwapBuffers();
}

// ================= Start Ishrak =================

float wheelAngle = 0.0f;
float angle = 0.0f;
float targetAngle = 0.0f;
bool  rotating = false;
float speed1 = 1.0f;
float _moveA = 0.0f;
float _moveB = 0.0f;
float _moveC = 0.0f;
float speed = 0.06f;

float planeX_N = 0.0f;


static float wavePhase = 0.0f;
static const float waveSpeed = 0.05f;   // how fast the ripples move
static const float waveAmp = 2.0f;    // how tall the ripples are
static const float waveFreq = 0.2f;    // how many ripples across the span

inline float fakeRand(int seed) {
    return fmod(sin(seed * 12.9898f) * 43758.5453f, 1.0f); // returns [0.0, 1.0)
}

void drawWindmill() {
    // tower
    glColor3f(0.55f, 0.45f, 0.35f);
    glBegin(GL_QUADS);
        glVertex2f(72.17f, 47.02f); // +3 X
        glVertex2f(74.47f, 47.01f);
        glVertex2f(74.36f, 52.55f);
        glVertex2f(72.76f, 52.58f);
    glEnd();

    glColor3f(0.65f, 0.55f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2f(74.47f, 47.01f);
        glVertex2f(76.77f, 47.00f);
        glVertex2f(75.96f, 52.52f);
        glVertex2f(74.36f, 52.55f);
    glEnd();

    // selling
    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(72.76f, 52.58f);
        glVertex2f(73.13f, 54.04f);
        glVertex2f(74.35f, 55.07f);
        glVertex2f(75.09f, 54.42f);
        glVertex2f(75.96f, 52.52f);
    glEnd();

    // door
    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(73.35f, 46.88f);
        glVertex2f(75.44f, 46.94f);
        glVertex2f(75.41f, 49.72f);
        glVertex2f(73.36f, 49.75f);
    glEnd();

    //window
    glColor3f(0.9f, 0.9f, 0.7f);
    glBegin(GL_QUADS);
        glVertex2f(73.2f, 50.5f);
        glVertex2f(73.7f, 50.5f);
        glVertex2f(73.7f, 51.2f);
        glVertex2f(73.2f, 51.2f);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(75.0f, 50.5f);
        glVertex2f(75.5f, 50.5f);
        glVertex2f(75.5f, 51.2f);
        glVertex2f(75.0f, 51.2f);
    glEnd();

    //blade
    glPushMatrix();

    glTranslatef(74.3f, 53.5f, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-74.3f, -53.5f, 0.0f);

    glColor3f(0.95f, 0.95f, 0.95f);
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(74.3f, 53.5f, 0.0f);
        glRotatef(i * 90.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(-74.3f, -53.5f, 0.0f);

        glBegin(GL_POLYGON);
            glVertex2f(74.0f, 53.5f);
            glVertex2f(74.6f, 53.5f);
            glVertex2f(75.2f, 59.5f);
            glVertex2f(73.4f, 59.5f);
        glEnd();

        glPopMatrix();
    }
    glPopMatrix();

    glColor3f(0.6f, 0.3f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * PI / 180.0f;
        glVertex2f(74.3f + cos(rad) * 1.5f, 53.5f + sin(rad) * 1.5f);
    }
    glEnd();
}

// animation update
void update(float value) {
    angle += 1.5f;
    if (angle >= 360.0f) angle -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void drawStars(int count) {
    glPointSize(2.0f); // Star size
    glBegin(GL_POINTS);
    for (int i = 0; i < count; ++i) {
        float x = fakeRand(i * 3) * 100.0f;         // x in [0, 100]
        float y = 60.0f + fakeRand(i * 5) * 20.0f;  // y in [60, 80]

        // Slight variation in star color
        float r = 0.9f + fakeRand(i * 7) * 0.1f;    // 0.9 to 1.0
        float g = r;
        float b = r * 0.9f;

        glColor3f(r, g, b);
        glVertex2f(x, y);
    }
    glEnd();
}

void nboat() {
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(22.0f, 0.5f);
    glVertex2f(21.0f, 1.5f);
    glVertex2f(17.5f, 1.5f);
    glVertex2f(18.0f, 0.5f);
    glEnd();

    // 2) Black stripe
    glBegin(GL_QUADS);
    glColor3ub(0, 0, 0);
    glVertex2f(22.0f, 0.0f);
    glVertex2f(22.0f, 0.5f);
    glVertex2f(17.0f, 0.5f);
    glVertex2f(17.0f, 0.0f);
    glEnd();

    // 5) Stern triangle
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(17.0f, 0.0f);
    glVertex2f(17.0f, 0.5f);
    glVertex2f(15.5f, 0.8f);
    glEnd();

    // 6) Bow triangle
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(22.0f, 0.5f);
    glVertex2f(22.0f, 0.0f);
    glVertex2f(23.5f, 0.8f);
    glEnd();

    // 7) Deck-detail triangle
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(17.0f, 0.5f);
    glVertex2f(18.0f, 0.5f);
    glVertex2f(17.5f, 1.5f);
    glEnd();
}

void ndrawPlane() {
    glPushMatrix();
    glTranslatef(planeX_N, 65.0f, 0.0f);
    glScalef(-16.0, 30.0, 0);

    // ================= Plane Body =================
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.4214f, 0.2920f);
    glVertex2f(-0.8376f, 0.2912f);
    glVertex2f(-0.9320f, 0.2881f);
    glVertex2f(-0.9289f, 0.2556f);
    glVertex2f(-0.9041f, 0.2378f);
    glVertex2f(-0.8732f, 0.2278f);
    glVertex2f(-0.8453f, 0.2193f);
    glVertex2f(-0.8144f, 0.2108f);
    glVertex2f(-0.7842f, 0.2069f);
    glVertex2f(-0.7440f, 0.2077f);
    glVertex2f(-0.3897f, 0.2092f);
    glVertex2f(-0.3603f, 0.2131f);
    glEnd();

    // ================= Plane Head =================
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(-0.4214f, 0.2920f);
    glVertex2f(-0.4044f, 0.2893f);
    glVertex2f(-0.3832f, 0.2803f);
    glVertex2f(-0.3546f, 0.2671f);
    glVertex2f(-0.3381f, 0.2622f);
    glVertex2f(-0.3238f, 0.2573f);
    glVertex2f(-0.3177f, 0.2518f);
    glVertex2f(-0.3122f, 0.2463f);
    glVertex2f(-0.3100f, 0.2400f);
    glVertex2f(-0.3098f, 0.2357f);
    glVertex2f(-0.3100f, 0.2300f);
    glVertex2f(-0.3138f, 0.2259f);
    glVertex2f(-0.3204f, 0.2228f);
    glVertex2f(-0.3281f, 0.2191f);
    glVertex2f(-0.3379f, 0.2157f);
    glVertex2f(-0.3500f, 0.2128f);
    glVertex2f(-0.3603f, 0.2131f);
    glEnd();

    // ================= Head Windows =================
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.3819f, 0.2759f);
    glVertex2f(-0.3881f, 0.2729f);
    glVertex2f(-0.3772f, 0.2609f);
    glVertex2f(-0.3705f, 0.2634f);
    glVertex2f(-0.3661f, 0.2658f);
    glVertex2f(-0.3609f, 0.2696f);
    glVertex2f(-0.3787f, 0.2782f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.3989f, 0.2687f);
    glVertex2f(-0.4099f, 0.2680f);
    glVertex2f(-0.4085f, 0.2627f);
    glVertex2f(-0.4031f, 0.2556f);
    glVertex2f(-0.3926f, 0.2562f);
    glVertex2f(-0.3805f, 0.2589f);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.4128f, 0.2603f);
    glVertex2f(-0.4148f, 0.2668f);
    glVertex2f(-0.4318f, 0.2669f);
    glVertex2f(-0.4323f, 0.2604f);
    glVertex2f(-0.4296f, 0.2515f);
    glVertex2f(-0.4078f, 0.2526f);
    glEnd();

    // ================= Front Door =================
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.4540f, 0.2650f);
    glVertex2f(-0.4772f, 0.2641f);
    glVertex2f(-0.4757f, 0.2159f);
    glVertex2f(-0.4517f, 0.2157f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.4540f, 0.2650f);
    glVertex2f(-0.4772f, 0.2641f);
    glVertex2f(-0.4757f, 0.2159f);
    glVertex2f(-0.4517f, 0.2157f);
    glEnd();

    // Door Handle
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.4696f, 0.2426f);
    glVertex2f(-0.4728f, 0.2424f);
    glVertex2f(-0.4726f, 0.2379f);
    glVertex2f(-0.4693f, 0.2381f);
    glEnd();


    // ================= Wings =================
    // Upper Wing
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.5498f, 0.2873f);
    glVertex2f(-0.6218f, 0.3771f);
    glVertex2f(-0.6566f, 0.3778f);
    glVertex2f(-0.6489f, 0.2916f);
    glEnd();

    // Lower Wing
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.8513f, 0.1241f);
    glVertex2f(-0.8653f, 0.1246f);
    glVertex2f(-0.8522f, 0.1102f);
    glVertex2f(-0.8291f, 0.1111f);
    glVertex2f(-0.5056f, 0.2087f);
    glVertex2f(-0.7115f, 0.2078f);
    glEnd();

    // Lower Wing Back
    glBegin(GL_QUADS);
    glColor3f(0.5f, 0.5f, 0.5f);
    glVertex2f(-0.8479f, 0.2812f);
    glVertex2f(-0.9293f, 0.2448f);
    glVertex2f(-0.9793f, 0.2453f);
    glVertex2f(-0.9320f, 0.2881f);
    glEnd();

    // Upper Wing Back
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.8229f, 0.3036f);
    glVertex2f(-0.8415f, 0.3121f);
    glVertex2f(-0.8562f, 0.3283f);
    glVertex2f(-0.9057f, 0.3910f);
    glVertex2f(-0.9428f, 0.3894f);


    glVertex2f(-0.9320f, 0.2881f);
    glVertex2f(-0.7618f, 0.2914f);
    glVertex2f(-0.7935f, 0.2959f);
    glVertex2f(-0.8097f, 0.2989f);
    glEnd();

    // ================= Back Door =================
    glBegin(GL_QUADS);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(-0.7514f, 0.2701f);
    glVertex2f(-0.7756f, 0.2687f);
    glVertex2f(-0.7743f, 0.2286f);
    glVertex2f(-0.7496f, 0.2281f);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(0.4f, 0.4f, 0.4f);
    glVertex2f(-0.7514f, 0.2701f);
    glVertex2f(-0.7756f, 0.2687f);
    glVertex2f(-0.7743f, 0.2286f);
    glVertex2f(-0.7496f, 0.2281f);
    glEnd();

    // Back Door Handle
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);
    glVertex2f(-0.7679f, 0.2511f);
    glVertex2f(-0.7709f, 0.2509f);
    glVertex2f(-0.7708f, 0.2474f);
    glVertex2f(-0.7677f, 0.2477f);
    glEnd();

    // ================= Windows =================
    glBegin(GL_QUADS);
    glColor3f(0.2f, 0.2f, 0.2f);

    // Window 1
    glVertex2f(-0.7151f, 0.2669f);
    glVertex2f(-0.7145f, 0.2435f);
    glVertex2f(-0.6963f, 0.2435f);
    glVertex2f(-0.6976f, 0.2669f);

    // Window 2
    glVertex2f(-0.6820f, 0.2682f);
    glVertex2f(-0.6813f, 0.2441f);
    glVertex2f(-0.6638f, 0.2445f);
    glVertex2f(-0.6641f, 0.2678f);

    // Window 3
    glVertex2f(-0.6501f, 0.2669f);
    glVertex2f(-0.6492f, 0.2448f);
    glVertex2f(-0.6316f, 0.2445f);
    glVertex2f(-0.6329f, 0.2672f);

    // Window 4
    glVertex2f(-0.6196f, 0.2672f);
    glVertex2f(-0.6183f, 0.2451f);
    glVertex2f(-0.6014f, 0.2448f);
    glVertex2f(-0.6030f, 0.2669f);

    // Window 5
    glVertex2f(-0.5858f, 0.2662f);
    glVertex2f(-0.5852f, 0.2458f);
    glVertex2f(-0.5702f, 0.2454f);
    glVertex2f(-0.5712f, 0.2669f);

    // Window 6
    glVertex2f(-0.5533f, 0.2669f);
    glVertex2f(-0.5520f, 0.2454f);
    glVertex2f(-0.5371f, 0.2448f);
    glVertex2f(-0.5394f, 0.2669f);

    // Window 7
    glVertex2f(-0.5228f, 0.2665f);
    glVertex2f(-0.5208f, 0.2432f);
    glVertex2f(-0.5040f, 0.2435f);
    glVertex2f(-0.5056f, 0.2669f);

    glEnd();

    glPopMatrix();
}

void updateRipple() {
    wavePhase += waveSpeed;
    if (wavePhase > 2 * PI) wavePhase -= 2 * PI;
    glutPostRedisplay();
}

void drawRiverRipple(float x0, float x1, float y0, float y1) {
    glColor3ub(59, 116, 140);
    glLineWidth(2.0f);
    glBegin(GL_POLYGON);
    // sample resolution: increase for smoother wave
    const float step = 0.5f;
    for (float x = x0; x <= x1; x += step) {
        float t = (x - x0) / (x1 - x0);
        float baseY = y0 + t * (y1 - y0);
        float y = baseY + waveAmp * sinf(waveFreq * x + wavePhase);
        glVertex2f(x, y);
    }
    glEnd();
}

void drawCircle_N(float cx, float cy, float r, int segments = 32) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segments; ++i) {
        float theta = 2.0f * PI * i / segments;
        glVertex2f(cx + r * cosf(theta), cy + r * sinf(theta));
    }
    glEnd();
}

void drawHuman(float x, float y, float h = 1.0f) {
    // Head (skin tone)
    glColor3f(1.0f, 0.8f, 0.6f);
    drawCircle_N(x, y + 0.2f * h, 0.06f * h);

    // Torso (blue shirt)
    glColor3f(0.1f, 0.1f, 0.8f);
    glBegin(GL_POLYGON);
    glVertex2f(x - 0.03f * h, y + 0.15f * h);
    glVertex2f(x + 0.03f * h, y + 0.15f * h);
    glVertex2f(x + 0.05f * h, y - 0.1f * h);
    glVertex2f(x - 0.05f * h, y - 0.1f * h);
    glEnd();

    // Arms (blue)
    glLineWidth(5.0f);
    glColor3f(0.1f, 0.1f, 0.8f);
    glBegin(GL_LINES);
    // left arm
    glVertex2f(x, y + 0.05f * h);
    glVertex2f(x - 0.15f * h, y - 0.05f * h);
    // right arm
    glVertex2f(x, y + 0.05f * h);
    glVertex2f(x + 0.15f * h, y - 0.05f * h);
    glEnd();

    // Legs (dark gray pants)
    glLineWidth(6.0f);
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_LINES);
    // left leg
    glVertex2f(x, y - 0.1f * h);
    glVertex2f(x - 0.1f * h, y - 0.3f * h);
    // right leg
    glVertex2f(x, y - 0.1f * h);
    glVertex2f(x + 0.1f * h, y - 0.3f * h);
    glEnd();
}

// draw Kite

//right thke left

float kiteOffset = 20.0f;   // Start at right
float kiteSpeed  = -0.05f;   // move left first
float minX = 2.0f;         // left boundary
float maxX = 15.0f;         // right boundary


//left thke right

//float kiteOffset = -10.0f;   // Start at left
//float kiteSpeed  = 0.05f;    // Positive → moves right first

//float minX = 10.0f;   // left boundary
//float maxX = 20.0f;   // right boundary

//float hx = 50.0f, hy = 0.0f;
//float h  = 1.0f;


void drawKite(float kx, float ky, float s, float hx, float hy) {
    // Kite body (red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(kx, ky);
    glVertex2f(kx + s, ky + s);
    glVertex2f(kx, ky + 2 * s);
    glVertex2f(kx - s, ky + s);
    glEnd();

    // String (black wavy line)
    glColor3f(0.0f, 0.0f, 0.0f);
    glLineWidth(1.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(kx, ky);
    glVertex2f(kx - 0.02f * s, ky - 0.08f * s);
    glVertex2f(kx + 0.01f * s, ky - 0.16f * s);
    glVertex2f(kx - 0.01f * s, ky - 0.24f * s);
    glVertex2f(hx, hy);
    glEnd();
}

// Draw filled circle
void drawCircle_N(float cx, float cy, float radius, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 100; i++) {
        float angle = 2.0f * 3.1416f * i / 100;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}
// Outline circle (not filled)
void drawCircleOutline(GLfloat x, GLfloat y, GLfloat radius, GLfloat r, GLfloat g, GLfloat b) {
    int triangleAmount = 50;
    GLfloat twicePi = 2.0f * M_PI;

    glColor3f(r, g, b);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= triangleAmount; i++) {
        glVertex2f(
            x + (radius * cos(i * twicePi / triangleAmount)),
            y + (radius * sin(i * twicePi / triangleAmount))
        );
    }
    glEnd();
}

//draw line
void drawGrass(float x, float y,
    float bladeHeight = 1.0f,
    float spread = 0.5f,
    float lineWidth = 2.0f)
{
    glLineWidth(lineWidth);
    glColor3f(0.1f, 0.4f, 0.1f); // Grass green

    glBegin(GL_LINES);
    // Left blade
    glVertex2f(x, y);
    glVertex2f(x - spread, y + bladeHeight);
    // Center blade (taller)
    glVertex2f(x, y);
    glVertex2f(x, y + bladeHeight * 1.2f);
    // Right blade
    glVertex2f(x, y);
    glVertex2f(x + spread, y + bladeHeight);
    glEnd();
}

void drawGrassClump(float x, float y, int count = 60)
{
    for (int i = 0; i < count; ++i)
    {
        float offsetX = (fakeRand(i * 2) - 0.5f) * 2.0f;         // -1.0 to +1.0
        float height = 0.8f + fakeRand(i * 3) * 0.9f;           // 0.8 to 1.7
        float spread = 0.3f + fakeRand(i * 4) * 0.4f;           // 0.3 to 0.7
        float thick = 1.0f + fakeRand(i * 5) * 2.0f;           // 1.0 to 3.0

        drawGrass(x + offsetX, y, height, spread, thick);
    }
}

void drawWheel(float R, int N) {
    // 1) RIM
    glColor3ub(139, 69, 19);
    glLineWidth(10.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; ++i) {
        float theta = 2 * PI * i / 100;
        glVertex2f(R * cos(theta), R * sin(theta));
    }
    glEnd();

    // 2) HUB
    glBegin(GL_POLYGON);
    for (int i = 0; i < 40; ++i) {
        float theta = 2 * PI * i / 40;
        glVertex2f((R * 0.2f) * cos(theta), (R * 0.2f) * sin(theta));
    }
    glEnd();

    // 3) BUCKETS
    float bucketLen = R * 0.2f;
    float halfAngWid = (2 * PI / N) * 0.3f;
    glColor3ub(205, 133, 63);
    for (int i = 0; i < N; ++i) {
        float theta = 2 * PI * i / N;
        float a0 = theta - halfAngWid;
        float a1 = theta + halfAngWid;
        float r0 = R, r1 = R + bucketLen;

        float x0 = r0 * cos(a0), y0 = r0 * sin(a0);
        float x1 = r0 * cos(a1), y1 = r0 * sin(a1);
        float x2 = r1 * cos(a1), y2 = r1 * sin(a1);
        float x3 = r1 * cos(a0), y3 = r1 * sin(a0);

        glBegin(GL_QUADS);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
        glEnd();
    }
}

void drawGrain(float x, float y, float bladeHeight = 2.5f, float spread = 0.3f, float lineWidth = 0.1f)
{
    glLineWidth(lineWidth);
    // golden wheat color
    glColor3f(0.9f, 0.8f, 0.2f);

    glBegin(GL_LINES);
    // left awn
    glVertex2f(x, y);
    glVertex2f(x - spread, y + bladeHeight);
    // center awn (taller)
    glVertex2f(x, y);
    glVertex2f(x, y + bladeHeight * 1.3f);
    // right awn
    glVertex2f(x, y);
    glVertex2f(x + spread, y + bladeHeight);
    glEnd();
}


inline void drawGrainField(float x0, float y0,
    float width, float height,
    int rows = 10, int cols = 25)
{
    float dx = width / cols;
    float dy = height / rows;

    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            float xi = x0 + j * dx + dx * 0.5f;
            float yi = y0 + i * dy;
            float h = 1.2f + 0.3f * fakeRand(index * 3);
            float s = 0.25f + 0.1f * fakeRand(index * 5);
            drawGrain(xi, yi, h, s, 2.0f);
            ++index;
        }
    }
}
void ntree() {
    // Trunk
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(5.0, 44.5);
    glVertex2f(4.77, 43.505);
    glVertex2f(4.175, 42.035);
    glVertex2f(3.16, 40.535);
    glVertex2f(4.195, 40.71);
    glVertex2f(4.975, 41.115);
    glVertex2f(5.8, 41.725);
    glVertex2f(6.6, 40.52);
    glVertex2f(6.805, 39.1);
    glVertex2f(7.195, 40.315);
    glVertex2f(7.57, 41.475);
    glVertex2f(7.99, 42.755);
    glVertex2f(9.0, 42.5);
    glVertex2f(9.805, 41.535);
    glVertex2f(10.585, 41.19);
    glVertex2f(11.805, 41.02);
    glVertex2f(10.805, 42.02);
    glVertex2f(10.195, 42.99);
    glVertex2f(10.0, 44.5);
    glEnd();

    // Lower part
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(10.0, 44.5);
    glVertex2f(10.0, 47.0);
    glVertex2f(10.0, 49.5);
    glVertex2f(5.0, 49.5);
    glVertex2f(5.0, 47.0);
    glVertex2f(5.0, 44.5);
    glEnd();

    // Middle part
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(5.0, 49.5);
    glVertex2f(4.44, 51.0);
    glVertex2f(6.475, 51.0);
    glVertex2f(7.98, 51.0);
    glVertex2f(10.025, 51.0);
    glVertex2f(10.0, 49.5);
    glEnd();

    // Upper part
    glBegin(GL_POLYGON);
    glColor3ub(139, 69, 19);
    glVertex2f(4.44, 51.0);
    glVertex2f(3.425, 52.075);
    glVertex2f(2.525, 52.9805);
    glVertex2f(3.945, 54.55);
    glVertex2f(4.965, 53.5);
    glVertex2f(5.98, 52.57);
    glVertex2f(6.475, 51.0);
    glVertex2f(7.465, 53.065);
    glVertex2f(8.455, 54.605);
    glVertex2f(10.0, 54.5);
    glVertex2f(9.035, 52.98);
    glVertex2f(7.98, 51.0);
    glVertex2f(10.025, 51.0);
    glVertex2f(11.04, 51.96);
    glVertex2f(11.945, 53.01);
    glVertex2f(12.5, 52.0);
    glVertex2f(10.0, 49.5);
    glEnd();

    // Circles (tree leaves)
    drawCircle_N(0.99, 55.565, 2.98, 0.0f, 0.8f, 0.0f);
    drawCircle_N(4.25, 60.895, 4.05, 0.0f, 0.7f, 0.0f);
    drawCircle_N(10.25, 62.895, 4.20, 0.0f, 0.7f, 0.0f);
    drawCircle_N(10.19, 56.54, 2.81, 0.0f, 0.7f, 0.0f);
    drawCircle_N(15.59, 62.5, 3.67, 0.0f, 0.8f, 0.0f);
    drawCircle_N(16.865, 55.955, 3.67, 0.0f, 0.7f, 0.0f);
    drawCircle_N(9.215, 56.87, 2.815, 0.0f, 0.7f, 0.0f);
    drawCircle_N(5.215, 55.87, 2.315, 0.0f, 0.7f, 0.0f);
    drawCircle_N(11.715, 55.37, 2.815, 0.0f, 0.7f, 0.0f);
    drawCircle_N(12.765, 59.87, 2.815, 0.0f, 0.8f, 0.0f);

    // Outline circles (not filled)
    drawCircleOutline(11.85, 52.10, 0.50, 0.0f, 0.0f, 0.0f);
    drawCircleOutline(11.85, 52.10, 0.25, 0.0f, 0.0f, 0.0f);

}

void waterwheel() {
    glLineWidth(7.0f);

    // Set color (Red)
    glColor3f(0.65f, 0.16f, 0.16f);

    // Draw the wide line
    glBegin(GL_LINES);
    glVertex2f(65.0f, 24.0f);
    glVertex2f(65.0f, 20.0f);
    glEnd();

    const float centerX = 65.0f;
    const float centerY = 24.0f;
    const float radius = 6.0f;
    const float axleLen = radius * 1.2f;  // 20% beyond rim

    // Position & rotate the wheel
    glPushMatrix();
    glTranslatef(centerX, centerY, 0.0f);
    glRotatef(wheelAngle, 0.0f, 0.0f, 1.0f);
    drawWheel(radius, 12);

    // Axle (rotates with wheel)
    glColor3ub(0, 0, 0);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(-axleLen, 0.0f);
    glVertex2f(axleLen, 0.0f);
    glVertex2f(0.0f, -axleLen);
    glVertex2f(0.0f, axleLen);
    glEnd();
    glPopMatrix();
}

#define MAX_RAINDROP_JS_J 600
#define MAX_SPLASH_JES_J 200

//all about Rain
typedef struct {
    float x, y;
    float targetY;
} RainDrop_J;

typedef struct {
    float x, y;
    float radius;
    int active;
    float alpha;
} Splash_J;

RainDrop_J rain_J[MAX_RAINDROP_JS_J];
Splash_J splash_Jes[MAX_SPLASH_JES_J];
float rainSpeed_J = 0.6f;

void initRain_J() {
    for (int i = 0; i < MAX_RAINDROP_JS_J; i++) {
        rain_J[i].x = rand() % 100;
        rain_J[i].y = 100 + rand() % 40;
        rain_J[i].targetY = rand() % 61; // random y between 0 and 60
    }
    for (int i = 0; i < MAX_SPLASH_JES_J; i++) {
        splash_Jes[i].active = 0;
    }
}

void addSplash_J(float x, float y) {
    for (int i = 0; i < MAX_SPLASH_JES_J; i++) {
        if (!splash_Jes[i].active) {
            splash_Jes[i].x = x;
            splash_Jes[i].y = y;
            splash_Jes[i].radius = 0.001f;
            splash_Jes[i].alpha = 1.0f;
            splash_Jes[i].active = 1;
            break;
        }
    }
}

void drawRain_J() {
    glColor3f(0.7f, 0.8f, 1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < MAX_RAINDROP_JS_J; i++) {
        glVertex2f(rain_J[i].x, rain_J[i].y);
        glVertex2f(rain_J[i].x, rain_J[i].y - 2.0f);
    }
    glEnd();
}

void drawSplash_J() {
    for (int i = 0; i < MAX_SPLASH_JES_J; i++) {
        if (splash_Jes[i].active) {
            glColor4f(1.0f, 1.0f, 1.0f, splash_Jes[i].alpha);
            glBegin(GL_LINE_LOOP);
            for (int j = 0; j < 12; j++) {
                float angle = 2 * PI * j / 12;
                float dx = splash_Jes[i].radius * cos(angle);
                float dy = splash_Jes[i].radius * sin(angle);
                glVertex2f(splash_Jes[i].x + dx, splash_Jes[i].y + dy);
            }
            glEnd();
        }
    }
}

void updateRain_J(int value) {
    for (int i = 0; i < MAX_RAINDROP_JS_J; i++) {
        rain_J[i].y -= rainSpeed_J;

        // Check if it has reached the target splash_J point
        if (rain_J[i].y <= rain_J[i].targetY) {
            addSplash_J(rain_J[i].x, rain_J[i].targetY);

            // Reset rain_Jdrop_J
            rain_J[i].x = rand() % 100;
            rain_J[i].y = 100 + rand() % 50;
            rain_J[i].targetY = rand() % 45; // New target Y between 0 and 60
        }
    }

    // Update splash_Jes
    for (int i = 0; i < MAX_SPLASH_JES_J; i++) {
        if (splash_Jes[i].active) {
            splash_Jes[i].radius += 0.02f;
            splash_Jes[i].alpha -= 0.03f;
            if (splash_Jes[i].alpha <= 0.0f) {
                splash_Jes[i].active = 0;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateRain_J, 0);
}

void drawScene_N() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glColor3ub(125, 201, 238);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 80.0f);
    glVertex2f(0.0f, 80.0f);
    glEnd();

    //sun -----------------

    drawCircle_N(65, 65, 3, 255, 255, 0);

    // Left soil (green, arbitrary shape)
    glColor3ub(155, 188, 84);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 25.0f);
    glVertex2f(34.0f, 25.0f);
    glVertex2f(40.0f, 29.0f);
    glVertex2f(31.0f, 31.0f);
    glVertex2f(52.0f, 40.0f);
    glVertex2f(41.0f, 48.0f);
    glVertex2f(47.0f, 51.0f);
    glVertex2f(40.0f, 55.0f);
    glVertex2f(0.0f, 55.0f);
    glEnd();

    // Right soil (green, via a fan)
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(155, 188, 84);        glVertex2f(73.0f, 44.0f);
    glVertex2f(58.0f, 24.0f);        // fan origin
    glVertex2f(67.0f, 16.0f);
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(64.0f, 55.0f);

    glEnd();

    // Brown “side‐face” under that slope (C→D→B→A)
    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(42.3f, 47.3f);   // C
    glVertex2f(47.0f, 50.0f);   // D
    glVertex2f(47.0f, 51.0f);   // B
    glVertex2f(41.0f, 48.0f);   // A
    glEnd();

    glColor3ub(117, 86, 44);    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(33.1f, 30.5f);   // C
    glVertex2f(52.0f, 38.0f);   // D
    glVertex2f(52.0f, 40.0f);   // B
    glVertex2f(31.0f, 31.0f);   // A
    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(35.0f, 24.0f);   // D
    glVertex2f(40.0f, 27.5f);
    glVertex2f(40.0f, 29.0f);// B
    glVertex2f(34.0f, 25.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(0.0f, 24.0f);   // D
    glVertex2f(35.0f, 24.0f);
    glVertex2f(34.0f, 25.0f);// B
    glVertex2f(0.0f, 25.0f);   // A

    glEnd();

    //------------------------------------
    //right
    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(62.0f, 55.0f);   // D
    glVertex2f(72.0f, 42.5f);
    glVertex2f(73.0f, 44.0f);// B
    glVertex2f(64.0f, 55.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(58.0f, 24.0f);   // D
    glVertex2f(67.0f, 16.0f);
    glVertex2f(68.0f, 17.0f);// B
    glVertex2f(59.0f, 25.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(67.0f, 16.0f);   // D
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 17.0f);// B
    glVertex2f(68.0f, 17.0f);   // A

    glEnd();

    //brus------------------

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(222, 204, 87);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(34.0f, 43.0f);
    glVertex2f(34.0f, 45.0f);
    glVertex2f(32.0f, 47.0f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(24.0f, 47.0f);

    glEnd();

    glLineWidth(5.0f);

    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw the wide line
    glBegin(GL_LINES);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 51.0f);
    glEnd();

    ///house on left side///
    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.0f, 46.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(14.0f, 50.0f);

    glEnd();

    //polygon 2
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(17.0f, 46.0f);
    glVertex2f(25.0f, 46.0f);
    glVertex2f(22.0f, 50.0f);
    glVertex2f(14.0f, 50.0f);

    glEnd();

    //polygon 3
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(205, 133, 63);
    glVertex2f(14.0f, 50.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(12.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 4
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(24.0f, 46.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 5
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.5f, 42.0f);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(12.0f, 43.0f);

    glEnd();

    //polygon 6
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(25.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);

    glEnd();

    //polygon 7
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();


    ///door:left
    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();

    //polygon b
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(19.0f, 42.2f);
    glVertex2f(20.5f, 42.5f);
    glVertex2f(20.5f, 45.0f);
    glVertex2f(19.0f, 45.0f);

    glEnd();

    // house 3

    // --- Tiny House ---
    // Roof left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 52.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Roof right
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 52.5f);
    glVertex2f(32.0f, 52.5f);
    glVertex2f(30.5f, 54.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Main wall
    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 54.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(25.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Front wall
    glColor3ub(128, 135, 32);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(31.5f, 52.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Base trim left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.25f, 50.5f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(25.5f, 51.0f);
    glEnd();

    // Base trim right
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(32.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glEnd();

    // Small roof detail
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door panel (black)
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door frame
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, 50.6f);
    glVertex2f(29.75f, 50.75f);
    glVertex2f(29.75f, 52.0f);
    glVertex2f(29.0f, 52.0f);
    glEnd();

    //house 4

    // Roof left
    glColor3ub(105, 105, 105);  // dark gray
    glBegin(GL_POLYGON);
    glVertex2f(15.0f, 53.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 53.0f);
    glVertex2f(22.0f, 53.0f);
    glVertex2f(20.5f, 55.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(173, 216, 230);  // light blue
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 55.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(15.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(107, 142, 35);  // olive green
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(21.5f, 53.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);  // chocolate
    glBegin(GL_POLYGON);
    glVertex2f(15.25f, 51.0f);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(15.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);  // gold
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(22.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door panel (brown)
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(19.0f, 51.1f);
    glVertex2f(19.75f, 51.25f);
    glVertex2f(19.75f, 52.5f);
    glVertex2f(19.0f, 52.5f);
    glEnd();

    //house2.....

    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(105, 105, 105);
    glVertex2f(17.0f, 50.0f);
    glVertex2f(26.0f, 50.0f);
    glVertex2f(24.0f, 52.0f);
    glVertex2f(19.0f, 52.0f);

    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(24.0f, 47.0f);
    glVertex2f(25.0f, 48.0f);
    glVertex2f(25.0f, 50.0f);
    glVertex2f(22.0f, 50.0f);

    glEnd();

    //right

    // --- Tiny House  ---
    // Roof left
    glPushMatrix();
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, 0.0f);  // shift everything left by 9

    // Roof left
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();
    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();
    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();

    glPopMatrix();

    // ——— Fireplace ———---------------------------------------------
    glPushMatrix();
    glTranslatef(35.0f, 45.0f, 0.0f);
    glScalef(2.5f, 2.5f, 1.0f);

    // Fireplace opening
    glColor3ub(30, 30, 30);   // almost black
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(1.7f, 0.3f);
    glVertex2f(1.7f, 1.2f);
    glVertex2f(0.3f, 1.2f);
    glEnd();

    glPopMatrix();

    // grain field .....................................

    drawGrainField(70.0f, 25.0f,
        30.0f, 15.0f);

        //hill
    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(47, 74, 46);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(55.0f, 56.0f);
    glVertex2f(45.0f, 58.0f);
    glVertex2f(33.0f, 60.0f);
    glVertex2f(22.0f, 61.2f);
    glVertex2f(14.0f, 62.0f);
    glVertex2f(8.0f, 64.0f);
    glVertex2f(0.0f, 65.0f);


    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(47, 74, 46);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 65.0f);
    glVertex2f(94.0f, 64.5f);
    glVertex2f(85.0f, 63.0f);
    glVertex2f(76.0f, 60.0f);
    glVertex2f(70.0f, 59.0f);
    glVertex2f(65.0f, 57.0f);
    glVertex2f(55.0f, 56.0f);

    glEnd();

    ntree();
    //tree 2

    glPushMatrix(); // Save current matrix

    glTranslatef(73.0f, 32.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();

    glPopMatrix(); // Restore original matrix

    //tree 3

    glPushMatrix(); // Save current matrix

    glTranslatef(65.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();

    glPopMatrix();

    //tree4

    glPushMatrix(); // Save current matrix

    glTranslatef(93.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 5

    glPushMatrix(); // Save current matrix

    glTranslatef(40.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 6

    glPushMatrix(); // Save current matrix

    glTranslatef(33.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();
    glPopMatrix();

    //water-----------------------------------

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(71.0f, 23.0f);
    glVertex2f(100.0f, 42.0f);
    glVertex2f(100.0f, 44.0f);
    glVertex2f(71.0f, 25.0f);

    glEnd();

    drawRiverRipple(0.0f, 62.0f,   // x0, x1
        19.0f, 19.0f);

    //waterwheel --------------------------------------------------------

    waterwheel();

    //-----------water...

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(62.0f, 16.0f);
    glVertex2f(67.0f, 16.0f);
    glVertex2f(62.0f, 20.5f);

    glEnd();


    // Cloud 1
    glPushMatrix();
    glTranslatef(_moveC, 4, 0);
    drawCircle_N(10.0f, 65.0f, 2.0f, 255, 255, 255);
    drawCircle_N(12.0f, 67.0f, 1.8f, 255, 255, 255);
    drawCircle_N(14.0f, 65.0f, 2.0f, 255, 255, 255);
    drawCircle_N(12.0f, 63.0f, 1.6f, 255, 255, 255);
    drawCircle_N(16.0f, 65.0f, 1.8f, 255, 255, 255);
    drawCircle_N(15.0f, 63.0f, 1.5f, 255, 255, 255);
    drawCircle_N(15.0f, 67.0f, 1.5f, 255, 255, 255);

    glPopMatrix();

    // --- Cloud 2: x≈45…51, y≈70 ---
    glColor3ub(255, 255, 255);        // white puffs
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(45.0f, 70.0f, 2.5f, 255, 255, 255);
    drawCircle_N(47.0f, 72.0f, 2.2f, 255, 255, 255);
    drawCircle_N(49.0f, 70.0f, 2.5f, 255, 255, 255);
    drawCircle_N(47.0f, 68.0f, 2.0f, 255, 255, 255);

    glPopMatrix();

    //plane---------
    glPushMatrix();
    ndrawPlane();
    glPopMatrix();


    // --- Cloud 3: x≈75…81, y≈68 ---
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(75.0f, 68.0f, 2.3f, 255, 255, 255);
    drawCircle_N(77.0f, 70.0f, 2.0f, 255, 255, 255);
    drawCircle_N(79.0f, 68.0f, 2.3f, 255, 255, 255);
    drawCircle_N(77.0f, 66.0f, 1.9f, 255, 255, 255);
    // drawCircle_N(81.0f, 68.0f, 2.0f,255,255,255);
    glPopMatrix();

    float hx = 25.f, hy = 35.0f, h = 10.0f;
    drawHuman(hx, hy, h);

    glColor3ub(0, 0, 0);
    glLineWidth(3.0f);
    glBegin(GL_LINES);
    glVertex2f(25.5f, 36.5f);
    glVertex2f(26.4f, 34.7f);
    glEnd();

    drawCircle_N(26.6f, 35.7f, 0.6, 0, 0, 0);

    // animation kite

    glPushMatrix();
    float kx = 40.0f + kiteOffset, ky = 60.0f, ks = 3.1f;
drawKite(kx, ky, ks, hx, hy);
    glPopMatrix();

    // wave---------------------------------------------

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        13.0f, 13.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        8.0f, 8.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        3.0f, 3.0f);

    //grass...........

    drawGrassClump(5.0f, 25.0f, 60); drawGrassClump(2.0f, 25.0f, 60); drawGrassClump(8.0f, 25.0f, 60);
    drawGrassClump(11.0f, 25.0f, 60); drawGrassClump(14.0f, 25.0f, 60); drawGrassClump(17.0f, 25.0f, 60);
    drawGrassClump(20.0f, 25.0f, 60); drawGrassClump(23.0f, 25.0f, 60);   drawGrassClump(26.0f, 25.0f, 60);
    drawGrassClump(29.0f, 25.0f, 60);    drawGrassClump(32.0f, 25.0f, 60);    drawGrassClump(33.0f, 25.0f, 60);

    drawGrassClump(70.0f, 17.0f, 60);
    drawGrassClump(73.0f, 17.0f, 60);drawGrassClump(76.0f, 17.0f, 60);drawGrassClump(79.0f, 17.0f, 60);
    drawGrassClump(82.0f, 17.0f, 60);drawGrassClump(85.0f, 17.0f, 60);drawGrassClump(88.0f, 17.0f, 60);
    drawGrassClump(91.0f, 17.0f, 60);drawGrassClump(94.0f, 17.0f, 60);drawGrassClump(97.0f, 17.0f, 60);

    drawGrass(5, 35); drawGrass(10, 35); drawGrass(14, 40); drawGrass(20, 33); drawGrass(25, 38); drawGrass(30, 35); drawGrass(30, 40);
    drawGrass(80, 45); drawGrass(85, 43); drawGrass(90, 46); drawGrass(73, 47);

    //boat-----

    //boaty1

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveA, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(75.0f, 10.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(2.6f, 2.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);
    nboat();
    glPopMatrix();

    // boat-2 motion right → left, scaled so its original base from x=[17→22], y=[0→...]

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveB, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(15.0f, 1.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(3.6f, 3.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);

    nboat();
    // 3) Red deck
    glBegin(GL_QUADS);
    glColor3ub(255, 99, 71);
    glVertex2f(20.5f, 1.5f);
    glVertex2f(21.0f, 3.5f);
    glVertex2f(18.5f, 3.5f);
    glVertex2f(18.0f, 1.5f);
    glEnd();

    // 4) Mast post
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(19.8f, 3.5f);
    glVertex2f(19.8f, 4.0f);
    glVertex2f(19.7f, 4.0f);
    glVertex2f(19.7f, 3.5f);
    glEnd();

    glPopMatrix();
    drawWindmill();
    glutSwapBuffers();
}

void drawScene2_N() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Sky (blue band)
    // Night Sky
    glColor3ub(24, 84, 92);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 80.0f);
    glVertex2f(0.0f, 80.0f);
    glEnd();

    // Moon
    drawCircle_N(65, 65, 3, 0.996f, 0.980f, 0.714f);
    drawStars(150);

    // Left soil (green, arbitrary shape)
    glColor3ub(155, 188, 84);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 25.0f);
    glVertex2f(34.0f, 25.0f);
    glVertex2f(40.0f, 29.0f);
    glVertex2f(31.0f, 31.0f);
    glVertex2f(52.0f, 40.0f);
    glVertex2f(41.0f, 48.0f);
    glVertex2f(47.0f, 51.0f);
    glVertex2f(40.0f, 55.0f);
    glVertex2f(0.0f, 55.0f);
    glEnd();

    // Right soil (green, via a fan)
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(155, 188, 84);        glVertex2f(73.0f, 44.0f);
    glVertex2f(58.0f, 24.0f);        // fan origin
    glVertex2f(67.0f, 16.0f);
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(64.0f, 55.0f);

    glEnd();

    // Brown “side‐face” under that slope (C→D→B→A)
    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(42.3f, 47.3f);   // C
    glVertex2f(47.0f, 50.0f);   // D
    glVertex2f(47.0f, 51.0f);   // B
    glVertex2f(41.0f, 48.0f);   // A
    glEnd();

    glColor3ub(117, 86, 44);    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(33.1f, 30.5f);   // C
    glVertex2f(52.0f, 38.0f);   // D
    glVertex2f(52.0f, 40.0f);   // B
    glVertex2f(31.0f, 31.0f);   // A
    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(35.0f, 24.0f);   // D
    glVertex2f(40.0f, 27.5f);
    glVertex2f(40.0f, 29.0f);// B
    glVertex2f(34.0f, 25.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(0.0f, 24.0f);   // D
    glVertex2f(35.0f, 24.0f);
    glVertex2f(34.0f, 25.0f);// B
    glVertex2f(0.0f, 25.0f);   // A

    glEnd();

    //------------------------------------
    //right
    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(62.0f, 55.0f);   // D
    glVertex2f(72.0f, 42.5f);
    glVertex2f(73.0f, 44.0f);// B
    glVertex2f(64.0f, 55.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(58.0f, 24.0f);   // D
    glVertex2f(67.0f, 16.0f);
    glVertex2f(68.0f, 17.0f);// B
    glVertex2f(59.0f, 25.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(67.0f, 16.0f);   // D
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 17.0f);// B
    glVertex2f(68.0f, 17.0f);   // A

    glEnd();

    //brus------------------

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(222, 204, 87);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(34.0f, 43.0f);
    glVertex2f(34.0f, 45.0f);
    glVertex2f(32.0f, 47.0f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(24.0f, 47.0f);

    glEnd();

    glLineWidth(5.0f);

    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw the wide line
    glBegin(GL_LINES);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 51.0f);
    glEnd();

    ///house on left side///
    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.0f, 46.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(14.0f, 50.0f);
    glEnd();

    //polygon 2
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(17.0f, 46.0f);
    glVertex2f(25.0f, 46.0f);
    glVertex2f(22.0f, 50.0f);
    glVertex2f(14.0f, 50.0f);

    glEnd();

    //polygon 3
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(205, 133, 63);
    glVertex2f(14.0f, 50.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(12.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 4
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(24.0f, 46.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 5
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.5f, 42.0f);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(12.0f, 43.0f);

    glEnd();

    //polygon 6
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(25.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);

    glEnd();

    //polygon 7
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();

    ///door:left
    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(254, 250, 71);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();

    //polygon b
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(19.0f, 42.2f);
    glVertex2f(20.5f, 42.5f);
    glVertex2f(20.5f, 45.0f);
    glVertex2f(19.0f, 45.0f);

    glEnd();

    // house 3

    // --- Tiny House (scaled ~50%, around 25,50) ---
    // Roof left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 52.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Roof right
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 52.5f);
    glVertex2f(32.0f, 52.5f);
    glVertex2f(30.5f, 54.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Main wall
    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 54.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(25.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Front wall
    glColor3ub(128, 135, 32);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(31.5f, 52.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Base trim left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.25f, 50.5f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(25.5f, 51.0f);
    glEnd();

    // Base trim right
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(32.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glEnd();

    // Small roof detail
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door panel (black)
    glColor3ub(254, 250, 71);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door frame
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, 50.6f);
    glVertex2f(29.75f, 50.75f);
    glVertex2f(29.75f, 52.0f);
    glVertex2f(29.0f, 52.0f);
    glEnd();

    //house 4

    // Roof left
    glColor3ub(105, 105, 105);  // dark gray
    glBegin(GL_POLYGON);
    glVertex2f(15.0f, 53.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 53.0f);
    glVertex2f(22.0f, 53.0f);
    glVertex2f(20.5f, 55.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(173, 216, 230);  // light blue
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 55.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(15.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(107, 142, 35);  // olive green
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(21.5f, 53.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);  // chocolate
    glBegin(GL_POLYGON);
    glVertex2f(15.25f, 51.0f);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(15.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);  // gold
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(22.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door panel (brown)
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(19.0f, 51.1f);
    glVertex2f(19.75f, 51.25f);
    glVertex2f(19.75f, 52.5f);
    glVertex2f(19.0f, 52.5f);
    glEnd();

    //house2.....

    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(105, 105, 105);
    glVertex2f(17.0f, 50.0f);
    glVertex2f(26.0f, 50.0f);
    glVertex2f(24.0f, 52.0f);
    glVertex2f(19.0f, 52.0f);

    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(24.0f, 47.0f);
    glVertex2f(25.0f, 48.0f);
    glVertex2f(25.0f, 50.0f);
    glVertex2f(22.0f, 50.0f);

    glEnd();

    //right

    // --- Tiny House at (85,50) ---
    // Roof left
    glPushMatrix();
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, 0.0f);  // shift everything left by 9

    // Roof left
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();
    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();
    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door frame
    glColor3ub(254, 250, 71);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();

    glPopMatrix();

    // ——— Fireplace ———---------------------------------------------
    glPushMatrix();
    glTranslatef(35.0f, 45.0f, 0.0f);
    glScalef(2.5f, 2.5f, 1.0f);

    // Fireplace opening
    glColor3ub(30, 30, 30);   // almost black
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(1.7f, 0.3f);
    glVertex2f(1.7f, 1.2f);
    glVertex2f(0.3f, 1.2f);
    glEnd();

    // Flame – yellow base
    glColor3ub(255, 255, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.5f, 1.2f);
    glVertex2f(1.0f, 1.6f);
    glVertex2f(1.5f, 1.2f);
    glEnd();

    // Flame – orange mid
    glColor3ub(255, 165, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.6f, 1.2f);
    glVertex2f(1.0f, 1.4f);
    glVertex2f(1.4f, 1.2f);
    glEnd();

    // Flame – red inner
    glColor3ub(255, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(0.8f, 1.2f);
    glVertex2f(1.0f, 1.3f);
    glVertex2f(1.2f, 1.2f);
    glEnd();

    glPopMatrix();

    // grain field .....................................

    drawGrainField(70.0f, 25.0f,
        30.0f, 15.0f);

    //------------ grass field

    //hill 1............................-------------


    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(91, 131, 109);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(55.0f, 56.0f);
    glVertex2f(45.0f, 58.0f);
    glVertex2f(33.0f, 60.0f);
    glVertex2f(22.0f, 61.2f);
    glVertex2f(14.0f, 62.0f);
    glVertex2f(8.0f, 64.0f);
    glVertex2f(0.0f, 65.0f);

    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(91, 131, 109);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 65.0f);
    glVertex2f(94.0f, 64.5f);
    glVertex2f(85.0f, 63.0f);
    glVertex2f(76.0f, 60.0f);
    glVertex2f(70.0f, 59.0f);
    glVertex2f(65.0f, 57.0f);
    glVertex2f(55.0f, 56.0f);

    glEnd();

    //----------------------------------------------------------------------------------------

    ntree();
    //tree 2

    glPushMatrix(); // Save current matrix

    glTranslatef(73.0f, 32.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();

    glPopMatrix(); // Restore original matrix

    //tree 3

    glPushMatrix(); // Save current matrix

    glTranslatef(65.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();

    glPopMatrix();

    //tree4

    glPushMatrix(); // Save current matrix

    glTranslatef(93.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 5

    glPushMatrix(); // Save current matrix

    glTranslatef(40.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 6

    glPushMatrix(); // Save current matrix

    glTranslatef(33.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();
    glPopMatrix();

    //water-----------------------------------

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(71.0f, 23.0f);
    glVertex2f(100.0f, 42.0f);
    glVertex2f(100.0f, 44.0f);
    glVertex2f(71.0f, 25.0f);

    glEnd();

    drawRiverRipple(0.0f, 62.0f,   // x0, x1
        19.0f, 19.0f);

    //waterfan --------------------------------------------------------

    waterwheel();

    //-----------water...

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(62.0f, 16.0f);
    glVertex2f(67.0f, 16.0f);
    glVertex2f(62.0f, 20.5f);

    glEnd();

    // Cloud 1
    glPushMatrix();
    glTranslatef(_moveC, 4, 0);
    drawCircle_N(10.0f, 65.0f, 2.0f, 128, 178, 177);
    drawCircle_N(12.0f, 67.0f, 1.8f, 128, 178, 177);
    drawCircle_N(14.0f, 65.0f, 2.0f, 128, 178, 177);
    drawCircle_N(12.0f, 63.0f, 1.6f, 128, 178, 177);
    drawCircle_N(16.0f, 65.0f, 1.8f, 128, 178, 177);
    drawCircle_N(15.0f, 63.0f, 1.5f, 128, 178, 177);
    drawCircle_N(15.0f, 67.0f, 1.5f, 128, 178, 177);

    glPopMatrix();

    // --- Cloud 2: x≈45…51, y≈70 ---
    glColor3ub(255, 255, 255);        // white puffs
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(45.0f, 70.0f, 2.5f, 128, 178, 177);
    drawCircle_N(47.0f, 72.0f, 2.2f, 128, 178, 177);
    drawCircle_N(49.0f, 70.0f, 2.5f, 128, 178, 177);
    drawCircle_N(47.0f, 68.0f, 2.0f, 128, 178, 177);
    glPopMatrix();

    //plane---------
    glPushMatrix();
    ndrawPlane();
    glPopMatrix();

    // --- Cloud 3: x≈75…81, y≈68 ---
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(75.0f, 68.0f, 2.3f, 128, 178, 177);
    drawCircle_N(77.0f, 70.0f, 2.0f, 128, 178, 177);
    drawCircle_N(79.0f, 68.0f, 2.3f, 128, 178, 177);
    drawCircle_N(77.0f, 66.0f, 1.9f, 128, 178, 177);
    glPopMatrix();

    // wave---------------------------------------------

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        13.0f, 13.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        8.0f, 8.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        3.0f, 3.0f);

    //grass...........

    drawGrassClump(5.0f, 25.0f, 60); drawGrassClump(2.0f, 25.0f, 60); drawGrassClump(8.0f, 25.0f, 60);
    drawGrassClump(11.0f, 25.0f, 60); drawGrassClump(14.0f, 25.0f, 60); drawGrassClump(17.0f, 25.0f, 60);
    drawGrassClump(20.0f, 25.0f, 60); drawGrassClump(23.0f, 25.0f, 60);   drawGrassClump(26.0f, 25.0f, 60);
    drawGrassClump(29.0f, 25.0f, 60);    drawGrassClump(32.0f, 25.0f, 60);    drawGrassClump(33.0f, 25.0f, 60);

    drawGrassClump(70.0f, 17.0f, 60);
    drawGrassClump(73.0f, 17.0f, 60);drawGrassClump(76.0f, 17.0f, 60);drawGrassClump(79.0f, 17.0f, 60);
    drawGrassClump(82.0f, 17.0f, 60);drawGrassClump(85.0f, 17.0f, 60);drawGrassClump(88.0f, 17.0f, 60);
    drawGrassClump(91.0f, 17.0f, 60);drawGrassClump(94.0f, 17.0f, 60);drawGrassClump(97.0f, 17.0f, 60);

    drawGrass(5, 35); drawGrass(10, 35); drawGrass(14, 40); drawGrass(20, 33); drawGrass(25, 38); drawGrass(30, 35); drawGrass(30, 40);

    drawGrass(80, 45); drawGrass(85, 43); drawGrass(90, 46); drawGrass(73, 47);

    //boat-----

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveA, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(75.0f, 10.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(2.6f, 2.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);
    nboat();
    glPopMatrix();

    // boat-2 motion right → left, scaled so its original base from x=[17→22], y=[0→...]

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveB, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(15.0f, 1.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(3.6f, 3.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);

    nboat();

    glBegin(GL_QUADS);
    glColor3ub(255, 99, 71);
    glVertex2f(20.5f, 1.5f);
    glVertex2f(21.0f, 3.5f);
    glVertex2f(18.5f, 3.5f);
    glVertex2f(18.0f, 1.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(19.8f, 3.5f);
    glVertex2f(19.8f, 4.0f);
    glVertex2f(19.7f, 4.0f);
    glVertex2f(19.7f, 3.5f);
    glEnd();

    glPopMatrix();

    drawWindmill();

    //==============--------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0f, 0.0f, 0.0f, 0.3f); // Black overlay with 30% darkness
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(100.0f, 100.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();

    glDisable(GL_BLEND);
    glutSwapBuffers();
}

void update4(int value) {

    _moveA += speed;
    if (_moveA > 90)
    {
        _moveA = -90;
    }

    if (_moveB > +95) {
        _moveB = -90;
    }
    _moveB += 0.15;
    if (_moveC > +95) {
        _moveC = -90;
    }
    _moveC += 0.04;
//kite logic

  //  kiteOffset += kiteSpeed;

 //  if (kiteOffset > maxX) {
   //kiteOffset = maxX;
    //kiteSpeed = -kiteSpeed;
    //}
    //else if (kiteOffset < minX) {
    //kiteOffset = minX;
    //kiteSpeed = -kiteSpeed;

//}

//kite logic 2 left to right
    kiteOffset += kiteSpeed;

    // Reverse at boundaries
    if (kiteOffset > maxX) {
        kiteOffset = maxX;
        kiteSpeed = -kiteSpeed;
    }
    else if (kiteOffset < minX) {
        kiteOffset = minX;
        kiteSpeed = -kiteSpeed;
    }

    // --- Ripple effect update ---
    updateRipple();

    // --- Wheel rotation logic ---
    if (rotating) {
        wheelAngle -= speed1;
        if (wheelAngle <= targetAngle) {
            wheelAngle = targetAngle;
            rotating = false;
        }
    }

    angle -= 2.0f;
    if (angle > 360.0)
    {
        angle -= 360;
    }

    planeX_N -= planeSpeed;
    if (planeX_N < -30.0f) planeX_N = 120.0f;

    // --- Redraw the scene ---
    glutPostRedisplay();

    // --- Set timer again ---
    glutTimerFunc(20, update4, 0);
}

void drawRainDayScene1_N() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glColor3ub(61, 100, 153);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 80.0f);
    glVertex2f(0.0f, 80.0f);
    glEnd();

    //sun -----------------
    // Left soil (green, arbitrary shape)
    glColor3ub(155, 188, 84);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 25.0f);
    glVertex2f(34.0f, 25.0f);
    glVertex2f(40.0f, 29.0f);
    glVertex2f(31.0f, 31.0f);
    glVertex2f(52.0f, 40.0f);
    glVertex2f(41.0f, 48.0f);
    glVertex2f(47.0f, 51.0f);
    glVertex2f(40.0f, 55.0f);
    glVertex2f(0.0f, 55.0f);
    glEnd();

    // Right soil (green, via a fan)
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(155, 188, 84);        glVertex2f(73.0f, 44.0f);
    glVertex2f(58.0f, 24.0f);        // fan origin
    glVertex2f(67.0f, 16.0f);
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(64.0f, 55.0f);

    glEnd();

    // Brown “side‐face” under that slope (C→D→B→A)

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(58.0f, 24.0f);   // D
    glVertex2f(67.0f, 16.0f);
    glVertex2f(68.0f, 17.0f);// B
    glVertex2f(59.0f, 25.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(67.0f, 16.0f);   // D
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 17.0f);// B
    glVertex2f(68.0f, 17.0f);   // A

    glEnd();

    //brus------------------

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(222, 204, 87);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(34.0f, 43.0f);
    glVertex2f(34.0f, 45.0f);
    glVertex2f(32.0f, 47.0f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(24.0f, 47.0f);

    glEnd();
    glLineWidth(5.0f);

    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw the wide line
    glBegin(GL_LINES);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 51.0f);
    glEnd();


    ///house on left side///
    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.0f, 46.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(14.0f, 50.0f);

    glEnd();

    //polygon 2
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(17.0f, 46.0f);
    glVertex2f(25.0f, 46.0f);
    glVertex2f(22.0f, 50.0f);
    glVertex2f(14.0f, 50.0f);

    glEnd();

    //polygon 3
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(205, 133, 63);
    glVertex2f(14.0f, 50.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(12.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 4
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(24.0f, 46.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 5
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.5f, 42.0f);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(12.0f, 43.0f);

    glEnd();

    //polygon 6
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(25.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);

    glEnd();

    //polygon 7
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();

    ///door:left
    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(0, 0, 0);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();

    //polygon b
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(19.0f, 42.2f);
    glVertex2f(20.5f, 42.5f);
    glVertex2f(20.5f, 45.0f);
    glVertex2f(19.0f, 45.0f);

    glEnd();

    // house 3
    // --- Tiny House (scaled ~50%, around 25,50) ---
    // Roof left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 52.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Roof right
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 52.5f);
    glVertex2f(32.0f, 52.5f);
    glVertex2f(30.5f, 54.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Main wall
    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 54.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(25.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Front wall
    glColor3ub(128, 135, 32);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(31.5f, 52.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Base trim left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.25f, 50.5f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(25.5f, 51.0f);
    glEnd();

    // Base trim right
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(32.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glEnd();

    // Small roof detail
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door panel (black)
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door frame
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, 50.6f);
    glVertex2f(29.75f, 50.75f);
    glVertex2f(29.75f, 52.0f);
    glVertex2f(29.0f, 52.0f);
    glEnd();

    //house 4
    // Roof left
    glColor3ub(105, 105, 105);  // dark gray
    glBegin(GL_POLYGON);
    glVertex2f(15.0f, 53.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 53.0f);
    glVertex2f(22.0f, 53.0f);
    glVertex2f(20.5f, 55.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(173, 216, 230);  // light blue
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 55.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(15.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(107, 142, 35);  // olive green
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(21.5f, 53.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);  // chocolate
    glBegin(GL_POLYGON);
    glVertex2f(15.25f, 51.0f);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(15.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);  // gold
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(22.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door panel (brown)
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(19.0f, 51.1f);
    glVertex2f(19.75f, 51.25f);
    glVertex2f(19.75f, 52.5f);
    glVertex2f(19.0f, 52.5f);
    glEnd();

    //house2.....

    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(105, 105, 105);
    glVertex2f(17.0f, 50.0f);
    glVertex2f(26.0f, 50.0f);
    glVertex2f(24.0f, 52.0f);
    glVertex2f(19.0f, 52.0f);


    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(24.0f, 47.0f);
    glVertex2f(25.0f, 48.0f);
    glVertex2f(25.0f, 50.0f);
    glVertex2f(22.0f, 50.0f);

    glEnd();

    //right

    // --- Tiny House at (85,50) ---
    // Roof left
    glPushMatrix();
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, 0.0f);  // shift everything left by 9

    // Roof left
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();
    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();
    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();

    glPopMatrix();

    // ——— Fireplace ———---------------------------------------------
    glPushMatrix();
    glTranslatef(35.0f, 45.0f, 0.0f);
    glScalef(2.5f, 2.5f, 1.0f);

    // Fireplace opening
    glColor3ub(30, 30, 30);   // almost black
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(1.7f, 0.3f);
    glVertex2f(1.7f, 1.2f);
    glVertex2f(0.3f, 1.2f);
    glEnd();

    glPopMatrix();

    // grain field .....................................

    drawGrainField(70.0f, 25.0f,
        30.0f, 15.0f);

    //------------ grass field

    //hill 1............................-------------

    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(47, 74, 46);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(55.0f, 56.0f);
    glVertex2f(45.0f, 58.0f);
    glVertex2f(33.0f, 60.0f);
    glVertex2f(22.0f, 61.2f);
    glVertex2f(14.0f, 62.0f);
    glVertex2f(8.0f, 64.0f);
    glVertex2f(0.0f, 65.0f);

    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(47, 74, 46);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 65.0f);
    glVertex2f(94.0f, 64.5f);
    glVertex2f(85.0f, 63.0f);
    glVertex2f(76.0f, 60.0f);
    glVertex2f(70.0f, 59.0f);
    glVertex2f(65.0f, 57.0f);
    glVertex2f(55.0f, 56.0f);

    glEnd();

    ntree();
    //tree 2

    glPushMatrix(); // Save current matrix

    glTranslatef(73.0f, 32.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();

    glPopMatrix(); // Restore original matrix

    //tree 3

    glPushMatrix(); // Save current matrix

    glTranslatef(65.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();

    glPopMatrix();

    //tree4

    glPushMatrix(); // Save current matrix

    glTranslatef(93.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 5

    glPushMatrix(); // Save current matrix

    glTranslatef(40.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 6

    glPushMatrix(); // Save current matrix

    glTranslatef(33.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();
    glPopMatrix();

    //water-----------------------------------

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(71.0f, 23.0f);
    glVertex2f(100.0f, 42.0f);
    glVertex2f(100.0f, 44.0f);
    glVertex2f(71.0f, 25.0f);

    glEnd();

    drawRiverRipple(0.0f, 62.0f,   // x0, x1
        19.0f, 19.0f);

    //waterwheel --------------------------------------------------------

    waterwheel();

    //-----------water...

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(62.0f, 16.0f);
    glVertex2f(67.0f, 16.0f);
    glVertex2f(62.0f, 20.5f);

    glEnd();

    // Cloud 1
    glPushMatrix();
    glTranslatef(_moveC, 4, 0);
    drawCircle_N(10.0f, 65.0f, 2.0f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(12.0f, 67.0f, 1.8f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(14.0f, 65.0f, 2.0f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(12.0f, 63.0f, 1.6f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(16.0f, 65.0f, 1.8f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(15.0f, 63.0f, 1.5f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(15.0f, 67.0f, 1.5f, 0.725f, 0.765f, 0.8f);

    glPopMatrix();

    glColor3ub(255, 255, 255);        // white puffs
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(45.0f, 70.0f, 2.5f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(47.0f, 72.0f, 2.2f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(49.0f, 70.0f, 2.5f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(47.0f, 68.0f, 2.0f, 0.725f, 0.765f, 0.8f);
    glPopMatrix();

    //plane---------
    glPushMatrix();
    ndrawPlane();
    glPopMatrix();

    // --- Cloud 3: x≈75…81, y≈68 ---
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(75.0f, 68.0f, 2.3f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(77.0f, 70.0f, 2.0f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(79.0f, 68.0f, 2.3f, 0.725f, 0.765f, 0.8f);
    drawCircle_N(77.0f, 66.0f, 1.9f, 0.725f, 0.765f, 0.8f);
    glPopMatrix();

    // wave---------------------------------------------

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        13.0f, 13.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        8.0f, 8.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        3.0f, 3.0f);

    //grass...........

    drawGrassClump(5.0f, 25.0f, 60); drawGrassClump(2.0f, 25.0f, 60); drawGrassClump(8.0f, 25.0f, 60);
    drawGrassClump(11.0f, 25.0f, 60); drawGrassClump(14.0f, 25.0f, 60); drawGrassClump(17.0f, 25.0f, 60);
    drawGrassClump(20.0f, 25.0f, 60); drawGrassClump(23.0f, 25.0f, 60);   drawGrassClump(26.0f, 25.0f, 60);
    drawGrassClump(29.0f, 25.0f, 60);    drawGrassClump(32.0f, 25.0f, 60);    drawGrassClump(33.0f, 25.0f, 60);

    drawGrassClump(70.0f, 17.0f, 60);
    drawGrassClump(73.0f, 17.0f, 60);drawGrassClump(76.0f, 17.0f, 60);drawGrassClump(79.0f, 17.0f, 60);
    drawGrassClump(82.0f, 17.0f, 60);drawGrassClump(85.0f, 17.0f, 60);drawGrassClump(88.0f, 17.0f, 60);
    drawGrassClump(91.0f, 17.0f, 60);drawGrassClump(94.0f, 17.0f, 60);drawGrassClump(97.0f, 17.0f, 60);

    drawGrass(5, 35); drawGrass(10, 35); drawGrass(14, 40); drawGrass(20, 33); drawGrass(25, 38); drawGrass(30, 35); drawGrass(30, 40);

    drawGrass(80, 45); drawGrass(85, 43); drawGrass(90, 46); drawGrass(73, 47);

    //boat-----

    //boaty1

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveA, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(75.0f, 10.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(2.6f, 2.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);
    nboat();
    glPopMatrix();
    // boat-2 motion right → left, scaled so its original base from x=[17→22], y=[0→...]

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveB, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(15.0f, 1.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(3.6f, 3.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);

    nboat();
    // 3) Red deck
    glBegin(GL_QUADS);
    glColor3ub(255, 99, 71);
    glVertex2f(20.5f, 1.5f);
    glVertex2f(21.0f, 3.5f);
    glVertex2f(18.5f, 3.5f);
    glVertex2f(18.0f, 1.5f);
    glEnd();

    // 4) Mast post
    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(19.8f, 3.5f);
    glVertex2f(19.8f, 4.0f);
    glVertex2f(19.7f, 4.0f);
    glVertex2f(19.7f, 3.5f);
    glEnd();

    glPopMatrix();
    drawWindmill();
    drawRain_J();
    drawSplash_J();
    glutSwapBuffers();
}

void drawRainNightScene1_N() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Sky (blue band)
    // Night Sky
    glColor3ub(25, 43, 60);
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 80.0f);
    glVertex2f(0.0f, 80.0f);
    glEnd();

    // Left soil (green, arbitrary shape)
    glColor3ub(155, 188, 84);
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, 25.0f);
    glVertex2f(34.0f, 25.0f);
    glVertex2f(40.0f, 29.0f);
    glVertex2f(31.0f, 31.0f);
    glVertex2f(52.0f, 40.0f);
    glVertex2f(41.0f, 48.0f);
    glVertex2f(47.0f, 51.0f);
    glVertex2f(40.0f, 55.0f);
    glVertex2f(0.0f, 55.0f);
    glEnd();

    // Right soil (green, via a fan)
    glBegin(GL_TRIANGLE_FAN);
    glColor3ub(155, 188, 84);        glVertex2f(73.0f, 44.0f);
    glVertex2f(58.0f, 24.0f);        // fan origin
    glVertex2f(67.0f, 16.0f);
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(64.0f, 55.0f);

    glEnd();

    //-----------
    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(58.0f, 24.0f);   // D
    glVertex2f(67.0f, 16.0f);
    glVertex2f(68.0f, 17.0f);// B
    glVertex2f(59.0f, 25.0f);   // A

    glEnd();

    glColor3ub(117, 86, 44);
    glBegin(GL_TRIANGLE_FAN);
    // C
    glVertex2f(67.0f, 16.0f);   // D
    glVertex2f(100.0f, 16.0f);
    glVertex2f(100.0f, 17.0f);// B
    glVertex2f(68.0f, 17.0f);   // A

    glEnd();

    //brus------------------

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(222, 204, 87);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(34.0f, 43.0f);
    glVertex2f(34.0f, 45.0f);
    glVertex2f(32.0f, 47.0f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(24.0f, 47.0f);

    glEnd();

    glLineWidth(5.0f);

    glColor3f(0.0f, 0.0f, 0.0f);

    // Draw the wide line
    glBegin(GL_LINES);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 51.0f);
    glEnd();

    ///house on left side///
    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.0f, 46.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(14.0f, 50.0f);
    glEnd();

    //polygon 2
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(17.0f, 46.0f);
    glVertex2f(25.0f, 46.0f);
    glVertex2f(22.0f, 50.0f);
    glVertex2f(14.0f, 50.0f);

    glEnd();

    //polygon 3
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(205, 133, 63);
    glVertex2f(14.0f, 50.0f);
    glVertex2f(12.0f, 46.0f);
    glVertex2f(12.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 4
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(128, 135, 32);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(24.0f, 46.0f);
    glVertex2f(17.0f, 46.0f);

    glEnd();

    //polygon 5
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(11.5f, 42.0f);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(17.0f, 42.0f);
    glVertex2f(12.0f, 43.0f);

    glEnd();

    //polygon 6
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(17.0f, 41.0f);
    glVertex2f(25.0f, 42.0f);
    glVertex2f(24.0f, 43.0f);
    glVertex2f(17.0f, 42.0f);

    glEnd();

    //polygon 7
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();


    ///door:left
    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(254, 250, 71);
    glVertex2f(14.0f, 44.0f);
    glVertex2f(15.0f, 44.2f);
    glVertex2f(15.0f, 45.0f);
    glVertex2f(14.0f, 45.0f);

    glEnd();

    //polygon b
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(139, 69, 19);
    glVertex2f(19.0f, 42.2f);
    glVertex2f(20.5f, 42.5f);
    glVertex2f(20.5f, 45.0f);
    glVertex2f(19.0f, 45.0f);

    glEnd();

    // house 3

    // --- Tiny House (scaled ~50%, around 25,50) ---
    // Roof left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.0f, 52.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Roof right
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 52.5f);
    glVertex2f(32.0f, 52.5f);
    glVertex2f(30.5f, 54.5f);
    glVertex2f(26.5f, 54.5f);
    glEnd();

    // Main wall
    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 54.5f);
    glVertex2f(25.5f, 52.5f);
    glVertex2f(25.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Front wall
    glColor3ub(128, 135, 32);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(31.5f, 52.5f);
    glVertex2f(28.0f, 52.5f);
    glEnd();

    // Base trim left
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(25.25f, 50.5f);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(28.0f, 50.5f);
    glVertex2f(25.5f, 51.0f);
    glEnd();

    // Base trim right
    glColor3ub(184, 134, 11);
    glBegin(GL_POLYGON);
    glVertex2f(28.0f, 50.0f);
    glVertex2f(32.0f, 50.5f);
    glVertex2f(31.5f, 51.0f);
    glVertex2f(28.0f, 50.5f);
    glEnd();

    // Small roof detail
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door panel (black)
    glColor3ub(254, 250, 71);
    glBegin(GL_POLYGON);
    glVertex2f(26.5f, 51.5f);
    glVertex2f(27.0f, 51.6f);
    glVertex2f(27.0f, 52.0f);
    glVertex2f(26.5f, 52.0f);
    glEnd();

    // Door frame
    glColor3ub(139, 69, 19);
    glBegin(GL_POLYGON);
    glVertex2f(29.0f, 50.6f);
    glVertex2f(29.75f, 50.75f);
    glVertex2f(29.75f, 52.0f);
    glVertex2f(29.0f, 52.0f);
    glEnd();

    //house 4

    // Roof left
    glColor3ub(105, 105, 105);  // dark gray
    glBegin(GL_POLYGON);
    glVertex2f(15.0f, 53.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 53.0f);
    glVertex2f(22.0f, 53.0f);
    glVertex2f(20.5f, 55.0f);
    glVertex2f(16.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(173, 216, 230);  // light blue
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 55.0f);
    glVertex2f(15.5f, 53.0f);
    glVertex2f(15.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(107, 142, 35);  // olive green
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(21.5f, 53.0f);
    glVertex2f(18.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);  // chocolate
    glBegin(GL_POLYGON);
    glVertex2f(15.25f, 51.0f);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(18.0f, 51.0f);
    glVertex2f(15.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);  // gold
    glBegin(GL_POLYGON);
    glVertex2f(18.0f, 50.5f);
    glVertex2f(22.0f, 51.0f);
    glVertex2f(21.5f, 51.5f);
    glVertex2f(18.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(105, 105, 105);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door panel (brown)
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(16.5f, 52.0f);
    glVertex2f(17.0f, 52.1f);
    glVertex2f(17.0f, 52.5f);
    glVertex2f(16.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(19.0f, 51.1f);
    glVertex2f(19.75f, 51.25f);
    glVertex2f(19.75f, 52.5f);
    glVertex2f(19.0f, 52.5f);
    glEnd();

    //house2.....

    //polygon 1
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(105, 105, 105);
    glVertex2f(17.0f, 50.0f);
    glVertex2f(26.0f, 50.0f);
    glVertex2f(24.0f, 52.0f);
    glVertex2f(19.0f, 52.0f);

    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(184, 134, 11);
    glVertex2f(24.0f, 47.0f);
    glVertex2f(25.0f, 48.0f);
    glVertex2f(25.0f, 50.0f);
    glVertex2f(22.0f, 50.0f);

    glEnd();

    //right
    // --- Tiny House at (85,50) ---
    // Roof left
    glPushMatrix();
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();

    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();

    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();

    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();

    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();

    // Door frame
    glColor3ub(70, 70, 70);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-6.0f, 0.0f, 0.0f);  // shift everything left by 9

    // Roof left
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(85.0f, 53.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Roof right
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 53.0f);
    glVertex2f(93.0f, 53.0f);
    glVertex2f(91.5f, 55.0f);
    glVertex2f(86.5f, 55.0f);
    glEnd();
    // Main wall
    glColor3ub(245, 222, 179);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 55.0f);
    glVertex2f(85.5f, 53.0f);
    glVertex2f(85.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Front wall
    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(92.5f, 53.0f);
    glVertex2f(89.0f, 53.0f);
    glEnd();
    // Base trim left
    glColor3ub(210, 105, 30);
    glBegin(GL_POLYGON);
    glVertex2f(85.25f, 51.0f);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(89.0f, 51.0f);
    glVertex2f(85.5f, 51.5f);
    glEnd();
    // Base trim right
    glColor3ub(218, 165, 32);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 50.5f);
    glVertex2f(93.0f, 51.0f);
    glVertex2f(92.5f, 51.5f);
    glVertex2f(89.0f, 51.0f);
    glEnd();
    // Small roof detail
    glColor3ub(169, 28, 10);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door panel
    glColor3ub(101, 67, 33);
    glBegin(GL_POLYGON);
    glVertex2f(86.5f, 52.0f);
    glVertex2f(87.0f, 52.1f);
    glVertex2f(87.0f, 52.5f);
    glVertex2f(86.5f, 52.5f);
    glEnd();
    // Door frame
    glColor3ub(254, 250, 71);
    glBegin(GL_POLYGON);
    glVertex2f(89.0f, 51.1f);
    glVertex2f(89.75f, 51.25f);
    glVertex2f(89.75f, 52.5f);
    glVertex2f(89.0f, 52.5f);
    glEnd();

    glPopMatrix();

    // ——— Fireplace ———---------------------------------------------
    glPushMatrix();
    glTranslatef(35.0f, 45.0f, 0.0f);
    glScalef(2.5f, 2.5f, 1.0f);

    // Fireplace opening
    glColor3ub(30, 30, 30);   // almost black
    glBegin(GL_POLYGON);
    glVertex2f(0.3f, 0.3f);
    glVertex2f(1.7f, 0.3f);
    glVertex2f(1.7f, 1.2f);
    glVertex2f(0.3f, 1.2f);
    glEnd();

    glPopMatrix();

    drawGrainField(70.0f, 25.0f,
        30.0f, 15.0f);

    //------------ grass field

    //hill 1............................-------------

    //polygon a
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(91, 131, 109);
    glVertex2f(0.0f, 55.0f);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(55.0f, 56.0f);
    glVertex2f(45.0f, 58.0f);
    glVertex2f(33.0f, 60.0f);
    glVertex2f(22.0f, 61.2f);
    glVertex2f(14.0f, 62.0f);
    glVertex2f(8.0f, 64.0f);
    glVertex2f(0.0f, 65.0f);

    glEnd();

    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
    glColor3ub(91, 131, 109);
    glVertex2f(55.0f, 55.0f);
    glVertex2f(100.0f, 55.0f);
    glVertex2f(100.0f, 65.0f);
    glVertex2f(94.0f, 64.5f);
    glVertex2f(85.0f, 63.0f);
    glVertex2f(76.0f, 60.0f);
    glVertex2f(70.0f, 59.0f);
    glVertex2f(65.0f, 57.0f);
    glVertex2f(55.0f, 56.0f);

    glEnd();

    ntree();
    //tree 2

    glPushMatrix(); // Save current matrix

    glTranslatef(73.0f, 32.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();

    glPopMatrix(); // Restore original matrix

    //tree 3

    glPushMatrix(); // Save current matrix

    glTranslatef(65.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();

    glPopMatrix();

    //tree4

    glPushMatrix(); // Save current matrix

    glTranslatef(93.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 5

    glPushMatrix(); // Save current matrix

    glTranslatef(40.0f, 30.0f, 0.0f); // Move the tree to new location
    glScalef(0.5f, 0.5f, 1.0f);

    ntree();
    glPopMatrix();

    //tree 6

    glPushMatrix(); // Save current matrix

    glTranslatef(33.0f, 41.0f, 0.0f); // Move the tree to new location
    glScalef(0.3f, 0.3f, 1.0f);

    ntree();
    glPopMatrix();

    //water-----------------------------------

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(71.0f, 23.0f);
    glVertex2f(100.0f, 42.0f);
    glVertex2f(100.0f, 44.0f);
    glVertex2f(71.0f, 25.0f);
    glEnd();

    drawRiverRipple(0.0f, 62.0f,   // x0, x1
        19.0f, 19.0f);

    //waterfan --------------------------------------------------------

    waterwheel();

    //-----------water...

    glBegin(GL_POLYGON);
    glColor3ub(81, 144, 168);
    glVertex2f(62.0f, 16.0f);
    glVertex2f(67.0f, 16.0f);
    glVertex2f(62.0f, 20.5f);

    glEnd();

    // Cloud 1
    glPushMatrix();
    glTranslatef(_moveC, 4, 0);
    drawCircle_N(10.0f, 65.0f, 2.0f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(12.0f, 67.0f, 1.8f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(14.0f, 65.0f, 2.0f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(12.0f, 63.0f, 1.6f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(16.0f, 65.0f, 1.8f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(15.0f, 63.0f, 1.5f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(15.0f, 67.0f, 1.5f, 0.157f, 0.275f, 0.369f);

    glPopMatrix();

    // --- Cloud 2: x≈45…51, y≈70 ---
    glColor3ub(255, 255, 255);        // white puffs
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(45.0f, 70.0f, 2.5f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(47.0f, 72.0f, 2.2f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(49.0f, 70.0f, 2.5f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(47.0f, 68.0f, 2.0f, 0.157f, 0.275f, 0.369f);
    glPopMatrix();

    //plane---------
    glPushMatrix();
    ndrawPlane();
    glPopMatrix();

    // --- Cloud 3: x≈75…81, y≈68 ---
    glColor3ub(255, 255, 255);
    glPushMatrix();
    glTranslatef(_moveC, 0.0f, 0.0f);
    drawCircle_N(75.0f, 68.0f, 2.3f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(77.0f, 70.0f, 2.0f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(79.0f, 68.0f, 2.3f, 0.157f, 0.275f, 0.369f);
    drawCircle_N(77.0f, 66.0f, 1.9f, 0.157f, 0.275f, 0.369f);
    glPopMatrix();

    // wave---------------------------------------------

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        13.0f, 13.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        8.0f, 8.0f);

    drawRiverRipple(0.0f, 100.0f,   // x0, x1
        3.0f, 3.0f);

    //grass...........

    drawGrassClump(5.0f, 25.0f, 60); drawGrassClump(2.0f, 25.0f, 60); drawGrassClump(8.0f, 25.0f, 60);
    drawGrassClump(11.0f, 25.0f, 60); drawGrassClump(14.0f, 25.0f, 60); drawGrassClump(17.0f, 25.0f, 60);
    drawGrassClump(20.0f, 25.0f, 60); drawGrassClump(23.0f, 25.0f, 60);   drawGrassClump(26.0f, 25.0f, 60);
    drawGrassClump(29.0f, 25.0f, 60);    drawGrassClump(32.0f, 25.0f, 60);    drawGrassClump(33.0f, 25.0f, 60);

    drawGrassClump(70.0f, 17.0f, 60);
    drawGrassClump(73.0f, 17.0f, 60);drawGrassClump(76.0f, 17.0f, 60);drawGrassClump(79.0f, 17.0f, 60);
    drawGrassClump(82.0f, 17.0f, 60);drawGrassClump(85.0f, 17.0f, 60);drawGrassClump(88.0f, 17.0f, 60);
    drawGrassClump(91.0f, 17.0f, 60);drawGrassClump(94.0f, 17.0f, 60);drawGrassClump(97.0f, 17.0f, 60);

    drawGrass(5, 35); drawGrass(10, 35); drawGrass(14, 40); drawGrass(20, 33); drawGrass(25, 38); drawGrass(30, 35); drawGrass(30, 40);

    drawGrass(80, 45); drawGrass(85, 43); drawGrass(90, 46); drawGrass(73, 47);

    //boat-----

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveA, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(75.0f, 10.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(2.6f, 2.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);
    nboat();
    glPopMatrix();

    // boat-2 motion right → left, scaled so its original base from x=[17→22], y=[0→...]

    glPushMatrix();
    // horizontal animation
    glTranslatef(_moveB, 0.0f, 0.0f);

    // 1) move the original base-left (17,0) → (15,12)
    glTranslatef(15.0f, 1.0f, 0.0f);
    // 2) scale so width 22−17 = 5 → 33−15 = 18  ⇒ scale = 18/5 = 3.6
    glScalef(3.6f, 3.6f, 1.0f);
    // 3) shift original coords so (17,0) becomes the new origin
    glTranslatef(-17.0f, 0.0f, 0.0f);

    nboat();

    glBegin(GL_QUADS);
    glColor3ub(255, 99, 71);
    glVertex2f(20.5f, 1.5f);
    glVertex2f(21.0f, 3.5f);
    glVertex2f(18.5f, 3.5f);
    glVertex2f(18.0f, 1.5f);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(139, 69, 19);
    glVertex2f(19.8f, 3.5f);
    glVertex2f(19.8f, 4.0f);
    glVertex2f(19.7f, 4.0f);
    glVertex2f(19.7f, 3.5f);
    glEnd();
    glPopMatrix();

    drawWindmill();

    //==============--------------------

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.0f, 0.0f, 0.0f, 0.3f); // Black overlay with 30% darkness
    glBegin(GL_QUADS);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(100.0f, 0.0f);
    glVertex2f(100.0f, 100.0f);
    glVertex2f(0.0f, 100.0f);
    glEnd();

    glDisable(GL_BLEND);
    drawRain();
    drawSplashes();

    glutSwapBuffers();
}

// ================= End Ishrak =================

void display() {

    if (Fuad) {
        glClearColor(0.5, 0.5, 0.5, 1.0); // City scene background
    }
    else if (Azim) {
        glClearColor(0.9725f, 0.4980f, 0.1373f, 1.0f); // Beach scene background
    }
    else if (Mahfuzur) {
        glClearColor(0.5, 0.5, 0.5, 1.0);
    }
    else if (Ishrak) {
        glClearColor(0.3176f, 0.5647f, 0.6588f, 1.0f);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    //===================Fuad================================

    if (isNight && !isRaining && Fuad) {
        drawNightScene();
    }

    else if (isNight && isRaining && Fuad) {
        drawNightRainScene();
    }

    else if (!isNight && isRaining && Fuad) {
        drawDayRainScene();
    }

    else if (Fuad) {
        drawDayScene();
    }

    //===================Mahfuzur================================

    if (isNight && !isRaining && Mahfuzur) {
        drawScene1_A();
    }

    else if (isNight && isRaining && Mahfuzur) {
        drawNightRainScene_A();
    }

    else if (!isNight && isRaining && Mahfuzur) {
        drawDayRainScene_A();
    }

    else if (Mahfuzur) {
        drawScene_A();
    }

    //===================Azim================================

    if (isNight_J && !isRaining_J && Azim) {
        drawNightScene_J();
    }

    else if (isNight_J && isRaining_J && Azim) {
        drawRainNightScene_J();
    }

    else if (!isNight_J && isRaining_J && Azim) {
        drawRainDayScene_J();
    }

    else if (Azim) {
        drawDayScene_J();
    }


    //===================Ishrak================================

    if (isNight && !isRaining && Ishrak) {
        drawScene2_N();
    }

    else if (isNight && isRaining && Ishrak) {
        drawRainNightScene1_N();
    }

    else if (!isNight && isRaining && Ishrak) {
        drawRainDayScene1_N();
    }


    else if (Ishrak) {
        drawScene_N();
    }

}

void initRendering() {
    //glEnable(GL_DEPTH_TEST); // Enable depth testing for 3D
    if (Fuad) {
        glClearColor(0.5, 0.5, 0.5, 0.5); // Set background to gray
    }
    else if (Azim) {
        glClearColor(0.9725f, 0.4980f, 0.1373f, 1.0f);
    }
    else if (Mahfuzur) {
        glClearColor(0.5, 0.5, 0.5, 0.5);
    }
    else if (Ishrak) {
        glClearColor(0.3176f, 0.5647f, 0.6588f, 1.0f);
    }

}

void handleResize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (Fuad) {
        gluOrtho2D(0.0, 100.0, 0.0, 90.0);
    }
    else if (Azim) {
        gluOrtho2D(0.0, 100.0, 0.0, 80.0);
    }
    else if (Mahfuzur) {
        gluOrtho2D(0.0, 100.0, 0.0, 80.0);
    }
    else if (Ishrak) {
        gluOrtho2D(0.0, 100.0, 0.0, 80.0);
    }

    glMatrixMode(GL_MODELVIEW);
}

// Add key & mouse function
void handleKeypress(unsigned char key, int x, int y) {

    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);

    if (Fuad) {
        switch (key) {
        case 'n':
        case 'N':
            isNight = true;
            nightLight = true;
            sound_f();
            glutPostRedisplay();
            break;

        case 'd':
        case 'D':
            isNight = false;
            nightLight = false;
            glutPostRedisplay();
            break;

        case 'r':
        case 'R':
            isRaining = true;
            glutPostRedisplay();
            break;

        case 's':
        case 'S':
            isRaining = false;
            glutPostRedisplay();
            break;

        case '+':
            rainSpeed += 0.1f;
            if (rainSpeed > 5.0f) rainSpeed = 5.0f;
            break;

        case '-':
            rainSpeed -= 0.1f;
            if (rainSpeed < 0.1f) rainSpeed = 0.1f;
            break;

        case '1':
            cloudSpeed = maxCloudSpeed;
            planeSpeed = planeSpeed * 2;

            trainSpeed = trainSpeed * 2;
            planeSpeed2 = planeSpeed2 * 2;
            boatSpeed = 0.3f * 4;
            carSpeed1 = 0.5 * 5;
            carSpeed2 = -0.4f * 2;
            carSpeed3 = 0.6f * 3;
            carSpeed4 = -0.5f * 4;
            break;

        case '2':
            cloudSpeed = minCloudSpeed;
            planeSpeed = planeSpeed / 2;
            cloudSpeed = normalCloudSpeed * 0.5f;

            trainSpeed = trainSpeed / 2;
            planeSpeed2 = planeSpeed2 / 2;
            boatSpeed = 0.3f / 4;
            carSpeed1 = 0.5 / 5;
            carSpeed2 = -0.4f / 2;
            carSpeed3 = 0.6f / 3;
            carSpeed4 = -0.5f / 4;
            break;

        case '3':
            cloudSpeed = normalCloudSpeed;
            planeSpeed = 0.2f * 2;

            trainSpeed = -0.15f * 2;
            planeSpeed2 = 0.4;
            boatSpeed = 0.3f;
            carSpeed1 = 0.5;
            carSpeed2 = -0.4f;
            carSpeed3 = 0.6f;
            carSpeed4 = -0.5f;
            rainSpeed = 0.6;
            break;

        case 'A': // New key for Azim
            Azim = true;
            Fuad = false;
            Mahfuzur = false;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 45.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'M': // New key for Mahfuzur
            Azim = false;
            Fuad = false;
            Mahfuzur = true;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 55.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'I': // New key for Ishrak
            Azim = false;
            Fuad = false;
            Mahfuzur = false;
            Ishrak = true;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 55.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
        }
    }

    else if (Azim) {
        switch (key) {
        case 'n':
        case 'N':
            isNight_J = true;
            sound_a();
            glutPostRedisplay();
            break;

        case 'd':
        case 'D':
            isNight_J = false;
            glutPostRedisplay();
            break;

        case 'r':
        case 'R':
            isRaining_J = true;
            glutTimerFunc(30, updatetree_J, 0);
            glutPostRedisplay();
            break;

        case 's':
        case 'S':
            isRaining_J = false;
            glutPostRedisplay();
            break;

        case '+':
            rainSpeed += 0.1f;
            if (rainSpeed > 5.0f) rainSpeed = 5.0f;
            break;

        case '-':
            rainSpeed -= 0.1f;
            if (rainSpeed < 0.1f) rainSpeed = 0.1f;
            break;

        case 'F': // New key for Fuad
            Azim = false;
            Fuad = true;
            Mahfuzur = false;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 50.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'M': // New key for Mahfuzur
            Azim = false;
            Fuad = false;
            Mahfuzur = true;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 60.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'I': // New key for Ishrak
            Azim = false;
            Fuad = false;
            Mahfuzur = false;
            Ishrak = true;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 55.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
        }
    }

    else if (Mahfuzur) {
        switch (key) {
        case 'n':
        case 'N':
            isNight = true;
            sound_m();
            glutPostRedisplay();
            break;

        case 'd':
        case 'D':
            isNight = false;
            glutPostRedisplay();
            break;

        case 's':
        case 'S':
            boatMoving = !boatMoving;
            treeSpeed1_A = 0.0f;
            break;

        case 'r':
        case 'R':
            isRaining = !isRaining;
            glutPostRedisplay();
            break;

        case '+':
            rainSpeed += 0.1f;
            if (rainSpeed > 5.0f) rainSpeed = 5.0f;
            break;

        case '-':
            rainSpeed -= 0.1f;
            if (rainSpeed < 0.1f) rainSpeed = 0.1f;
            break;

        case '0':
            rainSpeed = 0.6f;
            break;

        case 'F': // New key for Fuad
            Azim = false;
            Fuad = true;
            Mahfuzur = false;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 50.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'A': // New key for Azim
            Azim = true;
            Fuad = false;
            Mahfuzur = false;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 45.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'I': // New key for Ishrak
            Azim = false;
            Fuad = false;
            Mahfuzur = false;
            Ishrak = true;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 55.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
        }
    }

    else if (Ishrak) {

        if ((key == 'w' || key == 'W') && !rotating) {
            targetAngle = wheelAngle - 360.0f;
            rotating = true;
        }

        switch (key) {
        case 'n':
        case 'N':
            isNight = true;
            sound_i();
            glutPostRedisplay();
            break;

        case 'd':
        case 'D':
            isNight = false;
            glutPostRedisplay();
            break;

        case 'r':
            speed = 0.02f;
            planeSpeed = 0.4;
            rainSpeed = 0.6;
            break;

        case 'R':
            isRaining = true;
            glutPostRedisplay();
            break;

        case 's':
            speed = 0.0f;
            break;

        case 'S':
            isRaining = false;
            glutPostRedisplay();
            break;

        case '+':
            rainSpeed += 0.1f;
            if (rainSpeed > 5.0f) rainSpeed = 5.0f;
            break;

        case '-':
            rainSpeed -= 0.1f;
            if (rainSpeed < 0.1f) rainSpeed = 0.1f;
            break;

        case 'A': // New key for Azim
            Azim = true;
            Fuad = false;
            Mahfuzur = false;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 45.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'M': // New key for Mahfuzur
            Azim = false;
            Fuad = false;
            Mahfuzur = true;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 55.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 'F': // New key for Fuad
            Azim = false;
            Fuad = true;
            Mahfuzur = false;
            Ishrak = false;
            rainTargetYMin = 0.0f;
            rainTargetYMax = 50.0f;
            handleResize(w, h);
            glutPostRedisplay();
            break;

        case 27:
            exit(0);
        }
    }
}

// Mouse Handler Function
void handleMouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN) {
        if (button == GLUT_RIGHT_BUTTON) {
            // Increase speed for all elements (make faster)
            cloudSpeed     *= 2.0f;  // Double speed
            planeSpeed     *= 2.0f;
            planeSpeed2    *= 2.0f;
            boatSpeed      *= 2.0f;
            carSpeed1      *= 2.0f;
            carSpeed2      *= 2.0f;
            carSpeed3      *= 2.0f;
            carSpeed4      *= 2.0f;
            trainSpeed     *= 2.0f;
            ShipSpeed_J    *= 2.0f;

            std::cout << "Antar, Azim, Ishrak, Mahfuz → Speed Doubled (Right Click)" << std::endl;
        }
        else if (button == GLUT_LEFT_BUTTON) {
            // Decrease speed for all elements (slower)
            cloudSpeed     *= 0.5f;  // Half speed
            planeSpeed     *= 0.5f;
            planeSpeed2    *= 0.5f;
            boatSpeed      *= 0.5f;
            carSpeed1      *= 0.5f;
            carSpeed2      *= 0.5f;
            carSpeed3      *= 0.5f;
            carSpeed4      *= 0.5f;
            trainSpeed     *= 0.5f;
            ShipSpeed_J    *= 0.5f;

            std::cout << "Antar, Azim, Ishrak, Mahfuz → Speed Halved (Left Click)" << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("Four_Shades_of_Living_City_Coastal_Village_&_Wilderness");

    glutDisplayFunc(display);         // Use the new display function
    glutKeyboardFunc(handleKeypress); // Register key handler
   glutMouseFunc(handleMouse);

 // Register mouse handler
    glutReshapeFunc(handleResize);
    glutTimerFunc(0, updateClouds, 0);
    glutTimerFunc(0, updateRain, 0);
    glutTimerFunc(0, updatePlane, 0);

    glutTimerFunc(0, updateTrain, 0);
    glutTimerFunc(0, updateBoat, 0);
    glutTimerFunc(0, updateCars, 0);
    updateLightning(0);
    updateLightning2(0);


    //===================Mahfuzur=======================
    glutTimerFunc(0, update, 0);
    glutTimerFunc(0, updatetree_A, 0);


    //===================Azim=======================
    glutTimerFunc(0, updateClouds_J, 0);
    glutTimerFunc(0, updatePlane_J, 0);
    glutTimerFunc(0, updatetree_J, 0);
    glutTimerFunc(0, updateShip_J, 0);

    //===================Ishrak=======================
    glutTimerFunc(20, update4, 0);
    glutTimerFunc(0, updateRain_J, 0);


    glutMainLoop();
    return 0;//done
}
