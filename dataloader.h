
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
  xt::xarray<int> indices;
  XArrayList<Batch<DType,LType>> batch;
  // TODO : add more member variables to support the iteration
 public:
  DataLoader(Dataset<DType, LType>* ptr_dataset, int batch_size,
             bool shuffle = true, bool drop_last = false) {
    // TODO implement
    this->ptr_dataset=ptr_dataset;
    this->batch_size=batch_size;
    this->shuffle=shuffle;
    this->drop_last=drop_last;
    if (shuffle){
      indices=xt::arange<int>(ptr_dataset->len());
      xt::random::shuffle(indices);
    } else {
      indices=xt::arange<int>(ptr_dataset->len());
    }
   
    int num_samples=ptr_dataset->len();
    int num_batches;
     batch=XArrayList<Batch<DType,LType>>(nullptr,0,num_batches);
  }
  virtual ~DataLoader() {
    // TODO implement
    delete [] ptr_dataset;
    batch_size=0;
  }
  Iterator begin() {
    // TODO implement
    return Iterator(this,0);
  }

  Iterator end() {
    // TODO implement
    return Iterator(this,batch_size);
  }


  
  // TODO implement forech
  class Iterator {
   public:
    // TODO implement contructor
    Iterator(DataLoader<DType,LType>*data_loader,int current_index){
      this->data_loader=data_loader;
      this->current_index=current_index;
    }

    Iterator& operator=(const Iterator& iterator) {
      // TODO implement
      if (this!=&iterator){
        data_loader=iterator.data_loader;
        current_index=iterator.current_index;
      }
      return *this;
    }

    Iterator& operator++() {
      // TODO implement
      ++current_index;
      return *this;
    }

    Iterator operator++(int) {
      // TODO implement
      Iterator temp=*this;
      ++(*this);
      return temp;
    }

    bool operator!=(const Iterator& other) const {
      // TODO implement
      return current_index!=other.current_index;
    }

    Batch<DType, LType> operator*() const {
      // TODO implement
      return data_loader->batch.get(current_index);
    }
    
    


   private:
    // TODO implement
    DataLoader<DType,LType>*data_loader;
    int current_index;
  };
};

#endif /* DATALOADER_H */
