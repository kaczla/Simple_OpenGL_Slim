/*!
   \mainpage Główna strona:
   Więcej informacji pod adresem: <a href="https://github.com/kaczla/Simple_OpenGL_Slim">LINK</a>
*/
/*!
   \file main.cpp
   \brief Plik główny

   W plik main.cpp znajduje się \link main() \endlink oraz klasa \link Gra \endlink.
*/
#include "header.hpp"
#include "common.cpp"
#include "camera.cpp"
#include "mesh.cpp"
#include "light.cpp"

/*!
   \brief Główna klasa, w której gromadzone są wszystkich informacje potrzebne do uruchomienia aplikacji.
*/
class Gra{
   public:
      /*!
         \brief Inicjalizuje biblioteki, tworzy okno aplikacji, ładuje shadery oraz wszystkie obiekty.

         Inicjalizuje biblioteki:\n
         <ul>
         <li>SDL2</li>
         <li>GLEW</li>
         <li>DevIL</li>
         </ul>
         Tworzy okno oraz kontekst dla OpenGL 3.3.\n
         Ładuje shader wierzchołków i fragmentu oraz ustala uniformy.\n
         Wczytuje wszystkie obiekty z plików .obj z teksturami.
      */
      Gra();
      /*!
      \brief Czyści zaalokowaną pamięć.

      Usuwa niepotrzebnie zaalokowaną pamięć.\n
      Deaktywuje aktywne biblioteki.\n
      */
      ~Gra();
      /*!
         \brief Urchamia aplikację.
      */
      void Start();
   private:
      /*!
         \brief Rysowanie wszystkich obiektów.

         Przekazanie wszystkich wartości do shaderów.\n
         Rysowanie wszystkich obiektów.\n
      */
      void Update();
      /*!
         \brief Poprawność zainicjalizowanych wszystkich elementów. FALSE = Błąd.
      */
      bool CheckInit = true;
      /*!
         \brief Wskaźnik dla okna SDL2.
      */
      SDL_Window *Okno = NULL;
      /*!
         \brief Wysokość okna, domyślnie 600.
      */
      int Wysokosc = 600;
      /*!
         \brief Szerokość okna, domyślnie 800.
      */
      int Szerokosc = 800;
      /*!
         \brief Wskaźnik dla kontekstu Opengl dla okna SDL2.
      */
      SDL_GLContext Kontekst = NULL;
      /*!
         \brief Typ zdarzenia (SDL2).
      */
      SDL_Event Event;
      //Shader:
      /*!
         \brief Ścieżka do shadera wierzchołków.
      */
      string vertex = "./data/Shader.vert";
      /*!
         \brief Ścieżka do shadera fragmentu.
      */
      string fragment = "./data/Shader.frag";
      /*!
         \brief identyfikator programu dla shaderów.
      */
      GLuint ProgramID = 0;
      //Uniforms:
      /*!
         \brief Uniform dla macierzy modelu.
      */
      GLuint UniformModel;
      /*!
         \brief Uniform dla macierzy widoku.
      */
      GLuint UniformView;
      /*!
         \brief Uniform dla macierzy projekcji.
      */
      GLuint UniformProjection;
      /*!
         \brief Uniform dla tekstury głównej obiektu.
      */
      GLuint UniformTexture;
      /*!
         \brief Uniform dla tekstury spektralnej obiektu.
      */
      GLuint UniformTextureSpecular;
      /*!
         \brief Uniform dla pozycji kamery.
      */
      GLuint UniformViewPos;
      /*!
         \brief Uniform dla pozycji światła numer 1.
      */
      GLuint UniformLightPosition_1;
      /*!
         \brief Uniform dla wartości Ambient światła numer 1.
      */
      GLuint UniformLightAmbient_1;
      /*!
         \brief Uniform dla wartości Diffuse światła numer 1.
      */
      GLuint UniformLightDiffuse_1;
      /*!
         \brief Uniform dla wartości Specular światła numer 1.
      */
      GLuint UniformLightSpecular_1;
      /*!
         \brief Uniform dla pozycji światła numer 2.
      */
      GLuint UniformLightPosition_2;
      /*!
         \brief Uniform dla wartości Ambient światła numer 2.
      */
      GLuint UniformLightAmbient_2;
      /*!
         \brief Uniform dla wartości Diffuse światła numer 2.
      */
      GLuint UniformLightDiffuse_2;
      /*!
         \brief Uniform dla wartości Specular światła numer 2.
      */
      GLuint UniformLightSpecular_2;
      //Camera:
      /*!
         \brief Kamera, miejsce z którego będzie przetwarzana cała scena OpenGL.
      */
      Camera camera;
      /*!
         \brief Aktualne poruszenie myszki, różnica pomiędzy poprzednią, a aktualną pozycją myszki.
      */
      vec2 Mouse;
      //All items:
      /*!
         \brief Wektor wszystkich obiektów.
      */
      vector <Mesh> Item;
      /*!
         \brief Iterator dla wektora wszystkich obiektów.
      */
      vector <Mesh>::iterator It_Item;
      //Lights:
      /*!
         \var light1
         \brief Światło numer 1.
      */
      /*!
         \var light2
         \brief Światło numer 2.
      */
      Light light1, light2;
};

/*
   ========
    SOURCE:
   ========
*/

/*!
   \brief Główna funkcja uruchamiająca całą aplikację.
*/
int main( int argc, char* argv[] ){
   /*
      Stworzenie klasy.
   */
   Gra gra;
   /*
      Uruchomienie aplikacji.
   */
   gra.Start();
   return 0;
}

Gra::Gra(){
   //SDL2:
   /*
      Inicjalizuje bibliotekę SDL2.
      SDL_INIT_EVERYTHING - uruchamia wszystkie moduły biblioteki SDL2.
   */
   if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
      /*
         Wyświetl błąd, gdy jest mniejszy od 0.
      */
      cout<<"SDL_Init: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }
   /*
      Ustalenie wersji OpenGL dla SDL2, w tym przypadku jest to OpenGL 3.3
   */
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
   /*
      Profil Core dla OpenGL.
   */
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
   /*
      Profil Core OpenGL dla biblioteki GLEW.
   */
   glewExperimental = true;
   /*
      Stworzenie okna o tytule: OpenGL
      Okna na pozycji 0,0
      Wielkość okna Szerokosc x Wysokosc
      SDL_WINDOW_OPENGL - flaga dla okna, aby wiedział że to jest okno dla OpenGL
   */
   this->Okno = SDL_CreateWindow( "OpenGL", 0, 0, this->Szerokosc, this->Wysokosc, SDL_WINDOW_OPENGL );
   if( this->Okno == NULL ){
      /*
         W razie błędu wypisz go.
      */
      cout<<"SDL_CreateWindow: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }
   /*
      Tryb Relative Mouse Mode - ukrycie myszki.
   */
   SDL_SetRelativeMouseMode( SDL_TRUE );
   /*
      Utworzenie kontekstu dla OpenGL dla okna w SDL2.
   */
   this->Kontekst = SDL_GL_CreateContext( this->Okno );
   if( this->Kontekst == NULL ){
      /*
         W razie błędu wypisz go.
      */
      cout<<"SDL_GL_CreateContext: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }

   //GLEW:
   /*
      Inicjalizuje bibliotekę GLEW.
   */
   GLenum GL_Error = glewInit();
   if( GL_Error != GLEW_OK  ){
      /*
         W razie błędu wypisz go.
      */
      cout<<"glewInit: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }
   /*
      Włącz Z-buffor (bufor głębokości).
   */
   glEnable( GL_DEPTH_TEST );
   /*
      Jaka funkcja dla Z-buffor (bufor głębokości).
   */
   glDepthFunc( GL_LESS );
   /*
      Ucinanie/usuwanie nie elementów przy rysowaniu. Domyślnie ucina/usuwa tylne ściany, które są niewidoczne.
   */
   glEnable( GL_CULL_FACE );
   /*
      Kolor czyszczenia.
   */
   glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
   //DevIL
   /*
      Inicjalizuje DevIL.
   */
   ilInit();
   /*
      Inicjalizuje pomocniczą bibliotekę dla DevIL (w celu wyświetlania tekstowych błędów).
   */
   iluInit();
   ILenum IL_Error;
   while( ( IL_Error = ilGetError() ) != IL_NO_ERROR ){
      /*
         W razie błędu wypisz go.
      */
      cout<<"DevIL: "<<iluErrorString( IL_Error )<<"\n";
      this->CheckInit = false;
      return;
   }
   //Shader:
   /*
      Tworzy program z shaderami.
   */
   this->ProgramID = CreateShader( vertex, fragment );
   if( this->ProgramID <= 0 ){
      /*
         W razie błędu wypisz go.
      */
      cout<<"Shader error:"<<this->ProgramID<<"\n";
      this->CheckInit = false;
      return;
   }
   /*
      Ustala wskaźniki dla położenia uniformów w pamięci GPU.
      np.
      this->ProgramID - identyfikator programu shadera
      "model" - nazwa uniformu
   */
   this->UniformModel = glGetUniformLocation( this->ProgramID, "model" );
   this->UniformView = glGetUniformLocation( this->ProgramID, "view" );
   this->UniformProjection = glGetUniformLocation( this->ProgramID, "projection" );
   this->UniformTexture = glGetUniformLocation( this->ProgramID, "Model.Texture" );
   this->UniformTextureSpecular = glGetUniformLocation( this->ProgramID, "Model.Texture_specular" );
   this->UniformViewPos = glGetUniformLocation( this->ProgramID, "ViewPos" );
   this->UniformLightPosition_1 = glGetUniformLocation( this->ProgramID, "DirectionalLight[0].Position" );
   this->UniformLightAmbient_1 = glGetUniformLocation( this->ProgramID, "DirectionalLight[0].Ambient" );
   this->UniformLightDiffuse_1 = glGetUniformLocation( this->ProgramID, "DirectionalLight[0].Diffuse" );
   this->UniformLightSpecular_1 = glGetUniformLocation( this->ProgramID, "DirectionalLight[0].Specular" );
   this->UniformLightPosition_2 = glGetUniformLocation( this->ProgramID, "DirectionalLight[1].Position" );
   this->UniformLightAmbient_2 = glGetUniformLocation( this->ProgramID, "DirectionalLight[1].Ambient" );
   this->UniformLightDiffuse_2 = glGetUniformLocation( this->ProgramID, "DirectionalLight[1].Diffuse" );
   this->UniformLightSpecular_2 = glGetUniformLocation( this->ProgramID, "DirectionalLight[1].Specular" );

   //Data:
   /*
      Wczytywanie danych z pliku: ./data/data.init
   */
   fstream file;
   file.open( "./data/data.init", ios::in );
   if( file.good() ){
      /*
         stringstream dla łatwego zarządzania buforem tekstu z pliku.
      */
      stringstream tmp_stream;
      string tmp_string;
      string tmp_name, tmp_obj, tmp_img, tmp_spec;
      GLfloat tmp_float;
      vec3 tmp_vector_vec3;
      /*
         Dopóki coś będzie w pliku to pobierz do zmiennej tmp_string
      */
      while( getline( file, tmp_string ) ){
         /*
            Czyszczenie strumienia tmp_stream.
            samo clear() - czyści tylko FLAGI strumeinia!
            wyczyszczenie strumienia z tekstu można, np. tmp_stream.str( "" );
         */
         tmp_stream.clear();
         /*
            Dodanie tesktu do strumienia.
         */
         tmp_stream.str( tmp_string );
         /*
            Stworzenie tymczasowego obiektu.
         */
         Mesh tmp_item;
         //Set string
         /*
            Pobranie ze strumienia nazwy pliku.
         */
         tmp_stream >> tmp_name;
         /*
            Pobranie ze strumienia nazwy pliku .obj.
         */
         tmp_stream >> tmp_obj;
         /*
            Pobranie ze strumienia nazwy pliku głównej tekstury.
         */
         tmp_stream >> tmp_img;
         /*
            Pobranie ze strumienia nazwy pliku spektralnej tekstury.
         */
         tmp_stream >> tmp_spec;
         /*
            Ustalenie wszystkich plików do tymczasowego obiektu.
         */
         tmp_item.SetString( tmp_name,
                             "./data/" + tmp_obj,
                             "./data/" + tmp_img,
                             "./data/" + tmp_spec
                           );
         //Set model matrix
         /*
            Pobranie danych o położeniu obiektu w świecie z strumienia.
         */
         tmp_stream >> tmp_float;
         tmp_vector_vec3.x = tmp_float;
         tmp_stream >> tmp_float;
         tmp_vector_vec3.y = tmp_float;
         tmp_stream >> tmp_float;
         tmp_vector_vec3.z = tmp_float;
         /*
            Ustalenie położenia dla obiektu (macierz modelu).
         */
         tmp_item.SetModelMatrix( tmp_vector_vec3 );
         //Push back
         /*
            Dodanie go do wektora Item.
         */
         this->Item.push_back( tmp_item );
      }
      /*
         Załadowanie wszystkich wczytanych danych do pamięcie.
         Wykorzystane są iteratory dla wektora.
      */
      for( this->It_Item = this->Item.begin(); this->It_Item != this->Item.end(); ++this->It_Item ){
         this->It_Item->LoadData();
      }
   }
   else{
      /*
         W razie błędu z otwarciem pliku, wypisz błąd.
      */
      cout<<"File error: ./data/data.init\n";
      this->CheckInit = false;
      return;
   }
   //Lights:
   /*
      Położenie 1 światła.
   */
   vec3 tmp_vector_vec3 = vec3( 0.0f, 15.0f, 0.0f );
   this->light1.SetPosition( tmp_vector_vec3 );
   /*
      Położenie 2 światła.
   */
   tmp_vector_vec3 = vec3( 15.0f, 0.0f, 15.0f );
   this->light2.SetPosition( tmp_vector_vec3 );
}

Gra::~Gra(){
   /*
      Usunięcie programu z shaderami z pamięci.
   */
   glDeleteProgram( this->ProgramID );
   SDL_SetRelativeMouseMode( SDL_FALSE );
   /*
      Usunięcie kontekstu i okna.
   */
   SDL_GL_DeleteContext( this->Kontekst );
   SDL_DestroyWindow( this->Okno );
   /*
      Deaktywowanie SDL2.
   */
   SDL_Quit();
}

void Gra::Start(){
   /*
      Gry wszystko jest załadowane, to zacznij odbierać sygnały zdarzeń w SDL2 (klawiatury i myszy).
   */
   while( this->CheckInit ){
      /*
         Wykonuj dopóki jest jakieś zdarzenie w SDL2.
      */
      while( SDL_PollEvent( & this->Event ) ){
         /*
            Podział na typt zdarzeń w SDL2.
         */
         switch( this->Event.type ){
            /*
               Zamknięcie okna krzyżykiem w narożniku.
            */
            case SDL_QUIT:
               this->CheckInit = false;
               break;
            /*
               Akcja poruszenia myszki.
            */
            case SDL_MOUSEMOTION:
               /*
                  Różnica pomiędzy ostaną i aktualną pozycją myszki.
               */
               this->Mouse.x = -this->Event.motion.xrel;
               this->Mouse.y = -this->Event.motion.yrel;
               /*
                  Wyślij to do kamery.
               */
               this->camera.MouseUpdate( this->Mouse );
               /*
                  Ustaw myszkę na środku ekranu.
               */
               SDL_WarpMouseInWindow( this->Okno, ( this->Wysokosc / 2 ), ( this->Szerokosc / 2 ) );
               break;
            /*
               Akcja wciśnięcia klawisza.
            */
            case SDL_KEYDOWN:
               switch( this->Event.key.keysym.sym ){
                  /*
                  ESC - wyjście z aplikacji.
                  */
                  case SDLK_ESCAPE:
                     this->CheckInit = false;
                     break;
                  /*
                     Poruszenie kamery do przodu (prze siebie).
                  */
                  case SDLK_UP:
                  case SDLK_w:
                     this->camera.MoveForward();
                     break;
                  /*
                     Poruszenie kamery do tyłu.
                  */
                  case SDLK_DOWN:
                  case SDLK_s:
                     this->camera.MoveBackward();
                     break;
                  /*
                     Poruszenie kamery w lewo.
                  */
                  case SDLK_LEFT:
                  case SDLK_a:
                     this->camera.MoveLeft();
                     break;
                  /*
                     Poruszenie kamery w prawo.
                  */
                  case SDLK_RIGHT:
                  case SDLK_d:
                     this->camera.MoveRight();
                     break;
                  /*
                     Poruszenie kamery do góry.
                  */
                  case SDLK_SPACE:
                     this->camera.MoveUp();
                     break;
                  /*
                     Poruszenie kamery w dół.
                  */
                  case SDLK_LCTRL:
                  case SDLK_c:
                     this->camera.MoveDown();
                     break;
                  default:
                     break;
               }
               break;
            default:
               break;
         }
      }
      //Update:
      /*
         Rysowanie wszystkich elementów.
      */
      this->Update();
   }
}

void Gra::Update(){
   /*
      Wyczyszczenie ekranu.
   */
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   /*
      Użycie programu shadera.
   */
   glUseProgram( this->ProgramID );
   /*
      Przekazanie wartości do uniformów.

      value_ptr - zwraca wskaźnik do każdego typu danych

      W kolejności:
      - macierz widoku
      - macierz projekcji

      - pozycja światła 1
      - wartość Ambient światła 1
      - wartość Diffuse światła 1
      - wartość Specular światła 1

      - pozycja światła 2
      - wartość Ambient światła 2
      - wartość Diffuse światła 2
      - wartość Specular światła 2

      - pozycja kamery
   */
   glUniformMatrix4fv( this->UniformView, 1, GL_FALSE, value_ptr( this->camera.ReturnViewMatrix() ) );
   glUniformMatrix4fv( this->UniformProjection, 1, GL_FALSE, value_ptr( this->camera.ReturnProjectionMatrix() ) );

   glUniform3fv( this->UniformLightPosition_1, 1, value_ptr( this->light1.ReturnPosition() ) );
   glUniform3fv( this->UniformLightAmbient_1, 1, value_ptr( this->light1.ReturnAmbient() ) );
   glUniform3fv( this->UniformLightDiffuse_1, 1, value_ptr( this->light1.ReturnDiffuse() ) );
   glUniform3fv( this->UniformLightSpecular_1, 1, value_ptr( this->light1.ReturnSpecular() ) );

   glUniform3fv( this->UniformLightPosition_2, 1, value_ptr( this->light2.ReturnPosition() ) );
   glUniform3fv( this->UniformLightAmbient_2, 1, value_ptr( this->light2.ReturnAmbient() ) );
   glUniform3fv( this->UniformLightDiffuse_2, 1, value_ptr( this->light2.ReturnDiffuse() ) );
   glUniform3fv( this->UniformLightSpecular_2, 1, value_ptr( this->light2.ReturnSpecular() ) );

   glUniform3fv( this->UniformViewPos, 1, value_ptr( this->camera.ReturnPosition() ) );

   /*
      Rysowanie wszystkich obiektów
   */
   for( this->It_Item = this->Item.begin(); this->It_Item != this->Item.end(); ++this->It_Item ){
      /*
         Przekazanie macierzy modelu.
      */
      glUniformMatrix4fv( this->UniformModel, 1, GL_FALSE, value_ptr( this->It_Item->ReturnModelMatrix() ) );
      /*
         Wyznaczenie numerów tekstur dla tekstów w uniformach
         0 = główna tekstura
         1 = spektralna tekstura
      */
      glUniform1i( this->UniformTexture, 0 );
      glUniform1i( this->UniformTextureSpecular, 1 );
      /*
         Aktywowanie i przekazanie tekstur do uniformów.
         - główna tekstura
         - spektralna tekstura
      */
      glActiveTexture( GL_TEXTURE0 );
      glBindTexture( GL_TEXTURE_2D, this->It_Item->ReturnTexture() );
      glActiveTexture( GL_TEXTURE1 );
      glBindTexture( GL_TEXTURE_2D, this->It_Item->ReturnTextureSpecular() );
      /*
         Ryosowanie elementu.
      */
      this->It_Item->Draw();
   }

   /*
      Odświeżenie okna.
   */
   SDL_GL_SwapWindow( this->Okno );
}
