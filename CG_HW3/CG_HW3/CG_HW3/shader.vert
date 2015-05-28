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
	vec3 L = normalize((LightSource.position - av4position).xyz);
	vec3 N = normalize(av3normal);
	vec4 diffuse = Material.diffuse * dot(N, L);

	// Compute the specular term
	vec4 specular = vec4(0.0, 0.0, 0.0, 0.0);
	if (Material.shininess != 0) {
		vec3 H = normalize(L - normalize(gl_Position.xyz));
		float specAngle = max(dot(N, H), 0.0);
		specular = Material.specular * pow(specAngle, Material.shininess);
	}

	vv4color = ambient + LightSource.diffuse * (diffuse + specular);
}
