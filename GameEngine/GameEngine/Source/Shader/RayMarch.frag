#version 460 core
#define MAX_ITERATION 250	
#define MAX_DISTANCE 100
#define ACCEPT_DISTANCE 0.001
#define MAX_SHAPE_NUMBER 100

struct Result
{
	int success;
	vec3 color;
	vec3 origin;
};

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

struct Cube
{
	vec3 color;
	vec3 origin;
	vec3 parameters;
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
uniform vec3 uLightPos;
uniform mat4 uViewProjMatrix;
uniform int uSphereNumber;
uniform Sphere uSpheres[MAX_SHAPE_NUMBER];
uniform int uTorusNumber;
uniform Torus uToruses[MAX_SHAPE_NUMBER];
uniform int uCubeNumber;
uniform Cube uCubes[MAX_SHAPE_NUMBER];


//Function Declaration
Ray GenerateRay();
float SphereDistance(vec3 rayOrigin, Sphere sphere);
float TorusDistance(vec3 rayOrigin, Torus torus);
float CubeDistance(vec3 rayOrigin, Cube cube);
Hit ClosestDistance(vec3 rayOrigin);
vec3 GenerateNormal(Ray ray);
float CalculateLight(Ray ray);
Result RayMarch(Ray ray);

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

float CubeDistance(vec3 rayOrigin, Cube cube)
{ 
	vec3 p = abs(rayOrigin - cube.origin) - cube.parameters;
	vec3 a = vec3(max(0, p.x), max(0, p.y), max(0, p.z));
	float dist = length(a);
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
	

	for(int i = 0; i < uCubeNumber; ++i)
	{
		float dist = CubeDistance(rayOrigin, uCubes[i]);

		if(dist < closestHit.dist)
		{
			closestHit.dist = dist;
			closestHit.color = uCubes[i].color;
		}
	}

	if(rayOrigin.y < closestHit.dist)
	{
		closestHit.dist = rayOrigin.y;
		closestHit.color = vec3(1);
	}

	return closestHit;
}

vec3 GenerateNormal(vec3 rayOrigin)
{
	float closestDistance = ClosestDistance(rayOrigin).dist;
	float changeX = ClosestDistance(rayOrigin + vec3(0.001, 0, 0)).dist - closestDistance;
	float changeY = ClosestDistance(rayOrigin + vec3(0, 0.001, 0)).dist - closestDistance;
	float changeZ = ClosestDistance(rayOrigin + vec3(0, 0, 0.001)).dist - closestDistance;
	return normalize(vec3(changeX, changeY, changeZ));
}

float CalculateLight(vec3 rayOrigin)
{
	vec3 normal = GenerateNormal(rayOrigin);
	vec3 toLight = uLightPos - rayOrigin;
	
	float diffuseIntensity = clamp(dot(normal, normalize(toLight)), 0, 1);

	Ray newRay;
	newRay.origin = rayOrigin + normal * 0.025;
	newRay.direction = normalize(toLight);
	float shadow = RayMarch(newRay).success == 1 ? 0 : 1;

	return diffuseIntensity * shadow;
}

Result RayMarch(Ray ray)
{
	Result result;
	result.success = 0;
	float dist = 0;

	for(int i = 0; i < MAX_ITERATION; ++i)
	{
		Hit closestHit = ClosestDistance(ray.origin);
		ray.origin += ray.direction * closestHit.dist;
		dist += closestHit.dist;

		if(closestHit.dist < ACCEPT_DISTANCE)
		{
			result.origin = ray.origin;
			result.color = closestHit.color;
			result.success = 1;
			break;
		}

		if(dist > MAX_DISTANCE)
			break;
	}

	return result;
}


void main()
{
	Ray ray = GenerateRay();
	Result result = RayMarch(ray);

	if(result.success == 1)
	{
		out_color = vec4(result.color * CalculateLight(result.origin), 1);
	}
	else
	{
		out_color = vec4(1);
	}
}