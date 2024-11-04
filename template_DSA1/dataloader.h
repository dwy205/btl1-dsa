#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/dataset.h"
#include "ann/xtensor_lib.h"

using namespace std;

template <typename DType, typename LType>
class DataLoader {
 public:
  class Iterator;

 private:
  Dataset<DType, LType>* ptr_dataset;
  int batch_size;
  bool shuffle;
  bool drop_last;
  // TODO : add more member variables to support the iteration
 public:
  DataLoader(Dataset<DType, LType>* ptr_dataset, int batch_size,
             bool shuffle = true, bool drop_last = false) {
    // TODO implement
  }
  virtual ~DataLoader() {
    // TODO implement
  }

  Iterator begin() {
    return Iterator();
    // TODO implement
  }

  Iterator end() {
    return Iterator();
    // TODO implement
  }

  // TODO implement forech
  class Iterator {
   public:
    // TODO implement contructor
    Iterator() {}

    Iterator& operator=(const Iterator& iterator) {
      // TODO implement
      return this;
    }

    Iterator& operator++() {
      // TODO implement
      return *this;
    }

    Iterator operator++(int) {
      // TODO implement
      return *this;
    }

    bool operator!=(const Iterator& other) const {
      // TODO implement
      return false;
    }

    Batch<DType, LType> operator*() const {
      // TODO implement
      xt::xarray<DType> data;
      xt::xarray<LType> label;
      return Batch<DType, LType>(data, label);
    }

   private:
    Dataset<DType, LType>* ptr_dataset;
    // TODO implement
  };
};

#endif /* DATALOADER_H */
