#version 330 core

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct Light {
   vec3 position;
   
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

out vec4 FragColor;

in vec3 color;
in vec2 tex;
in vec3 normal;
in vec3 fragPos;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

uniform Material material;
uniform Light light;

uniform vec3 lightColor;
// uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
   vec3 norm = normalize(normal);

   vec3 ambient = light.ambient * material.ambient;

   vec3 lightDir = normalize(light.position - fragPos);
   vec3 viewDir = normalize(viewPos - fragPos);
   // vec3 reflectDir = -lightDir - 2 * dot(norm, -lightDir) * norm;
   vec3 reflectDir = reflect(-lightDir, norm);

   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = light.diffuse * (diff * material.diffuse);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
   vec3 specular = light.specular * (material.specular * spec);

   vec3 result = ambient + diffuse + specular;
   FragColor = vec4(result, 1.0);
}