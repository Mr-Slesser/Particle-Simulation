#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <vector>
#include "../Primitives/Vertex.h"

namespace GL
{
    class VertexData
    {
    private:
        std::vector<Vertex> data;

    public:
        VertexData(int size) {
            //data.reserve(size);
        }
        virtual ~VertexData() {}

        std::vector<Vertex>& get() { return data; }

        int size() {
            return sizeof(Vertex) * data.size();
        }

        void add(Vertex& v) {
            data.push_back(v);
        }

        void add(Vertex v[], int num) {
            for (int i = 0; i < num; ++i) {
                data.push_back(v[i]);
            }
        }

        void update(Vertex& v, int i) {
            data[i] = v;
        }

        void remove(int i) {
            // TODO: Test & handle not found case
            auto it = data.begin() + i;
            data.erase(it);
        }

        void clear() {
            data.clear();
        }
    };
    
} // namespace PT


#endif /* VERTEXDATA_H */
