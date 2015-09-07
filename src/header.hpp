#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
//GLEW:
#define GLEW_STATIC
#include <GL/glew.h>
//SDL2:
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
//glm:
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/detail/setup.hpp>
#if GLM_VERSION >= 96
   #include <glm/gtc/vec1.hpp>
#else
   #include <glm/gtx/vec1.hpp>
#endif
//DevIL:
#include <IL/il.h>
#include <IL/ilu.h>
//assimp:
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace glm;
