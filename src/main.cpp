#include "header.hpp"
#include "common.cpp"
#include "camera.cpp"
#include "mesh.cpp"
#include "light.cpp"

class Gra{
   public:
      Gra();
      ~Gra();
      void Start();
   private:
      void Shader();
      void Update();
      bool CheckInit = true;
      SDL_Window *Okno = NULL;
      int Wysokosc = 800;
      int Szerokosc = 600;
      SDL_GLContext Kontekst = NULL;
      SDL_Event Event;
      //Shader:
      string vertex = "./data/Shader.vert";
      string fragment = "./data/Shader.frag";
      GLuint ProgramID = 0;
      //Uniforms:
      GLuint UniformModel;
      GLuint UniformView;
      GLuint UniformProjection;
      GLuint UniformTexture;
      GLuint UniformTextureSpecular;
      GLuint UniformViewPos;
      GLuint UniformLightPosition_1;
      GLuint UniformLightAmbient_1;
      GLuint UniformLightDiffuse_1;
      GLuint UniformLightSpecular_1;
      GLuint UniformLightPosition_2;
      GLuint UniformLightAmbient_2;
      GLuint UniformLightDiffuse_2;
      GLuint UniformLightSpecular_2;
      //Camera:
      Camera camera;
      vec2 Mouse;
      //All items:
      vector <Mesh> Item;
      vector <Mesh>::iterator It_Item;
      //Lights:
      Light light1, light2;
};

int main( int argc, char* argv[] ){
   Gra gra;
   gra.Start();
   return 0;
}

Gra::Gra(){
   //SDL2:
   if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ){
      cout<<"SDL_Init: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
   SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
   glewExperimental = true;
   this->Okno = SDL_CreateWindow( "OpenGL", 0, 0, this->Wysokosc, this->Szerokosc, SDL_WINDOW_OPENGL );
   if( this->Okno == NULL ){
      cout<<"SDL_CreateWindow: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }
   SDL_SetRelativeMouseMode( SDL_TRUE );
   this->Kontekst = SDL_GL_CreateContext( this->Okno );
   if( this->Kontekst == NULL ){
      cout<<"SDL_GL_CreateContext: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }
   //GLEW:
   GLenum GL_Error = glewInit();
   if( GL_Error != GLEW_OK  ){
      cout<<"glewInit: "<<SDL_GetError()<<"\n";
      this->CheckInit = false;
      return;
   }
   glEnable( GL_DEPTH_TEST );
   glDepthFunc( GL_LESS );
   glEnable( GL_CULL_FACE );
   glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
   //DevIL
   ilInit();
   iluInit();
   ILenum IL_Error;
   while( ( IL_Error = ilGetError() ) != IL_NO_ERROR ){
      cout<<"DevIL: "<<iluErrorString( IL_Error )<<"\n";
      this->CheckInit = false;
      return;
   }
   //Shader:
   this->ProgramID = CreateShader( vertex, fragment );
   if( this->ProgramID <= 0 ){
      cout<<"Shader error:"<<this->ProgramID<<"\n";
      this->CheckInit = false;
      return;
   }
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
   fstream file;
   file.open( "./data/data.init", ios::in );
   if( file.good() ){
      stringstream tmp_stream;
      string tmp_string;
      string tmp_name, tmp_obj, tmp_img, tmp_spec;
      GLfloat tmp_float;
      vec3 tmp_vector_vec3;
      while( getline( file, tmp_string ) ){
         tmp_stream.str( tmp_string );
         Mesh tmp_item;
         //Set string
         tmp_stream >> tmp_name;
         tmp_stream >> tmp_obj;
         tmp_stream >> tmp_img;
         tmp_stream >> tmp_spec;
         tmp_item.SetString( tmp_name,
                             "./data/" + tmp_obj,
                             "./data/" + tmp_img,
                             "./data/" + tmp_spec
                           );
         //Set model matrix
         tmp_stream >> tmp_float;
         tmp_vector_vec3.x = tmp_float;
         tmp_stream >> tmp_float;
         tmp_vector_vec3.y = tmp_float;
         tmp_stream >> tmp_float;
         tmp_vector_vec3.z = tmp_float;
         tmp_item.SetModelMatrix( tmp_vector_vec3 );
         //Push back
         this->Item.push_back( tmp_item );
      }
      for( this->It_Item = this->Item.begin(); this->It_Item != this->Item.end(); ++this->It_Item ){
         this->It_Item->LoadData();
      }
   }
   else{
      cout<<"File error: ./data/data.init\n";
      this->CheckInit = false;
      return;
   }
   //Lights:
   vec3 tmp_vector_vec3 = vec3( 0.0f, 15.0f, 0.0f );
   this->light1.SetPosition( tmp_vector_vec3 );
   tmp_vector_vec3 = vec3( 15.0f, 0.0f, 15.0f );
   this->light2.SetPosition( tmp_vector_vec3 );
}

Gra::~Gra(){
   glDeleteProgram( this->ProgramID );
   SDL_SetRelativeMouseMode( SDL_FALSE );
   SDL_GL_DeleteContext( this->Kontekst );
   SDL_DestroyWindow( this->Okno );
   SDL_Quit();
}

void Gra::Start(){
   while( this->CheckInit ){
      while( SDL_PollEvent( & this->Event ) ){
         switch( this->Event.type ){
            case SDL_QUIT:
               this->CheckInit = false;
               break;
            case SDL_MOUSEMOTION:
               this->Mouse.x = -this->Event.motion.xrel;
               this->Mouse.y = -this->Event.motion.yrel;
               this->camera.MouseUpdate( this->Mouse );
               SDL_WarpMouseInWindow( this->Okno, ( this->Wysokosc / 2 ), ( this->Szerokosc / 2 ) );
               break;
            case SDL_KEYDOWN:
               switch( this->Event.key.keysym.sym ){
                  case SDLK_ESCAPE:
                     this->CheckInit = false;
                     break;
                  case SDLK_UP:
                  case SDLK_w:
                     this->camera.MoveForward();
                     break;
                  case SDLK_DOWN:
                  case SDLK_s:
                     this->camera.MoveBackward();
                     break;
                  case SDLK_LEFT:
                  case SDLK_a:
                     this->camera.MoveLeft();
                     break;
                  case SDLK_RIGHT:
                  case SDLK_d:
                     this->camera.MoveRight();
                     break;
                  case SDLK_SPACE:
                     this->camera.MoveUp();
                     break;
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
      this->Update();
   }
}

void Gra::Update(){
   glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   glUseProgram( this->ProgramID );
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

   for( this->It_Item = this->Item.begin(); this->It_Item != this->Item.end(); ++this->It_Item ){
      glUniformMatrix4fv( this->UniformModel, 1, GL_FALSE, value_ptr( this->It_Item->ReturnModelMatrix() ) );
      glUniform1i( this->UniformTexture, 0 );
      glUniform1i( this->UniformTextureSpecular, 1 );
      glActiveTexture( GL_TEXTURE0 );
      glBindTexture( GL_TEXTURE_2D, this->It_Item->ReturnTexture() );
      glActiveTexture( GL_TEXTURE1 );
      glBindTexture( GL_TEXTURE_2D, this->It_Item->ReturnTextureSpecular() );
      this->It_Item->Draw();
   }

   SDL_GL_SwapWindow( this->Okno );
}
