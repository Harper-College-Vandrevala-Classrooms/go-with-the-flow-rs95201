#include <iostream>
#include <vector>
#include <iomanip>

class HeatFlow
{
private:
    std::vector<double> sections;           
    double K;   
    double initial_temperature;
    int number_of_sections;                         
    std::vector<double> sources_and_sinks;  

public:
    HeatFlow(double initial_temperature, int number_of_sections, double K, 
             const std::vector<double> sources_and_sinks);
    void tick();
    void pretty_print();
};

HeatFlow::HeatFlow(double initial_temperature, int number_of_sections, double K, 
                   const std::vector<double> sources_and_sinks)
    : sections(number_of_sections, initial_temperature), K(K), sources_and_sinks(sources_and_sinks) 
{
    
    for (int i = 0; i < sources_and_sinks.size(); ++i) {
        if (sources_and_sinks[i] != 0.0 && i < number_of_sections) {
            sections[i] = sources_and_sinks[i];
        }
    }
}
void HeatFlow::tick() {
    std::vector<double> new_sections = sections;

    for (int i = 0; i < sections.size(); ++i) {
        if (sources_and_sinks[i] != 0.0) {
            continue;
        }
        double left_temp = (i > 0) ? sections[i - 1] : sections[i];
        double right_temp = (i < sections.size() - 1) ? sections[i + 1] : sections[i];
        new_sections[i] = sections[i] + K * (left_temp - 2 * sections[i] + right_temp);
    }

    sections = new_sections;
}
void HeatFlow::pretty_print() {
    std::cout << "+";
    for (int i = 0; i < sections.size(); ++i) {
        std::cout << "-------+";
    }
    std::cout << "\n|";
    for (double temp : sections) {
        std::cout << " " << std::setw(5) << std::fixed << std::setprecision(1) << temp << " |";
    }
    std::cout << "\n+";
    for (int i = 0; i < sections.size(); ++i) {
        std::cout << "-------+";
    }
    std::cout << "\n";
}

int main() {
    std::vector<double> sources_and_sinks = {100.0, 0.0, 0.0, 0.0, 0.0};  

    double initial_temperature = 10;
    int number_of_sections = 5;
    double K = 0.1;

    HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);
    h.pretty_print();

    h.tick();
    h.pretty_print();

    h.tick();
    h.pretty_print();

    return 0;
}
