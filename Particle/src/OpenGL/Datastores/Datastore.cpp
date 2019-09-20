#include "PCHeader.h"
#include "Datastore.h"

namespace GL
{

Datastore::Datastore()
{
    Init();
}

Datastore::~Datastore()
{
    delete pointer;

    delete vb1;
    delete vb2;
    delete vaR;
    delete vaU;
}

void Datastore::Init()
{
    PROFILE("Datastore::Init");

    // Setup Pointer
    pointer = new VBPointer();
    pointer->start = pointer->it = nullptr;
    pointer->size = 0;
    PT::GC::get()->init();

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3, 0); // Position
    vbl.push<float>(3, 0); // Velocity
    vbl.push<float>(4, 1); // Colour
    vbl.push<float>(1, 1); // Lifespan
    vbl.push<float>(1, 1); // Mass

    vaU = new VertexArray();
    vaU->init();

    vb1 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb1->init(sizeof(PT::ParticleData) * PT::GC::get()->getInt("MAX_PARTICLES"));

    {
        pointer->start = pointer->it = vb1->getPointer();
        pointer->size = 0;
        // const int total = 10;
        // for (int i = 0; i < total; i++)
        // {
        //     float lat = Utils::Mathf::Map(i, 0, total, -HALF_PI, HALF_PI);
        //     for (int j = 0; j < total; j++)
        //     {
        //         float lon = Utils::Mathf::Map(j, 0, total, -PI, PI);

        //         float x = 100 * sin(lon) * cos(lat);
        //         float y = 100 * sin(lon) * sin(lat);
        //         float z = 100 * cos(lon);

        //         pointer->it->position = glm::vec3(x, y, z);
        //         pointer->it->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        //         pointer->it->colour = Colour::PINK;
        //         pointer->it->lifespan = 1.0f;
        //         pointer->it->mass = 1.0f;
        //         pointer->it++;
        //         pointer->size++;
        //     }
        // }

        pointer->it->position = glm::vec3(1.0f, 0.0f, 1.0f);
        pointer->it->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
        pointer->it->colour = Colour::RED;
        pointer->it->lifespan = 1.0f;
        pointer->it->mass = 1.0f;
        pointer->it++;
        pointer->size++;

        PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);

        vb1->releasePointer();
    }

    vb2 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb2->init(sizeof(PT::ParticleData) * PT::GC::get()->getInt("MAX_PARTICLES"));

    vb1->bind();
    vaU->setVertexLayout(vbl);

    vaR = new VertexArray();
    vaR->init();
    vaR->setVertexLayout(vbl);

    vb1->bind();
    vaR->setVertexLayout(vbl);
    vaR->unbind();
}

void Datastore::checkForFreeIndices()
{
  if (freeIndices.empty())
  {
	bindVertexBuffer();

	auto cursor = vb1->getPointer();

	for (int i = 0; i < pointer->size; ++i, cursor++)
	{
	  auto c = *cursor;

	  if (c.lifespan <= 0.0f)
	  {
		std::lock_guard<std::mutex> lockGuard(mutex);

		std::pair<std::set<int>::iterator, bool> p = s.insert(i);
		if (p.second)
		{
		  freeIndices.push(i);
		}
	  }
	}

	vb1->releasePointer();
  }
}


void Datastore::Update()
{
    PROFILE("Datastore::Update");
  	checkForFreeIndices();

    if (!waitingToSpawn.empty())
    {
        submitData(waitingToSpawn.front());
        waitingToSpawn.pop();
    }
}

void Datastore::submitData(std::vector<PT::ParticleData> &data)
{
    PROFILE("Datastore::submitData");

    auto maxSize = PT::GC::get()->getInt("MAX_PARTICLES");
    if (getPointerSize() + data.size() > maxSize)
        data.resize(maxSize - getPointerSize());

    if (data.size() != 0)
    {
        copyData(data);
    }
}

void Datastore::copyData(std::vector<PT::ParticleData> &data)
{
    PROFILE("Datastore::copyData");
    bindVertexBuffer();
    pointer->it = vb1->getPointer();
    while (!freeIndices.empty() && !data.empty())
	{

	  int i = freeIndices.front();
	  freeIndices.pop();
	  s.erase(i);

      	auto toAdd = data.back();
      	data.pop_back();

	  	*(pointer->it + i) = toAdd;
	}

  if (!data.empty())
  {
  	pointer->it += pointer->size - 1;
  	memcpy(pointer->it, data.data(), data.size() * sizeof(PT::ParticleData));
  	pointer->size += data.size() - 1;
  }
    vb1->releasePointer();
    PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);
}

void Datastore::submitData(PT::ParticleData &data)
{
    PROFILE("Datastore::submitData (single)");

    auto maxSize = PT::GC::get()->getInt("MAX_PARTICLES");
    if (!(getPointerSize() + 1 > maxSize))
        copyData(data);
}

void Datastore::copyData(PT::ParticleData data)
{
    PROFILE("Datastore::copyData (single)");

  bindVertexBuffer();
  if (!freeIndices.empty())
  {
	int i = freeIndices.front();
	freeIndices.pop();
	pointer->it = vb1->getPointer() + i;
	*pointer->it = data;
  } else {
	bindVertexBuffer();
	pointer->it = vb1->getPointer() + pointer->size - 1;
    memcpy(pointer->it, &data, sizeof(PT::ParticleData));
    pointer->size += 1;
    vb1->releasePointer();
    PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);
  }

  vb1->releasePointer();

}

void Datastore::swapBuffers()
{
    std::swap(vb1, vb2);
}

void Datastore::addElement(PT::ParticleData element)
{
    elements.push_back(element);
}

void Datastore::addToQueue(PT::ParticleData element)
{
    waitingToSpawn.push(element);
}

void Datastore::bindUpdateArray()
{
    vaU->bind();
}

void Datastore::bindRenderArray()
{
    vaU->bind();
}

void Datastore::unbindUpdateArray()
{
    vaU->unbind();
}

void Datastore::unbindRenderArray()
{
    vaU->unbind();
}

void Datastore::bindVertexBuffer()
{
    vb1->bind();
}

void Datastore::unbindVertexBuffer()
{
    vb1->unbind();
}

void Datastore::bindSubVertexBuffer()
{
    vb2->bind();
}

void Datastore::unbindSubVertexBuffer()
{
    vb2->unbind();
}

} // namespace GL