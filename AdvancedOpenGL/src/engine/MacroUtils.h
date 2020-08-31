#define IDENT(x) x
#define XSTR(x) #x
#define STR(x) XSTR(x)
#define PATH(x, y) STR(IDENT(x)IDENT(y))
#define PATH3(p, x, y) STR(IDENT(p)IDENT(x)IDENT(y))
#define EXT .h
#define EXT_VERT .vert
#define EXT_FRAG .frag
#define SHADER_PATH assets/shaders/
#define SHADER_VERT(s) PATH3(SHADER_PATH, s, EXT_VERT)
#define SHADER_FRAG(s) PATH3(SHADER_PATH, s, EXT_FRAG)
#define SHADER_ID(s) STR(s)

#define SCENE_NAME Scene_010_TextureCoordinates
#define SHADER_NAME IDENT(010_texture_coordinates)
