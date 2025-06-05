#pragma once
#include<iostream>
#include<map>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "VAO.h";
#include "VBO.h";
#include "EBO.h";
#include "shaderClass.h"
#include "Texture.h"

#include "../Engine/Pieces/Piece.h"; //TODO quitar esto

struct MovingPiece {
	int representation;
	int x;
	int y;
	bool isWhite;
	MovingPiece() : representation(0), x(-1), y(-1), isWhite(false) {};
	MovingPiece(int representation, int x, int y, bool isWhite) : representation(representation), x(x), y(y), isWhite(isWhite) {}; //TODO try with the reference
};

class UI
{
	VBO mSquareVBO;
	EBO mSquareEBO;
	VAO mSquareVAO;

	GLuint mBoardTransform;
	GLuint mBoardAColor;

	GLuint mPieceTransform;
	GLuint mPieceAColor;

	GLFWwindow* mWindow;
	Shader mPiecesShaderProgram;
	Shader mBoardShaderProgram;

	Texture mTextures[7];
	
	std::pair<int, bool> mBoardRepresentation[8][8];

	MovingPiece mMovingPiece;

public:
	UI(GLfloat* vertices, GLsizeiptr vSize, GLuint* indices, GLsizeiptr iSize);
	~UI();

	void PrintBoard();
	void LoadTextures();
	void DeleteTextures();
	void GenerateBoardRepresentation(Piece* const(&board)[8][8]);

	void SetMovingPiece(int glX, int glY) { // TODO fix coordinates
		// converting from OpenGL coordinates to board coordinates
		int x = glX / 100; 
		int y = glY / 100;
		mMovingPiece = MovingPiece(mBoardRepresentation[y][x].first, glX, glY, mBoardRepresentation[y][x].second);
		mBoardRepresentation[y][x] = std::make_pair(0, 0);
	}

	void UpdatePosition(int glX, int glY) {
		mMovingPiece.x = glX;
		mMovingPiece.y = glY;
	}

	void UnsetMovingPiece() {
		mMovingPiece = MovingPiece();
	}
	void UnsetMovingPiece(int x, int y) {
		mBoardRepresentation[y][x] = std::make_pair(mMovingPiece.representation, mMovingPiece.isWhite);
		mMovingPiece = MovingPiece();
	}

	VAO& squareVAO() {
		return mSquareVAO;
	}

	EBO& squareEBO() {
		return mSquareEBO;
	}

	VBO& squareVBO() {
		return mSquareVBO;
	}

	GLFWwindow* window() {
		return mWindow;
	}

	Shader& piecesShaderProgram() {
		return mPiecesShaderProgram;
	}

	Shader& boardShaderProgram() {
		return mBoardShaderProgram;
	}	
};
