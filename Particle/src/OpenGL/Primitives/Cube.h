#ifndef CUBE_H
#define CUBE_H

#include "Vertex.h"

struct Cube
{
  Vertex vertices[36] = {
	  {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
	  {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
	  {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
	  {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
	  {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
	  {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},

	  {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
	  {{0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
	  {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
	  {{0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
	  {{-0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},
	  {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}},

	  {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
	  {{-0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
	  {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
	  {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
	  {{-0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},
	  {{-0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f}},

	  {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
	  {{0.5f, 0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
	  {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
	  {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
	  {{0.5f, -0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
	  {{0.5f, 0.5f, 0.5f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

	  {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
	  {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
	  {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
	  {{0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
	  {{-0.5f, -0.5f, 0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},
	  {{-0.5f, -0.5f, -0.5f}, {1.0f, 1.0f, 0.0f, 1.0f}, {0.0f, -1.0f, 0.0f}},

	  {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
	  {{0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
	  {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
	  {{0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
	  {{-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
	  {{-0.5f, 0.5f, -0.5f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}
  };

  unsigned int indices[6 * 6] =
	  {
		  0, 1, 3, 3, 1, 2,
		  1, 5, 2, 2, 5, 6,
		  5, 4, 6, 6, 4, 7,
		  4, 0, 7, 7, 0, 3,
		  3, 2, 7, 7, 2, 6,
		  4, 5, 0, 0, 5, 1
	  };
};


#endif /* CUBE_H */
