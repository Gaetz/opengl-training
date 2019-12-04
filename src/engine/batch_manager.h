// #include <vector>
// #include <string>
// #include <memory>
// #include "batch_sprite_vertex.h"
// #include "batch_config.h"

// using std::vector;
// using std::string;

// class Batch;

// class BatchManager
// {

// public:
//     BatchManager(unsigned numBatches, unsigned numVerticesPerBatch);
//     virtual ~BatchManager();

//     static BatchManager *const get();

//     void render(const vector<SpriteVertex>& vertices, const BatchConfig &config, const std::string &strId);
//     void emptyAll();

// private:
//     std::vector<std::shared_ptr<Batch>> batches;
//     unsigned numBatches;
//     unsigned maxNumVerticesPerBatch;


//     /**
//      *  Empties The Batches According To Priority. If emptyAll() Is False Then
//      * Only Empty The Batches That Are Lower Priority Than The One Specified
//      * AND Also Empty The One That Is Passed In
//      * */
//     void emptyBatch(bool emptyAll, Batch *pBatchToEmpty);


//     BatchManager(const BatchManager &c);            // Not Implemented
//     BatchManager &operator=(const BatchManager &c); // Not Implemented

//     //void  renderBatch( const std::vector<GuiVertex>& vVertices, const BatchConfig& config );
// };