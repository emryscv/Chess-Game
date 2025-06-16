#include "UI.h";

UI::UI(GLfloat* vertices, GLsizeiptr vSize, GLuint* indices, GLsizeiptr iSize)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mWindow = glfwCreateWindow(800, 800, "Chess Game", NULL, NULL);

	if (mWindow == NULL) {
		std::cout << "Falied to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(mWindow);

	gladLoadGL();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glViewport(0, 0, 800, 800);

	mBoardShaderProgram = Shader("UI/Shaders/default.vert", "UI/Shaders/color.frag");
	mPiecesShaderProgram = Shader("UI/Shaders/default.vert", "UI/Shaders/default.frag");
	
	mSquareVAO = VAO(true);
	mSquareVBO = VBO(vertices, vSize);
	mSquareEBO = EBO(indices, iSize);

	mSquareVAO.LinkAttrib(mSquareVBO, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
	mSquareVAO.LinkAttrib(mSquareVBO, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	mSquareVAO.Unbind();
	mSquareVBO.Unbind();
	mSquareEBO.Unbind();

	mBoardTransform = glGetUniformLocation(mBoardShaderProgram.ID, "transform");
	mBoardAColor = glGetUniformLocation(mBoardShaderProgram.ID, "aColor");

	mPieceTransform = glGetUniformLocation(mPiecesShaderProgram.ID, "transform");
	mPieceAColor = glGetUniformLocation(mPiecesShaderProgram.ID, "aColor");
	LoadTextures();
	glDisable(GL_DEPTH_TEST);
}

UI::~UI()
{
	mSquareVAO.Delete();
	mSquareVBO.Delete();
	mSquareEBO.Delete();
	mPiecesShaderProgram.Delete();

	glfwDestroyWindow(mWindow);
	glfwTerminate();
}

void UI::PrintBoard()
{
	glClearColor(0.93f, 0.93f, 0.82f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	mBoardShaderProgram.Activate();
	mSquareVAO.Bind();

	glm::mat4 trans = glm::mat4(1.0f);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i + j) % 2 == 0) {
				glUniform4f(mBoardAColor, 0.46f, 0.59f, 0.34f, 1.0f);
				glUniformMatrix4fv(mBoardTransform, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			trans = glm::translate(trans, glm::vec3(0.25f, 0.0f, 0.0f));
		}
		trans = glm::translate(trans, glm::vec3(-2.0f, 0.25f, 0.0f));
	}

	trans = glm::translate(trans, glm::vec3(0.0f, -2.0f, 0.0f));

	mPiecesShaderProgram.Activate();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (mBoardRepresentation[i][j].first != 0) {
				mTextures[mBoardRepresentation[i][j].first].Bind();
				if (mBoardRepresentation[i][j].second) {
					glUniform4f(mPieceAColor, 1.0f, 1.0f, 1.0f, 1.0f);
				}
				else {
					glUniform4f(mPieceAColor, 0.0f, 0.0f, 0.0f, 1.0f);
				}
				trans = glm::mat4(1.0f);
				trans = glm::translate(trans, glm::vec3(j * 0.25f, (7 - i) * 0.25f, 0.0f));
				glUniformMatrix4fv(mPieceTransform, 1, GL_FALSE, glm::value_ptr(trans));
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
		}
	}
	//Move the piece
	if (mMovingPiece.representation != 0) {
		std::cout << mMovingPiece.x << " " << mMovingPiece.y << " " << (float) mMovingPiece.x / 400.0f << " " << 2.0f - (float) mMovingPiece.y / 400.0f << "\n";
		
		float x = (float)mMovingPiece.x / 400.0f - 0.125;
		float y = 2.0f - (float)mMovingPiece.y / 400.0f - 0.125;
		
		if (x < 0) x = 0;
		else if (x > 1.75) x = 1.75;

		if (y < 0) y = 0;
		else if (y > 1.75) y = 1.75;

		trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
		mTextures[mMovingPiece.representation].Bind();

		if (mMovingPiece.isWhite) {
			glUniform4f(mPieceAColor, 1.0f, 1.0f, 1.0f, 1.0f);
		}
		else {
			glUniform4f(mPieceAColor, 0.0f, 0.0f, 0.0f, 1.0f);
		}
		glUniformMatrix4fv(mPieceTransform, 1, GL_FALSE, glm::value_ptr(trans));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	mSquareVAO.Unbind();
}

void UI::PrintPromoteMenu(int x, int y, Color turn)
{
	y += 4;
	mBoardShaderProgram.Activate();
	mSquareVAO.Bind();

	glUniform4f(mBoardAColor, 0.8f, 0.8f, 0.8f, 1.0f);

	glm::mat4 trans = glm::mat4(1.0f);

	trans = glm::scale(trans, glm::vec3(1.0f, 4.3f, 1.0f));
	trans = glm::translate(trans, glm::vec3(x * 0.25f, y * 0.25f, 0.0f));


	glUniformMatrix4fv(mBoardTransform, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	mPiecesShaderProgram.Activate();

	if (turn == Color::White) {
		glUniform4f(mPieceAColor, 1.0f, 1.0f, 1.0f, 1.0f);
	}
	else {
		glUniform4f(mPieceAColor, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	mTextures[5].Bind();
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x * 0.25f, (y + 3) * 0.25f, 0.0f));
	glUniformMatrix4fv(mPieceTransform, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	mTextures[4].Bind();
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x * 0.25f, (y + 2) * 0.25f, 0.0f));
	glUniformMatrix4fv(mPieceTransform, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	mTextures[3].Bind();
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x * 0.25f, (y + 1) * 0.25f, 0.0f));
	glUniformMatrix4fv(mPieceTransform, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	mTextures[2].Bind();
	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(x * 0.25f, y * 0.25f, 0.0f));
	glUniformMatrix4fv(mPieceTransform, 1, GL_FALSE, glm::value_ptr(trans));
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	mSquareVAO.Unbind();
}

void UI::LoadTextures()
{
	Texture pawn("Assets/chess_pawn.png", GL_TEXTURE_2D);
	pawn.texUnit(mPiecesShaderProgram, "text0", 0);

	Texture knight("Assets/chess_knight.png", GL_TEXTURE_2D);
	knight.texUnit(mPiecesShaderProgram, "text0", 0);

	Texture bishop("Assets/chess_bishop.png", GL_TEXTURE_2D);
	bishop.texUnit(mPiecesShaderProgram, "text0", 0);

	Texture rook("Assets/chess_rook.png", GL_TEXTURE_2D);
	rook.texUnit(mPiecesShaderProgram, "text0", 0);

	Texture queen("Assets/chess_queen.png", GL_TEXTURE_2D);
	queen.texUnit(mPiecesShaderProgram, "text0", 0);

	Texture king("Assets/chess_king.png", GL_TEXTURE_2D);
	king.texUnit(mPiecesShaderProgram, "text0", 0);

	mTextures[1] = pawn;
	mTextures[2] = knight;
	mTextures[3] = bishop;
	mTextures[4] = rook;
	mTextures[5] = queen;
	mTextures[6] = king;
}

void UI::DeleteTextures()
{
	for (int i = 1; i < 7; i++) {
		mTextures[i].Delete();
	}
}

void UI::GenerateBoardRepresentation(Piece* const(&board)[8][8])
{
	std::map<std::string, int> mapRepresentationToNumber;
	mapRepresentationToNumber["Pa"] = 1;
	mapRepresentationToNumber["Kn"] = 2;
	mapRepresentationToNumber["Bi"] = 3;
	mapRepresentationToNumber["Ro"] = 4;
	mapRepresentationToNumber["Qu"] = 5;
	mapRepresentationToNumber["Ki"] = 6;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] != nullptr) {
				mBoardRepresentation[i][j] = std::make_pair(mapRepresentationToNumber[board[i][j]->GetRepresentation()], board[i][j]->GetColor() == Color::White);
			}
			else {
				mBoardRepresentation[i][j] = std::make_pair(0, 0);
			}
		}
	}
}
