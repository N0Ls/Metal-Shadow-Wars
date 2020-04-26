static const unsigned int WINDOW_WIDTH = 600;
static const unsigned int WINDOW_HEIGHT = 600;

static const int MAP_SIZE = 10;
static const float GL_VIEW_SIZE = 100.;

static const unsigned int MAP_TILE_SIZE = GL_VIEW_SIZE/MAP_SIZE;


static const int nb_textures = 2;
static char textures_paths[nb_textures][255]= {"doc/logo_imac.png", "doc/grass_block_side.png"};

static GLuint textureIds[nb_textures];
