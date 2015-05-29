attribute vec4 av4position;
attribute vec3 av3normal;

struct LightSourceParameters {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec4 position;
	vec4 halfVector;
	vec3 spotDirection;
	float spotExponent;
	float spotCutoff; // (range: [0.0,90.0], 180.0)
	float spotCosCutoff; // (range: [1.0,0.0],-1.0)
	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;
};

struct MaterialParameters {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform mat4 mvp;
//uniform mat4 um4rotateMatrix, um4modelMatrix;
uniform MaterialParameters Material;
uniform LightSourceParameters LightSource;

varying vec4 vv4color;
varying vec4 vv4ambient, vv4diffuse;
varying vec3 vv3normal, vv3halfVector;

void main() {
	// Position
	gl_Position = mvp * av4position;

	// Compute the ambient term
	vec4 ambient = Material.ambient * LightSource.ambient;

	// Compute the diffuse term
	vec3 L = normalize((LightSource.position - gl_Position).xyz);
	vec3 N = normalize(av3normal);
	vec4 diffuse = Material.diffuse * LightSource.diffuse * max(dot(N, L), 0.0);
	diffuse = clamp(diffuse, 0.0, 1.0);

	// Compute the specular term
	vec3 E = normalize(-gl_Position.xyz);
	vec3 R = normalize(-reflect(L, N));
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
	if (Material.shininess > 0.0)
		specular = Material.specular * LightSource.specular *
			pow(max(dot(R, E), 0.0), 0.3 * Material.shininess);
	specular = clamp(specular, 0.0, 1.0);

	vv4color = ambient + diffuse + specular;
}
