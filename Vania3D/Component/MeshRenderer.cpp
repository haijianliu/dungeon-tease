
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
MeshRenderer::MeshRenderer() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
MeshRenderer::~MeshRenderer() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void MeshRenderer::start() {
	// get main camera from the scene
	this->camera = this->gameObject->scene->mainCamera;
	// initialize static shader uniforms before rendering
	for (unsigned int i = 0; i < this->materials.size(); i++)
		this->materials[i]->setTextureUniformLocations();
}


/*------------------------------------------------------------------------------
< render shadow >
------------------------------------------------------------------------------*/
void MeshRenderer::renderShadow() {
	// model
	this->gameObject->getComponent<Transform>()->setUniform(this->game->shadowMapping->shader);
	// pose
	this->model->setPoseUniform(this->game->shadowMapping->shader);
	// draw
	for (unsigned int i = 0; i < this->model->meshes.size(); i++) {
		glBindVertexArray(this->model->meshes[i]->vao);
		this->model->meshes[i]->draw();
		glBindVertexArray(0);
	}

}
