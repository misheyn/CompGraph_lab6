//
// Created by Amalia on 03.11.2021.
//


//
// Created by Amalia on 17.10.2021.
//
#include "AreaFill.h"
#include <iostream>
#include <vector>
#include <gl\glut.h>

using namespace std;

#define WinW 830
#define WinH 600
#define STEP 50
int scr = 16;

int sign(double a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

void digitalToDecard(int x, int y, int &X, int &Y) {
    if (x > STEP / 2) X = x - STEP / 2;
    else
        X = -(STEP / 2 - x);
    if (y > STEP / 2) Y = -(y - STEP / 2);
    else
        Y = STEP / 2 - y;
}

void drawPixel(int x, int y, int Red, int Green, int Blue) {
    int X, Y;
    digitalToDecard(x, y, X, Y);
    double sizeX = (float) WinW / (float) STEP;
    double sizeY = (float) WinH / (float) STEP;
    glColor3d(Red, Green, Blue);
    glBegin(GL_QUADS);

    double _x = X * sizeX;
    double _y = Y * sizeY;

    glVertex2d(_x, _y);
    glVertex2d(_x + sizeX, _y);
    glVertex2d(_x + sizeX, _y + sizeY);
    glVertex2d(_x, _y + sizeY);
    glEnd();
}

void decardToDigital(int x, int y, int &X, int &Y) {
    X = (STEP / 2 + x);
    Y = (STEP / 2 - y);
}

void drawBrezehamLine(int x1, int x2, int y1, int y2, vector<vector<int>> &field) {
    int x, y, dx, dy, sx, sy;
    int X, Y;
    x = x1, y = y1;
    dx = abs(x2 - x1), dy = abs(y2 - y1);
    sx = sign(x2 - x1), sy = sign(y2 - y1);
    bool swap = false;

    if (dx < dy) {
        std::swap(dx, dy);
        swap = true;
    }
    int eps = 2 * dy - dx;
    if (sx < 0) x += sx;
    if (sy < 0) y += sy;
    for (int i = 0; i <= dx; i++) {
        decardToDigital(x, y, X, Y);
        field[X][Y] = 1;
        while (eps >= 0) {
            if (swap)
                x += sx;
            else
                y += sy;
            eps -= (2 * dx);
        }
        if (swap)
            y += sy;
        else
            x += sx;
        eps += (2 * dy);
    }
}

void fillPixel(vector<vector<int>> &field, int x, int y) {
    if (x >= 0 && x <= STEP && y >= 0 && y < STEP) {
        if (field[x][y] == 0) field[x][y] = 3;
    }
}

void fillArea(vector<vector<int>> &field) {
    for (int i = 0; i <= STEP; ++i) {
        for (int j = 0; j <= STEP; ++j) {
            if (field[i][j] == 2) {
                fillPixel(field, i, j - 1);
                fillPixel(field, i, j + 1);
                fillPixel(field, i - 1, j);
                fillPixel(field, i + 1, j);
            }
        }
    }
    for (int i = 0; i <= STEP; ++i) {
        for (int j = 0; j <= STEP; ++j) {
            if (field[i][j] == 3) field[i][j] = 2;
        }
    }
}

void drawField(vector<vector<int>> &field) {

    for (int i = 0; i <= STEP; ++i) {
        for (int j = 0; j <= STEP; ++j) {
            if (field[i][j] == 1) {
                drawPixel(i, j, 0, 0, 0);
            }
            if (field[i][j] == 2) {
                drawPixel(i, j, 1, 1, 0);
            }
        }

    }
}

void drawPolygon(vector<vector<int>> &coords, vector<vector<int>> &field) {
    for (int i = 0; i < coords.size() - 1; ++i) {
        drawBrezehamLine(coords[i][0], coords[i + 1][0], coords[i][1], coords[i + 1][1], field);
    }
    drawBrezehamLine(coords[0][0], coords[coords.size() - 1][0], coords[0][1], coords[coords.size() - 1][1], field);
}

void drawGrid() {
    glLineWidth(1);
    glColor3d(0, 0, 0);
    for (float i = -STEP; i < STEP; ++i) {
        glBegin(GL_LINES);
        glVertex2d(i * WinW / (float) STEP, -WinH);
        glVertex2d(i * WinW / (float) STEP, WinH);
        glEnd();
    }
    for (float i = -STEP; i < STEP; ++i) {
        glBegin(GL_LINES);
        glVertex2d(-WinW, i * WinH / (float) STEP);
        glVertex2d(WinW, i * WinH / (float) STEP);
        glEnd();
    }

    glLineWidth(3);
    glColor3d(256, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(-WinW, 0);
    glVertex2f(WinW, 0);
    glVertex2f(0, WinH);
    glVertex2f(0, -WinH);
    glEnd();
}

vector<vector<int>> field;

void display() {

    static int start = 1;
    if (start == 1) {
        start = 0;
        field.resize(STEP + 1);
        for (int i = 0; i < STEP + 1; ++i) {
            field[i].resize(STEP + 1);
        }
        field[25][35] = 2;
    }
    vector<vector<int>> coords1{{-16, 16},
                                {16,  16},
                                {16,  -16},
                                {-16, -16}};
    vector<vector<int>> coords2{{0,   10},
                                {-10, -8},
                                {10,  -8}};
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    drawPolygon(coords1, field);
    drawPolygon(coords2, field);
    fillArea(field);
    drawField(field);
    drawGrid();
    glPopMatrix();
    glutSwapBuffers();
}

void timer(int value) { // timer function for cube rotation
    value = 0;
    glutPostRedisplay();  // cube drawing functions
    glutTimerFunc(100, timer, value); // timer for 5 milliseconds
}

void reshape(GLsizei Winw, GLsizei Winh) {
    glViewport(0, 0, Winw, Winh);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-Winw / 2, Winw / 2, -Winh / 2, Winh / 2, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

