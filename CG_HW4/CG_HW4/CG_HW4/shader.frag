struct LightSourceParameters {
	// Directional Light
	bool dirEnabled;
	vec4 dirDirection;
	vec4 dirAmbient;
	vec4 dirColor;

	// Positional Light
	bool posEnabled;
	vec4 posPosition;
	vec4 posAmbient;
	vec4 posColor;

	// Spot Light
	bool spotEnabled;
	vec4 spotPos;
	vec4 spotAmbient;
	vec4 spotColor;
	float spotExponent;
	float spotCutoff; // (range: [0.0,90.0], 180.0)
	float spotCosCutoff; // (range: [1.0,0.0],-1.0)
};

struct MaterialParameters {
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float shininess;
};

uniform mat4 mvp;
uniform MaterialParameters material;
uniform LightSourceParameters lights;

varying vec4 vv4color;

void main() {

	gl_FragColor = vv4color;
}
