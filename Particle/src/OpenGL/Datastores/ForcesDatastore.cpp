#include "PCHeader.h"
#include "ForcesDatastore.h"

GL::ForcesDatastore::ForcesDatastore(ProgramManager *_programs, glm::vec3 dimensions, glm::vec2 resolution, GL::DebugDatastore *_debugData)
{

//  // Perlin Setup
  std::vector<int> p;
  p.resize(256, 0);
  std::iota(p.begin(), p.end(), 0); // Fill with sequentially increasing values.
  std::default_random_engine random(256);
  std::shuffle(p.begin(), p.end(), random); // Shuffle elements
  p.insert(p.end(), p.begin(), p.end());    // Duplicate current p and append into p

  data = new ForceData(p, dimensions, resolution);

  Utils::Perlin *perlin = new Utils::Perlin(rand());

  std::vector<glm::vec3> noise;
  double yoff = 0.0;
  for (int y = 0; y < data->Dimensions.y; y++)
  {
	static double zoff = 0.0;
	for (int z = 0; z < data->Dimensions.z; z++)
	{
	  static double xoff = 0.0;
	  double lat = perlin->Noise(data->Octaves, data->Persistance, xoff, yoff + y, zoff) * TWO_PI * 4;
	  for (int x = 0; x < data->Dimensions.x; x++)
	  {
		double lon = perlin->Noise(data->Octaves, data->Persistance, xoff, yoff + y, zoff) * TWO_PI * 4;

		float xp = 1.0f * sin(lon) * cos(lat);
		float yp = 0.5f * sin(lon) * sin(lat);
		float zp = 1.0f * cos(lon);

		float mag = sqrt(xp * xp + yp * yp + zp * zp);
		float magnitude = maxMagnitude * perlin->Noise(data->Octaves, data->Persistance, xoff, yoff + y, zoff);
		xp = xp * magnitude / mag;
		yp = yp * magnitude / mag;
		zp = zp * magnitude / mag;

		noise.push_back(glm::vec3(xp, yp, zp));
		xoff += 0.01;
	  }
	  zoff += 0.01;
	}
	yoff += 0.01;
  }

	Noise = new NoiseTBO(GL_TEXTURE0, noise);

	Init(_programs, _debugData);
}

GL::ForcesDatastore::~ForcesDatastore()
{
  	delete pointer;
	delete VBO;
  	delete VAO;
  	delete TBO;
}

void GL::ForcesDatastore::Init(ProgramManager *_programs, GL::DebugDatastore *_debugData)
{
  PROFILE("ForcesDatastore::Init");

  programs = _programs;

  programs->use(UPDATE_FORCE);
//  programs->get_active(UPDATE_FORCE)->setIntArray("p", data->P.data(), data->P.size());
  programs->get_active(UPDATE_FORCE)->setVec3("dimensions", data->Dimensions);
  programs->get_active(UPDATE_FORCE)->setVec2("resolution", data->Resolution);

  // Setup basic forces
  std::vector<glm::vec3> forces;
  for (int y = 0; y < data->Dimensions.y; y++)
  {
	for (int z = 0; z < data->Dimensions.z; z++)
	{
	  for (int x = 0; x < data->Dimensions.x; x++)
	  {
		forces.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
		_debugData->addElement( { glm::vec3(x, y, z) } );
	  }
	}
  }

  // Setup Pointer
  pointer = new VBPointer<glm::vec3>();
  pointer->start = pointer->it = nullptr;
  pointer->size = forces.size();

  // Setup Buffers
  GL::VBOLayout vbl = VBOLayout();
  vbl.push<float>(3, 0); // Force

  VAO = new VertexArray();
  VAO->init();

  VBO = new VertexBuffer<glm::vec3>(GL_DYNAMIC_DRAW);
  VBO->init(sizeof(glm::vec3) * forces.size(), forces);

  TBO = new UpdateTBO(GL_TEXTURE0, forces);

  VAO->setVertexLayout(vbl);
}

void GL::ForcesDatastore::Update(double dt)
{
  PROFILE("ForcesDatastore::Update");

  static double yoff = 0.0;
  programs->use(UPDATE_FORCE);
  bindUpdateArray();
  bindVertexBuffer();

  Noise->bindTexture();

  programs->get_active(UPDATE_FORCE)->setInt("tbo_id0", 0);
  programs->get_active(UPDATE_FORCE)->setFloat("dt", dt);
//  programs->get_active(UPDATE_FORCE)->setDouble("yoffset", yoff);
  programs->get_active(UPDATE_FORCE)->setInt("octaves", data->Octaves);
  programs->get_active(UPDATE_FORCE)->setFloat("persistence", data->Persistance);
  programs->get_active(UPDATE_FORCE)->setFloat("maxMagnitude", maxMagnitude);

  GLCheck(glEnable(GL_RASTERIZER_DISCARD));
  GLCheck(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, VBO->getID()));
  GLCheck(glBeginTransformFeedback(GL_POINTS));
  GLCheck(glDrawArrays(GL_POINTS, 0, pointer->size));
  GLCheck(glEndTransformFeedback());
  GLCheck(glFlush());
  GLCheck(glDisable(GL_RASTERIZER_DISCARD));

  TBO->bindTexture();
  TBO->loadData(VBO->getPointer(), sizeof(glm::vec3) * pointer->size);

  pointer->it = nullptr;
  VBO->releasePointer();
  yoff += data->Dimensions.y * 0.01 * dt;
}

void GL::ForcesDatastore::bindUpdateArray()
{
  VAO->bind();
}

void GL::ForcesDatastore::bindVertexBuffer()
{
  VBO->bind();
}

void GL::ForcesDatastore::SetDebugUniforms(Program *program)
{
  program->setVec3("dimensions", data->Dimensions);
  program->setVec2("resolution", data->Resolution);
  program->setBool("showMagnitude", showActualMagnitude);
}