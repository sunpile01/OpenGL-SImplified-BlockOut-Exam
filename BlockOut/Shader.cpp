/**
* @file shader.cpp
*
* @author Aleksander Solhaug
*/

#include <string>
#include <glm/glm.hpp>

const std::string tunnelWallVertexShaderSrc = R"(
#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;
out vec2 vsTexCoords;
out vec2 positionGrid;
out vec4 vs_fragPosition;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
void main()
{ 
	gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 0.0, 1.0);
    vsTexCoords = texCoords;
    vs_fragPosition = u_modelMatrix * vec4(position, 0.0f, 1.0f);
    positionGrid = position;
}
)";


const std::string tunnelWallFragmentShaderSrc = R"(
#version 460 core
layout (binding = 0) uniform sampler2D u_Texture;
out vec4 color;
in vec2 positionGrid;
in vec2 vsTexCoords;
in vec4 vs_fragPosition;
uniform vec4 u_colorA = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 u_colorB = vec4(0.0f, 0.0f, 0.0f, 0.0f);
uniform vec3 u_normal;
uniform vec3 u_cameraPosition;
uniform vec2 u_gridSize;
uniform mat4 u_modelMatrix;
uniform int   u_setTextures;
uniform int   u_setLight;
uniform float u_ambientStrength;
uniform vec3  u_lightSourcePosition;
uniform float u_diffuseStrength;
uniform float u_specularStrength;
uniform vec4  u_lightColor;
float pi = 3.1415926536f;

void main()
{
    vec4 u_normal = normalize(u_modelMatrix*vec4(u_normal, 1.0f));
    vec4 ambient = u_ambientStrength * u_lightColor;

    vec3 lightDirection = normalize(vec3(u_lightSourcePosition - vs_fragPosition.xyz));
    float diffuseStrength = max(dot(lightDirection, u_normal.xyz), 0.0f) * u_diffuseStrength;
    
    vec3 reflectedLight = normalize(reflect(-lightDirection, u_normal.xyz));
    vec3 observerDirection = normalize(u_cameraPosition - vs_fragPosition.xyz);
    float specFactor = pow(max(dot(observerDirection, reflectedLight), 0.0), 24);
    float specular = specFactor * u_specularStrength;

	if (sin(pi * u_gridSize.y * (positionGrid.y -0.5f)) < 0){

        if (sin(pi * u_gridSize.x * (positionGrid.x -0.5f)) > 0){
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorB * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorB;
            }
        }
        else{
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorA * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorA;
            }
        }
    }
    //Colors left right corner white, and right down black
    else  {
        if(sin(pi * u_gridSize.x * (positionGrid.x -0.5f)) < 0){
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorB * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorB;
            }
        }
        else {
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorA * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorA;
            }
            
        }
    }
}
)";

const std::string endWallVertexShaderSrc = R"(
#version 460 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoords;
out vec2 vsTexCoords;
out vec2 positionGrid;
out vec4 vs_fragPosition;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
void main()
{ 
	positionGrid = position;
	gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 0.0, 1.0);
    vsTexCoords = texCoords;
    vs_fragPosition = u_modelMatrix * vec4(position, 0.0f, 1.0f);
}
)";


const std::string endWallFragmentShaderSrc = R"(
#version 460 core
layout (binding = 0) uniform sampler2D u_Texture;
out vec4 color;
in vec2 positionGrid;
in vec2 vsTexCoords;
in vec4 vs_fragPosition;
uniform vec4 u_colorA = vec4(1.0f, 1.0f, 1.0f, 1.0f);
uniform vec4 u_colorB = vec4(0.0f, 0.0f, 0.0f, 0.0f);
uniform vec3 u_normal;
uniform vec3 u_cameraPosition;
uniform vec2 u_gridSize;
uniform mat4 u_modelMatrix;
uniform int u_setTextures;
uniform int u_setLight;
uniform float u_ambientStrength;
uniform vec3 u_lightSourcePosition;
uniform float u_diffuseStrength;
uniform float u_specularStrength;
uniform vec4 u_lightColor;
float pi = 3.1415926536f;

void main()
{
    vec4 u_normal = normalize (u_modelMatrix * vec4(u_normal, 1.0f));
    vec4 ambient = u_ambientStrength * u_lightColor;
    vec3 lightDirection = -normalize(vec3(u_lightSourcePosition - vs_fragPosition.xyz));
    float diffuseStrength = max(dot(lightDirection, u_normal.xyz), 0.0f) * u_diffuseStrength;
    
    vec3 reflectedLight = normalize(reflect(-lightDirection, u_normal.xyz));
    vec3 observerDirection = normalize(u_cameraPosition - vs_fragPosition.xyz);
    float specFactor = pow(max(dot(observerDirection, reflectedLight), 0.0), 24);
    float specular = specFactor * u_specularStrength;

	if (sin(pi * u_gridSize.y * (positionGrid.y -0.5f)) < 0){

        if (sin(pi * u_gridSize.x * (positionGrid.x -0.5f)) > 0){
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorB * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorB;
            }
        }
        else{
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorA * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorA;
            }
        }
    }
    //Colors left right corner white, and right down black
    else  {
        if(sin(pi * u_gridSize.x * (positionGrid.x -0.5f)) < 0){
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorB, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorB * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorB;
            }
        }
        else {
            if(u_setTextures  == 1 && u_setLight == 1){
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f) * (ambient + diffuseStrength + specular);
            } 
            else if (u_setTextures == 1) {
                color = mix(u_colorA, texture(u_Texture, vsTexCoords), 0.7f);
            }   
            else if (u_setLight == 1){
                color = u_colorA * (ambient + diffuseStrength + specular);
            }
            else{
                color = u_colorA;
            }
            
        }
    }
}
)";


const std::string cubeVertexShaderSrc = R"(
#version 460 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 i_normal;
out vec4 vs_normal;
out vec4 vs_fragPosition;
out vec3 texCords;
uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projMatrix;
uniform vec3 u_Color;
void main()
{ 
   texCords = position;
   gl_Position = u_projMatrix * u_viewMatrix * u_modelMatrix * vec4(position, 1.0);
   vs_normal = normalize (u_modelMatrix * vec4(i_normal, 1.0f));
   vs_fragPosition = u_modelMatrix * vec4(position, 1.0f);
}
)";

// Fragment shader code
const std::string cubeFragmentShaderSrc = R"(
#version 460 core
layout(binding = 1) uniform samplerCube u_CubeTexture;
in vec3 texCords;
in vec4 vs_fragPosition;
in vec4 vs_normal;
out vec4 color;
uniform vec4 u_color;
uniform int u_setTextures;
uniform int u_setLight;
uniform vec3 u_lightSourcePosition;
uniform vec3 u_cameraPosition;
uniform float u_ambientStrength;
uniform float u_translationVectorZ;
uniform float u_diffuseStrength;
uniform float u_specularStrength;
uniform vec4 u_lightColor;

void main()
{
    bool active1 = false;
    vec4 activeColor  = vec4(0.0f, 0.0f, 1.0f, 0.4f);
    if (u_color == activeColor){
        active1 = true;
    }

    //If statement needs to contribute to the shaders output, I could not get it to work
    //unless i duplicated the code for each of the two scenarios
    if (u_translationVectorZ <= 0.04f){
    vec4 result = u_color * u_lightColor;
    result *= u_ambientStrength;
    vec3 lightDirection = -normalize(vec3(u_lightSourcePosition - vs_fragPosition.xyz));
    float diffuseStrength = max(dot(lightDirection, vs_normal.xyz), 0.0f) * u_diffuseStrength;

    vec3 reflectedLight = normalize(reflect(-lightDirection, vs_normal.xyz));
    vec3 observerDirection = normalize(u_cameraPosition - vs_fragPosition.xyz);
    float specFactor = pow(max(dot(observerDirection, reflectedLight), 0.0), 16);
    float specular = specFactor * u_specularStrength;
        if (u_setTextures == 1 && u_setLight == 1){
            color = mix(result, texture(u_CubeTexture, texCords), 0.7f) *  (diffuseStrength + specular);
            if(active1 == false){
                color[3] = 1.0f;
            }
            else{
                color[3] = 0.5f;
            }
        }
        else if (u_setTextures == 1){
            color = mix(u_color, texture(u_CubeTexture, texCords), 0.7f);
            if (active1 == true){
            color[3] = 0.4f;
            }
        }
        else if (u_setLight == 1){
            color = result * (diffuseStrength + specular);
            if(active1 == false){
                color[3] = 1.0f;
            }
            else{
                color[3] = 0.5f;
            }
        }
        else color = u_color;
    }
    else{
        vec4 result = u_color * u_lightColor;
        result *= u_ambientStrength;
        vec3 lightDirection =  normalize(vec3(u_lightSourcePosition - vs_fragPosition.xyz));
        vec3 reflectedLight =  normalize(reflect(-lightDirection, vs_normal.xyz));
        vec3 observerDirection =  normalize(u_cameraPosition - vs_fragPosition.xyz);
        float diffuseStrength = max(dot(lightDirection, vs_normal.xyz), 0.0f) * u_diffuseStrength;
        float specFactor = pow(max(dot(observerDirection, reflectedLight), 0.0), 16);
        float specular = specFactor * u_specularStrength;
        if (u_setTextures == 1 && u_setLight == 1){
            color = mix(result, texture(u_CubeTexture, texCords), 0.7f) *  (diffuseStrength + specular);
            if(active1 == false){
                color[3] = 1.0f;
            }
            else{
                color[3] = 0.5f;
            }
        }
        else if (u_setTextures == 1){
            color = mix(u_color, texture(u_CubeTexture, texCords), 0.5f);
            if (active1 == true){
            color[3] = 0.4f;
            }
        }
        else if (u_setLight == 1){
            color = result * (diffuseStrength + specular);
            if(active1 == false){
                color[3] = 1.0f;
            }
            else{
                color[3] = 0.5f;
            }
        }
        else color = u_color;
    }

}
)";
