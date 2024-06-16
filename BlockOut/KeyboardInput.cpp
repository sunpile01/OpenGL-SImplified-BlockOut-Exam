#include <vector>

/**
* @brief Checks collision with blocks to the right of active cube
* 
* @param translationVectors - Position of all the cubes 
* @param numObjects - Number of cubes 
* 
* @return bool - If moving to the right caused a collision or not
*/
bool checkRight(std::vector<glm::vec3>& translationVectors, const int numObjects) {
	for (int i = 0; i < numObjects-1; i++) {
		//Cant check == because floats sometimes have  for example 0.150000000005. so need to add or subtract a small value
		//and check inbetween instead, therefore 6 conditions instead of 3
		if (translationVectors[numObjects - 1].x + 0.1f >= translationVectors[i].x - 0.03f &&
			translationVectors[numObjects - 1].x + 0.1f <= translationVectors[i].x + 0.03f &&
			translationVectors[numObjects-1].y   >= translationVectors[i].y - 0.03f && 
			translationVectors[numObjects - 1].y <= translationVectors[i].y + 0.03f &&
			translationVectors[numObjects-1].z >= translationVectors[i].z - 0.03f &&
			translationVectors[numObjects - 1].z <= translationVectors[i].z + 0.03f) {
			return false;
		}
	}
	return true;
}

/**
* @brief Checks collision with blocks to the left of active cube
*
* @param translationVectors - Position of all the cubes
* @param numObjects - Number of cubes
*
* @return bool - If moving to the right caused a collision or not
*/
bool checkLeft(std::vector<glm::vec3>& translationVectors, const int numObjects) {
	for (int i = 0; i < numObjects - 1; i++) {
		if (translationVectors[numObjects - 1].x - 0.1f >= translationVectors[i].x - 0.03f &&
			translationVectors[numObjects - 1].x - 0.1f <= translationVectors[i].x + 0.03f &&
			translationVectors[numObjects - 1].y >= translationVectors[i].y - 0.03f &&
			translationVectors[numObjects - 1].y <= translationVectors[i].y + 0.03f &&
			translationVectors[numObjects - 1].z >= translationVectors[i].z - 0.03f &&
			translationVectors[numObjects - 1].z <= translationVectors[i].z + 0.03f) {
			return false;
		}
	}
	return true;
}

/**
* @brief Checks collision with blocks above on the y axis of active cube
*
* @param translationVectors - Position of all the cubes
* @param numObjects - Number of cubes
*
* @return bool - If moving to the right caused a collision or not
*/
bool checkUp(std::vector<glm::vec3>& translationVectors, const int numObjects) {
	for (int i = 0; i < numObjects - 1; i++) {
		if (translationVectors[numObjects - 1].y + 0.1f >= translationVectors[i].y - 0.03f &&
			translationVectors[numObjects - 1].y + 0.1f <= translationVectors[i].y + 0.03f &&
			translationVectors[numObjects - 1].x >= translationVectors[i].x - 0.03f &&
			translationVectors[numObjects - 1].x <= translationVectors[i].x + 0.03f &&
			translationVectors[numObjects - 1].z >= translationVectors[i].z - 0.03f &&
			translationVectors[numObjects - 1].z <= translationVectors[i].z + 0.03f) {
			return false;
		}
	}
	return true;
}

/**
* @brief Checks collision with blocks one down on the y axis of active cube
*
* @param translationVectors - Position of all the cubes
* @param numObjects - Number of cubes
*
* @return bool - If moving to the right caused a collision or not
*/
bool checkDown(std::vector<glm::vec3>& translationVectors, const int numObjects) {
	for (int i = 0; i < numObjects - 1; i++) {
		if (translationVectors[numObjects - 1].y - 0.1f >= translationVectors[i].y - 0.03f &&
			translationVectors[numObjects - 1].y - 0.1f <= translationVectors[i].y + 0.03f &&
			translationVectors[numObjects - 1].x >= translationVectors[i].x - 0.03f &&
			translationVectors[numObjects - 1].x <= translationVectors[i].x + 0.03f &&
			translationVectors[numObjects - 1].z >= translationVectors[i].z - 0.03f &&
			translationVectors[numObjects - 1].z <= translationVectors[i].z + 0.03f) {
			return false;
		}
	}
	return true;
}

/**
* @brief Process the keyboard input
*
* @param window - the window for the application
* @param keyPressed - whether a key has been pressed or not
* @param setTextures - Toggling textures on and off
* @param setLight - Toggling the light on and off
* @param cubeMoved - If a cube was moved or not
* @param translationVectors - Position of all the cubes
* @param translationMatrices - All the translation matrices for the cubes
* @param numObjects - Number of cubes
*/
static void keyBoardInput(GLFWwindow* window, bool& keyPressed, int& setTextures, int& setLight, bool& cubeMoved,
		std::vector<glm::vec3>& translationVectors, std::vector<glm::mat4>& translationMatrices, const int numObjects) {	

	float sizeOfMove = 1.0f / 10.0f;							//Size of move on the x and y axis
	//Same approach for DOWN, LEFT, RIGHT and X keys just checking different boundaries and axis
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (translationVectors[numObjects - 1].y < 0.5f - sizeOfMove
			&& checkUp(translationVectors, numObjects)) {		//Not out of bounds and not colliding with other blocks
			translationVectors[numObjects - 1].y += sizeOfMove;			//Change the translation vector of the cube
			translationMatrices[numObjects - 1] = glm::translate(glm::mat4(1.0f),  //update matrix of the cube
				glm::vec3(translationVectors[numObjects - 1]));
			cubeMoved = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (translationVectors[numObjects - 1].y > 0.0f + sizeOfMove
			&& checkDown(translationVectors, numObjects)) {
			translationVectors[numObjects - 1].y -= sizeOfMove;
			translationMatrices[numObjects - 1] = glm::translate(glm::mat4(1.0f),
				glm::vec3(translationVectors[numObjects - 1]));
			cubeMoved = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (translationVectors[numObjects - 1].x > -0.25f + sizeOfMove
			&&checkLeft(translationVectors, numObjects)) {
			translationVectors[numObjects - 1].x -= sizeOfMove;
			translationMatrices[numObjects - 1] = glm::translate(glm::mat4(1.0f),
				glm::vec3(translationVectors[numObjects - 1]));
		}
		cubeMoved = true;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (translationVectors[numObjects - 1].x < 0.25f - sizeOfMove
			&& checkRight(translationVectors, numObjects)) {
			translationVectors[numObjects - 1].x += sizeOfMove;
			translationMatrices[numObjects - 1] = glm::translate(glm::mat4(1.0f),
				glm::vec3(translationVectors[numObjects - 1]));
			cubeMoved = true;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (translationVectors[numObjects - 1].z > -0.5f + sizeOfMove) {
			translationVectors[numObjects - 1].z -= sizeOfMove;
			translationMatrices[numObjects - 1] = glm::translate(glm::mat4(1.0f),
				glm::vec3(translationVectors[numObjects - 1]));
		}
		cubeMoved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		bool cubeUnderneath = false;											
		for (int i = 0; i < numObjects - 1; i++) {		
			//Checks if there is a cube underneath the active cube
			if (translationVectors[numObjects - 1].x == translationVectors[i].x && 
					translationVectors[numObjects - 1].y == translationVectors[i].y) 
			{
				//Always one above the highest z value cube with the same x and y, 
				//since the highest z value will also be the last vector
				translationVectors[numObjects - 1].z = translationVectors[i].z + sizeOfMove; 
				translationMatrices[numObjects - 1] = glm::translate(glm::mat4(1.0f),
										glm::vec3(translationVectors[numObjects - 1]));
				cubeMoved = true;
				cubeUnderneath = true;
			}
		}
		//Not cube underneath move the cube to the lowest level
		if (!cubeUnderneath) {
			translationVectors[numObjects - 1].z = 0.5f - (sizeOfMove * 9) - 1.0f / 20.0f;
			translationMatrices[numObjects - 1] = glm::translate(glm::mat4(1.0f),
				glm::vec3(translationVectors[numObjects - 1]));
			cubeMoved = true;
		}
	}
	//Toggling the light on and off
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (setLight == 0) 
			setLight = 1;
		else 
			setLight = 0;
	}
	//Toggling the textures on and off
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && keyPressed == false) {
		keyPressed = true;
		if (setTextures == 0) 
			setTextures = 1;
		else
			setTextures = 0;
	}
	//Check if no key is being pressed, if so, set pressed to false
	//Ensures that only one keyInput is processed per key press
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE && 
		glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_L) == GLFW_RELEASE  &&
		glfwGetKey(window, GLFW_KEY_T) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_X) == GLFW_RELEASE &&
		glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE &&
		keyPressed == true)
		keyPressed = false;
}