
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
RenderPass::RenderPass() {
	Game* game = Game::getInstance();
	// default shaders
	this->lightProbe = game->resources->getLightProbe("hdr"); game->resources->getLightProbe("hdr");
	this->shadowShader = game->resources->getShader("shadow_pass");
	this->ambientShader = game->resources->getShader("ambient_pass");
	this->lightingShader = game->resources->getShader("lighting_pass");
	this->combineShader = game->resources->getShader("renderpass_combine");
	this->ssaoShader = game->resources->getShader("ssao_pass");
}


/*------------------------------------------------------------------------------
< Desstructor >
------------------------------------------------------------------------------*/
RenderPass::~RenderPass() {

}

std::vector<glm::vec3> genSSAOKernel(unsigned int kernelSize) {

	std::vector<glm::vec3> ssaoKernel;

	std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
	std::default_random_engine generator;

	for (unsigned int i = 0; i < kernelSize; ++i) {
		glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
		sample = glm::normalize(sample);
		sample *= randomFloats(generator);
		float scale = float(i) / kernelSize;
		// scale samples s.t. they're more aligned to center of kernel
		scale = 0.1f + (1.0f - 0.1f) * scale * scale;
		sample *= scale;
		ssaoKernel.push_back(sample);
	}
	return ssaoKernel;
}

/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void RenderPass::start() {
	Game* game = Game::getInstance();
	this->quad = game->resources->quad;
	
	// hdr
	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->lightProbe->irradiance);
	glActiveTexture(GL_TEXTURE11);
	glBindTexture(GL_TEXTURE_CUBE_MAP, this->lightProbe->prefilter);
	glActiveTexture(GL_TEXTURE12);
	glBindTexture(GL_TEXTURE_2D, this->lightProbe->brdf);

	// deferred pass
	glGenFramebuffers(1, &this->deferredPass.fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->deferredPass.fbo);
	this->deferredPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT0, GL_RGB));
	this->deferredPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT1, GL_RGB16F));
	this->deferredPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT2, GL_RGB));
	this->deferredPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT3, GL_RGB16F));
	drawBuffers(4);
	createDepthAttachment(GL_DEPTH_COMPONENT24);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// fx pass
	glGenFramebuffers(1, &this->fxPass.fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->fxPass.fbo);
	this->fxPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT0, GL_RGB));
	drawBuffers(1);
	createDepthAttachment(GL_DEPTH_COMPONENT24);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ambient pass
	glGenFramebuffers(1, &this->ambientPass.fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->ambientPass.fbo);
	this->ambientPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT0, GL_RGB));
	drawBuffers(1);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->ambientShader->use();
	this->ambientShader->setInt("albedoPass", 0);
	this->ambientShader->setInt("normalPass", 1);
	this->ambientShader->setInt("mrcPass", 2);
	this->ambientShader->setInt("positionPass", 3);
	this->ambientShader->setInt("irradianceMap", 10);
	this->ambientShader->setInt("prefilterMap", 11);
	this->ambientShader->setInt("brdfLUT", 12);

	// lighting pass
	glGenFramebuffers(1, &this->lightingPass.fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->lightingPass.fbo);
	this->lightingPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT0, GL_RGB));
	drawBuffers(1);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->lightingShader->use();
	this->lightingShader->setInt("albedoPass", 0);
	this->lightingShader->setInt("normalPass", 1);
	this->lightingShader->setInt("mrcPass", 2);
	this->lightingShader->setInt("positionPass", 3);

	// shadow pass
	glGenFramebuffers(1, &this->shadowPass.fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowPass.fbo);
	this->shadowPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT0, GL_RED));
	drawBuffers(1);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->shadowShader->use();
	this->shadowShader->setInt("normalPass", 1);
	this->shadowShader->setInt("positionPass", 3);
	this->shadowShader->setInt("shadowMap", 4);

	// ssao pass
	glGenFramebuffers(1, &this->ssaoPass.fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, this->ssaoPass.fbo);
	this->ssaoPass.textures.push_back(createColorAttachment(GL_COLOR_ATTACHMENT0, GL_RED));
	drawBuffers(1);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	this->ssaoShader->use();
	this->ssaoShader->setInt("normalPass", 1);
	this->ssaoShader->setInt("positionPass", 3);
	std::vector<glm::vec3> ssaoKernel = genSSAOKernel(4);
	for (unsigned int i = 0; i < ssaoKernel.size(); ++i)
		this->ssaoShader->setVec3(("samples[" + std::to_string(i) + "]").c_str(), ssaoKernel[i]);

	// final shader
	this->combineShader->use();
	this->combineShader->setInt("mrcPass", 2);
	this->combineShader->setInt("fxPass", 4);
	this->combineShader->setInt("ambientPass", 5);
	this->combineShader->setInt("lightingPass", 6);
	this->combineShader->setInt("shadowPass", 7);
	this->combineShader->setInt("ssaoPass", 8);
}


/*------------------------------------------------------------------------------
< render >
------------------------------------------------------------------------------*/
void RenderPass::render(RenderLayer* renderLayer, RenderLayer* fxLayer, std::vector<PointLight*>* pointLights, GameObject* camera) {
	Game* game = Game::getInstance();
	int width = game->window->screenWidth;
	int height = game->window->screenHeight;

	// deferred pass
	glBindFramebuffer(GL_FRAMEBUFFER, this->deferredPass.fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderLayer->render(camera);

	// fx pass
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->fxPass.fbo);
	glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	glClear(GL_COLOR_BUFFER_BIT);
	glBlendFunc(GL_ONE, GL_ONE);
	glDepthMask(GL_FALSE);
	fxLayer->render(camera);
	glDepthMask(GL_TRUE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// active g-buffer textures
	for (unsigned int i = 0; i < this->deferredPass.textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, this->deferredPass.textures[i]);
	}

	// ambient pass
	glBindFramebuffer(GL_FRAMEBUFFER, this->ambientPass.fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->ambientShader->use();
	this->ambientShader->setVec3("cameraPosition", camera->transform->position);
	game->resources->quad->draw();

	// lighting pass
	glBindFramebuffer(GL_FRAMEBUFFER, this->lightingPass.fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->lightingShader->use();
	this->lightingShader->setVec3("cameraPosition", camera->transform->position);
	int lightSize = 0;
	for (unsigned int i = 0; i < pointLights->size(); i++) {
		if (!pointLights->at(i)->culling) {
			this->lightingShader->setVec3(("lightColor[" + std::to_string(lightSize) + "]").c_str(), pointLights->at(i)->color * pointLights->at(i)->intensity);
			this->lightingShader->setVec3(("lightPosition[" + std::to_string(lightSize) + "]").c_str(), pointLights->at(i)->gameObject->transform->position);
			this->lightingShader->setFloat(("lightRadius[" + std::to_string(lightSize) + "]").c_str(), pointLights->at(i)->radius);
			lightSize++;
		}
	}
	this->lightingShader->setInt("lightSize", lightSize);
	game->resources->quad->draw();

	// shadow pass
	glBindFramebuffer(GL_FRAMEBUFFER, this->shadowPass.fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->shadowShader->use();
	this->shadowShader->setMat4("lightSpaceMatrix", game->shadowMapping->lightSpace);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, game->shadowMapping->depthMap);
	game->resources->quad->draw();

	// ssao pass
	Camera* cameraComponent = camera->getComponent<Camera>();
	glBindFramebuffer(GL_FRAMEBUFFER, this->ssaoPass.fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->ssaoShader->use();
	glm::mat4 normalMatrix = glm::transpose(glm::inverse(glm::mat3(cameraComponent->view)));
	this->ssaoShader->setMat4("normalMatrix", normalMatrix);
	cameraComponent->setUniforms(this->ssaoShader);
	game->resources->quad->draw();


	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// final pass
	this->combineShader->use();
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, this->fxPass.textures[0]);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_2D, this->ambientPass.textures[0]);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_2D, this->lightingPass.textures[0]);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, this->shadowPass.textures[0]);
	glActiveTexture(GL_TEXTURE8);
	glBindTexture(GL_TEXTURE_2D, this->ssaoPass.textures[0]);
	this->quad->draw();
}


/*------------------------------------------------------------------------------
< render bounding box >
------------------------------------------------------------------------------*/
void RenderPass::renderBounding(std::vector<MeshRenderer*>* renderQueue, GameObject* camera) {
	Game* game = Game::getInstance();

	// bind framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, this->deferredPass.fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// render bounding box in line mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	Shader* shader = game->resources->getShader("simple");
	shader->use();
	camera->getComponent<Camera>()->setUniforms(shader);
	for (unsigned int i = 0; i < renderQueue->size(); i++) {
		Transform* transform = renderQueue->at(i)->gameObject->getComponent<Transform>();
		transform->setUniform(shader);
		renderQueue->at(i)->model->drawBounding();
	}

	// reset framebuffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// bind shader
	game->resources->getShader("renderpass_color_1_passes")->use();
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->deferredPass.textures[0]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	this->quad->draw();
}


/*------------------------------------------------------------------------------
< create color attachment >
------------------------------------------------------------------------------*/
unsigned int RenderPass::createColorAttachment(GLenum attachment, GLint internalFormat) {
	Game* game = Game::getInstance();

	// create attachment
	unsigned int colorAttachment;
	glGenTextures(1, &colorAttachment);
	glBindTexture(GL_TEXTURE_2D, colorAttachment);

	if (internalFormat == GL_RGB)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, game->window->screenWidth, game->window->screenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	else if (internalFormat == GL_RGB16F)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, game->window->screenWidth, game->window->screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
	else if (internalFormat == GL_RGB32F)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, game->window->screenWidth, game->window->screenHeight, 0, GL_RGB, GL_FLOAT, NULL);
	else if (internalFormat == GL_RED)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, game->window->screenWidth, game->window->screenHeight, 0, GL_RED, GL_FLOAT, NULL);
	else return -1;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// attach texture to framebuffer
	glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, colorAttachment, 0);

	return colorAttachment;
}


/*------------------------------------------------------------------------------
< create depth attachment >
------------------------------------------------------------------------------*/
void RenderPass::createDepthAttachment(GLenum internalformat) {
	Game* game = Game::getInstance();

	unsigned int depthRBO;
	glGenRenderbuffers(1, &depthRBO);
	glBindRenderbuffer(GL_RENDERBUFFER, depthRBO);
	glRenderbufferStorage(GL_RENDERBUFFER, internalformat, game->window->screenWidth, game->window->screenHeight);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRBO);
}


/*------------------------------------------------------------------------------
< set draw buffers >
------------------------------------------------------------------------------*/
void RenderPass::drawBuffers(GLsizei n) {
	unsigned int attachments[n];
	for (unsigned int i = 0; i < n; i++)
		attachments[i] = GL_COLOR_ATTACHMENT0 + i;
	glDrawBuffers(n, attachments);
}
