/*
#include "font.h"


Font::Font(void)
{
}


Font::~Font(void)
{
}

void Font::Load(const char * filename) {
    FT_Error error;
  error = FT_Init_FreeType( &library );
  if ( error )
  {
    std::cout<<"an error occurred during freetype initialization";
  }
  error = FT_New_Face( library,
                     "../Graphics/Reality Hyper Regular.ttf",
                     0,
                     &face );
  if ( error == FT_Err_Unknown_File_Format ) {
    std::cout<<"Fonts file format unknown";
  } else if ( error ) {
    std::cout<<"Font file could not be opened";
  }
  FT_Set_Pixel_Sizes(face, 0, 100);

  if(FT_Load_Glyph( face, FT_Get_Char_Index( face, 'R' ), FT_LOAD_RENDER)) {
      std::cout<<"Glyph could not be loaded";
  }

  GLuint fonttextureID;
  
  glGenTextures( 1, &fonttextureID);
	glBindTexture(GL_TEXTURE_2D, fonttextureID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  glTexImage2D( GL_TEXTURE_2D,
				0,
				GL_RGBA,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_LUMINANCE,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
				);

}

void RenderText(unsigned char * string) {
}
*/