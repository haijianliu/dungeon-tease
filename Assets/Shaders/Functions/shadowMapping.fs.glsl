
// shadow mapping
float shadowMapping(mat4 lightSpaceMatrix, vec3 n, vec3 position) {
	// frag position light space
	vec4 fragPositionLightSpace = lightSpaceMatrix * vec4(position, 1.0);
	// perform perspective divide
	vec3 projection = fragPositionLightSpace.xyz / fragPositionLightSpace.w;
	// transform to [0,1] range
	projection = projection * 0.5 + 0.5;
	// get closest depth value from light's perspective
	float closestDepth = texture(shadowMap, projection.xy).r;
	// get depth of current fragment from light's perspective
	float currentDepth = projection.z;
	// calculate bias (based on depth map resolution and slope)
	vec3 normal = normalize(n);
	vec3 lightDirection = normalize(vec3(5.0f, 5.0f, -1.0f) - position);
	// vec3 lightDirection = normalize(vec3(-1.0f, 1.0f, -1.0f));
	float bias = max(0.05 * (1.0 - dot(normal, lightDirection)), 0.005);
	// check whether current frag pos is in shadow
	// float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
	// PCF
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x) {
		for(int y = -1; y <= 1; ++y) {
			float pcfDepth = texture(shadowMap, projection.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;
		}
	}
	shadow /= 9.0;

	// keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
	if(projection.z > 1.0) shadow = 0.0;

	return shadow;
}
