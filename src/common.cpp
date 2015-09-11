/*!
   \file common.cpp
   \brief Plik odpowiedzialny za ładowanie shaderów, tekstur i plików .obj.
*/
#ifndef __common_hpp__
#define __common_hpp__

/*!
   \brief Ładuje shader fragmentu i wierzchołków do pamięci.

   \param vertex - ścieżka do pliku z shaderem wierzchołków
   \param fragment - ścieżka do pliku z shaderem fragmentu
   \return - identyfikator programu z dołączonymi shaderami
*/
GLuint CreateShader( string vertex, string fragment );

/*!
   \brief Ładuje teksturę obiektu do pamięci.

   \param img_path_file - ścieżka do pliku z teksturą obiektu
   \param image - identyfikator tekstury obiektu
   \return - wartość logiczną dla ładowania tekstury, FALSE = błąd

   Wykorzystuje bibliotekę DevIL.
*/
bool LoadImg( const char *img_path_file, GLuint &image );

/*!
   \brief Ładuje plik .obj do pamięci.

   \param file - ścieżka do pliku .obj
   \param vertices - wektor Wierzchołków
   \param uvs - wektor UV Map
   \param normals - wektor Normalnych
   \param indices - wektor Indeksów Wierzchołków
   \return - wartość logiczną dla ładowania pliku .obj, FALSE = błąd

   Wykorzystuje bibliotekę assimp.
*/
bool LoadAssimp( string file, vector <vec3> &vertices, vector <vec2> &uvs, vector <vec3> &normals, vector <GLuint> &indices );

/*
   ========
    SOURCE:
   ========
*/

GLuint CreateShader( string vertex, string fragment ){
   /*
      Tworzenie shadera wierzchołków i fragmentu
      Zmienne w których przypisane będą ww shadery
   */
   GLuint VertexShaderID = glCreateShader( GL_VERTEX_SHADER );
   GLuint FragmentShaderID = glCreateShader( GL_FRAGMENT_SHADER );

   /*
      Zmienne dla pobierania tekstu z plików tekstowych z shaderami
   */
   string Line;
   //vertex_shader:
   /*
      Zmienna dla całego kodu shadera wierzchołków.
   */
   string VertexShaderCode;
   /*
      Otwarcie pliku tekstowego do odczytu
   */
   ifstream VertexShaderStream( vertex.c_str() );
   /*
      Sprawdzenie czy plik został poprawnie otwarty.
   */
   if( VertexShaderStream.good() ){
      Line = "";
      /*
         Dopuki coś jest w pliku to pobierz całą linię tekstu do zmiennej Line.
      */
      while( getline( VertexShaderStream, Line ) ){
         /*
            Dodaj to do zmiennej, w której będzie cały kod shadera.
         */
         VertexShaderCode += Line + "\n";
      }
      /*
         Zamknięcie pliku.
      */
      VertexShaderStream.close();
   }
   /*
      W przeciwnym wypadku wypisz błąd otwarcia pliku.
   */
   else{
      cout<<"File problem: "<<vertex<<"\n";
      return 0;
   }
   /*
      Podobnie dla shadera fragmentu.
   */
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

   /*
      Zmienna dla sprawdzenia błędu w OpenGL.
   */
   GLint Result;
   /*
      Zmienna informaująca ile znaków potrzebnych jest do wyświetlenia pełnego komunikatu o błędzie.
   */
   GLint InfoLogLength;
   string Error;

   /*
      Zamiana ze string na const char * (aby nie było problemów z dopasowaniem typów).
   */
   const char *VertexShaderCodePointer = VertexShaderCode.c_str();
   /*
      Dodanie źródła dla kompilacji shadera wierchołków.
   */
   glShaderSource( VertexShaderID, 1, &VertexShaderCodePointer, 0 );
   /*
      Kompilowanie shadera wierchołków.
   */
   glCompileShader( VertexShaderID );
   //Check vertex_shader:
   Result = GL_FALSE;
   /*
      Sprawdzenie kodu błędu.
   */
   glGetShaderiv( VertexShaderID, GL_COMPILE_STATUS, &Result );
   /*
      Gdy jest błąd to wyświetl go.
   */
   if( Result == GL_FALSE ){
      InfoLogLength = 0;
      /*
         Pobranie do zmiennej InfoLogLength ilości znaków dla tekstu błedu.
      */
      glGetShaderiv( VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength );
      /*
         Wektor znaków dla OpenGL.
      */
      vector <GLchar> VertexShaderErrorMessage(InfoLogLength);
      /*
         Pobranie tekstu błędu do zmiennej VertexShaderErrorMessage o ilości znaków InfoLogLength.
      */
      glGetShaderInfoLog( VertexShaderID, InfoLogLength, &InfoLogLength, &VertexShaderErrorMessage[0] );
      /*
         Przekopiowanie z wektora VertexShaderErrorMessage zmiennej string Error
      */
      Error = string( VertexShaderErrorMessage.begin(), VertexShaderErrorMessage.end() );
      /*
         Wyświetlenie błedu.
      */
      cout<<"Vertex shader: "<<Error<<"\n";
      /*
         Usunięcie shadera wierzchołków z pamięci.
      */
      glDeleteShader( VertexShaderID );
      return 0;
   }

   //fragment_shader:
   /*
      Tak samo dla shadera fragmentu.
   */
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
   /*
      Stworzenie programy z wszystkimi shaderami.
   */
   GLuint ProgramID = glCreateProgram();
   /*
      Dołączenie shadera wierzchołków do programu.
   */
   glAttachShader( ProgramID, VertexShaderID );
   /*
      Dołączenie shadera fragmentu do programu.
   */
   glAttachShader( ProgramID, FragmentShaderID );
   /*
      Linkuje program, aby mógł być wykorzystany później.
   */
   glLinkProgram( ProgramID );

   //Check program:
   /*
      Sprawdzenie poprawności stworzonego programu.
   */
   glGetProgramiv( ProgramID, GL_LINK_STATUS, &Result );
   /*
      Tak samo jak wcześniej, dla sprawdzania błędów w shaderach.
   */
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
   /*
      Wyczyszczenie pamięci po stworzonych shaderach, które teraz są w ProgramID.
   */
   glDetachShader( ProgramID, VertexShaderID );
   glDetachShader( ProgramID, FragmentShaderID );
   glDeleteShader( VertexShaderID );
   glDeleteShader( FragmentShaderID );

   /*
      Zwróć identyfikator programu shaderów.
   */
   return ProgramID;
}

bool LoadImg( const char *img_path_file, GLuint &image ){
   ILenum error;
   GLenum error_gl;
   ILboolean success;
   ILuint imgage_id;

   /*
      Tworzy identyfikator dla wczytywanej grafiki.
   */
   ilGenImages( 1, &imgage_id );
   /*
      Przygotowywuje dla wczytywania grafiki.
   */
   ilBindImage( imgage_id );
   /*
      Załadowanie pliku grafiki o nazwie img_path_file do pamięci.
   */
   success = ilLoadImage( img_path_file );
   /*
      Sprawdzenie3 czy jest błąd.
   */
   if( ! success ){
      /*
         Otrzymanie numeru błędu.
      */
      error = ilGetError();
      /*
         Sprawdzenie czy ten kod jest błędem.
      */
      if( error != IL_NO_ERROR ){
         /*
            Wyświetl bład.
         */
         cout<<"ilLoadImage ("<<img_path_file<<"): "<<iluErrorString( error )<<"\n";
         image = 0;
         /*
            Usuń z pamięci.
         */
         ilDeleteImages( 1, &imgage_id );
         return false;
      }
      /*
         Gdyby były błedy z wczytanie a kod błedu na to nie wskazywał.
      */
      cout<<"ilLoadImage ("<<img_path_file<<"): "<<ilGetError()<<"\n";
      image = 0;
      /*
         Usuń z pamięci.
      */
      ilDeleteImages( 1, &imgage_id );
      return false;
   }

   /*
      Szerokość obrazka
   */
   GLint width = ilGetInteger( IL_IMAGE_WIDTH );
   /*
      Wysokość obrazka
   */
   GLint height = ilGetInteger( IL_IMAGE_HEIGHT );
   /*
      Typ obrazka (np. RGB lub RGBA).
   */
   GLint type = ilGetInteger( IL_IMAGE_TYPE );
   /*
      Specyfikacja pikseli (jak są reprezentowane, np. unsigned int).
   */
   GLint format = ilGetInteger( IL_IMAGE_FORMAT );

   /*
      Tworzy identyfikator tekstury
   */
   glGenTextures( 1, &image );
   /*
      Do wcześniej stworzonego identyfikatora stwórz teksturę 2D
   */
   glBindTexture( GL_TEXTURE_2D, image );

   /*
      Kopiuje grafikę z DevIL do OpenGL.

      ilGetData() - przekazanie całego obrazka (danych), który jest aktualnie przetwarzany.
   */
   glTexImage2D( GL_TEXTURE_2D, 0, format, width, height, 0, format, type, ilGetData() );
   /*
      Sprawdzenie czy nie ma błedu.
   */
   error_gl = glGetError();
   if( error_gl != GL_NO_ERROR and error_gl != GL_INVALID_ENUM ){
      cout<<"glTexImage2D ("<<img_path_file<<"): "<<gluErrorString( error_gl )<<"\n";
      return false;
   }

   /*
      Tworzenie automatycznej Mipmapy, im dalej tym gorsza tekstura.
   */
   glGenerateMipmap( GL_TEXTURE_2D );

   /*
      Typ powtarzania obrazka, gdy się skończy dana tekstura.
   */
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
   /*
      Jak ma być skalowana tekstura. Typ skalowania.
   */
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
   glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

   /*
      Czyszczenie.
   */
   glBindTexture(GL_TEXTURE_2D, 0);

   /*
      Usunięcie z pamięci obrazka w DevIL.
   */
   ilDeleteImages( 1, &imgage_id );
   return true;
}

bool LoadAssimp( string file, vector <vec3> &vertices, vector <vec2> &uvs, vector <vec3> &normals, vector <GLuint> &indices ){
   /*
      Dane wyjściowe dla wierzchołków
   */
   vertices.clear();
   /*
      Dane wyjściowe dla UV Map
   */
   uvs.clear();
   /*
      Dane wyjściowe dla Normalnych
   */
   normals.clear();
   /*
      Dane wyjściowe dla kolejności trójkątów
   */
   indices.clear();
   /*
      Tworzenie importer dla ładowania danych.
   */
   Assimp::Importer importer;
   /*
      Wczytywanie pliku file (.obj)
   */
   const aiScene* scene = importer.ReadFile( file.c_str(), 0 );
   /*
      Sprawdzenie czy nie ma błedu.
   */
   if( !scene ){
      cout<<"importer.ReadFile ("<<file<<"):  "<<importer.GetErrorString()<<"\n";
      return false;
   }
   /*
      Wczytujemy tylko pierwszą część obiektu, inne pomijamy(występuje w obiektach kilku elementowych/częściowych).
   */
   const aiMesh* mesh = scene->mMeshes[0];
   unsigned int i = 0;
   /*
      Wektor dla pobierania danych.
   */
   aiVector3D tmp;
   //vertices:
   /*
      Wierzchołki obiektu.
   */
   vertices.reserve( mesh->mNumVertices );
   for( i = 0; i < mesh->mNumVertices; ++i ){
      tmp = mesh->mVertices[i];
      vertices.push_back( vec3( tmp.x, tmp.y, tmp.z ) );
   }
   //uvs:
   /*
      UV Mapy
   */
   uvs.reserve( mesh->mNumVertices );
   for( i = 0; i < mesh->mNumVertices; ++i ){
      tmp = mesh->mTextureCoords[0][i];
      //important!
      //This is done because most images have the top y-axis inversed with OpenGL's top y-axis.
      //or conver in shader
      uvs.push_back( glm::vec2( tmp.x, 1.0 - tmp.y ) );
   }
   //normals:
   /*
      Normalne
   */
   normals.reserve( mesh->mNumVertices );
   for( i = 0; i < mesh->mNumVertices; ++i ){
      tmp = mesh->mNormals[i];
      normals.push_back( vec3( tmp.x, tmp.y, tmp.z ) );
   }
   //indices:
   /*
      Kolejność rysowania trójkątów oraz jak każdy jest reprezentowany przez wierzchołki.
   */
   indices.reserve( 3*mesh->mNumFaces );
   for( i = 0; i < mesh->mNumFaces; ++i ){
      indices.push_back( mesh->mFaces[i].mIndices[0] );
      indices.push_back( mesh->mFaces[i].mIndices[1] );
      indices.push_back( mesh->mFaces[i].mIndices[2] );
   }
   return true;
}


#endif
