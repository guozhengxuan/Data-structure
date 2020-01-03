//
// ordered_list.h
// implementation of ordered list which is derived from contiguous list.

#include "contiguous_list.h"

template <class Record>
class Ordered_list: public List <typename Record> {
public:
  Ordered_list();
  Error_code insert(const Record& data);
  Error_code insert(int position, const Record& data);
  Error_code replace(int position, const Record& data);
};

template <class Record>
Ordered_list <Record>::Ordered_list() {}

template <class Record>
Error_code Ordered_list <Record>::insert(const Record& data) {
  int position;
  for (position = 0; position < this->size(); position++) {
	Record list_data;
	this->retrieve(position, list_data);
	if (data >= list_data) break;
  }
  return List<Record>::insert(position, data);
}

template <class Record>
Error_code Ordered_list <Record>::insert(int position, const Record& data) {
  Record list_data;
  if (position > 0) {
	this->retrieve(position - 1, list_data);
	if (data < list_data)
	  return fail;
  }
  if (position < this->size()) {
	this->retrieve(position, list_data);
	if (data > list_data)
	  return fail;
  }
  return List <Record>::insert(position, data);
}

template <class Record>
Error_code Ordered_list <Record>::replace(int position, const Record& data) {
  Record list_data;
  if (position > 0) {
	this->retrieve(position - 1, list_data);
	if (data < list_data)
	  return fail;
  }
  if (position < this->size() - 1) {
	this->retrieve(position + 1, list_data);
	if (data > list_data)
	  return fail;
  }
  return List <Record>::replace(position, data);
}