#include "spritebatch.h"

#include <algorithm>

Glyph::Glyph(const Vector4 &destRect, const Vector4 &uvRect, GLuint Texture, float Depth, const ColorRGBA8 &color)
    : texture(Texture),
      depth(Depth)
{

    topLeft.color = color;
    topLeft.setPosition(destRect.x, destRect.y + destRect.w);
    topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    bottomLeft.color = color;
    bottomLeft.setPosition(destRect.x, destRect.y);
    bottomLeft.setUV(uvRect.x, uvRect.y);

    bottomRight.color = color;
    bottomRight.setPosition(destRect.x + destRect.z, destRect.y);
    bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    topRight.color = color;
    topRight.setPosition(destRect.x + destRect.z, destRect.y + destRect.w);
    topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

Glyph::Glyph(const Vector4 &destRect, const Vector4 &uvRect, GLuint Texture, float Depth, const ColorRGBA8 &color, float angle)
    : texture(Texture),
      depth(Depth)
{

    Vector2 halfDims(destRect.z / 2.0f, destRect.w / 2.0f);

    // Get points centered at origin
    Vector2 tl(-halfDims.x, halfDims.y);
    Vector2 bl(-halfDims.x, -halfDims.y);
    Vector2 br(halfDims.x, -halfDims.y);
    Vector2 tr(halfDims.x, halfDims.y);

    // Rotate the points
    tl = rotatePoint(tl, angle) + halfDims;
    bl = rotatePoint(bl, angle) + halfDims;
    br = rotatePoint(br, angle) + halfDims;
    tr = rotatePoint(tr, angle) + halfDims;

    topLeft.color = color;
    topLeft.setPosition(destRect.x + tl.x, destRect.y + tl.y);
    topLeft.setUV(uvRect.x, uvRect.y + uvRect.w);

    bottomLeft.color = color;
    bottomLeft.setPosition(destRect.x + bl.x, destRect.y + bl.y);
    bottomLeft.setUV(uvRect.x, uvRect.y);

    bottomRight.color = color;
    bottomRight.setPosition(destRect.x + br.x, destRect.y + br.y);
    bottomRight.setUV(uvRect.x + uvRect.z, uvRect.y);

    topRight.color = color;
    topRight.setPosition(destRect.x + tr.x, destRect.y + tr.y);
    topRight.setUV(uvRect.x + uvRect.z, uvRect.y + uvRect.w);
}

Vector2 Glyph::rotatePoint(const Vector2 &pos, float angle)
{
    Vector2 newv;
    newv.x = pos.x * cos(angle) - pos.y * sin(angle);
    newv.y = pos.x * sin(angle) + pos.y * cos(angle);
    return newv;
}

Spritebatch::Spritebatch() : vbo(0), vao(0)
{
}

Spritebatch::~Spritebatch()
{
}

void Spritebatch::init()
{
    createVertexArray();
}

void Spritebatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */)
{
    sortType = sortType;
    renderBatches.clear();

    // Makes glyphs.size() == 0, however it does not free internal memory.
    // So when we later call emplace_back it doesn't need to internally call new.
    glyphs.clear();
}

void Spritebatch::end()
{
    // Set up all pointers for fast sorting
    glyphPointers.resize(glyphs.size());
    for (size_t i = 0; i < glyphs.size(); i++)
    {
        glyphPointers[i] = &glyphs[i];
    }

    sortGlyphs();
    createRenderBatches();
}

void Spritebatch::draw(const Vector4 &destRect, const Vector4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color)
{
    glyphs.emplace_back(destRect, uvRect, texture, depth, color);
}

void Spritebatch::draw(const Vector4 &destRect, const Vector4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color, float angle)
{
    glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void Spritebatch::draw(const Vector4 &destRect, const Vector4 &uvRect, GLuint texture, float depth, const ColorRGBA8 &color, const Vector2 &dir)
{
    const Vector2 right(1.0f, 0.0f);
    float angle = acos(Vector2::dot(right, dir));
    if (dir.y < 0.0f)
        angle = -angle;

    glyphs.emplace_back(destRect, uvRect, texture, depth, color, angle);
}

void Spritebatch::render()
{

    // Bind our VAO. This sets up the opengl state we need, including the
    // vertex attribute pointers and it binds the VBO
    glBindVertexArray(vao);

    for (size_t i = 0; i < renderBatches.size(); i++)
    {
        glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);

        glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
    }

    glBindVertexArray(0);
}

void Spritebatch::createRenderBatches()
{
    // This will store all the vertices that we need to upload
    vector<Vertex2D> vertices;
    // Resize the buffer to the exact size we need so we can treat
    // it like an array
    vertices.resize(glyphPointers.size() * 6);

    if (glyphPointers.empty())
    {
        return;
    }

    int offset = 0; // current offset
    int cv = 0;     // current vertex

    //Add the first batch
    renderBatches.emplace_back(offset, 6, glyphPointers[0]->texture);
    vertices[cv++] = glyphPointers[0]->topLeft;
    vertices[cv++] = glyphPointers[0]->bottomLeft;
    vertices[cv++] = glyphPointers[0]->bottomRight;
    vertices[cv++] = glyphPointers[0]->bottomRight;
    vertices[cv++] = glyphPointers[0]->topRight;
    vertices[cv++] = glyphPointers[0]->topLeft;
    offset += 6;

    //Add all the rest of the glyphs
    for (size_t cg = 1; cg < glyphPointers.size(); cg++)
    {

        // Check if this glyph can be part of the current batch
        if (glyphPointers[cg]->texture != glyphPointers[cg - 1]->texture)
        {
            // Make a new batch
            renderBatches.emplace_back(offset, 6, glyphPointers[cg]->texture);
        }
        else
        {
            // If its part of the current batch, just increase numVertices
            renderBatches.back().numVertices += 6;
        }
        vertices[cv++] = glyphPointers[cg]->topLeft;
        vertices[cv++] = glyphPointers[cg]->bottomLeft;
        vertices[cv++] = glyphPointers[cg]->bottomRight;
        vertices[cv++] = glyphPointers[cg]->bottomRight;
        vertices[cv++] = glyphPointers[cg]->topRight;
        vertices[cv++] = glyphPointers[cg]->topLeft;
        offset += 6;
    }

    // Bind our VBO
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // Orphan the buffer (for speed)
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex2D), nullptr, GL_DYNAMIC_DRAW);
    // Upload the data
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex2D), vertices.data());

    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Spritebatch::createVertexArray()
{

    // Generate the VAO if it isn't already generated
    if (vao == 0)
    {
        glGenVertexArrays(1, &vao);
    }

    // Bind the VAO. All subsequent opengl calls will modify it's state.
    glBindVertexArray(vao);

    // Generate the VBO if it isn't already generated
    if (vbo == 0)
    {
        glGenBuffers(1, &vbo);
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    //Tell opengl what attribute arrays we need
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    //This is the position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, position));
    //This is the color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, color));
    //This is the UV attribute pointer
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, uv));

    glBindVertexArray(0);
}

void Spritebatch::sortGlyphs()
{

    switch (sortType)
    {
    case GlyphSortType::BACK_TO_FRONT:
        std::stable_sort(glyphPointers.begin(), glyphPointers.end(), CompareBackToFront);
        break;
    case GlyphSortType::FRONT_TO_BACK:
        std::stable_sort(glyphPointers.begin(), glyphPointers.end(), CompareFrontToBack);
        break;
    case GlyphSortType::TEXTURE:
        std::stable_sort(glyphPointers.begin(), glyphPointers.end(), CompareTexture);
        break;
    }
}

bool Spritebatch::CompareFrontToBack(Glyph *a, Glyph *b)
{
    return (a->depth < b->depth);
}

bool Spritebatch::CompareBackToFront(Glyph *a, Glyph *b)
{
    return (a->depth > b->depth);
}

bool Spritebatch::CompareTexture(Glyph *a, Glyph *b)
{
    return (a->texture < b->texture);
}