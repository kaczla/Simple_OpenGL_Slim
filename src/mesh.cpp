/*!
   \file mesh.cpp
   \brief Plik odpowiedzialny zarządzanie obiektami 3D.
*/
#ifndef __mesh_hpp__
#define __mesh_hpp__

/*!
   \brief klasa odpowiedzialny zarządzanie obiektami 3D.
*/
class Mesh{
   public:
      /*!
         \brief Konstruktor domyślny.
      */
      Mesh();
      /*!
         \brief Destruktor.

         Zwalnia pamięć zaalokowanych elementów w OpenGL.
      */
      ~Mesh();
      /*!
         \brief Konstruktor kopiujący.
      */
      Mesh( const Mesh &mesh );
      /*!
         \brief Operator przypisania.
      */
      Mesh & operator=( const Mesh &mesh );
      /*!
         \brief Zwraca identyfikator głównej tekstury ( \link Texture \endlink ).
      */
      GLuint ReturnTexture() const;
      /*!
         \brief Zwraca identyfikator spektralnej tekstury ( \link TextureSpecular \endlink ).
      */
      GLuint ReturnTextureSpecular() const;
      /*!
         \brief Zwraca macierz modelu ( \link ModelMatrix \endlink ).
      */
      mat4 ReturnModelMatrix() const;
      /*!
         \brief Ustala nową ścieżkę dla pliku .obj oraz głównej i spektralnej tekstury.

         \param name - nowa wartość dla zmiennej \link Name \endlink
         \param obj - nowa wartość dla zmiennej \link OBJPathFile \endlink
         \param img - nowa wartość dla zmiennej \link ImgPathFile \endlink
         \param spec - nowa wartość dla zmiennej \link ImgSpecPathFile \endlink
      */
      void SetString( string name, string obj, string img, string spec );
      /*!
         \brief Zmiena aktualną macierz modelu ( \link ModelMatrix \endlink ).

         \param matrix - nowa wartość dla zmiennej \link ModelMatrix \endlink
      */
      void SetModelMatrix( mat4 matrix );
      /*!
         \brief Zmiena aktualną macierz modelu ( \link ModelMatrix \endlink ) na nową przesuniętą o wektor.

         \param vector_translate - wektor przesunięcia macierzy modelu
      */
      void SetModelMatrix( vec3 vector_translate );
      /*!
         \brief Wczytuje plik .obj, teksture główną i spektralną do pamięci.
      */
      void LoadData();
      /*!
         \brief Tworzy VAO (Vertex Array Object).
      */
      void BindVAO();
      /*!
         \brief Rysuje obiekt.
      */
      void Draw();
      /*!
         \brief Translacja macierzy modelu ( \link ModelMatrix \endlink ).

         \param vector_translate - wartość o jaką zostanie przesunieta macierz modelu ( \link ModelMatrix \endlink )
      */
      void Translate( vec3 vector_translate );
      /*!
         \brief Rotacja macierzy modelu ( \link ModelMatrix \endlink ).

         \param angle_rotate - wartość kąta w stopniach o jaki zostanie obrócona macierz modelu ( \link ModelMatrix \endlink )
         \param vector_rotate - wartość wektora o jaki zostanie obrócona macierz modelu ( \link ModelMatrix \endlink )
      */
      void Rotate( GLfloat angle_rotate, vec3 vector_rotate );
      /*!
         \brief Skalowanie macierzy modelu ( \link ModelMatrix \endlink ).

         \param vector_scale - wartość o jaką zostanie przeskalowana macierz modelu ( \link ModelMatrix \endlink )
      */
      void Scale( vec3 vector_scale );
   private:
      /*!
         \brief Nazwa obiektu.
      */
      string Name;
      /*!
         \brief Wektor Wierzchołków.
      */
      vector <vec3> Vertices;
      /*!
         \brief Wektor UV Map.
      */
      vector <vec2> Uvs;
      /*!
         \brief Wektor Normalnych.
      */
      vector <vec3> Normals;
      /*!
         \brief Wektor Indeksów Wierzchołków.
      */
      vector <GLuint> Indices;
      /*!
         \brief Identyfikator VAO (Vertex Array Object).
      */
      GLuint VAO;
      /*!
         \brief Identyfikator Wierzchołków.
      */
      GLuint VertexBuffer;
      /*!
         \brief Identyfikator UV Map.
      */
      GLuint UvBuffer;
      /*!
         \brief Identyfikator Normalnych.
      */
      GLuint NormalBuffer;
      /*!
         \brief Identyfikator Indeksów Wierzchołków.
      */
      GLuint IndicesBuffer;
      /*!
         \brief Identyfikator głównej tekstury.
      */
      GLuint Texture;
      /*!
         \brief Identyfikator spektralnej tekstury.
      */
      GLuint TextureSpecular;
      /*!
         \brief Ścieżka do pliku .obj.
      */
      string OBJPathFile;
      /*!
         \brief Ścieżka do pliku głównej tekstury.
      */
      string ImgPathFile;
      /*!
         \brief Ścieżka do pliku spektralnej tekstury.
      */
      string ImgSpecPathFile;
      /*!
         \brief Macierz modelu.
      */
      mat4 ModelMatrix;
      /*!
         \brief Poprawność zainicjalizowanych wszystkich elementów. FALSE = Błąd.
      */
      bool Init = false;
};

/*
   ========
    SOURCE:
   ========
*/

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
