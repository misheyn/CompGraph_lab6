//
// Created by Amalia on 03.11.2021.
//

#ifndef COMPGRAPH_LAB6_AREAFILL_H
#define COMPGRAPH_LAB6_AREAFILL_H

#include <GL/gl.h>
#include <vector>

using namespace std;

int sign(double a);

void drawPixel(int x, int y, int Red, int Green, int Blue);

void drawField(vector<vector<int>> &field);

void drawBrezehamLine(int x1, int x2, int y1, int y2, vector<vector<int>> &field);

void drawPolygon(vector<vector<int>> &coords, vector<vector<int>> &field);

void drawGrid();

void fillPixel(vector<vector<int>> &field, int x, int y);

void digitalToDecard(int x, int y, int &X, int &Y);

void decardToDigital(int x, int y, int &X, int &Y);

void fillArea(vector<vector<int>> &field);

void timer(int value);

void display();

void reshape(GLsizei Winw, GLsizei Winh);

#endif //COMPGRAPH_LAB6_AREAFILL_H
