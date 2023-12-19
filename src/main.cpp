#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "GraphTheory.h"
#include "cRunWatch.h"

raven::graph::sGraphData gd;

std::vector<std::vector<int>> vCycle;
std::vector<int> nodeCycleCount;

void read(const std::string &fname)
{
    std::ifstream ifs(fname);
    if (!ifs.is_open())
        throw std::runtime_error(
            "Cannot open input");

    std::string line;
    getline(ifs, line);
    while (ifs.good())
    {
        std::string type, src, dst;
        ifs >> type >> src >> dst;
        if (!ifs.good())
            break;
        gd.g.add(src, dst);
    }
}

// void write()
// {
//     std::ofstream ofs("../dat/output.txt");
//     if( ! ofs.is_open() )
//         throw std::runtime_error(
//             "Cannot open output file"        );
//     ofs << gd.g.text();
// }

void findCycles()
{
    raven::set::cRunWatch aWatcher("findCycles");

    /* find cycles in graph
    using modified depth first search
    in PathFinder graph theory library
    https://github.com/JamesBremner/PathFinder
    */
   
    vCycle = dfs_cycle_finder(gd);

}
void histogram()
{
    raven::set::cRunWatch aWatcher("histogram");

    nodeCycleCount.resize(gd.g.vertexCount());
    for (auto &vc : vCycle)
    {
        for (int v : vc)
        {
            nodeCycleCount[v]++;
        }
    }
}

main(int argc, char *argv[])
{
    raven::set::cRunWatch::Start();

    if (argc != 2)
    {
        std::cout << "Usage\n";
        exit(1);
    }
    read(argv[1]);

    findCycles();

    std::cout << vCycle.size() << " cycles found\n";

    histogram();

    std::cout << "Node\tCycles\n";
    for (int n = 0; n < nodeCycleCount.size(); n++)
    {
        std::cout << gd.g.userName(n) << "\t" << nodeCycleCount[n] << "\n";
    }

    raven::set::cRunWatch::Report();

    return 0;
}
