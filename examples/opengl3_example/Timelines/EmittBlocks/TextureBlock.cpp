#include "TextureBlock.h"
#include "../../Other/GLFuncs.h"
#include <exception>
#include "../../Other/Constants.h"


TextureBlock::TextureBlock(TimeInterval t, const char* fileName, unsigned int texSlot)
	: Block(t, type::Emitter), _texSlot(texSlot)
{
	if (!loadTexture(fileName, gTextureID))
		loadTexture(DEFAULT_TEX, gTextureID);
	visualName = "Texture\n Slot";
	desc = "Block setting a specific texture slot for the particles";
	iconName = "Texture.png";
}

TextureBlock::~TextureBlock()
{
}

void TextureBlock::DrawProperties(ImVec2 pos, ImVec2 size){

}