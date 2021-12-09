#pragma  once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace LoadTextureUtil
{
	unsigned int LoadTexture(const char* szPath)
	{
		unsigned int textureId;
		glGenTextures(1, &textureId);

		int nWidth, nHeight, nComponents;
		unsigned char* data = stbi_load(szPath,&nWidth,&nHeight,&nComponents,0);
		if (data)
		{
			GLenum format;
			if (nComponents == 1)
				format = GL_RED;
			else if (nComponents == 3)
				format = GL_RGB;
			else if (nComponents == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, textureId);
			glTexImage2D(GL_TEXTURE_2D, 0, format, nWidth, nHeight, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);
		}

		return textureId;
	}

}