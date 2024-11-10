#include <iostream>
#include <iomanip>
#include <map>
class HeatFlow
{
    std::map<int, float> sources_and_sinks;
    double ini_temp, K;
    int num_of_sections;
    
    public:
    HeatFlow(double ini_temp, int num_of_sections, double K, 
             std::map<int, float>& sources_and_sinks);
    void tick();
    void pretty_print();
};
HeatFlow::HeatFlow(double ini_temp, int num_of_sections, double K, 
             std::map<int, float>& sources_and_sinks):
             ini_temp(ini_temp), num_of_sections(num_of_sections), 
             K(K), sources_and_sinks(sources_and_sinks){}
void HeatFlow::tick()
{
    std::map<int, float> new_sources_and_sinks = sources_and_sinks;

    for (auto it = sources_and_sinks.begin(); it != sources_and_sinks.end(); ++it) 
    {
        int current_section = it->first; 
        auto next_section = sources_and_sinks.find(current_section + 1); 
        auto prev_section = sources_and_sinks.find(current_section - 1); 
        if (sources_and_sinks[current_section] != 100.0) 
        {
            if (next_section != sources_and_sinks.end() && prev_section != sources_and_sinks.end())
            {
                new_sources_and_sinks[current_section] = it->second + K * (next_section->second - 2 * it->second + prev_section->second);
            }
            else if (prev_section == sources_and_sinks.end())  
            {
                if (next_section != sources_and_sinks.end()) {
                    new_sources_and_sinks[current_section] = it->second + K * (next_section->second - it->second);
                }
            }
            else if (next_section == sources_and_sinks.end()) 
            {
                if (prev_section != sources_and_sinks.end()) 
                {
                    new_sources_and_sinks[current_section] = it->second + K * (prev_section->second - it->second);
                }
            }
        }
    }
    sources_and_sinks = new_sources_and_sinks;
}

void HeatFlow::pretty_print()
{
     std::cout << "+";
    for (auto it = sources_and_sinks.begin(); it != sources_and_sinks.end(); ++it)
    {
        std::cout << "-------+";
    }
    std::cout << "\n|";
    for (auto it = sources_and_sinks.begin(); it != sources_and_sinks.end(); ++it) 
    {
        std::cout << " " << std::setw(5) << std::fixed << std::setprecision(1) << it->second << " |";
    }
    std::cout << "\n+";for (auto it = sources_and_sinks.begin(); it != sources_and_sinks.end(); ++it) 
    {
        std::cout << "-------+";
    }
    std::cout << "\n";
}
int main()
{
std::map<int, float> sources_and_sinks;

double ini_temp = 10;
int num_of_sections = 5;

double K = 0.1;
sources_and_sinks[4] = 100.0;
for (int i = 0; i < num_of_sections; ++i) 
    {
        if (sources_and_sinks.find(i) == sources_and_sinks.end()) 
        {  
            sources_and_sinks[i] = ini_temp;
        }
    }
HeatFlow h(ini_temp, num_of_sections, K, sources_and_sinks);
h.pretty_print();
h.tick();
h.pretty_print();

h.tick();
h.pretty_print();

    return 0;
}
