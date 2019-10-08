#include "PCHeader.h"
#include "Terrain.h"

Terrain::Terrain(float x, float y, float z, float width, float height, float depth, unsigned int _resolution)
	: Plane(x, y, z, width, height, depth, _resolution)
{
}

Terrain::~Terrain()
{
}

void Terrain::Generate()
{
  vertices.clear();
  indices.clear();

  GenerateHeightThresholds();

  auto maxi = maxHeightThresholds;

  int cellsX = dimensions.x / resolution;
  int cellsZ = dimensions.z / resolution;

  // Create Vertices
  Utils::Perlin *perlin = new Utils::Perlin();
  int triangleIndex = 0;

  static double yoff = 0.0;
  double zoff = 0.0;
  for (int z = 0; z < cellsZ; ++z)
  {
	double xoff = 0.0;
	for (int x = 0; x < cellsX; ++x)
	{
	  int xp = position.x + x * resolution;
	  int zp = position.z + z * resolution;
	  int yp = position.y;

	  float ypA = z + (float)abs(perlin->Noise(5, 0.6f, xoff, yoff, zoff)) * maxi[z];
	  float ypB = z + (float)abs(perlin->Noise(5, 0.6f, xoff + 0.01, yoff, zoff)) * maxi[z];
	  float ypC = z + (float)abs(perlin->Noise(5, 0.6f, xoff + 0.01, yoff, zoff + 0.02)) * maxi[z];
	  float ypD = z + (float)abs(perlin->Noise(5, 0.6f, xoff, yoff, zoff + 0.02)) * maxi[z];

	  xoff += 0.01;
	  glm::vec4 COLOUR = glm::vec4(0.98f, 0.77f, 0.19f, 1.0f);

	  CVertex A = { // A
		  {xp, yp + (float)ypA, zp },
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  CVertex B = { // B
		  {xp + resolution, yp + (float)ypB, zp },
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  CVertex C = { // C
		  {xp + resolution, yp + (float)ypC, zp + resolution},
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  CVertex D = { // D
		  {xp, yp + (float)ypD, zp + resolution},
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
	zoff += 0.02;
  }
  yoff += 0.0001;

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

void Terrain::GenerateHeightThresholds()
{
  maxHeightThresholds.clear();

  unsigned int numValues = dimensions.z / resolution;

  for (unsigned int i = 0; i < numValues; ++i)
  {
	  float percent = (i * 1.0f) / (numValues * 1.0f);

	  maxHeightThresholds.push_back(percent * dimensions.y + 50.0f);

	  if (percent >= 0.3 && percent < 0.6) {
	    maxHeightThresholds[i] += 50.0f;
	  } else if (percent >= 0.6) {
	    maxHeightThresholds[i] += 100.0f;
	  }

//	  if (percent < 0.3) {
//	    minHeightThresholds.push_back(position.y + 0.0f);
//	    maxHeightThresholds.push_back(position.y + dimensions.y * 0.43);
//	  } else if (percent < 0.6) {
//		minHeightThresholds.push_back(position.y + dimensions.y * 0.2f);
//		maxHeightThresholds.push_back(position.y + dimensions.y * 0.8f);
//	  } else {
//		minHeightThresholds.push_back(position.y + (dimensions.y * 0.7f));
//		maxHeightThresholds.push_back(position.y + dimensions.y);
//	  }
  }
}
