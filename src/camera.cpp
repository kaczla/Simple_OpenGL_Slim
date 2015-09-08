#ifndef __camera_hpp__
#define __camera_hpp__

class Camera{
   public:
      Camera();
      ~Camera();
      Camera( const Camera &camera );
      Camera & operator=( const Camera &camera );
      mat4 ReturnProjectionMatrix();
      mat4 ReturnViewMatrix();

      vec3 ReturnPosition() const;
      inline void UpdateProjectionMatrix();
      inline void UpdateViewMatrix();
      void MouseUpdate( const vec2 &Mouse );
      void MoveUp();
      void MoveDown();
      void MoveForward();
      void MoveBackward();
      void MoveLeft();
      void MoveRight();
   private:
      vec3 Position = vec3( 0.0f, 1.0f, 0.0f );
      vec3 ViewDirection = vec3( 0.0f, 0.0f, -1.0f );
      vec3 Up = vec3( 0.0f, 1.0f, 0.0f );
      vec1 RotationSpeed = vec1( 0.0005f );
      vec1 MovementSpeed = vec1( 0.15f );
      mat4 ProjectionMatrix = mat4( 1.0f );
      mat4 ViewMatrix = mat4( 1.0f );
      vec1 VOF = vec1( 45.0f );
      vec1 Aspect = vec1( 4.0f / 3.0f );
      vec1 Near = vec1( 0.1f );
      vec1 Far = vec1( 100.0f );
      //tmp:
      vec3 RotationAround;
      mat4 Rotation;
      vec3 MovementDirection;
};

Camera::Camera(){
   this->ProjectionMatrix = perspective( radians( this->VOF.x ), this->Aspect.x, this->Near.x, this->Far.x );
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
   this->ProjectionMatrix = perspective( radians( this->VOF.x ), this->Aspect.x, this->Near.x, this->Far.x );
   return this->ProjectionMatrix;
}

mat4 Camera::ReturnViewMatrix(){
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
