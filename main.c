#include "raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// gcc main.c -o out.a -lraylib -lX11

#define DEBUG

#define SWIDTH 1000
#define SHEIGHT 1000

Camera3D setupCamera();

void drawReticle(bool isLocked);

int main(){
	
	InitWindow(SWIDTH, SHEIGHT, "BattleZone");

	Camera3D cam = setupCamera();
	SetCameraMode(cam, CAMERA_FIRST_PERSON);
	SetTargetFPS(60);

	//TODO load tank model
	Model wireframeTank = LoadModel("res/model/tank_textured.obj");

	//TODO make the camera faster, with no sine step or whatever
	//also remove camera turning

	while(!WindowShouldClose()){

		UpdateCamera(&cam);

		//TODO check intersection between center of viewport and enemy tank

		BeginDrawing();

			ClearBackground(BLACK);

			BeginMode3D(cam);

				//background horizon
				DrawCircle3D(cam.position/*(Vector3){0.0f, 0.0f, 0.0f}*/, 100.0f, (Vector3){1.0f, 0.0f, 0.0f}, 90.0f, GREEN);

				//TODO draw 3d stuff
				DrawModelWires(wireframeTank, (Vector3){0.0f, 0.0f, 0.0f}, 10.0f, GREEN);

				//DrawBoundingBox(MeshBoundingBox(wireframeTank

			EndMode3D();

			drawReticle(true);

			#ifdef DEBUG
				DrawFPS(10,10);
			#endif

		EndDrawing();
	}

}

void drawReticle(bool isLocked){
	//draw common parts

	//upper T
	//vertical
	DrawLine(SWIDTH/2, SHEIGHT/4, SWIDTH/2, SHEIGHT/2-50, GREEN);
	//horizontal
	DrawLine(SWIDTH/2-50, SHEIGHT/2-50, SWIDTH/2+50, SHEIGHT/2-50, GREEN);

	//lower T
	//vertical
	DrawLine(SWIDTH/2, SHEIGHT/4*3, SWIDTH/2, SHEIGHT/2+50, GREEN);
	//horizontal
	DrawLine(SWIDTH/2-50, SHEIGHT/2+50, SWIDTH/2+50, SHEIGHT/2+50, GREEN);

	if(isLocked){
		//left top
		DrawLine(SWIDTH/2-50, SHEIGHT/2-50, SWIDTH/2-25, SHEIGHT/2-25, GREEN);
		//right top
		DrawLine(SWIDTH/2+50, SHEIGHT/2-50, SWIDTH/2+25, SHEIGHT/2-25, GREEN);

		//left bottom
		DrawLine(SWIDTH/2-50, SHEIGHT/2+50, SWIDTH/2-25, SHEIGHT/2+25, GREEN);
		//right bottom
		DrawLine(SWIDTH/2+50, SHEIGHT/2+50, SWIDTH/2+25, SHEIGHT/2+25, GREEN);
	}else{
		//left top
		DrawLine(SWIDTH/2-50, SHEIGHT/2-50, SWIDTH/2-50, SHEIGHT/2-25, GREEN);
		//right top
		DrawLine(SWIDTH/2+50, SHEIGHT/2-50, SWIDTH/2+50, SHEIGHT/2-25, GREEN);

		//left bottom
		DrawLine(SWIDTH/2-50, SHEIGHT/2+50, SWIDTH/2-50, SHEIGHT/2+25, GREEN);
		//right bottom
		DrawLine(SWIDTH/2+50, SHEIGHT/2+50, SWIDTH/2+50, SHEIGHT/2+25, GREEN);
	}
}

Camera3D setupCamera(){
	Camera3D camera = {0};
	camera.position = (Vector3){-20.0f, 10.0f, -20.0f};
	camera.target = (Vector3){0.0f, 0.0f, 0.0f};
	camera.up = (Vector3){0.0f, 1.0f, 0.0f};
	camera.fovy = 45.0f;
	camera.type = CAMERA_PERSPECTIVE;

	return camera;
}
