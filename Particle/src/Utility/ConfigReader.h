#ifndef PARTICLE_PARTICLE_SRC_UTILITY_INIREADER_H_
#define PARTICLE_PARTICLE_SRC_UTILITY_INIREADER_H_

namespace Utils
{

struct ApplicationData
{
	unsigned int maxParticles;
	unsigned int particleFloodNumber;
	unsigned int simWidth;
	unsigned int simHeight;
	unsigned int simDepth;
	unsigned int simResolution;
	unsigned int simYResolution;
	unsigned int meshResolution;
	unsigned int windowWidth;
	unsigned int windowHeight;
	bool wireframe;
	bool fullscreen;
};

class ConfigReader
{
public:
  static ApplicationData *ReadConfig(const char *filepath)
  {
    std::ifstream fs(filepath);
	ApplicationData *ad = new ApplicationData();

	if (fs.is_open())
	{
		fs >> ad->maxParticles >> ad->particleFloodNumber;
		fs >> ad->simWidth >> ad->simHeight >> ad->simDepth;
		fs >> ad->simResolution >> ad->simYResolution >> ad->meshResolution;
		fs >> ad->windowWidth >> ad->windowHeight;
		fs >> ad->wireframe >> ad->fullscreen;
	}
	else
	{
	  fs.close();
	  return nullptr;
	}

	fs.close();
    return ad;
  }
};

};

#endif //PARTICLE_PARTICLE_SRC_UTILITY_INIREADER_H_
