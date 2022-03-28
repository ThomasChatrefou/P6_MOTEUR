#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normals;

out vec2 v_TexCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_MVP;

void main()
{
	FragPos = vec3(u_MVP * position);
	Normal = mat3(transpose(inverse(u_MVP))) * normals; 
	gl_Position = u_MVP * position;
	v_TexCoord = texCoord;
};



#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec3 Normal;
in vec3 FragPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;
uniform vec3 viewPos;
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
	    vec4 texColor = texture(u_Texture, v_TexCoord);
	    color = texColor;
	
	    // ambient
    	float ambientStrength = 0.1;
    	vec3 ambient = ambientStrength * lightColor;
  	
    	// diffuse 
    	vec3 norm = normalize(Normal);
    	vec3 lightDir = normalize(lightPos - FragPos);
    	float diff = max(dot(norm, lightDir), 0.0);
    	vec3 diffuse = diff * lightColor;
    
    	// specular
    	float specularStrength = 1.0;
    	vec3 viewDir = normalize(viewPos - FragPos);
    	vec3 reflectDir = reflect(-lightDir, norm);  
    	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    	vec3 specular = specularStrength * spec * lightColor;  
        
    	vec3 result = (ambient + diffuse + specular) * objectColor;
        color = texColor * vec4(result, 1.0);
};