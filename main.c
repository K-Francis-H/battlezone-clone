#include "raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// gcc main.c -o out.a -lraylib -lX11

#define DEBUG

#define SWIDTH 1000	//GetMonitorWidth(0)
#define SHEIGHT 1000	//GetMonitorHeight(0)

Camera3D setupCamera();

void drawReticle(bool isLocked);

Vector3 scaleVector3(Vector3 v, float scale);
Vector3 translateVector3(Vector3 v, float xOff, float yOff, float zOff);

Ray getEyeRay(Camera3D* cam){
	return (Ray){cam->position, cam->target}; 
}

//TODO macrotize
Ray getCenterScreenRay(int screenWidth, int screenHeight, Camera3D cam){
	return GetMouseRay((Vector2){screenWidth/2, screenHeight/2}, cam);
}

int main(){
	
	InitWindow(SWIDTH, SHEIGHT, "BattleZone");
	//ToggleFullscreen();

	Camera3D cam = setupCamera();
	SetCameraMode(cam, CAMERA_FIRST_PERSON);
	SetTargetFPS(60);

	//TODO load tank model
	Model wireframeTank = LoadModel("res/model/tank_textured.obj");
	BoundingBox tankBox = MeshBoundingBox(wireframeTank.meshes[0]);

	tankBox.min = scaleVector3(tankBox.min, 10.0f);
	tankBox.max = scaleVector3(tankBox.max, 10.0f);
	tankBox.min = translateVector3(tankBox.min, 0.0f, 0.0f, 0.0f);
	tankBox.max = translateVector3(tankBox.max, 0.0f, 0.0f, 0.0f);

	//TODO make the camera faster, with no sine step or whatever
	//also remove camera turning

	while(!WindowShouldClose()){

		UpdateCamera(&cam);

		//printf("Position: %f %f %f\n", cam.position.x, cam.position.y, cam.position.z);
		//printf("Target: %f %f %f\n", cam.target.x, cam.target.y, cam.target.z);

		//TODO check intersection between center of viewport and enemy tank

		BeginDrawing();

			ClearBackground(BLACK);

			BeginMode3D(cam);

				DrawGrid(100, 1.0f);

				//background horizon
				DrawCircle3D(cam.position/*(Vector3){0.0f, 0.0f, 0.0f}*/, 100.0f, (Vector3){1.0f, 0.0f, 0.0f}, 90.0f, GREEN);

				//TODO draw 3d stuff
				DrawModelWires(wireframeTank, (Vector3){0.0f, 0.0f, 0.0f}, 10.0f, GREEN);

				DrawBoundingBox(tankBox, RED);

				//DrawBoundingBox(MeshBoundingBox(wireframeTank

				Ray eyeRay = getCenterScreenRay(SWIDTH, SHEIGHT, cam);

			EndMode3D();

			drawReticle(
				CheckCollisionRayBox(eyeRay, tankBox)
			);

			#ifdef DEBUG
				DrawFPS(10,10);
			#endif

		EndDrawing();
	}

}

Vector3 scaleVector3(Vector3 v, float scale){
	v.x *= scale;
	v.y *= scale;
	v.z *= scale;
	return v;
}

Vector3 translateVector3(Vector3 v, float xOff, float yOff, float zOff){
	v.x += xOff;
	v.y += yOff;
	v.z += zOff;
	return v;
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
