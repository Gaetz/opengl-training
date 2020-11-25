#ifndef TEXTURE_KTX_H
#define TEXTURE_KTX_H
#include <GL/glew.h>

struct TextureKtxHeader {
    unsigned char identifier[12];
    unsigned int endianness;
    unsigned int gltype;
    unsigned int gltypesize;
    unsigned int glformat;
    unsigned int glinternalformat;
    unsigned int glbaseinternalformat;
    unsigned int pixelwidth;
    unsigned int pixelheight;
    unsigned int pixeldepth;
    unsigned int arrayelements;
    unsigned int faces;
    unsigned int miplevels;
    unsigned int keypairbytes;
};

class TextureKtx {
   public:
    unsigned int id;

    union keyvaluepair {
        unsigned int size;
        unsigned char rawbytes[4];
    };

    unsigned int load(const char* filename, unsigned int tex = 0);
    bool save(const char* filename, unsigned int target, unsigned int tex);
    void use() const;

   private:
    int width, height;
    GLenum textureTarget;

    const unsigned int swap32(const unsigned int u32);
    const unsigned short swap16(const unsigned short u16);
    unsigned int calculateStride(const TextureKtxHeader& h, unsigned int width, unsigned int pad = 4);
    unsigned int calculateFaceSize(const TextureKtxHeader& h);

    static const unsigned char identifier[];
};

#endif
