#include "Plane.h"

Plane::Plane(float x, float y, float z, float width, float height, float depth, unsigned int _resolution)
	: Object(x, y, z, width, height, depth), resolution(_resolution)
{
}

Plane::~Plane()
{
}

void Plane::Generate()
{
  int cellsX = dimensions.x / resolution;
  int cellsZ = dimensions.z / resolution;

  // Create Vertices
  int triangleIndex = 0;

  for (int z = 0; z < cellsZ; ++z)
  {
	for (int x = 0; x < cellsX; ++x)
	{
	  int xp = position.x + x * resolution;
	  int zp = position.z + z * resolution;

	  // A -- B
	  // D -- C

	  // T1: ACD
	  // T2: CAB

	  glm::vec4 COLOUR = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

	  CVertex A = { // A
		  {xp, position.y, zp },
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  CVertex B = { // B
		  {xp + resolution, position.y, zp },
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  CVertex C = { // C
		  {xp + resolution, position.y, zp + resolution},
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  CVertex D = { // D
		  {xp, position.y, zp + resolution},
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  vertices.push_back(A);
	  vertices.push_back(B);
	  vertices.push_back(C);
	  vertices.push_back(D);

	  indices.push_back(triangleIndex + 0);
	  indices.push_back(triangleIndex + 2);
	  indices.push_back(triangleIndex + 3);

	  indices.push_back(triangleIndex + 2);
	  indices.push_back(triangleIndex + 0);
	  indices.push_back(triangleIndex + 1);
	  triangleIndex += 4;
	}
  }

  for (int i = 0; i < indices.size(); i += 3)
  {
	unsigned int ia = indices[i    ];
	unsigned int ib = indices[i + 1];
	unsigned int ic = indices[i + 2];

	glm::vec3 normal = glm::normalize(glm::cross(
		vertices[ib].position - vertices[ia].position,
		vertices[ic].position - vertices[ia].position));
	vertices[ia].normal = vertices[ib].normal = vertices[ic].normal = normal;
  }

  __Init(vertices, indices);
}
