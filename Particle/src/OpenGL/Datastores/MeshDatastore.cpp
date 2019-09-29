#include "PCHeader.h"
#include "MeshDatastore.h"

namespace GL
{

MeshDatastore::MeshDatastore(int _width, int _height, int _resolution)
	: width(_width), height(_height), resolution(_resolution)
{
	Init();
}

MeshDatastore::~MeshDatastore()
{
  delete pointer;
  delete VBO;
  delete VAO;
}

void MeshDatastore::Init()
{
  PROFILE("MeshDatastore::Init");

  // Setup Pointer
  pointer = new VBPointer<MVertex>();
  pointer->start = pointer->it = nullptr;
  pointer->size = 0;

  GL::VBOLayout vbl = VBOLayout();
  vbl.push<float>(3, 0); // Position
  vbl.push<float>(4, 1); // Colour
  vbl.push<float>(3, 0); // Normals

  VAO = new VertexArray();
  VAO->init();

  VBO = new VertexBuffer<MVertex>(GL_DYNAMIC_DRAW);
  VBO->init(sizeof(MVertex) * (width - 1)  * (height - 1) * 6);
  VAO->setVertexLayout(vbl);

  int cellsX = width / resolution;
  int cellsZ = height / resolution;

  // Create Vertices
  perlin = new Utils::Perlin();
  int triangleIndex = 0;

  static double yoff = 0.0;
  double zoff = 0.0;
  for (int z = 0; z < cellsZ; ++z)
  {
	double xoff = 0.0;
	for (int x = 0; x < cellsX; ++x)
	{
	  int xp = x * resolution;
	  int zp = z * resolution;

	  int hMod = 100;
	  double ypA = abs(perlin->Noise(5, 0.6f, xoff, yoff, zoff)) * hMod;
	  double ypB = abs(perlin->Noise(5, 0.6f, xoff + 0.01, yoff, zoff)) * hMod;
	  double ypC = abs(perlin->Noise(5, 0.6f, xoff + 0.01, yoff, zoff + 0.02)) * hMod;
	  double ypD = abs(perlin->Noise(5, 0.6f, xoff, yoff, zoff + 0.02)) * hMod;

	  xoff += 0.01;
	  // A -- B
	  // D -- C

	  // T1: ACD
	  // T2: CAB

	  glm::vec4 COLOUR = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);

	  MVertex A = { // A
		  {xp, ypA, zp },
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  MVertex B = { // B
		  {xp + resolution, ypB, zp },
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  MVertex C = { // C
		  {xp + resolution, ypC, zp + resolution},
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

	  MVertex D = { // D
		  {xp, ypD, zp + resolution},
		  COLOUR,
		  {0.0f, 0.0f, 0.0f	}
	  };

//	  elements.push_back(A);
//	  elements.push_back(C);
//	  elements.push_back(D);
//
//	  elements.push_back(C);
//	  elements.push_back(A);
//	  elements.push_back(B);

	  elements.push_back(A);
	  elements.push_back(B);
	  elements.push_back(C);
	  elements.push_back(D);

	  indices.push_back(triangleIndex + 0);
	  indices.push_back(triangleIndex + 2);
	  indices.push_back(triangleIndex + 3);
//	  triangleIndex += 3;

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
		elements[ib].position - elements[ia].position,
		elements[ic].position - elements[ia].position));
	elements[ia].normals = elements[ib].normals = elements[ic].normals = normal;
  }

  auto ptr = VBO->getPointer();
  memcpy(ptr, elements.data(), elements.size() * sizeof(MVertex));
  VBO->releasePointer();

  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void MeshDatastore::Update()
{
  PROFILE("MeshDatastore::Update");
}

void MeshDatastore::bindRenderArray()
{
	VAO->bind();
}

void MeshDatastore::bindVertexBuffer()
{
	VBO->bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
}

void MeshDatastore::unbindRenderArray()
{
	VAO->unbind();
}

void MeshDatastore::unbindVertexBuffer()
{
	VBO->unbind();
}

}