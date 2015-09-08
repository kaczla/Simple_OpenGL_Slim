#ifndef __mesh_hpp__
#define __mesh_hpp__

class Mesh{
   public:
      Mesh();
      ~Mesh();
      Mesh( const Mesh &mesh );
      Mesh & operator=( const Mesh &mesh );
      GLuint ReturnTexture() const;
      GLuint ReturnTextureSpecular() const;
      mat4 ReturnModelMatrix() const;
      void SetString( string name, string obj, string img, string spec );
      void SetModelMatrix( mat4 matrix );
      void SetModelMatrix( vec3 vector_translate );
      void LoadData();
      void BindVAO();
      void Draw();
      void Translate( vec3 vector_translate );
      void Rotate( GLfloat angle_rotate, vec3 vector_rotate );
      void Scale( vec3 vector_scale );
   private:
      string Name;
      vector <vec3> Vertices;
      vector <vec2> Uvs;
      vector <vec3> Normals;
      vector <GLuint> Indices;
      GLuint VAO;
      GLuint VertexBuffer;
      GLuint UvBuffer;
      GLuint NormalBuffer;
      GLuint IndicesBuffer;
      GLuint Texture;
      GLuint TextureSpecular;
      string OBJPathFile;
      string ImgPathFile;
      string ImgSpecPathFile;
      mat4 ModelMatrix;
      bool Init = false;
};

Mesh::Mesh(){
}

Mesh::~Mesh(){
   glDeleteTextures( 1, &this->Texture );
   glDeleteTextures( 1, &this->TextureSpecular );
   glDeleteBuffers( 1, &this->VertexBuffer );
   glDeleteBuffers( 1, &this->UvBuffer );
   glDeleteBuffers( 1, &this->NormalBuffer );
   glDeleteBuffers( 1, &this->IndicesBuffer );
   glDeleteVertexArrays( 1, &this->VAO );
}

Mesh::Mesh( const Mesh &mesh ){
   this->Name = mesh.Name;
   this->Vertices = mesh.Vertices;
   this->Uvs = mesh.Uvs;
   this->Normals = mesh.Normals;
   this->Indices = mesh.Indices;
   this->VAO = mesh.VAO;
   this->VertexBuffer = mesh.VertexBuffer;
   this->UvBuffer = mesh.UvBuffer;
   this->NormalBuffer = mesh.NormalBuffer;
   this->IndicesBuffer = mesh.IndicesBuffer;
   this->Texture = mesh.Texture;
   this->TextureSpecular = mesh.TextureSpecular;
   this->OBJPathFile = mesh.OBJPathFile;
   this->ImgPathFile = mesh.ImgPathFile;
   this->ImgSpecPathFile = mesh.ImgSpecPathFile;
   this->ModelMatrix = mesh.ModelMatrix;
}

Mesh & Mesh::operator=( const Mesh &mesh ){
   this->Name = mesh.Name;
   this->Vertices = mesh.Vertices;
   this->Uvs = mesh.Uvs;
   this->Normals = mesh.Normals;
   this->Indices = mesh.Indices;
   this->VAO = mesh.VAO;
   this->VertexBuffer = mesh.VertexBuffer;
   this->UvBuffer = mesh.UvBuffer;
   this->NormalBuffer = mesh.NormalBuffer;
   this->IndicesBuffer = mesh.IndicesBuffer;
   this->Texture = mesh.Texture;
   this->TextureSpecular = mesh.TextureSpecular;
   this->OBJPathFile = mesh.OBJPathFile;
   this->ImgPathFile = mesh.ImgPathFile;
   this->ImgSpecPathFile = mesh.ImgSpecPathFile;
   this->ModelMatrix = mesh.ModelMatrix;
   return *this;
}

GLuint Mesh::ReturnTexture() const{
   return this->Texture;
}

GLuint Mesh::ReturnTextureSpecular() const{
   return this->TextureSpecular;
}

mat4 Mesh::ReturnModelMatrix() const{
   return this->ModelMatrix;
}

void Mesh::SetString( string name, string obj, string img, string spec ){
   this->Name = name;
   this->OBJPathFile = obj;
   this->ImgPathFile = img;
   this->ImgSpecPathFile = spec;
}

void Mesh::SetModelMatrix( mat4 matrix ){
   this->ModelMatrix = matrix;
}

void Mesh::SetModelMatrix( vec3 vector_translate ){
   this->ModelMatrix = translate( mat4( 1.0f ), vector_translate );
}

void Mesh::LoadData(){
   if( OBJPathFile.empty() or ImgPathFile.empty() or ImgSpecPathFile.empty() ){
      cout<<"Set string!";
      return;
   }
   else{
      this->Init = LoadAssimp( this->OBJPathFile.c_str(), this->Vertices, this->Uvs, this->Normals, this->Indices );
      if( ! this->Init ){
         return;
      }
      this->Init = LoadImg( this->ImgPathFile.c_str(), this->Texture );
      if( ! this->Init ){
         return;
      }
      this->Init = LoadImg( this->ImgSpecPathFile.c_str(), this->TextureSpecular );
      if( ! this->Init ){
         return;
      }
      this->BindVAO();
      cout<<"Name: \""<<this->Name<<"\" success load.\n";
   }
}

void Mesh::BindVAO(){
   if( this->Init ){
      glGenVertexArrays( 1, &this->VAO );
      glGenBuffers( 1, &this->VertexBuffer );
      glGenBuffers( 1, &this->UvBuffer );
      glGenBuffers( 1, &this->NormalBuffer );
      glGenBuffers( 1, &this->IndicesBuffer );

      //Vertex:
      glBindBuffer( GL_ARRAY_BUFFER, this->VertexBuffer );
      glBufferData( GL_ARRAY_BUFFER, this->Vertices.size() * sizeof( vec3 ), &this->Vertices[0], GL_STATIC_DRAW );
      //Uv:
      glBindBuffer( GL_ARRAY_BUFFER, this->UvBuffer );
      glBufferData( GL_ARRAY_BUFFER, this->Uvs.size() * sizeof( vec2 ), &this->Uvs[0], GL_STATIC_DRAW );
      //Normal:
      glBindBuffer( GL_ARRAY_BUFFER, this->NormalBuffer );
      glBufferData( GL_ARRAY_BUFFER, this->Normals.size() * sizeof( vec3 ), &this->Normals[0], GL_STATIC_DRAW );

      //VAO:
      glBindVertexArray( this->VAO );

      //Vertex:
      glBindBuffer( GL_ARRAY_BUFFER, this->VertexBuffer );
      glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0 );
      glEnableVertexAttribArray( 0 );
      //Uv:
      glBindBuffer( GL_ARRAY_BUFFER, this->UvBuffer );
      glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0 );
      glEnableVertexAttribArray( 1 );
      //Normal:
      glBindBuffer( GL_ARRAY_BUFFER, this->NormalBuffer );
      glVertexAttribPointer( 2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0 );
      glEnableVertexAttribArray( 2 );
      //Indicies:
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, this->IndicesBuffer );
      glBufferData( GL_ELEMENT_ARRAY_BUFFER, this->Indices.size() * sizeof(GLuint), &this->Indices[0], GL_STATIC_DRAW );

      glBindVertexArray( 0 );
   }
   else{
      cout<<"Load files before bind!\n";
   }
}

void Mesh::Draw(){
   glBindVertexArray( this->VAO );
   glDrawElements( GL_TRIANGLES, this->Indices.size(), GL_UNSIGNED_INT, (GLvoid *)0 );
}

void Mesh::Translate( vec3 vector_translate ){
   this->ModelMatrix = translate( this->ModelMatrix, vector_translate );
}

void Mesh::Rotate( GLfloat angle_rotate, vec3 vector_rotate ){
   this->ModelMatrix = rotate( this->ModelMatrix, radians( angle_rotate ), vector_rotate );
}

void Mesh::Scale( vec3 vector_scale ){
   this->ModelMatrix = scale( this->ModelMatrix, vector_scale );
}

#endif
