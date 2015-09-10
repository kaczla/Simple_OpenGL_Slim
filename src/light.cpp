/*!
   \file light.cpp
   \brief Plik odpowiedzialny zarządzanie światłem.
*/
#ifndef __light_ccp__
#define ____light_ccp__

/*!
   \brief Klasa odpowiedzialny zarządzanie światłem.
*/
class Light{
   public:
      /*!
         \brief Konstruktor domyślny.
      */
      Light();
      /*!
         \brief Destruktor.
      */
      ~Light();
      /*!
         \brief Konstruktor kopiujący.
      */
      Light( const Light &light );
      /*!
         \brief Operator przypisania.
      */
      Light & operator=( const Light &light );
      /*!
         \brief Ustala nową pozycję światła (\link Position \endlink).

         \param vector_position - nowa wartość dla pozycji światła (\link Position \endlink)
      */
      void SetPosition( vec3 vector_position );
      /*!
         \brief Ustala nową wartość dla \link Ambient \endlink.

         \param vector_ambient - nowa wartość dla zmiennej \link Ambient \endlink dla światła
      */
      void SetAmbient( vec3 vector_ambient );
      /*!
         \brief Ustala nową wartość dla \link Diffuse \endlink.

         \param vector_diffuse - nowa wartość dla zmiennej \link Diffuse \endlink dla światła
      */
      void SetDiffuse( vec3 vector_diffuse );
      /*!
         \brief Ustala nową wartość dla \link Specular \endlink.

         \param vector_specular - nowa wartość dla zmiennej \link Specular \endlink dla światła
      */
      void SetSpecular( vec3 vector_specular );
      /*!
         \brief Zwraca aktualną pozycję światła.
      */
      vec3 ReturnPosition() const;
      /*!
         \brief Zwraca aktualną wartość zmiennej \link Ambient \endlink dla światła.
      */
      vec3 ReturnAmbient() const;
      /*!
         \brief Zwraca aktualną wartość zmiennej \link Diffuse \endlink dla światła.
      */
      vec3 ReturnDiffuse() const;
      /*!
         \brief Zwraca aktualną wartość zmiennej \link Specular \endlink dla światła.
      */
      vec3 ReturnSpecular() const;
   private:
      /*!
         \brief Pozycja światła.
      */
      vec3 Position = vec3( 0.0f, 10.0f, 0.0f );
      /*!
         \brief Wartość Ambient światła.
      */
      vec3 Ambient = vec3( 0.5f );
      /*!
         \brief Wartość Diffuse światła.
      */
      vec3 Diffuse = vec3( 0.5f );
      /*!
         \brief Wartość Specular światła.
      */
      vec3 Specular = vec3( 0.5f );
};

/*
   ========
    SOURCE:
   ========
*/

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
