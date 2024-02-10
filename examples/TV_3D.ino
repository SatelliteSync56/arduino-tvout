/********************************************
 * 3D models were converted using bitluni's *
 * STL conversion tool:                     *
 *           https://bitluni.net/esp32-vga  *
 ********************************************/
#include <TVout_FB.h>
#include "crate_bulge.h"

#define DOTS 16
#define FACES 42

TVout_FB TV;

float xRot;
float yRot;
float zRot;

float fov = 2;

bool edgeDir = false;

void zrotate(float q) {
  
}

int zOff = 150;
int xOff = 0;
int yOff = 0;
int cSize = 50;
int view_plane = 64;
float angle = PI/60;

void setup() {
  // put your setup code here, to run once:
  TV.begin(NTSC,128,96);
  TV.delay(1000);
  view_plane *= fov;
}

void loop() {
  // put your main code here, to run repeatedly:
  TV.clear_screen();
  draw3DEdges(object::vertices, object::edges);
  TV.synchro();
  TV.delay_frame(1);
  zRot += angle/2;
  //xRot = PI*1.2;
  yRot += angle;
}

void draw3D(const float verts[DOTS][3], const unsigned short tris[FACES][3]) {
  float model2D[DOTS][2];
  float model[DOTS][3];
  for(byte i = 0; i < DOTS; i++) {
    model[i][0] = verts[i][0];
    model[i][1] = verts[i][1];
    model[i][2] = verts[i][2];
  }
  float tx,ty,temp;
  for(byte i = 0; i < DOTS; i++) {
    tx = model[i][0] - xOff;
    ty = model[i][1] - yOff;
    temp = tx * cos(zRot) - ty * sin(zRot);
    ty = tx * sin(zRot) + ty * cos(zRot);
    tx = temp;
    model[i][0] = tx + xOff;
    model[i][1] = ty + yOff;
  }
  for(byte i = 0; i < DOTS; i++) {
    model[i][2] += 4;
    model2D[i][0] = (unsigned char)((model[i][0] * view_plane / (model[i][2])) + (TV.hres()/2));
    model2D[i][1] = (unsigned char)((model[i][1] * view_plane / (model[i][2])) + (TV.vres()/2));
  }
  for(byte i = 0; i < FACES; i++) {
    TV.draw_line(model2D[tris[i][0]][0],model2D[tris[i][0]][1],model2D[tris[i][1]][0],model2D[tris[i][1]][1],WHITE);
    TV.draw_line(model2D[tris[i][1]][0],model2D[tris[i][1]][1],model2D[tris[i][2]][0],model2D[tris[i][2]][1],WHITE);
    TV.draw_line(model2D[tris[i][2]][0],model2D[tris[i][2]][1],model2D[tris[i][0]][0],model2D[tris[i][0]][1],WHITE);
  }
}

void draw3DEdges(const float verts[DOTS][3], const unsigned short tris[FACES][2]) {
  float model2D[DOTS][2];
  float model[DOTS][3];
  for(byte i = 0; i < DOTS; i++) {
    model[i][0] = verts[i][0];
    model[i][1] = verts[i][1];
    model[i][2] = verts[i][2];
  }
  float tx,ty,tz,temp;
  if (zRot != 0) {
  for(byte i = 0; i < DOTS; i++) {
    tx = model[i][0] - xOff;
    ty = model[i][1] - yOff;
    temp = tx * cos(zRot) - ty * sin(zRot);
    ty = tx * sin(zRot) + ty * cos(zRot);
    tx = temp;
    model[i][0] = tx + xOff;
    model[i][1] = ty + yOff;
  }
  }
  if (yRot != 0) {
  for(byte i = 0; i < DOTS; i++) {
    tx = model[i][0] - xOff;
    ty = model[i][2] - yOff;
    temp = tx * cos(yRot) - ty * sin(yRot);
    ty = tx * sin(yRot) + ty * cos(yRot);
    tx = temp;
    model[i][0] = tx + xOff;
    model[i][2] = ty + yOff;
  }
  }
  if (xRot != 0) {
  for(byte i = 0; i < DOTS; i++) {
    tx = model[i][1] - xOff;
    ty = model[i][2] - yOff;
    temp = tx * cos(xRot) - ty * sin(xRot);
    ty = tx * sin(xRot) + ty * cos(xRot);
    tx = temp;
    model[i][1] = tx + xOff;
    model[i][2] = ty + yOff;
  }
  }
  for(byte i = 0; i < DOTS; i++) {
    model[i][2] += fov*1.2;
    model2D[i][0] = (unsigned char)((model[i][0] * view_plane / (model[i][2])) + (TV.hres()/2));
    model2D[i][1] = (unsigned char)((model[i][1] * view_plane / (model[i][2])) + (TV.vres()/2));
  }
  /*
  if (edgeDir) {
    edgeDir = false;
    for(byte i = 0; i < FACES; i++) {
      TV.draw_line(model2D[tris[i][0]][0],model2D[tris[i][0]][1],model2D[tris[i][1]][0],model2D[tris[i][1]][1],WHITE);
      //TV.delay_frame(1);
    }
  } else {
    edgeDir = true;
    */
    for(byte i = 0; i < FACES; i++) {
      TV.draw_line(model2D[tris[i][0]][0],model2D[tris[i][0]][1],model2D[tris[i][1]][0],model2D[tris[i][1]][1],WHITE);
      //TV.delay_frame(1);
    }
  //}
}
