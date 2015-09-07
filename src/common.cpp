#ifndef __common_hpp__
#define __common_hpp__

GLuint CreateShader( string vertex, string fragment );
bool LoadImg( const char *img_path_file, GLuint &image );
bool LoadAssimp( string file, vector <vec3> &vertices, vector <vec2> &uvs, vector <vec3> &normals, vector <GLuint> &indices );



GLuint CreateShader( string vertex, string fragment ){
   GLuint VertexShaderID = glCreateShader( GL_VERTEX_SHADER );
   GLuint FragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

   string Line;
   //vertex_shader:
   string VertexShaderCode;
   ifstream VertexShaderStream( vertex.c_str() );
   if( VertexShaderStream.good() ){
      Line = "";
      while( getline( VertexShaderStream, Line ) ){
         VertexShaderCode += Line + "\n";
      }
      VertexShaderStream.close();
   }
   else{
      cout<<"File problem: "<<vertex<<"\n";
      return 0;
   }

   //Load code fragment_shader:
   string FragmentShaderCode;
   ifstream FragmentShaderStream( fragment.c_str() );
   if( FragmentShaderStream.good() ){
      Line = "";
      while( getline( FragmentShaderStream, Line ) ){
         FragmentShaderCode += Line + "\n";
      }
      FragmentShaderStream.close();
   }
   else{
      cout<<"File problem: "<<fragment<<"\n";
      return 0;
   }

   GLint Result;
   GLint InfoLogLength;
   string Error;

   const char *VertexShaderCodePointer = VertexShaderCode.c_str();
   glShaderSource( VertexShaderID, 1, &VertexShaderCodePointer, 0 );
   glCompileShader( VertexShaderID );
   //Check vertex_shader:
   Result = GL_FALSE;
   glGetShaderiv( VertexShaderID, GL_COMPILE_STATUS, &Result );
   if( Result == GL_FALSE ){
      InfoLogLength = 0;
      glGetShaderiv( VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
      vector <GLchar> VertexShaderErrorMessage(InfoLogLength);
      glGetShaderInfoLog( VertexShaderID, InfoLogLength, &InfoLogLength, &VertexShaderErrorMessage[0] );
      Error = string( VertexShaderErrorMessage.begin(), VertexShaderErrorMessage.end() );
      cout<<"Vertex shader: "<<Error<<"\n";
      glDeleteShader( VertexShaderID );
      return 0;
   }

   //fragment_shader:
   const char *FragmentShaderCodePointer = FragmentShaderCode.c_str();
   glShaderSource( FragmentShaderID, 1, &FragmentShaderCodePointer, 0 );
   glCompileShader( FragmentShaderID );
   //Check fragment_shader:
   Result = GL_FALSE;
   glGetShaderiv( FragmentShaderID, GL_COMPILE_STATUS, &Result );
   if( Result == GL_FALSE ){
      InfoLogLength = 0;
      glGetShaderiv( FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
      vector <GLchar> FragmentShaderErrorMessage(InfoLogLength);
      glGetShaderInfoLog( FragmentShaderID, InfoLogLength, &InfoLogLength, &FragmentShaderErrorMessage[0] );
      Error.clear();
      Error = string( FragmentShaderErrorMessage.begin(), FragmentShaderErrorMessage.end() );
      cout<<"Fragment shader: "<<Error<<"\n";
      glDeleteShader( VertexShaderID );
      glDeleteShader( FragmentShaderID );
      return 0;
   }

   Result = GL_FALSE;
   InfoLogLength = 0;

   //Create program shader:
   GLuint ProgramID = glCreateProgram();
   glAttachShader( ProgramID, VertexShaderID );
   glAttachShader( ProgramID, FragmentShaderID );
   glLinkProgram( ProgramID );

   //Check program:
   glGetProgramiv( ProgramID, GL_LINK_STATUS, &Result );
   if( Result == GL_FALSE ){
      glGetProgramiv( ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength );
      vector <GLchar> ProgramErrorMessage(InfoLogLength);
      glGetProgramInfoLog( ProgramID, InfoLogLength, &InfoLogLength, &ProgramErrorMessage[0] );
      Error.clear();
      Error = string( ProgramErrorMessage.begin(), ProgramErrorMessage.end() );
      cout<<"program shader: "<<Error<<"\n";
      glDeleteProgram( ProgramID );
      glDeleteShader( VertexShaderID );
      glDeleteShader( FragmentShaderID );
      return 0;
   }

   //delete shaders:
   glDetachShader( ProgramID, VertexShaderID );
   glDetachShader( ProgramID, FragmentShaderID );
   glDeleteShader( VertexShaderID );
   glDeleteShader( FragmentShaderID );

   return ProgramID;
}

bool LoadImg( const char *img_path_file, GLuint &image ){
   ILenum error;
   GLenum error_gl;
   ILboolean success;
   ILuint imgage_id;

   ilGenImages( 1, &imgage_id );
   ilBindImage( imgage_id );
   success = ilLoadImage( img_path_file );
   if( ! success ){
      error = ilGetError();
      if( error != IL_NO_ERROR ){
         cout<<"ilLoadImage: "<<iluErrorString( error )<<"\n";
         image = 0;
         ilDeleteImages( 1, &imgage_id );
         return false;
      }
      cout<<"ilLoadImage: "<<ilGetError()<<"\n";
      image = 0;
      ilDeleteImages( 1, &imgage_id );
      return false;
   }

   GLint width = ilGetInteger( IL_IMAGE_WIDTH );
   GLint height = ilGetInteger( IL_IMAGE_HEIGHT );
   GLint type = ilGetInteger( IL_IMAGE_TYPE );
   GLint format = ilGetInteger( IL_IMAGE_FORMAT );

   glGenTextures( 1, &image );
   glBindTexture( GL_TEXTURE_2D, image );

   glTexParameteri( image, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( image, GL_TEXTURE_WRAP_T, GL_REPEAT );

   glPixelStorei( GL_UNPACK_SWAP_BYTES, GL_FALSE );
   glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
   glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
   glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
   glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );


   glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, type, ilGetData() );
   error_gl = glGetError();
   if( error_gl != GL_NO_ERROR and error_gl != GL_INVALID_ENUM ){
      cout<<"glTexImage2D: "<<gluErrorString( error_gl )<<"\n";
      return false;
   }

   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
   glGenerateMipmap( GL_TEXTURE_2D );

   ilDeleteImages( 1, &imgage_id );
   return true;
}

bool LoadAssimp( string file, vector <vec3> &vertices, vector <vec2> &uvs, vector <vec3> &normals, vector <GLuint> &indices ){
   vertices.clear();
   uvs.clear();
   normals.clear();
   indices.clear();
   Assimp::Importer importer;
   const aiScene* scene = importer.ReadFile( file.c_str(), 0 );
   if( !scene ){
      cout<<"importer.ReadFile: "<<importer.GetErrorString()<<"\n";
      return false;
   }
   const aiMesh* mesh = scene->mMeshes[0];
   unsigned int i = 0;
   aiVector3D tmp;
   //vertices:
   vertices.reserve( mesh->mNumVertices );
   for( i = 0; i < mesh->mNumVertices; ++i ){
      tmp = mesh->mVertices[i];
      vertices.push_back( vec3( tmp.x, tmp.y, tmp.z ) );
   }
   //uvs:
   uvs.reserve( mesh->mNumVertices );
   for( i = 0; i < mesh->mNumVertices; ++i ){
      tmp = mesh->mTextureCoords[0][i];
      uvs.push_back( vec2( tmp.x, tmp.y ) );
   }
   //normals:
   normals.reserve( mesh->mNumVertices );
   for( i = 0; i < mesh->mNumVertices; ++i ){
      tmp = mesh->mNormals[i];
      normals.push_back( vec3( tmp.x, tmp.y, tmp.z ) );
   }
   //indices:
   indices.reserve( 3*mesh->mNumFaces );
   for( i = 0; i < mesh->mNumFaces; ++i ){
      indices.push_back( mesh->mFaces[i].mIndices[0] );
      indices.push_back( mesh->mFaces[i].mIndices[1] );
      indices.push_back( mesh->mFaces[i].mIndices[2] );
   }
   return true;
}


#endif
