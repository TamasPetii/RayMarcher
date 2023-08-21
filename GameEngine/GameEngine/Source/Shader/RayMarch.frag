#version 460 core
#define MAX_ITERATION 50
#define MAX_DISTANCE 100000
#define ACCEPT_DISTANCE 0.01
#define MAX_SHAPE_NUMBER 100

struct Hit
{
	float dist;
	vec3 color;
};

struct Torus
{
    vec3 color;
	vec3 origin;
	float radiusPrimary;
	float radiusSecondary;
};

struct Sphere
{
	vec3 color;
	vec3 origin;
	float radius;
};

struct Ray
{
	vec3 origin;
	vec3 direction;
};

//Input Data
in vec3 frag_position;

//Output Data
out vec4 out_color;

//Uniform Data
uniform mat4 uViewProjMatrix;

uniform int uSphereNumber;
uniform Sphere uSpheres[MAX_SHAPE_NUMBER];

uniform int uTorusNumber;
uniform Torus uToruses[MAX_SHAPE_NUMBER];

Ray GenerateRay()
{
	vec4 startNdc = vec4(frag_position.xy, -1, 1);
	vec4 endNdc = vec4(frag_position.xy, 1, 1);
	vec4 startWorld = inverse(uViewProjMatrix) * startNdc; 
	vec4 endWorld = inverse(uViewProjMatrix) * endNdc;
	startWorld /= startWorld.w;
	endWorld /= endWorld.w;

	Ray ray;
	ray.origin = startWorld.xyz;
	ray.direction = normalize(endWorld.xyz - startWorld.xyz);

	return ray;
}

float SphereDistance(vec3 rayOrigin, Sphere sphere)
{
	float dist = length(sphere.origin - rayOrigin) - sphere.radius;
	return dist;
}

float TorusDistance(vec3 rayOrigin, Torus torus)
{
	vec3 p = vec3(rayOrigin.x, torus.origin.y, rayOrigin.z);
	float distXZ = length(p - torus.origin) - torus.radiusPrimary;
	float distY = rayOrigin.y - torus.origin.y;
	float dist = length(vec2(distXZ, distY)) - torus.radiusSecondary;
	return dist;
}

Hit ClosestDistance(vec3 rayOrigin)
{
	Hit closestHit;
	closestHit.dist = MAX_DISTANCE;
	closestHit.color = vec3(0);

	for(int i = 0; i < uSphereNumber; ++i)
	{
		float dist = SphereDistance(rayOrigin, uSpheres[i]);

		if(dist < closestHit.dist)
		{
			closestHit.dist = dist;
			closestHit.color = uSpheres[i].color;
		}
	}

	for(int i = 0; i < uTorusNumber; ++i)
	{
		float dist = TorusDistance(rayOrigin, uToruses[i]);

		if(dist < closestHit.dist)
		{
			closestHit.dist = dist;
			closestHit.color = uToruses[i].color;
		}
	}

	return closestHit;
}

vec3 GenerateNormal(Ray ray)
{
	float closestDistance = ClosestDistance(ray.origin).dist;
	float changeX = ClosestDistance(ray.origin + vec3(0.01, 0, 0)).dist - closestDistance;
	float changeY = ClosestDistance(ray.origin + vec3(0, 0.01, 0)).dist - closestDistance;
	float changeZ = ClosestDistance(ray.origin + vec3(0, 0, 0.01)).dist - closestDistance;
	return normalize(vec3(changeX, changeY, changeZ));
}

float CalculateLight(Ray ray)
{
	vec3 normal = GenerateNormal(ray);
	vec3 direction = normalize(vec3(-1, -1, -1));
	
	float diffuseIntensity = clamp(dot(normal, -direction), 0, 1);
	return diffuseIntensity;
}

vec3 RayMarch(Ray ray)
{
	for(int i = 0; i < MAX_ITERATION; ++i)
	{
		Hit closestHit = ClosestDistance(ray.origin);
		ray.origin += ray.direction * closestHit.dist;

		if(closestHit.dist < ACCEPT_DISTANCE)
		{
			return closestHit.color * CalculateLight(ray);
		}
	}

	return vec3(0);
}

void main()
{
	Ray ray = GenerateRay();
	vec3 color = RayMarch(ray);
	out_color = vec4(color,1);
}