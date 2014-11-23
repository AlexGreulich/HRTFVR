#include "SceneManager.h"
#include <vector>

using namespace std;

/*
Load models, populate scene and update graph every frame
*/


std::vector<int> sceneObjects;

SceneManager::SceneManager()
{
	
}


SceneManager::~SceneManager()
{
}

void SceneManager::renderScene(){

}


class ShaderSetup{

	
	int vertexShader = 0;
	int fragmentShader = 0;
	int shaderProgram = 0;

	int projectionMatrixLocation = 0;
	int viewMatrixLocation = 0;
	int modelMatrixLocation = 0;

	int texLocation = 0;

	int avatarPositionLocation = 0;
	int avatarViewLocation = 0;


	void init(){
	
		const char* vert = "loadMe";//openShaderSource(new File ("src/Resources/shader/PerPixelNormal.vert"));
		const char* frag = "loadMe";//openShaderSource(new File ("src / Resources / shader / PerPixelNormal.frag"));
			
		 //Vertex shader
		vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vert, NULL);
		glCompileShader(vertexShader);
		
		/*
		String vertexShaderErrorLog = glGetShaderInfoLog(vertexShader, 65536);
		if (vertexShaderErrorLog.length() != 0) {System.err.println("Vertex shader compile log: \n" + vertexShaderErrorLog);}
		*/

		//Fragment shader
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &frag, NULL);
		glCompileShader(fragmentShader);
		
		/*
		String fragmentShaderErrorLog = glGetShaderInfoLog(fragmentShader, 65536);
		if (fragmentShaderErrorLog.length() != 0) {System.err.println("Fragment shader compile log: \n" + fragmentShaderErrorLog);}
			
		*/
		//Shader program
		shaderProgram = glCreateProgram();
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);		

		glBindAttribLocation(shaderProgram, 0, "in_Position");
		
		// Texture -> attribute 1
		glBindAttribLocation(shaderProgram, 1, "in_TextureCoord");
			
		glLinkProgram(shaderProgram);
		glValidateProgram(shaderProgram);
		
		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		
		// Get uniform locations
		projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
		viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
		modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
		
		avatarPositionLocation = glGetUniformLocation(shaderProgram, "playerpos");
		avatarViewLocation = glGetUniformLocation(shaderProgram, "pviewdir");
		
		texLocation = glGetUniformLocation(shaderProgram, "tex0");
	
			
		glUseProgram(shaderProgram);
		glUniform1i(texLocation, 0);
	
		glUseProgram(0);
	
		/*
		String log = glGetProgramInfoLog(shaderProgram, 65536);
		if (log.length() != 0) {
			System.err.println("Program link log:\n" + log);
		}
		*/
	}

	void destroyShaders(){
		glDetachShader(shaderProgram, vertexShader);
		glDetachShader(shaderProgram, fragmentShader);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}

	// Getter
	int getProjMatrixLoc(){
		return projectionMatrixLocation;
	}	
	int getModelMatrixLoc(){
		return modelMatrixLocation;
	}
	int getViewMatrixLoc(){
		return viewMatrixLocation;
	}
	int getTexLoc(){
		return texLocation;
	}
	int getAvatarPosLoc(){
		return avatarPositionLocation;
	}
	int getAvatarVieLoc(){
		return avatarViewLocation;
	}
};