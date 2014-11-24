#include "Renderer.h"

using namespace std;

Renderer::Renderer()
	: 
{

}


Renderer::~Renderer()
{
	
}


void initOpenGL(int w, int h){
	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	
	glViewport(0, 0, w, h);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_FRONT);
}

void setupMatrices(){
	/*projectionMatrix = new mat4();
	projectionMatrix.m11 = y_scale;
	projectionMatrix.m22 = -((far_plane + near_plane) / frustum_length);
	projectionMatrix.m23 = -1f;
	projectionMatrix.m32 = -((2 * near_plane * far_plane) / frustum_length);
	projectionMatrix.m33 = 0f;

	// Setup view matrix
	viewMatrix = new Matrix4f();

	// Setup model matrix
	modelMatrix = new Matrix4f();

	// setup normalmatrix
	normalMatrix = new Matrix3f();

	// Create a FloatBuffer with the proper size to store our matrices later
	matrix44Buffer = BufferUtils.createFloatBuffer(16);
	matrix33Buffer = BufferUtils.createFloatBuffer(9);

	// store ProjectionMatrix once
	glUseProgram(shaders.getShaderProgram());

	projectionMatrix.store(matrix44Buffer);
	matrix44Buffer.flip();
	glUniformMatrix4(shaders.getProjectionMatLoc(), false, matrix44Buffer);

	glUseProgram(0);*/
}

void destroyGL(){

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

		avatarPositionLocation = glGetUniformLocation(shaderProgram, "avatarPos");
		avatarViewLocation = glGetUniformLocation(shaderProgram, "avatarDir");

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

	// There should be separate *.vert and *.frag shader files, but for now just hardcode those:
	const char* getVertexShader(){
		return "";
	}
	const char* getFragmentShader(){
		return "";
	}
};