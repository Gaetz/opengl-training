// #ifndef BATCH_CONFIG_H
// #define BATCH_CONFIG_H

// #include "math_core.h"

// struct BatchConfig
// {
//     /**
//      * How the vertices should be interpreted
//      * - a set of GL_LINES,
//      * - a set of GL_TRIANGLES, 
//      * - or a set of GL_TRIANGLE_STRIPS.
//      * */
//     unsigned renderType;

//     /**
//      * Which order Batches should be rendered in. 
//      * A higher priority value indicates that the Batch of vertices will appear 
//      * on top of another Batch that has a lower priority.
//      * */
//     int priority;

//     /**
//      *  If vertices stored in a Batch have texture coordinates, 
//      * then we need to know which texture to use.
//      * */
//     unsigned textureId;

//     /** 
//      * If the vertices need to be transformed before being rendered, 
//      * then their transformMatrix will contain a non-identity matrix.
//      * */
//     Matrix4 transformMatrix;
    
//     BatchConfig(unsigned renderType, int priority, unsigned textureId)
//         : renderType(renderType), priority(priority), textureId(textureId)
//     {
//     }

//     bool operator==(const BatchConfig &other) const
//     {
//         if (renderType != other.renderType || priority != other.priority 
//             || textureId != other.textureId || transformMatrix != other.transformMatrix)
//         {
//             return false;
//         }
//         return true;
//     }

//     bool operator!=(const BatchConfig &other) const { return !(*this == other); }
// };

// #endif