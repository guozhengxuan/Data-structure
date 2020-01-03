#include "hotel_candidates.h"
#include <iostream>

int main()
{
  int number;
  int cost, distance;
  std::cout << "Please enter the number of total hotels: ";
  std::cin >> number;
  const int size = number;
  Hotel* hotels = new Hotel[size];
  std::cout << "Please enter the cost and distance from the seashore of all the " << number << " hotels: " << std::endl;
  std::cout << "format: distance + space + cost + enter" << std::endl;
  std::cout << "Enter 0 to end inputing imformation of hotels." << std::endl;
  std::cout << "e.g  300 100" << std::endl;
  std::cout << "     100 300" << std::endl;
  std::cout << "     400 200" << std::endl;
  std::cout << "     200 400" << std::endl;
  std::cout << "     100 500" << std::endl;
  for (int i = 0; i < number; i++) {
    std::cin >> distance >> cost;
    hotels[i].cost = cost;
    hotels[i].distance = distance;
  }
  int candidates = find_candidates(hotels, number);
  std::cout << "Total number of candidate hotel is: " << candidates;
}
