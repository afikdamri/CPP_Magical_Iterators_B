#include "MagicalContainer.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace ariel
{
    /* My shorcut */
    typedef MagicalContainer::AscendingIterator short_Asc;
    typedef MagicalContainer::SideCrossIterator short_Sid;
    typedef MagicalContainer::PrimeIterator short_Pri;

    void MagicalContainer::addElement(int element)
    {
        size_t insertIndex = 0;
        while (insertIndex < elements.size() && elements[insertIndex] < element)
        {
            insertIndex++;
        }
        elements.push_back(0);
        for (size_t i = elements.size()-1; i > insertIndex; --i)
        {
            elements[i] = elements[i-1];
        }
        elements[insertIndex] = element;
    }

    void MagicalContainer::removeElement(int element)
    {
        auto iter = find(elements.begin(), elements.end(), element);
        if (iter == elements.end())
        {
            throw runtime_error("Element not found. (MagicalContainer::removeElement)");
        }
        elements.erase(iter);
    }

    int MagicalContainer::size() const
    {
        return elements.size();
    }

    bool MagicalContainer::getElement(int element) const
    {
        return find(elements.begin(), elements.end(), element) != elements.end();
    }


    /***** Reminder! short_Asc = MagicalContainer::AscendingIterator *****/
    short_Asc::AscendingIterator(MagicalContainer &container)
        : container(container)
    {
        iterator = container.elements.begin();
    }

    short_Asc &short_Asc::operator=(const AscendingIterator &other)
    {
        if (&container != &other.container)
            throw runtime_error("Same container.");

        iterator = other.iterator;
        return *this;
    }

    int short_Asc::operator*() const
    {
        return *iterator;
    }

    short_Asc &short_Asc::operator++()
    {
        if (iterator == container.elements.end())
            throw runtime_error("End of the container.");

        ++iterator;
        return *this;
    }

    bool short_Asc::operator==(const AscendingIterator &other) const
    {
        return iterator == other.iterator;
    }

    bool short_Asc::operator!=(const AscendingIterator &other) const
    {
        return !(*this == other);
    }

    bool short_Asc::operator<(const AscendingIterator &other) const
    {
        return *iterator < *other.iterator;
    }

    bool short_Asc::operator>(const AscendingIterator &other) const
    {
        return *iterator > *other.iterator;
    }

    short_Asc short_Asc::begin() const
    {
        AscendingIterator ascend(container);
        if (!container.elements.empty())
            ascend.iterator = container.elements.begin();
        
        return ascend;
    }

    short_Asc short_Asc::end() const
    {
        AscendingIterator ascend(container);
        if (!container.elements.empty())
            ascend.iterator = container.elements.end();
        return ascend;
    }

    /***** Reminder! short_Sid = MagicalContainer::SideCrossIterator *****/
    short_Sid::SideCrossIterator(MagicalContainer &container)
        : container(container)
    {
        if (container.elements.empty())
        {
            forwardIterator = container.elements.end();
            backwardIterator = container.elements.end();
            isBackwards = false;
        }
        else
        {
            forwardIterator = container.elements.begin();
            backwardIterator = prev(container.elements.end()); 
            isBackwards = true;
        }
    }

    short_Sid::SideCrossIterator(MagicalContainer &container, vector<int>::iterator forwar, vector<int>::iterator backforward, bool backwards)
     : container(container), forwardIterator(forwar), backwardIterator(backforward), isBackwards(backwards)
    {
    }

    bool short_Sid::operator==(const SideCrossIterator &other) const
    {
        int i = 0;
        if(forwardIterator == other.forwardIterator)
            i++;
        if(backwardIterator == other.backwardIterator)
            i++;
        if(isBackwards == other.isBackwards)
            i++;
        return  i == 3;
    }

    bool short_Sid::operator!=(const SideCrossIterator &other) const
    {
        return !(*this == other);
    }

    short_Sid &short_Sid::operator++()
    {
        if (forwardIterator == container.elements.end())
            throw runtime_error("End of the container.");
        
        if (forwardIterator == backwardIterator)
        {
            forwardIterator = container.elements.end();
            backwardIterator = container.elements.end();
            isBackwards = false;
            return *this;
        }

        if (isBackwards){
            ++forwardIterator;
            isBackwards = false;
        }
        else{
            --backwardIterator;
            isBackwards = true;
        }

        return *this;
    }

    int short_Sid::operator*()
    {
        if (isBackwards)
            return *forwardIterator;
        else
            return *backwardIterator;
    }

    bool short_Sid::operator<(const SideCrossIterator &other) const
    {
        return *forwardIterator < *other.forwardIterator;
    }

    bool short_Sid::operator>(const SideCrossIterator &other) const
    {
        return *forwardIterator > *other.forwardIterator;
    }

    short_Sid &short_Sid::operator=(const SideCrossIterator &other)
    {
        if (&container != &other.container)
            throw runtime_error("Same container.");

        if (this != &other)
        {
            container = other.container;
            forwardIterator = other.forwardIterator;
            backwardIterator = other.backwardIterator;
            isBackwards = other.isBackwards;
        }
        return *this;
    }

    short_Sid short_Sid::begin()
    {
        if (container.elements.empty())
            return end();
            
        SideCrossIterator cross(container, container.elements.begin(), prev(container.elements.end()), true);
        return cross;
    }

    short_Sid short_Sid::end()
    {
        SideCrossIterator cross(container, container.elements.end(), container.elements.end(), false);
        return cross;
    }

    /***** Reminder! MagicalContainer::PrimeIterator short_Pri *****/
    short_Pri::PrimeIterator(MagicalContainer &container)
        : container(container), iterator(container.elements.begin())
    {
        while (iterator != container.elements.end() && !isPrime(*iterator)){
            ++iterator;
        }
    }

    short_Pri &short_Pri::operator=(const PrimeIterator &other)
    {
        if (&container != &other.container)
            throw runtime_error("Same container.");

        iterator = other.iterator;
        return *this;
    }

    int short_Pri::operator*() const
    {
        return *iterator;
    }

    short_Pri &short_Pri::operator++()
    {
        if (iterator == container.elements.end())
            throw runtime_error("End of the container.");

        ++iterator;
        while (iterator != container.elements.end() && !isPrime(*iterator)){
            ++iterator;
        }
        return *this;
    }

    bool short_Pri::operator==(const PrimeIterator &other) const
    {
        return iterator == other.iterator;
    }

    bool short_Pri::operator!=(const PrimeIterator &other) const
    {
        return !(*this == other);
    }

    bool short_Pri::operator<(const PrimeIterator &other) const
    {
        return *iterator < *other.iterator;
    }

    bool short_Pri::operator>(const PrimeIterator &other) const
    {
        return *iterator > *other.iterator;
    }

    short_Pri short_Pri::begin() const
    {
        PrimeIterator primes(container);
        if (!container.elements.empty() && !isPrime(*container.elements.begin()))
            ++primes;
        
        return primes;
    }

    short_Pri short_Pri::end() const
    {
        PrimeIterator primes(container);
        primes.iterator = container.elements.end();
        return primes;
    }

    bool short_Pri::isPrime(int num) const
    {
        if (num < 2)
            return false;
            
        for (int i = 2; i <= sqrt(num); ++i)
        {
            if (num % i == 0)
                return false;
        }
        return true;
    }

} // namespace ariel
