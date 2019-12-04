#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H

#include "math_core.h"
#include "color.h"
#include "vertex2d.h"

#include <GL/glew.h>
#include <vector>
using std::vector;

// Determines how we should sort the glyphs
enum class GlyphSortType
{
    NONE,
    FRONT_TO_BACK,
    BACK_TO_FRONT,
    TEXTURE
};

// A glyph is a single quad. These are added via Spritebatch::Draw
class Glyph
{
public:
    Glyph(){};
    Glyph(const Vector4 &destRect, const Vector4 &uvRect, GLuint Texture, float Depth, const ColorRGBA8 &color);
    Glyph(const Vector4 &destRect, const Vector4 &uvRect, GLuint Texture, float Depth, const ColorRGBA8 &color, float angle);

    GLuint texture;
    float depth;

    Vertex2D topLeft;
    Vertex2D bottomLeft;
    Vertex2D topRight;
    Vertex2D bottomRight;

private:
    // Rotates a point about (0,0) by angle
    Vector2 rotatePoint(const Vector2 &pos, float angle);
};

// Each render batch is used for a single draw call
class BatchRender
{
public:
    BatchRender(GLuint Offset, GLuint NumVertices, GLuint Texture)
        : offset(Offset), numVertices(NumVertices), texture(Texture)
    {
    }
    GLuint offset;
    GLuint numVertices;
    GLuint texture;
};


// The Spritebatch class is a more efficient way of drawing sprites
class Spritebatch
{
public:
    Spritebatch();
    ~Spritebatch();

    // Initializes the spritebatch
    void init();

    // Begins the spritebatch
    void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);

    // Ends the spritebatch
    void end();

    // Adds a glyph to the spritebatch
    void draw(const Vector4& destRect, const Vector4& uvRect, GLuint texture, float depth, const ColorRGBA8& color);
    // Adds a glyph to the spritebatch with rotation
    void draw(const Vector4& destRect, const Vector4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, float angle);
    // Adds a glyph to the spritebatch with rotation
    void draw(const Vector4& destRect, const Vector4& uvRect, GLuint texture, float depth, const ColorRGBA8& color, const Vector2& dir);

    // Renders the entire Spritebatch to the screen
    void render();
	
private:
    // Creates all the needed RenderBatches
    void createRenderBatches();

    // Generates our VAO and VBO
    void createVertexArray();

    // Sorts glyphs according to _sortType
    void sortGlyphs();

    // Comparators used by sortGlyphs()
    static bool CompareFrontToBack(Glyph* a, Glyph* b);
    static bool CompareBackToFront(Glyph* a, Glyph* b);
    static bool CompareTexture(Glyph* a, Glyph* b);

    GLuint vbo;
    GLuint vao;

    GlyphSortType sortType;
	
    vector<Glyph*> glyphPointers; ///< This is for sorting
    vector<Glyph> glyphs; ///< These are the actual glyphs
	vector<BatchRender> renderBatches;
};

#endif