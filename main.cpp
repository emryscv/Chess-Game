#include <iostream>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "UI/UI.h";
#include "UI/Texture.h";
#include "UI/shaderClass.h";
#include "UI/VAO.h";
#include "UI/VBO.h";
#include "UI/EBO.h";

#include "Engine/Game.h"


GLfloat vertices[] =
{ //    COORDINATES      / TEX COORD /
	 -1.0f,  -1.0f, 0.0f, 0.0f, 0.0f, // Lower left corner
	 -1.0f, -0.75f, 0.0f, 0.0f, 1.0f, // Lower right corner
	-0.75f, -0.75f, 0.0f, 1.0f, 1.0f, // Upper corner
	-0.75f,  -1.0f, 0.0f, 1.0f, 0.0f, // Inner left
	 };

GLuint indices[] =
{
	0, 2, 1, // Upper triangle
	0, 3, 2, // Upper triangle
};

int main() {
	double mouseX;
	double mouseY;

	int originX;
	int originY;

	int destinationX;
	int destinationY;

	int promoteOption = -1;

	bool isDragging = false;

	UI ui(vertices, sizeof(vertices), indices, sizeof(indices));
	Game game;
	ui.GenerateBoardRepresentation(game.GetBoard());

	//Render loop
	while (!glfwWindowShouldClose(ui.window()))
	{
		auto start = std::chrono::high_resolution_clock::now();

		ui.PrintBoard();
		if (game.GetPromotePawn()) {
			ui.PrintPromoteMenu(destinationX, 0, game.GetTurn());
			if (promoteOption != -1) {
				std::cout << "Common common turn the radio on!\n";
				game.PromotePawn(destinationX, destinationY, promoteOption + 1);
				promoteOption = -1;
				game.AfterMove();
				ui.GenerateBoardRepresentation(game.GetBoard());
			}
		}

		if (glfwGetMouseButton(ui.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			glfwSetInputMode(ui.window(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			glfwGetCursorPos(ui.window(), &mouseX, &mouseY);

			//std::cout << mouseX << " " << mouseY << "\n";

			if (game.GetPromotePawn()) {
				std::cout << mouseX / 100 << " " << (int)(mouseY / 100) << "\n";
				if ((int)(mouseX / 100) == destinationX and (int) (mouseY / 100) >= 0 and (int)(mouseY / 100) <= 3) {
					promoteOption = mouseY / 100;
					std::cout << "YES!!!!\n";
				}
			}
			else if (!isDragging and game.IsValidPiece(mouseX / 100, mouseY / 100)) {
				isDragging = true;
				originX = mouseX / 100;
				originY = mouseY / 100;
				ui.SetMovingPiece(mouseX, mouseY);
			}

			if (isDragging) { 
				ui.UpdatePosition(mouseX, mouseY); 
			}
		}

		if (glfwGetMouseButton(ui.window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
			glfwSetInputMode(ui.window(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			if (isDragging) {
				glfwGetCursorPos(ui.window(), &mouseX, &mouseY);

				destinationX = mouseX/ 100;
				destinationY = mouseY/ 100;
				
				if (game.IsAValidMove(originX, originY, destinationX, destinationY)) {
					game.Move(originX, originY, destinationX, destinationY);
					
					if (!game.GetPromotePawn()) {
						game.AfterMove();
					}

					ui.GenerateBoardRepresentation(game.GetBoard());
					ui.UnsetMovingPiece();
				}
				else {
					ui.UnsetMovingPiece(originX, originY);
				}
			}
			isDragging = false;
		}

		glfwSwapBuffers(ui.window());
		glfwPollEvents();

		auto end = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		//std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
	}

	ui.DeleteTextures();

	return 0;
}