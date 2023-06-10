#include "MagicalContainer.hpp"
#include <iostream>
#include <stdexcept>
#include <stdexcept>

// #include <cmath>
using namespace std;
namespace ariel
{

    MagicalContainer::MagicalContainer() {}
    void MagicalContainer::addElement(int element)
    {
        auto in = _elements.insert(element);

        if (in.second)
        {
            const int *address = &(*in.first);

            _elements_ascending_order.push_back(address);

            if (_isPrime(element))
            {
                _elements_prime_order.push_back(address);
                sort(_elements_prime_order.begin(), _elements_prime_order.end(), [](const int *a, const int *b)
                     { return *a < *b; });
            }

            sort(_elements_ascending_order.begin(), _elements_ascending_order.end(), [](const int *a, const int *b)
                 { return *a < *b; });

            _elements_sidecross_order.clear();
            _elements_sidecross_order.reserve(_elements_ascending_order.size());

            size_t start = 0, end = _elements_ascending_order.size() - 1;

            while (start <= end && end != 0)
            {
                _elements_sidecross_order.push_back(_elements_ascending_order.at(start));

                if (start != end)
                    _elements_sidecross_order.push_back(_elements_ascending_order.at(end));

                start++;
                end--;
            }
        }
    }
    // int MagicalContainer::size(){ return ;}
    size_t MagicalContainer::size() const
    {
        return _elements.size();
    }

    void MagicalContainer::removeElement(int element)
    {
        auto it = _elements.find(element); // find function : https://cplusplus.com/reference/algorithm/find/

        if (it == _elements.end())
            throw std::runtime_error("Error: element not found");

        _elements.erase(element); // remove element from container

        if (_isPrime(element))
        {
            auto it_prime = find(_elements_prime_order.begin(), _elements_prime_order.end(), &(*it));
            _elements_prime_order.erase(it_prime); // remove element from prime iterator
        }

        auto it_ascending = find(_elements_ascending_order.begin(), _elements_ascending_order.end(), &(*it));
        _elements_ascending_order.erase(it_ascending); // remove element from ascending iterator

        auto it_sidecross = find(_elements_sidecross_order.begin(), _elements_sidecross_order.end(), &(*it));
        _elements_sidecross_order.erase(it_sidecross); // remove element from sidecross iterator
    }

    // copy constructor
    // MagicalContainer::MagicalContainer(MagicalContainer &other) : _container(other){}

    /*----------------------------------
    *AscendingIterator functions
    ----------------------------------*/
    // constructor
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container) : _container(container), _index(0) {}
    MagicalContainer::AscendingIterator::AscendingIterator(MagicalContainer &container, size_t index) : _container(container), _index(index) {}
    // assignment
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
    {
        if(&_container != &other._container){
            throw runtime_error("Cannot assign iterators of different containers");
        }

        if (this != &other)
        {
            _container = other._container;
            _index = other._index;
        }

        return *this;
    }
    // copy constructor
    MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other) noexcept
        : _container(other._container), _index(other._index) {}

    // dereference
    int MagicalContainer::AscendingIterator::operator*() const
    {
        if (_index > _container._elements_ascending_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        return *(_container._elements_ascending_order.at(_index));
    }
    // increment
    MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
    {
        if (_index > _container._elements_ascending_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        ++_index;
        return *this;
    }
    //
    bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &rhs) const
    {
        return _index == rhs._index;
    }

    bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &rhs) const
    {
        // return (_index!=rhs._index);
        return !(*this == rhs); // use of last function -operator==
    }

    bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
    {
        return _index > other._index;
        ;
    }

    bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
    {
        return !((*this > other || *this == other));
    }

    // MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
    // {
    //     _index = 0;
    //     return *this;
    // }

    /*----------------------------------
    *SideCrossIterator functions
    ----------------------------------*/
    // constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container)
        : _container(container), _index(0), forward(0), backward(static_cast<size_t>(container.size() - 1)), isForward(true) {}
    MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer &container, size_t index) : _container(container), _index(index) {}

    // assignment
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator &other)
    {
             if(&_container != &other._container){
            throw runtime_error("Cannot assign iterators of different containers");
        }

        if(this != &other){
            _container = other._container;
            _index=other._index;
            // forward = other.forward;
            // backward = other.backward;
            // isForward = other.isForward;
        }

        return *this;

    }

    // copy constructor
    MagicalContainer::SideCrossIterator::SideCrossIterator(const SideCrossIterator &other) noexcept : _container(other._container), _index(other._index), forward(other.forward), backward(other.backward), isForward(other.isForward) {}

    // dereference
    int MagicalContainer::SideCrossIterator::operator*() const
    {
        if (_index > _container._elements_sidecross_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        return *(_container._elements_sidecross_order.at(_index));
    }
    // increment
    MagicalContainer::SideCrossIterator &MagicalContainer::SideCrossIterator::operator++()
    {
        if (_index > _container._elements_sidecross_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        ++_index;
        return *this;
    }
    //
    bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator &rhs) const
    {
        return _index == rhs._index;
    }

    bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator &rhs) const
    {
        return !(*this == rhs);
    }

    bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator &other) const
    {
        return _index > other._index;
    }

    bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator &other) const
    {
        return !((*this > other || *this == other));
    }

    // MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
    // {
    //     forward = 0;
    //     backward = _container.getElements().size() - 1;
    //     isForward = true;
    //     return *this;
    // }

    /*----------------------------------
    *PrimeIterator functions
    ----------------------------------*/

    // constructor
    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container)
        : _container(container), _index(0) {}

    MagicalContainer::PrimeIterator::PrimeIterator(MagicalContainer &container, size_t index) : _container(container), _index(index) {}
    // assignment
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
    {
        if (&_container != &other._container)
        {
            throw runtime_error("Cannot assign iterators of different containers");
        }
        if (this != &other)
        {
            _container = other._container;
            _index = other._index;
        }
        return *this;
    }

    // copy constructor
    MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other) noexcept : _container(other._container), _index(other._index) {}

    // dereference
    int MagicalContainer::PrimeIterator::operator*() const
    {
        if (_index > _container._elements_prime_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        return *(_container._elements_prime_order.at(_index));
    }
    // increment
    MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
    {
        if (_index > _container._elements_prime_order.size())
        {
            throw std::out_of_range("Iterator out of range");
        }

        ++_index;
        return *this;
    }
    //
    bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &rhs) const
    {
        return _index == rhs._index;
    }

    bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &rhs) const
    {
        return !(*this == rhs);
    }

    bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
    {
        return _index > other._index;
        ;
    }

    bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
    {
        return !((*this > other || *this == other));
    }

    // MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
    // {
    //     _index = 0;
    //     return *this;
    // }

};
