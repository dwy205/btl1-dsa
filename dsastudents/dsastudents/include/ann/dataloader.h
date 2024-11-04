/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cppFiles/file.h to edit this template
 */

/* 
 * File:   dataloader.h
 * Author: ltsach
 *
 * Created on September 2, 2024, 4:01 PM
 */

#ifndef DATALOADER_H
#define DATALOADER_H
#include "ann/xtensor_lib.h"
#include "ann/dataset.h"

using namespace std;

template<typename DType, typename LType>
class DataLoader{
public:
    class Iterator;
private:
    Dataset<DType, LType>* ptr_dataset;
    int batch_size;
    bool shuffle;
    bool drop_last;
    int m_seed;
    xt::xarray<int> indices;
    /*TODO: add more member variables to support the iteration*/
public:
    DataLoader(Dataset<DType, LType>* ptr_dataset,
            int batch_size,
            bool shuffle=true,
            bool drop_last=false,int seed=-1){
        /*TODO: Add your code to do the initialization */
        this->ptr_dataset=ptr_dataset;
    this->batch_size=batch_size;
    this->shuffle=shuffle;
    this->drop_last=drop_last;
    m_seed=seed;
    if(shuffle){
      if (seed>=0){
      indices=xt::arange<int>(ptr_dataset->len());
      xt::random::seed(seed);
      xt::random::shuffle(indices);
    }else{
      indices=xt::arange<int>(ptr_dataset->len());
      xt::random::shuffle(indices);
    }} else {
       indices=xt::arange<int>(ptr_dataset->len());
    }
    
    }
    virtual ~DataLoader(){}

    
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// START: Section                                                     //
    /////////////////////////////////////////////////////////////////////////
    
    /*TODO: Add your code here to support iteration on batch*/
    Iterator begin() {
    // TODO implement
     return Iterator(this,0);
  }

  Iterator end() {

    return Iterator(this,ptr_dataset->len()/batch_size);
    // TODO implement
  }

  // TODO implement forech
   class Iterator {
    private:
    // TODO implement
    DataLoader<DType,LType>*data_loader;
    int current_index;
    

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
      
      int start=current_index*data_loader->batch_size; 
      int over=start+data_loader->batch_size;
      int num_batch=data_loader->ptr_dataset->len()/data_loader->batch_size;
      if (data_loader->drop_last==false && current_index==num_batch-1){over+=data_loader->ptr_dataset->len()%data_loader->batch_size;} 
      
      xt::svector<unsigned long> data_shape= data_loader->ptr_dataset->get_data_shape();
      xt::svector<unsigned long> label_shape= data_loader->ptr_dataset->get_label_shape();
      data_shape[0]=over-start;
      label_shape[0]=over-start;
      xt::svector<unsigned long> data_shape_vec(data_shape.begin(),data_shape.end());
      xt::svector<unsigned long> label_shape_vec(label_shape.begin(),label_shape.end());
      xt::xarray<DType>data(data_shape_vec);
      xt::xarray<LType>label(label_shape_vec);

  if (data_loader->ptr_dataset->len()<data_loader->batch_size){ return Batch<DType,LType>(data,label);}
      for (int i=start;i<over;i++){
        int index=data_loader->indices[i];
        DataLabel<DType,LType> sample=data_loader->ptr_dataset->getitem(index);
       xt::view(data,i-start)=sample.getData();
        if(label_shape.size()>0){
        xt::view(label,i-start)=sample.getLabel();
        } else {
          label=sample.getLabel();
        }
    }
    return Batch<DType,LType>(data,label);

    } 
    
    /////////////////////////////////////////////////////////////////////////
    // The section for supporting the iteration and for-each to DataLoader //
    /// END: Section                                                       //
    /////////////////////////////////////////////////////////////////////////
   };
};


#endif /* DATALOADER_H */

