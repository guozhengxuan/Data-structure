struct Hotel {
  int cost;
  int distance;
  Hotel();
  Hotel(int cost, int distance);
  void operator=(Hotel& original);
};

Hotel* Hotel_lists_copy(Hotel* origin);

void sort_by_cost(Hotel* hotel_list, int origin_size);

void sort_by_distance(Hotel* hotel_list, int size);

int find_candidates(Hotel* hotel_list, int size);