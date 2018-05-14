#include "TextureBlock.h"
#include "../../Other/GLFuncs.h"
#include <exception>


TextureBlock::TextureBlock(TimeInterval t, const char* fileName, unsigned int texSlot)
	: Block(t, type::Emitter), _texSlot(texSlot)
{
	if (!loadTexture(fileName, gTextureID))
		throw std::exception();

}

TextureBlock::~TextureBlock()
{
}
