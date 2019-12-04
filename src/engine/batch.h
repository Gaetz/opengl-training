// #include "batch_config.h"
// #include "batch_sprite_vertex.h"
// #include "vertex_array.h"
// #include "shader.h"

// #include <vector>

// using std::vector;

// class Batch
// {
// public:
//     Batch(unsigned uMaxNumVertices);
//     ~Batch();
//     bool isBatchConfig(const BatchConfig &config) const;
//     bool isEmpty() const;

//     /**
//      * Returns true if the number of vertices passed in can be stored in this batch
//      * without reaching the limit of how many vertices can fit in the batch
//      * */
//     bool isEnoughRoom(unsigned uNumVertices) const;

//     /**
//      * Returns the batch that contains the most number of stored vertices between
//      * this batch and the one passed in
//      * */
//     Batch *getFullest(Batch *pBatch);
//     int getPriority() const;

//     /**
//      * Adds vertices to batch and also sets the batch config options
//     */
//     void add(const vector<SpriteVertex>& vVertices, const BatchConfig& config);

//     /**
//      * Adds vertices to batch
//     */
//     void add(const vector<SpriteVertex>& vVertices);

//     /**
//      * Use SpriteBatch to render
//      * */
//     void render();

// private:
//     unsigned maxNumVertices;
//     unsigned _uNumUsedVertices;
//     //VertexArray vao;
//     unsigned _vao;
//     unsigned _vbo;
//     BatchConfig _config;
//     SpriteVertex _lastVertex;
//     Shader shader;

//     void cleanUp();

//     Batch(const Batch &c);            // not implemented
//     Batch &operator=(const Batch &c); // not implemented
// };