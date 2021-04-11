#define IDENT(x) x
#define XSTR(x) #x
#define STR(x) XSTR(x)
#define PATH(x, y) STR(IDENT(x)IDENT(y))
#define PATH3(p, x, y) STR(IDENT(p)IDENT(x)IDENT(y))
#define EXT .h
#define EXT_VERT .vert
#define EXT_FRAG .frag
#define EXT_TECS .tesc
#define EXT_TESE .tese
#define EXT_GEOM .geom
#define EXT_COMP .glsl
#define SHADER_PATH assets/shaders/
#define SHADER_VERT(s) PATH3(SHADER_PATH, s, EXT_VERT)
#define SHADER_FRAG(s) PATH3(SHADER_PATH, s, EXT_FRAG)
#define SHADER_TECS(s) PATH3(SHADER_PATH, s, EXT_TECS)
#define SHADER_TESE(s) PATH3(SHADER_PATH, s, EXT_TESE)
#define SHADER_GEOM(s) PATH3(SHADER_PATH, s, EXT_GEOM)
#define SHADER_COMP(s) PATH3(SHADER_PATH, s, EXT_COMP)
#define SHADER_ID(s) STR(s)

#define SCENE_NAME Scene_023_ComputeShaderBoids
#define SHADER_NAME IDENT(023_ComputeShaderBoids)

/**
 * Scene_023_ComputeShaderBoids
 * Scene_022_ComputeShaderPrefixSum
 * Scene_021_ChangePrimitiveType
 * Scene_020_GenerateGeometry
 * Scene_019_ModifyGeometry
 * Scene_018_DiscardGeometry
 * Scene_017_CubicBezierPatches
 * Scene_016_TerrainRendering
 * Scene_015_TessellationModes
 * Scene_014_IndirectDrawAstroids
 * Scene_013_InstancedGrassBlades
 * Scene_012_ArrayTextureAlienRain
 * Scene_011_MipmapTunnel
 * Scene_010_TextureCoordinates
 * Scene_009_TextureAsData
 * Scene_008_SpinningCubes
 * Scene_007_SpinningCube
 * Scene_006_Fragment
 *  * */
