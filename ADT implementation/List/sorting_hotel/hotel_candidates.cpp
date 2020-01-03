#include "hotel_candidates.h"
#include <vector>

Hotel::Hotel(){}

Hotel::Hotel(int cost, int distance)
/*
  Post: Initialize Hotel with two given members: cost and distance.*/
{
  this->cost = cost;
  this->distance = distance;
}

void Hotel::operator=(Hotel& original)
{
  this->cost = original.cost;
  this->distance = original.distance;
}

Hotel* Hotel_lists_copy(Hotel* origin, int origin_size)
/*
  Post: Return a copy of the original hotels list.*/
{
  const int size = origin_size;
  Hotel* copy = new Hotel[size];
  for (int i = 0; i < size; i++)
    copy[i] = origin[i];
  return copy;
}

void sort_by_cost(Hotel* hotel_list, int size)
/*
  Post: Sort listed hotels with their cost using insertion sort algorithm.*/
{
  int first_unsorted, position;
  Hotel current;
  for (first_unsorted = 1; first_unsorted < size; first_unsorted++)
    if (hotel_list[first_unsorted].cost < hotel_list[first_unsorted - 1].cost) {
      position = first_unsorted;
      current = hotel_list[first_unsorted];
      do {
        hotel_list[position] = hotel_list[position - 1];
        position--;
      } while (position > 0 && current.cost < hotel_list[position - 1].cost);
      hotel_list[position] = current;
    }
}

void sort_by_distance(Hotel* hotel_list, int size)
/*
  Post: Sort listed hotels with their distance using insertion sort algorithm.*/
{
  int first_unsorted, position;
  Hotel current;
  for (first_unsorted = 1; first_unsorted < size; first_unsorted++)
    if (hotel_list[first_unsorted].distance < hotel_list[first_unsorted - 1].distance) {
        position = first_unsorted;
        current = hotel_list[first_unsorted];
        do {
          hotel_list[position] = hotel_list[position - 1];
          position--;
        } while (position > 0 && current.distance < hotel_list[position - 1].distance);
        hotel_list[position] = current;
    }
}

int find_candidates(Hotel* hotel_list, int size)
/*
  Post: Return the numbers of the candidate hotels that meet the standard.*/
{
  int min_cost, min_distance, count = 0;
  std::vector <int> condition1, condition2;
  Hotel* copy = Hotel_lists_copy(hotel_list, size);

  sort_by_distance(hotel_list, size);
  min_cost = hotel_list[0].cost;
  condition1.push_back(0);
  for (int i = 1; i < size; i++)
    if (min_cost > hotel_list[i].cost) {
      min_cost = hotel_list[i].cost;
      condition1.push_back(i);
    }

  sort_by_cost(copy, size);
  min_distance = copy[0].distance;
  condition2.push_back(0);
  for (int i = 1; i < size; i++)
    if (min_distance > copy[i].distance) {
      min_distance = copy[i].distance;
      condition2.push_back(i);
    }

  for (int i = 0; i < condition1.size(); i++)
    for (int j = 0; j < condition2.size(); j++)
      if (hotel_list[condition1[i]].cost == copy[condition2[j]].cost &&
        hotel_list[condition1[i]].distance == copy[condition2[j]].distance)
        count++;

  return count;
}