
// in position, uv, normal
vec3 getNormalFromMap(sampler2D normalMap) {
	vec3 tangentNormal = texture(normalMap, uv).xyz * 2.0 - 1.0;

	vec3 q1 = dFdx(position);
	vec3 q2 = dFdy(position);
	vec2 st1 = dFdx(uv);
	vec2 st2 = dFdy(uv);

	vec3 n = normalize(normal);
	vec3 t = normalize(q1 * st2.t - q2 * st1.t);
	vec3 b = -normalize(cross(n, t));
	mat3 tbn = mat3(t, b, n);

	return normalize(tbn * tangentNormal);
}

vec3 getNormalFromVec3(vec3 normalColor) {
	vec3 tangentNormal = normalColor * 2.0 - 1.0;

	vec3 q1 = dFdx(position);
	vec3 q2 = dFdy(position);
	vec2 st1 = dFdx(uv);
	vec2 st2 = dFdy(uv);

	vec3 n = normalize(normal);
	vec3 t = normalize(q1 * st2.t - q2 * st1.t);
	vec3 b = -normalize(cross(n, t));
	mat3 tbn = mat3(t, b, n);

	return normalize(tbn * tangentNormal);
}
