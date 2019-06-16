#include "raylib.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// gcc main.c -o out.a -lraylib -lX11

#define DEBUG

#define SWIDTH 1000
#define SHEIGHT 1000

Camera3D setupCamera();

int main(){
	
	InitWindow(SWIDTH, SHEIGHT, "BattleZone");

	Camera3D cam = setupCamera();
	SetCameraMode(cam, CAMERA_FIRST_PERSON);
	SetTargetFPS(60);

	//TODO load tank model
	Model wireframeTank = LoadModel("res/model/tank_textured.obj");

	while(!WindowShouldClose()){

		UpdateCamera(&cam);

		//TODO check intersection between center of viewport and enemy tank

		BeginDrawing();

			ClearBackground(BLACK);

			BeginMode3D(cam);

				//TODO draw 3d stuff
				DrawModelWires(wireframeTank, (Vector3){0.0f, 0.0f, 0.0f}, 10.0f, GREEN);

				//DrawBoundingBox(MeshBoundingBox(wireframeTank

			EndMode3D();

			#ifdef DEBUG
				DrawFPS(10,10);
			#endif

		EndDrawing();
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
