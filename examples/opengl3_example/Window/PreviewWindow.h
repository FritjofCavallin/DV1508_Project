#pragma once

#include "../camera.h"
#include "imgui.h"
#include "../Timelines/Data.h"
#include "../Particles/Particle.h"
#include "../Particles/Particle2DShader.h"

class SpawnBlock; class EffectBlock;

class PreviewWindow
{
public:
	PreviewWindow(Data* data);
	~PreviewWindow();

	void render();
	void resize(unsigned int w, unsigned int h);

	ImTextureID getWindowTex();
private:

	unsigned int _display_w, _display_h;

	void CreateShaders();
	void CreateTriangleData();

	Data* _data;

	// Render buffer target
	GLuint frameBuffer, depthTex, texture;
	ImVec4 clear_color;

	// Grid rendering
	GLuint gShaderProgram;
	GLuint gVertexBuffer, gVertexAttribute;
	GLint mvpMatrixID;
	size_t gridVertCount;

	Camera camera;

	// 2D window
	EffectBlock *_previewEff;
	SpawnBlock *_previewSpw;
	float _previewTime;
	Particle _part;
	GPUParticle _partData;
	Particle2DShader _part2D;
	void resetPart();
	void drawParticle();
};

