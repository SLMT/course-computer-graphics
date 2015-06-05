attribute vec4 av4position;
attribute vec3 av3normal;
attribute vec2 av2texCoord;

struct LightSourceParameters {
	// Directional Light
	int dirEnabled;
	vec3 dirDirection;
	vec4 dirAmbient;
	vec4 dirColor;

	// Positional Light
	int posEnabled;
	vec3 posPosition;
	vec4 posAmbient;
	vec4 posColor;

	// Spot Light
	int spotEnabled;
	vec3 spotPosition;
	vec4 spotAmbient;
	vec4 spotColor;
	vec3 spotDirection;
	float spotExponent;
	float spotCosCutoff; // (range: [1.0,0.0],-1.0)
};

const float constantAttenuation = 0.0;
const float linearAttenuation = 0.75;
const float quadraticAttenuation = 0.0;

struct MaterialParameters {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform mat4 mvp;
uniform MaterialParameters material;
uniform LightSourceParameters lights;
uniform int isVertexLighting;

varying vec4 vv4position;
varying vec4 vv4color;
varying vec3 vv3normal;
varying vec2 vv2texCoord;

void main() {
	vv4position = mvp * av4position;
	gl_Position = vv4position;
	vv2texCoord = av2texCoord;
	vv3normal = av3normal;
	vv4color = vec4(0.0, 0.0, 0.0, 1.0);

	if (isVertexLighting != 0) {
		vec3 N = normalize(vv3normal);

		// ===================
		//  Directional Light
		// ===================
		if (lights.dirEnabled != 0) {
			vec3 L = normalize(-lights.dirDirection);

			// Compute the ambient term
			vec4 ambient = material.ambient * lights.dirAmbient;

			// Compute the diffuse term
			vec4 diffuse = material.diffuse * lights.dirColor * max(dot(N, L), 0.0);

			// Compute the specular term
			vec3 E = normalize(-gl_Position.xyz);
			vec3 H = normalize(L + E);
			vec4 specular = material.specular * lights.dirColor *
			pow(max(dot(N, H), 0.0), material.shininess);

			vv4color += (ambient + diffuse + specular) * 0.8;
		}

		// ===================
		//  Positional Light
		// ===================
		if (lights.posEnabled != 0) {
			vec3 lightVec = lights.posPosition - gl_Position.xyz;
			vec3 L = normalize(lightVec);

			// Compute attenuation
			float lightDis = length(lightVec);
			float attenuation = 1.0 / (constantAttenuation +
				linearAttenuation * lightDis +
				quadraticAttenuation * lightDis * lightDis);

			// Compute the ambient term
			vec4 ambient = material.ambient * lights.posAmbient;

			// Compute the diffuse term
			vec4 diffuse = material.diffuse * lights.posColor * max(dot(N, L), 0.0);

			// Compute the specular term
			vec3 E = normalize(-gl_Position.xyz);
			vec3 H = normalize(L + E);
			vec4 specular = material.specular * lights.posColor *
			pow(max(dot(N, H), 0.0), material.shininess);

			vv4color += (ambient + diffuse + specular) * attenuation;
		}

		// ============
		//  Spot Light
		// ============
		if (lights.spotEnabled != 0) {
			vec3 lightVec = lights.spotPosition - gl_Position.xyz;
			vec3 L = normalize(lightVec);

			// Compute attenuation
			float lightDis = length(lightVec);
			float attenuation = 1.0 / (constantAttenuation +
				linearAttenuation * lightDis +
				quadraticAttenuation * lightDis * lightDis);

			// Compute Spot effect
			float spotCos = dot(L, -lights.spotDirection);
			if (spotCos < lights.spotCosCutoff)
				attenuation = 0.0;
			else
				attenuation *= pow(spotCos, lights.spotExponent);


			// Compute the ambient term
			vec4 ambient = material.ambient * lights.spotAmbient;

			// Compute the diffuse term
			vec4 diffuse = material.diffuse * lights.spotColor * max(dot(N, L), 0.0);

			// Compute the specular term
			vec3 E = normalize(-gl_Position.xyz);
			vec3 H = normalize(L + E);
			vec4 specular = material.specular * lights.spotColor *
			pow(max(dot(N, H), 0.0), material.shininess);

			vv4color += (ambient + diffuse + specular) * attenuation;
		}
	}
}
