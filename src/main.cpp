#include <bits/stdc++.h>
#include <climits>
#include <limits>
#include <utility>

using namespace std;


class OriginalArrayIterator;

class OriginalArray{
    friend OriginalArrayIterator;
public:
    using iterator = OriginalArrayIterator;
    using Itr = iterator;

    OriginalArray(int* array, const uint &size)
        :array_(array), size_(size){
    }

    Itr begin() const;
    Itr end() const;

private:
    int* array_;
    uint size_;
};


class OriginalArrayIterator
    : public std::iterator<std::forward_iterator_tag, int>
{
    friend OriginalArray;
private:
    uint index_;
    const OriginalArray *my_class_;

    // The constructor should be private.
private:
    OriginalArrayIterator(){
        index_ = UINT_MAX;
        my_class_ = nullptr;
    };

    OriginalArrayIterator(const OriginalArray* my_class, int index)
        :index_(index), my_class_(my_class)
    {
        index_ = index;
        my_class_ = my_class;
    }

    // Copy constructor should be public.
public:
    OriginalArrayIterator(const OriginalArrayIterator& iterator){
        index_ = iterator.index_;
        my_class_ = iterator.my_class_;
    }

public:
    OriginalArrayIterator& operator++(){
        index_++;
        if(index_ > my_class_->size_) index_ = UINT_MAX;
        return *this;
    }

    OriginalArrayIterator& operator--(){
        if(index_ == 0){
            return *this;
        }

        index_--;
        return *this;
    }

    OriginalArrayIterator operator++(int){
        OriginalArrayIterator result = *this;
        result.index_++;
        if(result.index_ >= my_class_->size_) result.index_ = my_class_->size_;
        return result;
    }

    OriginalArrayIterator operator--(int){
        OriginalArrayIterator result = *this;

        if(result.index_ == 0){
            return result;
        }

        result.index_--;
        return result;
    }

    OriginalArrayIterator operator+(const uint& step){
        OriginalArrayIterator result = *this;
        result.index_ += step;
        if(result.index_ >= my_class_->size_) result.index_ = my_class_->size_;
        return result;
    }

    OriginalArrayIterator operator-(const uint& step){
        OriginalArrayIterator result = *this;

        if(step > result.index_){
            result.index_ = 0;
        }else{
            result.index_ -= step;
        }

        return result;
    }

    int operator-(const OriginalArrayIterator& other){
        return this->index_ - other.index_;
    }

    int operator>(const OriginalArrayIterator& other){
        return this->index_ > other.index_;
    }

    int operator<(const OriginalArrayIterator& other){
        return this->index_ < other.index_;
    }

    int& operator*(){
        static int dummy;
        return (index_ !=  my_class_->size_ ? my_class_->array_[index_] : dummy);
    };

    bool operator!=(const OriginalArrayIterator& iterator){
        return my_class_ != iterator.my_class_ || index_ != iterator.index_;
    }
    bool operator==(const OriginalArrayIterator& iterator){
        return !(*this != iterator);
    }
};


OriginalArrayIterator OriginalArray::begin() const{
    return OriginalArrayIterator(this, 0);
}


OriginalArrayIterator OriginalArray::end() const{
    return OriginalArrayIterator(this, size_);
}


void show(const OriginalArray& original_array){
    for(auto itr = original_array.begin(); itr != original_array.end(); ++itr){
        cout << *itr << endl;
    }
}


int main(){
    int array[] = {4, 3, 2, 1};

    OriginalArray original_array = OriginalArray(array, 4);

    cout << "Access by for loop" << endl;
    show(original_array);

    auto original_itr = original_array.begin();

    cout << "Update value via iterator" << endl;
    *original_itr += 1;
    show(original_array);

    cout << "Sort by stl library" << endl;
    sort(original_array.begin(), original_array.end());
    show(original_array);
}
