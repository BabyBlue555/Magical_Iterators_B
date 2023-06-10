#include "MagicalContainer.hpp"
#include <iostream>
#include <stdexcept>
#include <stdexcept>


// #include <cmath>
using namespace std;
namespace ariel{
    
    MagicalContainer::MagicalContainer(){}
    void MagicalContainer::addElement(int element){}
    int MagicalContainer::size(){ return 1;}
    void MagicalContainer::removeElement(int element){}

    // copy constructor
   // MagicalContainer::MagicalContainer(MagicalContainer &other) : _container(other){}



/*----------------------------------
*AscendingIterator functions
----------------------------------*/
    // constructor
    MagicalContainer::AscendingIterator::AscendingIterator( MagicalContainer& container) : _container(container), _index(0){}
    // assignment
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator=(const AscendingIterator& other){
         return *this;
    }
    // copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator& other) noexcept
    : _container(other._container), _index(other._index) {}



    // dereference
    int MagicalContainer::AscendingIterator::operator*() const{
        if (_index > _container._elements_ascending_order.size())
            {
                throw std::out_of_range("Iterator out of range");
            }
					
		return *(_container._elements_ascending_order.at(_index));
    
    }
    // increment
    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++(){
        return *this;
    }
    //
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator& rhs) const{
        return 0;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator& rhs) const{
        return 0;
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator& other) const{
        return 0;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator& other) const{
        return 0;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::begin(){
        _index = 0;
        return *this;
    }

    MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::end(){
        _index = static_cast<size_t>(_container.size());
        return *this;
    }

/*----------------------------------
*SideCrossIterator functions
----------------------------------*/
    // constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& container)
    : _container(container),_index(0), forward(0), backward(static_cast<size_t>(container.size()-1)), isForward(true) {}
    // assignment
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other){
        return *this;
    }

    // copy constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) noexcept : 
    _container(other._container),_index(other._index), forward(other.forward), backward(other.backward), isForward(other.isForward) {}

    // dereference
    int MagicalContainer::SideCrossIterator::operator*() const{
        if (_index > _container._elements_sidecross_order.size())
            {
                throw std::out_of_range("Iterator out of range");
            }
					
		return *(_container._elements_sidecross_order.at(_index));
    
    }
    // increment
    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++(){
        return *this;
    }
    //
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& rhs) const{
        return 0;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& rhs) const{
        return 0;
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const{
        return 0;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const{
        return 0;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::begin(){
        forward = 0;
        backward = _container.getElements().size() - 1;
        isForward = true;
        return *this;
    }

    MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::end(){
        forward = _container.getElements().size();
        backward = 0;
        isForward = true;
        return *this;
    }

/*----------------------------------
*PrimeIterator functions
----------------------------------*/

    // constructor
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer& container)
    : _container(container), _index(0) {}
    // assignment
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator=(const PrimeIterator& other){
        return *this;
    }

    //copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator& other) noexcept:
    _container(other._container),_index(other._index){}


    // dereference
    int MagicalContainer::PrimeIterator::operator*() const{
           if (_index > _container._elements_prime_order.size())
            {
                throw std::out_of_range("Iterator out of range");
            }
					
		return *(_container._elements_prime_order.at(_index));
    
    
    }
    // increment
    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++(){
        return *this;
    }
    //
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator& rhs) const{
        return 0;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator& rhs) const{
        return 0;
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator& other) const{
        return 0;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator& other) const{
        return 0;
    }

    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::begin(){
        _index = 0;
        return *this;
    }


    MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::end(){
        _index = _container.getPrimeElements().size(); //last number
        return *this;
    }



};


