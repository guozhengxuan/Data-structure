//
// test.h
// testing performance of each searching algorithm.

#include "search_in_list.h"
#include <time.h>
#include <vector>
using namespace std;

typedef double clock_count;
typedef double compare_count;

clock_count abs_runtime(
  Error_code (*search_fuc)(const Ordered_list <Record>&, const Key&, int&, int&),
  const Ordered_list <Record>& the_list,
  const Key& target,
  int& position,
  const long times)
{
  int compare = 0;
  clock_t start, finish;
  start = clock();
  for (int i = 0; i < times; i++)
	(*search_fuc)(the_list, target, position, compare);
  finish = clock();
  clock_count duration = (double)(finish - start) / CLOCKS_PER_SEC;
  return duration;
}

compare_count avg_compare_of_key(
  Error_code(*search_fuc)(const Ordered_list <Record>&, const Key&, int&, int&),
  const Ordered_list <Record>& the_list,
  const vector <Key>& targets,
  int& position)
{
  int compare = 0;
  for (int i = 0; i < targets.size(); i++)
	(*search_fuc)(the_list, targets[i], position, compare);
  compare_count avg_compare = compare / double(targets.size());
  return avg_compare;
}