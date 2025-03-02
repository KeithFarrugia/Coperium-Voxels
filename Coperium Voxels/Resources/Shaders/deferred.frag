#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedoSpec;

uniform vec3 viewPos; // Camera position

// Hardcoded sun (directional light) parameters
// Sunlight coming straight down from above (0, -1, 0)
const vec3 sunDir = normalize(vec3(-1.0, -1.0, -1.0));
const vec3 sunColor = vec3(1.0, 1.0, 1.0);

void main()
{             
    // Retrieve data from the G-buffer
    vec3 FragPos = texture(gPosition, TexCoords).rgb;
    vec3 Normal = normalize(texture(gNormal, TexCoords).rgb);
    vec3 Diffuse = texture(gAlbedoSpec, TexCoords).rgb;
    float Specular = texture(gAlbedoSpec, TexCoords).a;
    
    // Ambient lighting (constant base light)
    vec3 ambient = Diffuse * 0.1;
    
    // Directional diffuse lighting (using Lambert's law)
    // Note: Use -sunDir because sunDir is the direction of the incoming light.
    float diff = max(dot(Normal, -sunDir), 0.0);
    vec3 diffuse = diff * Diffuse * sunColor;
    
    // Specular lighting (Blinn-Phong)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(-sunDir + viewDir);
    float spec = pow(max(dot(Normal, halfwayDir), 0.0), 16.0);
    vec3 specular = sunColor * spec * Specular;
    
    // Combine lighting contributions
    vec3 lighting = ambient + diffuse + specular;
    FragColor = vec4(lighting, 1.0);
}
