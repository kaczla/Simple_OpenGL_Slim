#version 330 core

struct Material_{
   sampler2D Texture;
   sampler2D Texture_specular;
};

struct Directional_Light{
   vec3 Position;
   vec3 Ambient;
   vec3 Diffuse;
   vec3 Specular;
};

#define Max_Directional_Light 2

in vec2 UV;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform Material_ Material;
uniform Directional_Light DirectionalLight[Max_Directional_Light];
uniform vec3 ViewPos;

vec3 CalculateDirectionalLight( Directional_Light DirectionalLight_, vec3 normal_, vec3 viewDir_, vec3 fragPos_ );

void main()
{
   vec3 normal = normalize( Normal );
   vec3 viewDir = normalize( ViewPos - FragPos );
   vec3 result = vec3( 0.0f );
   for( int i = 0; i < Max_Directional_Light; ++i ){
      result += CalculateDirectionalLight( DirectionalLight[i], normal, viewDir, FragPos  );
   }
   color = vec4( result, 1.0f );
}

vec3 CalculateDirectionalLight( Directional_Light DirectionalLight_, vec3 normal_, vec3 viewDir_, vec3 fragPos_ ){
   vec3 lightDir = normalize( DirectionalLight_.Position - fragPos_ );
   // Diffuse shading
   float diff = max( dot( normal_, lightDir ), 0.0 );
   // Specular shading
   vec3 reflectDir = reflect( -lightDir, normal_ );
   float spec = pow( max( dot( viewDir_, reflectDir ), 0.0 ), 32.0 );
   // Combine results
   vec3 ambient = DirectionalLight_.Ambient * vec3( texture( Material.Texture, UV ) );
   vec3 diffuse = DirectionalLight_.Diffuse * diff * vec3( texture( Material.Texture, UV ) );
   vec3 specular = DirectionalLight_.Specular * spec * vec3( texture( Material.Texture_specular, UV ) );
   return ( ambient + diffuse + specular );
}
