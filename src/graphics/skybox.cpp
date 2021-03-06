#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include "loadShader.h"

#include "graphics/skybox.h"
#include "graphics/glstate.h"
#include "sol.hpp"

namespace vtk {

Skybox::Skybox() {
	//xyzrgb
	float mVerts[] = {
		// front
		-1.0f,  1.0f, -1.0f,   
			1.0f,  1.0f, -1.0f,   
			1.0f, -1.0f, -1.0f,   
		-1.0f,  1.0f, -1.0f,   
			1.0f, -1.0f, -1.0f,   
		-1.0f, -1.0f, -1.0f,   

		// back
		-1.0f,  1.0f, 1.0f,   
			1.0f, -1.0f, 1.0f,  
			1.0f,  1.0f, 1.0f, 
		-1.0f,  1.0f, 1.0f,
		-1.0f, -1.0f, 1.0f, 
			1.0f, -1.0f, 1.0f,

		// left
		-1.0f,  1.0f,  1.0f,   
		-1.0f,  1.0f, -1.0f,   
		-1.0f, -1.0f, -1.0f,   
		-1.0f,  1.0f,  1.0f,   
		-1.0f, -1.0f, -1.0f,   
		-1.0f, -1.0f,  1.0f,   

		// right
			1.0f,  1.0f,  1.0f,   
			1.0f, -1.0f, -1.0f,   
			1.0f,  1.0f, -1.0f,   
			1.0f,  1.0f,  1.0f,   
			1.0f, -1.0f,  1.0f,   
			1.0f, -1.0f, -1.0f,   

		// top
		-1.0f,  1.0f,  1.0f,   
			1.0f,  1.0f,  1.0f,   
			1.0f,  1.0f, -1.0f,   
		-1.0f,  1.0f,  1.0f,   
			1.0f,  1.0f, -1.0f,   
		-1.0f,  1.0f, -1.0f,   

		// bottom
		-1.0f, -1.0f,  1.0f,   
			1.0f, -1.0f, -1.0f,   
			1.0f, -1.0f,  1.0f,   
		-1.0f, -1.0f,  1.0f,   
		-1.0f, -1.0f, -1.0f,   
			1.0f, -1.0f, -1.0f
	};

	mShader = LoadShaders("res/shaders/skybox.vert", "res/shaders/skybox.frag");
	mViewMat = glGetUniformLocation(mShader, "view");
	mProjMat = glGetUniformLocation(mShader, "proj");

	glGenVertexArrays(1, &mVao);
	glBindVertexArray(mVao);
	glGenBuffers(1, &mVbo);
	glBindBuffer(GL_ARRAY_BUFFER, mVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(mVerts), mVerts, GL_STATIC_DRAW);


	GLint posAttrib = glGetAttribLocation(mShader, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), 0);
}

void Skybox::draw(RenderTask& task) {
	auto camera = task.getCamera();
	auto viewMat = camera.getAngleMatrix();
	auto proj = camera.getProjectionMatrix();

	glUseProgram(mShader);	
	glUniformMatrix4fv(mViewMat, 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(mProjMat, 1, GL_FALSE, glm::value_ptr(proj));

	glDisable(GL_DEPTH_TEST);
	glBindVertexArray(mVao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glEnable(GL_DEPTH_TEST);
}

void Skybox::registerScriptInterface(::sol::state& lua) {
	lua.new_usertype<Skybox>("Skybox",
	                         sol::base_classes, sol::bases<Drawable>());
}

}
