#ifndef __light_ccp__
#define ____light_ccp__

class Light{
   public:
      Light();
      ~Light();
      Light( const Light &light );
      Light & operator=( const Light &light );
      void SetPosition( vec3 vector_position );
      void SetAmbient( vec3 vector_ambient );
      void SetDiffuse( vec3 vector_diffuse );
      void SetSpecular( vec3 vector_specular );
      vec3 ReturnPosition() const;
      vec3 ReturnAmbient() const;
      vec3 ReturnDiffuse() const;
      vec3 ReturnSpecular() const;
   private:
      vec3 Position = vec3( 0.0f, 10.0f, 0.0f );
      vec3 Ambient = vec3( 0.5f );
      vec3 Diffuse = vec3( 0.5f );
      vec3 Specular = vec3( 0.5f );
};

Light::Light(){
}

Light::~Light(){
}

Light::Light( const Light &light ){
   this->Position = light.Position;
   this->Ambient = light.Ambient;
   this->Diffuse = light.Diffuse;
   this->Specular = light.Specular;
}

Light & Light::operator=( const Light &light ){
   this->Position = light.Position;
   this->Ambient = light.Ambient;
   this->Diffuse = light.Diffuse;
   this->Specular = light.Specular;
   return *this;
}

void Light::SetPosition( vec3 vector_position ){
   this->Position = vector_position;
}

void Light::SetAmbient( vec3 vector_ambient ){
   this->Ambient = vector_ambient;
}

void Light::SetDiffuse( vec3 vector_diffuse ){
   this->Diffuse = vector_diffuse;
}

void Light::SetSpecular( vec3 vector_specular ){
   this->Specular = vector_specular;
}

vec3 Light::ReturnPosition() const{
   return this->Position;
}

vec3 Light::ReturnAmbient() const{
   return this->Ambient;
}

vec3 Light::ReturnDiffuse() const{
   return this->Diffuse;
}

vec3 Light::ReturnSpecular() const{
   return this->Specular;
}

#endif
