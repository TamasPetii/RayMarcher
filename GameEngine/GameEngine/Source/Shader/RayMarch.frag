#version 460 core
#define MAX_ITERATION 250	
#define MAX_DISTANCE 100
#define ACCEPT_DISTANCE 0.01
#define MAX_SHAPE_NUMBER 10

struct Result
{
	int material;
	int success;
	vec3 color;
	vec3 origin;
};

struct Hit
{
	int material;
	float dist;
	vec3 color;
};

struct Ray
{
	vec3 origin;
	vec3 direction;
};

struct Torus
{
	int material;
    vec3 color;
	vec3 origin;
	float radiusPrimary;
	float radiusSecondary;
};

struct Sphere
{
	int material;
	int subtract;
	vec3 color;
	vec3 origin;
	float radius;
};

struct Cube
{
	int material;
	vec3 color;
	vec3 origin;
	vec3 parameters;
};

struct Capsule
{
	int material;
	vec3 color;
	vec3 origin1;
	vec3 origin2;
	float radius;
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
uniform int uCapsuleNumber;
uniform Capsule uCapsules[MAX_SHAPE_NUMBER];

//Function Declaration
Ray GenerateRay();
float SphereDistance(vec3 rayOrigin, Sphere sphere);
float TorusDistance(vec3 rayOrigin, Torus torus);
float CubeDistance(vec3 rayOrigin, Cube cube);
float CapsuleDistance(vec3 rayOrigin, Capsule capsule);
Hit ClosestDistance(vec3 rayOrigin);
vec3 GenerateNormal(Ray ray);
float CalculateLight(Ray ray);
Result RayMarch(Ray ray);

float smoothUnion(float d1, float d2, float k) {
    float h = clamp(0.5 + 0.5*(d2-d1)/k, 0.0, 1.0);
    return mix(d2, d1, h) - k*h*(1.0-h);
}

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

float CapsuleDistance(vec3 rayOrigin, Capsule capsule)
{
	vec3 pa = rayOrigin - capsule.origin1;
	vec3 ba = capsule.origin2 - capsule.origin1;
	float t = clamp(dot(pa, ba) / dot(ba, ba), 0, 1);
	vec3 c = capsule.origin1 + t * ba;
	return length(rayOrigin - c) - capsule.radius;
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
			closestHit.material = uSpheres[i].material;
		}
	}

	for(int i = 0; i < uTorusNumber; ++i)
	{
		float dist = TorusDistance(rayOrigin, uToruses[i]);

		if(dist < closestHit.dist)
		{
			closestHit.dist = dist;
			closestHit.color = uToruses[i].color;
			closestHit.material = uToruses[i].material;
		}
	}
	

	for(int i = 0; i < uCubeNumber; ++i)
	{
		float dist = CubeDistance(rayOrigin, uCubes[i]);

		if(dist < closestHit.dist)
		{
			closestHit.dist = dist;
			closestHit.color = uCubes[i].color;
			closestHit.material = uCubes[i].material;
		}
	}
	
	for(int i = 0; i < uCapsuleNumber; ++i)
	{
		float dist = CapsuleDistance(rayOrigin, uCapsules[i]);

		if(dist < closestHit.dist)
		{
			closestHit.dist = dist;
			closestHit.color = uCapsules[i].color;
			closestHit.material = uCapsules[i].material;
		}
	}
	
	if(rayOrigin.y < closestHit.dist)
	{
		closestHit.dist = rayOrigin.y;
		closestHit.color = vec3(1);
		closestHit.material = 0;
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
			result.material = closestHit.material;
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

	for(int i = 0; i < 5; i++)
	{	
		Result result = RayMarch(ray);

		if(result.success == 1)
		{		
			out_color += vec4(result.color * CalculateLight(result.origin) / pow(2, i), 1);		
			if(result.material == 0) break;

			vec3 normal = GenerateNormal(ray.origin);
			ray.origin = result.origin + normal * 0.025;
			ray.direction = reflect(ray.direction, normal);		

		}
		else
		{
			out_color += vec4(0);
		}
	}

}