#include <cctype>       // Provides toupper
#include <iostream>     // Provides cout and cin
#include <cstdlib>      // Provides EXIT_SUCCESS
#include <array>
#include <cassert>
#include "sequence.h"  // With value_type defined as double
using namespace std;
using namespace main_savitch_4;

// TYPEDEFS and MEMBER CONSTANTS

// CONSTRUCTORS and DESTRUCTOR
sequence::sequence (int initial_capacity){
    data = new value_type[initial_capacity];
    capacity = initial_capacity;
    used = 0;
    current_index = 0;
}

sequence::sequence (const sequence& source){
    data = new value_type[source.capacity];
    capacity = source.capacity;
    used = source.used;
    current_index = source.current_index;
    copy(source.data, source.data + used, data);

}

sequence::~sequence( ){
    delete [] data;
}

// MODIFICATION MEMBER FUNCTIONS

void sequence::resize(int new_capacity){
    value_type *larger_array;

    if (new_capacity == capacity){
        return;
    }

    if (new_capacity < used){
        new_capacity = used;
    }

    larger_array = new value_type[new_capacity];
    copy(data, data + used, larger_array);
    delete [ ] data;
    data = larger_array;
    capacity = new_capacity;
}

void sequence::start( ){
    if(used){
        current_index = 0;
    }
}

//     Precondition: is_item returns true.
//     Postcondition: If the current item was already the last item in the
//     sequence, then there is no longer any current item. Otherwise, the new
//     current item is the item immediately after the original current item.
void sequence::advance( ){
    if (is_item()) {
        if (current_index < used) {
            current_index++;
        }
    } else {
        current_index = used;
    }
}

void sequence::insert(const value_type& entry){
    int i;
    if(used == capacity) {
        resize(used + 1);
    }
    if (!is_item( )) current_index = 0;
    for (i = used; i > current_index; --i) {
       data[i] = data[i-1];
    }
    data[current_index] = entry;
    ++used;
}

void sequence::attach(const value_type& entry){
    int i;
    if(used == capacity) {
        resize(used + 1);
    }
    if (!is_item( )) current_index = 0;
    else current_index += 1;
    for (i = used; i > (current_index - 1); --i) {
        data[i + 1] = data[i];
    }
    data[current_index] = entry;
    ++used;
}

void sequence::remove_current( ){
    if (is_item()) {
        int last_index = used - 1;
        for (int i = current_index; i < used; ++i) {
            if (i != last_index) {
                data[i] = data[i + 1];
            }
        }
        data[last_index] = NULL;
        --used;
    }
}

void sequence::operator =(const sequence& source){
    value_type *new_data;

    if(this == &source){
        return;
    }

    if (capacity != source.capacity){
        new_data = new value_type[source.capacity];
        delete [] data;
        data = new_data;
        capacity = source.capacity;
    }

    used = source.used;
    copy(source.data, source.data + used, data);
}

// CONSTANT MEMBER FUNCTIONS
int sequence::size() const{
    return used;
}

bool sequence::is_item( ) const{
    if(current()){
        return true;// if there's something there it returns true;
    }
    else{
        return false;//no current item
    }
}

value_type sequence::current( ) const{
    return data[current_index];
}
