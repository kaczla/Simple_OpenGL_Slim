/*!
   \file camera.cpp
   \brief Plik odpowiedzialny zarządzanie kamerą gracza.
*/
#ifndef __camera_hpp__
#define __camera_hpp__

/*!
   \brief Klasa odpowiedzialna za zarządzaniem kamerą gracza.
*/
class Camera{
   public:
      /*!
         \brief Konstruktor domyślny, ustawia macierz widoku i projekcji.
      */
      Camera();
      /*!
         \brief Destruktor.
      */
      ~Camera();
      /*!
         \brief Konstruktor kopiujący.
      */
      Camera( const Camera &camera );
      /*!
         \brief Operator przypisania.
      */
      Camera & operator=( const Camera &camera );
      /*!
         \brief Zwraca macierz projekcji.
      */
      mat4 ReturnProjectionMatrix();
      /*!
         \brief Zwraca macierz widoku.
      */
      mat4 ReturnViewMatrix();
      /*!
         \brief Zwraca aktualną pozycję kamery.
      */
      vec3 ReturnPosition() const;
      /*!
         \brief Aktualizuje macierz projekcji.
      */
      inline void UpdateProjectionMatrix();
      /*!
         \brief Aktualizuje macierz widoku.
      */
      inline void UpdateViewMatrix();
      /*!
         \brief Obrót kamery.

         \param Mouse - wartość przesunięcia dla \link ViewDirection \endlink

         Szybkość obrotu uzależniona jest od wielkości \link RotationSpeed \endlink.
      */
      void MouseUpdate( const vec2 &Mouse );
      /*!
         \brief Porusza kamerę w góry.

         Szybkość poruszania uzależniona jest od wielkości \link MovementSpeed \endlink.
      */
      void MoveUp();
      /*!
         \brief Porusza kamerę w dół.

         Szybkość poruszania uzależniona jest od wielkości \link MovementSpeed \endlink.
      */
      void MoveDown();
      /*!
         \brief Porusza kamerę do przodu (przed siebie).

         Szybkość poruszania uzależniona jest od wielkości \link MovementSpeed \endlink.
      */
      void MoveForward();
      /*!
         \brief Porusza kamerę do tyłu.

         Szybkość poruszania uzależniona jest od wielkości \link MovementSpeed \endlink.
      */
      void MoveBackward();
      /*!
         \brief Porusza kamerę w lewo.

         Szybkość poruszania uzależniona jest od wielkości \link MovementSpeed \endlink.
      */
      void MoveLeft();
      /*!
         \brief Porusza kamerę w prawo.

         Szybkość poruszania uzależniona jest od wielkości \link MovementSpeed \endlink.
      */
      void MoveRight();
   private:
      /*!
         \brief Pozycja kamery.
      */
      vec3 Position = vec3( 0.0f, 1.0f, 0.0f );
      /*!
         \brief Cel kamery, w jaki punkt patrzy.
      */
      vec3 ViewDirection = vec3( 0.0f, 0.0f, -1.0f );
      /*!
         \brief Wektor kierunku.
      */
      vec3 Up = vec3( 0.0f, 1.0f, 0.0f );
      /*!
         \brief Szybkość obrotu kamery.
      */
      vec1 RotationSpeed = vec1( 0.0005f );
      /*!
         \brief Szybkość poruszania się kamery.
      */
      vec1 MovementSpeed = vec1( 0.15f );
      /*!
         \brief Macierz projekcji.
      */
      mat4 ProjectionMatrix = mat4( 1.0f );
      /*!
         \brief Macierz widoku.
      */
      mat4 ViewMatrix = mat4( 1.0f );
      /*!
         \brief Kąt widzenia dla kamery, wyrażony w stopniach.
      */
      vec1 VOF = vec1( 45.0f );
      /*!
         \brief Współczynnik szerokości do wysokości, obliczany jako szerokość/wysokość.
      */
      vec1 Aspect = vec1( 4.0f / 3.0f );
      /*!
         \brief Odległość od jakiej rysowane są obiekty.
      */
      vec1 Near = vec1( 0.1f );
      /*!
         \brief Odległość do jakiej rysowane są obiekty.
      */
      vec1 Far = vec1( 100.0f );
      //tmp:
      /*!
         \brief Tymczasowy dla obrotu kamery.
      */
      vec3 RotationAround;
      /*!
         \brief Tymczasowy dla obrotu kamery.
      */
      mat4 Rotation;
      /*!
         \brief Tymczasowy dla poruszania się kamery.
      */
      vec3 MovementDirection;
};

/*
   ========
    SOURCE:
   ========
*/

Camera::Camera(){
   /*
      Otrzymanie macierzy projekcji
   */
   this->ProjectionMatrix = perspective( radians( this->VOF.x ), this->Aspect.x, this->Near.x, this->Far.x );
   /*
      Otrzymanie macierzy widoku
   */
   this->ViewMatrix = lookAt( this->Position, this->Position + this->ViewDirection, this->Up );
}

Camera::~Camera(){
}

Camera::Camera( const Camera &camera ){
   this->Position = camera.Position;
   this->ViewDirection = camera.ViewDirection;
   this->Up = camera.Up;
   this->RotationSpeed = camera.RotationSpeed;
   this->MovementSpeed = camera.MovementSpeed;
   this->ProjectionMatrix = camera.ProjectionMatrix;
   this->ViewMatrix = camera.ViewMatrix;
   this->VOF = camera.VOF;
   this->Aspect = camera.Aspect;
   this->Near = camera.Near;
   this->Far = camera.Far;
}

Camera & Camera::operator=( const Camera &camera ){
   this->Position = camera.Position;
   this->ViewDirection = camera.ViewDirection;
   this->Up = camera.Up;
   this->RotationSpeed = camera.RotationSpeed;
   this->MovementSpeed = camera.MovementSpeed;
   this->ProjectionMatrix = camera.ProjectionMatrix;
   this->ViewMatrix = camera.ViewMatrix;
   this->VOF = camera.VOF;
   this->Aspect = camera.Aspect;
   this->Near = camera.Near;
   this->Far = camera.Far;
   return *this;
}

mat4 Camera::ReturnProjectionMatrix(){
   /*
      Otrzymanie macierzy projekcji
   */
   this->ProjectionMatrix = perspective( radians( this->VOF.x ), this->Aspect.x, this->Near.x, this->Far.x );
   return this->ProjectionMatrix;
}

mat4 Camera::ReturnViewMatrix(){
   /*
      Otrzymanie macierzy widoku
   */
   this->ViewMatrix = lookAt( this->Position, this->Position + this->ViewDirection, this->Up );
   return this->ViewMatrix;
}

vec3 Camera::ReturnPosition() const{
   return this->Position;
}

void Camera::MouseUpdate( const vec2 &Mouse ){
   this->RotationAround = cross( this->ViewDirection, this->Up );
   this->Rotation = rotate( Mouse.x * this->RotationSpeed.x, this->Up ) * rotate( Mouse.y * this->RotationSpeed.x, this->RotationAround );
   this->ViewDirection = mat3( this->Rotation ) * this->ViewDirection;
}

void Camera::MoveUp(){
   this->Position += this->MovementSpeed.x * this->Up;
}

void Camera::MoveDown(){
   this->Position -= this->MovementSpeed.x * this->Up;
}

void Camera::MoveForward(){
   this->Position += this->MovementSpeed.x * this->ViewDirection;
}

void Camera::MoveBackward(){
   this->Position -= this->MovementSpeed.x * this->ViewDirection;
}

void Camera::MoveLeft(){
   this->MovementDirection = cross( this->ViewDirection, this->Up );
   this->Position -= this->MovementSpeed.x * this->MovementDirection;
}

void Camera::MoveRight(){
   this->MovementDirection = cross( this->ViewDirection, this->Up );
   this->Position += this->MovementSpeed.x * this->MovementDirection;
}

#endif
