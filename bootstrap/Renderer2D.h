#pragma once

namespace aie {

class Texture;
class Font;

// a class for rendering 2D sprites and font
class Renderer2D {
public:

	Renderer2D();
	virtual ~Renderer2D();

	// all draw calls must occur between a begin / end pair
	virtual void begin();
	virtual void end();

	// simple shape rendering
	virtual void drawBox(float xPos, float yPos, float width, float height, float rotation = 0.0f, float depth = 0.0f);
	virtual void drawCircle(float xPos, float yPos, float radius, float depth = 0.0f);

	/*
	* drawTriangle
	*
	* draws a triangle to the screen
	* 
	* @param float x1 - x coordinate of the first point in the triangle
	* @param float y1 - y coordinate of the first point in the triangle
	* @param float x2 - x coordinate of the second point in the triangle
	* @param float y2 - y coordinate of the second point in the triangle
	* @param float x3 - x coordinate of the third point in the triangle
	* @param float y3 - y coordinate of the third point in the triangle
	* @returns void
	*/
	virtual void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float depth = 0.0f);

	// if texture is nullptr then it renders a coloured sprite
	// depth is in the range [0,100] with lower being closer to the viewer
	virtual void drawSprite(Texture* texture, float xPos, float yPos, float width = 0.0f, float height = 0.0f, float rotation = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual void drawSpriteTransformed3x3(Texture* texture, float* transformMat3x3, float width = 0.0f, float height = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual void drawSpriteTransformed4x4(Texture* texture, float* transformMat4x4, float width = 0.0f, float height = 0.0f, float depth = 0.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);

	// draws a simple coloured line with a given thickness
	// depth is in the range [0,100] with lower being closer to the viewer
	virtual void drawLine(float x1, float y1, float x2, float y2, float thickness = 1.0f, float depth = 0.0f );

	// draws simple text on the screen horizontally
	// depth is in the range [0,100] with lower being closer to the viewer
	virtual void drawText(Font* font, const char* text, float xPos, float yPos, float depth = 0.0f);

	// sets the tint colour for all subsequent draw calls
	void setRenderColour(float r, float g, float b, float a = 1.0f);
	void setRenderColour(unsigned int colour);

	// can be used to set the texture coordinates of sprites using textures
	// for all subsequent drawSprite calls
	void setUVRect(float uvX, float uvY, float uvW, float uvH);

	// specify the camera position
	void setCameraPos(float x, float y) { m_cameraX = x; m_cameraY = y; }
	void getCameraPos(float& x, float& y) const { x = m_cameraX; y = m_cameraY; }

	// returns the width in pixels for the given text.
	// this is usefull for center alligning text.
	float measureTextWidth(Font *font, const char *text);

protected:

	// helper methods used during drawing
	bool shouldFlush(int additionalVertices = 0, int additionalIndices = 0);
	void flushBatch();
	unsigned int pushTexture(Texture* texture);

	// indicates in the middle of a begin/end pair
	bool				m_renderBegun;

	// the camera position
	float				m_cameraX, m_cameraY;

	// texture handling
	enum { TEXTURE_STACK_SIZE = 16 };
	Texture*			m_nullTexture;
	Texture*			m_textureStack[TEXTURE_STACK_SIZE];
	int					m_fontTexture[TEXTURE_STACK_SIZE];
	unsigned int		m_currentTexture;

	// texture coordinate information
	float				m_uvX, m_uvY, m_uvW, m_uvH;

	// represents colour in red, green, blue and alpha 0.0-1.0 range
	float				m_r, m_g, m_b, m_a;

	// sprite handling
	enum { MAX_SPRITES = 512 };
	struct SBVertex {
		float pos[4];
		float color[4];
		float texcoord[2];
	};

	// data used for opengl to draw the sprites (with padding)
	SBVertex			m_vertices[MAX_SPRITES * 4];
	unsigned short		m_indices[MAX_SPRITES * 6];
	int					m_currentVertex, m_currentIndex;
	unsigned int		m_vao, m_vbo, m_ibo;

	// shader used to render sprites
	unsigned int		m_shader;

	// helper method used to rotate sprites around a pivot
	void	rotateAround(float inX, float inY, float& outX, float& outY, float sin, float cos);

	// data used for a virtual camera
	float	m_projectionMatrix[16];
};

} // namespace aie